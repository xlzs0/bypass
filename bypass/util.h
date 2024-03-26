#pragma once

#include <windows.h>
#include <vector>
#include <string>

namespace util {
	template<typename... args_t>
	inline void con_msg(const char* msg, args_t... args) {
		static auto con_msg = reinterpret_cast<void(*)(const char*, ...)>(GetProcAddress(reinterpret_cast<HMODULE>(modules::tier0), "?ConMsg@@YAXPBDZZ"));
		if (con_msg)
			con_msg(msg, args...);
	}

	inline void patch(void* ptr, uint8_t instruction, uint32_t amt) {
		if (!ptr || !amt)
			return;

		DWORD old_protect;
		if (VirtualProtect(ptr, amt, PAGE_EXECUTE_READWRITE, &old_protect)) {
			memset(ptr, instruction, amt);
			VirtualProtect(ptr, amt, old_protect, &old_protect);
		}
	}

	inline void copy_str(char** str, const char* new_str, int32_t size = -1) {
		if (size == -1)
			size = strlen(new_str);

		DWORD old_protect;
		if (VirtualProtect(*str, size, PAGE_EXECUTE_READWRITE, &old_protect)) {
			memcpy(*str, new_str, size);
			VirtualProtect(*str, size, old_protect, &old_protect);
		}
	}

	template <typename t>
	inline t* get_interface(const HMODULE module, const char* name) {
		using create_interface_t = t*(__cdecl*)(const char*, int32_t*);
		auto create_interface = reinterpret_cast<create_interface_t>(GetProcAddress(reinterpret_cast<HMODULE>(module), "CreateInterface"));
		
		if (create_interface)
			return create_interface(name, nullptr);
		
		return nullptr;
	}

	template <typename ret_t, typename ... args_t>
	inline constexpr ret_t call_this(void* instance, size_t index, args_t... args) {
		using fn_t = ret_t(__thiscall*)(void*, args_t...);
		auto vtable = *static_cast<fn_t**>(instance);
		return vtable[index](instance, args...);
	}

	inline uintptr_t pattern_scan(const HMODULE module, const char* signature) {
		auto to_byte = [](const char c) -> uint8_t {
			if (c >= '0' && c <= '9') 
				return c - '0';

			if (c >= 'A' && c <= 'F') 
				return 10 + c - 'A';

			if (c >= 'a' && c <= 'f') 
				return 10 + c - 'a';

			return static_cast<uint8_t>(-1);
		};

		if (!module)
			return NULL;

		auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
		auto nt_header = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(module) + dos_header->e_lfanew);

		auto size_of_image = nt_header->OptionalHeader.SizeOfImage;
		auto bytes = reinterpret_cast<uint8_t*>(module);

		std::vector<int> pattern;
		const char* current_char = signature;

		while (*current_char) {
			if (*current_char == '?') {
				current_char++;
				pattern.push_back(-1);
			}
			else if (*current_char == ' ')
				current_char++;
			else {
				pattern.push_back(to_byte(*current_char) << 4 | to_byte(*(current_char + 1)));
				current_char += 2;
			}
		}

		auto end = bytes + size_of_image - pattern.size();

		for (auto current = bytes; current < end; ++current) {
			bool found = true;
			for (size_t i = 0; i < pattern.size(); ++i) {
				if (pattern[i] != -1 && pattern[i] != current[i]) {
					found = false;
					break;
				}
			}

			if (found)
				return reinterpret_cast<uintptr_t>(current);
		}

		return NULL;
	}
};