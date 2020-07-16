


var playerTurn = true;

function setCounter(num, token) {
	if (token == -1) {
		blackStoneCounter.text = "" + num;
	} else {
		whiteStoneCounter.text = "" + num;
	}
}

function createStone(pos1, player) {
	

	if (player == -1) {
		var stone = Qt.createComponent("qrc:/BlackGameToken.qml");
	} else {
		var stone = Qt.createComponent("qrc:/WhiteGameToken.qml");
	}
	

	if (pos1 != null) {
		var dynamicObject = stone.createObject(pos1.parent, { posIndex: pos1.posIndex });
		dynamicObject.x = pos1.x - 15;
		dynamicObject.y = pos1.y - 15;
		window.tokens[pos1.parent.ringIndex + "" + pos1.posIndex] = dynamicObject;
	}
	
}

function createStoneAtPos(ring, pos, player) {
	var posArray = [
		[position00, position01, position02, position03, position04, position05, position06, position07],
		[position10, position11, position12, position13, position14, position15, position16, position17],
		[position20, position21, position22, position23, position24, position25, position26, position27]
	];

	var pos = posArray[ring][pos];
	createStone(pos, player);
}

function selectedPosition(position) {

	window.positionSignal(position.parent.ringIndex, position.posIndex);
}

function setPlayerTurn() {
	if (!playerTurn) {
		playerTurn = true;
	} else {
		playerTurn = false;
	}
}

function removeToken(Ring, pos) {
	
	var position = Ring + "" + pos;
	window.tokens[position].destroy();
}