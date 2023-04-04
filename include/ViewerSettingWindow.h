#ifndef VIEWER_SETTING_WINDOW_H
#define VIEWER_SETTING_WINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <string>

//#define N 6

class ViewerSettingWindow : public QWidget
{
    Q_OBJECT

    public:
        ViewerSettingWindow(QWidget *parent = 0);
        ~ViewerSettingWindow(){};

    public slots:
        void Show();
        void Update(bool s);

    signals:
        void valueChanged();

    public:
        std::string GetDrawOption(){return draw_option;}

    private:
        static const int N = 7;
        std::string _options[N] = {
            "colz", "lego2z", "lego", "surf", "surf1", "text", "colz text same"
        };
        std::string draw_option = "colz text same";

        QRadioButton *check[N];

        QGroupBox *DrawOptionGroupBox();
};

#endif
