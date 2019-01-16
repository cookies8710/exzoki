#include <exzoki/model/obj/ee_model_obj_material.h>

void EE_MODEL_OBJ_MATERIAL_C::SetName( const std::string &crS_name )
{
    mS_Name = crS_name;
}
void EE_MODEL_OBJ_MATERIAL_C::SetTextureFilename( const std::string &crS_name )
{
    mS_TextureFilename = crS_name;
}
void EE_MODEL_OBJ_MATERIAL_C::SetColor( EE_FLOAT_t f_r, EE_FLOAT_t f_g, EE_FLOAT_t f_b )
{
    mf_ColorR = f_r;
    mf_ColorG = f_g;
    mf_ColorB = f_b;
}
        
const std::string& EE_MODEL_OBJ_MATERIAL_C::GetName( void ) const
{
    return( mS_Name );
}
const std::string& EE_MODEL_OBJ_MATERIAL_C::GetTextureFilename( void ) const
{
    return( mS_TextureFilename );
}
EE_FLOAT_t EE_MODEL_OBJ_MATERIAL_C::GetColorR( void ) const
{
    return( mf_ColorR );
}
EE_FLOAT_t EE_MODEL_OBJ_MATERIAL_C::GetColorG( void ) const
{
    return( mf_ColorG );
}
EE_FLOAT_t EE_MODEL_OBJ_MATERIAL_C::GetColorB( void ) const
{
    return( mf_ColorB );
}
