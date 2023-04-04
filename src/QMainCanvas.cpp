#include "QMainCanvas.h"

#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TSystem.h>
#include <TStyle.h>

#include <iostream>

#include <QMouseEvent>

QMainCanvas::QMainCanvas(QWidget* parent) : QWidget(parent)
{
    if(parent != nullptr)
        resize(parent->width(), parent->height());

    fCanvas = new QRootCanvas(this);
    fCanvas -> resize(width(), height());

    layout = new QVBoxLayout(this);
    layout->addWidget(fCanvas);

    connect(fCanvas, SIGNAL(ItemSelected()), this, SIGNAL(ItemSelected()));
    connect(fCanvas, SIGNAL(ItemDeSelected()), this, SIGNAL(ItemDeSelected()));

    fRootTimer = new QTimer(this);
    QObject::connect(fRootTimer, SIGNAL(timeout()), this, SLOT(handle_root_events()));
    fRootTimer->start(20);

    draw_option = "colz";
}

void QMainCanvas::DrawCanvas()
{
    static TCanvas *c = fCanvas->GetCanvas();
    c -> Clear();
    //gStyle->SetOptStat(0);
    c->cd();
    static TH1F * h = 0; 
    if(h == 0) h = new TH1F("h", "h", 100, -10, 10);
    h->Reset("M");
    h->SetTitle("");
    gPad->SetTopMargin(0.02);
    gPad->SetBottomMargin(0.04);
    h->FillRandom("gaus", 1e6);
    h->Draw();

    c->Modified();
    c->Update();

    Refresh();
}

void QMainCanvas::DrawCanvas(TH1F* _h)
{
    static TCanvas *c = fCanvas -> GetCanvas();
    c -> Clear();
    static TH1F* h = 0;
    h = _h;
    h -> Draw();
    c->Modified();
    c->Update();

    Refresh();
}

void QMainCanvas::DrawCanvas(const std::vector<TH1F*> &h)
{
    int s = h.size();
    if(s <= 0)
        return;

    static TCanvas *c = fCanvas -> GetCanvas();
    c -> Clear();
    c -> Divide(s, 1);

    for(int i=0; i<s; i++) {
        c->cd(i+1);
        h[i] -> Draw();
    }

    c -> Modified();
    c -> Update();

    Refresh();
}

void QMainCanvas::DrawCanvas2D(const std::vector<TH2F*> &h)
{
    int s = h.size();
    if(s <= 0)
        return;

    static TCanvas *c = fCanvas -> GetCanvas();
    c -> Clear();
    c -> Divide(s, 1);

    for(int i=0; i<s; i++) {
        c->cd(i+1);
        gPad->SetLeftMargin(0.1);
        gPad->SetRightMargin(0.1);
        //h[i] -> Draw("LEGO2Z");
        h[i] -> Draw(draw_option.c_str());
    }

    c -> Modified();
    c -> Update();

    Refresh();
}

void QMainCanvas::handle_root_events()
{
    gSystem->ProcessEvents();
}

void QMainCanvas::mousePressEvent(QMouseEvent *e)
{
    switch(e->button()) {
        case Qt::LeftButton:
            emit ItemSelected();
            break;
        case Qt::RightButton:
            emit ItemDeSelected();
            break;
        case Qt::MidButton:
            break;
        default:
            break;
    }
}

void QMainCanvas::Refresh()
{
    fCanvas -> Refresh();
}
