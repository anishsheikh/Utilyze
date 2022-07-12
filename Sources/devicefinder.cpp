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


#include "Headers/devicefinder.h"
#include "Headers/devicehandler.h"
#include "Headers/deviceinfo.h"

DeviceFinder::DeviceFinder(DeviceHandler *handler, QObject *parent):
    BluetoothBaseClass(parent),
    m_deviceHandler(handler),
    m_ready(true),
    not_found(false)
{
    //! [devicediscovery-1]
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000);

    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &DeviceFinder::addDevice);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred, this,
            &DeviceFinder::scanError);

    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &DeviceFinder::scanFinished);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled, this, &DeviceFinder::scanFinished);
    //! [devicediscovery-1]
}

DeviceFinder::~DeviceFinder()
{
    qDeleteAll(m_devices);
    m_devices.clear();
}

void DeviceFinder::startSearch()
{
    clearMessages();
    m_deviceHandler->setDevice(nullptr);
    qDeleteAll(m_devices);
    m_devices.clear();
    m_ready = false;
    emit devicesChanged();
    emit stateChanged();


    //! [devicediscovery-2]
    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    //! [devicediscovery-2]
    emit scanningChanged();
    setInfo(tr("Finding RoomNet..."));
}

//! [devicediscovery-3]
void DeviceFinder::addDevice(const QBluetoothDeviceInfo &device)
{
    // If device is LowEnergy-device, add it to the list
    if (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        m_devices.append(new DeviceInfo(device));
        setInfo(tr("Found Nearby Devices.. Finding More..."));
        not_found = false;
        emit notFoundChanged();
        emit devicesChanged();
    }
    //...
}
//! [devicediscovery-4]

void DeviceFinder::scanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
        setError(tr("The Bluetooth adaptor is powered off."));
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
        setError(tr("Writing or reading from the device resulted in an error."));
    else if (error == QBluetoothDeviceDiscoveryAgent::LocationServiceTurnedOffError)
        setError(tr("Check if Location is Enabled."));
    else
        setError(tr("Unknown Error"));
}

bool DeviceFinder::notfound(){
    return not_found;

}

void DeviceFinder::scanFinished()
{

    if (m_devices.isEmpty()){
        setError(tr("No Bluetooth devices found."));
        not_found = true;
        emit notFoundChanged();
    }
    else {
        setInfo(tr("Scanning done."));
        not_found = false;
        emit notFoundChanged();
    }

    emit scanningChanged();
    emit devicesChanged();
}

void DeviceFinder::connectToService(const QString &address)
{
    m_deviceDiscoveryAgent->stop();

    DeviceInfo *currentDevice = nullptr;
    for (QObject *entry : qAsConst(m_devices)) {
        auto device = qobject_cast<DeviceInfo *>(entry);
        if (device && device->getAddress() == address ) {
            currentDevice = device;
            break;
        }
        else {
            setInfo("Search Again and Connect");
        }
    }

    if (currentDevice) {
        m_deviceHandler->setDevice(currentDevice);
    }
    else {
        setInfo("Search Again and Connect");
    }
}

bool DeviceFinder::scanning() const
{
    return m_deviceDiscoveryAgent->isActive();
}

bool DeviceFinder::ready() {
    return m_ready;
}

QVariant DeviceFinder::devices()
{
    return QVariant::fromValue(m_devices);
}
