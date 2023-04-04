#ifndef VMMDECODERSOLIDPROTOTYPE_H
#define VMMDECODERSOLIDPROTOTYPE_H

#include <vector>
#include <unordered_map>
#include <string>
#include <ostream>

namespace solid_prototype
{

#define NHITS 256

    class data_struct
    {
        public:
            unsigned int complete; // '1' = event complete
            unsigned int evt_num;
            unsigned int build_id;
            unsigned int time_1;
            unsigned int time_2;
            unsigned int num_hits; // number of valid hits in arrays that follow (max NHITS = 256 per event)
            //unsigned int hit_chan[NHITS];
            //unsigned int hit_strip[NHITS];
            //unsigned int hit_time[NHITS];
            //unsigned int hit_adc[NHITS];
            std::vector<unsigned int> hit_chan;
            std::vector<unsigned int> hit_strip;
            std::vector<unsigned int> hit_time;
            std::vector<unsigned int> hit_adc;

            unsigned int word_count;

            data_struct();
            data_struct(const data_struct &d);
            void clear();
    };

    std::ostream &operator<<(std::ostream &os, const data_struct &d);

    class hit_struct
    {
        public:
            unsigned int strip_no;
            unsigned int chan_no;
            std::vector<unsigned int> time;
            std::vector<unsigned int> adc;

            hit_struct();
            hit_struct(const hit_struct &d);
            void clear();
    };

    std::ostream &operator<<(std::ostream &os, const hit_struct &d);

    class VmmDecoderSolid
    {
        public:
            VmmDecoderSolid();
            ~VmmDecoderSolid();

            void SetRawFile(const char* path);
            void SetGEMChamberType(int t) {gem_chamber_type = t;}
            void Decode();
            const data_struct & GetEvent(int i) const;
            const std::vector<data_struct> & GetAllDecodedEvents() const {return decoded_data;}

        private:
            unsigned int decode_word(unsigned int data);
            unsigned int strip_map(unsigned int channel);

        private:
            data_struct event_data;
            std::string raw_file;

            std::vector<data_struct> decoded_data;

            bool i_print = false; // print raw data word decode information

            int max_event = -1;
            int event_count = 0;

            int gem_chamber_type = 0; // UVa GEM = 0; MSU GEM = 1
    };
};

#endif
