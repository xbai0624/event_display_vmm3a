#ifndef VIEWER_H
#define VIEWER_H

#include "QMainCanvas.h"
#include "ComponentsSchematic.h"
#include "Analyzer.h"

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

class TH1F;

class Viewer : public QWidget
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = 0);
    ~Viewer() {}

    void InitGui();
    void InitComponentsSchematic();

public slots:
    void DrawEvent(int);
    void DrawNextEvent();
    void DrawPrevEvent();
    void InitAnalysis(const QString &);
    void OpenFileDialog();
    void Analyze();

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

    // data cache
    std::vector<std::vector<TH1F*>> data_cache;

    // analyzer
    Analyzer *ana = nullptr;

    // a indicator
    int event_count = 0;
};

#endif
