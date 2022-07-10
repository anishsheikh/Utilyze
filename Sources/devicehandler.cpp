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
#include "Headers/devicehandler.h"
#include "Headers/deviceinfo.h"
#include <QtEndian>
#include <QRandomGenerator>
#include <qdebug.h>

DeviceHandler::DeviceHandler(QObject *parent) :
    BluetoothBaseClass(parent),
    m_foundRoomNetService(false)
{

}



void DeviceHandler::setAddressType(AddressType type)
{
    switch (type) {
    case DeviceHandler::AddressType::PublicAddress:
        m_addressType = QLowEnergyController::PublicAddress;
        break;
    case DeviceHandler::AddressType::RandomAddress:
        m_addressType = QLowEnergyController::RandomAddress;
        break;
    }
}

DeviceHandler::AddressType DeviceHandler::addressType() const
{
    if (m_addressType == QLowEnergyController::RandomAddress)
        return DeviceHandler::AddressType::RandomAddress;

    return DeviceHandler::AddressType::PublicAddress;
}

void DeviceHandler::setDevice(DeviceInfo *device)
{
    clearMessages();
    m_currentDevice = device;
    // Disconnect and delete old connection
    if (m_control) {
        m_control->disconnectFromDevice();
        delete m_control;
        m_control = nullptr;
    }

    // Create new controller and connect it if device available
    if (m_currentDevice) {

        // Make connections
        //! [Connect-Signals-1]
        m_control = QLowEnergyController::createCentral(m_currentDevice->getDevice(), this);
        //! [Connect-Signals-1]
        m_control->setRemoteAddressType(m_addressType);
        //! [Connect-Signals-2]
        connect(m_control, &QLowEnergyController::serviceDiscovered,
                this, &DeviceHandler::serviceDiscovered);
        connect(m_control, &QLowEnergyController::discoveryFinished,
                this, &DeviceHandler::serviceScanDone);

        connect(m_control, &QLowEnergyController::errorOccurred, this,
                [this](QLowEnergyController::Error error) {
                    Q_UNUSED(error);
                    setError("Can't Connect, Retry");
                });
        connect(m_control, &QLowEnergyController::connected, this, [this]() {
            setInfo("Connected, Searching RoomNet");
            m_control->discoverServices();
        });
        connect(m_control, &QLowEnergyController::disconnected, this, [this]() {
            setError("Bluetooth disconnected");
        });

        // Connect
        m_control->connectToDevice();
        //! [Connect-Signals-2]
    }
}

void DeviceHandler::write(QByteArray &swn)
{
        if(m_service != nullptr && m_foundRoomNetService == true){
        const QLowEnergyCharacteristic input = m_service->characteristic(QBluetoothUuid(DeviceHandler::BleApplianceInputid));
        m_service->writeCharacteristic(input, QByteArray::fromHex(swn));
        DeviceHandler::read();
        }
        else {
            setInfo("Unknown Error");
        }
}

void DeviceHandler::read()
{
    connect(m_service, &QLowEnergyService::characteristicRead,
               this, &DeviceHandler::onCharacteristicRead);
    const QLowEnergyCharacteristic output = m_service->characteristic(QBluetoothUuid(DeviceHandler::BleApplianceOutputid));
    m_service->readCharacteristic(output);
}

void DeviceHandler::onCharacteristicRead(const QLowEnergyCharacteristic &c,
                                        const QByteArray &value){
    Q_UNUSED(c)
    emit dataReceived(value);
    DeviceHandler::inforead(value);
}

void DeviceHandler::inforead(const QByteArray &infr) {
    if (infr == "youroutput") {
        setInfo("Switched Number 1");
    }
    else if (infr == "youroutput") {
        setInfo("Switched Number 2");
    }
    else if (infr == "youroutput") {
        setInfo("Switched Number 3");
    }
    else if (infr == "youroutput") {
        setInfo("Switched Number 4");
    }
    else if (infr == "youroutput") {
        setInfo("Switched Number 5");
    }
    else if (infr == "youroutput") {
        setInfo("Switched Number 6");
    }
    else if (infr == "youroutput") {
        setInfo("Switched Number 7");
    }
    else {
        setInfo("Switched Number 8");
    }

}



//! [Filter HeartRate service 1]
void DeviceHandler::serviceDiscovered(const QBluetoothUuid &gatt)
{
    if (gatt == QBluetoothUuid(DeviceHandler::BleApplianceServiceid)) {
        setInfo("Getting Ready..");
        m_foundRoomNetService = true;
    }
}
//! [Filter HeartRate service 1]

void DeviceHandler::serviceScanDone()
{
    setInfo("Found Nearby Devices..");

    // Delete old service if available
    if (m_service) {
        delete m_service;
        m_service = nullptr;
    }

//! [Filter HeartRate service 2]
    // If heartRateService found, create new service
    if (m_foundRoomNetService)
        m_service = m_control->createServiceObject(QBluetoothUuid(DeviceHandler::BleApplianceServiceid), this);

    if (m_service) {
        connect(m_service, &QLowEnergyService::stateChanged, this, &DeviceHandler::serviceStateChanged);
        m_service->discoverDetails();
    } else {
        setError("Not a RoomNet Device");
    }
}
void DeviceHandler::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    switch (s) {
    case QLowEnergyService::RemoteServiceDiscovering:
        setInfo(tr("Getting Ready.."));
        break;
    case QLowEnergyService::RemoteServiceDiscovered:
    {
        setInfo(tr("Ready to Switch..."));

        const QLowEnergyCharacteristic hrChar = m_service->characteristic(QBluetoothUuid(DeviceHandler::BleApplianceInputid));
        if (!hrChar.isValid()) {
            setError("Not a RoomNet Device");
            break;
        }
    }
    default:
        //nothing for now
        break;
    }
    emit connectionChanged();
}
void DeviceHandler::disconnectService()
{


        if (m_control != nullptr) {
            m_control->disconnectFromDevice();
            m_foundRoomNetService = false;
            delete m_service;
            m_service = nullptr;
        }
        else {
            m_foundRoomNetService = false;
            setInfo("Already Disconnected");
        }

}

bool DeviceHandler::ready() const
{
    if (m_service)
        return m_service->state() == QLowEnergyService::RemoteServiceDiscovered;

    return false;
}
