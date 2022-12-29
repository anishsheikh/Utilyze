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


#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include "bluetoothbaseclass.h"

#include <QDateTime>
#include <QList>
#include <QTimer>

#include <QLowEnergyController>
#include <QLowEnergyService>

class DeviceInfo;

class DeviceHandler : public BluetoothBaseClass
{
    Q_OBJECT
    QUuid BleApplianceServiceid = QBluetoothUuid(QStringLiteral("YOUR-UUID"));
    QUuid BleApplianceInputid = QBluetoothUuid(QStringLiteral("YOUR-UUID"));
    QUuid BleApplianceOutputid = QBluetoothUuid(QStringLiteral("YOUR-UUID"));
    Q_PROPERTY(bool ready READ ready NOTIFY connectionChanged)
    Q_PROPERTY(AddressType addressType READ addressType WRITE setAddressType)

public:
    enum class AddressType {
        PublicAddress,
        RandomAddress
    };
    Q_ENUM(AddressType)

    DeviceHandler(QObject *parent = nullptr);

    void setDevice(DeviceInfo *device);
    void setAddressType(AddressType type);
    AddressType addressType() const;
    bool ready() const;

signals:
    void connectionChanged();
    void aliveChanged();
    void statsChanged();
    void dataReceived(const QByteArray &data);

public slots:
    void disconnectService();
    void write(const QByteArray &swn);





private:
    //QLowEnergyController
    void serviceDiscovered(const QBluetoothUuid &);
    void serviceScanDone();


    //QLowEnergyService
    void onCharacteristicRead(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void serviceStateChanged(QLowEnergyService::ServiceState s);

private slots:
    void read();
    void inforead(const QByteArray &infr);
private:

    QLowEnergyController *m_control = nullptr;
    QLowEnergyService *m_service = nullptr;
    QLowEnergyDescriptor m_notificationDesc;
    DeviceInfo *m_currentDevice = nullptr;

    bool m_foundRoomNetService;


    QLowEnergyController::RemoteAddressType m_addressType = QLowEnergyController::PublicAddress;

#ifdef SIMULATOR
    QTimer m_demoTimer;
#endif
};

#endif // DEVICEHANDLER_H
