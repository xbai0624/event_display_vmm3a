#ifndef SHOW_ANALYSIS_RESULT_H
#define SHOW_ANALYSIS_RESULT_H

#include <QWidget>
#include <QCheckBox>
#include <string>
#include <string>

class QMainCanvas;
class TH1F;

//#define N 6

class AnalysisResultWindow : public QWidget
{
    Q_OBJECT

    public:
        AnalysisResultWindow(QWidget *parent = 0);
        ~AnalysisResultWindow(){};

    public slots:
        void Show();
        void PassContents(const std::vector<TH1F*> &c);

    public:
        std::string GetDrawOption(){return draw_option;}

    private:
        static const int N = 7;
        std::string _options[N] = {
            "colz", "lego2z", "lego", "surf", "surf1", "text", "colz text same"
        };
        std::string draw_option = "colz text same";

        QMainCanvas *fCanvas;
        std::vector<TH1F*> draw_contents;
};

#endif
