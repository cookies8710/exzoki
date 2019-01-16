#include <exzoki/debug/ee_debug_rtds.h>

std::string EE_DEBUG_RTDS_C::S_FontName;
EE_TEXTURE_FONT_MANAGER_C* EE_DEBUG_RTDS_C::pC_FontManager;
std::map< std::string, EE_DEBUG_RTDS_C > EE_DEBUG_RTDS_C::co_RTDS;

void EE_DEBUG_RTDS_C::AddRTDS( EE_CCSTRING_t ccs_name )
{
    if( EE_DEBUG_RTDS_C::co_RTDS.find( std::string( ccs_name ) ) == EE_DEBUG_RTDS_C::co_RTDS.end() )
        EE_DEBUG_RTDS_C::co_RTDS[ std::string( ccs_name ) ] = EE_DEBUG_RTDS_C();    
}
        
EE_DEBUG_RTDS_C& EE_DEBUG_RTDS_C::GetRTDS( EE_CCSTRING_t ccs_name )
{
    std::map< std::string, EE_DEBUG_RTDS_C >::iterator I_RTDS;
    if( ( I_RTDS = EE_DEBUG_RTDS_C::co_RTDS.find( std::string( ccs_name ) ) ) != EE_DEBUG_RTDS_C::co_RTDS.end() )
        return( I_RTDS->second );
    else
        EE_ERROR_C( "EE_DEBUG_RTDS_C", "GetRTDS", EE_ERROR_CODES_n::cS_Internal, "RTDS \"%s\" not found", ccs_name );
}
       
void EE_DEBUG_RTDS_C::DeleteRTDS( EE_CCSTRING_t ccs_name )
{
}
// Nastavení font manažeru
void EE_DEBUG_RTDS_C::SetFontManager( EE_TEXTURE_FONT_MANAGER_C &rC_fontManager )
{
    EE_DEBUG_RTDS_C::pC_FontManager = &rC_fontManager;
}
        
void EE_DEBUG_RTDS_C::SetFont( EE_CCSTRING_t ccs_fontName )
{
    EE_DEBUG_RTDS_C::S_FontName = ccs_fontName;    
}
        
        // Vyèištìní
void EE_DEBUG_RTDS_C::Clear( void )
{
    mco_Infos.clear();
}
        
        // Aktualizace debugovacích dat
void EE_DEBUG_RTDS_C::UpdateInfo( EE_CCSTRING_t ccs_id, EE_CCSTRING_t ccs_data, ... )
{
    va_list p_Argument;
 	EE_CHAR_t ac_OutputString[ 1024 ]; 
 
 	va_start( p_Argument, ccs_data );
 	vsprintf( ac_OutputString, ccs_data, p_Argument );
 	va_end( p_Argument );
     
    mco_Infos[ std::string( ccs_id ) ] = ac_OutputString;     
}
        // Smazání debugovacích dat
void EE_DEBUG_RTDS_C::DeleteInfo( EE_CCSTRING_t ccs_id )
{}
        // Získání debugovacích dat
EE_CCSTRING_t EE_DEBUG_RTDS_C::GetInfo( EE_CCSTRING_t ccs_id ) const
{
    std::map< std::string, std::string >::const_iterator cI_Info;
    if( ( cI_Info = mco_Infos.find( std::string( ccs_id ) ) ) != mco_Infos.end() )
        return( cI_Info->second.c_str() );
    else
        EE_ERROR_C( "EE_DEBUG_RTDS_C", "GetInfo", EE_ERROR_CODES_n::cS_Internal, "Debug info \"%s\" not found", ccs_id );    
}
        
        // Tisk na obrazovku
void EE_DEBUG_RTDS_C::Print( void )
{
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    
    glLoadIdentity();
    glOrtho(0.0,32.0,0.0,24.0,1.0,2.0);
    
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix(); 
    glPushAttrib(GL_ALL_ATTRIB_BITS);   		
   		glColor3ub(255,255,255);              
        glTranslatef(1.0, 23.0, -1.5);
        
        pC_FontManager->SetFont( EE_DEBUG_RTDS_C::S_FontName.c_str() );
              
        std::map< std::string, std::string >::const_iterator cI_Info( mco_Infos.begin() ),
                                                             cI_InfoEnd( mco_Infos.end() );
        for(; cI_Info != cI_InfoEnd; cI_Info++ )
        {       
            pC_FontManager->Print(1.0, cI_Info->second.c_str() );
            glTranslatef( 0.0, -1.0, 0.0 );
        }
                                                         
    glPopAttrib();        
    glPopMatrix(); 
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();    
    glMatrixMode( GL_MODELVIEW );    
}
       
void EE_DEBUG_RTDS_C::Print( std::ostream &rC_outputStream ) const
{
    std::map< std::string, std::string >::const_iterator cI_Info( mco_Infos.begin() ),
                                                         cI_InfoEnd( mco_Infos.end() );
    for(; cI_Info != cI_InfoEnd; cI_Info++ )
        rC_outputStream<< cI_Info->second << std::endl;
}
