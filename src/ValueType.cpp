#include "ValueType.h"

ValueType::ValueType()
{
}

ValueType::ValueType(const vector<string> &v)
{
    _content.clear();
    for(auto &i: v)
        _content.push_back(i);
}

ValueType::~ValueType()
{
    _content.clear();
}
