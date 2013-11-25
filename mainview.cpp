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
#include "./maincontroler.h"
#include "./playlistpageview.h"
#include "playbackmodel.h"
#include <QMimeData>
#include "./playbackphonon.h"

MainView::MainView(PlaybackModel* PlaybackModel) :
    QMainWindow()
{
    setAcceptDrops(true);
    setupUi(this);
    this->statusLabel->setText(tr("Stopped"));
    show();

    PlaybackPhonon* phonon = dynamic_cast<PlaybackPhonon*>(PlaybackModel);

    this->seekSlider->setMediaObject(phonon->getPhonon());
    this->volumeSlider->setAudioOutput(phonon->getAudio());
    connect(this, SIGNAL(pathDropped(QList<QUrl>)), MainControler::getMainControler(), SLOT(addPathToPlayList(QList<QUrl>)));
    connect(this->PlayListsTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(this->newButton, SIGNAL(clicked()), this, SLOT(newPlayListView()));

//     TODO find more elegant way for the below connections
    connect(this->PlayListsTabs, SIGNAL(currentChanged(int)), this, SLOT(notifyPlayListManagerAboutActivePlayListChange(int)));
    connect(this, SIGNAL(modelSignal(PlayListModel*)), MainControler::getMainControler(), SLOT(changeActivePlayList(PlayListModel*)));

    connect(this->toggleButton, SIGNAL(clicked()), this, SLOT(toggleButtonControl()));
    connect(this, SIGNAL(TogglePlayback()), MainControler::getMainControler(), SLOT(togglePlayback()));
    connect(this, SIGNAL(StartPlaybackOnActivePlaylist()), MainControler::getMainControler(), SLOT(startPlayback()));

    connect(MainControler::getMainControler(), SIGNAL(StatusChanged(SharedTypes::PlaybackState, SharedTypes::PlaybackState)), this, SLOT(changeStatus(SharedTypes::PlaybackState, SharedTypes::PlaybackState)));
    connect(this->nextButton, SIGNAL(clicked()), MainControler::getMainControler(), SLOT(nextTrack()));
    connect(this->prevButton, SIGNAL(clicked()), MainControler::getMainControler(), SLOT(prevTrack()));
    newPlayListView();
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

void MainView::newPlayListView()
{
    const QString label = "Playlist";
    QWidget* playlistpageview = new PlayListPageView( MainControler::getMainControler()->generatePlayListModel() );
    this->PlayListsTabs->addTab(playlistpageview, label);
}

void MainView::closeTab(int index)
{
    if (PlayListsTabs->count() == 1) //there has to be at least on playlist all the time
    {
        newPlayListView();
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
    }
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
