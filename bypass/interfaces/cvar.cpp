#include "cvar.h"
#include "../interfaces.h"

/*
	sig: 55 8B EC 83 ? ? 8B 45 ? 83 EC ? 83 38 ? 53 56 57

void __cdecl setinfo(_DWORD* args) {
	if (*args != 3) {
		Msg("Syntax: setinfo <key> <value>\n");
		return;
	}

	const char* name = (const char*)args[259];
	const char* value = args[260];

	c_cvar* cvar = g_cvar->find_var(name);
	if (!cvar)
	{
		const char* cvar_name = g_memalloc->alloc(strlen(name) + 1);
		strcpy(cvar_name, name);

		void* mem = g_memalloc->alloc(104);
		if (mem)
			cvar = new_cvar(mem, cvar_name, "", 512, "Custom user info value");
		else
			cvar = 0;

	set_value_allowed:
		cvar->set_value(value);
		if (g_clientstate->sign_on_state >= 2)
		{
			c_set_cvar_msg msg;
			construct_net_msg(msg);

			msg->name = name;
			msg->value = cvar->get_string();

			g_clientstate->net_channel->send_net_msg(msg, 0, 0);
			destruct_net_msg(msg);
		}
		return;
	}

	if (cvar->is_command())
	{
		Msg("Name %s is already registered as console command\n", name);
		return;
	}

	if (!cvar->flag_set(512))
	{
		Msg("Convar %s is already registered but not as user info value\n", name);
		return;
	}

	if (cvar->flag_set(0x400000) && g_clientstate->sign_on_state >= 2 && (!cvar->flag_set(512) || !g_clientdll || !g_clientdll->unk_func(0)))
	{
		ConMsg("Can't change %s when playing, disconnect from the server or switch team to spectators\n", cvar->get_name());
		return;
	}

	sv_cheats = unk_fn("sv_cheats", false); ; not g_cvar->find_var
	v4 = unk_fn();
	if (v4 == 2 || v4 == 4 || !cvar->flag_set(2))
	{
		if (cvar->flag_set(0x4000) && !sv_cheats->get_value())
		{
			Msg("Convar %s is marked as cheat and cheats are off\n", name);
			return;
		}
		goto set_value_allowed;
	}
}
*/

c_cvar* i_engine_convar::create_cvar(const char* name, const char* value) {
	if (auto cvar = find_var(name); cvar)
		return cvar;

	char buffer[520];
	sprintf_s(buffer, "setinfo %s %s", name, value);

	interfaces::engine->execute_client_cmd(buffer);

	auto cvar = find_var(name);
	if (cvar) {
		cvar->flags &= ~e_cvar_flags::userinfo;
		cvar->flags |= e_cvar_flags::archive | e_cvar_flags::hidden;
	}

	return cvar;
}