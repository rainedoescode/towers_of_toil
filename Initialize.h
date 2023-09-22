#pragma once

#ifndef INITIALIZE_H
#define INITIALIZE_H
#endif // !INITIALIZE_H

#include "Location.h"

class Initialize
{
public:
	Initialize();
	~Initialize();

private:
	std::string shortDescs[17];
	std::string longDescs[17];
	std::string examineText[17];
};

Initialize::Initialize()
{
}

Initialize::~Initialize()
{
}
