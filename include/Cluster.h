#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <ostream>

struct Cluster 
{
    Cluster();
    ~Cluster();

    int max_charge();
    int sum_charge();
    int size();
    float pos();
    std::vector<int> strip_timing_difference();
    float max_timing_difference();
    float average_timing_difference();

    std::vector<int> strips; // ch No
    std::vector<int> charge; // pdo
    std::vector<int> timing; // tdo

    std::vector<int> bcid;
    std::vector<int> gray_code_bcid; // gray code decoded bcid
    int daq_time_s;
    int daq_time_ns;
};

std::ostream& operator<<(std::ostream &os, const Cluster &c);

#endif
