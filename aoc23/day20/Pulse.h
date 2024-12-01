#pragma once

#include <functional>
#include "Module.h"

class Module;

enum class PulseType
{
	HIGH,
	LOW
};

class Pulse
{
	std::reference_wrapper<Module> module;
	PulseType pulseType;
	Pulse(Module& module, PulseType pulseType);
};

