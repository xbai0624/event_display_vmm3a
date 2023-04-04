#include "ClusteringAlgorithm.h"
#include "Cluster.h"
#include <unordered_map>
#include <iostream>
#include <algorithm>

//#define DEBUG

ClusteringAlgorithm* ClusteringAlgorithm::_instance = nullptr;

ClusteringAlgorithm::~ClusteringAlgorithm()
{
}

void ClusteringAlgorithm::InitCuts()
{
    strip_threshold = Config::instance()->get_config().at("strip offline threshold").val<int>();
    strip_tdo_min = Config::instance()->get_config().at("strip tdo min").val<int>();
    strip_tdo_max = Config::instance()->get_config().at("strip tdo max").val<int>();
}

// clustering for GPVMM board
void ClusteringAlgorithm::group_cluster(
        std::vector<Cluster> &res,    // result buffer
        const std::vector<int> &ch,   // ch no 
        const std::vector<int> &adc,  // pdo
        const std::vector<int> &time, // tdo
        const std::vector<int> &bcid, // bcid
        const std::vector<int> &gray_bcid, // gray code decoded bcid
        const int &daq_time_s, // daq time s
        const int &daq_time_ns // daqtime ns
        )
{
    res.clear();

    std::vector<float> charge_temp;
    std::vector<int> strip_temp;
    std::vector<float> time_temp;
    std::vector<int> bcid_temp;
    std::vector<int> gray_bcid_temp;

    for(unsigned int i=0; i<ch.size(); ++i)
    {
        // cut strips with adc < strip threshold
        if(adc[i] < strip_threshold)
            continue;
        // tdo cut
        if(time[i] < strip_tdo_min || time[i] > strip_tdo_max)
            continue;

        if(charge_temp.size() > 0)
        {
            if( (ch[i] - strip_temp.back()) == 1) {
                strip_temp.push_back(ch[i]);
                charge_temp.push_back(adc[i]);
                time_temp.push_back(time[i]);
                bcid_temp.push_back(bcid[i]);
                gray_bcid_temp.push_back(gray_bcid[i]);
            }
            else {
                Cluster c;
                c.strips = strip_temp;
                c.charge = charge_temp;
                c.timing = time_temp;
                c.bcid = bcid_temp;
                c.gray_code_bcid = gray_bcid_temp;
                c.daq_time_s = daq_time_s;
                c.daq_time_ns = daq_time_ns;
                res.push_back(c);

                charge_temp.clear();
                strip_temp.clear();
                time_temp.clear();
                bcid_temp.clear();
                gray_bcid_temp.clear();

                strip_temp.push_back(ch[i]);
                charge_temp.push_back(adc[i]);
                time_temp.push_back(time[i]);
                bcid_temp.push_back(bcid[i]);
                gray_bcid_temp.push_back(gray_bcid[i]);
            }
        }
        else {
            strip_temp.push_back(ch[i]);
            charge_temp.push_back(adc[i]);
            time_temp.push_back(time[i]);
            bcid_temp.push_back(bcid[i]);
            gray_bcid_temp.push_back(gray_bcid[i]);
        }
    }

    if(charge_temp.size() > 0) {
        Cluster c;
        c.strips = strip_temp;
        c.charge = charge_temp;
        c.timing = time_temp;
        c.bcid = bcid_temp;
        c.gray_code_bcid = gray_bcid_temp;
        c.daq_time_s = daq_time_s;
        c.daq_time_ns = daq_time_ns;
        res.push_back(c);
    }
}

// extract hits for solid prototype board
void ClusteringAlgorithm::extract_hits(
                std::vector<solid_prototype::hit_struct> &hits,
                const solid_prototype::data_struct &event_data
        )
{
    hits.clear();

    // dynamic programming
    std::unordered_map<unsigned int, unsigned int> hit_table; // channel no - position in hits vector

    for(unsigned int i=0; i<event_data.num_hits; i++)
    {
        // new hit
        if(hit_table.find(event_data.hit_chan[i]) == hit_table.end())
        {
            unsigned int pos = hits.size();
            hit_table[event_data.hit_chan[i]] = pos;

            solid_prototype::hit_struct new_hit;
            new_hit.strip_no = event_data.hit_strip[i];
            new_hit.chan_no = event_data.hit_chan[i];

            hits.push_back(new_hit);
        }

        unsigned int pos = hit_table[event_data.hit_chan[i]];

        hits[pos].time.push_back(event_data.hit_time[i]);
        hits[pos].adc.push_back(event_data.hit_adc[i]);
    }

    //std::cout<<event_data<<std::endl;
    //std::cout<<"------ all hits ------ "<<std::endl;
    //for(auto &i: hits)
    //    std::cout<<i<<std::endl;
}

// clustering for solid prototype board
void ClusteringAlgorithm::group_cluster(
        std::vector<Cluster> &res,
        const solid_prototype::data_struct &event_data
        )
{
    res.clear();

    std::vector<solid_prototype::hit_struct> hits;
    extract_hits(hits, event_data);

    // sort hits according to strip no
    std::sort(hits.begin(), hits.end(),
            [](const solid_prototype::hit_struct &h1, const solid_prototype::hit_struct &h2) {
            if(h1.strip_no < h2.strip_no) return true;
            return false;
            }
            );

    std::vector<int> strip_temp;
    std::vector<float> adc_temp;
    std::vector<float> time_temp;

    // do the clustering
    for(unsigned int i=0; i<hits.size(); ++i)
    {
#ifdef DEBUG
        if(hits[i].adc.size() > 1) {
            std::cout<<"INTERESTING:: detected > 1 peaks on one strip."<<std::endl;
            std::cout<<event_data<<std::endl;
            std::cout<<hits[i]<<std::endl;
        }
#endif

        // cut strips with adc < strip threshold
        if(hits[i].adc[0] < (unsigned int)strip_threshold)
            continue;
        // tdo cut
        if(hits[i].time[0] < (unsigned int)strip_tdo_min || hits[i].time[0] > (unsigned int)strip_tdo_max)
            continue;

        // using strip no to do clustering
        int _strip = hits[i].strip_no;

        if(adc_temp.size() > 0)
        {
            if( (_strip - strip_temp.back()) == 1) {
                strip_temp.push_back(_strip);
                adc_temp.push_back(hits[i].adc[0]);
                time_temp.push_back(hits[i].time[0]);
            }
            else {
                Cluster c;
                c.strips = strip_temp;
                c.charge = adc_temp;
                c.timing = time_temp;
                res.push_back(c);

                adc_temp.clear();
                strip_temp.clear();
                time_temp.clear();

                strip_temp.push_back(_strip);
                adc_temp.push_back(hits[i].adc[0]);
                time_temp.push_back(hits[i].time[0]);
            }
        }
        else {
            strip_temp.push_back(_strip);
            adc_temp.push_back(hits[i].adc[0]);
            time_temp.push_back(hits[i].time[0]);
        }
    }

    if(adc_temp.size() > 0) {
        Cluster c;
        c.strips = strip_temp;
        c.charge = adc_temp;
        c.timing = time_temp;
        res.push_back(c);
    }

    //std::cout<<"--------------------------------"<<std::endl;
    //std::cout<<"hits: "<<std::endl;
    //for(auto &i: hits)
    //    std::cout<<i<<std::endl;

    //std::cout<<"clusters: "<<std::endl;
    //for(auto &i: res)
    //    std::cout<<i<<std::endl;
    //getchar();
}

