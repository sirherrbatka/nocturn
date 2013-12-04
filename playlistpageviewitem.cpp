#include "./playlistpageviewitem.h"
#include <QDebug>

PlayListPageViewItem::PlayListPageViewItem(const QString& text, int position) :
    QListWidgetItem(text),
    mPosition(position)
{

}

PlayListPageViewItem::~PlayListPageViewItem()
{
qDebug()<<"Item destroyed";
}

int PlayListPageViewItem::getPosition() const
{
    return mPosition;
}
