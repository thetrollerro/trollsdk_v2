#pragma once
#include <cstdint>
#include "../../classes/i_client_entity.hpp"
#include "../../math/vector.hpp"
#include "../../utl.hpp"

class glow_object_definition_t
{
public:
    glow_object_definition_t( ) { memset( this, 0, sizeof( *this ) ); }

    int32_t next_free_slot;
    class i_client_entity* entity;
    union
    {
        vec3_t glow_color;
        struct
        {
            float  red;
            float  green;
            float  blue;
        };
    };
    float   alpha;
    uint8_t pad_0014[ 4 ];
    float   some_float;
    uint8_t pad_001C[ 4 ];
    float   another_float;
    bool    render_when_occluded;
    bool    render_when_unoccluded;
    bool    full_bloom_render;
    uint8_t pad_0027[ 5 ];
    int32_t glow_style;
    int32_t split_screen_slot;

    bool is_unused( ) const { return next_free_slot != entry_in_use; }

    static const int end_of_free_list = -1;
    static const int entry_in_use = -2;
}; //Size: 0x0038 (56)

class c_glow_object_manager
{
public:
    int register_glow_object( i_client_entity* pEntity, const vec3_t& vGlowColor, float flGlowAlpha, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded, int nSplitScreenSlot )
    {
        int index;
        if ( first_free_slot == glow_object_definition_t::end_of_free_list ) {
            index = m_glow_object_definitions.AddToTail( );
        }
        else {
            index = first_free_slot;
            first_free_slot = m_glow_object_definitions[ index ].next_free_slot;
        }

       m_glow_object_definitions[ index ].entity = pEntity;
       m_glow_object_definitions[ index ].glow_color = vGlowColor;
       m_glow_object_definitions[ index ].alpha = flGlowAlpha;
       m_glow_object_definitions[ index ].render_when_occluded = bRenderWhenOccluded;
       m_glow_object_definitions[ index ].render_when_unoccluded = bRenderWhenUnoccluded;
       m_glow_object_definitions[ index ].split_screen_slot = nSplitScreenSlot;
       m_glow_object_definitions[ index ].next_free_slot = glow_object_definition_t::entry_in_use;

        return index;
    }

    void UnregisterGlowObject( int glow_object_handle )
    {
        m_glow_object_definitions[ glow_object_handle ].next_free_slot = first_free_slot;
        m_glow_object_definitions[ glow_object_handle ].entity = NULL;
        first_free_slot = glow_object_handle;
    }

    void SetEntity( int glow_object_handle, i_client_entity* entity )
    {
        m_glow_object_definitions[ glow_object_handle ].entity = entity;
    }

    void SetColor( int glow_object_handle, const vec3_t& glow_color )
    {
        m_glow_object_definitions[ glow_object_handle ].glow_color = glow_color;
    }

    void SetAlpha( int glow_object_handle, float alpha )
    {
        m_glow_object_definitions[ glow_object_handle ].alpha = alpha;
    }

    void SetRenderFlags( int glow_object_handle, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded )
    {
        m_glow_object_definitions[ glow_object_handle ].render_when_occluded = bRenderWhenOccluded;
        m_glow_object_definitions[ glow_object_handle ].render_when_unoccluded = bRenderWhenUnoccluded;
    }

    bool IsRenderingWhenOccluded( int glow_object_handle ) const
    {
        return m_glow_object_definitions[ glow_object_handle ].render_when_occluded;
    }

    bool IsRenderingWhenUnoccluded( int glow_object_handle ) const
    {
        return m_glow_object_definitions[ glow_object_handle ].render_when_unoccluded;
    }

    bool HasGlowEffect( i_client_entity* entity ) const
    {
        for ( int i = 0; i < m_glow_object_definitions.Count( ); ++i ) {
            if ( !m_glow_object_definitions[ i ].is_unused( ) && m_glow_object_definitions[ i ].entity == entity ) {
                return true;
            }
        }

        return false;
    }


    CUtlVector<glow_object_definition_t> m_glow_object_definitions; //0x0000
    int first_free_slot;                                       //0x000C
};