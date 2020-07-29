#pragma once
#include <vector>
#include <map>
#include <string>
#include "action.cpp"
#include "Mill_Board.h"

using namespace std;

class Bot_Brain
{
	
private:
	int simulationCount = 5000;
	int rolloutcount = 1;
	float explore = 0.5;
	vector<string> path;
	int player;

	std::map<string, int> Q_value;
	std::map<string, int> N_value;

	int getsimucount();
	int getrolloutcount();
	float UCB1(Mill_Board gamf);

	Mill_Board descent(Mill_Board gam);
	void expansion(Mill_Board gam);
	Mill_Board rollout(Mill_Board gam);
	void backPropagation(Mill_Board gam);

	std::tuple<Mill_Board, vector<std::string>> thread_descent(Mill_Board gam, vector<std::string> locpath);
	std::tuple<vector<std::string>, Mill_Board> thread_MCTS(Mill_Board gam, vector<std::string> pat);
	void threat_backPropagation(Mill_Board gam, vector<std::string> locpath);
	vector<Mill_Board> getBestAction(Mill_Board gam, int nums, vector<std::string> pat);
	float UCB1_threaded(Mill_Board gam, vector<std::string> pat);

public:
	Bot_Brain(int pla = 1);
	~Bot_Brain();

	action makeRndMove(Mill_Board gam);
	action think(Mill_Board gam);

	action threaded_thinking(Mill_Board gam);

};

