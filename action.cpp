#pragma once
#include<vector>
#include<tuple>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

struct action {

	std::tuple<int, int> location;
	std::tuple<int, int> target;
	std::tuple<int, int> takeAway;

	action(int location1, int location2, int target1, int target2, int take1 = 7, int take2 = 7)
	{
		location = std::make_tuple(location1, location2);
		target = std::make_tuple(target1, target2);
		takeAway = std::make_tuple(take1, take2);
	}
	action() {

	}

	bool operator==(const action& act1) {

		if (act1.location == location && act1.target == target && act1.takeAway == takeAway) {
			return true;
		}
		else {
			return false;
		}
	}

};
Q_DECLARE_METATYPE(action)




