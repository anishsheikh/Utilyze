/*
 * This file is part of the Utilyze distribution (https://github.com/anishsheikh/Utilyze).
 * Copyright (c) 2022 Anish Sheikh.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QObject>
#include <QBluetoothLocalDevice>

#ifdef Q_OS_ANDROID
#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>
#include <QGeoCoordinate>
#include<QDebug>
#endif


class ConnectionHandler : public QObject
{
    Q_PROPERTY(bool alive READ alive NOTIFY deviceChanged)
    Q_PROPERTY(QString name READ name NOTIFY deviceChanged)
    Q_PROPERTY(QString address READ address NOTIFY deviceChanged)
    Q_PROPERTY(bool requiresAddressType READ requiresAddressType CONSTANT)
    Q_PROPERTY(bool loc READ loc NOTIFY locationChanged)

    Q_OBJECT
public:
    explicit ConnectionHandler(QObject *parent = nullptr);
    bool loc() const;
    bool alive() const;
    bool requiresAddressType() const;
    QString name() const;
    QString address() const;

signals:
    void deviceChanged();
    void locationChanged();

private slots:
    void hostModeChanged(QBluetoothLocalDevice::HostMode mode);
#ifdef Q_OS_ANDROID
    void errorOccured(QGeoPositionInfoSource::Error err);
#endif
private:
    QBluetoothLocalDevice m_localDevice;
    bool m_loc;
#ifdef Q_OS_ANDROID
    QGeoPositionInfoSource *source;
#endif
};

#endif // CONNECTIONHANDLER_H
