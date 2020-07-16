#pragma once
#include<vector>
#include"action.cpp"
#include <string>
class Mill_Board
{
	private:

		std::vector<std::vector<int>> board = { 
												{0,0,0,0,0,0,0,0},// Outer Square
												{0,0,0,0,0,0,0,0},// Middle
												{0,0,0,0,0,0,0,0} // Inner Square
											};
		int activePlayer = 1;
		int gamePhase1 = 1;
		int gamePhase2 = 1;
		int whiteStones = 9;
		int whiteStonestaken = 0;
		int blackStones = 9;
		int blackStonestaken = 0;

		void setStones();
		void setGamePhase();
		void setactivePlayer();
		void setStoneTaken();

	public:

		int getactivePlayer();
		int getStones(int player);
		std::vector<action> possibleActions();
		std::vector<std::tuple<int, int>> possibleStones();

		void makeMove(action move);
		void takeStone(std::tuple<int, int> pos);
		bool checkforMill(std::tuple<int, int> act, bool adonly = false, std::tuple<int, int> loca = std::make_tuple(7, 7));
		int checkforwin();

		int getGamePhase();

		void printField();
		std::string stateRepresentation();

};

