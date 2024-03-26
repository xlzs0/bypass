#include "defines.h"
#include "addresses.h"
#include <fstream>

extern "C" __declspec(dllexport) c_plugin* __cdecl CreateInterface(const char* name, int32_t* ret) {
	static c_plugin plugin;

	if (!strcmp(name, "ISERVERPLUGINCALLBACKS001")) {
		if (ret)
			*ret = 0;

		return &plugin;
	}

	if (ret)
		*ret = 1;

	return NULL;
}

DWORD WINAPI main::thread(void* base) {
	while (!GetModuleHandleA("serverbrowser.dll"))
		SleepEx(1000, false);

	modules::initialize();
	interfaces::initialize();
	addresses::initialize();

	assign_address(protocol_version);
	assign_address(server_version);
	assign_address(client_version);
	assign_address(exe_build);
	assign_address_s(exe_build_fmt);
	assign_address_s(exe_build_version);

	if (game_original::server_version > 1400) {
		util::patch(addresses::net_graph_beta_check, 0x90, 2);
		util::patch(addresses::net_graph_connected_check, 0x81, 1);
	}
	
	if (addresses::cbuf_execute)
		util::patch(addresses::cbuf_execute_thread_check, 0x90, 51);

	std::vector<const char*> cvars_to_delete {
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
		"scoreboard_use_sf",
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

	for (const auto& name : cvars_to_delete)
		if (auto cvar = interfaces::convar->find_var(name); cvar)
			interfaces::convar->unregister_con_command(cvar);

	std::vector<std::pair<const char*, const char*>> cvars_to_create {
		std::make_pair("sc_joystick_map", "1"),
		std::make_pair("sc_enable", "1.0"),
		std::make_pair("sc_pitch_sensitivity", "1"),
		std::make_pair("sc_pitch_sensitivity_default", "1"),
		std::make_pair("sc_yaw_sensitivity", "1"),
		std::make_pair("sc_yaw_sensitivity_default", "1"),
		std::make_pair("cl_accountprivacysetting1", "1"),
		std::make_pair("cl_mainmenu_blog_file_cache", "blogfilecache.txt"),
		std::make_pair("cl_mainmenu_blog_file", "\"\""),
		std::make_pair("bot_show_patrol_areas", "0"),
		std::make_pair("ui_mainmenu_bkgnd_movie2", "mutiny"),
		std::make_pair("mp_coopmission_dz", "0"),
		std::make_pair("mp_coopmission_dz_use_bt", "1"),
		std::make_pair("cl_radialmenu_deadzone_size", "0.04"),
		std::make_pair("cl_mainmenu_show_datagraph", "\"\""),
		std::make_pair("cl_filtertext_enabled", "0"),
		std::make_pair("cl_forcepreload", "0"),
		std::make_pair("cl_thirdperson", "0"),
		std::make_pair("player_competitive_maplist_8_8_0_C51B3F85", "mg_de_dust2,mg_de_train,mg_de_inferno,mg_de_nuke,mg_de_vertigo,mg_de_mirage,mg_cs_office,mg_de_cache,mg_de_mutiny,mg_de_anubis,mg_de_swamp,mg_cs_agency,mg_de_overpass"),
		std::make_pair("player_competitive_maplist_2v2_8_0_E8907D2E", "mg_de_train,mg_de_lake,mg_de_inferno,mg_de_shortnuke,mg_de_vertigo,mg_gd_rialto,mg_de_shortdust,mg_de_overpass,mg_de_cbble"),
		std::make_pair("player_wargames_list2_8_0_604", "mg_skirmish_flyingscoutsman,mg_skirmish_armsrace,mg_skirmish_demolition"),
		std::make_pair("player_survival_list_8_0_3", "mg_dz_blacksite,mg_dz_sirocco"),
		std::make_pair("player_ping_throttle_decay", "0.58"),
		std::make_pair("debug_purchase_defidx", "\"\""),
		std::make_pair("ui_store_scaleform", "1"),
		std::make_pair("tr_completed_training", "0"),
		std::make_pair("tr_best_course_time", "0"),
		std::make_pair("weapon_accuracy_logging", "0"),
		std::make_pair("softshadow_a1", "128"),
		std::make_pair("softshadow_a2", "164"),
		std::make_pair("softshadow_a3", "255"),
		std::make_pair("bench_upload", "\"\""),
		std::make_pair("blackbox", "1"),
		std::make_pair("steam_controller_status", "\"\"")
	};

	for (const auto& [name, value] : cvars_to_create)
		interfaces::convar->create_cvar(name, value);

	std::vector<std::pair<const char*, const char*>> cvars_to_change {
		std::make_pair("tv_broadcast_server_info_message_size_kb", "512"),
		std::make_pair("sv_shield_hitpoints", "650"),
		std::make_pair("sv_shield_explosive_damage_mindist", "250"),
		std::make_pair("nav_selected_set_border_color", "100 100 0 255"),
		std::make_pair("nav_selected_set_color", "255 255 200 96"),
		std::make_pair("nav_area_bgcolor", "0 0 0 30"),
		std::make_pair("mp_endmatch_votenextmap_wargames_modes", "armsrace demolition flyingscoutsman"),
		std::make_pair("mp_drop_grenade_enable", "0"),
		std::make_pair("bot_coop_force_throw_grenade_chance", "0.7"),
		std::make_pair("steamworks_sessionid_lifetime_client", "8794908647456"),
		std::make_pair("@panorama_3dpanel_softshadow_camheight", "200.f"),
		std::make_pair("@panorama_3dpanel_softshadow_camfov", "20.f"),
		std::make_pair("softshadow_prt", "8.f"),
		std::make_pair("softshadow_frt", "4.f"),
		std::make_pair("softshadow_prd", "8.f"),
		std::make_pair("softshadow_frd", "7.f"),
		std::make_pair("softshadow_a0", "90"),
		std::make_pair("@panorama_3dpanel_softshadow_a", "0.95f"),
		std::make_pair("sv_temp_baseline_string_table_buffer_size", "262144"),
		std::make_pair("mem_max_heapsize", "512")
	};

	for (const auto& [name, value] : cvars_to_change)
		if (auto cvar = interfaces::convar->find_var(name); cvar)
			cvar->set_value(value);
	
	ExitThread(TRUE);
}

void main::shutdown() {
	restore_address(protocol_version);
	restore_address(server_version);
	restore_address(client_version);
	restore_address(exe_build);
	restore_address_s(exe_build_fmt);
	restore_address_s(exe_build_version);

	if (game_original::server_version > 1400) {
		if (addresses::net_graph_beta_check) {
			util::patch(addresses::net_graph_beta_check, 0x74, 1);
			util::patch(reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(addresses::net_graph_beta_check) + 1), 0x7, 1);
		}

		util::patch(addresses::net_graph_connected_check, 0x85, 1);
	}
}

BOOL WINAPI DllMain(HINSTANCE base, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(static_cast<HMODULE>(base));
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(main::thread), base, NULL, nullptr);
	}

	return TRUE;
}