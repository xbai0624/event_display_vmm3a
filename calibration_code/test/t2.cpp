{
    TFile *f = new TFile("test.root");

    const int N = 100;
    int nhits;
    float adc[N];

    TTree *T = (TTree*)f->Get("T");
    T -> SetBranchAddress("nhits", &nhits);
    T -> SetBranchAddress("adc", adc);

    cout<<T->GetEntries()<<endl;

    TH1F *h = new TH1F("h", "h", 10000, -500, 500);

    for(int entry=0; entry < T->GetEntries(); entry++)
    {
        T->GetEntry(entry);

        for(int i=0; i<nhits; i++) {
            h -> Fill(adc[i]);
        }
    }
    
   h -> Draw(); 
}
