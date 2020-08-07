// Copyright(c) 2017-2019 Alejandro Sirgo Rica & Contributors
//              2020, KylinSoft Co., Ltd.
// This file is part of Kylin-Screenshot.
//
//     Kylin-Screenshot is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     Kylin-Screenshot is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with Kylin-Screenshot.  If not, see <http://www.gnu.org/licenses/

#pragma once

#include "src/cli/commandlineparser.h"
#include <QDBusConnection>
#include <QObject>

class DBusUtils : public QObject {
    Q_OBJECT
public:
    explicit DBusUtils(QObject *parent = nullptr);

    void connectPrintCapture(QDBusConnection &session, uint id);
    void checkDBusConnection(const QDBusConnection &connection);

public slots:
    void captureTaken(uint id, QByteArray rawImage);
    void captureFailed(uint id);

private:

    uint m_id;
};
