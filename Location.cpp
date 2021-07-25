#include "Location.h"


Location::Location()
{
	//nothing
}

Location::Location(std::string name, std::string shortDesc, std::string longDesc, std::string examineDesc)
{
	this->name = name;
	this->shortDesc = shortDesc;
	this->longDesc = longDesc;
	this->examineDesc = examineDesc;

	this->visited = false; //set visited to false on initialization
	this->examined = false; //location has not been examined
}


Location::~Location()
{
}

void Location::setCoords(int xIn, int yIn)
{
	this->x = xIn;
	this->y = yIn;
}

std::pair<int, int> Location::getCoords()
{
	return std::make_pair(x, y);
}

std::string Location::getName()
{
	return name;
}

std::string Location::getShortDesc()
{
	return shortDesc;
}

std::string Location::getLongDesc()
{
	return longDesc;
}

std::string Location::getExamineDesc()
{
	return examineDesc;
}

bool Location::isVisited()
{
	return visited;
}

void Location::setVisited(bool v)
{
	this->visited = v;
}

bool Location::isExamined()
{
	return examined;
}

void Location::setExamined(bool x)
{
	this->examined = x;
}