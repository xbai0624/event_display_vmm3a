#ifndef VIEWER_H
#define VIEWER_H

#include "QMainCanvas.h"
#include "ComponentsSchematic.h"
#include "Analyzer.h"
#include "ViewerSettingWindow.h"

#include <vector>

#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QMenu>
#include <QMenuBar>
#include <QGroupBox>
#include <QRadioButton>

class TH1F;
class AnalysisResultWindow;

class Viewer : public QWidget
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = 0);
    ~Viewer() {}

    void InitGui();
    void AddMenuBar();
    void InitComponentsSchematic(QWidget *parent = nullptr);
    void InitLeftCtrlPanel();
    void SaveCurrentEvent(const std::vector<TH1F*> &event);
    void SaveCurrentEvent(const std::vector<TH2F*> &event);
    void SetSolidType() {is_solid_type = true;}
    void UnsetSolidType() {is_solid_type = false;}
    QGroupBox *GEMChamberTypeGroupBox();

public slots:
    void DrawEvent(int);
    void DrawSolidPrototypeEvent(int);
    void DrawNextEvent();
    void DrawPrevEvent();
    void DrawNextEvent2D();
    void DrawPrevEvent2D();
    void InitAnalysis(const QString &);
    void OpenFileDialog();
    void UpdateSetting();
    void Analyze();
    void PopupAnalysisResult();
    void UpdateGEMChamberType(bool);

signals:
    void analyzeDone();

private:
    QLabel *l_evt_index;
    QSpinBox *spin_box;

    QPushButton *l_path;
    QLineEdit *le_path;
    QPushButton *btn_analyze;
    QPushButton *btn_save_event;
    QWidget *func_widget;

    ComponentsSchematic *componentsView;
    QMainCanvas *fCanvas1;

    QGridLayout *layout;

    // left control panel
    QWidget *left_ctrl_panel;
    QCheckBox *save_to_disk;

    // menu bar
    QMenuBar *pMenuBar;
    QMenu *pMenu;
    QMenu *pHelp;
    QMenu *pSetting;
    QMenu *pAnalysis;
    ViewerSettingWindow *viewer_setting;

    // qradiobutton to choose GEM detector type
    QGroupBox *chamberTypeGroup;
    QRadioButton *msu_gem;
    QRadioButton *uva_gem;

    // data cache
    std::vector<std::vector<TH1F*>> data_cache;
    std::vector<std::vector<TH2F*>> data_cache_2d;

    // analyzer
    Analyzer *ana = nullptr;

    // a indicator
    int event_count = 0;

    // solid prototype board
    bool is_solid_type = true;

    // when Analyze() function is done, show the result
    AnalysisResultWindow *result_window;

    // GEM detector type
    int gem_chamber_type = 0; // UVa GEM = 0, MSU GEM = 1
};

#endif
