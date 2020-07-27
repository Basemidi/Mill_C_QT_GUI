#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "FrontEndInterface.h"


int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qRegisterMetaType<action>();
    qRegisterMetaType<std::vector<action>>();
    
    QThread *AIWorkingThread = new QThread();
    BackEndInterface backend;
    backend.moveToThread(AIWorkingThread);
    AIWorkingThread->start();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* item = engine.rootObjects().value(0);
    FrontEndInterface front(item);
    
    QObject::connect(item, SIGNAL(positionSignal(int, int)), &front, SLOT(positionClicked(int, int)));
    QObject::connect(item, SIGNAL(startGame()), &front, SLOT(startGame()));
    QObject::connect(item, SIGNAL(tokenSelected(int, int, int)), &front, SLOT(tokenSelected(int, int, int)));

    QObject::connect(&backend, SIGNAL(sendMoveToFront(action, std::vector<action>)), &front, SLOT(makeAIMove(action, std::vector<action>)));
    QObject::connect(&front, SIGNAL(setPlayerMoveInBackEnd(action)), &backend, SLOT(setPlayerMove(action)));

    

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}