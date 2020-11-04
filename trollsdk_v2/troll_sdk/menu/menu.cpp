#include "menu.hpp"
#include "../hooks/hooks.hpp"

std::string to_lower( std::string str ) {
	std::transform( str.begin( ), str.end( ), str.begin( ), ( int( * )( int ) )std::tolower );
	return str;
}

void text( const char* name, int x )
{
	auto text_size = ImGui::CalcTextSize( name );
	ImGui::SetCursorPosY( text_size.y / 2 );
	ImGui::SetCursorPosX( x / 2 - text_size.x / 2 );
	ImGui::Text( name );
	ImGui::Separator( );
};
void menu::init( ) {
	/* start imgui */
	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );

	/* draw the menu */
	menu::render( );

	/* end imgui */
	ImGui::EndFrame( );
	ImGui::Render( );
	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
}

void menu::render( ) {

}



void menu::style( IDirect3DDevice9* dev ) {
	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( hooks::csgo_window );
	ImGui_ImplDX9_Init( dev );

	/* add font */
	ImGuiIO& io = ImGui::GetIO( );
	io.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\Verdana.ttf", 14.f, NULL, io.Fonts->GetGlyphRangesDefault( ) );

	/* do ur styles and colors */
}