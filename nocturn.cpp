/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright 2013  Marek Kochanowicz <sirherrbatka@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "nocturn.h"
#include <qapplication.h>
#include <QObject>
#include <QString>

nocturn* nocturn::mThisPointer = nullptr;

nocturn::nocturn()
{
    assert(!mThisPointer);
    mThisPointer = this;
}

nocturn::~nocturn()
{
    delete app;
}

int nocturn::runNoctrun(int argc, char** argv)
{
    app = new QApplication(argc, argv);
    app->setApplicationName("Nocturn");
    bool autoLoadMode = false;

    char * filename = getCmdOption(argv, argv + argc, "-f");
    ModelManager Manager;
    MainControler Controler(&Manager);
    MainView View(Manager.getPlaybackManager()->getPlaybackModel(), autoLoadMode);
    connect(app, SIGNAL(aboutToQuit()), this, SLOT(quitNocturn()) );
    connect(app, SIGNAL(aboutToQuit()), &Controler, SLOT(quitNocturn()));
    Manager.getPlayListManager()->restorePlayListFromFiles();
    if (filename)
    {
        Manager.getPlayListManager()->autoLoadPath(filename);
    }
    View.setFirstTab();
    return app->exec();
}

void nocturn::quitNocturn()
{
    mAboutToQuit = true;
}

nocturn* nocturn::getNocturn()
{
    return mThisPointer;
}

bool nocturn::nocturnQuits() const
{
    return mAboutToQuit;
}

char* nocturn::getCmdOption(char** begin, char** end, const std::string& option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
}
