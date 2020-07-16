#pragma once
#include "BackEndInterface.h"
#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

class FrontEndInterface : public QObject
{
	Q_OBJECT

	
	

public slots:

	void positionClicked(int rowIndex, int posIndex);
	void startGame();
	void tokenSelected(int rowIndex, int posIndex, int token);
	void makeAIMove();

private:

	QString m_loadingProgress;
	QString m_whichPlayerText = "Player: one";
	int m_blackStoneCounter = 9;
	int m_whiteStoneCounter = 9;
	int playerToken = -1;

	std::tuple<int, int>  clickPos;
	std::tuple<int, int>  tokenPos;
	std::tuple<int, int>  takeAwayPos;

	BackEndInterface backEnd;
	QObject *parentObject;

	
	void resetVarPos();
	void setStoneCount(int token);

	

public:
	FrontEndInterface(QObject* qmlObject, QObject *parent = nullptr);
	~FrontEndInterface();

};