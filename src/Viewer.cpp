#include "Viewer.h"
#include "AnalysisResultWindow.h"

#include <QGraphicsRectItem>
#include <TH1F.h>
#include <iostream>
#include <QFileInfo>
#include <QFileDialog>
#include <QDir>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QAction>

Viewer::Viewer(QWidget *parent) : QWidget(parent)
{
    InitGui();
    AddMenuBar();
    resize(1200, 600);
    setWindowTitle("VMM Event Display");

    InitAnalysis("./data/run_0588.root");
    //InitAnalysis("./backup/cosmic_3.bin");
}

void Viewer::InitGui()
{
    layout = new QGridLayout(this);

    // detector components layout
    InitLeftCtrlPanel();

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
    //le_path = new QLineEdit("./backup/cosmic_3.bin", func_widget);
    btn_analyze = new QPushButton("&Analyze", func_widget);
    QHBoxLayout* _lhy = new QHBoxLayout(func_widget);
    _lhy -> addWidget(le_path);
    _lhy -> addWidget(btn_analyze);

    layout->addWidget(l_path, 0, 0);
    layout->addWidget(func_widget, 0, 1);
    layout->addWidget(spin_box, 1, 1);
    layout->addWidget(l_evt_index, 1, 0);
    layout->addWidget(fCanvas1, 2, 1);
    layout->addWidget(left_ctrl_panel, 2, 0);

    connect(l_path, SIGNAL(clicked()), this, SLOT(OpenFileDialog()));
    connect(btn_analyze, SIGNAL(clicked()), this, SLOT(Analyze()));
    connect(spin_box, SIGNAL(valueChanged(int)), this, SLOT(DrawEvent(int)));
    connect(le_path, SIGNAL(textChanged(const QString &)), this, SLOT(InitAnalysis(const QString &)));
    //connect(fCanvas1, SIGNAL(ItemSelected()), componentsView, SLOT(ItemSelected()));
    //connect(fCanvas1, SIGNAL(ItemDeSelected()), componentsView, SLOT(ItemDeSelected()));

    connect(this, SIGNAL(analyzeDone()), this, SLOT(PopupAnalysisResult()));

    result_window = new AnalysisResultWindow();
}

void Viewer::InitComponentsSchematic(QWidget *parent)
{
    //componentsView = new ComponentsSchematic(parent);
    //componentsView->resize(100, 100);
    //componentsView -> setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored));
}

void Viewer::InitLeftCtrlPanel()
{
    left_ctrl_panel = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(left_ctrl_panel);

    // logo
    InitComponentsSchematic(left_ctrl_panel);

    // check box for writing plots to disk
    save_to_disk = new QCheckBox("Save Event", left_ctrl_panel);

    layout -> addWidget(save_to_disk);
    //layout -> addWidget(componentsView);
    layout -> addWidget(GEMChamberTypeGroupBox());
    layout -> addWidget(VMMBoardTypeGroupBox());
}

void Viewer::AddMenuBar()
{
    pMenuBar = new QMenuBar();

    // file menu
    pMenu = new QMenu("file");
    pMenu -> addAction("save");
    pMenu -> addAction("exit");
    pMenuBar -> addMenu(pMenu);

    // settings menu
    pSetting = new QMenu("settings");
    pSetting -> addAction("2d hist draw option", this, SLOT(UpdateSetting()));
    pMenuBar -> addMenu(pSetting);

    viewer_setting = new ViewerSettingWindow();
    connect(viewer_setting, SIGNAL(valueChanged()), this, SLOT(UpdateSetting()));

    // analysis menu
    pAnalysis = new QMenu("analysis");
    pAnalysis -> addAction("analysis", this, SLOT(Analyze()));
    pMenuBar -> addMenu(pAnalysis);

    // help menu
    pHelp = new QMenu("help");
    pHelp -> addAction("help");
    pMenuBar -> addMenu(pHelp);

    layout->setMenuBar(pMenuBar);
}

QGroupBox *Viewer::GEMChamberTypeGroupBox()
{
    QGroupBox *groupbox = new QGroupBox("GEM Type");
    QVBoxLayout *layout = new QVBoxLayout(groupbox);

    uva_gem = new QRadioButton("UVa GEM");
    uva_gem -> setChecked(true);
    msu_gem = new QRadioButton("MSU GEM");

    layout -> addWidget(uva_gem);
    layout -> addWidget(msu_gem);

    connect(uva_gem, SIGNAL(toggled(bool)), this, SLOT(UpdateGEMChamberType(bool)));
    connect(msu_gem, SIGNAL(toggled(bool)), this, SLOT(UpdateGEMChamberType(bool)));

    return groupbox;
}

QGroupBox *Viewer::VMMBoardTypeGroupBox()
{
    QGroupBox *groupbox = new QGroupBox("VMM Board Type");
    QVBoxLayout *layout = new QVBoxLayout(groupbox);

    solid_vmm_board = new QRadioButton("SoLID Type");
    solid_vmm_board -> setChecked(true);
    gp_vmm_board = new QRadioButton("GPVMM Type");

    layout -> addWidget(solid_vmm_board);
    layout -> addWidget(gp_vmm_board);

    connect(solid_vmm_board, SIGNAL(toggled(bool)), this, SLOT(UpdateGEMChamberType(bool)));
    connect(gp_vmm_board, SIGNAL(toggled(bool)), this, SLOT(UpdateGEMChamberType(bool)));

    return groupbox;
}


void Viewer::UpdateGEMChamberType(bool s)
{
    if(uva_gem -> isChecked())
        gem_chamber_type = 0;
    if(msu_gem -> isChecked())
        gem_chamber_type = 1;

    ana -> SetGEMChamberType(gem_chamber_type);
}

void Viewer::UpdateVMMBoardType(bool s)
{
    if(solid_vmm_board -> isChecked())
        is_solid_type = true;
    if(gp_vmm_board -> isChecked())
        is_solid_type = false;

    ana -> SetVMMBoardType(is_solid_type);
}


void Viewer::UpdateSetting()
{
    viewer_setting -> show();
    std::string option = viewer_setting -> GetDrawOption();
    std::cout<<"change histo draw option to: "<<option<<std::endl;
    fCanvas1 -> SetDrawOption(option);

    DrawEvent(event_count);
}

void Viewer::DrawEvent(int event_to_draw)
{
    if(ana == nullptr) {
        std::cout<<"WARNING:: Analyzer not initialized."<<std::endl;
        return;
    }

    ana -> SetOnlineEventId(event_to_draw);

    if(event_to_draw >= event_count)
    {
        if(is_solid_type)
            DrawNextEvent2D();
        else
            DrawNextEvent();
    }
    if(event_to_draw < event_count)
    {
        if(is_solid_type)
            DrawPrevEvent2D();
        else
            DrawPrevEvent();
    }
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
    SaveCurrentEvent(event);

    data_cache.push_back(event);

    fCanvas1 -> DrawCanvas(event);
}

void Viewer::DrawNextEvent2D()
{
    event_count++;

    // recover from backward event count
    if(event_count <= (int)data_cache_2d.size()) 
    {
        int s = event_count - 1;
        fCanvas1 -> DrawCanvas2D(data_cache_2d[s]);
        return;
    }

    std::vector<TH2F*> event;
    ana -> GetEvent2D(event);
    SaveCurrentEvent(event);

    data_cache_2d.push_back(event);

    fCanvas1 -> DrawCanvas2D(event);
}

void Viewer::DrawPrevEvent()
{
    event_count--;

    if(event_count < 1) 
        return;

    fCanvas1 -> DrawCanvas(data_cache[event_count-1]);
}

void Viewer::DrawPrevEvent2D()
{
    event_count--;

    if(event_count < 1) 
        return;

    fCanvas1 -> DrawCanvas2D(data_cache_2d[event_count-1]);
}

void Viewer::DrawSolidPrototypeEvent(int i)
{
}

void Viewer::SaveCurrentEvent(const std::vector<TH1F*> &event)
{
    if(!save_to_disk->isChecked())
        return;

    // parse file name
    std::string path = (le_path -> text()).toStdString();
    size_t pos1 = path.find_last_of("/");
    size_t pos2 = path.find_last_of(".");
    path = path.substr(pos1+1, pos2 - pos1 - 1);
    path = "cache_plots/" + path + "_event_" + std::to_string(event_count) + ".root";

    TFile *f = new TFile(path.c_str(), "recreate");
    for(auto &i: event)
        i -> Write();
    f->Close();
}

void Viewer::SaveCurrentEvent(const std::vector<TH2F*> &event)
{
    if(!save_to_disk->isChecked())
        return;

    // parse file name
    std::string path = (le_path -> text()).toStdString();
    size_t pos1 = path.find_last_of("/");
    size_t pos2 = path.find_last_of(".");
    path = path.substr(pos1+1, pos2 - pos1 - 1);
    path = "cache_plots/" + path + "_event_" + std::to_string(event_count) + ".root";

    TFile *f = new TFile(path.c_str(), "recreate");
    for(auto &i: event)
        i -> Write();
    f->Close();
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
    spin_box -> setValue(0);
}

void Viewer::OpenFileDialog()
{
    QString file_name = QFileDialog::getOpenFileName(
            this,
            "Open Document",
            //QDir::currentPath(),
            "/home/vt/event_display_vmm3a/daq/",
            //"All files (*.*) ;; evio files (*.evio);; dat files (*.dat)"
            "all files(*.*)"
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

    if(is_solid_type)
        ana -> AnalyzeSolidType();
    else
        ana -> Analyze();
    ana -> Save();

    QMessageBox::information(
            this,
            tr("Event Display"),
            tr("Analysis Done."));

    emit analyzeDone();
}

void Viewer::PopupAnalysisResult()
{
    auto histos = ana -> GetResultHistos1D();

    std::vector<TH1F*> temp;
    for(auto &i: histos)
        temp.push_back((TH1F*)i.second);
    result_window -> PassContents(temp);

    result_window -> Show();
}
