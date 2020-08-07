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
//     along with Kylin-Screenshot.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <QWidget>

class QTimer;

class NotifierBox : public QWidget {
    Q_OBJECT
public:
    explicit NotifierBox(QWidget *parent = nullptr);

protected:
    virtual void enterEvent(QEvent *);
    virtual void paintEvent(QPaintEvent *);

public slots:
    void showMessage(const QString &msg);
    void showColor(const QColor &color);

private:
    QTimer *m_timer;
    QString m_message;
    QColor m_bgColor;
    QColor m_foregroundColor;
};
