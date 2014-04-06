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
    const QString& pathToMusic = SettingsManager::getSettingsManager()->getSetting("file/PathToMusic").toString();
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
    mList.setCurrentIndex(mModel.index(0, 0, mModel.index(mModel.rootPath())));
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
        mModel.setNameFilters(QStringList());
        return;
    }

    if (string == mSearchText)
    {
        return;
    }
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

    if(event->key() == Qt::Key_Up)
    {
        const QModelIndex& current = mList.currentIndex();
        if (!current.isValid())
        {
            mList.setCurrentIndex(mModel.index(0, 0, mModel.index(mModel.rootPath())));
        }

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
        const QModelIndex& current = mList.currentIndex();
        if (!current.isValid())
        {
            mList.setCurrentIndex(mModel.index(0, 0, mModel.index(mModel.rootPath())));
        }

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
        mList.setCurrentIndex(QModelIndex());
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
            mList.setCurrentIndex(QModelIndex());
            mSearchMode = true;
            mEnterField.show();
            QDialog::keyPressEvent(event);
            return;
        }

        if (event->key() == Qt::Key_Return)
        {
            const QModelIndex& current = mList.currentIndex();
            if (!current.isValid())
            {
                return;
            }
            mEnterField.clear();
            const QString& path = mModel.filePath(current);
            mModel.setRootPath(path);
            mList.setRootIndex(mModel.index(path));
            return;
        }

        if (event->key() == Qt::Key_Backspace)
        {
            mEnterField.clear();
            QString path(mModel.rootPath());
            path.chop(path.length() - 1 - path.lastIndexOf(QDir::separator()));
            mModel.setRootPath(path);
            mList.setRootIndex(mModel.index(path));
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

        const QModelIndex& first = mModel.index(0, 0, mModel.index(mModel.rootPath()));
        if (first.isValid())
        {
            mList.setCurrentIndex(first);
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
