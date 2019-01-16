#include <exzoki/model/obj/ee_model_obj_vertex.h>

EE_MODEL_OBJ_VERTEX_C::EE_MODEL_OBJ_VERTEX_C( void )
{
}

EE_MODEL_OBJ_VERTEX_C::EE_MODEL_OBJ_VERTEX_C( const std::vector< std::string > &crco_parts )
{
    Load( crco_parts );
}
        
void EE_MODEL_OBJ_VERTEX_C::Load( const std::vector< std::string > &crco_parts )
{
    if( crco_parts.size() == 4 && crco_parts[ 0 ] == std::string( "v" )  )
    {
        mf_X = atof( crco_parts[ 1 ].c_str() );
        mf_Y = atof( crco_parts[ 2 ].c_str() );
        mf_Z = atof( crco_parts[ 3 ].c_str() );
        
        mf_X = trunc( mf_X * 1000.0 ) * .001;
        mf_Y = trunc( mf_Y * 1000.0 ) * .001;
        mf_Z = trunc( mf_Z * 1000.0 ) * .001;
    }
    else
        EE_ERROR_C( "EE_MODEL_OBJ_VERTEX_C", "Load", EE_ERROR_CODES_n::cS_Internal );
}
        
EE_FLOAT_t EE_MODEL_OBJ_VERTEX_C::GetX( void ) const
{
    return( mf_X );
}

EE_FLOAT_t EE_MODEL_OBJ_VERTEX_C::GetY( void ) const
{
    return( mf_Y );
}    
    
EE_FLOAT_t EE_MODEL_OBJ_VERTEX_C::GetZ( void ) const
{
    return( mf_Z );
}
