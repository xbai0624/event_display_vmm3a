#ifndef CONFIG_H
#define CONFIG_H

#include "ValueType.h"

#include <unordered_map>
#include <string>
#include <vector>

class Config
{
    public:
        static Config* instance() {
            if(_instance == nullptr)
                _instance = new Config();
            return _instance;
        }
        ~Config();

        void init(const char* path);
        void Print();

        void __load_file(const char* path);
        void __convert_map();
        void __parse_line(const std::string &line,
                std::string &key, std::vector<std::string> &val);

        const std::unordered_map<std::string, ValueType> & get_config() const {
            return _config;
        }

    private:
        Config(){}
        static Config* _instance;

        std::unordered_map<std::string, std::vector<std::string>> m_cache;
        std::unordered_map<std::string, ValueType> _config;

        std::string tokens = " ,;:";
};

#endif
