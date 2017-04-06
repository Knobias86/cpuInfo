/*! \mainpage CPU Information
 *
 * This program is a visual representation of the file '/proc/cpuinfo'. It uses the model/view approach
 * of Qt. The data will be collected/processed in the c++ part and stored in a model. The QML part
 * represents the graphical view of the model data.
 *
 * \section req_sec Requirements
 *
 * - Qt 5.7.1 for QtQuick SwipeView
 * - Unix system to read the proc file
 *
 * \section install_sec Installation
 *
 * -# Install the qt package from https://www.qt.io/download-open-source/
 * -# Select at least the qt version 5.7 in the installation process
 * -# Finish the installation process
 *
 * \subsection open_subsec Start the application
 * -# Inside the QtCreator open this project (file->open project).
 * -# Select in the open dialog this file: cpuInfo.pro
 * -# Now use the shortcut STRG+R to start the application
 *
 * \section handling_sec Usage
 *
 * The application is divided in two views:
 * - A graphical Bar for every logical processor
 * - A brief summary of relevant CPU information
 *
 * \subsection change_subsec Change the view
 *
 * Swipe horizontally on the screen.
 *
 * \section document_sec Documentation
 *
 * Take a look at the installation webpage of Doxygen.
 * They have a nice step-by-step guide: http://www.stack.nl/~dimitri/doxygen/manual/install.html
 *
 * This command generates the documentation:
 * doxygen cpuInfo_manual
 *
 * After the generation there will be a HTML directory in this folder. Open the index.html for a detailed documentation of this project.
 *
 * This documentation is created by Doxygen.
 *
 * \todo Switch to qbs to create different datamodels for several devices
 */
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlPropertyMap>
#include <QQmlContext>

#include "datamodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    DataModel datamodel(&datamodel);
    engine.rootContext()->setContextProperty("cpuData",
                                             &datamodel);
    engine.load(QUrl(QStringLiteral("qrc:/CpuInfo.qml")));

    return app.exec();
}
