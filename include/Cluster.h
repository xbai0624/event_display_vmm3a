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

    std::vector<int> strips;
    std::vector<int> charge;
    std::vector<int> timing;
};

std::ostream& operator<<(std::ostream &os, const Cluster &c);

#endif
