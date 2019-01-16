#include <exzoki/gui/ee_gui_button.h>

EE_TEXTURE_FONT_MANAGER_C* EE_GUI_BUTTON_C::pC_FontManager;
void EE_GUI_BUTTON_C::SetFontManager( EE_TEXTURE_FONT_MANAGER_C& rC_fontManager )
{
    EE_GUI_BUTTON_C::pC_FontManager = &rC_fontManager;  
}

EE_GUI_BUTTON_C::EE_GUI_BUTTON_C( void )
{
}
        
void EE_GUI_BUTTON_C::SetText( std::string S_text,
                               std::string S_font,
                               const EE_SYSTEM_COLOR_s &crs_color,
                               EE_FLOAT_t f_size,
                               EE_FLOAT_t f_space )
{
    mS_Text = S_text;
    mS_TextFont = S_font;
    ms_TextColor = crs_color;
    mf_TextSize = f_size;
    mf_TextSpacing = f_space;
            
    // Výpoèet rozmìrù dle velikosti písma, poètu znakù a požadované vzdálenosti od okrajù
    CalculateDimensions();
}  

void EE_GUI_BUTTON_C::UpdateText( std::string S_text )
{
    mS_Text = S_text;
    
    CalculateDimensions();
}                            
                            
void EE_GUI_BUTTON_C::SetExteriorColor( const EE_SYSTEM_COLOR_s &crs_exteriorColor )
{
    ms_ExteriorColor = crs_exteriorColor;
}

void EE_GUI_BUTTON_C::SetBorderColor( const EE_SYSTEM_COLOR_s &crs_borderColor )
{
    ms_BorderColor = crs_borderColor;
}

void EE_GUI_BUTTON_C::SetInteriorColor( const EE_SYSTEM_COLOR_s &crs_interiorColor )
{
    ms_InteriorColor = crs_interiorColor;
}

void EE_GUI_BUTTON_C::SetNInterpolationLevels( EE_BYTE_t b_il )
{
    mb_NInterpolationLevels = b_il;    
}

void EE_GUI_BUTTON_C::Draw( void )
{
    glPushMatrix();
    glPushAttrib( GL_ALL_ATTRIB_BITS );
          
    // Interpolace mezi "venkovní" barvou a barvou okraje  
    EE_S16_t s16_RInc( ( ms_ExteriorColor.b_R - ms_BorderColor.b_R ) / mb_NInterpolationLevels ),
             s16_GInc( ( ms_ExteriorColor.b_G - ms_BorderColor.b_G ) / mb_NInterpolationLevels ),
             s16_BInc( ( ms_ExteriorColor.b_B - ms_BorderColor.b_B ) / mb_NInterpolationLevels ),
             s16_AInc( ( ms_ExteriorColor.b_A - ms_BorderColor.b_A ) / mb_NInterpolationLevels );
            
    for( EE_BYTE_t b_Level( 0 ); b_Level < mb_NInterpolationLevels; b_Level++ )
    {
        EE_SYSTEM_COLOR_s s_InterpolatedColor = 
        {  
            ms_BorderColor.b_R + s16_RInc * b_Level,
            ms_BorderColor.b_G + s16_GInc * b_Level,
            ms_BorderColor.b_B + s16_BInc * b_Level,
            ms_BorderColor.b_A + s16_AInc * b_Level
        };
        
        DrawRectangle( GetPositionX() - b_Level * 2.0 - 0.2, 
                       GetPositionX() + GetWidth() + b_Level * 2.0 + 0.2 + mf_TextSpacing, 
                       GetPositionY() - b_Level * 2.0 - 0.2, 
                       GetPositionY() + GetHeight() + b_Level * 2.0 + 0.2,
                       s_InterpolatedColor, 
                       0 );        
    }
            
    // Okraj
    DrawRectangle( GetPositionX(), 
                   GetPositionX() + GetWidth() + mf_TextSpacing, 
                   GetPositionY(), 
                   GetPositionY() + GetHeight(),
                   ms_BorderColor, 
                   0 );  
    
    // Výplò vnitøku                           
    DrawRectangle( GetPositionX(), 
                   GetPositionX() + GetWidth() + mf_TextSpacing, 
                   GetPositionY(), 
                   GetPositionY() + GetHeight(),
                   ms_InteriorColor, 
                   1 );
             
    // Text                  
    glColor4ub(ms_TextColor.b_R,ms_TextColor.b_G,ms_TextColor.b_B,ms_TextColor.b_A);
    glTranslatef( GetPositionX() + mf_TextSpacing, GetPositionY() + mf_TextSpacing, 0.0 );
    pC_FontManager->SetFont( mS_TextFont.c_str() );
    pC_FontManager->Print( mf_TextSize, mS_Text.c_str() );
                       
    glPopAttrib();
    glPopMatrix();
        
    return;        
}
        
EE_U32_t EE_GUI_BUTTON_C::GuiProc( const EE_GUI_MOUSE_s &crs_mouse, 
                                   EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard )
{
    EE_GUI_RECTANGLE_s s_ButtonRect( GetActiveRect() );
    
    if( PointInRect( crs_mouse.f_X, crs_mouse.f_Y, s_ButtonRect ) && crs_mouse.b_LB && !crs_mouse.b_LBBefore )
        return( EE_GUI_SIGNAL_ACTIVATED );
    
    return( EE_GUI_SIGNAL_NOTHING );
}     
     
     
EE_GUI_ELEMENT_TYPE_e EE_GUI_BUTTON_C::GetElementType( void ) const  
{
    return( EE_GUI_ELEMENT_TYPE_BUTTON );    
}                            

void EE_GUI_BUTTON_C::CalculateDimensions( void )
{
    SetWidth( 2 * mf_TextSpacing + EE_EXZOKI_n::cf_TextureFontRelativeWidth * mS_Text.size() * mf_TextSize );
    SetHeight( 2 * mf_TextSpacing + mf_TextSize );    
}
