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


#include "Headers/roomnet.h"
#include "Headers/connectionhandler.h"
#include <QtBluetooth/qtbluetooth-config.h>
#include <QtCore/qsystemdetection.h>


ConnectionHandler::ConnectionHandler(QObject *parent) : QObject(parent), m_loc()
#ifdef Q_OS_ANDROID
    , source(NULL)
#endif
{
#ifdef Q_OS_ANDROID
    {
    if (!source){
    source = QGeoPositionInfoSource::createDefaultSource(this);

    connect(source, &QGeoPositionInfoSource::errorOccurred,
                         this, &ConnectionHandler::errorOccured);
    source->startUpdates();
    }
}
#else
    m_loc = false;
#endif
    connect(&m_localDevice, &QBluetoothLocalDevice::hostModeStateChanged,
            this, &ConnectionHandler::hostModeChanged);
}

bool ConnectionHandler::alive() const
{
#if defined(QT_PLATFORM_UIKIT)
    return true;
#else
    return m_localDevice.isValid() && m_localDevice.hostMode() != QBluetoothLocalDevice::HostPoweredOff;
#endif
}

bool ConnectionHandler::requiresAddressType() const
{
#if QT_CONFIG(bluez)
    return true;
#else
    return false;
#endif
}

QString ConnectionHandler::name() const
{
    return m_localDevice.name();
}

QString ConnectionHandler::address() const
{
    return m_localDevice.address().toString();
}

void ConnectionHandler::hostModeChanged(QBluetoothLocalDevice::HostMode /*mode*/)
{
    emit deviceChanged();
}
#ifdef Q_OS_ANDROID
void ConnectionHandler::errorOccured(QGeoPositionInfoSource::Error err){
    if (err == QGeoPositionInfoSource::AccessError) {
        m_loc = true;
        emit locationChanged();
    }
    else if (err == QGeoPositionInfoSource::NoError) {
        m_loc= false;
        emit locationChanged();
    }
    else if (err == QGeoPositionInfoSource::ClosedError){
        m_loc = true;
        emit locationChanged();
    }
    else if (QGeoPositionInfoSource::UpdateTimeoutError ){
        m_loc = false;
        emit locationChanged();
    }
}

#endif

bool ConnectionHandler::loc() const
{
    return m_loc;
}
