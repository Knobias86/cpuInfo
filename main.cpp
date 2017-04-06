/*! \mainpage CPU Information
 *
 * This program is a visual representation of the file '/proc/cpuinfo'. It uses the model/view approach
 * of Qt. The data will be collected/processed in the c++ part and stored in a model. The QML part
 * represents the graphhical view of the model data.
 *
 * \section req_sec Requirements
 *
 * - Qt 5.7.1 for QtQuick SwipeView
 * - Unix system to read the proc file
 *
 * \section  install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * \section  handling_sec Usage
 *
 * The application is divided in two views:
 * - A graphical Bar for every logical processor
 * - A brief summary of relevant cpu information
 *
 * \subsection change_subsec Change the view
 *
 * Swipe horicontally on the screen.
 *
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
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
