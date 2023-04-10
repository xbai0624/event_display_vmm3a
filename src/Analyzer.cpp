#include "Analyzer.h"
#include "Cluster.h"
#include "Config.h"
#include "ClusteringAlgorithm.h"

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
    InitTree();
    vmm_decoder_solid = new solid_prototype::VmmDecoderSolid();
}

Analyzer::Analyzer()
{
    histo_manager.init();
    InitTree();
    vmm_decoder_solid = new solid_prototype::VmmDecoderSolid();
}

Analyzer::~Analyzer()
{
}

void Analyzer::InitTree()
{
    T = new TTree("T", "VMM analysis result tree");
    T -> Branch("strip_index", &T_strip, "strip_index/I");
    T -> Branch("hit_adc", &T_hit_adc, "hit_adc/I");
    T -> Branch("hit_time", &T_hit_time, "hit_index/I");
}

void Analyzer::SetFile(const char* path)
{
    online_event_id = 0;
    histo_manager.reset();

    // for SoLID VMM prototype board analysis
    if(is_solid_type)
    {
        vmm_decoder_solid -> SetRawFile(path);
        vmm_decoder_solid -> Decode();
        _path = path;
        return;
    }

    // for GP VMM board type analysis
    _path = path;

    if(_f != nullptr)
        if(!_f->IsZombie())
            _f -> Close();

    Init();
}

// for online monitoring
void Analyzer::GetEvent(std::vector<TH1F*> &online_hits)
{
    if(is_solid_type)
        GetSolidVmmEvent(online_hits);
    else
        GetGPVmmEvent(online_hits);
}

// for online monitoring
void Analyzer::GetEvent2D(std::vector<TH2F*> &online_hits)
{
    if(is_solid_type){
        GetSolidVmmEvent2D(online_hits);
        return;
    }

    std::cout<<"ERROR: only solid prototype board has 2D histograms implemented."<<std::endl;
}

// for online monitoring - Solid VMM board, online_event_id will be incremented in Viewer class
void Analyzer::GetSolidVmmEvent(std::vector<TH1F*> &online_hits)
{
    int i = 0; // VMM chip index
    TH1F *h = new TH1F(Form("h_evt_%d_chip_%d", online_event_id, i),
            Form("h_evt_%d_chip_%d", online_event_id, i),
            140, -5, 135);
    h -> GetXaxis() -> SetTitle("VMM channel index");
    h -> GetYaxis() -> SetTitle("peak [adc counts]");

    TH1F *h_timing = new TH1F(Form("h_timing_evt_%d_chip_%d", online_event_id, i),
            Form("h_timing_evt_%d_chip_%d", online_event_id, i),
            140, -5, 135);
    h_timing -> GetXaxis() -> SetTitle("VMM channel index");
    h_timing -> GetYaxis() -> SetTitle("peak timing [adcc counts]");

    solid_prototype::data_struct event_data = vmm_decoder_solid -> GetEvent(online_event_id);

    if(event_data.num_hits > 0)
    {
        for(unsigned int i=0; i<event_data.num_hits; i++)
        {
            h -> SetBinContent(event_data.hit_strip[i], event_data.hit_adc[i]);
            h_timing -> SetBinContent(event_data.hit_strip[i], event_data.hit_time[i]);
        }
    }

    online_hits.push_back(h);
    online_hits.push_back(h_timing);
}

// for online monitoring - Solid VMM board, online_event_id will be incremented in Viewer class
void Analyzer::GetSolidVmmEvent2D(std::vector<TH2F*> &online_hits)
{
    solid_prototype::data_struct event_data = vmm_decoder_solid -> GetEvent(online_event_id);

    // get time range
    int time_low = -99999, time_high = 0;
    if(event_data.num_hits > 0)
    {
        for(unsigned int i=0; i<event_data.num_hits; i++)
        {
            int hit_time = event_data.hit_time[i];
            if(time_low <= -90000.0) time_low = hit_time;
            if(time_low > hit_time) time_low = hit_time;
            if(time_high < hit_time) time_high = hit_time;
        }
    }
    time_high += 10;
    time_low -= 10; if(time_low < 0) time_low = 0;
    int time_nbins = (int)(time_high - 0);

    int i = 0; // VMM chip index
    TH2F *h = new TH2F(Form("h_evt_%d_chip_%d", online_event_id, i),
            Form("h_evt_%d_chip_%d", online_event_id, i),
            140, -5, 135, time_nbins, 0, time_high);
    h -> GetXaxis() -> SetTitle("VMM channel index");
    h -> GetXaxis() -> SetTitleOffset(1.5);
    h -> GetXaxis() -> CenterTitle();
    h -> GetYaxis() -> SetTitle("hit time [adc counts]");
    h -> GetYaxis() -> SetTitleOffset(1.5);
    h -> GetYaxis() -> SetRangeUser(time_low, time_high);
    h -> GetYaxis() -> CenterTitle();
    h -> GetZaxis() -> SetTitle("peak [adc counts]");
    h -> GetZaxis() -> SetTitleOffset(1.0);
 
    if(event_data.num_hits > 0)
    {
        for(unsigned int i=0; i<event_data.num_hits; i++)
        {
            h -> SetBinContent(event_data.hit_strip[i]+5, event_data.hit_time[i], event_data.hit_adc[i]);
        }
    }

    online_hits.push_back(h);
}

// for online monitoring - GP VMM board, online_event_id will be incremented in Viewer class
void Analyzer::GetGPVmmEvent(std::vector<TH1F*> &online_hits)
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

void Analyzer::AnalyzeSolidType()
{
    // reset all histos
    histo_manager.reset();

    auto & all_events = vmm_decoder_solid -> GetAllDecodedEvents();

    std::vector<Cluster> clusters;
    for(auto &i: all_events)
    {
        // xb debug, for now discard events with all strips fired
        //if(i.num_hits > 20) continue;

        int index = 0;
        for(auto &adc: i.hit_adc)
        {
            //if( i.hit_time[index] >= 40 && i.hit_time[index] <= 50)
            histo_manager.histo_1d<float>("h_6bit_strip_adc") -> Fill(adc);

            T_strip = (int)i.hit_strip[index];
            T_hit_adc = (int)adc;
            T_hit_time = (int)i.hit_time[index];
            T -> Fill();

            histo_manager.histo_2d<float>("h2DADC_vs_Strip") -> Fill(T_strip, T_hit_adc);
            histo_manager.histo_2d<float>("h2DTime_vs_Strip") -> Fill(T_strip, T_hit_time);

            index++;
        }

        for(auto &strip_index: i.hit_strip)
            histo_manager.histo_1d<float>("h_6bit_strip_index") -> Fill(strip_index);

        // clustering
        ClusteringAlgorithm::Instance() -> group_cluster(clusters,  i);

        for(auto &c: clusters)
        {
            //if(c.size() >= 2 && c.size() <= 10)
            {
                histo_manager.histo_1d<float>("h_6bit_cluster_adc") -> Fill(c.sum_charge());
                histo_manager.histo_1d<float>("h_6bit_cluster_pos") -> Fill(c.pos());
                histo_manager.histo_1d<float>("h_6bit_cluster_size") -> Fill(c.size());

                auto timing_diff = c.strip_timing_difference();
                for(auto &i: timing_diff)
                    histo_manager.histo_1d<float>("h_6bit_strip_timing_reso") -> Fill(i);
            }
        }
    }
}

// save results
void Analyzer::Save()
{
    std::string output = __parse_output_file_name();
    std::cout<<"results saved to: "<<output<<std::endl;
    histo_manager.save(output.c_str(), T);
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

    // do clustering
    std::vector<Cluster> clusters;
    ClusteringAlgorithm::Instance() -> group_cluster(clusters, vmm_ch, vmm_pdo, vmm_tdo, vmm_bcid, vmm_gray_bcid, daqTimeStamp_s, daqTimeStamp_ns);

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
    if(is_solid_type) {
        return __parse_solidvmm_output_file_name();
    }
    else {
        return __parse_gpvmm_output_file_name();
    }
}

std::string Analyzer::__parse_gpvmm_output_file_name()
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

std::string Analyzer::__parse_solidvmm_output_file_name()
{
    std::string res = "Rootfiles/results.root";
    if(_path.size() < 3)
        return res;

    // input file format: /some/path/xxxx.bin
    if(_path.find(".bin") == std::string::npos){
        return res;
    }

    size_t p = _path.find_last_of("/");
    size_t e = _path.find_last_of(".");
    string tmp1 = _path.substr(p+1, e);
    std::cout<<tmp1<<std::endl;

    res = "Rootfiles/" + tmp1 + ".root";
    return res;
}
