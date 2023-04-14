void plot_root_result(const char* name)
{
    const int N = 8;

    TCanvas *c[N];
    for(int i=0; i<N; i++)
        c[i] = new TCanvas(Form("c%d", i), Form("c%d", i), 1000, 800);

    TFile *f = new TFile(name);
    TIter keyList(f->GetListOfKeys());
    TKey *key;
    int i = 0;
    while( (key=(TKey*)keyList()) )
    {
        TClass *c1 = gROOT -> GetClass(key->GetClassName());

        if(c1 -> InheritsFrom("TH2")) {
            TH1F *h1 = (TH1F*)key->ReadObj();
            c[i] -> cd();
            h1->Draw("colz");
            i++;
        }
        else if(c1 -> InheritsFrom("TH1")) {
            TH2F *h2 = (TH2F*)key->ReadObj();
            c[i] -> cd();
            h2->Draw("colz");
            i++;
        }
    }

    c[0] -> Print("../all_plots.pdf(");
    for(i=1; i<N-1; i++){
        c[i] -> Print("../all_plots.pdf");
    }
    c[N-1] -> Print("../all_plots.pdf)");
}
