#include "Cluster.h"
#include <iomanip>
#include <cmath>

Cluster::Cluster()
{
    strips.clear();
    charge.clear();
    timing.clear();

    bcid.clear();
    gray_code_bcid.clear();
}

Cluster::~Cluster()
{
}

int Cluster::size()
{
    return (int) strips.size();
}

int Cluster::max_charge()
{
    if(strips.size() <= 0)
        return -9999;

    int c = charge[0];
    for(size_t i=0; i<charge.size(); ++i)
    {
        if(c < charge[i])
            c = charge[i];
    }

    return c;
}

int Cluster::sum_charge()
{
    int s = 0;
    for(auto &i: charge)
        s += i;
    return s;
}

float Cluster::pos()
{
    if(size() <= 0)
        return -99999.;

    float s = (float)sum_charge();

    const float pitch = 0.4;

    float tmp = 0;
    for(int i=0; i<size(); ++i)
    {
        tmp += strips[i] * pitch * charge[i];
    }
    tmp /= s;

    return tmp;
}

std::vector<int> Cluster::strip_timing_difference()
{
    std::vector<int> res;

    if(strips.size() <= 0)
        return res;

    size_t max_charge_index = 0;
    int max_charge = charge[0];
    for(size_t i=1; i<charge.size(); ++i)
    {
        if(charge[i] <= max_charge)
            continue;

        max_charge = charge[i];
        max_charge_index = i;
    }

    // get timing difference relative to seed strip
    for(size_t i=0; i<timing.size(); ++i)
    {
        if(i == max_charge_index)
            continue;

        int diff = timing[max_charge_index] - timing[i];

        res.push_back(diff);
    }

    return res;
}

float Cluster::max_timing_difference()
{
    std::vector<int> timing_vec = strip_timing_difference();

    float res = 0;
    if(timing_vec.size() <= 0)
        return res;

    for(auto &i: timing_vec) {
        if(res < abs(i))
            res = (float)abs(i);
    }

    return res;
}

float Cluster::average_timing_difference()
{
    std::vector<int> timing_vec = strip_timing_difference();

    float avg = 0;
    if(timing_vec.size() <= 0)
        return avg;

    for(auto &i: timing_vec)
        avg += i;

    avg /= (float)timing_vec.size();

    return avg;
}

std::ostream & operator<<(std::ostream &os, const Cluster &c)
{
    os<<"strip: ";
    for(auto &i: c.strips)
        os<<std::setfill(' ')<<std::setw(6)<<i;
    os<<std::endl;
    os<<"adc: ";
    for(auto &i: c.charge)
        os<<std::setfill(' ')<<std::setw(6)<<i;
    os<<std::endl;
    os<<"timing: ";
    for(auto &i: c.timing)
        os<<std::setfill(' ')<<std::setw(6)<<i;
    os<<std::endl;
    return os;
}
