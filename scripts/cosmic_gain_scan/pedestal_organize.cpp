{
    TFile *f1 = new TFile("../../Rootfiles/results_0630.root");
    TFile *f2 = new TFile("../../Rootfiles/results_0631.root");

    TH2F *hp = new TH2F("hp", "strip pedestal distribution", 64, 0, 64, 150, 0, 150);
    hp -> GetXaxis() -> SetTitle("VMM Ch No.");
    hp -> GetYaxis() -> SetTitle("ADC");

    // first batch strips
    for(int i=0; i<63; i++){
        if(i%3 == 1)
            continue;
        TH1F *h = (TH1F*) f1 -> Get(Form("hADCDistributionVMM0_Ch%d", i));

        int nbins = h -> GetNbinsX();

        for(int j=0; j<nbins; j++)
        {
            int adc = h -> GetBinCenter(j);
            int counts = h -> GetBinContent(j);

            hp -> SetBinContent(i, adc, counts);
        }
    }

    // second batch strips
    for(int i=0; i<63; i++){
        if(i%3 != 1)
            continue;
        TH1F *h = (TH1F*) f2 -> Get(Form("hADCDistributionVMM0_Ch%d", i));

        int nbins = h -> GetNbinsX();

        for(int j=0; j<nbins; j++)
        {
            int adc = h -> GetBinCenter(j);
            int counts = h -> GetBinContent(j);

            hp -> SetBinContent(i, adc, counts);
        }
    }

    TCanvas *c = new TCanvas("c", "c", 1000, 700);
    gPad -> SetFrameLineWidth(2);
    hp -> Draw("colz");

}
