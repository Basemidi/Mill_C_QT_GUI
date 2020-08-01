#pragma once
#include "Bot_Brain.h"
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <future>

int Bot_Brain::getsimucount()
{
	return simulationCount;
}

int Bot_Brain::getrolloutcount()
{
	return rolloutcount;
}

float Bot_Brain::UCB1(Mill_Board gamf)
{
	float x = (static_cast<float>(Q_value[gamf.stateRepresentation()]) / static_cast<float>(N_value[gamf.stateRepresentation()]));
	float ro = sqrt((log(static_cast<float>(N_value[path.back()])) / static_cast<float>(N_value[gamf.stateRepresentation()])));

	return  x + (explore * ro);
}

Mill_Board Bot_Brain::descent(Mill_Board gam)
{
	path.push_back(gam.stateRepresentation());

	if ((N_value.find(gam.stateRepresentation()) == N_value.end()) || gam.checkforwin() != 0) {
		return gam;
	}

	while (true) {
		vector<action> children = gam.possibleActions();
		vector<float> UCB_values;

		for (int num = 0; num < static_cast<int>(children.size()); num++) {
			Mill_Board copygam = gam;

			copygam.makeMove(children[num]);

			if (N_value.find(copygam.stateRepresentation()) == N_value.end()) {
				path.push_back(copygam.stateRepresentation());
				return copygam;
			}
			else {
				if (std::find(path.begin(), path.end(), copygam.stateRepresentation()) == path.end()) {
					UCB_values.push_back(UCB1(copygam));
				}

			}
		}

		action bestaction = children[distance(UCB_values.begin(), max_element(UCB_values.begin(), UCB_values.end()))];

		gam.makeMove(bestaction);
		path.push_back(gam.stateRepresentation());

		if (gam.checkforwin() != 0 || static_cast<int>(path.size()) > 1000) {
			return gam;
		}
	}
}

void Bot_Brain::expansion(Mill_Board gam)
{
	if (N_value.find(gam.stateRepresentation()) != N_value.end()) {
		return;
	}
	else {
		N_value.insert({ gam.stateRepresentation() , 0 });
		Q_value.insert({ gam.stateRepresentation() , 0 });
	}

	return;
}

Mill_Board Bot_Brain::rollout(Mill_Board gam)
{
	if (gam.checkforwin() != 0) {
		return gam;
	}

	std::random_device rd;
	std::mt19937 eng(rd());

	while (gam.checkforwin() == 0) {
		vector<action> children = gam.possibleActions();
		std::uniform_int_distribution<int> distr(0, (static_cast<int>(children.size()) - 1));
		gam.makeMove(children[distr(eng)]);
	}
	return gam;
}

void Bot_Brain::backPropagation(Mill_Board gam)
{
	int pla = player;
	int reward;

	if (gam.checkforwin() == player) {
		reward = 0;
	}
	else {
		reward = 1;
	}

	for (int item = 0; item < static_cast<int>(path.size()); item++) {
		Q_value[path[item]] += reward;
		N_value[path[item]] += 1;

		reward = 1 - reward;
	}
}

std::tuple<Mill_Board, vector<std::string>> Bot_Brain::thread_descent(Mill_Board gam, vector<std::string> locpath)
{	
	locpath.push_back(gam.stateRepresentation());

	if ((N_value.find(gam.stateRepresentation()) == N_value.end()) || gam.checkforwin() != 0 || N_value[gam.stateRepresentation()] == 0) {
		return { gam, locpath };
	}

	while (true) {
		vector<action> children = gam.possibleActions();
		vector<float> UCB_values;

		for (int num = 0; num < static_cast<int>(children.size()); num++) {
			Mill_Board copygam = gam;

			copygam.makeMove(children[num]);

			if (N_value.find(copygam.stateRepresentation()) == N_value.end() || N_value[gam.stateRepresentation()] == 0) {
				locpath.push_back(copygam.stateRepresentation());
				return { copygam, locpath };
			}
			else {
				if (std::find(locpath.begin(), locpath.end(), copygam.stateRepresentation()) == locpath.end()) {
					UCB_values.push_back(UCB1_threaded(copygam, locpath));
				}

			}
		}

		action bestaction = children[distance(UCB_values.begin(), max_element(UCB_values.begin(), UCB_values.end()))];

		gam.makeMove(bestaction);
		locpath.push_back(gam.stateRepresentation());

		if (gam.checkforwin() != 0) {
			return std::make_tuple( gam, locpath );
		}
	}
}

std::tuple<vector<std::string>, Mill_Board> Bot_Brain::thread_MCTS(Mill_Board gam, vector<std::string> pat)
{
	std::tuple<Mill_Board, vector<std::string>> tup = thread_descent(gam, pat);
	expansion(std::get<0>(tup));
	Mill_Board wingame = rollout(std::get<0>(tup));
	

	return std::make_tuple(std::get<1>(tup), wingame);
}

void Bot_Brain::threat_backPropagation(Mill_Board gam, vector<std::string> locpath)
{
	int pla = player;
	int reward;

	if (gam.checkforwin() == player) {
		reward = 0;
	}
	else {
		reward = 1;
	}

	for (int item = 0; item < static_cast<int>(locpath.size()); item++) {
		Q_value[locpath[item]] += reward;
		N_value[locpath[item]] += 1;

		reward = 1 - reward;
	}
}

vector<Mill_Board> Bot_Brain::getBestAction(Mill_Board gam, int nums, vector<std::string> pat)
{	
	vector<action> child = gam.possibleActions();
	vector<Mill_Board> states;
	vector<float> UCB1_v;

	for (int i = 0; i < static_cast<int>(child.size()); i++) {

		Mill_Board cpyState = gam;
		cpyState.makeMove(child[i]);

		if (N_value.find(cpyState.stateRepresentation()) == N_value.end()) {
			
			if (static_cast<int>(states.size()) < nums) {
				states.push_back(cpyState);
			}
			else {
				return states;
			}
		}
		else {
				UCB1_v.push_back(UCB1_threaded(cpyState, pat));
		}
	}

	if (static_cast<int>(states.size()) < 3) {
		for (int i = 0; i < (nums - static_cast<int>(states.size())); i++) {
			Mill_Board copy = gam;
			int dist = distance(UCB1_v.begin(), max_element(UCB1_v.begin(), UCB1_v.end()));
			copy.makeMove(child[dist]);
			states.push_back(copy);

			child.erase(child.begin() + dist);
			UCB1_v.erase(UCB1_v.begin() + dist);
		}
	}

	return states;
}

float Bot_Brain::UCB1_threaded(Mill_Board gam, vector<std::string> pat)
{

	float x = (static_cast<float>(Q_value[gam.stateRepresentation()]) / static_cast<float>(N_value[gam.stateRepresentation()]));
	float ro = sqrt((log(static_cast<float>(N_value[pat.back()])) / static_cast<float>(N_value[gam.stateRepresentation()])));

	return  x + (explore * ro);
}


Bot_Brain::Bot_Brain(int pla)
{
	player = pla;

}

Bot_Brain::~Bot_Brain()
{
}

action Bot_Brain::makeRndMove(Mill_Board gam)
{
	std::random_device rd;
	std::mt19937 eng(rd());

	vector<action> child = gam.possibleActions();
	std::uniform_int_distribution<> distr(0, (static_cast<int>(child.size()) - 1));

	return child[distr(eng)];
}

action Bot_Brain::think(Mill_Board gam)
{
	for (int iter = 0; iter < simulationCount; iter++) {

		Mill_Board newgam = descent(gam);
		expansion(newgam);

		for (int roll = 0; roll < rolloutcount; roll++) {
			Mill_Board donegam = rollout(newgam);
			backPropagation(donegam);
		}
		path.clear();
		std::cout << "Thinking:" << to_string((static_cast<float>(iter) / static_cast<float>(simulationCount)) * 100.0f) << "%" << "\r";
	}

	vector<action> poschild = gam.possibleActions();
	vector<int> Nvals;
	vector<int> Qvalues;


	for (int i = 0; i < static_cast<int>(poschild.size()); i++) {
		Mill_Board newgam = gam;
		newgam.makeMove(poschild[i]);

		Nvals.push_back(N_value[newgam.stateRepresentation()]);
		Qvalues.push_back(Q_value[newgam.stateRepresentation()]);

	}

	int maxindex = distance(Nvals.begin(), max_element(Nvals.begin(), Nvals.end()));

	std::cout << to_string((static_cast<float>(Qvalues[maxindex]) / static_cast<float>(Nvals[maxindex]))) << endl;

	return poschild[maxindex];
}

action Bot_Brain::threaded_thinking(Mill_Board gam)
{
	
	int numthrs = std::thread::hardware_concurrency();

	
	if (N_value.find(gam.stateRepresentation()) == N_value.end()) {
		std::tuple<vector<std::string>, Mill_Board> tups = thread_MCTS(gam, {});
		threat_backPropagation(std::get<1>(tups), std::get<0>(tups));
	}

	for (int j = 0; j < simulationCount; j++) {
		vector<std::future<std::tuple<vector<std::string>, Mill_Board>>> thrds;
		vector<std::string> pathcontainer;
		pathcontainer.push_back(gam.stateRepresentation());
		vector<Mill_Board> stts = getBestAction(gam, numthrs, pathcontainer);

		for (int count = 0; count < static_cast<int>(stts.size()); count++) {

			Mill_Board cpy = stts[count];
			vector<std::string> pathcontainer;
			pathcontainer.push_back(gam.stateRepresentation());

			thrds.push_back(std::async([=] { return thread_MCTS(cpy, pathcontainer); }));
		}
		for (int i = 0; i < static_cast<int>(thrds.size()); i++) {

			std::tuple<vector<std::string>, Mill_Board> result = thrds[i].get();
			threat_backPropagation(std::get<1>(result), std::get<0>(result));
		}
		std::cout << "Thinking:" << to_string((static_cast<float>(j) / static_cast<float>(simulationCount)) * 100.0f) << "%" << "\r";
	}

	vector<action> poschild = gam.possibleActions();
	vector<int> Nvals;
	vector<int> Qvalues;


	for (int i = 0; i < static_cast<int>(poschild.size()); i++) {
		Mill_Board newgam = gam;
		newgam.makeMove(poschild[i]);

		Nvals.push_back(N_value[newgam.stateRepresentation()]);
		Qvalues.push_back(Q_value[newgam.stateRepresentation()]);

	}

	int maxindex = distance(Nvals.begin(), max_element(Nvals.begin(), Nvals.end()));

	std::cout << to_string((static_cast<float>(Qvalues[maxindex]) / static_cast<float>(Nvals[maxindex]))) << endl;

	return poschild[maxindex];
}
