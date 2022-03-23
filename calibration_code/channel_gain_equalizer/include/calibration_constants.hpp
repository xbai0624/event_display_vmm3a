#ifndef CALIBRATION_CONSTANTS_HPP
#define CALIBRATION_CONSTANTS_HPP

namespace vmm_calibration {

    // convert dac pulser counts to charge
    // VMM channel test capacitor: 300 fF
    // return charge in unit [fC]
    template<typename T = float> T pulser_dac_to_fC(int dac)
    {
        float slope = 0.7611; // mV/cts
        float intercept = 28.39; // mV

        float mV = slope * dac + intercept;

        float res = mV / 1000. * 300;

        return res;
    }
};

#endif
