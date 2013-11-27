#include "./playlistpageviewitem.h"

PlayListPageViewItem::PlayListPageViewItem(const QString& text, int position) :
    QListWidgetItem(text),
    mPosition(position)
{

}

PlayListPageViewItem::~PlayListPageViewItem()
{

}

int PlayListPageViewItem::getPosition() const
{
    return mPosition;
}
