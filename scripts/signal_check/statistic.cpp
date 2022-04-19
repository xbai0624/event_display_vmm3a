#include "histo_format.hpp"

void statistic()
{
    //gStyle -> SetOptStat(0);

    Format<> format;

    TCanvas *c = new TCanvas("c", "c", 1000, 1000);
    c -> Divide(4, 4);
    int start_channel = 0;

    //TFile *f = new TFile("../../Rootfiles/results_0781.root");
    TFile *f = new TFile("../../Rootfiles/results_0841.root");

    for(int i=start_channel; i<start_channel+16; i++)
    {
        TH1F *h = (TH1F*)f->Get(Form("hADCDistributionVMM0_Ch%d", i));
        Format<>::__format_histo(h);
        h -> GetXaxis() -> SetRangeUser(100, 600);

        c -> cd(i-start_channel+1);
        gPad->SetLeftMargin(0.12); // gPad exists after creating TCanvas
        gPad->SetBottomMargin(0.12); // gPad exists after creating TCanvas
        gPad->SetRightMargin(0.01); // gPad exists after creating TCanvas
        gPad->SetTopMargin(0.01); // gPad exists after creating TCanvas
        gPad->SetFrameLineWidth(2);
        gPad -> SetLogy();

        h -> Draw();
    }

    //c -> Print("good_stats.png");
}
