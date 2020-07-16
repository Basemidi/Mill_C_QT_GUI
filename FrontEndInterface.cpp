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

	action act = backEnd.getAiMove();
	QMetaObject::invokeMethod(parentObject, "setStone", Q_ARG(QVariant, std::get<0>(act.target)), Q_ARG(QVariant, std::get<0>(act.target)), Q_ARG(QVariant, 1));

	if (playerToken == -1) {
		m_whiteStoneCounter--;
		setStoneCount(1);
	}
	else {
		m_blackStoneCounter--;
		setStoneCount(-1);
	}
}

void FrontEndInterface::makeAIMove()
{
	action aiAction = backEnd.getAiMove();

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
	
	
	if (token == playerToken && std::get<0>(tokenPos) == NULL) {
		tokenPos = std::make_tuple(rowIndex, posIndex);
	}
	else if (token != playerToken && std::get<0>(tokenPos) != NULL) {

		takeAwayPos == std::make_tuple(rowIndex, posIndex);
		action act(std::get<0>(tokenPos), std::get<1>(tokenPos),
			std::get<0>(clickPos), std::get<1>(clickPos),
			std::get<0>(takeAwayPos), std::get<1>(takeAwayPos));

		std::vector<action> actList = backEnd.getActions();
		
		if (std::find( actList.begin(), actList.end(), act) != actList.end()) {

			resetVarPos();

			backEnd.setPlayerMove(act);

			makeAIMove();
			
		}
	}
}



void FrontEndInterface::positionClicked(int ringIndex, int posIndex) {

	qDebug() << ringIndex << "||" << posIndex;
	vector<action> actionList = backEnd.getActions();

	action simpleact(9, 9, ringIndex, posIndex);
	
	if (std::find(actionList.begin(), actionList.end(), simpleact) != actionList.end()) {
		qDebug() << "Works";
		if (playerToken == -1) {
			m_blackStoneCounter--;
			setStoneCount(-1);
		}
		else {
			m_whiteStoneCounter--;
			setStoneCount(1);
		}
		
		backEnd.setPlayerMove(simpleact);
		QMetaObject::invokeMethod(parentObject, "setStone", 
			Q_ARG(QVariant, std::get<0>(simpleact.target)), 
			Q_ARG(QVariant, std::get<1>(simpleact.target)), 
			Q_ARG(QVariant, playerToken));

		resetVarPos();
		
		QMetaObject::invokeMethod(parentObject, "prepForAiMove");

	}
	else if (std::get<0>(tokenPos) != NULL) {
		simpleact.location = tokenPos;
		if (std::find(actionList.begin(), actionList.end(), simpleact) != actionList.end()) {

			backEnd.setPlayerMove(simpleact);

			QMetaObject::invokeMethod(parentObject, "removeStone",
				Q_ARG(QVariant, std::get<0>(simpleact.location)),
				Q_ARG(QVariant, std::get<1>(simpleact.location)));

			QMetaObject::invokeMethod(parentObject, "setStone", 
				Q_ARG(QVariant, std::get<0>(simpleact.target)),
				Q_ARG(QVariant, std::get<1>(simpleact.target)),
				Q_ARG(QVariant, playerToken));

			resetVarPos();
			makeAIMove();

		}
	}
	else {
		clickPos = std::make_tuple(ringIndex, posIndex);
	}
}
