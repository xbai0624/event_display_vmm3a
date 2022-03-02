{
    TFile *f_s = new TFile("../../Rootfiles/results_0606.root");
    TFile *f_n = new TFile("../../Rootfiles/results_0630.root");

    TH1F *h_s = (TH1F*)f_s ->Get("hStripAdcDistributionPlaneX0");
    TH1F *h_n = (TH1F*)f_n ->Get("hStripAdcDistributionPlaneX0");

    h_s -> GetXaxis() -> SetRangeUser(0, 1000);
    h_n -> GetXaxis() -> SetRangeUser(0, 1000);
    h_s -> GetYaxis() -> SetTitle("Normalized Counts");
    h_n -> GetYaxis() -> SetTitle("Normalized Counts");
    h_s -> GetYaxis() -> SetTitleOffset(1.5);
    h_n -> GetYaxis() -> SetTitleOffset(1.5);

    h_s -> SetTitle("strip ADC distribution, 64 channels combined");
    h_n -> SetTitle("strip ADC distribution, 64 channels combined");



    h_s -> Scale(1./h_s->Integral());
    h_n -> Scale(0.2/h_n->Integral());

    TCanvas *c1 = new TCanvas("c1", "c", 1000, 700);
    gPad -> SetFrameLineWidth(2);
    h_s -> SetLineColor(1);
    h_s -> SetLineWidth(2);
    h_n -> SetLineColor(2);
    h_n -> SetLineWidth(2);

    h_n -> Draw("hist");
    h_s -> Draw("same");

    TLegend *leg = new TLegend(0.35, 0.6, 0.75, 0.8);
    leg -> AddEntry(h_s, "cosimic signal strip ADC", "lp");
    leg -> AddEntry(h_n, "strip pedestal noise ADC", "lp");
    //leg -> SetBorderLineWidth(0);
    leg -> Draw();

    TText *t = new TText(250, 0.01, "VMM gain = 6 mV/fC, GEM HV = 3800 V");
    t -> Draw();
}
