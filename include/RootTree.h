#ifndef ROOT_TREE_H
#define ROOT_TREE_H

#include <TTree.h>
#include <TFile.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

class RootTree
{
    public:
        RootTree(const char* path);
        RootTree();
        ~RootTree();

        void Init();
        void SetFile(const char* path);
        bool IsCalibRun();

    protected:
        string _path;
        TFile *_f = nullptr;
        TTree *T_run = nullptr;
        TTree *T_vmm = nullptr;

        // run properties
        int f_runNumber;
        int f_gain;
        int f_tacSlope;
        int f_peakTime;
        int f_dacCounts;
        int f_pulserCounts;
        int f_tpSkew; // in steps
        int f_angle;
        int f_ckbc; // CKBC freqency, used for converted TP skew
        bool b_calibRun;

        // vmm data
        int f_eventNumberFAFA;
        int f_daqCnt;

        vector<int> *v_boardId = 0;
        vector<int> *v_triggerTimeStamp = 0;
        vector<int> *v_triggerCounter = 0;
        vector<int> *v_chipId = 0;
        vector<int> *v_eventSize = 0;
        vector<int> *v_daq_timestamp_s = 0;
        vector<int> *v_daq_timestamp_ns = 0;
        vector<int> *v_art = 0; // ART
        vector<int> *v_art_valid = 0; // ART
        vector<int> *v_art_trigger = 0; // ART

        vector<vector<int>> *vv_pdo = 0;
        vector<vector<int>> *vv_tdo = 0;
        vector<vector<int>> *vv_flag = 0;
        vector<vector<int>> *vv_threshold = 0;
        vector<vector<int>> *vv_bcid = 0;
        vector<vector<int>> *vv_relbcid = 0;
        vector<vector<int>> *vv_overflow = 0;
        vector<vector<int>> *vv_orbit_count = 0;
        vector<vector<int>> *vv_grayDecoded = 0;
        vector<vector<int>> *vv_channelId = 0;
        vector<vector<int>> *vv_febChannelId = 0;
        vector<vector<int>> *vv_mappedChannelId = 0;

        // if calibration run
        int f_pulserCounts_calib;
        double f_gain_calib;
        int f_peakTime_calib;
        int f_dacCounts_calib;
        int f_tpSkew_calib;
        vector<vector<int>> *vv_neighbor_calib;

    private:
};

#endif
