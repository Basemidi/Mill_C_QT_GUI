#pragma once
#include "Bot_Brain.h"
#include "Mill_Board.h"
#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

class BackEndInterface : public QObject
{
	Q_OBJECT

private:
	Mill_Board board;
	Bot_Brain AIPlayer;

	

public:
	BackEndInterface();
	~BackEndInterface();

	action getAiMove();
	void setPlayerMove(action act);
	int whichPlayer();
	int getGamePhase();
	std::vector<action> getActions();
	
};
