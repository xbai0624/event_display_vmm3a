{
    TFile *f1 = new TFile("../../Rootfiles/results_0588.root");
    TFile *f2 = new TFile("../../Rootfiles/results_0589.root");
    TFile *f3 = new TFile("../../Rootfiles/results_0590.root");
    TFile *f4 = new TFile("../../Rootfiles/results_0591.root");

    TH1F *h1 = (TH1F*)f1 -> Get("hClusterAdcDistributionPlaneX0");
    TH1F *h2 = (TH1F*)f2 -> Get("hClusterAdcDistributionPlaneX0");
    TH1F *h3 = (TH1F*)f3 -> Get("hClusterAdcDistributionPlaneX0");
    TH1F *h4 = (TH1F*)f4 -> Get("hClusterAdcDistributionPlaneX0");


    TCanvas *c = new TCanvas("c", "c", 1700, 600);
    c -> Divide(2, 1);
    c -> cd(1);
    gPad -> SetFrameLineWidth(2);

    h1 -> GetXaxis() -> SetRangeUser(0, 1600);
    h1 -> SetLineWidth(2);
    h1 -> SetLineColor(2);
    h1 -> SetTitle("Fe55 spectrum");
    h1 -> Draw();

    h2 -> GetXaxis() -> SetRangeUser(0, 1600);
    h2 -> SetLineWidth(2);
    h2 -> SetLineColor(3);
    h2 -> Draw("same");

    h3 -> GetXaxis() -> SetRangeUser(0, 1600);
    h3 -> SetLineWidth(2);
    h3 -> SetLineColor(4);
    h3 -> Draw("same");

    h4 -> GetXaxis() -> SetRangeUser(0, 1600);
    h4 -> SetLineWidth(2);
    h4 -> SetLineColor(1);
    h4 -> Draw("same");

    TLegend *leg = new TLegend(0.12, 0.6, 0.4, 0.8);
    leg -> AddEntry(h1, "25 ns shapping time", "lp");
    leg -> AddEntry(h2, "50 ns shapping time", "lp");
    leg -> AddEntry(h3, "100 ns shapping time", "lp");
    leg -> AddEntry(h4, "200 ns shapping time", "lp");
    leg -> SetBorderSize(0);
    leg -> Draw();

    float x[4] = {25, 50, 100, 200};
    float xerr[] = {0, 0, 0, 0};
    float y[4] = {747, 855.6, 889.5, 896.2};
    float yerr[] = {103, 110.4, 104.5, 105.6};

    c -> cd(2);
    TGraphErrors *g = new TGraphErrors(4, x, y, xerr, yerr);
    gPad -> SetGridx();
    gPad -> SetGridy();
    g -> SetMarkerStyle(20);
    //g -> SetMarkerColor(2);
    g -> SetMarkerSize(1.5);
    g -> SetLineWidth(2);
    g -> SetTitle("Signal average amplitude vs signal shapping time");
    g -> GetXaxis() -> SetTitle("Shaping time [ns]");
    g -> GetYaxis() -> SetTitle("Fe55 spectrum peak [ADC]");
    gPad -> SetFrameLineWidth(2);
    g -> Draw("ap");

    c -> Print("gain_vs_shaping_time.png");
}
