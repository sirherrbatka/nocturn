#include "./fsview.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QRegExp>
#include <iostream>

#include "settingsmanager.h"
#include "maincontroler.h"

FSView::FSView() :
mList(),
mEnterField(),
mModel()
{
    const QString& pathToMusic = SettingsManager::getSettingsManager()->getSetting("File/PathToMusic").toString();
    connect(&mModel, SIGNAL(directoryLoaded(QString)), this, SLOT(modelDirectoryLoaded(QString)));
    if (pathToMusic.isEmpty())
    {
        mModel.setRootPath(QDir::homePath());
    } else {
        mModel.setRootPath(pathToMusic);
    }
    mModel.setFilter(QDir::NoDotAndDotDot |
                     QDir::QDir::AllEntries);
    mList.setModel(&mModel);
    mList.setSelectionMode(QAbstractItemView::SingleSelection);
    mList.setUniformItemSizes(true);
    mModel.setNameFilterDisables(false);
    connect(&mEnterField, SIGNAL(textChanged(QString)), this, SLOT(createMatching(QString)));
    QVBoxLayout* layout = new QVBoxLayout(this);

    mList.setFocusPolicy(Qt::NoFocus);
    mEnterField.setFocusPolicy(Qt::NoFocus);

    mEnterField.hide();
    layout->addWidget(&mList, 0);
    layout->addWidget(&mEnterField, 1);

    this->setFocusPolicy(Qt::WheelFocus);
    this->setFocus(Qt::OtherFocusReason);
}

void FSView::broadMatching(const QString& string)
{

}

void FSView::clearMatching(const QString& string)
{

}

void FSView::createMatching(const QString& string)
{
    if (string.isEmpty())
    {
        mModel.setNameFilters(QStringList("*"));
        return;
    }

    if (string == mSearchText)
    {
        return;
    }
    mList.setCurrentIndex(mModel.index(0, 0));
    QStringList filters;
    filters<<"*"+string+"*";
    mModel.setNameFilters(filters);
    mList.setCurrentIndex(mModel.index(0, 0, mModel.index(mModel.rootPath())));
}

void FSView::focusNextMatching()
{

}

void FSView::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        close();
        return;
    }

    const QModelIndex& current = mList.currentIndex();
    if (!current.isValid())
    {
        mList.setCurrentIndex(mModel.index(0, 0, mModel.index(mModel.rootPath())));
    }


    if(event->key() == Qt::Key_Up)
    {
        if (mList.currentIndex().isValid())
        {
            if (mList.currentIndex().row() == 0)
            {
                mList.setCurrentIndex(mModel.index(mModel.rowCount(mModel.index(mModel.rootPath()))-1, 0, mModel.index(mModel.rootPath())));
            } else {
                mList.setCurrentIndex(mModel.index(current.row()-1, 0, mModel.index(mModel.rootPath())));
            }
        }
        return;
    }

    if (event->key() == Qt::Key_Down)
    {
        if (mList.currentIndex().isValid())
        {
            if (mList.currentIndex().row() == mModel.rowCount(mModel.index(mModel.rootPath()))-1)
            {
                mList.setCurrentIndex(mModel.index(0, 0, mModel.index(mModel.rootPath())));
            } else {
                mList.setCurrentIndex(mModel.index(current.row()+1, 0, mModel.index(mModel.rootPath())));
            }
        }
        return;
    }

    if (mSearchMode)
    {
        if (event->key() == Qt::Key_Return)
        {
            mSearchMode = false;
            mEnterField.hide();
        } else {
            if (!event->text().isEmpty())
            {
                mSearchText = mEnterField.text();
                QApplication::sendEvent(&mEnterField, event);
            }
        }
        QDialog::keyPressEvent(event);
    } else {
        if (event->key() == Qt::Key_Slash)
        {
            mSearchMode = true;
            mEnterField.show();
            QDialog::keyPressEvent(event);
            return;
        }

        if (!mList.currentIndex().isValid())
        {
            const QModelIndex& first = mModel.index(0, 0);
            if (first.isValid())
            {
                mList.setCurrentIndex(first);
            }
        }

        if (event->key() == Qt::Key_Return)
        {
            const QModelIndex& current = mList.currentIndex();
            const QString& path = mModel.filePath(current);
            mModel.setRootPath(path);
            mList.setCurrentIndex(mModel.index(0, 0, mModel.index(mModel.rootPath())));
            mEnterField.clear();
            return;
        }

        if (event->key() == Qt::Key_Backspace)
        {
            QString path(mModel.rootPath());
            path.chop(path.length() - 1 - path.lastIndexOf(QDir::separator()));
            mModel.setRootPath(path);
            mList.setCurrentIndex(mModel.index(0, 0, mModel.index(path)));
            mEnterField.clear();
            return;
        }

        if (event->key() == Qt::Key_Space)
        {
            const QModelIndex& current = mList.currentIndex();
            const QString& path = mModel.filePath(current);
            QList<QUrl> list;
            list.append(QUrl(path));
            MainControler::getMainControler()->addPathToPlayList(list);
            return;
        }

        if (!event->text().isEmpty() &&
            event->key() != Qt::Key_Delete)
        {
            QApplication::sendEvent(&mList, event);
            QDialog::keyPressEvent(event);
        }
    }
}

void FSView::narrowMatching(const QString& string)
{

}

void FSView::modelDirectoryLoaded(const QString& string)
{
    mList.setRootIndex(mModel.index(string));
}
