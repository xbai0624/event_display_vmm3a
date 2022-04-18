#ifndef ANALYZER_H
#define ANALYZER_H

#include "list_parser.hpp"
#include "calibration_constants.hpp"
#include <TH1F.h>
#include <TFile.h>
#include <TGraph.h>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TF1.h>
#include <map>
#include <vector>
#include <iomanip>

using std::vector;
using std::map;

template<typename T=int> class Analyzer
{
    public:
        Analyzer(){
            list_parser.setPath("runlist.txt");
        }
        ~Analyzer(){}

        unordered_map<int, TH1F*> get_vmm_channels(const char* path)
        {
            unordered_map<int, TH1F*> res;
            TFile *f = new TFile(path);
            for(int i=0; i<64; i++) {
                TH1F *h = (TH1F*)f->Get(Form("hADCDistributionVMM0_Ch%d", i));
                if(h != nullptr)
                    res[i] = h;
            }
            return res;
        }

        void run() {
            list_parser.load();

            // pulser, channel, histogram
            map<int, unordered_map<int, TH1F*>> cache;

            auto &runlist = list_parser.get_content();
            for(auto &i: runlist) {
                cache[i.first] = get_vmm_channels(i.second.c_str());
            }

            // channel, TGraph
            unordered_map<int, TGraphErrors*> fittings;
            for(int i=0; i<64; i++) {
                vector<float> pulse_level, adc_level, adc_error;
                for(map<int, unordered_map<int, TH1F*>>::iterator it = cache.begin();
                        it != cache.end(); ++it)
                {
                    pulse_level.push_back(it->first);
                    if(it->second.find(i) != it->second.end())
                    {
                        // fit the main peak
                        //int binmax = (it->second.at(i)) -> GetMaximumBin();
                        //double x = (it->second.at(i)) -> GetXaxis() -> GetBinCenter(binmax);
                        //(it->second.at(i)) -> Fit("gaus", "Q", "",  x-100, x+100);
                        //adc_level.push_back(it->second.at(i)->GetFunction("gaus") -> GetParameter("Mean"));
                        //adc_error.push_back(it->second.at(i)->GetFunction("gaus") -> GetParameter("Sigma"));

                        adc_level.push_back(it->second.at(i)->GetMean());
                        adc_error.push_back(it->second.at(i)->GetRMS());
                    }
                    else {
                        adc_level.push_back(0);
                        adc_error.push_back(0);
                    }
                }

                // get the graph
                int n = pulse_level.size();
                if(n <= 0) continue;

                float x[n], xerr[n], y[n], yerr[n];
                for(int p=0; p<n; p++) {
                    x[p] = pulse_level[p]; // counts
                    // convert to charge
                    x[p] = vmm_calibration::pulser_dac_to_fC<float>(x[p]);
                    xerr[p] = 0;
                    y[p] = adc_level[p];
                    yerr[p] = adc_error[p];
                }
                TGraphErrors *g = new TGraphErrors(n, x, y, xerr, yerr);
                fittings[i] = g;
            }

            TH1F *h_gain = new TH1F("h_gain", "channel gain", 64, 0, 64);
            TH1F *h_offset = new TH1F("h_offset", "channel offset", 64, 0, 64);
            TCanvas *c[64];
            // save results
            TFile *fff = new TFile("result_canvas.root", "recreate");
            for(auto &i: fittings) {
                c[i.first] = new TCanvas(Form("c%d", i.first), Form("c%d", i.first), 1000, 600);
                gPad -> SetFrameLineWidth(2);
                i.second -> Draw("apl");
                i.second -> SetMarkerStyle(20);
                i.second -> SetTitle(Form("channel_%d", i.first));
                i.second -> GetXaxis() -> SetTitle("pulser input charge [fC]");
                i.second -> GetYaxis() -> SetTitle("channel pdo output [ADC counts]");
                i.second -> Fit("pol1");
                TLatex text;
                text.SetTextFont(42);
                text.SetTextSize(0.7 * text.GetTextSize());
                std::stringstream ss;
                ss.str("");
                ss << "Slope     :  "<<std::setprecision(4)<<(i.second->GetFunction("pol1"))->GetParameter("p1") << " cts/fC";
                text.DrawLatexNDC(0.14, 0.85, ss.str().c_str());
                h_gain -> SetBinContent((int)i.first, (i.second->GetFunction("pol1"))->GetParameter("p1"));
                ss.str("");
                ss << "Intercept :  "<<std::setprecision(4)<<(i.second->GetFunction("pol1"))->GetParameter("p0") << " cts";
                text.DrawLatexNDC(0.14, 0.80, ss.str().c_str());
                h_offset -> SetBinContent((int)i.first, (i.second->GetFunction("pol1"))->GetParameter("p0"));
 
                c[i.first] -> Write(Form("ch%d", i.first));
                c[i.first] -> Clear();

                std::pair<float, float> gain_offset(0, 0);
                gain_offset.first = (i.second->GetFunction("pol1"))->GetParameter("p1");
                gain_offset.second = (i.second->GetFunction("pol1"))->GetParameter("p0");
                channel_gain_offset[(int)i.first] = gain_offset;
            }
            fff->Close();

            TFile *f1 = new TFile("result_tgraph.root", "recreate");
            for(auto &i: fittings) {
                i.second -> Write(Form("g_ch_%d", i.first));
            }
            f1->Close();

            TFile *f2 = new TFile("result_histos.root", "recreate");
            h_gain -> GetXaxis() -> SetTitle("VMM channel Index");
            h_gain -> GetYaxis() -> SetTitle("VMM channel Gain [ADC Counts per fC]");
            h_gain -> Write();
            h_offset -> GetXaxis() -> SetTitle("VMM channel Index");
            h_offset -> GetYaxis() -> SetTitle("VMM channel Offset [ADC Counts]");
            h_offset -> Write();
            f2 -> Close();

            // save gain and offset
            std::fstream txt_gain_offset("channel_gain_offset.txt", std::fstream::out);
            for(auto &i: channel_gain_offset)
                txt_gain_offset<<std::setfill(' ')<<std::setw(16)<<i.first
                    <<std::setfill(' ')<<std::setw(16)<<i.second.first
                    <<std::setfill(' ')<<std::setw(16)<<i.second.second<<std::endl;
            txt_gain_offset.close();
        }

    private:
        ListParser<> list_parser;

        // gain and offset calibration constants
        // <channel, <gain, offset>>
        map<int, std::pair<float, float>> channel_gain_offset;
};

#endif
