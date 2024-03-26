#include "addresses.h"
#include "util.h"
#include "defines.h"

namespace addresses {
	uint32_t* protocol_version;
	uint32_t* client_version;
	uint32_t* server_version;
	uint8_t* net_graph_beta_check;
	uint8_t* net_graph_connected_check;
	uintptr_t cbuf_execute;
	uint8_t* cbuf_execute_thread_check;
	uintptr_t* exe_build;
	char** exe_build_fmt;
	char** exe_build_version;

	void initialize() {
		// ref: "Pinging %s\n"
		if (auto ptr = util::pattern_scan(modules::engine, "FF 35 ? ? ? ? 8D 4C 24 10"); ptr) {
			protocol_version = *reinterpret_cast<uint32_t**>(ptr + 0x2);
			client_version = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(protocol_version) + 0x4);
			server_version = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(protocol_version) - 0x4);
		}

		// ref: "Exe build: "
		if (auto ptr = util::pattern_scan(modules::engine, "FF 35 ? ? ? ? 68 ? ? ? ? FF D7 83 C4 ? FF"); ptr) {
			exe_build = *reinterpret_cast<uintptr_t**>(ptr + 0x2);
			exe_build_fmt = reinterpret_cast<char**>(ptr + 0x7);
		}

		// ref: "Protocol version %i [%i/%i]\nExe versio"
		if (auto ptr = util::pattern_scan(modules::engine, "0F 45 05 ? ? ? ? 80 3D ? ? ? ? 00 57 74"); ptr)
			exe_build_version = *reinterpret_cast<char***>(ptr + 0x3);

		// ref: "fps: %5i  var: %4.1f ms  ping: %i ms"
		if (auto ptr = util::pattern_scan(modules::client, "8B 45 10 83 C4 ? ? 44 ? ? 8B"); ptr)
			net_graph_beta_check = reinterpret_cast<uint8_t*>(ptr + 0x56);

		if (auto ptr = util::pattern_scan(modules::client, "89 44 24 4C 8B 11 8B 52 ? ? ? 84 C0 0F"); ptr)
			net_graph_connected_check = reinterpret_cast<uint8_t*>(ptr + 0xE);

		// ref: "Executing command outside main loop thread\n"
		if (auto ptr = util::pattern_scan(modules::engine, "55 8B EC 81 EC ? ? ? ? 53 56 57 ? ? ? ? ? ? 84 C0 75 ? 68"); ptr) {
			cbuf_execute = ptr;
			cbuf_execute_thread_check = reinterpret_cast<uint8_t*>(cbuf_execute + 0xC);
		}
	}
}