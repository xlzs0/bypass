#pragma once

#include "interfaces/cvar.h"
#include "interfaces/engine.h"
#include "util.h"

namespace interfaces {
	extern i_engine_client* engine;
	extern i_engine_convar* convar;

	void initialize();
};