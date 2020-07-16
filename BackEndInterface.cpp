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
	board.makeMove(act);
	return act;
}

void BackEndInterface::setPlayerMove(action act)
{
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


