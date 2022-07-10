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


#include "Headers/bluetoothbaseclass.h"

BluetoothBaseClass::BluetoothBaseClass(QObject *parent) : QObject(parent)
{
}

QString BluetoothBaseClass::error() const
{
    return m_error;
}

QString BluetoothBaseClass::info() const
{
    return m_info;
}

void BluetoothBaseClass::setError(const QString &error)
{
    if (m_error != error) {
        m_error = error;
        emit errorChanged();
    }
}

void BluetoothBaseClass::setInfo(const QString &info)
{
    if (m_info != info) {
        m_info = info;
        emit infoChanged();
    }
}

void BluetoothBaseClass::clearMessages()
{
    setInfo("");
    setError("");
}
