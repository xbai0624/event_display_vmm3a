#include "Viewer.h"

#include <QGraphicsRectItem>
#include <TH1F.h>
#include <iostream>
#include <QFileInfo>
#include <QFileDialog>
#include <QDir>
#include <QHBoxLayout>
#include <QMessageBox>

Viewer::Viewer(QWidget *parent) : QWidget(parent)
{
    InitGui();
    resize(1200, 600);
    setWindowTitle("VMM Event Display");

    InitAnalysis("./data/run_0588.root");
}

void Viewer::InitGui()
{
    layout = new QGridLayout(this);

    // detector components layout
    InitComponentsSchematic();

    // histogram canvases
    fCanvas1 = new QMainCanvas(this);

    // push button
    l_evt_index = new QLabel("Event Number:", this);
    spin_box = new QSpinBox(this);
    spin_box -> setRange(0, 9999);


    // file path open button
    l_path = new QPushButton("Open &File", this);

    // file path indicator and func widget
    func_widget = new QWidget(this);
    le_path = new QLineEdit("./data/run_0588.root", func_widget);
    btn_analyze = new QPushButton("&Analyze", func_widget);
    QHBoxLayout* _lhy = new QHBoxLayout(func_widget);
    _lhy -> addWidget(le_path);
    _lhy -> addWidget(btn_analyze);

    layout->addWidget(l_path, 0, 0);
    layout->addWidget(func_widget, 0, 1);
    layout->addWidget(spin_box, 1, 1);
    layout->addWidget(l_evt_index, 1, 0);
    layout->addWidget(fCanvas1, 2, 1);
    layout->addWidget(componentsView, 2, 0);

    connect(l_path, SIGNAL(clicked()), this, SLOT(OpenFileDialog()));
    connect(btn_analyze, SIGNAL(clicked()), this, SLOT(Analyze()));
    connect(spin_box, SIGNAL(valueChanged(int)), this, SLOT(DrawEvent(int)));
    connect(le_path, SIGNAL(textChanged(const QString &)), this, SLOT(InitAnalysis(const QString &)));
    connect(fCanvas1, SIGNAL(ItemSelected()), componentsView, SLOT(ItemSelected()));
    connect(fCanvas1, SIGNAL(ItemDeSelected()), componentsView, SLOT(ItemDeSelected()));
}

void Viewer::InitComponentsSchematic()
{
    componentsView = new ComponentsSchematic(this);
    componentsView->resize(800, 400);
    componentsView -> setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored));
}

void Viewer::DrawEvent(int event_to_draw)
{
    if(event_to_draw >= event_count)
        DrawNextEvent();
    if(event_to_draw < event_count)
        DrawPrevEvent();
}

void Viewer::DrawNextEvent()
{
    event_count++;

    // recover from backward event count
    if(event_count <= (int)data_cache.size()) 
    {
        int s = event_count - 1;
        fCanvas1 -> DrawCanvas(data_cache[s]);
        return;
    }

    std::vector<TH1F*> event;
    ana -> GetEvent(event);

    data_cache.push_back(event);

    fCanvas1 -> DrawCanvas(event);
}

void Viewer::DrawPrevEvent()
{
    event_count--;

    if(event_count < 1) 
        return;

    fCanvas1 -> DrawCanvas(data_cache[event_count-1]);
}

void Viewer::InitAnalysis(const QString &)
{
    std::string path = (le_path -> text()).toStdString();

    // check file exist
    if(QFileInfo::exists(QString(path.c_str())))
    {
        if(ana == nullptr)
            ana = new Analyzer();
        ana -> SetFile(path.c_str());

        std::cout<<"Analyzing file: "<<path<<std::endl;
    }
    else {
        std::cout<<path<<" not exist"<<std::endl;
    }

    // reset event counter for online
    //event_count = 0;
}

void Viewer::OpenFileDialog()
{
    QString file_name = QFileDialog::getOpenFileName(
            this,
            "Open Document",
            //QDir::currentPath(),
            "/home/vt",
            //"All files (*.*) ;; evio files (*.evio);; dat files (*.dat)"
            "root files(*.root)"
            );
    le_path -> setText(file_name);
}

void Viewer::Analyze()
{
    std::string path = (le_path -> text()).toStdString();

    // check file exist
    if(QFileInfo::exists(QString(path.c_str())))
    {
        if(ana == nullptr)
            ana = new Analyzer();
        ana -> SetFile(path.c_str());

        std::cout<<"Analyzing file: "<<path<<std::endl;
    }
    else {
        std::cout<<path<<" not exist"<<std::endl;
    }

    ana -> Analyze();
    ana -> Save();

    QMessageBox::information(
            this,
            tr("Event Display"),
            tr("Analysis Done."));
}
