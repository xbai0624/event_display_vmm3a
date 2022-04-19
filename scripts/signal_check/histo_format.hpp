#ifndef HISTO_FORMAT_HPP
#define HISTO_FORMAT_HPP

#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TH2F.h>

template<typename T=int> class Format
{
    public:
        Format(){}
        ~Format(){}

        // format tcanvas
        static void __format_canvas(TCanvas *c)
        {
            c->SetTitle(""); // no title
            //c->SetGridx();
            //c->SetGridy();
            c->SetBottomMargin(0.12);
            c->SetLeftMargin(0.12);
            c->SetRightMargin(0.05);
            c->SetTopMargin(0.05);

            gPad->SetLeftMargin(0.15); // gPad exists after creating TCanvas
            gPad->SetBottomMargin(0.15); // gPad exists after creating TCanvas
            gPad->SetFrameLineWidth(2);
        }

        // format TGraph, TGraphErrors
        //template<typename Graph> 
        static void __format_graph(TGraph* g)
        {
            g->SetTitle(""); // no title                                                     
            g->SetMarkerStyle(20);                                                           
            g->SetMarkerSize(1.0);                                                           
            g->SetMarkerColor(1);                                                            

            g->SetLineWidth(2); // xb                                                        
            g->SetLineColor(4); // xb                                                        

            double label_size = 0.045;                                                       
            double title_size = 0.055;
            //g->GetXaxis()->SetTitle(x_title.c_str());                                        
            g->GetXaxis()->SetLabelSize(label_size);                                         
            g->GetXaxis()->SetTitleSize(title_size);                                         
            g->GetXaxis()->SetLabelFont(62);                                                 
            g->GetXaxis()->SetTitleFont(62);
            g->GetXaxis()->SetTitleOffset(1.0);                                              
            g->GetXaxis()->CenterTitle();                                                    

            //g->GetYaxis()->SetTitle(y_title.c_str());                                        
            g->GetYaxis()->SetLabelSize(label_size);                                         
            g->GetYaxis()->SetTitleSize(title_size);                                         
            g->GetYaxis()->SetLabelFont(62);                                                 
            g->GetYaxis()->SetTitleFont(62);
            g->GetYaxis()->SetTitleOffset(1.1);                                              
            g->GetYaxis()->SetNdivisions(505);                                               
            g->GetYaxis()->CenterTitle();   
        }

        // format TH1F*, TH2F*
        //template<typename Histo> 
        static void __format_histo(TH1F* g)
        {
            double label_size = 0.045;                                                       
            double title_size = 0.055;
            //g->GetXaxis()->SetTitle(x_title.c_str());                                        
            g->GetXaxis()->SetLabelSize(label_size);                                         
            g->GetXaxis()->SetTitleSize(title_size);                                         
            g->GetXaxis()->SetLabelFont(62);                                                 
            g->GetXaxis()->SetTitleFont(62);
            g->GetXaxis()->SetTitleOffset(1.0);                                              
            g->GetXaxis()->CenterTitle();                                                    

            //g->GetYaxis()->SetTitle(y_title.c_str());                                        
            g->GetYaxis()->SetLabelSize(label_size);                                         
            g->GetYaxis()->SetTitleSize(title_size);                                         
            g->GetYaxis()->SetLabelFont(62);                                                 
            g->GetYaxis()->SetTitleFont(62);
            g->GetYaxis()->SetTitleOffset(1.1);                                              
            g->GetYaxis()->SetNdivisions(505);                                               
            g->GetYaxis()->CenterTitle();   

            g->SetLineWidth(2);
        }

    private:
};

#endif
