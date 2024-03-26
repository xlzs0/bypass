#pragma once

#include <cstdint>

namespace addresses {
	extern uint32_t* protocol_version;
	extern uint32_t* client_version;
	extern uint32_t* server_version;
	extern uint8_t* net_graph_beta_check;
	extern uint8_t* net_graph_connected_check;
	extern uintptr_t cbuf_execute;
	extern uint8_t* cbuf_execute_thread_check;
	extern uintptr_t* exe_build;
	extern char** exe_build_fmt;
	extern char** exe_build_version;

	void initialize();
};