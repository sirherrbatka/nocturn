/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright 2014  Marek Kochanowicz <sirherrbatka@gmail.com>
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

#include "streamsmenuwrapper.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <utility>

#include <QString>

#include "settingsmanager.h"
#include "./maincontroler.h"

NewStreamView::NewStreamView() :
mStreams(SettingsManager::getSettingsManager()->getStreams())
{
    setupUi(this);
    nameLineEdit->setDisabled(true);
    urlLineEdit->setDisabled(true);
    setWindowTitle("Add new stream");
    for (auto it(mStreams.begin()); it != mStreams.end(); ++it)
    {
        listWidget->addItem (it->first);
    }
    connect(newButton, SIGNAL(clicked()), this, SLOT(addNew()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteCurrent()));
    connect(mStoreButton, SIGNAL(clicked()), this, SLOT(storeStreams()));
    connect(nameLineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(storeName(const QString &)));
    connect(urlLineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(storeUrl(const QString &)));
    connect(listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(updateEdits()));
}

void NewStreamView::deleteCurrent()
{
    int row = listWidget->currentRow();
    mStreams.erase(mStreams.begin() + row);
    listWidget->clear();

    for (auto it(mStreams.begin()); it != mStreams.end(); ++it)
    {
        listWidget->addItem (it->first);
    }
    listWidget->setCurrentRow(row);
    updateEdits();
}

void NewStreamView::addNew()
{
    int row = listWidget->currentRow() + 1;
    mStreams.push_back(std::make_pair("", QUrl()));

    listWidget->addItem ("New Stream");
    listWidget->setCurrentRow(row);
}

void NewStreamView::storeStreams()
{
    SettingsManager::getSettingsManager()->replaceAudioStreams(mStreams);
}

void NewStreamView::updateEdits()
{
    const int row = listWidget->currentRow();
    if (row == -1 or listWidget->count() == 0)
    {
        nameLineEdit->setDisabled(true);
        urlLineEdit->setDisabled(true);
    } else {
        nameLineEdit->setDisabled(false);
        urlLineEdit->setDisabled(false);
        nameLineEdit->setText(mStreams[row].first);
        urlLineEdit->setText(mStreams[row].second.path());
    }
}

void NewStreamView::storeName(const QString & text)
{
    int row = listWidget->currentRow();
    listWidget->currentItem()->setText(text);
    mStreams.at(row).first = text;
}

void NewStreamView::storeUrl(const QString & text)
{
    int row = listWidget->currentRow();
    QUrl& url(mStreams.at(row).second);
    url = QUrl(text);
}

QUrlProxy::QUrlProxy(const QUrl& url) :
mUrl(url)
{
    
}

void QUrlProxy::triggered()
{
    emit triggered(mUrl);
}

StreamsMenuWrapper::StreamsMenuWrapper()
{
}

void StreamsMenuWrapper::storeMenu(QMenu* menu)
{
  mMenu = menu;
  //can't be done in the constructor
  connect (SettingsManager::getSettingsManager(), SIGNAL(streamsChanged()), this, SLOT(rebuildMenu()));
  rebuildMenu();
}

void StreamsMenuWrapper::rebuildMenu()
{
    const std::vector<std::pair<QString, QUrl>>& streams(SettingsManager::getSettingsManager()->getStreams());
    mMenu->clear();

    connect(mMenu->addAction("Streams Configuration"), SIGNAL(triggered(bool)), this, SLOT(showStreamEdit()));

    mProxyVector.erase(mProxyVector.begin(), mProxyVector.end());
    for (auto it(streams.begin()); it != streams.end(); ++it)
    {
        std::unique_ptr<QUrlProxy> proxy(new QUrlProxy(it->second));
        mProxyVector.push_back(std::move(proxy));

        connect(mMenu->addAction(it->first), SIGNAL(triggered(bool)),
                mProxyVector.rbegin()->get(), SLOT(triggered()));
        connect(mProxyVector.rbegin()->get(), SIGNAL(triggered(const QUrl&)), this, SLOT(triggered(const QUrl&)));
    }
}

void StreamsMenuWrapper::triggered(const QUrl& url)
{
    MainControler::getMainControler()->playStream(url);
}

void StreamsMenuWrapper::showStreamEdit()
{
    NewStreamView conf;
    conf.exec();
}