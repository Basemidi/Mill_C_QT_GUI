#include "BackEndInterface.h"


BackEndInterface::BackEndInterface(QObject* parent)
{
}

BackEndInterface::~BackEndInterface()
{
}

action BackEndInterface::getAiMove()
{
	action act = AIPlayer.think(board);
	qDebug() << "Location |" << std::get<0>(act.location) << ":" << std::get<1>(act.location);
	qDebug() << "Target |" << std::get<0>(act.target) << ":" << std::get<1>(act.target);
	qDebug() << "TakeAway |" << std::get<0>(act.takeAway) << ":" << std::get<1>(act.takeAway);
	qDebug() << "----------------------------------------------";
	board.makeMove(act);
	return act;
}

void BackEndInterface::compAIMove() {

	action act = AIPlayer.think(board);
	qDebug() << "Location |" << std::get<0>(act.location) << ":" << std::get<1>(act.location);
	qDebug() << "Target |" << std::get<0>(act.target) << ":" << std::get<1>(act.target);
	qDebug() << "TakeAway |" << std::get<0>(act.takeAway) << ":" << std::get<1>(act.takeAway);
	qDebug() << "----------------------------------------------";
	board.makeMove(act);
	std::vector<action> actiList = board.possibleActions();

	emit sendMoveToFront(act, actiList);
}

void BackEndInterface::setPlayerMove(action act)
{
	if (std::get<0>(act.location) != 10) {
		qDebug() << "Location |" << std::get<0>(act.location) << ":" << std::get<1>(act.location);
		qDebug() << "Target |" << std::get<0>(act.target) << ":" << std::get<1>(act.target);
		qDebug() << "TakeAway |" << std::get<0>(act.takeAway) << ":" << std::get<1>(act.takeAway);
		qDebug() << "----------------------------------------------";
		board.makeMove(act);
	}
	
	compAIMove();
}

int BackEndInterface::whichPlayer()
{
	return board.getactivePlayer();
}

int BackEndInterface::getGamePhase()
{
	return board.getGamePhase();
}

std::vector<action> BackEndInterface::getActions()
{
	return board.possibleActions();
}


