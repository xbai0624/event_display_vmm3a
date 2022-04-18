#ifndef CALIBRATION_CONSTANTS_HPP
#define CALIBRATION_CONSTANTS_HPP

#include <string>
#include <iostream>
#include <unordered_map>

#include "Cluster.h"

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;
using std::pair;
using std::fstream;

namespace calibration_constants {
    template<typename T=int> class Calib
    {
        public:
            Calib() {
                Load();
            };

            ~Calib() {
                m_gain_offset.clear();
            }

            void SetPath(const char* p) {
                path = p;
            }

            string GetPath() {
                return path;
            }

            void Load() {
                m_gain_offset.clear();

                fstream fin(path.c_str(), fstream::in);
                if(!fin.is_open()) {
                    cout<<"Error: cannot open file: "<<path<<endl;
                    exit(0);
                }

                int channel;
                float gain, offset;

                while(fin>>channel>>gain>>offset) {
                    m_gain_offset[channel] = pair<float, float>(gain, offset);
                }
            }

            const unordered_map<int, pair<float, float>> & GetContent() const
            {
                return m_gain_offset;
            }

            Cluster correct_cluster(const Cluster &c)
            {
                Cluster res = c;

                for(size_t i=0; i<res.strips.size(); ++i)
                {
                    res.charge[i] = ((float)res.charge[i] - m_gain_offset[res.strips[i]].second) / 
                        (float)m_gain_offset[res.strips[i]].first;
                }

                return res;
            }

        private:
            // hard code for now
            string path = "calibration_code/channel_gain_equalizer/channel_gain_offset.txt";
            unordered_map<int, pair<float, float>> m_gain_offset;
    };
};

#endif
