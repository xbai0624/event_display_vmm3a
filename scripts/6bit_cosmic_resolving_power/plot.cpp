


void plot()
{
    TFile *f1 = new TFile("../../Rootfiles/cosmic_external_trigger_gain9.bin.root");
    TH1F *h1 = (TH1F*)f1->Get("h_6bit_cluster_adc");
    h1 -> Scale(1./h1->Integral());
    h1 -> SetLineColor(1);

    TFile *f11 = new TFile("../../Rootfiles/cosmic_external_trigger_gain6.bin.root");
    TH1F *h11 = (TH1F*)f11->Get("h_6bit_cluster_adc");
    h11 -> Scale(1./h11->Integral());
    h11 -> SetLineColor(2);

    TLegend *leg = new TLegend(0.5, 0.5, 0.8, 0.8);
    leg -> AddEntry(h1, "6bit gain = 9mV/fC cosmic", "lp");
    leg -> AddEntry(h11, "6bit gain = 6mV/fC cosmic", "lp");

    TCanvas *c = new TCanvas("c", "c", 1000, 800);
    h11 -> Draw("hist same");
    h1 -> Draw("hist same");

    leg -> Draw();
}
