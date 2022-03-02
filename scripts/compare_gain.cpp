void compare_gain(const char* path1 = "../Rootfiles/results_0366.root", 
        const char* path2 = "../Rootfiles/results_0367.root")
{
    TFile *f1 = new TFile(path1);
    TFile *f2 = new TFile(path2);

    TH1F *h1 = (TH1F*) f1 -> Get("hClusterAdcDistributionPlaneX");
    TH1F *h2 = (TH1F*) f2 -> Get("hClusterAdcDistributionPlaneX");

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    h1 -> SetLineColor(2);
    h1 -> Scale(1./h1->Integral());
    h1 -> Fit("landau", "", "", 300, 700);
    h2 -> Scale(1./h2->Integral());
    h2 -> Fit("landau", "", "", 300, 700);

    h1 -> Draw();
    h2 -> Draw("same");
}
