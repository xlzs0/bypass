DWORD WINAPI Main(LPVOID pBase) {
	while (!GetModuleHandleA("serverbrowser.dll")) {
		SleepEx(1000, false);
	}

	auto EngineClient = GetInterface<IVEngineClient>("engine.dll", "VEngineClient014");
	EngineClient->ExecuteClientCmd("clear");

	std::vector<const char*> ToDelete = {
		"chatwheel_ping",
		"sv_mapvetopickvote_maps",
		"sv_mapvetopickvote_phase_duration",
		"sv_game_mode_flags",
		"mp_guardian_ai_bt_difficulty_adjust_wave_interval",
		"mp_guardian_ai_bt_difficulty_max_next_level_bots",
		"mp_guardian_ai_bt_difficulty_cap_beginning_round",
		"mp_guardian_ai_bt_difficulty_initial_value",
		"mp_guardian_bomb_plant_emit_bounds_config",
		"mp_guardian_bomb_plant_add_bounds_pt",
		"mp_guardian_bomb_plant_clear_all_bounds",
		"mp_guardian_bomb_plant_new_bounds",
		"mp_guardian_clear_all_player_spawns",
		"mp_guardian_add_player_spawn_pt",
		"mp_guardian_clear_all_enemy_spawns",
		"mp_guardian_add_enemy_spawn_pt",
		"player_ping_token_cooldown",
		"sv_radio_throttle_window",
		"sv_playerradio_use_allowlist",
		"mp_hostages_spawn_force_positions_xyz",
		"nav_approach_points_area_size_threshold",
		"dev_break_after_count",
		"steaminput_glyph_style",
		"steaminput_glyph_solid",
		"steaminput_glyph_neutral",
		"+duck_notoggle",
		"-duck_notoggle",
		"+use_or_reload",
		"-use_or_reload",
		"toggle_speed",
		"dev_create_sensitivity_report",
		"move_stick_square_deadzone_forward",
		"move_stick_square_deadzone_strafe",
		"move_stick_circular_deadzone_min",
		"move_stick_circular_deadzone_max",
		"move_stick_response_curve",
		"move_stick_aggressive",
		"move_stick_aggression_strength",
		"move_stick_walk_zone",
		"move_touchpad_circular_deadzone_min",
		"move_touchpad_square_deadzone_strafe",
		"move_touchpad_square_deadzone_forward",
		"move_touchpad_sensitivity_strafe",
		"move_touchpad_sensitivity_forward",
		"aim_stick_invert_pitch",
		"aim_stick_invert_yaw",
		"aim_stick_circular_deadzone_min",
		"aim_stick_circular_deadzone_max",
		"aim_stick_square_deadzone_yaw",
		"aim_stick_square_deadzone_pitch",
		"aim_stick_response_curve",
		"aim_stick_rate_yaw",
		"aim_stick_rate_pitch",
		"aim_stick_extra_yaw",
		"aim_stick_extra_turning_ramp_up_time",
		"aim_stick_extra_turning_delay",
		"aim_stick_zoom_dampening_level1",
		"aim_stick_zoom_dampening_level2",
		"aim_flickstick_enabled",
		"aim_flickstick_circular_deadzone_min",
		"aim_flickstick_circular_deadzone_max",
		"aim_flickstick_flick_snap_mode",
		"aim_flickstick_forward_deadzone",
		"aim_flickstick_flick_tightness",
		"aim_flickstick_crank_tightness",
		"aim_flickstick_crank_sensitivity",
		"aim_flickstick_release_dampen_speed",
		"aim_gyro_enable_mode",
		"aim_gyro_siapi_convert_pixels_to_angles",
		"aim_gyro_siapi_sensitivity_setting",
		"aim_gyro_siapi_vertical_scale_setting",
		"aim_gyro_raw",
		"aim_gyro_conversion_mode",
		"aim_gyro_invert_pitch",
		"aim_gyro_invert_yaw",
		"aim_gyro_acceleration",
		"aim_gyro_low_sense_speed",
		"aim_gyro_base_sensitivity",
		"aim_gyro_high_sense_speed",
		"aim_gyro_high_sense_multiplier",
		"aim_gyro_precision_speed",
		"aim_gyro_circular_deadzone",
		"aim_gyro_square_deadzone_yaw",
		"aim_gyro_square_deadzone_pitch",
		"aim_gyro_pitchyaw_ratio",
		"aim_gyro_ray_angle",
		"aim_gyro_zoom_dampening_level1",
		"aim_gyro_zoom_dampening_level2",
		"aim_touchpad_circular_deadzone_min",
		"aim_touchpad_square_deadzone_yaw",
		"aim_touchpad_square_deadzone_pitch",
		"aim_touchpad_sensitivity_pitch",
		"aim_touchpad_sensitivity_yaw",
		"aim_touchpad_invert_pitch",
		"aim_touchpad_invert_yaw",
		"aim_touchpad_zoom_dampening_level1",
		"aim_touchpad_zoom_dampening_level2",
		"sc_say",
		"sc_say_team",
		"invnextgun",
		"invnextequipment",
		"show_untrusted_warning_again",
		"sv_hide_roundtime_until_seconds",
		"sv_fade_player_visibility_farz",
		"sv_ggprogressive_autosniper_first",
		"sv_ggprogressive_shotgun_last",
		"mp_technical_timeout_per_team",
		"mp_technical_timeout_duration_s",
		"mp_shorthanded_cash_bonus_round_delay",
		"mp_shorthanded_cash_bonus_ignore_kicked",
		"mp_ggprogressive_healthshot_killcount",
		"cash_team_bonus_shorthanded",
		"sv_shield_purchase_restricted_to",
		"cl_buywheel_donate_key",
		"cl_inventory_radial_immediate_select",
		"cl_inventory_radial_tap_to_cycle",
		"steaminput_firsttimepopup",
		"+quickbuyradial",
		"-quickbuyradial",
		"+quickgrenaderadial",
		"-quickgrenaderadial",
		"cl_quickinventory_filename",
		"+quickgearradial",
		"-quickgearradial",
		"cl_radial_radio_tab_0_text_1",
		"cl_radial_radio_tab_0_text_2",
		"cl_radial_radio_tab_0_text_3",
		"cl_radial_radio_tab_0_text_4",
		"cl_radial_radio_tab_0_text_5",
		"cl_radial_radio_tab_0_text_6",
		"cl_radial_radio_tab_0_text_7",
		"cl_radial_radio_tab_0_text_8",
		"cl_radial_radio_tab_1_text_1",
		"cl_radial_radio_tab_1_text_2",
		"cl_radial_radio_tab_1_text_3",
		"cl_radial_radio_tab_1_text_4",
		"cl_radial_radio_tab_1_text_5",
		"cl_radial_radio_tab_1_text_6",
		"cl_radial_radio_tab_1_text_7",
		"cl_radial_radio_tab_1_text_8",
		"cl_radial_radio_tab_2_text_1",
		"cl_radial_radio_tab_2_text_2",
		"cl_radial_radio_tab_2_text_3",
		"cl_radial_radio_tab_2_text_4",
		"cl_radial_radio_tab_2_text_5",
		"cl_radial_radio_tab_2_text_6",
		"cl_radial_radio_tab_2_text_7",
		"cl_radial_radio_tab_2_text_8",
		"cl_radial_radio_version_reset",
		"cl_radial_radio_tap_to_ping",
		"+radialradio",
		"-radialradio",
		"+radialradio2",
		"-radialradio2",
		"+radialradio3",
		"-radialradio3",
		"cl_radialmenu_deadzone_size_fraction",
		"cl_radialmenu_deadzone_size_joystick",
		"cl_radial_menu_icon_radius",
		"cl_radial_menu_tap_duration",
		"cl_radial_coyote_time",
		"mat_enable_uber_shaders_restart",
		"mat_enable_uber_shaders_optionsui",
		"steaminput_glyph_display_mode",
		"cl_ping_fade_deadzone",
		"cl_ping_fade_distance",
		"cl_disable_round_end_report",
		"mp_retake_t_count",
		"mp_retake_ct_count",
		"mp_retake_ct_loadout_default_pistol_round",
		"mp_retake_ct_loadout_upgraded_pistol_round",
		"mp_retake_ct_loadout_light_buy_round",
		"mp_retake_ct_loadout_full_buy_round",
		"mp_retake_ct_loadout_bonus_card_availability",
		"mp_retake_ct_loadout_bonus_card",
		"mp_retake_ct_loadout_enemy_card",
		"mp_retake_t_loadout_default_pistol_round",
		"mp_retake_t_loadout_upgraded_pistol_round",
		"mp_retake_t_loadout_light_buy_round",
		"mp_retake_t_loadout_full_buy_round",
		"mp_retake_t_loadout_bonus_card_availability",
		"mp_retake_t_loadout_bonus_card",
		"mp_retake_t_loadout_enemy_card",
		"mp_retake_max_consecutive_rounds_same_target_site",
		"cl_parachute_autodeploy",
		"mp_dronegun_stop",
		"player_competitive_maplist_8_10_0_857D14B5",
		"player_competitive_maplist_2v2_10_0_4BCBD8E9",
		"player_wargames_list2_10_0_E04",
		"player_survival_list_10_0_303",
		"csgo_watch_friend_session_exit_current",
		"cl_matchlist_controlroom_aid",
		"ui_playsettings_prime",
		"ui_playsettings_custom_preset",
		"ui_playsettings_flags_listen_scrimcomp2v2",
		"ui_playsettings_flags_listen_skirmish",
		"ui_playsettings_flags_listen_casual",
		"ui_playsettings_flags_listen_survival",
		"ui_playsettings_flags_listen_cooperative",
		"ui_playsettings_flags_listen_competitive",
		"ui_playsettings_flags_listen_deathmatch",
		"ui_playsettings_flags_official_scrimcomp2v2",
		"ui_playsettings_flags_official_skirmish",
		"ui_playsettings_flags_official_casual",
		"ui_playsettings_flags_official_survival",
		"ui_playsettings_flags_official_cooperative",
		"ui_playsettings_flags_official_competitive",
		"ui_playsettings_flags_official_deathmatch",
		"ui_playsettings_directchallengekey",
		"ui_show_unlock_competitive_alert",
		"ui_deepstats_toplevel_mode",
		"ui_deepstats_radio_heat_tab",
		"ui_deepstats_radio_heat_team",
		"ui_deepstats_radio_heat_figurine",
		"ui_show_subscription_alert",
		"ui_mainmenu_bkgnd_movie_CC4ECB9",
		"mp_guardian_bomb_plant_custom_x_mark_location",
		"sv_shield_bash_damage_to_players",
		"sv_shield_bash_damage_to_nonplayer",
		"cl_observed_bot_crosshair",
		"@panorama_canvas_force_soft_lines",
		"softshadow_alpha_min_z",
		"softshadow_alpha_max_z",
		"webapi_values_max_pool_size_mb",
		"webapi_values_init_buffer_size",
		"demo_index",
		"demo_index_max_other",
		"tv_playcast_showerrors",
		"tv_broadcast_preload_avatars_show",
		"tv_broadcast_preload_avatars_clear",
		"tv_broadcast_preload_avatars_add",
		"cfgver",
		"sv_max_allowed_developer",
		"sdr",
		"steaminput_status",
		"mat_enable_uber_shaders",
		"webapi_values_max_pool_size_mb",
		"webapi_values_init_buffer_size"
	};

	while (ToDelete.begin() != ToDelete.end()) {
		Delete(ToDelete.back());
		ToDelete.pop_back();
	}

	**(uint32_t**)(PatternScan(GetModuleHandleA("engine.dll"), "FF 35 ? ? ? ? 8D 4C 24 10") + 2) = 13764;

	DWORD dwOld;
	VirtualProtect((LPVOID)((uintptr_t)GetModuleHandleA("engine.dll") + 0x390c2dc), 0xC, 0x40, &dwOld);
	*(uint32_t*)((uintptr_t)GetModuleHandleA("engine.dll") + 0x390c2dc) = 1176;
	*(uint32_t*)((uintptr_t)GetModuleHandleA("engine.dll") + 0x390c2e4) = 1176;
	VirtualProtect((LPVOID)((uintptr_t)GetModuleHandleA("engine.dll") + 0x390c2dc), 0xC, dwOld, &dwOld);

	auto pFixBeta = (uintptr_t)PatternScan(GetModuleHandleA("client.dll"), "8B 45 10 83 C4 ? ? 44 ? ? 8B CF 89 ? ? 1C 50 ? 74 ? ? E8 ? ? ? ? 80 ? ? ? ? ? ? F3 0F ? ? ? ? ? ? F3 0F 59 ? ? ? ? ? ? 74");
	if (pFixBeta) {
		VirtualProtect((LPVOID)pFixBeta, 90, 0x40, &dwOld);
		*(uint8_t*)(pFixBeta + 86) = 0x90;
		*(uint8_t*)(pFixBeta + 87) = 0x90;
		VirtualProtect((LPVOID)pFixBeta, 90, dwOld, &dwOld);
	}

	auto pFixMenu = (uintptr_t)PatternScan(GetModuleHandleA("client.dll"), "89 44 24 4C 8B 11 8B 52 ? ? ? 84 C0 0F");
	if (pFixMenu) {
		VirtualProtect((LPVOID)pFixMenu, 90, 0x40, &dwOld);
		*(uint8_t*)(pFixMenu + 14) = 0x81;
		VirtualProtect((LPVOID)pFixMenu, 90, dwOld, &dwOld);
	}

	EngineClient->ExecuteClientCmd("setinfo sc_joystick_map 1");
	EngineClient->ExecuteClientCmd("setinfo sc_enable 1.0");
	EngineClient->ExecuteClientCmd("setinfo sc_pitch_sensitivity 1.0");
	EngineClient->ExecuteClientCmd("setinfo sc_pitch_sensitivity_default 1.0");
	EngineClient->ExecuteClientCmd("setinfo sc_yaw_sensitivity 1.0");
	EngineClient->ExecuteClientCmd("setinfo sc_yaw_sensitivity_default 1.0");
	EngineClient->ExecuteClientCmd("setinfo cl_accountprivacysetting1 1");
	EngineClient->ExecuteClientCmd("setinfo bot_show_patrol_areas 0");
	EngineClient->ExecuteClientCmd("setinfo ui_mainmenu_bkgnd_movie2 \"mutiny\"");
	EngineClient->ExecuteClientCmd("setinfo player_competitive_maplist_2v2_8_0_E8907D2E \"mg_de_train\"");
	EngineClient->ExecuteClientCmd("setinfo player_competitive_maplist_8_8_0_C51B3F85 \"mg_de_dust2\"");
	EngineClient->ExecuteClientCmd("setinfo player_wargames_list2_8_0_604 \"mg_skirmish_flyingscoutsman\"");
	EngineClient->ExecuteClientCmd("setinfo mp_coopmission_dz 0");
	EngineClient->ExecuteClientCmd("setinfo mp_coopmission_dz_use_bt 1");
	EngineClient->ExecuteClientCmd("setinfo cl_radialmenu_deadzone_size 0.04");
	EngineClient->ExecuteClientCmd("setinfo cl_mainmenu_show_datagraph ");
	EngineClient->ExecuteClientCmd("setinfo cl_filtertext_enabled 1");
	EngineClient->ExecuteClientCmd("setinfo cl_forcepreload 0");

	EngineClient->ExecuteClientCmd("tv_broadcast_server_info_message_size_kb 512");
	EngineClient->ExecuteClientCmd("sv_shield_hitpoints 650");
	EngineClient->ExecuteClientCmd("sv_shield_explosive_damage_mindist 250");
	EngineClient->ExecuteClientCmd("nav_selected_set_border_color \"100 100 0 255\"");
	EngineClient->ExecuteClientCmd("nav_selected_set_color \"255 255 200 96\"");
	EngineClient->ExecuteClientCmd("nav_area_bgcolor \"0 0 0 30\"");

	ConMsg("loaded\n");

	EngineClient->ExecuteClientCmd(("plugin_unload \"\""));

	//FreeLibraryAndExitThread((HMODULE)pBase, 1);
	return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE base, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		CreateThread(nullptr, 0, Main, base, 0, nullptr);
	}

	return TRUE;
}
