#pragma once
#include "c_base_combat_weapon.hpp"
#include "../interfaces/interfaces.hpp"
#include "i_client_entity.hpp"
#include "c_base_handle.hpp"
#include "../../utilities/math/math.hpp"
#include "c_base_entity.hpp"

class c_base_player;

enum data_update_type_t {
	data_update_created = 0,
	data_update_datatable_changed,
};

enum client_frame_stage_t {
	frame_undefined = -1,
	frame_start,
	frame_net_update_start,
	frame_net_update_postdataupdate_start,
	frame_net_update_postdataupdate_end,
	frame_net_update_end,
	frame_render_start,
	frame_render_end
};

enum move_type {
	movetype_none = 0,
	movetype_isometric,
	movetype_walk,
	movetype_step,
	movetype_fly,
	movetype_flygravity,
	movetype_vphysics,
	movetype_push,
	movetype_noclip,
	movetype_ladder,
	movetype_observer,
	movetype_custom,
	movetype_last = movetype_custom,
	movetype_max_bits = 4,
	max_movetype
};

enum entity_activities : int {
	act_invalid = -1,
	act_reset = 0,
	act_idle = 1,
	act_transition = 2,
	act_cover = 3,
	act_cover_med = 4,
	act_cover_low = 5,
	act_walk = 6,
	act_walk_aim = 7,
	act_walk_crouch = 8,
	act_walk_crouch_aim = 9,
	act_run = 10,
	act_run_aim = 11,
	act_run_crouch = 12,
	act_run_crouch_aim = 13,
	act_run_protected = 14,
	act_script_custom_move = 15,
	act_range_attack1 = 16,
	act_range_attack2 = 17,
	act_range_attack1_low = 18,
	act_range_attack2_low = 19,
	act_diesimple = 20,
	act_diebackward = 21,
	act_dieforward = 22,
	act_dieviolent = 23,
	act_dieragdoll = 24,
	act_fly = 25,
	act_hover = 26,
	act_glide = 27,
	act_swim = 28,
	act_jump = 29,
	act_hop = 30,
	act_leap = 31,
	act_land = 32,
	act_climb_up = 33,
	act_climb_down = 34,
	act_climb_dismount = 35,
	act_shipladder_up = 36,
	act_shipladder_down = 37,
	act_strafe_left = 38,
	act_strafe_right = 39,
	act_roll_left = 40,
	act_roll_right = 41,
	act_turn_left = 42,
	act_turn_right = 43,
	act_crouch = 44,
	act_crouchidle = 45,
	act_stand = 46,
	act_use = 47,
	act_alien_burrow_idle = 48,
	act_alien_burrow_out = 49,
	act_signal1 = 50,
	act_signal2 = 51,
	act_signal3 = 52,
	act_signal_advance = 53,
	act_signal_forward = 54,
	act_signal_group = 55,
	act_signal_halt = 56,
	act_signal_left = 57,
	act_signal_right = 58,
	act_signal_takecover = 59,
	act_lookback_right = 60,
	act_lookback_left = 61,
	act_cower = 62,
	act_small_flinch = 63,
	act_big_flinch = 64,
	act_melee_attack1 = 65,
	act_melee_attack2 = 66,
	act_reload = 67,
	act_reload_start = 68,
	act_reload_finish = 69,
	act_reload_low = 70,
	act_arm = 71,
	act_disarm = 72,
	act_drop_weapon = 73,
	act_drop_weapon_shotgun = 74,
	act_pickup_ground = 75,
	act_pickup_rack = 76,
	act_idle_angry = 77,
	act_idle_relaxed = 78,
	act_idle_stimulated = 79,
	act_idle_agitated = 80,
	act_idle_stealth = 81,
	act_idle_hurt = 82,
	act_walk_relaxed = 83,
	act_walk_stimulated = 84,
	act_walk_agitated = 85,
	act_walk_stealth = 86,
	act_run_relaxed = 87,
	act_run_stimulated = 88,
	act_run_agitated = 89,
	act_run_stealth = 90,
	act_idle_aim_relaxed = 91,
	act_idle_aim_stimulated = 92,
	act_idle_aim_agitated = 93,
	act_idle_aim_stealth = 94,
	act_walk_aim_relaxed = 95,
	act_walk_aim_stimulated = 96,
	act_walk_aim_agitated = 97,
	act_walk_aim_stealth = 98,
	act_run_aim_relaxed = 99,
	act_run_aim_stimulated = 100,
	act_run_aim_agitated = 101,
	act_run_aim_stealth = 102,
	act_crouchidle_stimulated = 103,
	act_crouchidle_aim_stimulated = 104,
	act_crouchidle_agitated = 105,
	act_walk_hurt = 106,
	act_run_hurt = 107,
	act_special_attack1 = 108,
	act_special_attack2 = 109,
	act_combat_idle = 110,
	act_walk_scared = 111,
	act_run_scared = 112,
	act_victory_dance = 113,
	act_die_headshot = 114,
	act_die_chestshot = 115,
	act_die_gutshot = 116,
	act_die_backshot = 117,
	act_flinch_head = 118,
	act_flinch_chest = 119,
	act_flinch_stomach = 120,
	act_flinch_leftarm = 121,
	act_flinch_rightarm = 122,
	act_flinch_leftleg = 123,
	act_flinch_rightleg = 124,
	act_flinch_physics = 125,
	act_flinch_head_back = 126,
	act_flinch_head_left = 127,
	act_flinch_head_right = 128,
	act_flinch_chest_back = 129,
	act_flinch_stomach_back = 130,
	act_flinch_crouch_front = 131,
	act_flinch_crouch_back = 132,
	act_flinch_crouch_left = 133,
	act_flinch_crouch_right = 134,
	act_idle_on_fire = 135,
	act_walk_on_fire = 136,
	act_run_on_fire = 137,
	act_rappel_loop = 138,
	act_180_left = 139,
	act_180_right = 140,
	act_90_left = 141,
	act_90_right = 142,
	act_step_left = 143,
	act_step_right = 144,
	act_step_back = 145,
	act_step_fore = 146,
	act_gesture_range_attack1 = 147,
	act_gesture_range_attack2 = 148,
	act_gesture_melee_attack1 = 149,
	act_gesture_melee_attack2 = 150,
	act_gesture_range_attack1_low = 151,
	act_gesture_range_attack2_low = 152,
	act_melee_attack_swing_gesture = 153,
	act_gesture_small_flinch = 154,
	act_gesture_big_flinch = 155,
	act_gesture_flinch_blast = 156,
	act_gesture_flinch_blast_shotgun = 157,
	act_gesture_flinch_blast_damaged = 158,
	act_gesture_flinch_blast_damaged_shotgun = 159,
	act_gesture_flinch_head = 160,
	act_gesture_flinch_chest = 161,
	act_gesture_flinch_stomach = 162,
	act_gesture_flinch_leftarm = 163,
	act_gesture_flinch_rightarm = 164,
	act_gesture_flinch_leftleg = 165,
	act_gesture_flinch_rightleg = 166,
	act_gesture_turn_left = 167,
	act_gesture_turn_right = 168,
	act_gesture_turn_left45 = 169,
	act_gesture_turn_right45 = 170,
	act_gesture_turn_left90 = 171,
	act_gesture_turn_right90 = 172,
	act_gesture_turn_left45_flat = 173,
	act_gesture_turn_right45_flat = 174,
	act_gesture_turn_left90_flat = 175,
	act_gesture_turn_right90_flat = 176,
	act_barnacle_hit = 177,
	act_barnacle_pull = 178,
	act_barnacle_chomp = 179,
	act_barnacle_chew = 180,
	act_do_not_disturb = 181,
	act_specific_sequence = 182,
	act_vm_draw = 183,
	act_vm_holster = 184,
	act_vm_idle = 185,
	act_vm_fidget = 186,
	act_vm_pullback = 187,
	act_vm_pullback_high = 188,
	act_vm_pullback_low = 189,
	act_vm_throw = 190,
	act_vm_pullpin = 191,
	act_vm_primaryattack = 192,
	act_vm_secondaryattack = 193,
	act_vm_reload = 194,
	act_vm_dryfire = 195,
	act_vm_hitleft = 196,
	act_vm_hitleft2 = 197,
	act_vm_hitright = 198,
	act_vm_hitright2 = 199,
	act_vm_hitcenter = 200,
	act_vm_hitcenter2 = 201,
	act_vm_missleft = 202,
	act_vm_missleft2 = 203,
	act_vm_missright = 204,
	act_vm_missright2 = 205,
	act_vm_misscenter = 206,
	act_vm_misscenter2 = 207,
	act_vm_haulback = 208,
	act_vm_swinghard = 209,
	act_vm_swingmiss = 210,
	act_vm_swinghit = 211,
	act_vm_idle_to_lowered = 212,
	act_vm_idle_lowered = 213,
	act_vm_lowered_to_idle = 214,
	act_vm_recoil1 = 215,
	act_vm_recoil2 = 216,
	act_vm_recoil3 = 217,
	act_vm_pickup = 218,
	act_vm_release = 219,
	act_vm_attach_silencer = 220,
	act_vm_detach_silencer = 221,
	act_vm_empty_fire = 222,
	act_vm_empty_reload = 223,
	act_vm_empty_draw = 224,
	act_vm_empty_idle = 225,
	act_slam_stickwall_idle = 226,
	act_slam_stickwall_nd_idle = 227,
	act_slam_stickwall_attach = 228,
	act_slam_stickwall_attach2 = 229,
	act_slam_stickwall_nd_attach = 230,
	act_slam_stickwall_nd_attach2 = 231,
	act_slam_stickwall_detonate = 232,
	act_slam_stickwall_detonator_holster = 233,
	act_slam_stickwall_draw = 234,
	act_slam_stickwall_nd_draw = 235,
	act_slam_stickwall_to_throw = 236,
	act_slam_stickwall_to_throw_nd = 237,
	act_slam_stickwall_to_tripmine_nd = 238,
	act_slam_throw_idle = 239,
	act_slam_throw_nd_idle = 240,
	act_slam_throw_throw = 241,
	act_slam_throw_throw2 = 242,
	act_slam_throw_throw_nd = 243,
	act_slam_throw_throw_nd2 = 244,
	act_slam_throw_draw = 245,
	act_slam_throw_nd_draw = 246,
	act_slam_throw_to_stickwall = 247,
	act_slam_throw_to_stickwall_nd = 248,
	act_slam_throw_detonate = 249,
	act_slam_throw_detonator_holster = 250,
	act_slam_throw_to_tripmine_nd = 251,
	act_slam_tripmine_idle = 252,
	act_slam_tripmine_draw = 253,
	act_slam_tripmine_attach = 254,
	act_slam_tripmine_attach2 = 255,
	act_slam_tripmine_to_stickwall_nd = 256,
	act_slam_tripmine_to_throw_nd = 257,
	act_slam_detonator_idle = 258,
	act_slam_detonator_draw = 259,
	act_slam_detonator_detonate = 260,
	act_slam_detonator_holster = 261,
	act_slam_detonator_stickwall_draw = 262,
	act_slam_detonator_throw_draw = 263,
	act_shotgun_reload_start = 264,
	act_shotgun_reload_finish = 265,
	act_shotgun_pump = 266,
	act_smg2_idle2 = 267,
	act_smg2_fire2 = 268,
	act_smg2_draw2 = 269,
	act_smg2_reload2 = 270,
	act_smg2_dryfire2 = 271,
	act_smg2_toauto = 272,
	act_smg2_toburst = 273,
	act_physcannon_upgrade = 274,
	act_range_attack_ar1 = 275,
	act_range_attack_ar2 = 276,
	act_range_attack_ar2_low = 277,
	act_range_attack_ar2_grenade = 278,
	act_range_attack_hmg1 = 279,
	act_range_attack_ml = 280,
	act_range_attack_smg1 = 281,
	act_range_attack_smg1_low = 282,
	act_range_attack_smg2 = 283,
	act_range_attack_shotgun = 284,
	act_range_attack_shotgun_low = 285,
	act_range_attack_pistol = 286,
	act_range_attack_pistol_low = 287,
	act_range_attack_slam = 288,
	act_range_attack_tripwire = 289,
	act_range_attack_throw = 290,
	act_range_attack_sniper_rifle = 291,
	act_range_attack_rpg = 292,
	act_melee_attack_swing = 293,
	act_range_aim_low = 294,
	act_range_aim_smg1_low = 295,
	act_range_aim_pistol_low = 296,
	act_range_aim_ar2_low = 297,
	act_cover_pistol_low = 298,
	act_cover_smg1_low = 299,
	act_gesture_range_attack_ar1 = 300,
	act_gesture_range_attack_ar2 = 301,
	act_gesture_range_attack_ar2_grenade = 302,
	act_gesture_range_attack_hmg1 = 303,
	act_gesture_range_attack_ml = 304,
	act_gesture_range_attack_smg1 = 305,
	act_gesture_range_attack_smg1_low = 306,
	act_gesture_range_attack_smg2 = 307,
	act_gesture_range_attack_shotgun = 308,
	act_gesture_range_attack_pistol = 309,
	act_gesture_range_attack_pistol_low = 310,
	act_gesture_range_attack_slam = 311,
	act_gesture_range_attack_tripwire = 312,
	act_gesture_range_attack_throw = 313,
	act_gesture_range_attack_sniper_rifle = 314,
	act_gesture_melee_attack_swing = 315,
	act_idle_rifle = 316,
	act_idle_smg1 = 317,
	act_idle_angry_smg1 = 318,
	act_idle_pistol = 319,
	act_idle_angry_pistol = 320,
	act_idle_angry_shotgun = 321,
	act_idle_stealth_pistol = 322,
	act_idle_package = 323,
	act_walk_package = 324,
	act_idle_suitcase = 325,
	act_walk_suitcase = 326,
	act_idle_smg1_relaxed = 327,
	act_idle_smg1_stimulated = 328,
	act_walk_rifle_relaxed = 329,
	act_run_rifle_relaxed = 330,
	act_walk_rifle_stimulated = 331,
	act_run_rifle_stimulated = 332,
	act_idle_aim_rifle_stimulated = 333,
	act_walk_aim_rifle_stimulated = 334,
	act_run_aim_rifle_stimulated = 335,
	act_idle_shotgun_relaxed = 336,
	act_idle_shotgun_stimulated = 337,
	act_idle_shotgun_agitated = 338,
	act_walk_angry = 339,
	act_police_harass1 = 340,
	act_police_harass2 = 341,
	act_idle_mannedgun = 342,
	act_idle_melee = 343,
	act_idle_angry_melee = 344,
	act_idle_rpg_relaxed = 345,
	act_idle_rpg = 346,
	act_idle_angry_rpg = 347,
	act_cover_low_rpg = 348,
	act_walk_rpg = 349,
	act_run_rpg = 350,
	act_walk_crouch_rpg = 351,
	act_run_crouch_rpg = 352,
	act_walk_rpg_relaxed = 353,
	act_run_rpg_relaxed = 354,
	act_walk_rifle = 355,
	act_walk_aim_rifle = 356,
	act_walk_crouch_rifle = 357,
	act_walk_crouch_aim_rifle = 358,
	act_run_rifle = 359,
	act_run_aim_rifle = 360,
	act_run_crouch_rifle = 361,
	act_run_crouch_aim_rifle = 362,
	act_run_stealth_pistol = 363,
	act_walk_aim_shotgun = 364,
	act_run_aim_shotgun = 365,
	act_walk_pistol = 366,
	act_run_pistol = 367,
	act_walk_aim_pistol = 368,
	act_run_aim_pistol = 369,
	act_walk_stealth_pistol = 370,
	act_walk_aim_stealth_pistol = 371,
	act_run_aim_stealth_pistol = 372,
	act_reload_pistol = 373,
	act_reload_pistol_low = 374,
	act_reload_smg1 = 375,
	act_reload_smg1_low = 376,
	act_reload_shotgun = 377,
	act_reload_shotgun_low = 378,
	act_gesture_reload = 379,
	act_gesture_reload_pistol = 380,
	act_gesture_reload_smg1 = 381,
	act_gesture_reload_shotgun = 382,
	act_busy_lean_left = 383,
	act_busy_lean_left_entry = 384,
	act_busy_lean_left_exit = 385,
	act_busy_lean_back = 386,
	act_busy_lean_back_entry = 387,
	act_busy_lean_back_exit = 388,
	act_busy_sit_ground = 389,
	act_busy_sit_ground_entry = 390,
	act_busy_sit_ground_exit = 391,
	act_busy_sit_chair = 392,
	act_busy_sit_chair_entry = 393,
	act_busy_sit_chair_exit = 394,
	act_busy_stand = 395,
	act_busy_queue = 396,
	act_duck_dodge = 397,
	act_die_barnacle_swallow = 398,
	act_gesture_barnacle_strangle = 399,
	act_physcannon_detach = 400,
	act_physcannon_animate = 401,
	act_physcannon_animate_pre = 402,
	act_physcannon_animate_post = 403,
	act_die_frontside = 404,
	act_die_rightside = 405,
	act_die_backside = 406,
	act_die_leftside = 407,
	act_die_crouch_frontside = 408,
	act_die_crouch_rightside = 409,
	act_die_crouch_backside = 410,
	act_die_crouch_leftside = 411,
	act_open_door = 412,
	act_di_alyx_zombie_melee = 413,
	act_di_alyx_zombie_torso_melee = 414,
	act_di_alyx_headcrab_melee = 415,
	act_di_alyx_antlion = 416,
	act_di_alyx_zombie_shotgun64 = 417,
	act_di_alyx_zombie_shotgun26 = 418,
	act_readiness_relaxed_to_stimulated = 419,
	act_readiness_relaxed_to_stimulated_walk = 420,
	act_readiness_agitated_to_stimulated = 421,
	act_readiness_stimulated_to_relaxed = 422,
	act_readiness_pistol_relaxed_to_stimulated = 423,
	act_readiness_pistol_relaxed_to_stimulated_walk = 424,
	act_readiness_pistol_agitated_to_stimulated = 425,
	act_readiness_pistol_stimulated_to_relaxed = 426,
	act_idle_carry = 427,
	act_walk_carry = 428,
	act_startdying = 429,
	act_dyingloop = 430,
	act_dyingtodead = 431,
	act_ride_manned_gun = 432,
	act_vm_sprint_enter = 433,
	act_vm_sprint_idle = 434,
	act_vm_sprint_leave = 435,
	act_fire_start = 436,
	act_fire_loop = 437,
	act_fire_end = 438,
	act_crouching_grenadeidle = 439,
	act_crouching_grenadeready = 440,
	act_crouching_primaryattack = 441,
	act_overlay_grenadeidle = 442,
	act_overlay_grenadeready = 443,
	act_overlay_primaryattack = 444,
	act_overlay_shield_up = 445,
	act_overlay_shield_down = 446,
	act_overlay_shield_up_idle = 447,
	act_overlay_shield_attack = 448,
	act_overlay_shield_knockback = 449,
	act_shield_up = 450,
	act_shield_down = 451,
	act_shield_up_idle = 452,
	act_shield_attack = 453,
	act_shield_knockback = 454,
	act_crouching_shield_up = 455,
	act_crouching_shield_down = 456,
	act_crouching_shield_up_idle = 457,
	act_crouching_shield_attack = 458,
	act_crouching_shield_knockback = 459,
	act_turnright45 = 460,
	act_turnleft45 = 461,
	act_turn = 462,
	act_obj_assembling = 463,
	act_obj_dismantling = 464,
	act_obj_startup = 465,
	act_obj_running = 466,
	act_obj_idle = 467,
	act_obj_placing = 468,
	act_obj_deteriorating = 469,
	act_obj_upgrading = 470,
	act_deploy = 471,
	act_deploy_idle = 472,
	act_undeploy = 473,
	act_crossbow_draw_unloaded = 474,
	act_gauss_spinup = 475,
	act_gauss_spincycle = 476,
	act_vm_primaryattack_silenced = 477,
	act_vm_reload_silenced = 478,
	act_vm_dryfire_silenced = 479,
	act_vm_idle_silenced = 480,
	act_vm_draw_silenced = 481,
	act_vm_idle_empty_left = 482,
	act_vm_dryfire_left = 483,
	act_vm_is_draw = 484,
	act_vm_is_holster = 485,
	act_vm_is_idle = 486,
	act_vm_is_primaryattack = 487,
	act_player_idle_fire = 488,
	act_player_crouch_fire = 489,
	act_player_crouch_walk_fire = 490,
	act_player_walk_fire = 491,
	act_player_run_fire = 492,
	act_idletorun = 493,
	act_runtoidle = 494,
	act_vm_draw_deployed = 495,
	act_hl2mp_idle_melee = 496,
	act_hl2mp_run_melee = 497,
	act_hl2mp_idle_crouch_melee = 498,
	act_hl2mp_walk_crouch_melee = 499,
	act_hl2mp_gesture_range_attack_melee = 500,
	act_hl2mp_gesture_reload_melee = 501,
	act_hl2mp_jump_melee = 502,
	act_vm_fizzle = 503,
	act_mp_stand_idle = 504,
	act_mp_crouch_idle = 505,
	act_mp_crouch_deployed_idle = 506,
	act_mp_crouch_deployed = 507,
	act_mp_deployed_idle = 508,
	act_mp_run = 509,
	act_mp_walk = 510,
	act_mp_airwalk = 511,
	act_mp_crouchwalk = 512,
	act_mp_sprint = 513,
	act_mp_jump = 514,
	act_mp_jump_start = 515,
	act_mp_jump_float = 516,
	act_mp_jump_land = 517,
	act_mp_jump_impact_n = 518,
	act_mp_jump_impact_e = 519,
	act_mp_jump_impact_w = 520,
	act_mp_jump_impact_s = 521,
	act_mp_jump_impact_top = 522,
	act_mp_doublejump = 523,
	act_mp_swim = 524,
	act_mp_deployed = 525,
	act_mp_swim_deployed = 526,
	act_mp_vcd = 527,
	act_mp_attack_stand_primaryfire = 528,
	act_mp_attack_stand_primaryfire_deployed = 529,
	act_mp_attack_stand_secondaryfire = 530,
	act_mp_attack_stand_grenade = 531,
	act_mp_attack_crouch_primaryfire = 532,
	act_mp_attack_crouch_primaryfire_deployed = 533,
	act_mp_attack_crouch_secondaryfire = 534,
	act_mp_attack_crouch_grenade = 535,
	act_mp_attack_swim_primaryfire = 536,
	act_mp_attack_swim_secondaryfire = 537,
	act_mp_attack_swim_grenade = 538,
	act_mp_attack_airwalk_primaryfire = 539,
	act_mp_attack_airwalk_secondaryfire = 540,
	act_mp_attack_airwalk_grenade = 541,
	act_mp_reload_stand = 542,
	act_mp_reload_stand_loop = 543,
	act_mp_reload_stand_end = 544,
	act_mp_reload_crouch = 545,
	act_mp_reload_crouch_loop = 546,
	act_mp_reload_crouch_end = 547,
	act_mp_reload_swim = 548,
	act_mp_reload_swim_loop = 549,
	act_mp_reload_swim_end = 550,
	act_mp_reload_airwalk = 551,
	act_mp_reload_airwalk_loop = 552,
	act_mp_reload_airwalk_end = 553,
	act_mp_attack_stand_prefire = 554,
	act_mp_attack_stand_postfire = 555,
	act_mp_attack_stand_startfire = 556,
	act_mp_attack_crouch_prefire = 557,
	act_mp_attack_crouch_postfire = 558,
	act_mp_attack_swim_prefire = 559,
	act_mp_attack_swim_postfire = 560,
	act_mp_stand_primary = 561,
	act_mp_crouch_primary = 562,
	act_mp_run_primary = 563,
	act_mp_walk_primary = 564,
	act_mp_airwalk_primary = 565,
	act_mp_crouchwalk_primary = 566,
	act_mp_jump_primary = 567,
	act_mp_jump_start_primary = 568,
	act_mp_jump_float_primary = 569,
	act_mp_jump_land_primary = 570,
	act_mp_swim_primary = 571,
	act_mp_deployed_primary = 572,
	act_mp_swim_deployed_primary = 573,
	act_mp_attack_stand_primary = 574,
	act_mp_attack_stand_primary_deployed = 575,
	act_mp_attack_crouch_primary = 576,
	act_mp_attack_crouch_primary_deployed = 577,
	act_mp_attack_swim_primary = 578,
	act_mp_attack_airwalk_primary = 579,
	act_mp_reload_stand_primary = 580,
	act_mp_reload_stand_primary_loop = 581,
	act_mp_reload_stand_primary_end = 582,
	act_mp_reload_crouch_primary = 583,
	act_mp_reload_crouch_primary_loop = 584,
	act_mp_reload_crouch_primary_end = 585,
	act_mp_reload_swim_primary = 586,
	act_mp_reload_swim_primary_loop = 587,
	act_mp_reload_swim_primary_end = 588,
	act_mp_reload_airwalk_primary = 589,
	act_mp_reload_airwalk_primary_loop = 590,
	act_mp_reload_airwalk_primary_end = 591,
	act_mp_attack_stand_grenade_primary = 592,
	act_mp_attack_crouch_grenade_primary = 593,
	act_mp_attack_swim_grenade_primary = 594,
	act_mp_attack_airwalk_grenade_primary = 595,
	act_mp_stand_secondary = 596,
	act_mp_crouch_secondary = 597,
	act_mp_run_secondary = 598,
	act_mp_walk_secondary = 599,
	act_mp_airwalk_secondary = 600,
	act_mp_crouchwalk_secondary = 601,
	act_mp_jump_secondary = 602,
	act_mp_jump_start_secondary = 603,
	act_mp_jump_float_secondary = 604,
	act_mp_jump_land_secondary = 605,
	act_mp_swim_secondary = 606,
	act_mp_attack_stand_secondary = 607,
	act_mp_attack_crouch_secondary = 608,
	act_mp_attack_swim_secondary = 609,
	act_mp_attack_airwalk_secondary = 610,
	act_mp_reload_stand_secondary = 611,
	act_mp_reload_stand_secondary_loop = 612,
	act_mp_reload_stand_secondary_end = 613,
	act_mp_reload_crouch_secondary = 614,
	act_mp_reload_crouch_secondary_loop = 615,
	act_mp_reload_crouch_secondary_end = 616,
	act_mp_reload_swim_secondary = 617,
	act_mp_reload_swim_secondary_loop = 618,
	act_mp_reload_swim_secondary_end = 619,
	act_mp_reload_airwalk_secondary = 620,
	act_mp_reload_airwalk_secondary_loop = 621,
	act_mp_reload_airwalk_secondary_end = 622,
	act_mp_attack_stand_grenade_secondary = 623,
	act_mp_attack_crouch_grenade_secondary = 624,
	act_mp_attack_swim_grenade_secondary = 625,
	act_mp_attack_airwalk_grenade_secondary = 626,
	act_mp_stand_melee = 627,
	act_mp_crouch_melee = 628,
	act_mp_run_melee = 629,
	act_mp_walk_melee = 630,
	act_mp_airwalk_melee = 631,
	act_mp_crouchwalk_melee = 632,
	act_mp_jump_melee = 633,
	act_mp_jump_start_melee = 634,
	act_mp_jump_float_melee = 635,
	act_mp_jump_land_melee = 636,
	act_mp_swim_melee = 637,
	act_mp_attack_stand_melee = 638,
	act_mp_attack_stand_melee_secondary = 639,
	act_mp_attack_crouch_melee = 640,
	act_mp_attack_crouch_melee_secondary = 641,
	act_mp_attack_swim_melee = 642,
	act_mp_attack_airwalk_melee = 643,
	act_mp_attack_stand_grenade_melee = 644,
	act_mp_attack_crouch_grenade_melee = 645,
	act_mp_attack_swim_grenade_melee = 646,
	act_mp_attack_airwalk_grenade_melee = 647,
	act_mp_stand_item1 = 648,
	act_mp_crouch_item1 = 649,
	act_mp_run_item1 = 650,
	act_mp_walk_item1 = 651,
	act_mp_airwalk_item1 = 652,
	act_mp_crouchwalk_item1 = 653,
	act_mp_jump_item1 = 654,
	act_mp_jump_start_item1 = 655,
	act_mp_jump_float_item1 = 656,
	act_mp_jump_land_item1 = 657,
	act_mp_swim_item1 = 658,
	act_mp_attack_stand_item1 = 659,
	act_mp_attack_stand_item1_secondary = 660,
	act_mp_attack_crouch_item1 = 661,
	act_mp_attack_crouch_item1_secondary = 662,
	act_mp_attack_swim_item1 = 663,
	act_mp_attack_airwalk_item1 = 664,
	act_mp_stand_item2 = 665,
	act_mp_crouch_item2 = 666,
	act_mp_run_item2 = 667,
	act_mp_walk_item2 = 668,
	act_mp_airwalk_item2 = 669,
	act_mp_crouchwalk_item2 = 670,
	act_mp_jump_item2 = 671,
	act_mp_jump_start_item2 = 672,
	act_mp_jump_float_item2 = 673,
	act_mp_jump_land_item2 = 674,
	act_mp_swim_item2 = 675,
	act_mp_attack_stand_item2 = 676,
	act_mp_attack_stand_item2_secondary = 677,
	act_mp_attack_crouch_item2 = 678,
	act_mp_attack_crouch_item2_secondary = 679,
	act_mp_attack_swim_item2 = 680,
	act_mp_attack_airwalk_item2 = 681,
	act_mp_gesture_flinch = 682,
	act_mp_gesture_flinch_primary = 683,
	act_mp_gesture_flinch_secondary = 684,
	act_mp_gesture_flinch_melee = 685,
	act_mp_gesture_flinch_item1 = 686,
	act_mp_gesture_flinch_item2 = 687,
	act_mp_gesture_flinch_head = 688,
	act_mp_gesture_flinch_chest = 689,
	act_mp_gesture_flinch_stomach = 690,
	act_mp_gesture_flinch_leftarm = 691,
	act_mp_gesture_flinch_rightarm = 692,
	act_mp_gesture_flinch_leftleg = 693,
	act_mp_gesture_flinch_rightleg = 694,
	act_mp_grenade1_draw = 695,
	act_mp_grenade1_idle = 696,
	act_mp_grenade1_attack = 697,
	act_mp_grenade2_draw = 698,
	act_mp_grenade2_idle = 699,
	act_mp_grenade2_attack = 700,
	act_mp_primary_grenade1_draw = 701,
	act_mp_primary_grenade1_idle = 702,
	act_mp_primary_grenade1_attack = 703,
	act_mp_primary_grenade2_draw = 704,
	act_mp_primary_grenade2_idle = 705,
	act_mp_primary_grenade2_attack = 706,
	act_mp_secondary_grenade1_draw = 707,
	act_mp_secondary_grenade1_idle = 708,
	act_mp_secondary_grenade1_attack = 709,
	act_mp_secondary_grenade2_draw = 710,
	act_mp_secondary_grenade2_idle = 711,
	act_mp_secondary_grenade2_attack = 712,
	act_mp_melee_grenade1_draw = 713,
	act_mp_melee_grenade1_idle = 714,
	act_mp_melee_grenade1_attack = 715,
	act_mp_melee_grenade2_draw = 716,
	act_mp_melee_grenade2_idle = 717,
	act_mp_melee_grenade2_attack = 718,
	act_mp_item1_grenade1_draw = 719,
	act_mp_item1_grenade1_idle = 720,
	act_mp_item1_grenade1_attack = 721,
	act_mp_item1_grenade2_draw = 722,
	act_mp_item1_grenade2_idle = 723,
	act_mp_item1_grenade2_attack = 724,
	act_mp_item2_grenade1_draw = 725,
	act_mp_item2_grenade1_idle = 726,
	act_mp_item2_grenade1_attack = 727,
	act_mp_item2_grenade2_draw = 728,
	act_mp_item2_grenade2_idle = 729,
	act_mp_item2_grenade2_attack = 730,
	act_mp_stand_building = 731,
	act_mp_crouch_building = 732,
	act_mp_run_building = 733,
	act_mp_walk_building = 734,
	act_mp_airwalk_building = 735,
	act_mp_crouchwalk_building = 736,
	act_mp_jump_building = 737,
	act_mp_jump_start_building = 738,
	act_mp_jump_float_building = 739,
	act_mp_jump_land_building = 740,
	act_mp_swim_building = 741,
	act_mp_attack_stand_building = 742,
	act_mp_attack_crouch_building = 743,
	act_mp_attack_swim_building = 744,
	act_mp_attack_airwalk_building = 745,
	act_mp_attack_stand_grenade_building = 746,
	act_mp_attack_crouch_grenade_building = 747,
	act_mp_attack_swim_grenade_building = 748,
	act_mp_attack_airwalk_grenade_building = 749,
	act_mp_stand_pda = 750,
	act_mp_crouch_pda = 751,
	act_mp_run_pda = 752,
	act_mp_walk_pda = 753,
	act_mp_airwalk_pda = 754,
	act_mp_crouchwalk_pda = 755,
	act_mp_jump_pda = 756,
	act_mp_jump_start_pda = 757,
	act_mp_jump_float_pda = 758,
	act_mp_jump_land_pda = 759,
	act_mp_swim_pda = 760,
	act_mp_attack_stand_pda = 761,
	act_mp_attack_swim_pda = 762,
	act_mp_gesture_vc_handmouth = 763,
	act_mp_gesture_vc_fingerpoint = 764,
	act_mp_gesture_vc_fistpump = 765,
	act_mp_gesture_vc_thumbsup = 766,
	act_mp_gesture_vc_nodyes = 767,
	act_mp_gesture_vc_nodno = 768,
	act_mp_gesture_vc_handmouth_primary = 769,
	act_mp_gesture_vc_fingerpoint_primary = 770,
	act_mp_gesture_vc_fistpump_primary = 771,
	act_mp_gesture_vc_thumbsup_primary = 772,
	act_mp_gesture_vc_nodyes_primary = 773,
	act_mp_gesture_vc_nodno_primary = 774,
	act_mp_gesture_vc_handmouth_secondary = 775,
	act_mp_gesture_vc_fingerpoint_secondary = 776,
	act_mp_gesture_vc_fistpump_secondary = 777,
	act_mp_gesture_vc_thumbsup_secondary = 778,
	act_mp_gesture_vc_nodyes_secondary = 779,
	act_mp_gesture_vc_nodno_secondary = 780,
	act_mp_gesture_vc_handmouth_melee = 781,
	act_mp_gesture_vc_fingerpoint_melee = 782,
	act_mp_gesture_vc_fistpump_melee = 783,
	act_mp_gesture_vc_thumbsup_melee = 784,
	act_mp_gesture_vc_nodyes_melee = 785,
	act_mp_gesture_vc_nodno_melee = 786,
	act_mp_gesture_vc_handmouth_item1 = 787,
	act_mp_gesture_vc_fingerpoint_item1 = 788,
	act_mp_gesture_vc_fistpump_item1 = 789,
	act_mp_gesture_vc_thumbsup_item1 = 790,
	act_mp_gesture_vc_nodyes_item1 = 791,
	act_mp_gesture_vc_nodno_item1 = 792,
	act_mp_gesture_vc_handmouth_item2 = 793,
	act_mp_gesture_vc_fingerpoint_item2 = 794,
	act_mp_gesture_vc_fistpump_item2 = 795,
	act_mp_gesture_vc_thumbsup_item2 = 796,
	act_mp_gesture_vc_nodyes_item2 = 797,
	act_mp_gesture_vc_nodno_item2 = 798,
	act_mp_gesture_vc_handmouth_building = 799,
	act_mp_gesture_vc_fingerpoint_building = 800,
	act_mp_gesture_vc_fistpump_building = 801,
	act_mp_gesture_vc_thumbsup_building = 802,
	act_mp_gesture_vc_nodyes_building = 803,
	act_mp_gesture_vc_nodno_building = 804,
	act_mp_gesture_vc_handmouth_pda = 805,
	act_mp_gesture_vc_fingerpoint_pda = 806,
	act_mp_gesture_vc_fistpump_pda = 807,
	act_mp_gesture_vc_thumbsup_pda = 808,
	act_mp_gesture_vc_nodyes_pda = 809,
	act_mp_gesture_vc_nodno_pda = 810,
	act_vm_unusable = 811,
	act_vm_unusable_to_usable = 812,
	act_vm_usable_to_unusable = 813,
	act_primary_vm_draw = 814,
	act_primary_vm_holster = 815,
	act_primary_vm_idle = 816,
	act_primary_vm_pullback = 817,
	act_primary_vm_primaryattack = 818,
	act_primary_vm_secondaryattack = 819,
	act_primary_vm_reload = 820,
	act_primary_vm_dryfire = 821,
	act_primary_vm_idle_to_lowered = 822,
	act_primary_vm_idle_lowered = 823,
	act_primary_vm_lowered_to_idle = 824,
	act_secondary_vm_draw = 825,
	act_secondary_vm_holster = 826,
	act_secondary_vm_idle = 827,
	act_secondary_vm_pullback = 828,
	act_secondary_vm_primaryattack = 829,
	act_secondary_vm_secondaryattack = 830,
	act_secondary_vm_reload = 831,
	act_secondary_vm_dryfire = 832,
	act_secondary_vm_idle_to_lowered = 833,
	act_secondary_vm_idle_lowered = 834,
	act_secondary_vm_lowered_to_idle = 835,
	act_melee_vm_draw = 836,
	act_melee_vm_holster = 837,
	act_melee_vm_idle = 838,
	act_melee_vm_pullback = 839,
	act_melee_vm_primaryattack = 840,
	act_melee_vm_secondaryattack = 841,
	act_melee_vm_reload = 842,
	act_melee_vm_dryfire = 843,
	act_melee_vm_idle_to_lowered = 844,
	act_melee_vm_idle_lowered = 845,
	act_melee_vm_lowered_to_idle = 846,
	act_pda_vm_draw = 847,
	act_pda_vm_holster = 848,
	act_pda_vm_idle = 849,
	act_pda_vm_pullback = 850,
	act_pda_vm_primaryattack = 851,
	act_pda_vm_secondaryattack = 852,
	act_pda_vm_reload = 853,
	act_pda_vm_dryfire = 854,
	act_pda_vm_idle_to_lowered = 855,
	act_pda_vm_idle_lowered = 856,
	act_pda_vm_lowered_to_idle = 857,
	act_item1_vm_draw = 858,
	act_item1_vm_holster = 859,
	act_item1_vm_idle = 860,
	act_item1_vm_pullback = 861,
	act_item1_vm_primaryattack = 862,
	act_item1_vm_secondaryattack = 863,
	act_item1_vm_reload = 864,
	act_item1_vm_dryfire = 865,
	act_item1_vm_idle_to_lowered = 866,
	act_item1_vm_idle_lowered = 867,
	act_item1_vm_lowered_to_idle = 868,
	act_item2_vm_draw = 869,
	act_item2_vm_holster = 870,
	act_item2_vm_idle = 871,
	act_item2_vm_pullback = 872,
	act_item2_vm_primaryattack = 873,
	act_item2_vm_secondaryattack = 874,
	act_item2_vm_reload = 875,
	act_item2_vm_dryfire = 876,
	act_item2_vm_idle_to_lowered = 877,
	act_item2_vm_idle_lowered = 878,
	act_item2_vm_lowered_to_idle = 879,
	act_reload_succeed = 880,
	act_reload_fail = 881,
	act_walk_aim_autogun = 882,
	act_run_aim_autogun = 883,
	act_idle_autogun = 884,
	act_idle_aim_autogun = 885,
	act_reload_autogun = 886,
	act_crouch_idle_autogun = 887,
	act_range_attack_autogun = 888,
	act_jump_autogun = 889,
	act_idle_aim_pistol = 890,
	act_walk_aim_dual = 891,
	act_run_aim_dual = 892,
	act_idle_dual = 893,
	act_idle_aim_dual = 894,
	act_reload_dual = 895,
	act_crouch_idle_dual = 896,
	act_range_attack_dual = 897,
	act_jump_dual = 898,
	act_idle_shotgun = 899,
	act_idle_aim_shotgun = 900,
	act_crouch_idle_shotgun = 901,
	act_jump_shotgun = 902,
	act_idle_aim_rifle = 903,
	act_reload_rifle = 904,
	act_crouch_idle_rifle = 905,
	act_range_attack_rifle = 906,
	act_jump_rifle = 907,
	act_sleep = 908,
	act_wake = 909,
	act_flick_left = 910,
	act_flick_left_middle = 911,
	act_flick_right_middle = 912,
	act_flick_right = 913,
	act_spinaround = 914,
	act_prep_to_fire = 915,
	act_fire = 916,
	act_fire_recover = 917,
	act_spray = 918,
	act_prep_explode = 919,
	act_explode = 920,
	act_dota_idle = 921,
	act_dota_run = 922,
	act_dota_attack = 923,
	act_dota_attack_event = 924,
	act_dota_die = 925,
	act_dota_flinch = 926,
	act_dota_disabled = 927,
	act_dota_cast_ability_1 = 928,
	act_dota_cast_ability_2 = 929,
	act_dota_cast_ability_3 = 930,
	act_dota_cast_ability_4 = 931,
	act_dota_override_ability_1 = 932,
	act_dota_override_ability_2 = 933,
	act_dota_override_ability_3 = 934,
	act_dota_override_ability_4 = 935,
	act_dota_channel_ability_1 = 936,
	act_dota_channel_ability_2 = 937,
	act_dota_channel_ability_3 = 938,
	act_dota_channel_ability_4 = 939,
	act_dota_channel_end_ability_1 = 940,
	act_dota_channel_end_ability_2 = 941,
	act_dota_channel_end_ability_3 = 942,
	act_dota_channel_end_ability_4 = 943,
	act_mp_run_speedpaint = 944,
	act_mp_long_fall = 945,
	act_mp_tractorbeam_float = 946,
	act_mp_death_crush = 947,
	act_mp_run_speedpaint_primary = 948,
	act_mp_drowning_primary = 949,
	act_mp_long_fall_primary = 950,
	act_mp_tractorbeam_float_primary = 951,
	act_mp_death_crush_primary = 952,
	act_die_stand = 953,
	act_die_stand_headshot = 954,
	act_die_crouch = 955,
	act_die_crouch_headshot = 956,
	act_csgo_null = 957,
	act_csgo_defuse = 958,
	act_csgo_defuse_with_kit = 959,
	act_csgo_flashbang_reaction = 960,
	act_csgo_fire_primary = 961,
	act_csgo_fire_primary_opt_1 = 962,
	act_csgo_fire_primary_opt_2 = 963,
	act_csgo_fire_secondary = 964,
	act_csgo_fire_secondary_opt_1 = 965,
	act_csgo_fire_secondary_opt_2 = 966,
	act_csgo_reload = 967,
	act_csgo_reload_start = 968,
	act_csgo_reload_loop = 969,
	act_csgo_reload_end = 970,
	act_csgo_operate = 971,
	act_csgo_deploy = 972,
	act_csgo_catch = 973,
	act_csgo_silencer_detach = 974,
	act_csgo_silencer_attach = 975,
	act_csgo_twitch = 976,
	act_csgo_twitch_buyzone = 977,
	act_csgo_plant_bomb = 978,
	act_csgo_idle_turn_balanceadjust = 979,
	act_csgo_idle_adjust_stoppedmoving = 980,
	act_csgo_alive_loop = 981,
	act_csgo_flinch = 982,
	act_csgo_flinch_head = 983,
	act_csgo_flinch_molotov = 984,
	act_csgo_jump = 985,
	act_csgo_fall = 986,
	act_csgo_climb_ladder = 987,
	act_csgo_land_light = 988,
	act_csgo_land_heavy = 989,
	act_csgo_exit_ladder_top = 990,
	act_csgo_exit_ladder_bottom = 991,
	act_csgo_parachute = 992,
	act_csgo_uiplayer_idle = 993,
	act_csgo_uiplayer_walkup = 994,
	act_csgo_uiplayer_celebrate = 995,
	act_csgo_uiplayer_confirm = 996,
	act_csgo_uiplayer_buymenu = 997,
	act_csgo_uiplayer_patch = 998,
	activity_list_max
};

enum entity_flags {
	fl_onground = ( 1 << 0 ),
	fl_ducking = ( 1 << 1 ),
	fl_waterjump = ( 1 << 2 ),
	fl_ontrain = ( 1 << 3 ),
	fl_inrain = ( 1 << 4 ),
	fl_frozen = ( 1 << 5 ),
	fl_atcontrols = ( 1 << 6 ),
	fl_client = ( 1 << 7 ),
	fl_fakeclient = ( 1 << 8 ),
	fl_inwater = ( 1 << 9 ),
	fl_fly = ( 1 << 10 ),
	fl_swim = ( 1 << 11 ),
	fl_conveyor = ( 1 << 12 ),
	fl_npc = ( 1 << 13 ),
	fl_godmode = ( 1 << 14 ),
	fl_notarget = ( 1 << 15 ),
	fl_aimtarget = ( 1 << 16 ),
	fl_partialground = ( 1 << 17 ),
	fl_staticprop = ( 1 << 18 ),
	fl_graphed = ( 1 << 19 ),
	fl_grenade = ( 1 << 20 ),
	fl_stepmovement = ( 1 << 21 ),
	fl_donttouch = ( 1 << 22 ),
	fl_basevelocity = ( 1 << 23 ),
	fl_worldbrush = ( 1 << 24 ),
	fl_object = ( 1 << 25 ),
	fl_killme = ( 1 << 26 ),
	fl_onfire = ( 1 << 27 ),
	fl_dissolving = ( 1 << 28 ),
	fl_transragdoll = ( 1 << 29 ),
	fl_unblockable_by_player = ( 1 << 30 )
};

/* other structs */
struct animstate_pose_param_cache_t {
	std::uint8_t pad_0x0[ 0x4 ]; //0x0
	std::uint32_t m_idx; //0x4 
	char* m_name; //0x8

	void set_value( c_base_player* e, float val );
};

class animstate_t {
public:
	std::uint8_t pad_0x0000[ 0x4 ]; //0x0000
	bool m_force_update; //0x0005 
	std::uint8_t pad_0x0006[ 0x5A ]; //0x0006
	c_base_entity* m_entity; //0x0060 
	c_base_combat_weapon* m_weapon; //0x0064 
	c_base_combat_weapon* m_last_weapon; //0x0068 
	float m_last_clientside_anim_update; //0x006C 
	uint32_t m_last_clientside_anim_framecount; //0x0070 
	float m_last_clientside_anim_update_time_delta; //0x0074 
	float m_eye_yaw; //0x0078 
	float m_pitch; //0x007C 
	float m_abs_yaw; //0x0080 
	float m_feet_yaw; //0x0084 
	float m_body_yaw; //0x0088 
	float m_body_yaw_clamped; //0x008C 
	float m_feet_vel_dir_delta; //0x0090 
	uint8_t pad_0x0094[ 0x4 ]; //0x0094
	float m_feet_cycle; //0x0098 
	float m_feet_yaw_rate; //0x009C 
	uint8_t pad_0x00A0[ 0x4 ]; //0x00A0
	float m_duck_amount; //0x00A4 
	float m_landing_duck_additive; //0x00A8 
	uint8_t pad_0x00AC[ 0x4 ]; //0x00AC
	vec3_t m_origin;
	vec3_t m_old_origin;
	vec3_t m_velocity;
	vec3_t m_velocity_normalized;
	vec3_t m_last_accelerating_vel;
	float m_speed2d;
	float m_abs_velocity;
	float m_speed_normalized;
	float m_run_speed; //0x00F8 
	float m_duck_speed; //0x00FC 
	float m_time_since_move; //0x0100 
	float m_time_since_stop; //0x0104 
	bool m_on_ground; //0x0108 
	bool m_hit_ground; //0x0109 
	uint8_t pad_0x010A[ 0x4 ]; //0x010A
	float m_time_in_air; //0x0110 
	uint8_t pad_0x0114[ 0x6 ]; //0x0114
	float m_ground_fraction; //0x011C 
	uint8_t pad_0x0120[ 0x2 ]; //0x0120
	float m_unk_fraction; //0x0124 
	uint8_t pad_0x0128[ 0xC ]; //0x0128
	bool m_moving; //0x0134
	uint8_t pad_0x0135[ 0x7B ]; //0x0135
	animstate_pose_param_cache_t m_lean_yaw_pose; //0x1B0
	animstate_pose_param_cache_t m_speed_pose; //0x01BC
	animstate_pose_param_cache_t m_ladder_speed_pose; //0x01C8
	animstate_pose_param_cache_t m_ladder_yaw_pose; //0x01D4
	animstate_pose_param_cache_t m_move_yaw_pose; //0x01E0
	animstate_pose_param_cache_t m_run_pose; //0x01EC 
	animstate_pose_param_cache_t m_body_yaw_pose; //0x01F8
	animstate_pose_param_cache_t m_body_pitch_pose; //0x0204
	animstate_pose_param_cache_t m_dead_yaw_pose; //0x0210
	animstate_pose_param_cache_t m_stand_pose; //0x021C
	animstate_pose_param_cache_t m_jump_fall_pose; //0x0228
	animstate_pose_param_cache_t m_aim_blend_stand_idle_pose; //0x0234
	animstate_pose_param_cache_t m_aim_blend_crouch_idle_pose; //0x0240
	animstate_pose_param_cache_t m_strafe_yaw_pose; //0x024C
	animstate_pose_param_cache_t m_aim_blend_stand_walk_pose; //0x0258
	animstate_pose_param_cache_t m_aim_blend_stand_run_pose; //0x0264
	animstate_pose_param_cache_t m_aim_blend_crouch_walk_pose; //0x0270
	animstate_pose_param_cache_t m_move_blend_walk_pose; //0x027C
	animstate_pose_param_cache_t m_move_blend_run_pose; //0x0288
	animstate_pose_param_cache_t m_move_blend_crouch_pose; //0x0294
	uint8_t pad_0x02A0[ 0x4 ]; //0x02A0
	float m_vel_unk; //0x02A4 
	uint8_t pad_0x02A8[ 0x86 ]; //0x02A8
	float m_min_yaw; //0x0330 
	float m_max_yaw; //0x0334 
	float m_max_pitch; //0x0338 
	float m_min_pitch; //0x033C

	void reset( );
	void update( vec3_t& ang );

	float& time_since_in_air( ) {
		return *( float* ) ( ( uintptr_t ) this + 0x110 );
	}

	float& yaw_desync_adjustment( ) {
		return *( float* ) ( ( uintptr_t ) this + 0x334 );
	}

	bool& m_smooth_height_valid( ) {
		return *( bool* ) ( ( uintptr_t ) this + 0x328 );
	}
}; //Size=0x0340

struct animlayer_t {
	char pad_0x01[ 0x14 ];
	int	m_order;
	int	m_sequence;
	float m_previous_cycle;
	float m_weight;
	float m_weight_delta_rate;
	float m_playback_rate;
	float m_cycle;
	void* m_owner;
	char pad_0x02[ 0x4 ];
};

enum animlayer_stages
{
	main_idle_sequence_layer = 0, //0	 for 8-way blended models, this layer blends an idle on top of the run/walk animation to simulate a 9-way blend.
	//	 for 9-way blended models, we don't use this layer.
	aimsequence_layer1, //1	 aim sequence uses layers 0 and 1 for the weapon idle animation (needs 2 layers so it can blend).
	aimsequence_layer2, //2
	lowerbody_layer, //3
	jumping_layer, //4
	landing_layer, //5
	feet_layer, //6
	silencerchangesequence_layer, //7
	wholebodyaction_layer, //8
	flashedsequence_layer, //9
	flinchsequence_layer, //10
	idle_layer, //11
	lean_layer, //12
	unused1, //13
	unused2, //14
};

inline c_base_player* g_local;

class c_base_player : public c_base_entity {
public:
	static __forceinline c_base_player* get_player_by_index( int index ) {
		return static_cast< c_base_player* >( get_entity_by_index( index ) );
	}

	/* offsets / indexes */
	float m_flSpawnTime( ) {
		return *( float* ) ( ( uintptr_t ) this + 0x103C0 );
	}

	int& m_iEFlags( ) {
		return *( int* ) ( ( uintptr_t ) this + 0xE8 );
	}

	int& m_nFinalPredictedTick( ) {
		return *( int* ) ( ( DWORD ) this + 0x3434 );
	}

	vec3_t& tp_angles( ) {
		static int m_tp_angles = ( netvars::get_offset( "DT_BasePlayer->deadflag" ) + 0x4 ); // 0x31D4 + 0x4
		return *( vec3_t* ) ( ( uintptr_t ) this + m_tp_angles );
	}

	vec3_t& m_vecAbsVelocity( ) {
		return *( vec3_t* ) ( ( uintptr_t ) this + 0x94 );
	}

	bool& m_JiggleBones( ) {
		return *( bool* ) ( ( uintptr_t ) this + 0x2930 );
	}

	std::uint32_t& bone_count( ) {
		static auto offset = *( std::uintptr_t* ) ( ( std::uint32_t ) ( utils::find_sig_ida( "client.dll", "8B 87 ? ? ? ? 8B 4D 0C" ) + 2 ) );
		return *( uint32_t* ) ( std::uintptr_t( get_client_renderable( ) ) + offset );
	}

	animlayer_t* get_animoverlays( ) {
		return *( animlayer_t** ) ( ( DWORD ) this + 0x2990 );
	}

	animstate_t* get_animstate( ) {
		return *reinterpret_cast< animstate_t** >( reinterpret_cast< void* >( uintptr_t( this ) + 0x9960 ) );
	}

	bool& should_use_new_animstate( ) {
		return *( bool* ) ( ( uintptr_t ) this + 0x3AC8 );
	}

	int& m_iOcclusionFlags( ) {
		return *( int* ) ( ( uintptr_t ) this + 0xA28 );
	}

	int& m_iOcclusionFramecount( ) {
		return *( int* ) ( ( uintptr_t ) this + 0xA30 );
	}

	uint32_t& get_readable_bones( ) {
		return *( uint32_t* ) ( ( uintptr_t ) this + 0x26AC );
	}

	uint32_t& get_writeable_bones( ) {
		return *( uint32_t* ) ( ( uintptr_t ) this + 0x26B0 );
	}

	void set_model_index( int index ) {
		using o_fn = void( __thiscall* )( void*, int );
		return utils::call_virtual<o_fn>( this, 75 )( this, index );
	}

	vec3_t& get_abs_origin( ) {
		using o_fn = vec3_t & ( __thiscall* )( void* );
		return utils::call_virtual<o_fn>( this, 10 )( this );
	}

	vec3_t& get_abs_angles( ) {
		using o_fn = vec3_t & ( __thiscall* )( void* );
		return utils::call_virtual<o_fn>( this, 11 )( this );
	}

	CUtlVector <matrix_t>& m_BoneCache( ) {
		static auto m_CachedBoneData = *( DWORD* ) ( utils::find_sig_ida( _( "client.dll" ), _( "FF B7 ?? ?? ?? ?? 52" ) ) + 0x2 ) + 0x4;
		return *( CUtlVector <matrix_t>* )( uintptr_t( this ) + m_CachedBoneData );
	}

	void update_clientside_animation( ) {
		/*
		CVProfile *v0; // ecx
		int v1; // ebx
		int v2; // edi
		int v3; // esi

		v0 = (CVProfile *)g_VProfCurrentProfile;
		v1 = *(_DWORD *)(g_VProfCurrentProfile + 4108); // 1027
		if ( v1 )
		{
		  CVProfile::EnterScope(g_VProfCurrentProfile, "UpdateClientSideAnimations", 0, "Client_Animation", 0, 4);
		  v0 = (CVProfile *)g_VProfCurrentProfile;
		}
		v2 = dword_14D91F58;
		v3 = 0;
		if ( dword_14D91F58 > 0 )
		{
			if ( *(_BYTE *)(dword_14D91F4C + 8 * v3 + 4) & 1 )
			  (*(void (**)(void))(**(_DWORD **)(dword_14D91F4C + 8 * v3) + 892))(); // 223
			++v3;
		  while ( v3 < v2 );
		  v0 = (CVProfile *)g_VProfCurrentProfile;
		}
		if ( v1 )
		  CVProfile::ExitScope(v0);
		*/
		typedef void( __thiscall* o_fn )( void* );
		return utils::call_virtual<o_fn>( this, 224 )( this );
	}

	void modify_eye_pos( animstate_t* anim, vec3_t* pos ) {
		using bone_lookup_fn = int( __thiscall* )( void*, const char* );
		static auto lookup_bone = ( bone_lookup_fn ) utils::find_sig_ida( "client.dll", "55 8B EC 53 56 8B F1 57 83 BE ? ? ? ? ? 75 14 8B 46 04 8D 4E 04 FF 50 20 85 C0 74 07 8B CE E8 ? ? ? ? 8B 8E ? ? ? ? 85 C9 0F 84" );

		if ( anim->m_hit_ground && anim->m_duck_amount != 0.0f ) {
			auto bone_pos = this->m_BoneCache( )[ lookup_bone( this, "head_0" ) ].at( 3 );

			bone_pos.z += 1.7f;

			if ( ( *pos ).z > bone_pos.z ) {
				auto some_factor = 0.0f;
				auto delta = ( *pos ).z - bone_pos.z;
				auto some_offset = ( delta - 4.0f ) / 6.0f;

				if ( some_offset >= 0.0f )
					some_factor = std::fminf( some_offset, 1.0f );

				( *pos ).z += ( ( bone_pos.z - ( *pos ).z ) * ( ( ( some_factor * some_factor ) * 3.0f ) - ( ( ( some_factor * some_factor ) * 2.0f ) * some_factor ) ) );
			}
		}
	}

	void simulate_movement( vec3_t& pred, int choked ) {
		pred = vec3_t( this->get_eye_pos( ).x + ( this->m_vecVelocity( ).x * i::globalvars->m_interval_per_tick ) * choked, this->get_eye_pos( ).y + ( this->m_vecVelocity( ).y * i::globalvars->m_interval_per_tick ) * choked, this->get_eye_pos( ).z );
	}

	vec3_t pred_eyepos( int ticks ) {
		vec3_t pred;
		simulate_movement( pred, ticks );
		return pred;
	}

	OFFSET( std::uint32_t, shhessh, 0x3AB4 );
	OFFSET( matrix_t*, GetBoneArrayForWrite, 0x26A8 );
	OFFSET( vec3_t, m_vecOldOrigin, 0x3A8 );
	vec3_t weapon_shoot_pos( )
	{
		/* only on local ( when fakeducking ) */
		/*if ( keyhandler::auto_check( g_vars.antiaim.fakeduck_key[ 1 ], g_vars.antiaim.fakeduck_key[ 0 ] ) && this->ent_index( ) == i::engine->get_local_player( ) ) {
			vec3_t m_origin = this->m_vecOrigin( );

			vec3_t m_duck_hull_min = i::game_movement->get_player_mins( true );
			vec3_t m_stand_hull_min = i::game_movement->get_player_mins( false );

			float m_more = ( m_duck_hull_min.z - m_stand_hull_min.z );

			vec3_t m_duck_view_offset = i::game_movement->get_player_view_offset( true );
			vec3_t m_stand_view_offset = i::game_movement->get_player_view_offset( false );
			float m_duck_fraction = this->m_flDuckAmount( );

			float m_tempz = ( ( m_duck_view_offset.z - m_more ) * m_duck_fraction ) +
				( m_stand_view_offset.z * ( 1 - m_duck_fraction ) );

			m_origin.z += m_tempz;

			return m_origin;
		}*/

		auto pos = this->get_eye_pos( );

		if ( shhessh( ) ) {
			auto animstate = this->get_animstate( );
			if ( animstate ) {
				modify_eye_pos( animstate, &pos );
			}
		}

		return pos;
	}

	std::array<int, 5>& m_vecPlayerPatchEconIndices( ) {
		return *( std::array<int, 5>* )( ( uintptr_t ) this + 0xB970 );
	}

	studio_hdr_t* get_model_ptr( ) {
		return *( studio_hdr_t** ) ( ( uintptr_t ) this + 0x2950 );
	}

	/* other */
	c_base_combat_weapon* get_active_weapon( ) {
		auto active_weapon = *( int* ) ( uintptr_t( this ) + netvars::get_offset( "DT_CSPlayer->m_hActiveWeapon" ) ) & 0xFFF;
		return reinterpret_cast< c_base_combat_weapon* >( i::entitylist->get_client_entity( active_weapon ) );
	}

	void invalidate_bone_cache( ) {
		static auto invalidate_bone_cache = std::uintptr_t( utils::find_sig_ida( "client.dll", "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81" ) + 10 );

		*( std::uint32_t* ) ( ( std::uintptr_t ) this + 0x2924 ) = 0xFF7FFFFF;
		*( std::uint32_t* ) ( ( std::uintptr_t ) this + 0x2690 ) = **( std::uintptr_t** ) invalidate_bone_cache - 1;
	}

	bool is_alive( ) {
		return this->m_iHealth( ) > 0;
	}

	matrix_t get_bone_matrix( int id ) {
		matrix_t matrix;

		auto offset = *reinterpret_cast< uintptr_t* >( uintptr_t( this ) + 0x26A8 );
		if ( offset )
			matrix = *reinterpret_cast< matrix_t* >( offset + 0x30 * id );

		return matrix;
	}

	vec3_t get_bone_pos( int i );

	void create_anim_state( animstate_t* state )
	{
		using create_anim_state_t = void( __thiscall* ) ( animstate_t*, c_base_player* );
		static auto create_anim_state = reinterpret_cast< create_anim_state_t > ( utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 56 8B F1 B9 ? ? ? ? C7 46" ) ) );

		if ( !create_anim_state )
			return;

		if ( !state )
			return;

		create_anim_state( state, this );
	}

	float max_desync_delta( ) {
		auto animstate = uintptr_t( this->get_animstate( ) );

		float duckammount = *( float* ) ( animstate + 0xA4 );
		float speedfraction = std::fmax( 0, std::fmin( *reinterpret_cast< float* >( animstate + 0xF8 ), 1 ) );

		float speedfactor = std::fmax( 0, std::fmin( 1, *reinterpret_cast< float* > ( animstate + 0xFC ) ) );

		float unk1 = ( ( *reinterpret_cast< float* > ( animstate + 0x11C ) * -0.30000001 ) - 0.19999999 ) * speedfraction;
		float unk2 = unk1 + 1.f;
		float unk3;

		if ( duckammount > 0 ) {

			unk2 += ( ( duckammount * speedfactor ) * ( 0.5f - unk2 ) );

		}

		unk3 = *( float* ) ( animstate + 0x334 ) * unk2;

		return unk3;
	}

	vec3_t get_hitbox_pos( int hitbox, matrix_t* matrix = nullptr )
	{
		auto mdl = this->get_model( );
		if ( !mdl ) return vec3_t( 0, 0, 0 );

		studio_hdr_t* m_studio_model = i::modelinfo->get_studio_model( this->get_model( ) );
		if ( !m_studio_model ) return vec3_t( 0, 0, 0 );

		auto* m_hitbox = m_studio_model->hitbox_set( 0 )->hitbox( hitbox );
		if ( !m_hitbox ) return vec3_t( 0, 0, 0 );

		vec3_t vmin, vmax;

		matrix_t temp_matrix[ 128 ];
		setup_bones( temp_matrix, 128, 256, m_flSimulationTime( ) );

		math::vector_transform( m_hitbox->maxs, matrix ? matrix[ m_hitbox->bone ] : temp_matrix[ m_hitbox->bone ], vmax );
		math::vector_transform( m_hitbox->mins, matrix ? matrix[ m_hitbox->bone ] : temp_matrix[ m_hitbox->bone ], vmin );

		auto pos = ( vmin + vmax ) * 0.5f;

		return pos;
	}

	void invalidate_physics( int flags ) {
		static const auto invalidate_physics_recursive = reinterpret_cast< void( __thiscall* )( void*, int32_t ) >( utils::find_sig_ida( "client.dll", "55 8B EC 83 E4 F8 83 EC 0C 53 8B 5D 08 8B C3 56" ) );
		invalidate_physics_recursive( this, flags );
	}

	vec3_t get_eye_pos( ) {
		return m_vecOrigin( ) + m_vecViewOffset( );
	}

	bool can_see_player_pos( c_base_player* player, vec3_t& pos, vec3_t origin = vec3_t( 0, 0, 0 ) ) {
		trace_t tr;
		trace_filter filter;
		filter.skip = this;

		i::trace->trace_ray( ray_t( origin.is_zero( ) ? this->get_eye_pos( ) : origin, pos ), mask_shot | contents_grate, &filter, &tr );

		return tr.player == player || tr.fraction > 0.97f;
	}

	int get_choked_packets( ) {
		float simtime = this->m_flSimulationTime( );
		float oldsimtime = this->m_flOldSimulationTime( );
		float simdiff = simtime - oldsimtime;

		return time2ticks( std::fmaxf( 0, simdiff ) );
	}

	player_info_t get_player_info( )
	{
		player_info_t pinfo;
		i::engine->get_player_info( ent_index( ), &pinfo );
		return pinfo;
	}

	void set_abs_angles( vec3_t angles ) {
		using o_fn = void( __thiscall* )( void*, const vec3_t& );
		static o_fn set_angles_fn = ( o_fn ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1" ) );
		set_angles_fn( this, angles );
	}

	void set_abs_origin( vec3_t position ) {
		using o_fn = void( __thiscall* )( void*, const vec3_t& );
		static o_fn set_position_fn = ( o_fn ) utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8" ) );
		set_position_fn( this, position );
	}

	bool is_enemy( ) {
		if ( !this || !g_local )
			return false;

		if ( this == g_local )
			return false;

		if ( this->m_iTeamNum( ) != g_local->m_iTeamNum( ) )
			return true;

		if ( i::cvar->find_var( "mp_teammates_are_enemies" )->get_int( ) )
			return true;

		return false;
	}

	bool is_valid_target( bool check_team = true, bool check_dormant = true ) {
		if ( !this )
			return false;

		if ( !g_local )
			return false;

		if ( !is_player( ) )
			return false;

		if ( !is_alive( ) )
			return false;

		if ( this->is_dormant( ) && check_dormant )
			return false;

		if ( check_team && !this->is_enemy( ) )
			return false;

		if ( this->m_bGunGameImmunity( ) || ( this->m_fFlags( ) & fl_frozen ) )
			return false;

		return true;
	}

	int sequence_activity( int sequence ) {
		if ( !this ) //-V704
			return 0;

		auto hdr = i::modelinfo->get_studio_model( this->get_model( ) );

		if ( !hdr )
			return 0;

		static auto sequence_activity = reinterpret_cast< int( __fastcall* )( void*, studio_hdr_t*, int ) >( utils::find_sig_ida( _( "client.dll" ), _( "55 8B EC 53 8B 5D 08 56 8B F1 83" ) ) );
		return sequence_activity( this, hdr, sequence );
	}

	void build_transformations( studio_hdr_t* hdr, vec3_t* pos, quaternion* q, const matrix_t& transform, int mask, uint8_t* computed ) {
		using o_fn = void( __thiscall* )( decltype( this ), studio_hdr_t*, vec3_t*, quaternion*, matrix_t const&, int, uint8_t* );
		return utils::call_virtual< o_fn >( this, 189 )( this, hdr, pos, q, transform, mask, computed );
	}

	void standard_blending_rules( studio_hdr_t* hdr, vec3_t* pos, quaternion* q, float time, int mask ) {
		using o_fn = void( __thiscall* )( decltype( this ), studio_hdr_t*, vec3_t*, quaternion*, float, int );
		return utils::call_virtual< o_fn >( this, 205 )( this, hdr, pos, q, time, mask );
	}

	/* DT_BasePlayer */
	// m_iFOV                                 
	// m_iFOVStart                            
	// m_flFOVTime                            
	// m_iDefaultFOV                          
	// m_hZoomOwner                           
	// m_afPhysicsFlags                       
	// m_hVehicle                             
	// m_hUseEntity                           
	// m_hGroundEntity                        
	NETVAR( "DT_BasePlayer->m_iHealth", m_iHealth, int );
	NETVAR( "DT_BasePlayer->m_lifeState", m_lifeState, int );
	//m_iBonusProgress
	//m_iBonusChallenge
	NETVAR( "DT_BasePlayer->m_flMaxspeed", m_flMaxspeed, float );
	NETVAR( "DT_BasePlayer->m_fFlags", m_fFlags, int );
	NETVAR( "DT_BasePlayer->m_iObserverMode", m_iObserverMode, int );
	// m_bActiveCameraMan
	// m_bCameraManXRay
	// m_bCameraManOverview
	// m_bCameraManScoreBoard
	// m_uCameraManGraphs
	// m_iDeathPostEffect
	NETVAR( "DT_BasePlayer->m_hObserverTarget", m_hObserverTarget, HANDLE );
	NETVAR( "DT_BasePlayer->m_hViewModel[0]", m_hViewModel, int );
	// m_hViewModel
	// m_iCoachingTeam
	// m_szLastPlaceName
	// m_vecLadderNormal
	// m_ladderSurfaceProps
	// m_ubEFNoInterpParity
	// m_hPostProcessCtrl
	// m_hColorCorrectionCtrl
	// m_PlayerFog.m_hCtrl
	// m_vphysicsCollisionState
	// m_hViewEntity
	// m_bShouldDrawPlayerWhileUsingViewEntity
	NETVAR( "DT_BasePlayer->m_flDuckAmount", m_flDuckAmount, float );
	NETVAR( "DT_BasePlayer->m_flDuckSpeed", m_flDuckSpeed, float );
	// m_nWaterLevel
	// localdata
	NETVAR( "DT_BasePlayer->m_vecViewOffset[0]", m_vecViewOffset, vec3_t );
	// m_vecViewOffset[1]
	// m_vecViewOffset[2]
	// m_flFriction
	// m_fOnTarget
	NETVAR( "DT_BasePlayer->m_nTickBase", m_nTickBase, int );
	// m_nNextThinkTick
	// m_hLastWeapon
	NETVAR( "DT_BasePlayer->m_vecVelocity[0]", m_vecVelocity, vec3_t );
	// m_vecVelocity[1]
	// m_vecVelocity[2]
	NETVAR( "DT_BasePlayer-m_vecBaseVelocity", m_vecBaseVelocity, vec3_t );
	NETVAR( "DT_BasePlayer->m_vecMaxs", m_vecMaxs, vec3_t );
	NETVAR( "DT_BasePlayer->m_vecMins", m_vecMins, vec3_t );
	// m_hConstraintEntity                
	// m_vecConstraintCenter
	// m_flConstraintRadius               
	// m_flConstraintWidth                
	// m_flConstraintSpeedFactor          
	// m_bConstraintPastRadius            
	// m_flDeathTime                      
	// m_flNextDecalTime                  
	// m_fForceTeam                       
	// m_flLaggedMovementValue            
	// m_hTonemapController               
	// m_Local                            
	// m_iHideHUD                     
	// m_flFOVRate                    
	// m_bDucked                      
	// m_bDucking                     
	// m_flLastDuckTime               
	// m_bInDuckJump
	// m_nDuckTimeMsecs
	// m_nDuckJumpTimeMsecs
	// m_nJumpTimeMsecs
	// m_flFallVelocity 
	NETVAR( "DT_BasePlayer->m_viewPunchAngle", m_viewPunchAngle, vec3_t );
	NETVAR( "DT_BasePlayer->m_aimPunchAngle", m_aimPunchAngle, vec3_t );
	// m_aimPunchAngleVel             
	// m_bDrawViewmodel               
	// m_bWearingSuit                 
	// m_bPoisoned                    
	// m_flStepSize                   
	// m_bAllowAutoMovement           
	// m_skybox3d.scale               
	// m_skybox3d.origin              
	// m_skybox3d.area                
	// m_skybox3d.fog.enable          
	// m_skybox3d.fog.blend           
	// m_skybox3d.fog.dirPrimary      
	// m_skybox3d.fog.colorPrimary    
	// m_skybox3d.fog.colorSecondary  
	// m_skybox3d.fog.start           
	// m_skybox3d.fog.end             
	// m_skybox3d.fog.maxdensity      
	// m_skybox3d.fog.HDRColorScale   
	// m_audio.localSound[0]          
	// m_audio.localSound[1]          
	// m_audio.localSound[2]          
	// m_audio.localSound[3]          
	// m_audio.localSound[4]          
	// m_audio.localSound[5]          
	// m_audio.localSound[6]          
	// m_audio.localSound[7]          
	// m_audio.soundscapeIndex        
	// m_audio.localBits              
	// m_audio.entIndex               
	// m_chAreaBits                   
	// m_chAreaPortalBits             
	// pl                                     
	// deadflag                           
	// m_iAmmo                                

	/* DT_CSPlayer */
	NETVAR( "DT_CSPlayer->m_flSimulationTime", m_flSimulationTime, float );
	NETVAR_OFFSET( "DT_CSPlayer->m_flSimulationTime", 0x4, m_flOldSimulationTime, float );
	NETVAR( "DT_CSPlayer->m_angEyeAngles[0]", m_angEyeAngles, vec3_t );
	// m_angEyeAngles[1]                             
	// m_iAddonBits                                
	// m_iPrimaryAddon                             
	// m_iSecondaryAddon                           
	// m_iThrowGrenadeCounter                      
	// m_bWaitForNoAttack                          
	// m_bIsRespawningForDMBonus                   
	// m_iPlayerState     
	NETVAR( "DT_CSPlayer->m_iAccount", m_iAccount, int );
	// m_iStartAccount                             
	// m_totalHitsOnServer                         
	// m_bInBombZone                               
	// m_bInBuyZone                                
	// m_bInNoDefuseArea                           
	// m_bKilledByTaser                            
	// m_iMoveState                                
	// m_iClass                           
	NETVAR( "DT_CSPlayer->m_ArmorValue", m_ArmorValue, int );
	// m_angEyeAngles                     
	NETVAR( "DT_CSPlayer->m_bHasDefuser", m_bHasDefuser, bool );
	NETVAR( "DT_CSPlayer->m_bHasNightVision", m_bHasNightVision, float );
	NETVAR( "DT_CSPlayer->m_bNightVisionOn", m_bNightVisionOn, float );
	// m_bInHostageRescueZone                      
	NETVAR( "DT_CSPlayer->m_bIsDefusing", m_bIsDefusing, bool );
	// m_bIsGrabbingHostage                        
	// m_iBlockingUseActionInProgress 
	NETVAR( "DT_CSPlayer->m_bIsScoped", m_bIsScoped, bool );
	// m_bIsWalking                                
	// m_nIsAutoMounting                           
	// m_bResumeZoom                               
	// m_fImmuneToGunGameDamageTime                
	NETVAR( "DT_CSPlayer->m_bGunGameImmunity", m_bGunGameImmunity, bool );
	// m_bHasMovedSinceSpawn                       
	// m_bMadeFinalGunGameProgressiveKill          
	// m_iGunGameProgressiveWeaponIndex            
	// m_iNumGunGameTRKillPoints                   
	// m_iNumGunGameKillsWithCurrentWeapon         
	// m_iNumRoundKills                            
	// m_fMolotovUseTime                           
	// m_fMolotovDamageTime                        
	// m_szArmsModel                               
	// m_hCarriedHostage                           
	// m_hCarriedHostageProp                       
	NETVAR( "DT_CSPlayer->m_bIsRescuing", m_bIsRescuing, bool );
	// m_flGroundAccelLinearFracLastTime           
	// m_bCanMoveDuringFreezePeriod                
	// m_isCurrentGunGameLeader                    
	// m_isCurrentGunGameTeamLeader                
	// m_flGuardianTooFarDistFrac                  
	// m_flDetectedByEnemySensorTime               
	// m_bIsPlayerGhost                            
	// m_bHasParachute                             
	// m_unMusicID      
	NETVAR( "DT_CSPlayer->m_bHasHelmet", m_bHasHelmet, bool );
	NETVAR( "DT_CSPlayer->m_bHasHeavyArmor", m_bHasHeavyArmor, bool );
	// m_nHeavyAssaultSuitCooldownRemaining        
	NETVAR( "DT_CSPlayer->m_flFlashDuration", m_flFlashDuration, float );
	NETVAR( "DT_CSPlayer->m_flFlashMaxAlpha", m_flFlashMaxAlpha, float );
	// m_iProgressBarDuration                      
	// m_flProgressBarStartTime                    
	// m_hRagdoll                                  
	// m_hPlayerPing                               
	// m_cycleLatch                                
	// m_unCurrentEquipmentValue                   
	// m_unRoundStartEquipmentValue                
	// m_unFreezetimeEndEquipmentValue             
	// m_bIsControllingBot                         
	// m_bHasControlledBotThisRound                
	// m_bCanControlObservedBot                    
	// m_iControlledBotEntIndex                    
	// m_vecAutomoveTargetEnd                      
	// m_flAutoMoveStartTime                       
	// m_flAutoMoveTargetTime                      
	// m_bIsAssassinationTarget                    
	// m_bHud_MiniScoreHidden                      
	// m_bHud_RadarHidden                          
	// m_nLastKillerIndex                          
	// m_nLastConcurrentKilled                     
	// m_nDeathCamMusic                            
	// m_bIsHoldingLookAtWeapon                    
	// m_bIsLookingAtWeapon                        
	// m_iNumRoundKillsHeadshots                   
	// m_unTotalRoundDamageDealt    
	NETVAR( "DT_CSPlayer->m_flLowerBodyYawTarget", m_flLowerBodyYawTarget, float );
	// m_bStrafing                                 
	// m_flThirdpersonRecoil                       
	// m_bHideTargetID                             
	// m_bIsSpawnRappelling                        
	// m_vecSpawnRappellingRopeOrigin              
	NETVAR( "DT_CSPlayer->m_nSurvivalTeam", m_nSurvivalTeam, int );
	// m_hSurvivalAssassinationTarget              
	NETVAR( "DT_CSPlayer->m_flHealthShotBoostExpirationTime", m_flHealthShotBoostExpirationTime, float );
	// m_flLastExoJumpTime                         
	// cslocaldata                                 
	NETVAR( "DT_CSPlayer->m_vecOrigin", m_vecOrigin, vec3_t );
	// m_vecOrigin[2]                          
	// m_flStamina                             
	// m_iDirection      
	NETVAR( "DT_CSPlayer->m_iShotsFired", m_iShotsFired, int );
	NETVAR( "DT_CSPlayer->m_flNextAttack", m_flNextAttack, float );
	// m_nNumFastDucks                         
	// m_bDuckOverride                         
	// m_flVelocityModifier                    
	// m_unActiveQuestId                       
	// m_nQuestProgressReason                  
	// m_bPlayerDominated                      
	// m_bPlayerDominatingMe                   
	// m_iWeaponPurchasesThisRound             
	// csnonlocaldata                                                       
	// csteamdata                                  
	// m_iWeaponPurchasesThisMatch             
	// m_EquippedLoadoutItemDefIndices         
	// m_iMatchStats_Kills                         
	// m_iMatchStats_Damage                        
	// m_iMatchStats_EquipmentValue                
	// m_iMatchStats_MoneySaved                    
	// m_iMatchStats_KillReward                    
	// m_iMatchStats_LiveTime                      
	// m_iMatchStats_Deaths                        
	// m_iMatchStats_Assists            
	NETVAR( "DT_CSPlayer->m_flAnimTime", m_flAnimTime, float );
	NETVAR( "DT_CSPlayer->m_flCycle", m_flCycle, float );
	NETVAR( "DT_CSPlayer->m_vphysicsCollisionState", m_vphysicsCollisionState, int );
	// m_iMatchStats_HeadShotKills                 
	// m_iMatchStats_Objective                     
	// m_iMatchStats_CashEarned                    
	// m_iMatchStats_UtilityDamage                 
	// m_iMatchStats_EnemiesFlashed                
	// m_rank                                      
	// m_passiveItems    
	NETVAR_PTR( "DT_CSPlayer->m_hMyWearables", m_hMyWearables, c_base_handle );

	int* m_hMyWeapons( ) {
		return reinterpret_cast< int* >( uintptr_t( this ) + 0x2DF8 );
	}

	/* DT_SmokeGrenadeProjectile */
	NETVAR( "DT_SmokeGrenadeProjectile->m_nSmokeEffectTickBegin", m_nSmokeEffectTickBegin, int );

	/* DT_BaseAnimating */
	NETVAR( "DT_BaseAnimating->m_bClientSideAnimation", m_bClientSideAnimation, bool );
	NETVAR( "DT_BaseAnimating->m_nHitboxSet", m_nHitboxSet, int );
	std::array<float, 24>& m_flPoseParameter( ) {
		static int _m_flPoseParameter = netvars::get_offset( "DT_BaseAnimating->m_flPoseParameter" );
		return *( std::array<float, 24>* )( uintptr_t( this ) + _m_flPoseParameter );
	}
};
