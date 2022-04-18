#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <ostream>

struct Cluster 
{
    Cluster();
    ~Cluster();

    float max_charge();
    float sum_charge();
    int size();
    float pos();
    std::vector<float> strip_timing_difference();
    float max_timing_difference();
    float average_timing_difference();

    std::vector<int> strips; // ch No
    std::vector<float> charge; // pdo
    std::vector<float> timing; // tdo

    std::vector<int> bcid;
    std::vector<int> gray_code_bcid; // gray code decoded bcid
    int daq_time_s;
    int daq_time_ns;
};

std::ostream& operator<<(std::ostream &os, const Cluster &c);

#endif
