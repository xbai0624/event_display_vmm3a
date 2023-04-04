#ifndef CLUSTERING_ALGORITHM_H
#define CLUSTERING_ALGORITHM_H

#include <vector>
#include "Config.h"
#include "VmmDecoderSolidProtoType.h"

class Cluster;

class ClusteringAlgorithm
{
    public:
        static ClusteringAlgorithm* Instance() {
            if(_instance == nullptr)
                _instance = new ClusteringAlgorithm();
            return _instance;
        }

        ~ClusteringAlgorithm();

        void group_cluster(
                std::vector<Cluster> &res,
                const std::vector<int> &ch,   // ch no 
                const std::vector<int> &adc,  // pdo
                const std::vector<int> &time, // tdo
                const std::vector<int> &bcid, // bcid
                const std::vector<int> &gray_bcid, // gray code decoded bcid
                const int &daq_time_s, // daq time s
                const int &daq_time_ns // daqtime ns
                );

        void group_cluster(
                std::vector<Cluster> &res,
                const solid_prototype::data_struct &event_data
                );
        void extract_hits(
                std::vector<solid_prototype::hit_struct> &hits,
                const solid_prototype::data_struct &event_data
                );

        void InitCuts();

    private:
        ClusteringAlgorithm() {
            InitCuts();
        }

        static ClusteringAlgorithm *_instance;

        // cuts for clustering
        int strip_threshold;
        int strip_tdo_min;
        int strip_tdo_max;
};

#endif
