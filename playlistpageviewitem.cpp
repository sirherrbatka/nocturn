#include "./playlistpageviewitem.h"
#include <QObject>
#include <QDebug>
#include "./playlistpageview.h"

PlayListPageViewItem::PlayListPageViewItem(const std::map<unsigned long long, AudioTrackModel>::iterator& Model, int position, PlayListPageView* parent) :
    mAudioTrackModel(Model),
    mPosition(position),
    mParent(parent)
{
    setLabel(false);
    mAudioTrackModel->second.storeThis(Model);
    connect(&(mAudioTrackModel->second), SIGNAL(NeedRefreshLabel()), this, SLOT(setLabel()));
}

PlayListPageViewItem::~PlayListPageViewItem()
{
}

int PlayListPageViewItem::getPosition() const
{
    return mPosition;
}

void PlayListPageViewItem::setLabel(bool bold)
{
    setText(mAudioTrackModel->second.getArtist() + " - " + mAudioTrackModel->second.getName());
    QFont font;
    if (bold or mAudioTrackModel->second.isPlayed())
    {
        font.setBold(true);
    } else {
        font.setBold(false);
    }
    setFont(font);
}

void PlayListPageViewItem::storeAudioTrackModel(const std::map< unsigned long long, AudioTrackModel >::iterator& Model)
{
    mAudioTrackModel = Model;
}

std::map< unsigned long long, AudioTrackModel >::iterator PlayListPageViewItem::getAudioTrackModel()
{
    return mAudioTrackModel;
}

void PlayListPageViewItem::playThisTrack()
{
    mAudioTrackModel->second.playThisTrack();
}