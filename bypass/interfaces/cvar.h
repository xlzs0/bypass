#pragma once

#include "../util.h"

enum e_cvar_flags : uint32_t {
	none = 0 << 0,
	hidden = 1 << 4,
	archive = 1 << 7,
	userinfo = 1 << 9,
};

struct c_cvar {
	bool is_command() {
		return util::call_this<bool>(this, 1);
	}

	int32_t get_int() {
		return util::call_this<int32_t>(this, 13, value);
	}

	void set_value(const char* value) {
		util::call_this<void>(this, 14, value);
	}

	void set_int(int32_t value) {
		util::call_this<void>(this, 16, value);
	}

	struct c_value {
		char* string;
		int32_t string_length;
		float_t fvalue;
		int32_t nvalue;
	};

	char pad_0x0[0x4];
	c_cvar* next;
	bool registered;
	char pad_0x9[0x3];
	const char* name;
	const char* help_string;
	uint32_t flags;
	char pad_0x18[0x4];
	c_cvar* parent;
	const char* default_value;
	c_value value;
	char pad_0x2c[0x34];
};

struct i_engine_convar {
	c_cvar* create_cvar(const char* name, const char* value);

	void unregister_con_command(c_cvar* cvar) {
		util::call_this<void>(this, 11, cvar);
	}

	c_cvar* find_var(const char* name) {
		return util::call_this<c_cvar*>(this, 15, name);
	}
};