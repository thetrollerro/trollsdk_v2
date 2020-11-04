#pragma once

class i_client_networkable;

typedef i_client_networkable* ( *create_client_class_fn )( int ent_number, int serial_number );
typedef i_client_networkable* ( *create_event_fn )( );

/* includes */
#include <stdio.h>

#pragma warning(disable : 4514)

enum image_format {
	image_format_unknown = -1,
	image_format_rgba8888 = 0,
	image_format_abgr8888,
	image_format_rgb888,
	image_format_bgr888,
	image_format_rgb565,
	image_format_i8,
	image_format_ia88,
	image_format_p8,
	image_format_a8,
	image_format_rgb888_bluescreen,
	image_format_bgr888_bluescreen,
	image_format_argb8888,
	image_format_bgra8888,
	image_format_dxt1,
	image_format_dxt3,
	image_format_dxt5,
	image_format_bgrx8888,
	image_format_bgr565,
	image_format_bgrx5551,
	image_format_bgra4444,
	image_format_dxt1_onebitalpha,
	image_format_bgra5551,
	image_format_uv88,
	image_format_uvwq8888,
	image_format_rgba16161616f,
	image_format_rgba16161616,
	image_format_uvlx8888,
	image_format_r32f,
	image_format_rgb323232f,
	image_format_rgba32323232f,
	image_format_nv_dst16,
	image_format_nv_dst24,
	image_format_nv_intz,
	image_format_nv_rawz,
	image_format_ati_dst16,
	image_format_ati_dst24,
	image_format_nv_null,
	image_format_ati2n,
	image_format_ati1n,
	image_format_dxt1_runtime,
	image_format_dxt5_runtime,
	num_image_formats
};

enum class_id : int {
	class_id_ai_base_npc = 0,
	class_id_c_ak47,
	class_id_base_animating,
	class_id_base_animating_overlay,
	class_id_base_attributable_item,
	class_id_base_button,
	class_id_base_combat_character,
	class_id_base_combat_weapon,
	class_id_base_cs_grenade,
	class_id_base_cs_grenade_projectile,
	class_id_base_door,
	class_id_base_entity,
	class_id_base_flex,
	class_id_base_grenade,
	class_id_base_particle_entity,
	class_id_base_player,
	class_id_base_prop_door,
	class_id_base_team_objective_resource,
	class_id_base_temp_entity,
	class_id_base_toggle,
	class_id_base_trigger,
	class_id_base_view_model,
	class_id_base_physics_trigger,
	class_id_base_weapon_world_model,
	class_id_beam,
	class_id_beam_spot_light,
	class_id_bone_follower,
	class_id_br_c4_target,
	class_id_breach_charge,
	class_id_breach_charge_projectile,
	class_id_breakable_prop,
	class_id_breakable_surface,
	class_id_bump_mine,
	class_id_bump_mine_projectile,
	class_id_c_c4,
	class_id_cascade_light,
	class_id_chicken,
	class_id_color_correction,
	class_id_color_correctionv_olume,
	class_id_cs_game_rules_proxy,
	class_id_cs_player,
	class_id_cs_player_resource,
	class_id_cs_ragdoll,
	class_id_cs_team,
	class_id_danger_zone,
	class_id_danger_zone_controller,
	class_id_deagle,
	class_id_decoy_grenade,
	class_id_decoy_projectile,
	class_id_drone,
	class_id_drone_gun,
	class_id_dynamic_light,
	class_id_dynamic_prop,
	class_id_econ_entity,
	class_id_econ_wearable,
	class_id_embers,
	class_id_entity_dissolve,
	class_id_entity_flame,
	class_id_entity_freezing,
	class_id_entity_particletrail,
	class_id_env_ambient_light,
	class_id_env_detail_controller,
	class_id_env_dof_controller,
	class_id_env_gas_canister,
	class_id_env_particle_script,
	class_id_env_projected_texture,
	class_id_env_quadratic_beam,
	class_id_env_screen_effect,
	class_id_env_screen_overlay,
	class_id_env_tonemap_controller,
	class_id_env_wind,
	class_id_fe_player_decal,
	class_id_fire_cracker_blast,
	class_id_fire_smoke,
	class_id_fire_trail,
	class_id_fish,
	class_id_fists,
	class_id_flashbang,
	class_id_fog_controller,
	class_id_footstep_control,
	class_id_func_dust,
	class_id_func_lod,
	class_id_func_area_portal_window,
	class_id_func_brush,
	class_id_func_conveyor,
	class_id_func_ladder,
	class_id_func_monitor,
	class_id_func_move_linear,
	class_id_func_occluder,
	class_id_func_reflective_glass,
	class_id_func_rotating,
	class_id_func_smoke_volume,
	class_id_func_track_train,
	class_id_game_rules_proxy,
	class_id_grass_burn,
	class_id_handle_test,
	class_id_he_grenade,
	class_id_hostage,
	class_id_hostage_carriable_prop,
	class_id_incendiary_grenade,
	class_id_inferno,
	class_id_info_ladder_dismount,
	class_id_info_map_region,
	class_id_info_overlay_accessor,
	class_id_item_healthshot,
	class_id_item_cash,
	class_id_item_dogtags,
	class_id_knife,
	class_id_knife_gg,
	class_id_light_glow,
	class_id_material_modify_control,
	class_id_melee,
	class_id_molotov_grenade,
	class_id_molotov_projectile,
	class_id_movie_display,
	class_id_paradrop_chopper,
	class_id_particle_fire,
	class_id_particle_performance_monitor,
	class_id_particle_system,
	class_id_phys_box,
	class_id_phys_box_multiplayer,
	class_id_physics_prop,
	class_id_physics_prop_multiplayer,
	class_id_phys_magnet,
	class_id_phys_prop_ammo_box,
	class_id_phys_prop_loot_crate,
	class_id_phys_prop_radar_jammer,
	class_id_phys_prop_weapon_upgrade,
	class_id_planted_c4,
	class_id_plasma,
	class_id_player_ping,
	class_id_player_resource,
	class_id_point_camera,
	class_id_point_commentarynode,
	class_id_point_worldtext,
	class_id_pose_controller,
	class_id_post_process_controller,
	class_id_precipitation,
	class_id_precipitation_blocker,
	class_id_predicted_view_model,
	class_id_prop_hallucination,
	class_id_prop_counter,
	class_id_prop_door_rotating,
	class_id_prop_jeep,
	class_id_prop_vehicle_driveable,
	class_id_ragdoll_manager,
	class_id_ragdoll_prop,
	class_id_ragdoll_prop_attached,
	class_id_rope_key_frame,
	class_id_scar17,
	class_id_scene_entity,
	class_id_sensor_grenade,
	class_id_sensor_grenade_projectile,
	class_id_shadow_control,
	class_id_slideshow_display,
	class_id_smoke_grenade,
	class_id_smoke_grenade_projectile,
	class_id_smoke_stack,
	class_id_snowball,
	class_id_snowball_pile,
	class_id_snowball_projectile,
	class_id_spatial_entity,
	class_id_spotlight_end,
	class_id_sprite,
	class_id_sprite_oriented,
	class_id_sprite_trail,
	class_id_statue_prop,
	class_id_steam_jet,
	class_id_sun,
	class_id_sun_light_shadow_control,
	class_id_survival_spawn_chopper,
	class_id_tablet,
	class_id_team,
	class_id_team_play_round_based_rules_proxy,
	class_id_te_armor_ricochet,
	class_id_te_base_beam,
	class_id_te_beam_ent_point,
	class_id_te_beam_ents,
	class_id_te_beam_follow,
	class_id_te_beam_laser,
	class_id_te_beam_points,
	class_id_te_beam_ring,
	class_id_te_beam_ring_point,
	class_id_te_beam_spline,
	class_id_te_blood_sprite,
	class_id_te_blood_stream,
	class_id_te_break_model,
	class_id_te_bsp_decal,
	class_id_te_bubbles,
	class_id_te_bubble_trail,
	class_id_te_client_projectile,
	class_id_te_decal,
	class_id_te_dust,
	class_id_te_dynamic_light,
	class_id_te_effect_dispatch,
	class_id_te_energy_splash,
	class_id_te_explosion,
	class_id_te_fire_bullets,
	class_id_te_fizz,
	class_id_te_foot_print_decal,
	class_id_te_foundry_helpers,
	class_id_te_gauss_explosion,
	class_id_te_glow_sprite,
	class_id_te_impact,
	class_id_te_kill_player_attachments,
	class_id_te_large_funnel,
	class_id_te_metal_sparks,
	class_id_te_muzzle_flash,
	class_id_te_particle_system,
	class_id_te_physics_prop,
	class_id_te_plant_bomb,
	class_id_te_player_animevent,
	class_id_te_player_decal,
	class_id_te_projected_decal,
	class_id_te_radio_icon,
	class_id_te_shatter_surface,
	class_id_te_show_line,
	class_id_te_sla,
	class_id_te_smoke,
	class_id_te_sparks,
	class_id_te_sprite,
	class_id_te_sprite_spray,
	class_id_test_proxytoggle_networkable,
	class_id_testtraceline,
	class_id_teworlddecal,
	class_id_trigger_player_movement,
	class_id_trigger_sound_operator,
	class_id_vgui_screen,
	class_id_vote_controller,
	class_id_water_bullet,
	class_id_water_bod_control,
	class_id_weapon_aug,
	class_id_weapon_awp,
	class_id_weapon_base_item,
	class_id_weapon_bizon,
	class_id_weapon_cs_base,
	class_id_weapon_cs_base_gun,
	class_id_weapon_cycler,
	class_id_weapon_elite,
	class_id_weapon_famas,
	class_id_weapon_five_seven,
	class_id_weapon_g3sg1,
	class_id_weapon_galil,
	class_id_weapon_galil_ar,
	class_id_weapon_glock,
	class_id_weapon_hkp2000,
	class_id_weapon_m249,
	class_id_weapon_m3,
	class_id_weapon_m4a1,
	class_id_weapon_mac10,
	class_id_weapon_mag7,
	class_id_weapon_mp5_navy,
	class_id_weapon_mp7,
	class_id_weapon_mp9,
	class_id_weapon_negev,
	class_id_weapon_nova,
	class_id_weapon_p228,
	class_id_weapon_p250,
	class_id_weapon_p90,
	class_id_weapon_sawedoff,
	class_id_weapon_scar20,
	class_id_weapon_scout,
	class_id_weapon_sg550,
	class_id_weapon_sg552,
	class_id_weapon_sg556,
	class_id_weapon_shield,
	class_id_weapon_ssg08,
	class_id_weapon_taser,
	class_id_weapon_tec9,
	class_id_weapon_tmp,
	class_id_weapon_ump45,
	class_id_weapon_usp,
	class_id_weapon_xm1014,
	class_id_world,
	class_id_world_vgui_text,
	class_id_dust_trail,
	class_id_movie_explosion,
	class_id_particle_smoke_grenade,
	class_id_rocket_trail,
	class_id_smoke_trail,
	class_id_spore_explosion,
	class_id_spore_trail
};

class c_client_class {
public:
	create_client_class_fn create_fn;
	create_event_fn create_event_fn;
	char* network_name;
	recv_table* recvtable_ptr;
	c_client_class* next_ptr;
	class_id class_id;
};