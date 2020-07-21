#pragma once
#include "Mill_Board.h"
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include "action.cpp"
#include <String>


int Mill_Board::getactivePlayer()
{
	return activePlayer;
}

void Mill_Board::setactivePlayer()
{
	activePlayer *= -1;
}

void Mill_Board::setStoneTaken()
{
	if (activePlayer == 1) {
		blackStonestaken++;
	}
	else {
		whiteStonestaken++;
	}
}

int Mill_Board::getStones(int player)
{
	if (player == 1) {
		return whiteStones;
	}
	else {
		return blackStones;
	}
	return 0;
}

std::vector<action> Mill_Board::possibleActions()
{
	std::vector<action> actionlist;
	
	if ((gamePhase1 == 1 && activePlayer == 1) || (gamePhase2 == 1 && activePlayer == -1)) {
		for (int i = 0; i < static_cast<int>(board.size()); i++) {
			for (int j = 0; j < static_cast<int>(board[i].size()); j++) {
				if (board[i][j] == 0) {
					if (checkforMill(std::tuple<int, int>(i, j), true)) {

						std::vector<std::tuple<int, int>> actns = possibleStones();
						for (int k = 0; k < static_cast<int>(actns.size()); k++) {
							actionlist.push_back(action(9, 9, i, j, std::get<0>(actns[k]), std::get<1>(actns[k])));
						}
					}
					else {
						actionlist.push_back(action(9, 9, i, j));
					}
					
				}
			}
		}
	}
	else if ((gamePhase1 == 2 && activePlayer == 1) || (gamePhase2 == 2 && activePlayer == -1)) {
		for (int i = 0; i < static_cast<int>(board.size()); i++) {
			for (int j = 0; j < static_cast<int>(board[i].size()); j++) {
				
				if (board[i][j] == activePlayer) {
					if (board[i][(j + 1) % 8] == 0) {
						if (checkforMill(std::tuple<int, int>(i, ((j + 1) % 8)), true, std::tuple<int, int>(i, j))) {

							std::vector<std::tuple<int, int>> actns = possibleStones();
							for (int k = 0; k < static_cast<int>(actns.size()); k++) {
								actionlist.push_back(action(i, j, i, ((j + 1) % 8), std::get<0>(actns[k]), std::get<1>(actns[k])));
							}
						}
						else {
							actionlist.push_back(action(i, j, i, ((j + 1) % 8)));
						}
					}

					if (j - 1 >= 0) {

						if (board[i][j - 1] == 0) {

							if (checkforMill(std::tuple<int, int>(i, (j - 1)), true, std::tuple<int, int>(i, j))) {

								std::vector<std::tuple<int, int>> actns = possibleStones();
								for (int k = 0; k < static_cast<int>(actns.size()); k++) {
									actionlist.push_back(action(i, j, i, (j - 1), std::get<0>(actns[k]), std::get<1>(actns[k])));
								}
							}
							else {
								actionlist.push_back(action(i, j, i, (j - 1)));
							}
						}
					}
					else {
						if (board[i][7] == 0) {

							if (checkforMill(std::tuple<int, int>(i, 7), true, std::tuple<int, int>(i, j))) {

								std::vector<std::tuple<int, int>> actns = possibleStones();
								for (int k = 0; k < static_cast<int>(actns.size()); k++) {
									actionlist.push_back(action(i, j, i, 7, std::get<0>(actns[k]), std::get<1>(actns[k])));
								}
							}
							else {
								actionlist.push_back(action(i, j, i, 7));
							}
						}
					}

					if (j % 2 == 1) {
						if (i < 2) {
							if (board[i + 1][j] == 0) {

								if (checkforMill(std::tuple<int, int>((i + 1), j), true, std::tuple<int, int>(i, j))) {

									std::vector<std::tuple<int, int>> actns = possibleStones();
									for (int k = 0; k < static_cast<int>(actns.size()); k++) {
										actionlist.push_back(action(i, j, (i + 1), j, std::get<0>(actns[k]), std::get<1>(actns[k])));
									}
								}
								else {
									actionlist.push_back(action(i, j, (i + 1), j));
								}
							}
						}
						if (i > 0) {
							if (board[i - 1][j] == 0) {

								if (checkforMill(std::tuple<int, int>((i - 1), j), true, std::tuple<int, int>(i, j))) {

									std::vector<std::tuple<int, int>> actns = possibleStones();
									for (int k = 0; k < static_cast<int>(actns.size()); k++) {
										actionlist.push_back(action(i, j, (i - 1), j, std::get<0>(actns[k]), std::get<1>(actns[k])));
									}
								}
								else {
									actionlist.push_back(action(i, j, (i - 1), j));
								}
							}
						}
					}
				}
			}
		}
	}
	else if ((gamePhase1 == 3 && activePlayer == 1) || (gamePhase2 == 3 && activePlayer == -1)) {
		//GamePhase3
		for (int i = 0; i < static_cast<int>(board.size()); i++) {
			for (int j = 0; j < static_cast<int>(board[i].size()); j++) {
				if (board[i][j] == activePlayer) {
					for (int k = 0; k < static_cast<int>(board.size()); k++) {
						for (int l = 0; l < static_cast<int>(board[k].size()); l++) {
							if (board[k][l] == 0) {
								if (checkforMill(std::tuple<int, int>(i, ((j + 1) % 8)), true, std::tuple<int, int>(i, j))) {

									std::vector<std::tuple<int, int>> actns = possibleStones();
									for (int m = 0; m < static_cast<int>(actns.size()); m++) {
										actionlist.push_back(action(i, j, k, l, std::get<0>(actns[m]), std::get<1>(actns[m])));
									}
								}
								else {
									actionlist.push_back(action(i, j, k, l));
								}
							}
						}
					}
				}
			}
		}
	}

	return actionlist;
}

std::vector<std::tuple<int, int>> Mill_Board::possibleStones()
{
	std::vector<std::tuple<int, int>> stoneLocation;

	for (int i = 0; i < static_cast<int>(board.size()); i++) {
		for (int j = 0; j < static_cast<int>(board[i].size()); j++) {

			if (board[i][j] == (activePlayer * -1) && !checkforMill(std::tuple<int, int>(i, j), false)) {
				stoneLocation.push_back(std::tuple<int, int>(i, j));
			}
			else {

			}
		}
	}
	if (static_cast<int>(stoneLocation.size()) == 0) {
		
		stoneLocation.push_back(std::tuple<int, int>(7, 7));
	}

	return stoneLocation;
}

void Mill_Board::makeMove(action move)
{	
	
	if (std::get<0>(move.location) == 9) {

		board[std::get<0>(move.target)][std::get<1>(move.target)] = activePlayer;
	}
	else {
		int sym = board[std::get<0>(move.location)][std::get<1>(move.location)];

		board[std::get<0>(move.target)][std::get<1>(move.target)] = sym;
		board[std::get<0>(move.location)][std::get<1>(move.location)] = 0;
	}
	

	if (std::get<0>(move.takeAway) != 7) {

		board[std::get<0>(move.takeAway)][std::get<1>(move.takeAway)] = 0;
		setStoneTaken();

	}

	setStones();

	if (blackStonestaken == 6) {
		gamePhase2 = 3;
	}
	else if (whiteStonestaken == 6) {
		gamePhase1 = 3;
	}
	
	setactivePlayer();
}

void Mill_Board::takeStone(std::tuple<int, int> pos)
{
	board[std::get<0>(pos)][std::get<1>(pos)] = 0;
	setStoneTaken();
}

bool Mill_Board::checkforMill(std::tuple<int, int> act, bool adonly, std::tuple<int, int> loca)
{
	int squ = std::get<0>(act);
	int field = std::get<1>(act);
	int tar1 = std::get<0>(loca);
	int tar2 = std::get<1>(loca);

	if (!adonly) {
		if ((field % 2) == 0) {
			if (field - 1 >= 0) {
				if ((board[squ][field] == 1 && board[squ][field + 1] == 1 && board[squ][(field + 2) % 8] == 1) ||
					(board[squ][field] == -1 && board[squ][field + 1] == -1 && board[squ][(field + 2) % 8] == -1)) {

					return true;
				}
				if ((board[squ][field] == 1 && board[squ][field - 1] == 1 && board[squ][field - 2] == 1) ||
					(board[squ][field] == -1 && board[squ][field - 1] == -1 && board[squ][field - 2] == -1)) {

					return true;
				}
			}
			else {
				if ((board[squ][field] == 1 && board[squ][field + 1] == 1 && board[squ][(field + 2) % 8] == 1) ||
					(board[squ][field] == -1 && board[squ][field + 1] == -1 && board[squ][(field + 2) % 8] == -1)) {

					return true;
				}
				if ((board[squ][field] == 1 && board[squ][7] == 1 && board[squ][6] == 1) ||
					(board[squ][field] == -1 && board[squ][7] == -1 && board[squ][6] == -1)) {

					return true;
				}
			}
		}
		else {
			if ((board[squ][field] == 1 && board[squ][(field + 1) % 8] == 1 && board[squ][field - 1] == 1) ||
				(board[squ][field] == -1 && board[squ][(field + 1) % 8] == -1 && board[squ][field - 1] == -1)) {

				return true;
			}
			if ((board[squ][field] == 1 && board[(squ + 1) % 3][field] == 1 && board[(squ + 2) % 3][field] == 1) ||
				(board[squ][field] == -1 && board[(squ + 1) % 3][field] == -1 && board[(squ + 2) % 3][field] == -1)) {

				return true;
			}
		}
	}
	else {
		if ((field % 2) == 0) {
			if (field - 1 >= 0) {
				if (board[squ][field + 1] == activePlayer && board[squ][(field + 2) % 8] == activePlayer && (field + 1) != tar2) {

					return true;
				}
				if (board[squ][field - 1] == activePlayer && board[squ][field - 2] == activePlayer && (field - 1) != tar2) {

					return true;
				}
			}
			else {
				if (board[squ][field + 1] == activePlayer && board[squ][(field + 2) % 8] == activePlayer && (field + 1) != tar2) {

					return true;
				}
				if (board[squ][7] == activePlayer && board[squ][6] == activePlayer && tar2 != 7) {

					return true;
				}
			}
		}
		else {
			
			if (board[squ][(field + 1) % 8] == activePlayer && 
				board[squ][field - 1] == activePlayer && 
				tar2 != ((field + 1) % 8) && 
				(tar2 != field - 1)) {

				return true;
			}
			if (board[(squ + 1) % 3][field] == activePlayer && 
				board[(squ + 2) % 3][field] == activePlayer && tar1 != ((squ + 1) % 3) && tar1 != ((squ + 2) % 3)) {
				
				return true;
			}
		}
	}

	return false;
}

int Mill_Board::checkforwin()
{
	if (whiteStonestaken == 7 || (static_cast<int>(possibleActions().size()) == 0 && activePlayer == 1)) {
		return -1;
	}
	else if (blackStonestaken == 7 || (static_cast<int>(possibleActions().size()) == 0 && activePlayer == -1)) {
		return 1;
	}
	else {
		return 0;
	}
}

int Mill_Board::getGamePhase()
{
	if (activePlayer == 1) {
		return gamePhase1;
	}
	else {
		return gamePhase2;
	}
}

void Mill_Board::printField()
{
	std::string longline = "---------------------";
	std::string midline = "--------------";
	std::string shortline = "-------";
	std::string offset = "   ";
	std::vector<std::vector<char>> replaceBoard = { {},{},{} };

	std::cout << "X" << whiteStones << "||" << whiteStonestaken << std::endl;
	std::cout << "O" << blackStones << "||" << blackStonestaken << std::endl;

	for (int i = 0; i < static_cast<int>(board.size()); i++) {
		for (int j = 0; j < static_cast<int>(board[i].size()); j++) {
			if (board[i][j] == 1) {
				replaceBoard[i].push_back('X');
			}
			else if (board[i][j] == -1) {
				replaceBoard[i].push_back('O');
			}
			else {
				replaceBoard[i].push_back('.');
			}
		}
	}

	std::cout << offset << replaceBoard[0][0] << longline << replaceBoard[0][1] << longline << replaceBoard[0][2] << std::endl;

	for (int i = 0; i < 3; i++) {
		std::cout << offset << "|                     |                     |" << std::endl;
	}

	std::cout << offset << "|      " << replaceBoard[1][0] << midline << replaceBoard[1][1] << midline << replaceBoard[1][2] << "      |" << std::endl;

	for (int i = 0; i < 3; i++) {
		std::cout << offset << "|      |              |              |      |" << std::endl;
	}

	std::cout << offset << "|      |      " << replaceBoard[2][0] << shortline << replaceBoard[2][1] << shortline << replaceBoard[2][2] << "      |      |" << std::endl;

	for (int i = 0; i < 2; i++) {
		std::cout << offset << "|      |      |               |      |      |" << std::endl;
	}
	std::cout << offset << replaceBoard[0][7] << "------" << replaceBoard[1][7] << "------" << replaceBoard[2][7] << "               " << replaceBoard[2][3] << "------" << replaceBoard[1][3] << "------" << replaceBoard[0][3] << std::endl;

	for (int i = 0; i < 2; i++) {
		std::cout << offset << "|      |      |               |      |      |" << std::endl;
	}

	std::cout << offset << "|      |      " << replaceBoard[2][6] << shortline << replaceBoard[2][5] << shortline << replaceBoard[2][4] << "      |      |" << std::endl;

	for (int i = 0; i < 3; i++) {
		std::cout << offset << "|      |              |              |      |" << std::endl;
	}

	std::cout << offset << "|      " << replaceBoard[1][6] << midline << replaceBoard[1][5] << midline << replaceBoard[1][4] << "      |" << std::endl;

	for (int i = 0; i < 3; i++) {
		std::cout << offset << "|                     |                     |" << std::endl;
	}

	std::cout << offset << replaceBoard[0][6] << longline << replaceBoard[0][5] << longline << replaceBoard[0][4] << std::endl;
}

std::string Mill_Board::stateRepresentation()
{
	std::string statestring;

	for (int i = 0; i < static_cast<int>(board.size()); i++) {
		for (int j = 0; j < static_cast<int>(board[i].size()); j++) {
			statestring.append(std::to_string(board[i][j]));
		}
	}
	return statestring;
}

void Mill_Board::setStones()
{
	if (activePlayer == 1 && gamePhase1 == 1) {
		whiteStones -= 1;
	}
	else if (activePlayer == -1 && gamePhase2 == 1){
		blackStones -= 1;
	}
	if ((activePlayer == 1 && gamePhase1 == 1 && whiteStones == 0) || 
		(activePlayer == -1 && gamePhase2 == 1 && blackStones == 0)){
		setGamePhase();
	}
}

void Mill_Board::setGamePhase()
{
	if (activePlayer == 1) {
		if (gamePhase1 < 3) {
			gamePhase1++;
		}
	}
	else {
		if (gamePhase2 < 3) {
			gamePhase2++;
		}
	}

}
