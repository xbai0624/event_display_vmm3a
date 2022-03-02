#include "Analyzer.h"
#include "Cluster.h"
#include "Config.h"

#include <iostream>
#include <iomanip>
#include <cassert>
#include <chrono>

using std::cout;
using std::endl;
using std::setfill;
using std::setw;
using std::left;

Analyzer::Analyzer(const char* path) : RootTree(path) 
{
    histo_manager.init();
}

Analyzer::Analyzer()
{
    histo_manager.init();
}

Analyzer::~Analyzer()
{
}

void Analyzer::SetFile(const char* path)
{
    _path = path;

    if(_f != nullptr)
        if(!_f->IsZombie())
            _f -> Close();

    Init();

    // reset online event id counter
    online_event_id = 0;
}

// for online monitoring
void Analyzer::GetEvent(std::vector<TH1F*> &online_hits)
{
    T_vmm -> GetEntry(online_event_id);

    int number_of_vmm_chips = vv_pdo -> size();

    for(int i=0; i<number_of_vmm_chips; i++) 
    {
        int fired_strips = vv_pdo->at(i).size();

        TH1F *h = new TH1F(Form("h_evt_%d_chip_%d", online_event_id, i),
                Form("h_evt_%d_chip_%d", online_event_id, i),
                100, -20, 80);
        h -> GetXaxis() -> SetTitle("VMM channel index");
        h -> GetYaxis() -> SetTitle("peak [adc counts]");

        TH1F *h_timing = new TH1F(Form("h_timing_evt_%d_chip_%d", online_event_id, i),
                Form("h_timing_evt_%d_chip_%d", online_event_id, i),
                100, -20, 80);
        h_timing -> GetXaxis() -> SetTitle("VMM channel index");
        h_timing -> GetYaxis() -> SetTitle("peak timing [adcc counts]");

        for(int j=0; j<fired_strips; j++) {
            h -> SetBinContent(vv_channelId->at(i).at(j) + 20, vv_pdo->at(i).at(j));
            h_timing -> SetBinContent(vv_channelId->at(i).at(j) + 20, vv_tdo->at(i).at(j));
        }

        online_hits.push_back(h);
        online_hits.push_back(h_timing);
    }

    online_event_id++;
}

// for analysis, hit process etc
void Analyzer::Analyze()
{
    cout<<"total runs: "<<T_run -> GetEntries()<<endl;
    cout<<"total entries for all runs summed together:"<<T_vmm -> GetEntries()<<endl;

    int N = T_vmm -> GetEntries();

    // run properties
    for(int entry = 0; entry < T_run -> GetEntries(); entry++)
    {
        //T_run -> GetEntry(entry);
    }


    // reset all histos
    histo_manager.reset();

    // get start time
    auto start = std::chrono::high_resolution_clock::now();

    // vmm data
    for(int entry = 0; entry < N; entry++)
    {
        //cout<<"event id: "<<entry<<endl;
        T_vmm -> GetEntry(entry);

        int number_of_vmm_chips = vv_pdo -> size();
        //cout<<"number of vmm chips: "<<number_of_vmm_chips<<endl;

        for(int i=0; i<number_of_vmm_chips; i++) 
        {
            int fired_strips = vv_pdo->at(i).size();
            //h_chip_occupancy -> Fill(fired_strips);
            /*
               TH1F *h = new TH1F(Form("h_evt_%d_chip_%d", entry, i),
               Form("h_evt_%d_chip_%d", entry, i),
               100, -20, 80);
               h -> GetXaxis() -> SetTitle("VMM channel index");
               h -> GetYaxis() -> SetTitle("peak [adc counts]");

               TH1F *h_timing = new TH1F(Form("h_timing_evt_%d_chip_%d", entry, i),
               Form("h_timing_evt_%d_chip_%d", entry, i),
               100, -20, 80);
               h_timing -> GetXaxis() -> SetTitle("VMM channel index");
               h_timing -> GetYaxis() -> SetTitle("peak timing [adcc counts]");

               for(int j=0; j<fired_strips; j++) {
               h -> SetBinContent(vv_channelId->at(i).at(j) + 20, vv_pdo->at(i).at(j));
               h_timing -> SetBinContent(vv_channelId->at(i).at(j) + 20, vv_tdo->at(i).at(j));
               }

               v_hits.push_back(h);
               v_hits_timing.push_back(h_timing);
               */
        }

        // analyze event
        FillEvent(vv_pdo, vv_tdo, vv_channelId);
    }

    // get end time
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    cout<<"Time elapsed: "<<elapsed_time.count() <<" seconds."<<endl;
}

void Analyzer::Save()
{
    std::string output = __parse_output_file_name();
    std::cout<<"results saved to: "<<output<<std::endl;

    histo_manager.save(output.c_str());
}

void Analyzer::FillEvent(std::vector<std::vector<int>> *m_pdo,
        std::vector<std::vector<int>> *m_tdo,
        std::vector<std::vector<int>> *m_chNo)
{
    assert(m_pdo->size() == m_tdo->size());
    assert(m_pdo->size() == 1);
    assert(m_chNo->size() == m_tdo->size());

    auto &vmm_pdo = m_pdo -> at(0);
    auto &vmm_tdo = m_tdo -> at(0);
    auto &vmm_ch = m_chNo -> at(0);

    int strip_threshold = Config::instance()->get_config().at("strip offline threshold").val<int>();
 
    // group cluster, first round, no cut
    auto group_cluster = [&](const std::vector<int> &ch, const std::vector<int> &adc,
            const std::vector<int> &time)
        -> std::vector<Cluster>
        {
            std::vector<Cluster> res;

            std::vector<int> charge_temp;
            std::vector<int> strip_temp;
            std::vector<int> time_temp;

            for(size_t i=0; i<ch.size(); ++i)
            {
                // cut strips with adc < strip threshold
                if(adc[i] < strip_threshold)
                    continue;

                if(charge_temp.size() > 0)
                {
                    if( (ch[i] - strip_temp.back()) == 1) {
                        strip_temp.push_back(ch[i]);
                        charge_temp.push_back(adc[i]);
                        time_temp.push_back(time[i]);
                    }
                    else {
                        Cluster c;
                        c.strips = strip_temp;
                        c.charge = charge_temp;
                        c.timing = time_temp;
                        res.push_back(c);

                        charge_temp.clear();
                        strip_temp.clear();
                        time_temp.clear();
                        strip_temp.push_back(ch[i]);
                        charge_temp.push_back(adc[i]);
                        time_temp.push_back(time[i]);
                    }
                }
                else {
                    strip_temp.push_back(ch[i]);
                    charge_temp.push_back(adc[i]);
                    time_temp.push_back(time[i]);
                }
            }

            if(charge_temp.size() > 0) {
                Cluster c;
                c.strips = strip_temp;
                c.charge = charge_temp;
                c.timing = time_temp;
                res.push_back(c);
            }
            return res;
        };

    // do clustering
    auto clusters = group_cluster(vmm_ch, vmm_pdo, vmm_tdo);
    /*
    // debug
    for(auto &i: vmm_ch)
    std::cout<<std::setfill(' ')<<std::setw(6)<<i;
    std::cout<<std::endl<<std::endl;
    for(auto &i: vmm_pdo)
    std::cout<<std::setfill(' ')<<std::setw(6)<<i;
    std::cout<<std::endl<<std::endl;

    for(auto &i: vmm_tdo)
    std::cout<<std::setfill(' ')<<std::setw(6)<<i;
    std::cout<<std::endl<<std::endl;

    std::cout<<"grouped custers:"<<std::endl; 
    for(auto &i: clusters)
    cout<<i;
    std::cout<<std::endl<<std::endl;

    getchar();
    */

    // cluster size cut
    int cluster_min = Config::instance()->get_config().at("min cluster size").val<int>();
    int cluster_max = Config::instance()->get_config().at("max cluster size").val<int>();
    // cut strip min cluster adc
    int seed_strip_adc_min = Config::instance()->get_config().at("seed strip min peak ADC").val<int>();
    int seed_strip_adc_max = Config::instance()->get_config().at("seed strip max peak ADC").val<int>();
    // cut on cluster timing
    float max_timing = Config::instance()->get_config().at("max timing difference").val<float>();
    // cut on cluster sum adc
    float min_sum_adc = Config::instance()->get_config().at("min cluster adc sum").val<float>();
    vector<float> cluster_pos_cut = Config::instance()->get_config().at("x cluster position cut").arr<float>();

    for(auto &c: clusters)
    {
        if(c.size() < cluster_min || c.size() > cluster_max)
            continue;
        if(c.max_charge() < seed_strip_adc_min || c.max_charge() > seed_strip_adc_max)
            continue;
        if(c.sum_charge() < min_sum_adc)
            continue;
        if(c.max_timing_difference() > max_timing)
            continue;
        if(c.pos() < cluster_pos_cut[0] || c.pos() > cluster_pos_cut[1])
            continue;

        histo_manager.histo_1d<float>("h_occupancy_vmm0") -> Fill(c.size());

        vector<int> timing_diff_vec = c.strip_timing_difference();
        for(auto &i: timing_diff_vec)
            histo_manager.histo_1d<float>("hStripTimingDifference") -> Fill(i);

        int nStrip = c.size();

        for(int strip=0; strip<nStrip; ++strip){
            histo_manager.histo_1d<float>("hStripAdcDistributionPlaneX0") -> Fill(c.charge[strip]);
            histo_manager.histo_1d<float>("hStripIndexDistributionPlaneX0") -> Fill(c.strips[strip]);

            // strip adc
            histo_manager.histo_1d<float>(Form("hADCDistributionVMM0_Ch%d",c.strips[strip])) -> Fill(c.charge[strip]);
            // strip timing
            histo_manager.histo_1d<float>(Form("hTimingDistributionVMM0_Ch%d",c.strips[strip])) -> Fill(c.timing[strip]);
 
            // strip adc and timing 2d
            histo_manager.histo_2d<float>("h2DADCVMM0") -> Fill(c.strips[strip], c.charge[strip]);
            histo_manager.histo_2d<float>("h2DTimingVMM0") -> Fill(c.strips[strip], c.timing[strip]);
        }

        //if(c.pos() >= 0. && c.pos() <= 25.)
        //if(c.size() == 2 || c.size() == 3 || c.size() == 4)
        histo_manager.histo_1d<float>("hClusterAdcDistributionPlaneX0") -> Fill(c.sum_charge());
        histo_manager.histo_1d<float>("hClusterPosDistributionPlaneX0") -> Fill(c.pos());
        histo_manager.histo_1d<float>("hClusterSizeDistributionPlaneX0") -> Fill(c.size());
    }
}

std::string Analyzer::__parse_output_file_name()
{
    std::string res = "Rootfiles/results.root";
    if(_path.size() < 10)
        return res;

    // input file format: /some/path/run_xxxx.root
    if(_path.find(".root") == std::string::npos){
        return res;
    }

    size_t length = _path.size();
    string tmp1 = _path.substr(length-9, 9);
    string tmp2 = _path.substr(length-9, 4);
    try {
        run_number = std::stoi(tmp2);
    }
    catch(...) {
        std::cerr<<"Warning Failed to parse run number from input file name."<<endl;
    }

    res = "Rootfiles/results_" + tmp1;
    return res;
}
