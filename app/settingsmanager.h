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

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
class QUrl;
class QVariant;

class SettingsManager : public QObject
{
  Q_OBJECT
    bool mRepeatMode{true};
    std::vector<std::pair<QString, QUrl>> mAudioStreams;

    //other members
    QSettings mSettings;
    static SettingsManager* mThisPointer;

public:
    SettingsManager();
    static SettingsManager* getSettingsManager();

    QVariant getSetting(const QString& key) const;

    template <typename T>
    void setValue(const QString& key, T value)
    {
      mSettings.setValue(key, value);
      emit ConfigurationUpdated();
    }

    const std::vector<std::pair<QString, QUrl>> getStreams() const;
    const bool getRepeatMode() const;


public slots:
    void replaceAudioStreams(const std::vector<std::pair<QString, QUrl>>& streams);
    void setRepeatMode();

signals:
  void ConfigurationUpdated();
  void streamsChanged();
};

#endif // SETTINGSMANAGER_H
