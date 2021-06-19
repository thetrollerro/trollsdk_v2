#include "../hooks.hpp"

void __fastcall hooks::panel::paint_traverse::hook( void* ecx, void* edx, vgui::vpanel vgui_panel, bool force_repaint, bool allow_force ) {
	static auto panel_id = vgui::vpanel { 0 };
	o_paint_traverse( ecx, edx, vgui_panel, force_repaint, allow_force );

	if ( !panel_id ) {
		auto panel_name = i::panel->get_name( vgui_panel );
		if ( !strcmp( panel_name, "FocusOverlayPanel" ) ) {
			panel_id = vgui_panel;
		}
	}
	else if ( panel_id == vgui_panel ) {
		if ( !i::engine->is_in_game( ) || !g_local ) {
			return;
		}
	}
}