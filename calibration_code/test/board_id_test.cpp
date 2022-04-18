void _board_id_test(string path ="../../../data/run_0509.root")
{
    TFile *f = new TFile(path.c_str());

    if(f->IsZombie()) {
        cout<<path<<" NOT EXIST."<<endl;
        return;
    }

    TTree *T = (TTree*)f->Get("vmm");
    int entries = T -> GetEntries();
    if(entries <= 0)
    {
        cout<<"no event."<<endl;
        return;
    }

    TH1F *h = new TH1F("htest", "h", 100, 0, 100);
    T->Draw("boardId>>htest");
    float mean = h -> GetMean();
    cout<<mean<<endl;

    if(mean == 2.)
        cout<<"not found."<<endl;
    else  {
        cout<<"found: "<<path<<endl;
        getchar();
        cout<<"enter to continue..."<<endl;
    }
    f->Close();
}

void board_id_test()
{
    int size=15;
    int bad_files[] = {
        17, 20, 30, 31, 37, 39, 41, 67, 70, 72, 
        83, 380, 399, 447, 581
    };
    for(int i=0; i<900; i++)
    {
        // bad files
        bool bad = false;
        for(int j=0; j<size; j++)
            if(bad_files[j] == i) {
                bad=true;
                break;
            } 
        if(bad) continue;

        ostringstream ostr;
        ostr << "../../../data/run_"<<setfill('0')<<setw(4)<<i<<".root";
        //cout<<ostr.str()<<endl;
        //_board_id_test("../../../data/run_0509.root");
        string s = ostr.str();
        cout<<s<<endl;
        _board_id_test(s.c_str());
    }
}
