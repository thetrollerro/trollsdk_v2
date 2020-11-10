#include "menu.hpp"
#include "../hooks/hooks.hpp"

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
	/* draw menu only when opened */
	if ( !menu::opened ) return;

	static std::vector<std::string> tab = {
			"Legit",
			"Rage",
			"Antiaim",
			"Visuals",
			"Misc",
			"Skins"
	};

	enum tab_select : int {
		legit, rage, antiaim, visuals, misc, skins
	};

	/* vars */
	static int current_tab = visuals;
	ImGui::SetNextWindowSize( ImVec2( 560, 440 ), ImGuiCond_Always );
	ImGui::Begin( "TrollerWare.xyz", &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar );
	{
		ImGui::SetCursorPosX( ImGui::GetWindowWidth( ) / 2 - ImGui::CalcTextSize( "TrollerWare" ).x / 2 );
		ImGui::Text( "TrollerWare" );

		static float rainbowSpeed = 0.005;
		static float staticHue = 0;
		ImDrawList* draw_list = ImGui::GetWindowDrawList( );
		ImVec2 panelPos = ImGui::GetWindowPos( );
		auto pos = ImVec2( panelPos.x, panelPos.y + ImGui::CalcTextSize( "TrollerWare" ).y * 2 );
		staticHue -= rainbowSpeed;
		if ( staticHue < -1.f ) staticHue += 1.f;
		for ( int i = 0; i <= 560; i++ )
		{
			float hue = staticHue + ( 1.f / ( float ) 560 ) * i;
			if ( hue < 0.f ) hue += 1.f;
			ImColor cRainbow = ImColor::HSV( hue, 1.f, 1.f );
			draw_list->AddRectFilled( ImVec2( pos.x + i, pos.y ), ImVec2( pos.x + i + 1, pos.y + 4 ), cRainbow );
		}

		for ( int i = 0; i < tab.size( ); i++ )
		{
			if ( i == current_tab )
				ImGui::GetStyle( ).Colors[ ImGuiCol_Button ] = ImColor( 20, 20, 20, 255 ); //main
			else
				ImGui::GetStyle( ).Colors[ ImGuiCol_Button ] = ImColor( 15, 15, 15, 255 ); //main

			if ( ImGui::Button( tab[ i ].c_str( ), ImVec2( 83, 22 ) ) )
				current_tab = i;

			if ( i < tab.size( ) - 1 )
				ImGui::SameLine( );
		}

		ImGui::BeginChild( "##THIS IS A CHILD DONT BE A PEDO", ImVec2( -1, -1 ), true );
		{
			switch ( current_tab )
			{
			case legit: break;
			case rage:  break;
			case antiaim: break;
			case visuals:  break;
			case misc: misc_tab( ); break;
			case skins: break;
			}
		}ImGui::EndChild( );
	}
	ImGui::End( );
}

void menu::misc_tab( ) {
	ImGui::Columns( 2, NULL, false );
	const char* strafer[ ] = { "Off", "Normal", "Directional" };
	ImGui::BeginChild( "Movement", ImVec2( 230, 150 ), true ); {
		text( "Movement", 230 );

		if ( ImGui::Button( "Unload" ) )
			g_vars.misc.unload = true;
	}
	ImGui::EndChild( );
	ImGui::BeginChild( "Buy-Bot", ImVec2( 230, 150 ), true ); {
		text( "Buy-Bot", 230 );

	}
	ImGui::EndChild( );
	ImGui::NextColumn( );

	ImGui::BeginChild( "Miscellaneous", ImVec2( 230, 160 ), true ); {
		
	}
	ImGui::EndChild( );
	ImGui::BeginChild( "Config", ImVec2( 230, 140 ), true ); {
		text( "Config", 230 );
		ImGui::SetCursorPosY( ImGui::GetCursorPosY( ) - 10 );
		get_config( );
		ImGui::PushItemWidth( -1 );
		if ( ImGui::Combo( "##cfg", &selectedcfg, [ ] ( void* data, int idx, const char** out_text )
		{
			*out_text = configs[ idx ].c_str( );
			return true;
		}, nullptr, configs.size( ), 10 ) )
		{
			cfgname = configs[ selectedcfg ];
			cfgname.erase( cfgname.length( ) - 4, 4 );
			strcpy( g_vars.misc.config_name, cfgname.c_str( ) );
		}
		ImGui::PopItemWidth( );

		static bool create;

		if ( ImGui::Button( "New config", ImVec2( -1, 15 ) ) ) create = !create;

		if ( ImGui::Button( "Save", ImVec2( -1, 15 ) ) )
		{
			g_vars.save_config( );
		}
		if ( ImGui::Button( "Load", ImVec2( -1, 15 ) ) )
		{
			g_vars.load_config( );
		}

		if ( ImGui::Button( "Reset settings", ImVec2( -1, 15 ) ) ) g_vars.setup_config( );

		if ( create )
		{
			ImGui::SetNextWindowSize( ImVec2( 260, 160 ), ImGuiCond_Always );
			ImGui::Begin( "##createconfig", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar );
			{
				ImGui::Text( "Config name:" );
				ImGui::InputText( "Name", g_vars.misc.config_name, 52 );
				if ( ImGui::Button( "Create & Save", ImVec2( -1, 15 ) ) )
				{
					g_vars.save_config( );
					create = !create;
				}
				if ( ImGui::Button( "Cancel", ImVec2( -1, 15 ) ) )
					create = !create;
				ImGui::End( );
			}
		}
	}
	ImGui::EndChild( );
}


void menu::style( IDirect3DDevice9* dev ) {
	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( hooks::csgo_window );
	ImGui_ImplDX9_Init( dev );

	/* add font */
	ImGuiIO& io = ImGui::GetIO( );
	io.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\Verdana.ttf", 14.f, NULL, io.Fonts->GetGlyphRangesDefault( ) );
	ImGuiStyle& style = ImGui::GetStyle( );

	style.Alpha = 1.f;
	style.WindowPadding = ImVec2( 13.f, 13.f );
	style.WindowTitleAlign = ImVec2( 0.005f, 0.5f );
	style.SelectableTextAlign = ImVec2( 0.5f, 0.5f );
	style.ItemSpacing = ImVec2( 8.f, 12.f );
	style.ItemInnerSpacing = ImVec2( 8.f, 8.f );
	style.ColumnsMinSpacing = 0.f;
	style.AntiAliasedLines = true;
	style.FramePadding = ImVec2( 2.f, 2.f );
	style.ScrollbarSize = 4.f;
	style.GrabMinSize = 4.f;
	style.ChildBorderSize = 1.f;
	style.PermanentItemWidth = 140.f;
	style.ButtonTextAlign = ImVec2( 0.5f, 0.3f );

	static const float main_rounding = 2.f;
	static const float window_rounding = 6.f;
	style.WindowRounding = window_rounding;
	style.ChildRounding = window_rounding;
	style.PopupRounding = main_rounding;
	style.FrameRounding = main_rounding;
	style.ScrollbarRounding = main_rounding;
	style.GrabRounding = main_rounding;
	style.TabRounding = main_rounding;

	/* colors */
	const auto main_color = ImColor( 57, 57, 57, 100 );
	const auto purple = ImColor( 3, 136, 252, 255 );

	ImVec4* colors = style.Colors;

	/* text */
	colors[ ImGuiCol_Text ] = ImColor( 200, 200, 200, 255 );
	colors[ ImGuiCol_TextDisabled ] = colors[ ImGuiCol_Text ];
	colors[ ImGuiCol_TextSelectedBg ] = colors[ ImGuiCol_Text ];

	/* window */
	colors[ ImGuiCol_WindowBg ] = ImColor( 0, 0, 0 );
	colors[ ImGuiCol_ChildBg ] = ImColor( 15, 15, 15 );
	colors[ ImGuiCol_MenuBarBg ] = main_color;

	/* border */
	colors[ ImGuiCol_Border ] = ImColor( 66, 66, 66, 255 );
	colors[ ImGuiCol_BorderShadow ] = ImColor( 51, 51, 51, 255 );

	/* frame */
	colors[ ImGuiCol_PopupBg ] = colors[ ImGuiCol_ChildBg ];
	colors[ ImGuiCol_FrameBg ] = main_color;
	colors[ ImGuiCol_FrameBgHovered ] = main_color;
	colors[ ImGuiCol_FrameBgActive ] = main_color;

	/* title */
	colors[ ImGuiCol_TitleBg ] = colors[ ImGuiCol_WindowBg ];
	colors[ ImGuiCol_TitleBgActive ] = colors[ ImGuiCol_WindowBg ];
	colors[ ImGuiCol_TitleBgCollapsed ] = colors[ ImGuiCol_WindowBg ];

	/* scroll-bar */
	colors[ ImGuiCol_ScrollbarBg ] = ImVec4( 0.02f, 0.02f, 0.02f, 0.00f );
	colors[ ImGuiCol_ScrollbarGrab ] = ImVec4( 0.31f, 0.31f, 0.31f, 0.00f );
	colors[ ImGuiCol_ScrollbarGrabHovered ] = main_color;
	colors[ ImGuiCol_ScrollbarGrabActive ] = main_color;

	/* check-mark */
	colors[ ImGuiCol_CheckMark ] = purple;
	/* slider */
	colors[ ImGuiCol_SliderGrab ] = purple;
	colors[ ImGuiCol_SliderGrabActive ] = purple;

	/* button */
	colors[ ImGuiCol_Button ] = ImColor( 15, 15, 15, 255 );
	colors[ ImGuiCol_ButtonHovered ] = ImColor( 20, 20, 20, 255 );
	colors[ ImGuiCol_ButtonAnimActive ] = purple;
	colors[ ImGuiCol_ButtonAnimInactive ] = ImColor( 214, 94, 122, 255 );
	colors[ ImGuiCol_ButtonActive ] = ImColor( 20, 20, 20, 255 );

	/* header */
	colors[ ImGuiCol_Header ] = main_color;
	colors[ ImGuiCol_HeaderHovered ] = purple;
	colors[ ImGuiCol_HeaderActive ] = purple;

	/* resize */
	colors[ ImGuiCol_ResizeGrip ] = main_color;
	colors[ ImGuiCol_ResizeGripHovered ] = main_color;
	colors[ ImGuiCol_ResizeGripActive ] = main_color;

}