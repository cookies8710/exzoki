#include <exzoki/model/obj/ee_model_obj_face.h>
        
EE_MODEL_OBJ_FACE_C* EE_MODEL_OBJ_FACE_C::Load( const std::vector< std::string > &crco_parts )
{           
    if( crco_parts.size() != 4 && crco_parts.size() != 5 )
        EE_ERROR_C( "EE_MODEL_OBJ_FACE_C", "Load", EE_ERROR_CODES_n::cS_Internal );
    if( crco_parts[ 0 ] != std::string( "f" )  )
        EE_ERROR_C( "EE_MODEL_OBJ_FACE_C", "Load", EE_ERROR_CODES_n::cS_Internal );
            
    EE_U32_t u32_Dummy;
    EE_U32_t u32_V1, u32_V2, u32_V3, u32_V4;    
    EE_U32_t u32_TC1, u32_TC2, u32_TC3, u32_TC4;      
    
    Decode( crco_parts[ 1 ], u32_V1, u32_TC1, u32_Dummy );
    Decode( crco_parts[ 2 ], u32_V2, u32_TC2, u32_Dummy );
    Decode( crco_parts[ 3 ], u32_V3, u32_TC3, u32_Dummy );    
    
    if( crco_parts.size() == 4 )
    {
        mu32_V1 = u32_V1;   
        mu32_V2 = u32_V2;   
        mu32_V3 = u32_V3; 
        
        mu32_TC1 = u32_TC1; 
        mu32_TC2 = u32_TC2;
        mu32_TC3 = u32_TC3;  
    }
    else
    {
        Decode( crco_parts[ 4 ], u32_V4, u32_TC4, u32_Dummy );
        
        mu32_V1 = u32_V1;   
        mu32_V2 = u32_V2;   
        mu32_V3 = u32_V4; 
        
        mu32_TC1 = u32_TC1; 
        mu32_TC2 = u32_TC2;
        mu32_TC3 = u32_TC4; 
        
        EE_MODEL_OBJ_FACE_C *pC_Face2( new EE_MODEL_OBJ_FACE_C() );
                
        pC_Face2->mu32_V1 = u32_V2;
        pC_Face2->mu32_TC1 = u32_TC2;
        pC_Face2->mu32_V2 = u32_V4;
        pC_Face2->mu32_TC2 = u32_TC4;  
        pC_Face2->mu32_V3 = u32_V3;
        pC_Face2->mu32_TC3 = u32_TC3;        
                
        return( pC_Face2 ); 
    }        
    
    return( 0 );  
}
        
EE_U32_t EE_MODEL_OBJ_FACE_C::GetVertex1Index( void ) const
{
    return( mu32_V1 );
}
        
EE_U32_t EE_MODEL_OBJ_FACE_C::GetVertex2Index( void ) const
{ 
    return( mu32_V2 );
}

EE_U32_t EE_MODEL_OBJ_FACE_C::GetVertex3Index( void ) const
{
    return( mu32_V3 );
}
        
EE_U32_t EE_MODEL_OBJ_FACE_C::GetVertex1TexCoordIndex( void ) const
{
    return( mu32_TC1 );
}

EE_U32_t EE_MODEL_OBJ_FACE_C::GetVertex2TexCoordIndex( void ) const
{
    return( mu32_TC2 );
}

EE_U32_t EE_MODEL_OBJ_FACE_C::GetVertex3TexCoordIndex( void ) const
{
    return( mu32_TC3 );
}
            
void EE_MODEL_OBJ_FACE_C::Decode( std::string S_src, 
                                  EE_U32_t &ru32_vertexIndex,
                                  EE_U32_t &ru32_texCoordIndex,
                                  EE_U32_t &ru32_normalIndex )
{
    std::string S_VertexIndex, S_TexCoordIndex, S_NormalIndex;
    EE_U32_t u32_I, u32_J;
            
    // Najdu prvni lomitko
    u32_I = S_src.find( "/" ); 
    if( u32_I >= S_src.size() )
    {
                // Lomitko nenalezeno -> pouze vertex index
        S_VertexIndex = S_src;
        ru32_vertexIndex = atoi( S_VertexIndex.c_str() );
        return;      
    }
    else            
    {
        // Lomitko nalezeno -> vyjmu vertex index
        S_VertexIndex = S_src.substr( 0, u32_I );    
        ru32_vertexIndex = atoi( S_VertexIndex.c_str() ); 
        // Novy zdroj bude bez vertex indexu          
        S_src = S_src.substr( u32_I + 1, S_src.size() );   
    }
            
    // Najdu druhe lomitko
    u32_J = S_src.find( "/" );            
    if( u32_J >= S_src.size() )
    {
        // Lomitko nenalezeno -> nactu pouze tex coordy
        S_TexCoordIndex = S_src;
        ru32_texCoordIndex = atoi( S_TexCoordIndex.c_str() );
        return;      
    }
    else
    {
        // Lomitko nalezeno -> nactu tex coordy
        S_TexCoordIndex = S_src.substr( 0, u32_J );    
        ru32_texCoordIndex = atoi( S_TexCoordIndex.c_str() ); 
        // Ze zbytku vytahnu index normaly          
        S_src = S_src.substr( u32_J + 1, S_src.size() );
        S_NormalIndex = S_src;  
        ru32_normalIndex = atoi( S_NormalIndex.c_str() );                 
    }       
          
    return;
}
