#include "Viewer.h"
#include "Config.h"
#include "histos.hpp"

#include <QApplication>
#include <TApplication.h>
#include <TInterpreter.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    TApplication root_app("root qt", &argc, argv);

    //gInterpreter -> AddIncludePath("./dict/");
    //gInterpreter -> GenerateDictionary("vector<vector<int>>", "vector", "dict");

    Config::instance() -> init("config/cuts.conf");
    Config::instance() -> Print();

    Viewer *view = new Viewer();
    view->show();

    QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
    return app.exec();
}
