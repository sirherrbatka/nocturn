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
#include "mainview.h"
#include "ui_mainform.h"
#include <QtGui/QMainWindow>
#include <QDebug>
#include <QUrl>
#include <QKeyEvent>
#include <Qt>
#include <QHBoxLayout>
#include "./maincontroler.h"
#include "./playlistpageview.h"
#include "playbackmodel.h"
#include <QMimeData>
#include "./playbackphonon.h"
#include "settingsview.h"
#include "settingsmanager.h"
#include <QToolButton>
#include <qt4/QtGui/qicon.h>


MainView::MainView(PlaybackModel* PlaybackModel, bool autoLoadMode) :
    QMainWindow(),
    mTrayIcon(QIcon(":/nocturn.png"))
{
    setAcceptDrops(true);
    setupUi(this);
    statusBar()->setVisible(false);
    this->statusLabel->setText(tr("Stopped"));
//Phonon related stuff.
    PlaybackPhonon* phonon = dynamic_cast<PlaybackPhonon*>(PlaybackModel);
    this->seekSlider->setMediaObject(phonon->getPhonon());
    this->volumeSlider->setAudioOutput(phonon->getAudio());

    //Playlists tabwidget related.
    QWidget* newTabButton = new QToolButton(this->PlayListsTabs);
    (dynamic_cast<QToolButton*>(newTabButton))->setIcon(QIcon::fromTheme("list-add"));
    this->PlayListsTabs->setCornerWidget(newTabButton, Qt::TopRightCorner);

    connect(SettingsManager::getSettingsManager(), SIGNAL(ConfigurationUpdated()), this, SLOT(updateTrayVisiblity()));

    //Inner mainview connections
    connect(this->PlayListsTabs, SIGNAL(currentChanged(int)), this, SLOT(notifyPlayListManagerAboutActivePlayListChange(int)));
    connect(this, SIGNAL(modelSignal(PlayListModel*)), MainControler::getMainControler(), SLOT(changeActivePlayList(PlayListModel*)));
    connect(this->toggleButton, SIGNAL(clicked()), this, SLOT(toggleButtonControl()));
    connect(this->PlayListsTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(newTabButton, SIGNAL(clicked()), this, SLOT(newPlayListView()));
    connect(actionShow_Configuration, SIGNAL(triggered()), this, SLOT(showConfWindow()));

//Mainview -> main controler
    connect(this, SIGNAL(TogglePlayback()), MainControler::getMainControler(), SLOT(togglePlayback()));
    connect(this, SIGNAL(StartPlaybackOnActivePlaylist()), MainControler::getMainControler(), SLOT(startPlayback()));
    connect(this->repeatButton, SIGNAL(clicked()), MainControler::getMainControler(), SLOT(setRepeateMode()));
    connect(this->nextButton, SIGNAL(clicked()), MainControler::getMainControler(), SLOT(nextTrack()));
    connect(this->prevButton, SIGNAL(clicked()), MainControler::getMainControler(), SLOT(prevTrack()));
    connect(this->clearButton, SIGNAL(clicked()), MainControler::getMainControler(), SLOT(clearActivePlayList()));
    connect(this, SIGNAL(pathDropped(QList<QUrl>)), MainControler::getMainControler(), SLOT(addPathToPlayList(QList<QUrl>)));

//     Main controler ->mainview
    connect(MainControler::getMainControler(), SIGNAL(StatusChanged(SharedTypes::PlaybackState, SharedTypes::PlaybackState)), this, SLOT(changeStatus(SharedTypes::PlaybackState, SharedTypes::PlaybackState)));
    connect(MainControler::getMainControler(), SIGNAL(TotalDurationChanged(unsigned long long)), this, SLOT(refreshTotalDurationLabel(unsigned long long)) );
    connect(MainControler::getMainControler(), SIGNAL(RelayPlayListModel(std::vector<PlayListModel*>)),this, SLOT(relayPlayListModel(std::vector<PlayListModel*>)));
    connect(MainControler::getMainControler(), SIGNAL(AutoLoadedPlayList(PlayListModel*)), this, SLOT(autoLoadPlayList(PlayListModel*)));

    //Key handler of main view -> Main view key handler
    connect(&mKeyHandler, SIGNAL(CloseTabKey(int)), this, SLOT(closeTab(int)));
    connect(&mKeyHandler, SIGNAL(NewPlayListViewKey()), this, SLOT(newPlayListView()));
    connect(&mKeyHandler, SIGNAL(SwitchPlayListViewKey(int)), this, SLOT(switchPlayListView(int)));

    setWindowIcon(QIcon(":/nocturn.png"));
    show();
}

void MainView::dropEvent(QDropEvent *ev)
{
    emit pathDropped(ev->mimeData()->urls());
}

void MainView::dragEnterEvent(QDragEnterEvent *ev)
{
    if (ev->mimeData()->hasUrls())
    {
        ev->accept();
    }
}

void MainView::newPlayListView(bool autoswitch, PlayListModel* playlist)
{
    QWidget* playlistpageview;
    if(playlist != nullptr)
    {
        qDebug()<<"Playlist pointer supplied";
        playlistpageview = new PlayListPageView(playlist, this->PlayListsTabs, &mKeyHandler);
    } else {
        playlistpageview = new PlayListPageView( MainControler::getMainControler()->generatePlayListModel(), this->PlayListsTabs, &mKeyHandler);
    }
    int index = this->PlayListsTabs->addTab(playlistpageview, dynamic_cast<PlayListPageView*>(playlistpageview)->getPlayListName());
    if (autoswitch)
    {
        PlayListsTabs->setCurrentIndex(index);
    }
}

void MainView::closeTab(int index = -1)
{
    if (PlayListsTabs->count() == 1) //there has to be at least on playlist all the time
    {
        newPlayListView(false); //false = no auto switching
    }
    if (index == -1)
    {
        index = this->PlayListsTabs->currentIndex();
    }
    QWidget* locDeleteMe = this->PlayListsTabs->widget(index);
    this->PlayListsTabs->removeTab(index);
    delete locDeleteMe;
}

PlayListModel* MainView::getPlayListModel(int index)
{
    QWidget* locCurrent = this->PlayListsTabs->widget(index);
    PlayListPageView* locCurrentPlaylist = static_cast<PlayListPageView*>(locCurrent);
    return locCurrentPlaylist->getModel();
}

void MainView::notifyPlayListManagerAboutActivePlayListChange(int index)
{
    emit modelSignal(getPlayListModel(index));
}

void MainView::changeStatus(SharedTypes::PlaybackState newstatus, SharedTypes::PlaybackState oldstatus)
{
    mState = newstatus;
    if (newstatus == SharedTypes::PlayingState or newstatus == SharedTypes::StoppedState or newstatus == SharedTypes::PausedState)
    {
        updateLabel();
        updateToggleButtonIcon();
    }
    mKeyHandler.newPlaybackStatus(newstatus);
}

inline void MainView::updateLabel()
{
    switch (mState)
    {
    case SharedTypes::PlayingState:
        this->statusLabel->setText(tr("Playing"));
        break;
    case SharedTypes::StoppedState:
        this->statusLabel->setText(tr("Stopped"));
        break;
    case SharedTypes::BufferingState:
        this->statusLabel->setText(tr("Buffering"));
        break;
    case SharedTypes::ErrorState:
        this->statusLabel->setText(tr("Error"));
        break;
    case SharedTypes::LoadingState:
        this->statusLabel->setText(tr("Loading"));
        break;
    case SharedTypes::PausedState:
        this->statusLabel->setText(tr("Paused"));
        break;
    }
    repaint();
    update();
    qDebug()<<"Updating status label";
}

void MainView::updateTrayVisiblity()
{
    mTrayIcon.setVisible(SettingsManager::getSettingsManager()->getShowTrayIcon());
}

void MainView::toggleButtonControl()
{
    switch(mState)
    {
    case SharedTypes::StoppedState:
        emit StartPlaybackOnActivePlaylist();
        break;
    default:
        emit TogglePlayback();
        break;
    }
}

void MainView::updateToggleButtonIcon()
{
    QIcon newIcon;
    switch (mState)
    {
    default:
        return;
        break;
    case SharedTypes::PlayingState:
        newIcon = QIcon::fromTheme("media-playback-pause");
        break;
    case SharedTypes::PausedState:
        newIcon = QIcon::fromTheme("media-playback-start");
        break;
    case SharedTypes::StoppedState:
        newIcon = QIcon::fromTheme("media-playback-start");
        break;
    }

    this->toggleButton->setIcon(newIcon);
}

void MainView::refreshTotalDurationLabel(unsigned long long duration)
{
    if (duration == 0)
    {
        mDurationLabel->clear();
        return;
    }
    unsigned hours = duration/3600;
    duration -= hours*3600;
    unsigned minutes = duration/60;
    duration -= minutes*60;
    unsigned seconds = duration;

    QString minutesstring;
    QString secondsstring;
    QString hoursstring("");
    if (seconds < 10)
    {
        secondsstring = QString::number(0) + QString::number(seconds);
    } else {
        secondsstring = QString::number(seconds);
    }

    if (minutes < 10)
    {
        minutesstring = QString::number(0) + QString::number(minutes);
    } else {
        minutesstring = QString::number(minutes);
    }

    if (hours != 0)
    {
        hoursstring = QString::number(hours) + ":";
    }

    mDurationLabel->setText(hoursstring + minutesstring + ":" + secondsstring);
}

void MainView::keyPressEvent(QKeyEvent *ev)
{
    ev->setAccepted(true);
    mKeyHandler.grabKeyEvent(ev->key());
}

MainViewKeyHandler* MainView::getKeyHandler()
{
    return &mKeyHandler;
}

void MainView::switchPlayListView(int side)
{
    int size = this->PlayListsTabs->count();
    int index = this->PlayListsTabs->currentIndex();
    int newindex = index + side;
    if (newindex < 0)
    {
        newindex = size + newindex;
    }

    if (newindex >= size)
    {
        newindex = newindex - size ;
    }
    this->PlayListsTabs->setCurrentIndex(newindex);
}

void MainView::relayPlayListModel(const std::vector< PlayListModel* >& playlists)
{
    if (playlists.empty())
    {
        newPlayListView(false);
    }
    for (auto &each : playlists)
    {
        newPlayListView(false, each);
    }
}

void MainView::autoLoadPlayList(PlayListModel* playlist)
{
    newPlayListView(true, playlist);
}

void MainView::setFirstTab()
{
    if (!(PlayListsTabs->count()))
    {
        newPlayListView();
    }
}

void MainView::showConfWindow()
{
    SettingsView settings;
    settings.exec();
}

void MainView::updateWindowTitle(const QString& title)
{
    if (SettingsManager::getSettingsManager()->getSongAsWindowTitle() and !title.isEmpty())
    {
        setWindowTitle(title);
    } else {
        setWindowTitle("Nocturn");
    }
}
