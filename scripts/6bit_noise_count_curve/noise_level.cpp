{
    TFile *f1 = new TFile("../../Rootfiles/threshold180_gain3.bin.root");
    TH1F *h1 = (TH1F*)f1->Get("h_6bit_strip_adc");
    h1 -> Scale(1./h1->Integral());

    TFile *f2 = new TFile("../../Rootfiles/threshold180_gain6.bin.root");
    TH1F *h2 = (TH1F*)f2->Get("h_6bit_strip_adc");
    h2 -> Scale(1./h2->Integral());


    TFile *f3 = new TFile("../../Rootfiles/threshold180_gain9.bin.root");
    TH1F *h3 = (TH1F*)f3->Get("h_6bit_strip_adc");
    h3 -> Scale(1./h3->Integral());


    TFile *f4 = new TFile("../../Rootfiles/threshold180_gain16.bin.root");
    TH1F *h4 = (TH1F*)f4->Get("h_6bit_strip_adc");
    h4 -> Scale(1./h4->Integral());

    TCanvas *c = new TCanvas("c", "c", 1000, 600);
    gPad -> SetFrameLineWidth(2);
    h1 -> SetLineColor(1);
    h1 -> Draw();
    h2 -> SetLineColor(2);
    h2 -> Draw("same");
    h3 -> SetLineColor(3);
    h3->Draw("same");
    h4 -> SetLineColor(4);
    h4->Draw("same");

    TLegend *leg = new TLegend(0.5, 0.5, 0.8, 0.8);
    leg -> AddEntry(h1, "gain 3 mV/fC", "lep");
    leg -> AddEntry(h2, "gain 6 mV/fC", "lep");
    leg -> AddEntry(h3, "gain 9 mV/fC", "lep");
    leg -> AddEntry(h4, "gain 16 mV/fC", "lep");
    leg -> Draw();



}
