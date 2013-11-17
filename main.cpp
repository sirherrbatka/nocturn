#include "./mainview.h"
#include "./maincontroler.h"
#include "./modelmanager.h"
#include <cinttypes>
#include <qapplication.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Nocturn");
    ModelManager ModelManager;
    MainControler MainControler(&ModelManager);
    MainView MainView(ModelManager.getPlaybackManager()->getPlaybackModel());
    return app.exec();
}
