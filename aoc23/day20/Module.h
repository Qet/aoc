#pragma once

#include <vector>
#include <queue>
#include <functional>

class Pulse;

class Module
{
	std::vector<std::reference_wrapper<Module>> outputs;
	
	std::queue<Pulse> pulseQueue;

public:
	void processOutputPulses();
	Module();


};

