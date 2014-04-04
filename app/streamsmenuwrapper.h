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

#ifndef STREAMSMENUWRAPPER_H
#define STREAMSMENUWRAPPER_H
#include <memory>
#include <vector>

#include <QUrl>
#include <QDialog>
#include <QMenuBar>

#include "ui_newstreamform.h"

class NewStreamView : public QDialog, public Ui_NewStreamWindow
{
    Q_OBJECT

    std::vector<std::pair<QString, QUrl>> mStreams;
public:
    NewStreamView();

private slots:
    void addNew();

    void deleteCurrent();

    void storeStreams();

    void updateEdits();

    void storeName(const QString & text);

    void storeUrl(const QString & text);
};

class QUrlProxy : public QObject
{
    Q_OBJECT

    const QUrl mUrl;
public:
    QUrlProxy(const QUrl& url);

public slots:
    void triggered();

signals:
    void triggered(const QUrl& url);
};

class StreamsMenuWrapper : public QObject
{
    Q_OBJECT

    std::vector<std::unique_ptr<QUrlProxy>> mProxyVector;
    QMenu* mMenu{nullptr};

public:
  StreamsMenuWrapper();
  void storeMenu(QMenu* menu);

private slots:
    void rebuildMenu();
    void triggered(const QUrl& url);
    void showStreamEdit();
};

#endif // STREAMSMENUWRAPPER_H
