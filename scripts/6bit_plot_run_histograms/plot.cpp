{
    TFile *f = new TFile("../../Rootfiles/cosmic_3.bin.root");

    TH1F* h1 = (TH1F*)f->Get("h_6bit_cluster_adc");
    TH1F* h2 = (TH1F*)f->Get("h_6bit_cluster_pos");
    TH1F* h3 = (TH1F*)f->Get("h_6bit_cluster_size");
    TH1F* h4 = (TH1F*)f->Get("h_6bit_strip_adc");
    TH1F* h5 = (TH1F*)f->Get("h_6bit_strip_timing_reso");

    TCanvas *c1 = new TCanvas("c1", "c0", 1000, 800);
    gPad -> SetLeftMargin(0.12);
    gPad -> SetBottomMargin(0.12);
    h1 -> Draw();
    TCanvas *c2 = new TCanvas("c2", "c0", 1000, 800);
    gPad -> SetLeftMargin(0.12);
    gPad -> SetBottomMargin(0.12);
    h2 -> Draw();
    TCanvas *c3 = new TCanvas("c3", "c0", 1000, 800);
    gPad -> SetLeftMargin(0.12);
    gPad -> SetBottomMargin(0.12);
    h3 -> Draw();
    TCanvas *c4 = new TCanvas("c4", "c0", 1000, 800);
    gPad -> SetLeftMargin(0.12);
    gPad -> SetBottomMargin(0.12);
    h4 -> Draw();
    TCanvas *c5 = new TCanvas("c5", "c0", 1000, 800);
    gPad -> SetLeftMargin(0.12);
    gPad -> SetBottomMargin(0.12);
    h5 -> Draw();

    c1 -> Print("cosmic.pdf(");
    c2 -> Print("cosmic.pdf");
    c3 -> Print("cosmic.pdf");
    c4 -> Print("cosmic.pdf");
    c5 -> Print("cosmic.pdf)");

}
