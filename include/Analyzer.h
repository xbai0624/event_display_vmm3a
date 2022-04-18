#ifndef ANALYZER_H
#define ANALYZER_H

#include "RootTree.h"
#include "histos.hpp"
#include "CalibrationConstants.hpp"
#include <TH1F.h>
#include <vector>

class Analyzer : public RootTree
{
    public:
        Analyzer(const char* path);
        Analyzer();
        ~Analyzer();

        void Analyze();

        std::string __parse_output_file_name();
        void Save();

        // for online
        void GetEvent(std::vector<TH1F *> &);
        void SetFile(const char* path);

        // for analysis
        void FillEvent(std::vector<std::vector<int>> *vv_pdo, 
                std::vector<std::vector<int>> *vv_tdo,
                std::vector<std::vector<int>> *vv_chNo,
                std::vector<std::vector<int>> *vv_bcid,
                std::vector<std::vector<int>> *vv_gray_bcid,
                std::vector<int> *v_daq_timestamp_s,
                std::vector<int> *v_daq_timestamp_ns);

    private:
        //friend class RootTree;

        std::vector<TH1F*> v_hits;
        std::vector<TH1F*> v_hits_timing;

        int online_event_id = 0;
        int run_number = -1;

        // histo manager
        histos::HistoManager<> histo_manager;

        // calibration constants
        calibration_constants::Calib<> calib;
};

#endif
