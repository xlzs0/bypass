#pragma once

#include "util.h"
#include "interfaces.h"

#define assign_address(name) if (addresses::name) { game_original::name = *addresses::name; *addresses::name = game::name; }
#define assign_address_s(name) if (addresses::name) { memcpy(game_original::name, *addresses::name, strlen(*addresses::name)); util::copy_str(addresses::name, game::name); }
#define restore_address(name) if (addresses::name) { *addresses::name = game_original::name; }
#define restore_address_s(name) if (addresses::name) { util::copy_str(addresses::name, game_original::name); }

namespace game {
	extern uint32_t protocol_version;
	extern uint32_t server_version;
	extern uint32_t client_version;
	extern uint32_t exe_build;
	extern const char* exe_build_fmt;
	extern const char* exe_build_version;
};

namespace game_original {
	extern uint32_t protocol_version;
	extern uint32_t client_version;
	extern uint32_t server_version;
	extern uint32_t exe_build;
	extern char exe_build_fmt[128];
	extern char exe_build_version[128];
}

namespace modules {
	extern HMODULE client;
	extern HMODULE engine;
	extern HMODULE vstdlib;
	extern HMODULE tier0;

	void initialize();
}

namespace main {
	DWORD WINAPI thread(void* base);
	void shutdown();
}

class c_plugin
{
public:
	c_plugin() = default;

	using create_interface_t = uintptr_t(__cdecl*)(const char*, int32_t*);

	virtual bool load(create_interface_t interface_factory, create_interface_t game_server_factory) { return true; }
	virtual void unload(void) { main::shutdown(); }
	virtual void pause(void) {}
	virtual void unpause(void) {}
	virtual const char* get_plugin_description(void) { return "bypass"; }
	virtual void level_init(void*) {}
	virtual void server_activate(void*, void*, void*) {}
	virtual void game_frame(bool) {}
	virtual void level_shutdown(void) {}
	virtual void client_active(void*) {}
	virtual void client_fully_connect(void*) {}
	virtual void client_disconnect(void*) {}
	virtual void client_put_in_server(void*, void*) {}
	virtual void set_command_client(void*) {}
	virtual void client_settings_changed(void*) {}
	virtual int client_connect(void*, void*, void*, void*, void*, void*) { return 0; }
	virtual int client_command(void*, void*) { return 0; }
	virtual void network_id_validated(void*, void*) {}
};