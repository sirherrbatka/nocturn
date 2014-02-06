#include "./playlistpageviewitem.h"
#include <QObject>
#include <QDebug>
#include "./playlistpageview.h"

PlayListPageViewItem::PlayListPageViewItem(unsigned int position, PlayListPageView* parent) :
    mPosition(position),
    mParent(parent)
{
    setLabel(false);
}

PlayListPageViewItem::~PlayListPageViewItem()
{
}

unsigned PlayListPageViewItem::getPosition() const
{
    return mPosition;
}

void PlayListPageViewItem::setLabel(bool bold)
{
  const AudioTrackModel& track = mParent->getAudioTrackModel(mPosition);
    setText(track.getArtist() + " - " + track.getName());
    QFont font;
    if (bold or track.isPlayed())
    {
        font.setBold(true);
    } else {
        font.setBold(false);
    }
    setFont(font);
}