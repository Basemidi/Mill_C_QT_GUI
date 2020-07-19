#include "BackEndInterface.h"


BackEndInterface::BackEndInterface()
{
}

BackEndInterface::~BackEndInterface()
{
}

action BackEndInterface::getAiMove()
{
	action act = AIPlayer.threaded_thinking(board);
	qDebug() << "Location |" << std::get<0>(act.location) << ":" << std::get<1>(act.location);
	qDebug() << "Target |" << std::get<0>(act.target) << ":" << std::get<1>(act.target);
	qDebug() << "TakeAway |" << std::get<0>(act.takeAway) << ":" << std::get<1>(act.takeAway);
	qDebug() << "----------------------------------------------";
	board.makeMove(act);
	return act;
}

void BackEndInterface::setPlayerMove(action act)
{
	qDebug() << "Location |"<< std::get<0>(act.location) << ":" << std::get<1>(act.location);
	qDebug() << "Target |"<< std::get<0>(act.target) << ":" << std::get<1>(act.target);
	qDebug() << "TakeAway |" << std::get<0>(act.takeAway) << ":" << std::get<1>(act.takeAway);
	qDebug() << "----------------------------------------------";
	board.makeMove(act);
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


