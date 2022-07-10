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

#ifndef BLUETOOTHBASECLASS_H
#define BLUETOOTHBASECLASS_H

#include <QObject>

class BluetoothBaseClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString error READ error WRITE setError NOTIFY errorChanged)
    Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged)

public:
    explicit BluetoothBaseClass(QObject *parent = nullptr);

    QString error() const;
    void setError(const QString& error);

    QString info() const;
    void setInfo(const QString& info);

    void clearMessages();

signals:
    void errorChanged();
    void infoChanged();

private:
    QString m_error;
    QString m_info;
};

#endif // BLUETOOTHBASECLASS_H
