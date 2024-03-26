#include "engine.h"
#include "../addresses.h"

void i_engine_client::execute_client_cmd(const char* cmd) {
	util::call_this<void>(this, 114, cmd, false);

	if (addresses::cbuf_execute)
		reinterpret_cast<void(__cdecl*)()>(addresses::cbuf_execute)();
}