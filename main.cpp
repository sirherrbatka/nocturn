#include "./nocturn.h"
#include <qapplication.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Nocturn");
    nocturn nocturn;
    return app.exec();
}
