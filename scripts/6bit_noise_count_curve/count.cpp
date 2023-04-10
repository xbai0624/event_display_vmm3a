{
    float x[6] = {
        150, 170, 180, 200, 210, 230
    };
    float y[6] = {
        0, 1243, 5.147e7, 5552461, 1757, 0
    };

    TCanvas *c = new TCanvas("c", "c", 1000, 600);
    gPad -> SetFrameLineWidth(2);
    TGraph *g = new TGraph(6, x, y);
    g -> SetTitle("overall noise signal counts vs threshold");
    g -> Draw("apl*");
    g -> SetMarkerStyle(20);
    g -> SetMarkerColor(1);
    g -> SetMarkerSize(1);
    g->GetXaxis()->SetTitle("12-bit DAC threshold (ADC)");
    g->GetYaxis()->SetTitle("Counts");
}
