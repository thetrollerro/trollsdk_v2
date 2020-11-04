#pragma once

class c_base_player;
class c_move_helper {
public:
	virtual void pad00( ) = 0;
	virtual void set_host( c_base_player* host ) = 0;
	virtual void pad01( ) = 0;
	virtual void pad02( ) = 0;
	virtual void process_impacts( ) = 0;
};