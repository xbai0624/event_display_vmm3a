{
    TFile *f = new TFile("test.root", "recreate");
    TTree *T = new TTree("T", "test");

    const int M = 100;
    int nhits;
    float adc[M];

    T -> Branch("nhits", &nhits, "nhits/I");
    T -> Branch("adc", adc, "adc[nhits]/F");

    TRandom *gen = new TRandom(0);

    for(int i=0; i<1000; i++)
    {
        nhits = gen -> Uniform(1, 10);

        for(int j=0; j<nhits; j++){
            float t = gen->Gaus(5., 2.);
            adc[j] = t;
        }

        T -> Fill();
    }

    f -> Write();
    f -> Close();
}
