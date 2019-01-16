#include <exzoki/gui/ee_gui_editbox.h>

EE_TEXTURE_FONT_MANAGER_C* EE_GUI_EDITBOX_C::pC_FontManager;

EE_GUI_EDITBOX_C::EE_GUI_EDITBOX_C( void ): mb_Callback( 0 ),
                                            mu32_CursorPosition( 0 )
{
}
        
void EE_GUI_EDITBOX_C::SetName( std::string S_name )
{
    mS_Name = S_name; 
    
    mf_NameX = GetPositionX() - EE_EXZOKI_n::cf_TextureFontRelativeWidth * mS_Name.size() * mf_TextSize;  
    mf_NameY = GetPositionY(); 
}

void EE_GUI_EDITBOX_C::SetNameColor( const EE_SYSTEM_COLOR_s &crs_nameColor )
{
    ms_NameColor = crs_nameColor;    
}
        
void EE_GUI_EDITBOX_C::SetText( std::string S_text )
{
    if( S_text.size() <= mu32_MaxTextSize )
        mS_Text = S_text;  
    else
        mS_Text = std::string( S_text.c_str(), S_text.c_str() + mu32_MaxTextSize - 1 );
    
    mu32_CursorPosition = mS_Text.size();  
}

void EE_GUI_EDITBOX_C::SetTextColor( const EE_SYSTEM_COLOR_s &crs_textColor )
{
    ms_TextColor = crs_textColor;    
}
        
        
void EE_GUI_EDITBOX_C::SetTextSize( EE_FLOAT_t f_size )
{
    mf_TextSize = f_size; 
    
    mf_NameX = GetPositionX() - EE_EXZOKI_n::cf_TextureFontRelativeWidth * mS_Name.size() * mf_TextSize;  
    mf_NameY = GetPositionY();   
    
    mu32_MaxTextSize = (int)( GetWidth() / ( mf_TextSize * EE_EXZOKI_n::cf_TextureFontRelativeWidth ) );
}

void EE_GUI_EDITBOX_C::SetTextFont( std::string S_font )
{
    mS_TextFont = S_font;    
}
        
void EE_GUI_EDITBOX_C::SetExteriorColor( const EE_SYSTEM_COLOR_s &crs_exteriorColor )
{
    ms_ExteriorColor = crs_exteriorColor;    
}

void EE_GUI_EDITBOX_C::SetBorderColor( const EE_SYSTEM_COLOR_s &crs_borderColor )
{
    ms_BorderColor = crs_borderColor;    
}

void EE_GUI_EDITBOX_C::SetInteriorColor( const EE_SYSTEM_COLOR_s &crs_interiorColor )
{
    ms_InteriorColor = crs_interiorColor;    
}

void EE_GUI_EDITBOX_C::SetNInterpolationLevels( EE_BYTE_t b_il )
{
    b_NInterpolationLevels = b_il;    
}
                
std::string EE_GUI_EDITBOX_C::GetText( void ) const
{
    return( mS_Text );    
}
        
void EE_GUI_EDITBOX_C::Draw( void )
{
    glPushMatrix();
    glPushAttrib( GL_ALL_ATTRIB_BITS );
          
    // Interpolace mezi "venkovní" barvou a barvou okraje  
    EE_S16_t s16_RInc( ( ms_ExteriorColor.b_R - ms_BorderColor.b_R ) / b_NInterpolationLevels ),
             s16_GInc( ( ms_ExteriorColor.b_G - ms_BorderColor.b_G ) / b_NInterpolationLevels ),
             s16_BInc( ( ms_ExteriorColor.b_B - ms_BorderColor.b_B ) / b_NInterpolationLevels ),
             s16_AInc( ( ms_ExteriorColor.b_A - ms_BorderColor.b_A ) / b_NInterpolationLevels );
            
    for( EE_BYTE_t b_Level( 0 ); b_Level < b_NInterpolationLevels; b_Level++ )
    {
        EE_SYSTEM_COLOR_s s_InterpolatedColor = 
        {  
            ms_BorderColor.b_R + s16_RInc * b_Level,
            ms_BorderColor.b_G + s16_GInc * b_Level,
            ms_BorderColor.b_B + s16_BInc * b_Level,
            ms_BorderColor.b_A + s16_AInc * b_Level
        };
        
        DrawRectangle( GetPositionX() - b_Level * 2.0 - 0.2, 
                       GetPositionX() + GetWidth() + b_Level * 2.0 + 0.2, 
                       GetPositionY() - b_Level * 2.0 - 0.2, 
                       GetPositionY() + GetHeight() + b_Level * 2.0 + 0.2,
                       s_InterpolatedColor, 
                       0 );        
    }
            
    // Okraj
    DrawRectangle( GetPositionX(), 
                   GetPositionX() + GetWidth(), 
                   GetPositionY(), 
                   GetPositionY() + GetHeight(),
                   ms_BorderColor, 
                   0 );  
    
    // Výplò vnitøku                           
    DrawRectangle( GetPositionX(), 
                   GetPositionX() + GetWidth(), 
                   GetPositionY(), 
                   GetPositionY() + GetHeight(),
                   ms_InteriorColor, 
                   1 );
             
    // Text                  
    glColor4ub(ms_TextColor.b_R,ms_TextColor.b_G,ms_TextColor.b_B,ms_TextColor.b_A);
    glPushMatrix();
    glTranslatef( GetPositionX() + mf_TextSize * 0.1, GetPositionY() + mf_TextSize * 0.1, 0.0 );
    pC_FontManager->SetFont( mS_TextFont.c_str() );
    pC_FontManager->Print( mf_TextSize, mS_Text.c_str() );
    glPopMatrix();
    
    // Kurzor vykresluji jen pokud jsem v callback režimu (odchytávám vstup z klávesnice)
    if( mb_Callback )
    {
        glPushMatrix();
        glPushAttrib( GL_ALL_ATTRIB_BITS );
        glTranslatef( GetPositionX() + mf_TextSize * 0.3 + 
                            mu32_CursorPosition * mf_TextSize * EE_EXZOKI_n::cf_TextureFontRelativeWidth, 
                      GetPositionY() + mf_TextSize * 0.1, 
                      0.0 );
        glDisable( GL_TEXTURE_2D );
        glBegin( GL_LINES );
            glVertex2f( 0.0, 0.0 );
            glVertex2f( 0.0, 0.9 * mf_TextSize );
        glEnd();
        
        glPopAttrib();
        glPopMatrix();
    }
    // Jméno
    glColor4ub(ms_NameColor.b_R,ms_NameColor.b_G,ms_NameColor.b_B,ms_NameColor.b_A);
    glTranslatef( mf_NameX, mf_NameY, 0.0 );
    pC_FontManager->SetFont( mS_TextFont.c_str() );
    pC_FontManager->Print( mf_TextSize, mS_Name.c_str() );
                
    glPopAttrib();
    glPopMatrix();
        
    return;        
}

EE_U32_t EE_GUI_EDITBOX_C::GuiProc( const EE_GUI_MOUSE_s &crs_mouse, 
                                           EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard )
{
    EE_GUI_RECTANGLE_s s_EditBoxRect( GetActiveRect() );
    
    if( mb_Callback )
    {
        if( !crs_mouse.b_LB && !crs_mouse.b_LBBefore )
        {
            EE_U16_t u16_LastKeyPressed;
            if( u16_LastKeyPressed = pC_keyboard->GetLastKeyPressed() )
            {
                pC_keyboard->ClearLastKeyPressed(); 
                if( u16_LastKeyPressed == EE_EXZOKI_n::cu16_LeftArrow )
                    if( mu32_CursorPosition >= 1 )
                        mu32_CursorPosition--;   
                
                if( u16_LastKeyPressed == EE_EXZOKI_n::cu16_RightArrow )
                    if( mu32_CursorPosition < mS_Text.size() )
                        mu32_CursorPosition++; 
                        
                if( u16_LastKeyPressed == EE_EXZOKI_n::cu16_DeleteKey )
                    if( mu32_CursorPosition < mS_Text.size() )
                    {
                        mS_Text = std::string( mS_Text.c_str(), mS_Text.c_str() + mu32_CursorPosition ) +
                                  std::string( mS_Text.c_str() + mu32_CursorPosition + 1, mS_Text.c_str() + mS_Text.size() );
                        
                            
                    }
            }
            
            EE_CHAR_t c_LastKeyPressed;
            if( c_LastKeyPressed = pC_keyboard->GetLastCharacterPressed() )    
            {
                pC_keyboard->ClearLastCharacterPressed();
                
                if( c_LastKeyPressed == EE_EXZOKI_n::cc_KeyEnter || 
                    c_LastKeyPressed == EE_EXZOKI_n::cc_KeyEscape )
                    mb_Callback = 0;
                if( c_LastKeyPressed == EE_EXZOKI_n::cc_KeyBackspace && mu32_CursorPosition > 0 )
                    if( mS_Text.size() )
                    {
                        //mS_Text = std::string( mS_Text.c_str(), mS_Text.c_str() + mS_Text.size() - 1 );
                        mS_Text = std::string( mS_Text.c_str(), mS_Text.c_str() + mu32_CursorPosition - 1 ) +
                                  std::string( mS_Text.c_str() + mu32_CursorPosition, mS_Text.c_str() + mS_Text.size() );
                        mu32_CursorPosition--;
                    }
                                    
                if( ( c_LastKeyPressed >= 32 ) && ( mu32_MaxTextSize > mS_Text.size() + 1 ) )
                {
                    //mS_Text += c_LastKeyPressed;  
                    mS_Text = std::string( mS_Text.c_str(), mS_Text.c_str() + mu32_CursorPosition ) + c_LastKeyPressed +
                              std::string( mS_Text.c_str() + mu32_CursorPosition, mS_Text.c_str() + mS_Text.size() );
                        
                    mu32_CursorPosition++;
                }     
            }            
        }
        else if( !PointInRect( crs_mouse.f_X, crs_mouse.f_Y, s_EditBoxRect ) && !crs_mouse.b_LBBefore )
        {
            mb_Callback = 0;
            return( EE_GUI_SIGNAL_NOTHING );  
        } 
           
        return( EE_GUI_SIGNAL_CALLBACK );             
    }
    else
    {
        if( PointInRect( crs_mouse.f_X, crs_mouse.f_Y, s_EditBoxRect ) && crs_mouse.b_LB && !crs_mouse.b_LBBefore )
        {
            mb_Callback = 1;
            pC_keyboard->ClearLastCharacterPressed(); 
            return( EE_GUI_SIGNAL_CALLBACK );
        }
        else
            return( EE_GUI_SIGNAL_NOTHING );
    }    
}
                                                   
EE_GUI_ELEMENT_TYPE_e EE_GUI_EDITBOX_C::GetElementType( void ) const
{
    return( EE_GUI_ELEMENT_TYPE_EDITBOX );    
}
        
void EE_GUI_EDITBOX_C::SetFontManager( EE_TEXTURE_FONT_MANAGER_C& rC_fontManager )
{
    EE_GUI_EDITBOX_C::pC_FontManager = &rC_fontManager;    
}

