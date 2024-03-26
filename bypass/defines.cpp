#include "defines.h"

namespace game_original {
	uint32_t protocol_version;
	uint32_t client_version;
	uint32_t server_version;
	uint32_t exe_build;
	char exe_build_fmt[128];
	char exe_build_version[128];
}

namespace game {
	uint32_t protocol_version = 13764;
	uint32_t client_version = 1176;
	uint32_t server_version = 1176;
	uint32_t exe_build = 7929;
	const char* exe_build_fmt = "Exe build: 13:50:31 Aug 17 2020";
	const char* exe_build_version = "1.37.6.4";
}

namespace modules {
	HMODULE client;
	HMODULE engine;
	HMODULE vstdlib;
	HMODULE tier0;

	void initialize() {
		client = GetModuleHandleA("client.dll");
		engine = GetModuleHandleA("engine.dll");
		vstdlib = GetModuleHandleA("vstdlib.dll");
		tier0 = GetModuleHandleA("tier0.dll");
	}
}