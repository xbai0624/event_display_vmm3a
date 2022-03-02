#include "Config.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using std::fstream;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::istringstream;

Config* Config::_instance = nullptr;

Config::~Config()
{
    m_cache.clear();
    _config.clear();
}

void Config::init(const char* path)
{
    __load_file(path);
    __convert_map();
}

void Config::Print()
{
    cout<<"============================================================="<<endl;
    cout<<"cuts applied: "<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    for(auto &i: m_cache) {
        cout<<std::setfill(' ')<<std::setw(36)<<i.first;
        cout<<" : ";
        for(auto &j: i.second)
            cout<<std::setfill(' ')<<std::setw(10)<<j;
        cout<<endl;
    }
    cout<<"============================================================="<<endl;
}

void Config::__load_file(const char* path)
{
    fstream input_file(path, fstream::in);
    if(!input_file.is_open()) {
        cout<<"Warning:: couldn't load config file for cuts"
            <<endl;
    }

    string line;
    while(std::getline(input_file, line))
    {
        string key;
        vector<string> val;

        __parse_line(line, key, val);

        if(key.size() > 0) {
            m_cache[key] = val;
        }
    }
}

void Config::__parse_line(const string &line, string &key, vector<string> &val)
{
    // replace tokens with white space
    auto __replace_tokens = [&](const string & s) -> string
    {
        string l = s;
        char whitespace = ' ';
        for(char &c: tokens)
        {
            if(c == whitespace)
                continue;
            size_t pos = l.find(c);
            if(pos != string::npos) {
                l.replace(pos, 1, 1, whitespace);
            }
        }
        return l;
    };

    // trim leading and trailing spaces
    auto __trim_space = [&](const string &s) -> string
    {
        if(s.size() <= 0)
            return string("");

        size_t pos1 = s.find_first_not_of(tokens);
        size_t pos2 = s.find_last_not_of(tokens);

        if(pos2 < pos1)
            return string("");

        size_t length = pos2 - pos1;

        return s.substr(pos1, length+1);
    };

    // separate key and values
    auto __parse_key_value_string = [&](const string &s, string &key, string &val)
    {
        size_t length = s.size();
        if(length <= 0)
            return;

        size_t pos = s.find('=');

        if(pos == string::npos || pos == 0 || pos == (length -1) )
        {
            cout<<"Warning:: format is incorrect, must be: \"key = value\" format."
                <<endl;
            return;
        }

        key = s.substr(0, pos);
        val = s.substr(pos+1, length - pos + 1);
    };

    // remove comments
    auto __remove_comments = [&](const string &s) -> string
    {
        string res = s;

        size_t length = s.size();
        if(length <= 0)
            return res;

        // comments are leading by '#'
        size_t pos = s.find('#');

        if(pos == 0) {
            res.clear();
            return res;
        }

        if(pos == string::npos)
            return res;

        res = s.substr(0, pos);
        return res;
    };

    // parse value list
    auto __separate_vals = [&](const string &s, vector<string> &res)
    {
        res.clear();
        string temp = __trim_space(s);
        temp = __replace_tokens(temp);

        istringstream iss(temp);
        string t;
        while(iss >> t)
        {
            res.push_back(t);
        }
    };

    // parse line
    string temp1 = __remove_comments(line);
    string temp2;
    __parse_key_value_string(temp1, key, temp2);
    key = __trim_space(key);
    __separate_vals(temp2, val);

}

void Config::__convert_map()
{
    _config.clear();
    for(auto &i: m_cache) {
        _config[i.first] = ValueType(i.second);
    }
}
