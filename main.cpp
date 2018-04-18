/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QApplication>
#include <QTextStream>

#include "mainwindow.h"

void printHelp()
{
    QTextStream out(stdout);
    out << QObject::tr("Simple timer - version: ") + "0.1" << endl << endl;
    out << QObject::tr("Simple countdown timer that displays time left in HH:MM format. \nClicking on the clock hides the menu and toolbar. Clicking again un-hides them.") << endl << endl;
    out << QObject::tr("Usage: ") + "timer " + QObject::tr("[options]") << endl << endl;
    out << QObject::tr("Options:") << endl;
    out << "  -f --full-screen\t" + QObject::tr("Start timer full-screen") << endl;
    out << "  -h --help\t\t" + QObject::tr("This usage info") << endl;
    out << "  -n --no-toolbar\t" + QObject::tr("Hide toolbar and menu") << endl;
    out << "  -m --maximized\t" + QObject::tr("Start maximized") << endl;
    out << "  -t=xxx --timer=xxx\t" + QObject::tr("Number of minutes to countdown. Timer starts immediately") << endl;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("AdrianTM");
    app.setApplicationName("Timer");

    if (app.arguments().contains("-h") || app.arguments().contains("--help")) {
        printHelp();
        return 0;
    }

    MainWindow w(app.arguments());
    w.show();
    return app.exec();
}
