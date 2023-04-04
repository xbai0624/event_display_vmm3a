#include "Viewer.h"
#include "Config.h"
#include "histos.hpp"

#include <QApplication>
#include <TApplication.h>
#include <TInterpreter.h>
#include <QStyleFactory>

#define SOLID_PROTOTYPE

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    //app.setStyle(QStyleFactory::create("Fusion"));
    TApplication root_app("root qt", &argc, argv);

    //gInterpreter -> AddIncludePath("./dict/");
    //gInterpreter -> GenerateDictionary("vector<vector<int>>", "vector", "dict");

    // must init Config in here
    Config::instance() -> init("config/cuts.conf");
    Config::instance() -> Print();

    Viewer *view = new Viewer();

#ifdef SOLID_PROTOTYPE
    view -> SetSolidType();
#endif

    view->show();

    QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
    return app.exec();
}
