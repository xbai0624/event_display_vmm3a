#ifndef VALUE_TYPE_H
#define VALUE_TYPE_H

#include <string>
#include <vector>
#include <type_traits>

using std::string;
using std::vector;

class ValueType
{
    public:
        ValueType();
        ValueType(const vector<string> &);
        ~ValueType();

        template<typename T>
            typename std::enable_if<std::is_same<T, int>::value, T>::type val() const
            {
                int res = 0;
                try {
                    res = std::stoi(_content[0]);
                }
                catch(...) {
                }
                return res;
            }

        template<typename T>
            typename std::enable_if<std::is_same<T, float>::value, T>::type val() const
            {
                float res = 0;
                try {
                    res = std::stod(_content[0]);
                }
                catch(...) {
                }
                return res;
            }

        template<typename T>
            typename std::enable_if<std::is_same<T, bool>::value, T>::type val() const
            {
                bool res = false;
                if(_content[0] == "true")
                    res = true;
                return res;
            }

        template<typename T>
            typename std::enable_if<std::is_same<T, int>::value, vector<T>>::type arr() const
            {
                vector<int> res;
                for(auto &i: _content) {
                    int tmp = 0;
                    try {
                        tmp = std::stoi(i);
                    }
                    catch(...) {
                    }
                    res.push_back(tmp);
                }
                return res;
            }

        template<typename T>
            typename std::enable_if<std::is_same<T, float>::value, vector<T>>::type arr() const
            {
                vector<float> res;
                for(auto &i: _content) {
                    float tmp = 0;
                    try {
                        tmp = std::stod(i);
                    }
                    catch(...) {
                    }
                    res.push_back(tmp);
                }
                return res;
            }

    private:
        vector<string> _content;
};

#endif
