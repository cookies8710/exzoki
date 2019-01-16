#include <exzoki/model/obj/ee_model_obj_texcoord.h>

EE_MODEL_OBJ_TEXCOORD_C::EE_MODEL_OBJ_TEXCOORD_C( void )
{
}
        
EE_MODEL_OBJ_TEXCOORD_C::EE_MODEL_OBJ_TEXCOORD_C( const std::vector< std::string > &crco_parts )
{
    Load( crco_parts );
}
        
void EE_MODEL_OBJ_TEXCOORD_C::Load( const std::vector< std::string > &crco_parts )
{
    if( crco_parts.size() == 4 && crco_parts[ 0 ] == std::string( "vt" )  )
    {
        mf_U = atof( crco_parts[ 1 ].c_str() );
        mf_V = atof( crco_parts[ 2 ].c_str() );
        mf_W = atof( crco_parts[ 3 ].c_str() );
    }
    else
        EE_ERROR_C( "EE_MODEL_OBJ_TEXCOORD_C", "Load", EE_ERROR_CODES_n::cS_Internal );
}
        
EE_FLOAT_t EE_MODEL_OBJ_TEXCOORD_C::GetU( void ) const
{
    return( mf_U );
}
        
EE_FLOAT_t EE_MODEL_OBJ_TEXCOORD_C::GetV( void ) const
{
    return( mf_V );
}
        
EE_FLOAT_t EE_MODEL_OBJ_TEXCOORD_C::GetW( void ) const
{
    return( mf_W );
}
        
