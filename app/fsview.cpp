#include "./fsview.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QRegExp>

#include "settingsmanager.h"

FSView::FSView() :
mList(this),
mEnterField(this),
mModel(this)
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
                     QDir::AllDirs);
    mList.setModel(&mModel);
    mList.setUniformItemSizes(true);
    connect(&mEnterField, SIGNAL(textChanged(QString)), this, SLOT(createMatching(QString)));
    QVBoxLayout* layout = new QVBoxLayout(this);
    mList.setFocusPolicy(Qt::NoFocus);
    mEnterField.setFocusPolicy(Qt::NoFocus);
    mEnterField.hide();
    layout->addWidget(&mList, 0);
    layout->addWidget(&mEnterField, 1);
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
        return;
    }
    if (mSearchText.isEmpty())
    {
        broadMatching(string);
        return;
    }
    QRegExp forwardPattern('^' + mSearchText + ".*", Qt::CaseInsensitive);
    if (string.contains(forwardPattern))
    {
        narrowMatching(string);
    } else {
        broadMatching(string);
    }
}

void FSView::focusNextMatching()
{

}

void FSView::keyPressEvent(QKeyEvent* event)
{
    if (mSearchMode)
    {
        if (event->key() == Qt::Key_Return)
        {
            mSearchMode = false;
            mEnterField.hide();
        } else {
            if (event->text().isEmpty())
            {
                QDialog::keyPressEvent(event);
                return;
            }
            mSearchText = mEnterField.text();
            QApplication::sendEvent(&mEnterField, event);
            QDialog::keyPressEvent(event);
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
    }
}

void FSView::narrowMatching(const QString& string)
{

}

void FSView::modelDirectoryLoaded(const QString& string)
{
    mList.setRootIndex(mModel.index(string));
}
