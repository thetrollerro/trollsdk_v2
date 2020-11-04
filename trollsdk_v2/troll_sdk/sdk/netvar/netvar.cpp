#include "netvar.hpp"
#include "../../sdk/interfaces/interfaces.hpp"
std::unordered_map< std::string, int > netvars::m_client_ids;
std::unordered_map< std::string, std::unordered_map< std::string, netvars::netvar_data_t > > netvars::m_offsets;

std::vector< std::string > split( std::string to_split, std::string delimeter ) {
	std::vector< std::string > split;
	int start = 0;
	int end = 0;

	while ( ( end = to_split.find( delimeter, start ) ) < to_split.size( ) ) {
		std::string val = to_split.substr( start, end - start );
		split.push_back( val );
		start = end + delimeter.size( );
	}

	if ( start < to_split.size( ) ) {
		std::string val = to_split.substr( start );
		split.push_back( val );
	}

	return split;
}

bool netvars::init( ) {
	// sanity check on client->
	if ( !i::clientdll )
		return false;

	// grab linked list.
	auto list = i::clientdll->get_all_classes( );
	if ( !list )
		return false;

	// iterate list of netvars.
	for ( ; list != nullptr; list = list->next_ptr )
		store_table( list->recvtable_ptr->table_name, list->recvtable_ptr );

	return true;
}

void netvars::store_table( const std::string& name, recv_table* table, std::size_t offset ) {
	// iterate props
	for ( int i { }; i < table->props_count; ++i ) {
		auto prop = &table->props[ i ];
		auto child = prop->data_table;

		// we have a child table, that contains props.
		if ( child && child->props_count > 0 )
			store_table( name, child, prop->offset + offset );

		// insert if not present.
		if ( !m_offsets[ name ][ prop->prop_name ].m_offset ) {
			m_offsets[ name ][ prop->prop_name ].m_datamap_var = false;
			m_offsets[ name ][ prop->prop_name ].m_prop_ptr = prop;
			m_offsets[ name ][ prop->prop_name ].m_offset = static_cast< size_t >( prop->offset + offset );
		}
	}
}

// get client id.
int netvars::get_client_id( const std::string& network_name ) {
	return m_client_ids[ network_name ];
}

// get netvar offset.
int netvars::get( const std::string& table, const std::string& prop ) {
	return m_offsets[ table ][ prop ].m_offset;
}

int netvars::get_offset( const char* name ) {
	const auto items = split( name, "->" );
	return m_offsets[ items.front( ) ][ items.back( ) ].m_offset;
}