#include <exzoki/map/ee_map_face.h>

EE_MAP_FACE_C::EE_MAP_FACE_C( void )
{
}

EE_MAP_FACE_C::EE_MAP_FACE_C( EE_U32_t u32_vi1, 
                              EE_U32_t u32_vi2, 
                              EE_U32_t u32_vi3 ): EE_MODEL_FACE_C( u32_vi1, u32_vi2, u32_vi3 )
{
}

void EE_MAP_FACE_C::SetMaterialIndex( EE_U32_t u32_material )
{
    mu32_MaterialIndex = u32_material;
}

void EE_MAP_FACE_C::SetTexCoordIndexA( EE_U32_t u32_tca )
{
    mu32_TexCoordIndexA = u32_tca;  
}

void EE_MAP_FACE_C::SetTexCoordIndexB( EE_U32_t u32_tcb )
{
    mu32_TexCoordIndexB = u32_tcb;  
}

void EE_MAP_FACE_C::SetTexCoordIndexC( EE_U32_t u32_tcc )
{
    mu32_TexCoordIndexC = u32_tcc;  
}
        
EE_U32_t EE_MAP_FACE_C::GetMaterialIndex( void ) const
{
    return( mu32_MaterialIndex );    
}

EE_U32_t EE_MAP_FACE_C::GetTexCoordIndex( EE_BYTE_t b_vertex ) const
{
    switch( b_vertex )    
    {
        case 0:
            return(mu32_TexCoordIndexA);
            break;
        case 1:
            return(mu32_TexCoordIndexB);
            break;
        case 2:  
            return(mu32_TexCoordIndexC);  
            break;
    }
    
}

EE_U32_t EE_MAP_FACE_C::GetTexCoordIndexA( void ) const
{
    return( mu32_TexCoordIndexA );    
}

EE_U32_t EE_MAP_FACE_C::GetTexCoordIndexB( void ) const
{
    return( mu32_TexCoordIndexB );    
}

EE_U32_t EE_MAP_FACE_C::GetTexCoordIndexC( void ) const
{
    return( mu32_TexCoordIndexC );    
}
       

