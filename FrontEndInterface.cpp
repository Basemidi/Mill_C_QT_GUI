#include "FrontEndInterface.h"

FrontEndInterface::FrontEndInterface(QObject* qmlObject, QObject *parent)
	: QObject(parent)
{
	parentObject = qmlObject;
}

FrontEndInterface::~FrontEndInterface()
{
}

void FrontEndInterface::startGame()
{
	setStoneCount(1);
	setStoneCount(-1);

	emit setPlayerMoveInBackEnd(action(10, 10, 10, 10));
	
	QMetaObject::invokeMethod(parentObject, "setLoadingScreen");
}

void FrontEndInterface::makeAIMove(action aiAction, std::vector<action> actionList)
{
	this->actList = actionList;
	QMetaObject::invokeMethod(parentObject, "removeLoadingScreen");

	if (std::get<0>(aiAction.location) != 9) {
		QMetaObject::invokeMethod(parentObject, "removeStone",
			Q_ARG(QVariant, std::get<0>(aiAction.location)),
			Q_ARG(QVariant, std::get<1>(aiAction.location)));

	}
	else {
		if (playerToken == -1 && m_whiteStoneCounter > 0) {
			m_whiteStoneCounter--;
			setStoneCount(1);
		}
		else if (playerToken == 1 && m_blackStoneCounter > 0) {
			m_blackStoneCounter--;
			setStoneCount(-1);
		}
	}

	QMetaObject::invokeMethod(parentObject, "setStone",
		Q_ARG(QVariant, std::get<0>(aiAction.target)),
		Q_ARG(QVariant, std::get<1>(aiAction.target)),
		Q_ARG(QVariant, playerToken * -1));

	if (std::get<0>(aiAction.takeAway) != 7) {
		QMetaObject::invokeMethod(parentObject, "removeStone",
			Q_ARG(QVariant, std::get<0>(aiAction.takeAway)),
			Q_ARG(QVariant, std::get<1>(aiAction.takeAway)));
	}

	
}

void FrontEndInterface::resetVarPos()
{
	std::tuple<int, int>* clickPos = new std::tuple<int, int>();
	std::tuple<int, int>* tokenPos = new std::tuple<int, int>();
	std::tuple<int, int>* takeAwayPos = new std::tuple<int, int>();

	clickPosSet  = false;
	tokenPosSet  = false;
	takeAwayPosSet  = false;


}

void FrontEndInterface::setStoneCount(int token)
{
	if (token == -1) {
		QMetaObject::invokeMethod(parentObject, "setCounter",
			Q_ARG(QVariant, m_blackStoneCounter),
			Q_ARG(QVariant, token));
	}
	else {
		QMetaObject::invokeMethod(parentObject, "setCounter",
			Q_ARG(QVariant, m_whiteStoneCounter),
			Q_ARG(QVariant, token));
	}
	
}

void FrontEndInterface::tokenSelected(int rowIndex, int posIndex, int token)
{	
	
	if (token == playerToken) {
		tokenPos = std::make_tuple(rowIndex, posIndex);
		tokenPosSet = true;
	}
	else if (token != playerToken && tokenPosSet) {
		
		
		action act(std::get<0>(tokenPos), std::get<1>(tokenPos),
			std::get<0>(clickPos), std::get<1>(clickPos),
			rowIndex, posIndex);

		
		resetVarPos();
		
		if (std::find( actList.begin(), actList.end(), act) != actList.end()) {

			
			QMetaObject::invokeMethod(parentObject, "removeStone",
				Q_ARG(QVariant, std::get<0>(act.takeAway)),
				Q_ARG(QVariant, std::get<1>(act.takeAway)));

			QMetaObject::invokeMethod(parentObject, "removeStone",
				Q_ARG(QVariant, std::get<0>(act.location)),
				Q_ARG(QVariant, std::get<1>(act.location)));

			QMetaObject::invokeMethod(parentObject, "setStone",
				Q_ARG(QVariant, std::get<0>(act.target)),
				Q_ARG(QVariant, std::get<1>(act.target)),
				Q_ARG(QVariant, playerToken));

			emit setPlayerMoveInBackEnd(act);
			QMetaObject::invokeMethod(parentObject, "setLoadingScreen");
			
		}
	}
	else if (token != playerToken && clickPosSet) {
		
		
		action act(9, 9,
			std::get<0>(clickPos), std::get<1>(clickPos),
			rowIndex, posIndex);

		resetVarPos();
		if (std::find(actList.begin(), actList.end(), act) != actList.end()) {
			emit setPlayerMoveInBackEnd(act);

			if (playerToken == -1) {
				m_blackStoneCounter--;
				setStoneCount(-1);
			}
			else {
				m_whiteStoneCounter--;
				setStoneCount(1);
			}

			QMetaObject::invokeMethod(parentObject, "removeStone",
				Q_ARG(QVariant, std::get<0>(act.takeAway)),
				Q_ARG(QVariant, std::get<1>(act.takeAway)));

			QMetaObject::invokeMethod(parentObject, "setStone",
				Q_ARG(QVariant, std::get<0>(act.target)),
				Q_ARG(QVariant, std::get<1>(act.target)),
				Q_ARG(QVariant, playerToken));

			QMetaObject::invokeMethod(parentObject, "setLoadingScreen");
		}
	}
}



void FrontEndInterface::positionClicked(int ringIndex, int posIndex) {
	
	action simpleact(9, 9, ringIndex, posIndex);
	
	if (std::find(actList.begin(), actList.end(), simpleact) != actList.end() && checkFormultipleActions(simpleact, actList)) {
		
		if (playerToken == -1) {
			m_blackStoneCounter--;
			setStoneCount(-1);
		}
		else {
			m_whiteStoneCounter--;
			setStoneCount(1);
		}
		
		emit setPlayerMoveInBackEnd(simpleact);
		QMetaObject::invokeMethod(parentObject, "setStone", 
			Q_ARG(QVariant, std::get<0>(simpleact.target)), 
			Q_ARG(QVariant, std::get<1>(simpleact.target)), 
			Q_ARG(QVariant, playerToken));


		resetVarPos();
		
		QMetaObject::invokeMethod(parentObject, "setLoadingScreen");

	}
	else if (tokenPosSet) {
		simpleact.location = tokenPos;
		
		if (std::find(actList.begin(), actList.end(), simpleact) != actList.end() && checkFormultipleActions(simpleact, actList)) {
			
			resetVarPos();
			emit setPlayerMoveInBackEnd(simpleact);

			QMetaObject::invokeMethod(parentObject, "removeStone",
				Q_ARG(QVariant, std::get<0>(simpleact.location)),
				Q_ARG(QVariant, std::get<1>(simpleact.location)));

			QMetaObject::invokeMethod(parentObject, "setStone", 
				Q_ARG(QVariant, std::get<0>(simpleact.target)),
				Q_ARG(QVariant, std::get<1>(simpleact.target)),
				Q_ARG(QVariant, playerToken));

			QMetaObject::invokeMethod(parentObject, "setLoadingScreen");
		}
		else {
			clickPos = std::make_tuple(ringIndex, posIndex);
			clickPosSet = true;
		}
	}
	else {
		clickPos = std::make_tuple(ringIndex, posIndex);
		clickPosSet = true;
	}
}

bool FrontEndInterface::checkFormultipleActions(action act, vector<action> actlist) {

	for (int i = 0; i < static_cast<int>(actlist.size()); i++) {
		if (actlist[i].location == act.location && actlist[i].target == act.target && std::get<0>(actlist[i].takeAway) != 7) {
			return false;
		}
	}

	return true;
}