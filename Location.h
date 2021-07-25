//Trevor Adams, taadams1@dmacc.edu, 4/19/19
//Location class for text based adventure game
//stores place name, short and long descriptions, coordinates, visited flag

#pragma once

#include <string>
#include <utility>

using std::pair;

class Location
{
private:
	std::string name;
	std::string shortDesc;
	std::string longDesc;
	std::string examineDesc;
	int x, y;
	bool visited;
	bool examined;
public:
	Location();
	Location(std::string, std::string, std::string, std::string);
	~Location();
	void setCoords(int x, int y);
	std::pair<int, int> getCoords();
	std::string getName();
	std::string getShortDesc();
	std::string getLongDesc();
	std::string getExamineDesc();
	void setVisited(bool);
	bool isVisited();
	void setExamined(bool);
	bool isExamined();
};

