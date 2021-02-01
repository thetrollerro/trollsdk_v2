#pragma once
#include <vector>
#include <string>
#include <iostream>

inline int selectedcfg = 0;
inline std::vector<std::string> configs;
inline std::string cfgname = "default";

extern void get_config( );

template <typename t>
class config_item
{
	std::string category, name;
	t* value;
public:
	config_item( std::string category, std::string name, t* value )
	{
		this->category = category;
		this->name = name;
		this->value = value;
	}
};

template <typename t>
class config_value
{
public:
	config_value( std::string category_, std::string name_, t* value_ )
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	t* value;
};

class vars {
public:
	struct misc {
		char config_name[ 52 ];
		bool unload = false;
	}misc;
protected:
	std::vector<config_value<int>*> ints;
	std::vector<config_value<bool>*> bools;
	std::vector<config_value<float>*> floats;
private:
	void add_var( int&, int, std::string, std::string );
	void add_var( bool&, bool, std::string, std::string );
	void add_var( float&, float, std::string, std::string );
public:
	vars( )
	{
		setup_config( );
	}

	void setup_config( );

	void save_config( );
	void load_config( );
private:
	void save_ragebot( );
	void save_antiaim( );
	void save_legitbot( );
	void save_esp( );
	void save_misc( );
	void save_skins( );
};
inline vars g_vars;

namespace keyhandler {
	bool is_key_down( int key );
	bool is_key_up( int key );
	bool is_key_pressed( int key );

	bool auto_check( int key_style, int key );

	static bool keys[ 256 ] = { false };
	static bool pressed[ 256 ] = { false };
	static bool toggles[ 256 ] = { false };
};