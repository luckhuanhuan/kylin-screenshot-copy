// Copyright(c) 2017-2019 Alejandro Sirgo Rica & Contributors
//              2020 KylinSoft Co., Ltd.
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

#include "applaunchertool.h"
#include "applauncherwidget.h"

AppLauncher::AppLauncher(QObject *parent) : AbstractActionTool(parent) {

}

bool AppLauncher::closeOnButtonPressed() const {
    return true;
}

QIcon AppLauncher::icon(const QColor &background, bool inEditor) const {
    //Q_UNUSED(inEditor);
    //return QIcon(iconPath(background) + "open_with.svg");
    Q_UNUSED(background);
    return inEditor ?  QIcon(QStringLiteral(":/img/material/black/") + "open_with.svg") :
                      QIcon(QStringLiteral(":/img/material/white/") + "open_with.svg");
}
QString AppLauncher::name() const {
    return tr("App Launcher");
}

QString AppLauncher::nameID() {
    return QLatin1String("");
}

QString AppLauncher::description() const {
    return tr("Choose an app to open the capture");
}

QWidget* AppLauncher::widget() {
    return new AppLauncherWidget(capture);
}

CaptureTool* AppLauncher::copy(QObject *parent) {
    return new AppLauncher(parent);
}

void AppLauncher::pressed(const CaptureContext &context) {
    capture = context.selectedScreenshotArea();
    emit requestAction(REQ_CAPTURE_DONE_OK);
    emit requestAction(REQ_ADD_EXTERNAL_WIDGETS);
}
