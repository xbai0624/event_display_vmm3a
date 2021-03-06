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

// for analysis, hit/cluster process etc
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
        }

        // analyze event
        FillEvent(vv_pdo, vv_tdo, vv_channelId, vv_bcid, vv_grayDecoded,
                v_daq_timestamp_s, v_daq_timestamp_ns);
    }

    // get end time
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    cout<<"Time elapsed: "<<elapsed_time.count() <<" seconds."<<endl;
}

// save results
void Analyzer::Save()
{
    std::string output = __parse_output_file_name();
    std::cout<<"results saved to: "<<output<<std::endl;

    histo_manager.save(output.c_str());
}

void Analyzer::FillEvent(std::vector<std::vector<int>> *m_pdo,
        std::vector<std::vector<int>> *m_tdo,
        std::vector<std::vector<int>> *m_chNo,
        std::vector<std::vector<int>> *m_bcid,
        std::vector<std::vector<int>> *m_gray_bcid,
        std::vector<int> *v_daq_timestamp_s,
        std::vector<int> *v_daq_timestamp_ns)
{
    assert(m_pdo->size() == m_tdo->size());
    assert(m_pdo->size() == 1);
    assert(m_chNo->size() == m_tdo->size());

    auto &vmm_pdo = m_pdo -> at(0);
    auto &vmm_tdo = m_tdo -> at(0);
    auto &vmm_ch = m_chNo -> at(0);
    auto &vmm_bcid = m_bcid -> at(0);
    auto &vmm_gray_bcid = m_gray_bcid -> at(0);
    int daqTimeStamp_s = v_daq_timestamp_s -> at(0);
    int daqTimeStamp_ns = v_daq_timestamp_ns -> at(0);

    int strip_threshold = Config::instance()->get_config().at("strip offline threshold").val<int>();
    int strip_tdo_min = Config::instance()->get_config().at("strip tdo min").val<int>();
    int strip_tdo_max = Config::instance()->get_config().at("strip tdo max").val<int>();

    // group cluster, first round, no cut
    auto group_cluster = [&](
            const std::vector<int> &ch,   // ch no 
            const std::vector<int> &adc,  // pdo
            const std::vector<int> &time, // tdo
            const std::vector<int> &bcid, // bcid
            const std::vector<int> &gray_bcid, // gray code decoded bcid
            const int &daq_time_s, // daq time s
            const int &daq_time_ns // daqtime ns
            )
        -> std::vector<Cluster>
        {
            std::vector<Cluster> res;

            std::vector<float> charge_temp;
            std::vector<int> strip_temp;
            std::vector<float> time_temp;
            std::vector<int> bcid_temp;
            std::vector<int> gray_bcid_temp;

            for(size_t i=0; i<ch.size(); ++i)
            {
                // cut strips with adc < strip threshold
                if(adc[i] < strip_threshold)
                    continue;
                // tdo cut
                if(time[i] < strip_tdo_min || time[i] > strip_tdo_max)
                    continue;

                if(charge_temp.size() > 0)
                {
                    if( (ch[i] - strip_temp.back()) == 1) {
                        strip_temp.push_back(ch[i]);
                        charge_temp.push_back(adc[i]);
                        time_temp.push_back(time[i]);
                        bcid_temp.push_back(bcid[i]);
                        gray_bcid_temp.push_back(gray_bcid[i]);
                    }
                    else {
                        Cluster c;
                        c.strips = strip_temp;
                        c.charge = charge_temp;
                        c.timing = time_temp;
                        c.bcid = bcid_temp;
                        c.gray_code_bcid = gray_bcid_temp;
                        c.daq_time_s = daq_time_s;
                        c.daq_time_ns = daq_time_ns;
                        res.push_back(c);

                        charge_temp.clear();
                        strip_temp.clear();
                        time_temp.clear();
                        bcid_temp.clear();
                        gray_bcid_temp.clear();

                        strip_temp.push_back(ch[i]);
                        charge_temp.push_back(adc[i]);
                        time_temp.push_back(time[i]);
                        bcid_temp.push_back(bcid[i]);
                        gray_bcid_temp.push_back(gray_bcid[i]);
                    }
                }
                else {
                    strip_temp.push_back(ch[i]);
                    charge_temp.push_back(adc[i]);
                    time_temp.push_back(time[i]);
                    bcid_temp.push_back(bcid[i]);
                    gray_bcid_temp.push_back(gray_bcid[i]);
                }
            }

            if(charge_temp.size() > 0) {
                Cluster c;
                c.strips = strip_temp;
                c.charge = charge_temp;
                c.timing = time_temp;
                c.bcid = bcid_temp;
                c.gray_code_bcid = gray_bcid_temp;
                c.daq_time_s = daq_time_s;
                c.daq_time_ns = daq_time_ns;
                res.push_back(c);
            }
            return res;
        };

    // do clustering
    auto clusters = group_cluster(vmm_ch, vmm_pdo, vmm_tdo, vmm_bcid, vmm_gray_bcid, daqTimeStamp_s, daqTimeStamp_ns);

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

        vector<float> timing_diff_vec = c.strip_timing_difference();
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

            // strip bcid
            histo_manager.histo_1d<float>(Form("hBCIDVMM0_Ch%d", c.strips[strip])) -> Fill(c.bcid[strip]);
            histo_manager.histo_1d<float>(Form("hGrayBCIDVMM0_Ch%d", c.strips[strip])) -> Fill(c.gray_code_bcid[strip]);
        }

        //if(c.pos() >= 0. && c.pos() <= 25.)
        //if(c.size() == 2 || c.size() == 3 || c.size() == 4)
        histo_manager.histo_1d<float>("hClusterAdcDistributionPlaneX0") -> Fill(c.sum_charge());
        histo_manager.histo_1d<float>("hClusterPosDistributionPlaneX0") -> Fill(c.pos());
        histo_manager.histo_1d<float>("hClusterSizeDistributionPlaneX0") -> Fill(c.size());

        // clusters after calibration
        Cluster temp = calib.correct_cluster(c);
        histo_manager.histo_1d<float>("hClusterChargeDistributionPlaneX0") -> Fill(temp.sum_charge());
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
