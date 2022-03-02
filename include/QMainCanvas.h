#ifndef QMAINCANVAS_H
#define QMAINCANVAS_H

#include "QRootCanvas.h"

#include <QVBoxLayout>
#include <QTimer>
#include <vector>

class TH1F;

class QMainCanvas : public QWidget
{
    Q_OBJECT

public:
    QMainCanvas(QWidget *parent = 0);
    ~QMainCanvas() {}

    void Refresh();

public slots:
    void DrawCanvas();
    void DrawCanvas(TH1F*);
    void DrawCanvas(const std::vector<TH1F*>&);
    void handle_root_events();

signals:
    void ItemSelected();
    void ItemDeSelected();

protected:
    virtual void mousePressEvent(QMouseEvent *);

protected:
    QRootCanvas *fCanvas;
    QVBoxLayout *layout;

    QTimer *fRootTimer;
};

#endif
