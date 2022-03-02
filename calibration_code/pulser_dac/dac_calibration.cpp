#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TText.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>

#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void dac_calibration(const char* path = "~/calib_run_0645.root")
{
    TFile *f = new TFile(path);
    TTree *T = (TTree*)f->Get("calib");

    int runNumber;
    double gain;
    int tacSlope;
    int peakTime;
    int dacCounts;
    double tpSkew;
    int pulserCounts;
    int subhysteresis;
    int neighbor_trigger;
    int nExpected;
    unsigned int channel;
    unsigned int boardID;
    unsigned int chip;
    unsigned int samples;
    int channelTrim;

    T -> SetBranchAddress("runNumber", &runNumber);
    T -> SetBranchAddress("gain", &gain);
    T -> SetBranchAddress("tacSlope", &tacSlope);
    T -> SetBranchAddress("peakTime", &peakTime);
    T -> SetBranchAddress("dacCounts", &dacCounts);
    T -> SetBranchAddress("tpSkew", &tpSkew);
    T -> SetBranchAddress("pulserCounts", &pulserCounts);
    T -> SetBranchAddress("subhysteresis", &subhysteresis);
    T -> SetBranchAddress("neighbor_trigger", &neighbor_trigger);
    T -> SetBranchAddress("nExpected", &nExpected);
    T -> SetBranchAddress("channel", &channel);
    T -> SetBranchAddress("boardId", &boardID);
    T -> SetBranchAddress("chip", &chip);
    T -> SetBranchAddress("samples", &samples);
    T -> SetBranchAddress("channelTrim", &channelTrim);

    int T_N = T -> GetEntries();

    std::map<int, TH1F*> mhist;

    for(int i=0; i<T_N; i++)
    {
        T -> GetEntry(i);

        int pulser = pulserCounts;
        int adc = samples;

        if(mhist.find(pulser) == mhist.end())
        {
            mhist[pulser] = new TH1F(Form("h_pulser_dac_%d", pulser), Form("h_pulser_dac_%d", pulser),
                    2500, 0, 2500);
        }

        mhist[pulser] -> Fill(adc);
    }

    TFile *_f = new TFile("res.root", "recreate");
    gStyle -> SetOptFit(111);

    TCanvas *c2 = new TCanvas("c2", "c2", 1200, 800);
    c2 -> Divide(4, 3);
    int c_index = 1;

    // fit histos
    for(map<int, TH1F*>::iterator it = mhist.begin(); it != mhist.end(); ++it)
    {
        float mean = (it -> second) -> GetMean();
        (it -> second) -> Fit("gaus", "Q", "", mean-20, mean+20);
        (it -> second) -> GetXaxis() -> SetRangeUser(mean-20, mean+20);
        (it -> second) -> SetLineWidth(2);
        (it -> second) -> GetXaxis() -> SetTitle("Pulser DAC [cts]");
        (it -> second) -> GetYaxis() -> SetTitle("xADC output [cts]");
        (it -> second) -> Write();

        c2 -> cd(c_index);
        (it -> second) -> Draw();
        c_index++;
    }
    c2 -> Write("c2");

    size_t num = mhist.size();
    float pulser_dac[num];
    float pulser_err[num];
    float output_adc[num];
    float adc_err[num];

    float mV[num];
    float mV_err[num];

    // fit
    int index = 0;
    for(map<int, TH1F*>::iterator it = mhist.begin(); it != mhist.end(); ++it)
    {
        float amplitude = ((it -> second) -> GetFunction("gaus")) -> GetParameter(0);
        float mu = ((it -> second) -> GetFunction("gaus")) -> GetParameter(1);
        float sigma = ((it -> second) -> GetFunction("gaus")) -> GetParameter(2);

        pulser_dac[index] = it -> first;
        pulser_err[index] = 0;
        output_adc[index] = mu;
        adc_err[index] = sigma;

        mV[index] = mu / 4.096;
        mV_err[index] = sigma / 4.096;

        index++;
    }

    TCanvas *c0 = new TCanvas("c0", "c0", 900, 600);
    TGraphErrors *gr = new TGraphErrors(num, pulser_dac, output_adc, pulser_err, adc_err);
    gr -> SetTitle("xADC [counts] vs pulser dac [counts]");
    gr -> SetMarkerStyle(20);
    gr -> Draw("apl");
    gr -> Write("g_adc");
    gr -> Fit("pol1");
    gr -> GetXaxis() -> SetTitle("pulser DAC [counts]");
    gr -> GetYaxis() -> SetTitle("output xADC [counts]");

    double p2 = (gr -> GetFunction("pol1")) -> GetParameter("p0");
    double p3 = (gr -> GetFunction("pol1")) -> GetParameter("p1");
    double p2_err = (gr -> GetFunction("pol1")) -> GetParError(0);
    double p3_err = (gr -> GetFunction("pol1")) -> GetParError(1);
    TLatex text;
    text.SetTextFont(42);
    text.SetTextSize(0.7 * text.GetTextSize());
    stringstream ss;
    ss.str("");
    ss << "Slope      : "<<std::setprecision(4)<<p2<<" #pm "<<p2_err<<" cts/cts";
    text.DrawLatexNDC(0.12, 0.85, ss.str().c_str());
    ss.str("");
    ss << "Intercept : "<<std::setprecision(4)<<p3<<" #pm "<<p3_err<<" cts";
    text.DrawLatexNDC(0.12, 0.80, ss.str().c_str());
    c0 -> SetGridx();
    c0 -> SetGridy();
    c0 -> Write("c0");



    TCanvas *c1 = new TCanvas("c1", "c1", 900, 600);
    TGraphErrors *gr1 = new TGraphErrors(num, pulser_dac, mV, pulser_err, mV_err);
    gr1 -> SetTitle("xADC [mV] vs pulser dac [counts]");
    gr1 -> SetMarkerStyle(20);
    gr1 -> Draw("apl");
    gr1 -> Write("g_mV");
    gr1 -> Fit("pol1");
    gr1 -> GetXaxis() -> SetTitle("pulser DAC [counts]");
    gr1 -> GetYaxis() -> SetTitle("output Voltage [mV]");
    double p0 = (gr1 -> GetFunction("pol1")) -> GetParameter("p0");
    double p0_err = (gr1 -> GetFunction("pol1")) -> GetParError(0);
    double p1 = (gr1 -> GetFunction("pol1")) -> GetParameter("p1");
    double p1_err = (gr1 -> GetFunction("pol1")) -> GetParError(1);
    ss.str("");
    ss << "Slope      : "<<std::setprecision(4)<<p0<<" #pm "<<p0_err<<" mV/cts";
    text.DrawLatexNDC(0.12, 0.85, ss.str().c_str());
    ss.str("");
    ss << "Intercept : "<<std::setprecision(4)<<p1<<" #pm "<<p1_err<<" mV";
    text.DrawLatexNDC(0.12, 0.80, ss.str().c_str());
    c1 -> SetGridx();
    c1 -> SetGridy();
    c1 -> Write("c1");

    _f -> Close();
}

int main(int argc, char* argv[])
{
    dac_calibration();

    return 0;
}
