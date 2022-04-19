#include "histo_format.hpp"

void events()
{
    gStyle -> SetOptStat(0);

    Format<> format;

    TCanvas *c = new TCanvas("c", "c", 1000, 1000);
    c -> Divide(4, 4);
    int start_event = 54+16;

    for(int i=start_event; i<start_event+16; i++)
    {
        //TFile *f = new TFile(Form("../../cache_plots/run_0781_event_%d.root", i));
        TFile *f = new TFile(Form("../../cache_plots/run_0841_event_%d.root", i));

        TH1F *h = (TH1F*)f->Get(Form("h_evt_%d_chip_0", i-1));
        Format<>::__format_histo(h);

        c -> cd(i-start_event+1);
        gPad->SetLeftMargin(0.12); // gPad exists after creating TCanvas
        gPad->SetBottomMargin(0.12); // gPad exists after creating TCanvas
        gPad->SetRightMargin(0.01); // gPad exists after creating TCanvas
        gPad->SetTopMargin(0.01); // gPad exists after creating TCanvas
        gPad->SetFrameLineWidth(2);

        h -> Draw();
    }

    c -> Print("bad_event.png");
}
