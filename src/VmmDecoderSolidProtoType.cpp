#include "VmmDecoderSolidProtoType.h"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace solid_prototype
{
    data_struct::data_struct(): complete(0), evt_num(0),
    build_id(0), time_1(0), time_2(0), num_hits(0)
    {
        hit_chan.clear();
        hit_strip.clear();
        hit_time.clear();
        hit_adc.clear();

        word_count = 0;
    };

    data_struct::data_struct(const data_struct &d)
    {
        complete = d.complete; evt_num = d.evt_num;  build_id = d.build_id;
        time_1 = d.time_1; time_2 = d.time_2; num_hits = d.num_hits;

        for(unsigned int i=0; i<d.num_hits; i++)
        {
            hit_chan.push_back(d.hit_chan[i]);
            hit_strip.push_back(d.hit_strip[i]);
            hit_time.push_back(d.hit_time[i]);
            hit_adc.push_back(d.hit_adc[i]);
        }

        word_count = d.word_count;
    }

    void data_struct::clear()
    {
        complete = 0; evt_num = 0;  build_id = 0;
        time_1 = 0; time_2 = 0; num_hits = 0;

        hit_chan.clear();
        hit_strip.clear();
        hit_time.clear();
        hit_adc.clear();

        word_count = 0;
    }

    std::ostream &operator<<(std::ostream &os, const data_struct &d)
    {
        os<<std::setfill(' ')<<std::setw(6)<<"chan"
            <<std::setfill(' ')<<std::setw(6)<<"strip"
            <<std::setfill(' ')<<std::setw(6)<<"adc"
            <<std::setfill(' ')<<std::setw(6)<<"time"
            <<std::endl;

        for(unsigned int i=0; i<d.num_hits; i++)
        {
            os<<std::setfill(' ')<<std::setw(6)<<d.hit_chan[i]
                <<std::setfill(' ')<<std::setw(6)<<d.hit_strip[i]
                <<std::setfill(' ')<<std::setw(6)<<d.hit_adc[i]
                <<std::setfill(' ')<<std::setw(6)<<d.hit_time[i]
                <<std::endl;
        }

        return os;
    }

    hit_struct::hit_struct() : strip_no(9999), chan_no(9999)
    {
        time.clear();
        adc.clear();
    }

    hit_struct::hit_struct(const hit_struct &d)
        : strip_no(d.strip_no), chan_no(d.chan_no), time(d.time), adc(d.adc)
    {
    }

    void hit_struct::clear()
    {
        strip_no = 0; chan_no = 0;
        time.clear(); adc.clear();
    }

    std::ostream &operator<<(std::ostream &os, const hit_struct &d)
    {
        os<<std::setfill(' ')<<std::setw(6)<<"chan"
            <<std::setfill(' ')<<std::setw(6)<<d.chan_no
            <<std::endl
            <<std::setfill(' ')<<std::setw(6)<<"strip"
            <<std::setfill(' ')<<std::setw(6)<<d.strip_no
            <<std::endl;
        os<<std::setfill(' ')<<std::setw(6)<<"adc:";
        for(auto &i: d.adc)
            os<<std::setfill(' ')<<std::setw(6)<<i;
        os<<std::endl;
        os<<std::setfill(' ')<<std::setw(6)<<"time:";
        for(auto &i: d.time)
            os<<std::setfill(' ')<<std::setw(6)<<i;
        os<<std::endl;

        return os;
    }

    VmmDecoderSolid::VmmDecoderSolid()
    {
        decoded_data.clear();
    }

    VmmDecoderSolid::~VmmDecoderSolid()
    {
    }

    void VmmDecoderSolid::Decode()
    {
        if(raw_file.size() <= 0) {
            std::cout<<"ERROR: raw input file not set."<<std::endl;
            return;
        }

        std::fstream file(raw_file.c_str(), std::ios::in|std::ios::binary);
        if(!file.is_open()) {
            std::cout<<"ERROR: Cannot open input file: "<<raw_file<<std::endl;
            return;
        }
        file.seekg(0); // back to the start of the file

        decoded_data.clear(); // clear for decoding

        int event_word_count = 0, total_word_count = 0;
        unsigned int complete;
        unsigned int buffer;

        std::cout<<"Decoding VMM raw event file: "<<raw_file<<"..."<<std::endl;

        while(!file.eof())
        {
            if(max_event > 0 && event_count > max_event)
                return;

            file.read((char*)&buffer, sizeof(unsigned int));
            //std::cout<<"event: "<<event_count<<std::endl;

            complete = decode_word(buffer);
            event_word_count++;
            total_word_count++;

            if(complete == 1) // EVENT TRAILER word
            {
                event_count++;
                decoded_data.push_back(event_data);
            }
            else if(complete == 2) // EVENT HEADER detected with NO proceding EVENT TRAILER
            {
                event_count++;
                event_word_count = 1; // reset for next event
                decoded_data.push_back(event_data);
            }
            else {
                //std::cout<<"WARNING: complete = "<<complete<<std::endl;
            }
        }
        file.clear(); // return error state of file after hitting EOF
        file.close();

        std::cout<<"decoding done. total events: "<<decoded_data.size()<<std::endl<<std::endl;
    }

    unsigned int VmmDecoderSolid::decode_word(unsigned int data)
    {
        unsigned int data_type = (data & 0x38000000) >> 27;

        static unsigned int hits = 0;
        static unsigned last_complete = 1; // EVENT TRAILER in preceeding data word - initialize

        unsigned int complete = 0;

        switch(data_type)
        {
            case 4: // EVENT HEADER
                {
                    hits = 0;
                    // event_data.time_1 = 0; // don't initialize times to allow debug of missing trailer word
                    // event_data.time_2 = 0;
                    event_data.num_hits = 0;
                    event_data.hit_chan.clear();
                    event_data.hit_strip.clear();
                    event_data.hit_time.clear();
                    event_data.hit_adc.clear();
                    event_data.word_count = 0;
                    event_data.complete = 0;

                    event_data.evt_num = (data & 0x00FFFFFF); // event number
                    event_data.build_id = (data & 0x07000000) >> 24; // builder id

                    if(i_print)
                        printf("\n%8X - EVENT HEADER (id = %d) - event number = %d\n", data, event_data.build_id, event_data.evt_num);
                    if(last_complete != 1)
                    {
                        //printf("\n******** ERROR - EVENT HEADER NOT PRECEEDED BY EVENT TRAILER ********\n");
                        complete = 2;
                    }
                    last_complete = 0;
                }
                break;

            case 2: // TRIGGER TIME 1
                {
                    event_data.time_1 = (data & 0x3FFFFFF);
                    last_complete = 0;
                    if(i_print)
                        //printf("%8X - TRIGGER TIME 1 - time = %LX\n", data, event_data.time_1);
                        printf("%8X - TRIGGER TIME 1 - time = %8X\n", data, event_data.time_1);
                }
                break;

            case 3: // TRIGGER TIME 2
                {
                    event_data.time_2 = (data & 0x00FFFFFF);
                    last_complete = 0;
                    if(i_print)
                        //printf("%8X - TRIGGER TIME 2 - time = %LX\n", data, event_data.time_2);
                        printf("%8X - TRIGGER TIME 2 - time = %8X\n", data, event_data.time_2);
                }
                break;

            case 1: // HIT DATA
                {
                    //event_data.hit_chan[hits] = (data & 0x001FC000) >> 14; // vmm channel
                    //event_data.hit_strip[hits] = strip_map( event_data.hit_chan[hits] ); // detector physical channel index
                    //event_data.hit_time[hits] = (data & 0x00003FC0) >> 6; // hit time
                    //event_data.hit_adc[hits] = (data & 0x000003F); // 6-bit ADC

                    event_data.hit_chan.push_back( (data & 0x001FC000) >> 14 ); // vmm channel
                    event_data.hit_strip.push_back( strip_map( event_data.hit_chan[hits] ) ); // detector physical channel index
                    event_data.hit_time.push_back( (data & 0x00003FC0) >> 6 ); // hit time
                    event_data.hit_adc.push_back( (data & 0x000003F) ); // 6-bit ADC


                    last_complete = 0;

                    if( i_print )
                        printf("%8X - HIT DATA - channel = %d  time = %d  adc = %d\n",
                                data, event_data.hit_chan[hits], event_data.hit_time[hits], event_data.hit_adc[hits]);

                    hits = hits + 1;
                    event_data.num_hits = hits;
                }
                break;

            case 6: // EVENT TRAILER
                {
                    unsigned int event_word_count = (data & 0x000003FF);
                    unsigned int builder_id = (data & 0x07000000) >> 24;
                    event_data.word_count = (data & 0x000003FF); // event_word_count;
                    complete = 1;           // set flag for complete event
                    event_data.complete = complete;
                    last_complete = 1;
                    if( i_print )
                        printf("%8X - EVENT TRAILER (id = %d) - event word count = %d\n", data, builder_id, event_word_count);
                }
                break;

            case  5: // UNDEFINED TYPE
                {
                    if( i_print )
                        printf("%8X - UNDEFINED TYPE = %d\n", data, data_type);
                }
                break;

            case 7: // UNDEFINED TYPE
                {
                    if( i_print )
                        printf("%8X - UNDEFINED TYPE = %d\n", data, data_type);
                }
                break;
        }

        return complete;
    }

    // maps channel number into GEM strip number
    unsigned int VmmDecoderSolid::strip_map(unsigned int channel)
    {
        if(gem_chamber_type == 0) {
            return channel;
        }
        else if(gem_chamber_type == 1) {
            unsigned int map[4] = {3, 1, 4, 2};
            unsigned int strip_number;
            int temp;

            temp = ((int)channel) % 4;
            strip_number = 4*(channel/4) + map[temp];

            return strip_number;
        }
        else {
            std::cout<<"VmmDecoderSolid:: unsupported GEM chamber Type [UVa GEM, MSU GEM]."<<std::endl;
            return channel;
        }
    }

    void VmmDecoderSolid::SetRawFile(const char* path)
    {
        raw_file = path;
    }

    const data_struct & VmmDecoderSolid::GetEvent(int i) const
    {
        if(decoded_data.size() <= 0)
        {
            std::cout<<"ERROR: Found 0 decoded VMM events."<<std::endl;
            std::cout<<"       returning a default event."<<std::endl;
            return event_data;
        }

        if(i >= (int)decoded_data.size()) {
            std::cout<<"WARNING: Already reached the last VMM event.\n"
                <<"         returning the last event."<<std::endl;
            return decoded_data.back();
        }

        return decoded_data[i];
    }
};
