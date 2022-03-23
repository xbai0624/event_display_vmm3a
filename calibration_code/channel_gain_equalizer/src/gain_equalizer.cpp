////////////////////////////////////////////////////////////////////////////////
// This code checks the gain and ambient offset electric level for            //
// each channel                                                               //
// This code reads a text file that contains a run list                       //
// This code takes the output of event_display_vmm3a as input                 //
// The runs should be dedicated to gain calibration purpose                   //
// These runs should be taken under a same threshold level, but each run has  //
// a specific DAC pulser level, this code checks each channel's PDO output    //
// under different pulser DAC levels, and then output the gain and offset for //
// each channel                                                               //
////////////////////////////////////////////////////////////////////////////////

#include "analyzer.hpp"

int main(int argc, char* argv[])
{
    Analyzer<> *ana = new Analyzer<>();
    ana -> run();

    return 0;
}
