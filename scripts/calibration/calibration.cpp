#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TApplication.h>
#include <TCanvas.h>

#include <map>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

const int NCH = 64;

////////////////////////////////////////////////////////////////////////////////
// load run list
map<int, string> get_runs(const char* path = "run_list.conf")
{
    map<int, string> res;

    fstream f(path, fstream::in);
    string file;
    int dac;

    while(f>>file>>dac){
        if(dac >= 0 )
            res[dac] = file;
    }

    // show run list
    cout<<"--------------------calibraton run list-------------------"<<endl;
    for(map<int, string>::const_iterator it = res.begin(); it != res.end(); ++it)
    {
        cout<<"dac: "<<it->first<<", file: "<<it->second<<endl;
    }
    cout<<"--------------------calibraton run list-------------------"<<endl;
 
    return res;
}


////////////////////////////////////////////////////////////////////////////////
// get adc distribution for each channel

map<int, TH1F*> get_channels_from_file(string file)
{
    map<int, TH1F*> res;

    TFile *_f = new TFile(file.c_str());

    for(int i=0; i<NCH; i++)
    {
        TH1F* h = (TH1F*)_f->Get(Form("hADCDistributioinVMM0_Ch%d", i));
        res[i] = h;
    }

    //_f -> Close();

    return res;
}


////////////////////////////////////////////////////////////////////////////////
// calibration

void calibration()
{
    // get run list
    map<int, string> run_list = get_runs();

    // get channels for reach run
    // <dac, <channel, TH1F*>>
    map<int, map<int, TH1F*>> dac_vmm_ch;
    for(auto &i: run_list) {
        map<int, TH1F*> tmp = get_channels_from_file(i.second);
        dac_vmm_ch[i.first] = tmp;
    }

    // get pedestal 2d histos
    // <channel, TH2F*> with TH2F* (X:dac, Y:ADC)
    map<int, TH2F*> pedestal_histos;
    for(auto &dac: dac_vmm_ch) 
    {
        int threshold = dac.first;
        for(auto &ch: dac.second)
        {
            int channel = ch.first;
            if(pedestal_histos.find(channel) == pedestal_histos.end()) {
                pedestal_histos[channel] = new TH2F(Form("hChannel%d", channel),
                        Form("channel %d pedestal vs threshold", channel),
                        500, 0, 500, 1000, 0, 1000);
            }

            TH1F *tmp = ch.second;
            int n_bins = tmp -> GetNbinsX();
            for(int i=0; i<n_bins; i++) {
                float adc = tmp -> GetBinCenter(i+1);
                pedestal_histos[channel] -> SetBinContent(threshold, adc, tmp -> GetBinContent(i));
            }
        }
    }

    // save results
    TFile *f = new TFile("results.root", "recreate");
    for(auto &i: pedestal_histos)
        i.second -> Write();
    f -> Close();
}

////////////////////////////////////////////////////////////////////////////////
// main

int main(int argc, char* argv[])
{
    TApplication app("app", &argc, argv);

    calibration();

    cout<<"calibration done."<<endl;

    app.Run();

    return 0;
}
