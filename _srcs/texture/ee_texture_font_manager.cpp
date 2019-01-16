#include <exzoki/texture/ee_texture_font_manager.h>

EE_TEXTURE_FONT_MANAGER_C::EE_TEXTURE_FONT_MANAGER_C( void )
{
}

EE_TEXTURE_FONT_MANAGER_C::~EE_TEXTURE_FONT_MANAGER_C( void )
{
}
        
void EE_TEXTURE_FONT_MANAGER_C::SetFont( EE_CCSTRING_t ccs_path )
{
    mcI_CurrentFont = mco_Storage.find( std::string( ccs_path ) );   
}

void EE_TEXTURE_FONT_MANAGER_C::Print( EE_FLOAT_t f_size, EE_CCSTRING_t ccs_format, ... ) const
{
    va_list p_Argument;
 	EE_CHAR_t ac_OutputString[ 1024 ];
 
 	va_start( p_Argument, ccs_format );
 	vsprintf( ac_OutputString, ccs_format, p_Argument );
 	va_end( p_Argument );
     
    mcI_CurrentFont->second.Print( f_size, ac_OutputString );      
}
