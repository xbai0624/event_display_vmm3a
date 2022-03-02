{
    TFile *f = new TFile("../../Rootfiles/results_0606.root");

    TH1F *h1 = (TH1F*) f->Get("h_occupancy_vmm0");
    TH1F *h2 = (TH1F*) f->Get("hClusterAdcDistributionPlaneX0");
    TH1F *h3 = (TH1F*) f->Get("hClusterPosDistributionPlaneX0");
    TH1F *h4 = (TH1F*) f->Get("hStripAdcDistributionPlaneX0");

    TH2F *h5 = (TH2F*) f->Get("h2DADCVMM0");
    TH2F *h6 = (TH2F*) f->Get("h2DTimingVMM0");

    TH1F *h7 = (TH1F*) f->Get("hStripTimingDifference");

    TCanvas *c = new TCanvas("c", "c", 1400, 900);
    c -> Divide(3, 3);
    gStyle -> SetOptFit(111);

    c -> cd(1);
    //gPad -> SetLogy(1);
    gPad -> SetFrameLineWidth(2);
    h1 -> GetXaxis() -> SetRangeUser(0, 8);
    h1 -> SetLineWidth(2);
    h1 -> SetTitle("cluster size");
    h1 -> Draw();

    c -> cd(2);
    gPad -> SetFrameLineWidth(2);
    //gPad -> SetLogy(1);
    h2 -> GetXaxis() -> SetRangeUser(0, 1600);
    //h2 -> GetXaxis() -> SetRangeUser(0, 1600); // 593 = gain 6.0 mV/fC
    h2 -> SetLineWidth(2);
    //h2 -> Fit("gaus", "", "", 600, 900); // 588
    //h2 -> Fit("gaus", "", "", 700, 1000); // 589
    //h2 -> Fit("gaus", "", "", 750, 1050); // 590
    //h2 -> Fit("gaus", "", "", 750, 1050); // 591
    h2 -> Fit("landau", "", "", 150, 800); // 591, 2nd peak
    //h2 -> Fit("gaus", "", "", 1300, 1600); // 593
    h2 -> Draw();

    c->cd(3);
    gPad -> SetFrameLineWidth(2);
    h3 -> GetXaxis() -> SetRangeUser(0, 27);
    h3 -> SetLineWidth(2);
    h3 -> Draw();

    c->cd(4);
    //gPad -> SetLogy(1);
    h4 -> GetXaxis() -> SetRangeUser(0, 1200);
    h4 -> Draw();

    c->cd(5);
    h5 -> GetYaxis() -> SetRangeUser(0, 1000);
    h5 -> Draw("colz");

    c->cd(6);
    h6 -> GetYaxis() -> SetRangeUser(0, 100);
    h6 -> Draw("colz");

    c->cd(7);
    gPad -> SetFrameLineWidth(2);
    h7 -> GetXaxis() -> SetRangeUser(-50, 50);
    h7 -> SetLineWidth(2);
    h7 -> Fit("gaus");
    h7 -> Draw();

    c -> Print("606.png");
}
