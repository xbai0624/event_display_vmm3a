
void plot()
{
    TFile *f1 = new TFile("../../Rootfiles/cosmic_external_trigger_HV4000_VMMgain9_run2.bin.root");
    TH1F *h1 = (TH1F*)f1 -> Get("h_6bit_strip_adc");
    h1 -> Scale(1./h1->Integral());
    h1 -> SetLineColor(1);

    TFile *f2 = new TFile("../../Rootfiles/cosmic_external_trigger_HV4050_VMMgain9.bin.root");
    TH1F *h2 = (TH1F*)f2 -> Get("h_6bit_strip_adc");
    h2 -> Scale(1./h2->Integral());
    h2 -> SetLineColor(2);

    TFile *f3 = new TFile("../../Rootfiles/threshold180_gain9.bin.root");
    TH1F *h3 = (TH1F*)f3 -> Get("h_6bit_strip_adc");
    h3 -> Scale(1./h3->Integral());
    h3 -> SetLineColor(4);

    TFile *f4 = new TFile("../../Rootfiles/cosmic_external_trigger_HV4150_VMMgain16.bin.root");
    TH1F *h4 = (TH1F*)f4 -> Get("h_6bit_strip_adc");
    h4 -> Scale(1./h4->Integral());
    h4 -> SetLineColor(8);

    TFile *f5 = new TFile("../../Rootfiles/threshold180_gain16.bin.root");
    TH1F *h5 = (TH1F*)f5 -> Get("h_6bit_strip_adc");
    h5 -> Scale(1./h5->Integral());
    h5 -> SetLineColor(6);

    TLegend *leg = new TLegend(0.3, 0.5, 0.8, 0.8);
    leg -> AddEntry(h1, "6bit gain = 9mV/fC, GEM HV 4000 (cosmic)", "lp");
    leg -> AddEntry(h2, "6bit gain = 9mV/fC, GEM HV 4050 (cosmic)", "lp");
    leg -> AddEntry(h4, "6bit gain = 16mV/fC, GEM HV = 4150 (cosmic)", "lp");
    leg -> AddEntry(h3, "6bit gain = 9mV/fC, GEM HV = 0 (noise)", "lp");
    leg -> AddEntry(h5, "6bit gain = 16mV/fC, GEM HV = 0 (noise)", "lp");

    TCanvas *c = new TCanvas("c", "c", 1000, 800);
    h3 -> Draw("hist");
    h2 -> Draw("hist same");
    h1 -> Draw("hist same");
    h4 -> Draw("hist same");
    h5 -> Draw("hist same");

    leg -> Draw();
}
