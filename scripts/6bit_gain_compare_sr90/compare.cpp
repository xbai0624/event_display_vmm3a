
void scale(TH1F* h)
{
    double s = h-> Integral();
    h -> Scale(1./s);
}

void compare()
{
    TFile *f0 = new TFile("../../Rootfiles/source_gain_scan_gain3.bin.root");
    TFile *f1 = new TFile("../../Rootfiles/source_gain_scan_gain6.bin.root");
    TFile *f2 = new TFile("../../Rootfiles/source_gain_scan_gain9.bin.root");
    TFile *f3 = new TFile("../../Rootfiles/source_gain_scan_gain16.bin.root");

    const char* txt[4] = {
        "gain = 3mV/fC",
        "gain = 6mV/fC",
        "gain = 9mV/fC",
        "gain = 16mV/fC"
    };

    TH1F *cluster_adc0 = (TH1F*)f0 -> Get("h_6bit_cluster_adc");
    scale(cluster_adc0);
    TH1F *cluster_adc1 = (TH1F*)f1 -> Get("h_6bit_cluster_adc");
    scale(cluster_adc1);
    TH1F *cluster_adc2 = (TH1F*)f2 -> Get("h_6bit_cluster_adc");
    scale(cluster_adc2);
    TH1F *cluster_adc3 = (TH1F*)f3 -> Get("h_6bit_cluster_adc");
    scale(cluster_adc3);
 

    TH1F *cluster_pos0 = (TH1F*)f0 -> Get("h_6bit_cluster_pos");
    scale(cluster_pos0);
    TH1F *cluster_pos1 = (TH1F*)f1 -> Get("h_6bit_cluster_pos");
    scale(cluster_pos1);
    TH1F *cluster_pos2 = (TH1F*)f2 -> Get("h_6bit_cluster_pos");
    scale(cluster_pos2);
    TH1F *cluster_pos3 = (TH1F*)f3 -> Get("h_6bit_cluster_pos");
    scale(cluster_pos3);

    TH1F *strip_adc0 = (TH1F*)f0 -> Get("h_6bit_strip_adc");
    scale(strip_adc0);
    TH1F *strip_adc1 = (TH1F*)f1 -> Get("h_6bit_strip_adc");
    scale(strip_adc1);
    TH1F *strip_adc2 = (TH1F*)f2 -> Get("h_6bit_strip_adc");
    scale(strip_adc2);
    TH1F *strip_adc3 = (TH1F*)f3 -> Get("h_6bit_strip_adc");
    scale(strip_adc3);

    TLegend *leg0 = new TLegend(0.5, 0.5, 0.8, 0.8);
    leg0 -> AddEntry(cluster_adc0, "3 mV/fC", "lp");
    leg0 -> AddEntry(cluster_adc1, "6 mV/fC", "lp");
    leg0 -> AddEntry(cluster_adc2, "9 mV/fC", "lp");
    leg0 -> AddEntry(cluster_adc3, "16 mV/fC", "lp");

    TCanvas* c0 = new TCanvas("c0", "c0", 1000, 800);
    gPad -> SetFrameLineWidth(2);
    cluster_adc0 -> SetLineColor(1);
    cluster_adc0 -> Draw("same");
    cluster_adc1 -> SetLineColor(2);
    cluster_adc1 -> Draw("same");
    cluster_adc2 -> SetLineColor(3);
    cluster_adc2 -> Draw("same");
    cluster_adc3 -> SetLineColor(4);
    cluster_adc3 -> Draw("same");
    leg0 -> Draw();

    TCanvas* c1 = new TCanvas("c1", "c1", 1000, 800);
    gPad -> SetFrameLineWidth(2);
    cluster_pos1 -> SetLineColor(2);
    cluster_pos1 -> Draw("same");
    cluster_pos2 -> SetLineColor(3);
    cluster_pos2 -> Draw("same");
    cluster_pos3 -> SetLineColor(4);
    cluster_pos3 -> Draw("same");
    cluster_pos0 -> SetLineColor(1);
    cluster_pos0 -> Draw("same");
    leg0 -> Draw();

    TCanvas* c2 = new TCanvas("c2", "c2", 1000, 800);
    gPad -> SetFrameLineWidth(2);
    strip_adc0 -> SetLineColor(1);
    strip_adc0 -> Draw("same");
    strip_adc1 -> SetLineColor(2);
    strip_adc1 -> Draw("same");
    strip_adc2 -> SetLineColor(3);
    strip_adc2 -> Draw("same");
    strip_adc3 -> SetLineColor(4);
    strip_adc3 -> Draw("same");
    leg0 -> Draw();

    c1 -> Print("Sr_90.pdf(");
    c0 -> Print("Sr_90.pdf");
    c2 -> Print("Sr_90.pdf)");
}
