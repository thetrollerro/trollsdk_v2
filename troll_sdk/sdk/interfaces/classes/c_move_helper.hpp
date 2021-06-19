#pragma once

class c_base_player;
class c_move_helper {
public:

	bool m_bfirstrunoffunctions : 1;
	bool m_bgamecodemovedplayer : 1;
	int m_nplayerhandle; // edict index on server, client entity handle on client=
	int m_nimpulsecommand; // impulse command issued.
	vec3_t m_vecviewangles; // command view angles (local space)
	vec3_t m_vecabsviewangles; // command view angles (world space)
	int m_nbuttons; // attack buttons.
	int m_noldbuttons; // from host_client->oldbuttons;
	float m_flforwardmove;
	float m_flsidemove;
	float m_flupmove;
	float m_flmaxspeed;
	float m_flclientmaxspeed;
	vec3_t m_vecvelocity; // edict::velocity // current movement direction.
	vec3_t m_vecangles; // edict::angles
	vec3_t m_vecoldangles;
	float m_outstepheight; // how much you climbed this move
	vec3_t m_outwishvel; // this is where you tried 
	vec3_t m_outjumpvel; // this is your jump velocity
	vec3_t m_vecconstraintcenter;
	float m_flconstraintradius;
	float m_flconstraintwidth;
	float m_flconstraintspeedfactor;
	float m_flunknown[5];
	vec3_t m_vecabsorigin;

	virtual void pad00() = 0;
	virtual void set_host(c_base_player* host) = 0;
	virtual void pad01() = 0;
	virtual void pad02() = 0;
	virtual void process_impacts() = 0;
};