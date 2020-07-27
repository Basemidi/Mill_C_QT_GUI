#pragma once
#include "Bot_Brain.h"
#include "Mill_Board.h"
#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QThread>

class BackEndInterface : public QObject
{
	Q_OBJECT


public slots:
	void setPlayerMove(action act);
	

signals:
	void sendMoveToFront(action ai, std::vector<action>actList);

private:
	Mill_Board board;
	Bot_Brain AIPlayer;


public:
	BackEndInterface(QObject* parent = nullptr);
	~BackEndInterface();

	action getAiMove();
	void compAIMove();
	int whichPlayer();
	int getGamePhase();
	std::vector<action> getActions();
	
};
