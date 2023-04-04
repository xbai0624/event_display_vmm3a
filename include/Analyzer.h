#ifndef ANALYZER_H
#define ANALYZER_H

#include "RootTree.h"
#include "histos.hpp"
#include "CalibrationConstants.hpp"
#include "VmmDecoderSolidProtoType.h"
#include <TH1F.h>
#include <vector>
#include <map>

class Analyzer : public RootTree
{
    public:
        Analyzer(const char* path);
        Analyzer();
        ~Analyzer();

        void Analyze();
        void AnalyzeSolidType();

        std::string __parse_output_file_name();
        std::string __parse_gpvmm_output_file_name();
        std::string __parse_solidvmm_output_file_name();

        void Save();
        void SetSolidType(){is_solid_type = true;}
        void UnsetSolidType(){is_solid_type = false;}
        void SetGEMChamberType(int t) {
            vmm_decoder_solid -> SetGEMChamberType(t);
            vmm_decoder_solid -> Decode(); // need to redo decoding after chaning chamber type
        }

        // for online
        void GetEvent(std::vector<TH1F *> &);
        void GetGPVmmEvent(std::vector<TH1F*> &);
        void GetSolidVmmEvent(std::vector<TH1F*> &);
        void GetEvent2D(std::vector<TH2F *> &); // 2d histogram - solid board
        void GetSolidVmmEvent2D(std::vector<TH2F*> &); // 2d histogram - solid board
 
        void SetFile(const char* path);
        void SetOnlineEventId(int id){online_event_id = id;}

        // for analysis
        void FillEvent(std::vector<std::vector<int>> *vv_pdo, 
                std::vector<std::vector<int>> *vv_tdo,
                std::vector<std::vector<int>> *vv_chNo,
                std::vector<std::vector<int>> *vv_bcid,
                std::vector<std::vector<int>> *vv_gray_bcid,
                std::vector<int> *v_daq_timestamp_s,
                std::vector<int> *v_daq_timestamp_ns);

        const std::map<std::string, TH1*> &GetResultHistos1D()
        {
            return histo_manager.get_histos_1d();
        }

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

        // analysis for solid prototype board
        bool is_solid_type = true;
        solid_prototype::VmmDecoderSolid *vmm_decoder_solid = nullptr;
};

#endif
