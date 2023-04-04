#include "ViewerSettingWindow.h"
#include <QVBoxLayout>
#include <iostream>

ViewerSettingWindow::ViewerSettingWindow(QWidget *parent) : QWidget(parent)
{
    resize(200, 100);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout -> addWidget(DrawOptionGroupBox());
}

void ViewerSettingWindow::Show()
{
    show();
}

void ViewerSettingWindow::Update(bool s)
{
    for(int i=0; i<N; i++)
        if(check[i] -> isChecked()) {
            draw_option = _options[i];
        }

    emit valueChanged();
}

QGroupBox *ViewerSettingWindow::DrawOptionGroupBox()
{
    QGroupBox *group_box = new QGroupBox(tr("Draw Options"));
    QVBoxLayout *layout = new QVBoxLayout(group_box);

    for(int i=0; i<N; i++){
        check[i] = new QRadioButton(_options[i].c_str());
        layout -> addWidget(check[i]);
        QObject::connect(check[i], SIGNAL(toggled(bool)), this, SLOT(Update(bool)));
    }
    layout -> addStretch(1);

    check[N-1] -> setChecked(true);

    return group_box;
}
