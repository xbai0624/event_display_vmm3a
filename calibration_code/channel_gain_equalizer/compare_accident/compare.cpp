

void compare(){
    //TFile *fbefore = new TFile("before_accident/result_tgraph.root");
    //TFile *fbefore = new TFile("before_accident_off_by_50_for_drawiing/result_tgraph.root");
    //TFile *fafter = new TFile("after_accident/result_tgraph.root");
    TFile *fbefore = new TFile("after_accident_with_Ed_PS/result_tgraph.root");
    TFile *fafter = new TFile("after_accident_benchtop_PS/result_tgraph.root");



    TCanvas *c[4];
    for(int i=0; i<4; i++) {
        c[i] = new TCanvas(Form("c%d", i), Form("c%d", i), 1000, 1000);
        c[i] -> Divide(4, 4);
    }

    for(int i=0; i<64; i++) {
        int nc = i/16;
        int np = i%16 + 1;
        c[nc] -> cd(np);

        TGraphErrors* g1 = (TGraphErrors*)fbefore->Get(Form("g_ch_%d", i));
        g1 -> SetLineColor(2);
        g1 -> SetLineWidth(2);
        g1 -> SetMarkerColor(2);


        TGraphErrors* g2 = (TGraphErrors*)fafter->Get(Form("g_ch_%d", i));
        g2 -> SetLineColor(4);
        g2 -> SetLineWidth(2);
        g2 -> SetMarkerColor(4);
        g2 -> GetFunction("pol1")->SetLineColor(4);

        TMultiGraph *g = new TMultiGraph();
        g -> Add(g1);
        g -> Add(g2);
        g -> SetTitle(Form("channel_%d", i));

        g -> Draw("apl");
        gStyle -> SetTitleFontSize(0.1);

        g->GetXaxis() -> SetTitle("pulser input charge [fC]");
        g->GetXaxis()->SetTitleOffset(0.6);
        g->GetXaxis()->SetTitleSize(0.06);
        //g->GetXaxis()->GetTitle()->SetFont(72);
        g->GetYaxis() -> SetTitle("PDO [ADC]");
        g->GetYaxis()->SetTitleOffset(0.8);
        g->GetYaxis()->SetTitleSize(0.06);
 
        TLegend *leg = new TLegend(0.2, 0.7, 0.7, 0.85);
        leg -> AddEntry(g1, "Ed's PS", "lep");
        leg -> AddEntry(g2, "Benchtop PS", "lep");
        leg -> Draw();

        gPad -> Modified();
        gPad -> Update();
    }

    c[0] -> Print("compare.pdf(");
    c[1] -> Print("compare.pdf");
    c[2] -> Print("compare.pdf");
    c[3] -> Print("compare.pdf)");




}
