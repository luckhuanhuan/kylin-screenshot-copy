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

#include "src/tools/abstractactiontool.h"

class RedoTool : public AbstractActionTool {
    Q_OBJECT
public:
    explicit RedoTool(QObject *parent = nullptr);

    bool closeOnButtonPressed() const;

    QIcon icon(const QColor &background, bool inEditor) const override;
    QString name() const override;
    static QString nameID();
    QString description() const override;

    CaptureTool* copy(QObject *parent = nullptr) override;

public slots:
    void pressed(const CaptureContext &context) override;

};
