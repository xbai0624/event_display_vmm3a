#include "AnalysisResultWindow.h"
#include <QHBoxLayout>
#include "QMainCanvas.h"
#include <iostream>
#include <TH1F.h>

AnalysisResultWindow::AnalysisResultWindow(QWidget *parent) : QWidget(parent)
{
    resize(1200, 500);

    fCanvas = new QMainCanvas(this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout -> addWidget(fCanvas);
}

void AnalysisResultWindow::Show()
{
    show();

    fCanvas -> DrawCanvas(draw_contents);
}

void AnalysisResultWindow::PassContents(const std::vector<TH1F*> &c)
{
    draw_contents.clear();

    for(auto &i: c)
        draw_contents.push_back(i);
}

