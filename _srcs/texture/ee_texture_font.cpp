#include <exzoki/texture/ee_texture_font.h>

EE_TEXTURE_FONT_C::EE_TEXTURE_FONT_C( void ): mb_FontLoaded( EE_FALSE )
{
}

EE_TEXTURE_FONT_C::~EE_TEXTURE_FONT_C( void )
{
	Destroy();	
}

void EE_TEXTURE_FONT_C::Load( EE_CCSTRING_t ccs_path )
{
 	// Pokud je již naèten nìjaký texture font, smažu ho
	if( mb_FontLoaded == EE_TRUE )
		Destroy();
	
	// Nahraju texturu
	EE_TEXTURE_C::Load( ccs_path, 
                        EE_EXZOKI_n::ce_TEXTURE_FONT_FILTERING, 
                        EE_TEXTURE_ALPHA_BY_GREYSCALE, 0, 0, 0, GL_CLAMP, GL_CLAMP );
	
	 
	const EE_FLOAT_t cf_TextureUnit = 1.0f / 16.0f;
 	EE_FLOAT_t f_Left, f_Right, f_Top, f_Bottom;
 	EE_FLOAT_t f_Temp;
	
	// Vytvoøím místo pro 256 textur - znakù
 	mu32_Base = glGenLists( 256 );
 
 	// Vytvoøím znaky z pùvodní textury
	for( EE_U32_t u32_CurrentChar = 0; u32_CurrentChar < 256; u32_CurrentChar++ )
 	{
  		f_Left = ( u32_CurrentChar % 16 ) * cf_TextureUnit;
  		f_Right = cf_TextureUnit * ( ( u32_CurrentChar % 16 ) + 1.0f );
  		f_Top = 1.0f - ( u32_CurrentChar / 16 ) * cf_TextureUnit;
  		f_Bottom = 1.0f - cf_TextureUnit * ( ( u32_CurrentChar / 16 ) + 1.0f );

  		glNewList( mu32_Base + u32_CurrentChar, GL_COMPILE );
   		EE_TEXTURE_C::Bind();
   		glBegin( GL_QUADS );
   			f_Temp = cf_TextureUnit * EE_FLOAT_t( u32_CurrentChar / 16 );
   			glTexCoord2f( f_Left, 1.0f - f_Temp - cf_TextureUnit ); glVertex2f(0.0f, 0.0f);
   			glTexCoord2f( f_Right, 1.0f - f_Temp - cf_TextureUnit ); glVertex2f(1.0f, 0.0f);
   			glTexCoord2f( f_Right, 1.0f - f_Temp ); glVertex2f( 1.0f, 1.0f );
   			glTexCoord2f( f_Left, 1.0f - f_Temp ); glVertex2f( 0.0f, 1.0f );
   		glEnd();
   		glTranslatef( EE_EXZOKI_n::cf_TextureFontRelativeWidth, 0.0f, 0.0f );
  		glEndList();
 	}
 	
 	// Font je naèten
	mb_FontLoaded = EE_TRUE;
 	
 	return;
}

void EE_TEXTURE_FONT_C::Print( EE_FLOAT_t f_size, EE_CCSTRING_t cpc_format, ... ) const
{
 	// Zkontroluju, zda je nìjaký font naèten
	if( mb_FontLoaded != EE_TRUE )
 		EE_ERROR_C( "EE_TEXTURE_FONT_C", "Print", EE_ERROR_CODES_n::cS_NoTextureLoaded );
	 
	va_list p_Argument;
 	EE_CHAR_t ac_OutputString[ 1024 ]; // 1024 ?
 
 	va_start( p_Argument, cpc_format );
 	vsprintf( ac_OutputString, cpc_format, p_Argument );
 	va_end( p_Argument ); 
 
 	glPushMatrix();
 	glPushAttrib( GL_ALL_ATTRIB_BITS );
 	glDisable( GL_DEPTH_TEST );
 	glDisable( GL_LIGHTING );
 	glEnable( GL_TEXTURE_2D );
 	glDisable( GL_ALPHA_TEST );
  
 	glListBase( mu32_Base );
   
 	glEnable( GL_BLEND );
 	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );  
 	glScalef( f_size, f_size, f_size );
 	glCallLists( strlen( ac_OutputString ), GL_UNSIGNED_BYTE, ac_OutputString );
 
 	glPopAttrib();  
 	glPopMatrix();
}

void EE_TEXTURE_FONT_C::Destroy( void )
{
	// Pokud je nìjaký font naèten, smažu display listy znakù a pak i samotnou texturu
	if( mb_FontLoaded == EE_TRUE )
	{
		glDeleteLists( 256, mu32_Base );
		EE_TEXTURE_C::Destroy();
		mb_FontLoaded = EE_FALSE;	
	}
	return;	
}
