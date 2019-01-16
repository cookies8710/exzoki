#include <exzoki/texture/ee_texture_manager.h>

EE_TEXTURE_MANAGER_C::EE_TEXTURE_MANAGER_C( void )
{
}

EE_TEXTURE_MANAGER_C::~EE_TEXTURE_MANAGER_C( void )
{
    Clear();
}
        
void EE_TEXTURE_MANAGER_C::Load( EE_CCSTRING_t ccs_path, 
                                 EE_TEXTURE_FILTERING_e e_filtering,
                                 EE_TEXTURE_ALPHA_e e_alpha,
                                 EE_BYTE_t b_r,
                                 EE_BYTE_t b_g,
                                 EE_BYTE_t b_b,
                                 EE_S32_t s32_wrapS,
                                 EE_S32_t s32_wrapT,
                                 EE_S32_t s32_envMode )
{
    if( ++mco_Counter[ std::string( ccs_path ) ] == 1 ) // ? mozna chyba
        mco_Storage[ std::string( ccs_path ) ].Load( ccs_path,
                                                     e_filtering,
                                                     e_alpha,
                                                     b_r,
                                                     b_g,
                                                     b_b,
                                                     s32_wrapS,
                                                     s32_wrapT,
                                                     s32_envMode );          
}

inline void EE_TEXTURE_MANAGER_C::operator[]( EE_CCSTRING_t ccs_path ) const
{
    Bind( ccs_path );    
}

inline void EE_TEXTURE_MANAGER_C::Bind( EE_CCSTRING_t ccs_path, EE_S32_t s32_layer ) const
{
    std::map< std::string, EE_TEXTURE_C >::const_iterator cI_Texture = 
        mco_Storage.find( std::string( ccs_path ) );
 	
    if( cI_Texture != mco_Storage.end() )
  		cI_Texture->second.Bind( s32_layer );
 	else
  		EE_ERROR_C( "EE_TEXTURE_MANAGER_C", "Bind", EE_ERROR_CODES_n::cS_TextureDoesntExist, ccs_path );
      
}  
        
