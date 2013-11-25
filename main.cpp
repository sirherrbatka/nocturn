#include "./mainview.h"
#include "./maincontroler.h"
#include "./modelmanager.h"
#include <cinttypes>
#include <qapplication.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Nocturn");
    ModelManager* Models = new ModelManager();
    MainControler* Controler = new MainControler(Models);
    MainView* View = new MainView(Models->getPlaybackManager()->getPlaybackModel());
    return app.exec();
    delete View;
    delete Models;
    delete Controler;
    //Deleting in this order prevents segfaults. 
}
