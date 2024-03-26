#include "interfaces.h"
#include "defines.h"

namespace interfaces {
	i_engine_client* engine;
	i_engine_convar* convar;

	void initialize() {
		engine = util::get_interface<i_engine_client>(modules::engine, "VEngineClient014");
		convar = util::get_interface<i_engine_convar>(modules::vstdlib, "VEngineCvar007");
	}
}