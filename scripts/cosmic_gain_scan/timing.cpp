{
    TFile *f = new TFile("../../Rootfiles/results_0606.root");

    TH1F *h7 = (TH1F*) f->Get("hStripTimingDifference");

    h7->GetXaxis() -> SetRangeUser(-50, 50);
    h7 -> Fit("gaus");

    TCanvas *c = new TCanvas("c", "c", 1000, 700);
    gPad -> SetFrameLineWidth(2);
    h7->SetLineWidth(2);
    gStyle -> SetOptFit(111);
    
    h7 -> Draw();
}
