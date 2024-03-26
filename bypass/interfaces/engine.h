#pragma once

#include "../util.h"

struct i_engine_client {
	void execute_client_cmd(const char* cmd);
};