{
    // 559: fe55

    TFile *f = new TFile("results_0559.root");
    TH1F *h1 = (TH1F*)f->Get("h_occupancy");
    TH1F *h2 = (TH1F*)f->Get("hClusterAdcDistributionPlaneX");
    TH1F *h3 = (TH1F*)f->Get("hClusterPosDistributionPlaneX");

    TCanvas *c = new TCanvas("c", "c", 1700, 600);
    c -> Divide(3, 1);

    gStyle -> SetOptFit(111);

    c -> cd(1);
    gPad -> SetFrameLineWidth(2);
    gPad -> SetLogy();
    h1 -> SetLineWidth(2);
    h1 -> GetXaxis()->SetRangeUser(0, 8);
    h1 -> Draw();

    c -> cd(2);
    gPad -> SetFrameLineWidth(2);
    h2 -> SetLineWidth(2);
    h2 -> GetXaxis()->SetRangeUser(0, 1600);
    h2 -> Fit("gaus", "", "", 700, 1020);
    h2 -> Draw();

    c -> cd(3);
    gPad -> SetFrameLineWidth(2);
    h3 -> SetLineWidth(2);
    h3 -> GetXaxis()->SetRangeUser(0, 26);
    h3 -> Draw();

}
