#pragma once

struct datamap_t;

class typedescription_t
{
public:
	int field_type; //0x0000
	char* field_name; //0x0004
	int field_offset[ 2 ]; //0x0008
	int field_size_UNKNOWN; //0x0010
	int flags_UNKNWON; //0x0012
	char pad_0014[ 12 ]; //0x0014
	datamap_t* td; //0x0020
	char pad_0024[ 24 ]; //0x0024
}; // size: 0x003C

struct datamap_t
{
	typedescription_t* data_description;
	int data_fields;
	char const* data_class_name;
	datamap_t* base_map;
	bool chains_validated;
	bool packed_offsets_computed;
	int packed_size;
};
