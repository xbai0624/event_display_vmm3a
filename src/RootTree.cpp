#include "RootTree.h"

RootTree::RootTree(const char* path) : b_calibRun(false)
{
    _path = path;
}

RootTree::RootTree() : b_calibRun(false)
{
}

RootTree::~RootTree()
{
}

void RootTree::SetFile(const char* path)
{
    _path = path;
}

void RootTree::Init()
{
    _f = new TFile(_path.c_str());

    T_run = (TTree*) _f -> Get("run_properties");
    T_vmm = (TTree*) _f -> Get("vmm");

    // run properties
    T_run -> SetBranchAddress("runNumber", &f_runNumber);
    T_run -> SetBranchAddress("gain", &f_gain);
    T_run -> SetBranchAddress("tacSlope", &f_tacSlope);
    T_run -> SetBranchAddress("peakTime", &f_peakTime);
    T_run -> SetBranchAddress("dacCounts", &f_dacCounts);
    T_run -> SetBranchAddress("pulserCounts", &f_pulserCounts);
    T_run -> SetBranchAddress("tpSkew", &f_tpSkew);
    T_run -> SetBranchAddress("ckbc", &f_ckbc);
    T_run -> SetBranchAddress("angle", &f_angle);
    T_run -> SetBranchAddress("calibrationRun", &b_calibRun);

    // vmm event data
    T_vmm -> SetBranchAddress("eventFAFA", &f_eventNumberFAFA);
    T_vmm -> SetBranchAddress("triggerTimeStamp", &v_triggerTimeStamp);
    T_vmm -> SetBranchAddress("triggerCounter", &v_triggerCounter);
    T_vmm -> SetBranchAddress("boardId", &v_boardId);
    T_vmm -> SetBranchAddress("chip", &v_chipId);
    T_vmm -> SetBranchAddress("eventSize", &v_eventSize);
    T_vmm -> SetBranchAddress("daq_timestamp_s", &v_daq_timestamp_s); // new version
    T_vmm -> SetBranchAddress("daq_timestamp_ns", &v_daq_timestamp_ns); // new version

    T_vmm -> SetBranchAddress("art", &v_art);
    T_vmm -> SetBranchAddress("art_valid", &v_art_valid);
    T_vmm -> SetBranchAddress("art_trigger", &v_art_trigger);

    T_vmm -> SetBranchAddress("tdo", &vv_tdo);
    T_vmm -> SetBranchAddress("pdo", &vv_pdo);
    T_vmm -> SetBranchAddress("flag", &vv_flag);
    T_vmm -> SetBranchAddress("threshold", &vv_threshold);
    T_vmm -> SetBranchAddress("bcid", &vv_bcid);
    T_vmm -> SetBranchAddress("relbcid", &vv_relbcid);
    T_vmm -> SetBranchAddress("overflow", &vv_overflow);
    T_vmm -> SetBranchAddress("orbitCount", &vv_orbit_count);
    T_vmm -> SetBranchAddress("grayDecoded", &vv_grayDecoded);
    T_vmm -> SetBranchAddress("channel", &vv_channelId);
    T_vmm -> SetBranchAddress("febChannel", &vv_febChannelId);
    T_vmm -> SetBranchAddress("mappedChannel", &vv_mappedChannelId);

    if(IsCalibRun()) {
        T_vmm -> SetBranchAddress("calibrationRun", &b_calibRun);
        T_vmm -> SetBranchAddress("pulserCounts", &f_pulserCounts_calib);
        T_vmm -> SetBranchAddress("dacCounts", &f_dacCounts_calib);
        T_vmm -> SetBranchAddress("gain", &f_gain_calib);
        T_vmm -> SetBranchAddress("peakTime", &f_peakTime_calib);
        T_vmm -> SetBranchAddress("tpSkew", &f_tpSkew_calib);
        T_vmm -> SetBranchAddress("neighbor", &vv_neighbor_calib);
    }
}

bool RootTree::IsCalibRun()
{
    return false;
}
