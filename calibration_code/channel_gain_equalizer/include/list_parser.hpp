#ifndef TXT_PARSER_HPP
#define TXT_PARSER_HPP

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using std::unordered_map;
using std::cout;
using std::endl;
using std::string;
using std::fstream;

template<typename T=string> class ListParser
{
    public:
        ListParser(){}
        ~ListParser(){}

        void setPath(const char* p) {
            path = p;
        }

        void trim(string &line) {
            if(line.size() <= 0)
                return;
            size_t p1 = line.find_first_not_of(' ');
            size_t p2 = line.find_last_not_of(' ');

            line = line.substr(p1, p2-p1+1);
        }

        void load() {
            // format: #  Threshold DAC(int), Test pulse(int), run(string) 
            fstream f(path.c_str(), fstream::in);
            string cache;

            while(std::getline(f, cache))
            {
                trim(cache);
                if(cache.size() <= 0) continue;
                if(cache[0] == '#') continue;

                std::istringstream iss(cache);
                string threshold, pulser, run;
                iss >> threshold >> pulser >> run;
                int pulse;
                try {
                    pulse = stoi(pulser);
                } catch(...) {
                    cout<<"Error: cannot convert string to int."<<endl;
                }

                __content[pulse] = run;
            }
        }

        unordered_map<int, string> & get_content() {
            return __content;
        }

        void print() {
            for(auto &i: __content)
                cout<<i.first<<": "<<i.second<<endl;
        }

    private:
        string path;
        unordered_map<int, string> __content;
};

#endif
