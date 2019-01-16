#include <exzoki/gui/ee_gui_window.h>

EE_TEXTURE_FONT_MANAGER_C* EE_GUI_WINDOW_C::pC_FontManager;
void EE_GUI_WINDOW_C::SetFontManager( EE_TEXTURE_FONT_MANAGER_C& rC_fontManager )
{
    EE_GUI_WINDOW_C::pC_FontManager = &rC_fontManager;  
}

EE_GUI_WINDOW_C::EE_GUI_WINDOW_C( void ): mb_Minimalized( 0 ),
                                          mu32_LongestLength( 0 )
{
}

void EE_GUI_WINDOW_C::Draw( void )
{  
    if( mb_Minimalized )
    {
        // Pøedchod exterior/border
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
                           GetPositionX() + GetWidth() + b_Level * 2.0 + 0.2, 
                           GetPositionY() + GetHeight() - mf_UnitSize - b_Level * 2.0 - 0.2, 
                           GetPositionY() + GetHeight() + b_Level * 2.0 + 0.2,
                           s_InterpolatedColor, 
                           0 );        
        }
        
        // Okraj okna
        DrawRectangle( GetPositionX(),
                       GetPositionX() + GetWidth(),
                       GetPositionY() + GetHeight() - mf_UnitSize,
                       GetPositionY() + GetHeight(),
                       ms_BorderColor,
                       0 ); 
                   
        // Interier    
        DrawRectangle( GetPositionX(),
                       GetPositionX() + GetWidth(),
                       GetPositionY() + GetHeight() - mf_UnitSize,
                       GetPositionY() + GetHeight(),
                       ms_InteriorColor,
                       1 );     
        //
    
        // Title text
        glPushMatrix();
        glTranslatef( GetPositionX(), GetPositionY() + GetHeight() - mf_UnitSize, 0.0 );
        glColor4ub( ms_TitleTextColor.b_R, ms_TitleTextColor.b_G, ms_TitleTextColor.b_B, ms_TitleTextColor.b_A );
        pC_FontManager->SetFont( mS_TitleTextFont.c_str() );
        pC_FontManager->Print( mf_UnitSize, mS_VisibleTitleText.c_str() ); 
        glPopMatrix();
    
        // Tlaèítko _
        DrawRectangle( GetPositionX() + GetWidth() - 2.0 * mf_UnitSize,
                       GetPositionX() + GetWidth() - 1.0 * mf_UnitSize,
                       GetPositionY() + GetHeight() - 1.0 * mf_UnitSize,
                       GetPositionY() + GetHeight(),
                       ms_BorderColor,
                       0 ); 
        // Tlaèítko X
        DrawRectangle( GetPositionX() + GetWidth() - 1.0 * mf_UnitSize,
                       GetPositionX() + GetWidth(),
                       GetPositionY() + GetHeight() - 1.0 * mf_UnitSize,
                       GetPositionY() + GetHeight(),
                       ms_BorderColor,
                       0 );      
                   
        
    }
    else
    {
      
        // Pøedchod exterior/border        
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
                           GetPositionX() + GetWidth() + b_Level * 2.0 + 0.2, 
                           GetPositionY() - b_Level * 2.0 - 0.2, 
                           GetPositionY() + GetHeight() + b_Level * 2.0 + 0.2,
                           s_InterpolatedColor, 
                           0 );        
        }
        
        // Okraj okna
        DrawRectangle( GetPositionX(),
                       GetPositionX() + GetWidth(),
                       GetPositionY(),
                       GetPositionY() + GetHeight(),
                       ms_BorderColor,
                       0 ); 
    
    // Inner window
    glClear( GL_STENCIL_BUFFER_BIT );
    glEnable( GL_STENCIL_TEST );
    
    glStencilFunc( GL_ALWAYS, 1, 1 );
    glStencilOp( GL_REPLACE, GL_REPLACE, GL_REPLACE );
    
    DrawRectangle( mf_InnerX,
                   mf_InnerX + mf_InnerWidth,
                   mf_InnerY,
                   mf_InnerY + mf_InnerHeight,
                   ms_InnerColor,
                   1 ); 
    // Inner text
    glStencilFunc( GL_EQUAL, 1, 1 );
    glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
    
    glPushMatrix();
    glTranslatef( mf_InnerX, 
                  mf_InnerY + mf_InnerHeight - mf_UnitSize, 0.0 );
    
    if( mb_HorizontalScrollbar )
    {
        glTranslatef( - mC_HorizontalScrollbar.GetRelativeSliderPosition() * 
                         mf_InnerWidth / mC_HorizontalScrollbar.GetRelativeSliderLength(), 0.0, 0.0 );
        
    }
    if( mb_VerticalScrollbar )
    {
        glTranslatef( 0.0, 
                      - mC_VerticalScrollbar.GetRelativeSliderPosition() * 
                      mf_InnerHeight / mC_VerticalScrollbar.GetRelativeSliderLength(), 0.0 );
        
    }
    glColor4ub( ms_InnerTextColor.b_R, ms_InnerTextColor.b_G, ms_InnerTextColor.b_B, ms_InnerTextColor.b_A );
    pC_FontManager->SetFont( mS_InnerTextFont.c_str() );
    
    for( EE_U32_t u32_Row( 0 ); u32_Row < mu32_InnerTextNRows; u32_Row++ )
    {
        pC_FontManager->Print( mf_UnitSize, mco_InnerText[ u32_Row ].c_str() ); 
        glTranslatef( 0.0, -mf_UnitSize, 0.0 );
    }
        
    glPopMatrix();
    
    // Interier
    glStencilFunc( GL_GREATER, 1, 1 );
    glStencilOp( GL_REPLACE, GL_REPLACE, GL_REPLACE );
    
    DrawRectangle( GetPositionX(),
                   GetPositionX() + GetWidth(),
                   GetPositionY(),
                   GetPositionY() + GetHeight(),
                   ms_InteriorColor,
                   1 );     
    
    glDisable( GL_STENCIL_TEST );
    glClear( GL_STENCIL_BUFFER_BIT );
    //
    
    // Title text
    glPushMatrix();
    glTranslatef( GetPositionX(), GetPositionY() + GetHeight() - mf_UnitSize, 0.0 );
    glColor4ub( ms_TitleTextColor.b_R, ms_TitleTextColor.b_G, ms_TitleTextColor.b_B, ms_TitleTextColor.b_A );
    pC_FontManager->SetFont( mS_TitleTextFont.c_str() );
    pC_FontManager->Print( mf_UnitSize, mS_VisibleTitleText.c_str() ); 
    glPopMatrix();
    
    
    // Scrollbary
    if( mb_HorizontalScrollbar )
        mC_HorizontalScrollbar.Draw();
    if( mb_VerticalScrollbar )
        mC_VerticalScrollbar.Draw();
    
    // Tlaèítko _
    DrawRectangle( GetPositionX() + GetWidth() - 2.0 * mf_UnitSize,
                   GetPositionX() + GetWidth() - 1.0 * mf_UnitSize,
                   GetPositionY() + GetHeight() - 1.0 * mf_UnitSize,
                   GetPositionY() + GetHeight(),
                   ms_BorderColor,
                   0 ); 
    // Tlaèítko X
    DrawRectangle( GetPositionX() + GetWidth() - 1.0 * mf_UnitSize,
                   GetPositionX() + GetWidth(),
                   GetPositionY() + GetHeight() - 1.0 * mf_UnitSize,
                   GetPositionY() + GetHeight(),
                   ms_BorderColor,
                   0 );   
    // Tlaèítko zmìny velikosti okna
    DrawRectangle( GetPositionX() + GetWidth() - 1.0 * mf_UnitSize,
                   GetPositionX() + GetWidth(),
                   GetPositionY(), 
                   GetPositionY() + 1.0 * mf_UnitSize,
                   ms_BorderColor,
                   0 );       
                   
    // Text v innerwindow
    
    }
}

EE_U32_t EE_GUI_WINDOW_C::GuiProc( const EE_GUI_MOUSE_s &crs_mouse, 
                                   EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard )
{
    EE_GUI_RECTANGLE_s s_TitleBarRectangle;
    s_TitleBarRectangle.f_Left = GetPositionX();
    s_TitleBarRectangle.f_Right = GetPositionX() + GetWidth() - 2.0 * mf_UnitSize;
    s_TitleBarRectangle.f_Bottom = GetPositionY() + GetHeight() - mf_UnitSize;
    s_TitleBarRectangle.f_Top = GetPositionY() + GetHeight();
    
    EE_GUI_RECTANGLE_s s_ResizeButtonRectangle = { GetPositionX() + GetWidth() - mf_UnitSize, 
                                                   GetPositionX() + GetWidth(),
                                                   GetPositionY(),
                                                   GetPositionY() + mf_UnitSize };
    
    EE_GUI_RECTANGLE_s s_MinimalizeButtonRectangle = { GetPositionX() + GetWidth() - 2.0 * mf_UnitSize, 
                                                       GetPositionX() + GetWidth() - 1.0 * mf_UnitSize,
                                                       GetPositionY() + GetHeight() - mf_UnitSize,
                                                       GetPositionY() + GetHeight() };
    EE_GUI_RECTANGLE_s s_WindowRectangle = { GetPositionX(), 
                                             GetPositionX() + GetWidth(),
                                             GetPositionY(),
                                             GetPositionY() + GetHeight() };
    
    if( mb_MoveCallback )
    {
        if( !crs_mouse.b_LB )  
        {
            mb_MoveCallback = 0;
            return( EE_GUI_SIGNAL_NOTHING );
        }
        else
        {
            EE_FLOAT_t f_DeltaX( crs_mouse.f_X - crs_mouse.f_XBefore ), 
                       f_DeltaY( crs_mouse.f_Y - crs_mouse.f_YBefore );
            
            MoveX( f_DeltaX );
            MoveY( f_DeltaY );
            
            // Pøepoèítám pozici scrollbarù a inner window
            mf_InnerX = GetPositionX() + mf_UnitSize;
            mf_InnerY = GetPositionY() + mf_UnitSize;
            
            if( mb_VerticalScrollbar )
            {
                mC_VerticalScrollbar.MoveX( f_DeltaX );   
                mC_VerticalScrollbar.MoveY( f_DeltaY );     
            }
            
            if( mb_HorizontalScrollbar )
            {
                mC_HorizontalScrollbar.MoveX( f_DeltaX );   
                mC_HorizontalScrollbar.MoveY( f_DeltaY );     
            }
            
            return( EE_GUI_SIGNAL_CALLBACK );
        }  
        
    }
    
    if( mb_ResizeCallback )
    {
        if( !crs_mouse.b_LB )  
        {
            mb_ResizeCallback = 0;
            return( EE_GUI_SIGNAL_NOTHING );
        }
        else
        {
            EE_FLOAT_t f_DeltaX( crs_mouse.f_X - crs_mouse.f_XBefore ), 
                       f_DeltaY( crs_mouse.f_Y - crs_mouse.f_YBefore );
            
            ResizeProc( f_DeltaX, f_DeltaY ); 
            
            return( EE_GUI_SIGNAL_CALLBACK );
        }  
        
    }
    
    
    if( PointInRect( crs_mouse.f_X, crs_mouse.f_Y, s_TitleBarRectangle ) && 
        crs_mouse.b_LB &&
        !crs_mouse.b_LBBefore )
    {
        mb_MoveCallback = 1;
        return( EE_GUI_SIGNAL_CALLBACK );
    }
    
    if( !mb_Minimalized )
    {   
        if( PointInRect( crs_mouse.f_X, crs_mouse.f_Y, s_ResizeButtonRectangle ) && 
            crs_mouse.b_LB &&
            !crs_mouse.b_LBBefore )
        {
            mb_ResizeCallback = 1;
            return( EE_GUI_SIGNAL_CALLBACK );
        }
    }
    
    EE_GUI_RECTANGLE_s s_CloseButtonRectangle;
    s_CloseButtonRectangle.f_Left = GetPositionX() + GetWidth() - mf_UnitSize;
    s_CloseButtonRectangle.f_Right = GetPositionX() + GetWidth();
    s_CloseButtonRectangle.f_Bottom = GetPositionY() + GetHeight() - mf_UnitSize;
    s_CloseButtonRectangle.f_Top = GetPositionY() + GetHeight();
        
    if( PointInRect( crs_mouse.f_X, crs_mouse.f_Y, s_MinimalizeButtonRectangle ) && 
        crs_mouse.b_LB &&
        !crs_mouse.b_LBBefore )
    {
        mb_Minimalized = !mb_Minimalized;
        return( EE_GUI_SIGNAL_NOTHING );
    }              
                      
                                                  
    if( PointInRect( crs_mouse.f_X, crs_mouse.f_Y, s_CloseButtonRectangle ) && 
        crs_mouse.b_LB &&
        !crs_mouse.b_LBBefore )
        return( EE_GUI_SIGNAL_DELETE );
    
    if( !mb_Minimalized )
    {
    
        if( mb_HorizontalScrollbar )
        {
            EE_U32_t u32_Signal( mC_HorizontalScrollbar.GuiProc( crs_mouse,pC_keyboard ) ); 
            if( u32_Signal != EE_GUI_SIGNAL_NOTHING )
                return( u32_Signal );    
        }
    
        if( mb_VerticalScrollbar )
        {
            EE_U32_t u32_Signal( mC_VerticalScrollbar.GuiProc( crs_mouse,pC_keyboard ) ); 
            if( u32_Signal != EE_GUI_SIGNAL_NOTHING )
                return( u32_Signal ); 
        }
    }
    
    if( PointInRect( crs_mouse.f_X, crs_mouse.f_Y, s_WindowRectangle ) && 
        crs_mouse.b_LB &&
        !crs_mouse.b_LBBefore )
        return( EE_GUI_SIGNAL_ACTIVATED );
    else
        return( EE_GUI_SIGNAL_NOTHING );
}

EE_GUI_ELEMENT_TYPE_e EE_GUI_WINDOW_C::GetElementType( void ) const
{
    return( EE_GUI_ELEMENT_TYPE_WINDOW );
}

void EE_GUI_WINDOW_C::SetColors( const EE_SYSTEM_COLOR_s &crs_border,
                                 const EE_SYSTEM_COLOR_s &crs_interior,
                                 const EE_SYSTEM_COLOR_s &crs_exterior,
                                 const EE_SYSTEM_COLOR_s &crs_titleText,
                                 const EE_SYSTEM_COLOR_s &crs_innerText,
                                 const EE_SYSTEM_COLOR_s &crs_innerWindow )
{
    ms_BorderColor = crs_border;
    ms_InteriorColor = crs_interior;
    ms_ExteriorColor = crs_exterior;
    ms_TitleTextColor = crs_titleText;
    ms_InnerTextColor = crs_innerText;
    ms_InnerColor = crs_innerWindow;
}
                
void EE_GUI_WINDOW_C::Set( EE_FLOAT_t f_unitSize,
                           EE_BYTE_t b_nInterpolationLvls,
                           std::string S_titleText,
                           std::string S_titleTextFont,
                           std::string S_innerTextFont )
{
    // Nastavím velikost jednotky
    mf_UnitSize = f_unitSize;
    
    // Spoèítám pozici a velikost vnitøního okna
    RecalcInnerWindow();
    
    // Nastavím poèet interpolaèních stupòù
    mb_NInterpolationLevels = b_nInterpolationLvls;
    
    // Nastavím title text
    mS_TitleText = S_titleText;
    
    RecalcTitleBarText();
        
    // Nastavím fonty title textu a vnitøního okna
    mS_TitleTextFont = S_titleTextFont;
    mS_InnerTextFont = S_innerTextFont;    
}

void EE_GUI_WINDOW_C::SetInnerText( std::string S_innerText )
{
    // Smažu pøedchozí text
    mco_InnerText.clear();
    
    // Text rozsekám na øádky
    EE_U32_t u32_RowBegining( 0 );  
    EE_U32_t u32_TextSize( S_innerText.size() ); 
        
    for( EE_U32_t u32_Char( 0 ); u32_Char < u32_TextSize; u32_Char++ )
    {
        if( S_innerText[ u32_Char ] == '\n' )
        {
            mco_InnerText.push_back( 
                std::string( S_innerText.c_str() + u32_RowBegining, 
                             S_innerText.c_str() + u32_Char ) );
            if( u32_Char - u32_RowBegining > mu32_LongestLength )
                mu32_LongestLength = u32_Char - u32_RowBegining;        
                      
            u32_RowBegining = u32_Char + 1;
        }
    }
    
    mco_InnerText.push_back( std::string( S_innerText.c_str() + u32_RowBegining, 
                             S_innerText.c_str() + u32_TextSize ) ); 
    
    if( u32_TextSize - u32_RowBegining > mu32_LongestLength )
        mu32_LongestLength = u32_TextSize - u32_RowBegining;       
    
    mu32_InnerTextNRows = mco_InnerText.size();
    
    RecalcScrollbars();
    /*// Pokud je nejdelší øádek pøíliš dlouhý na zobrazení, aktivuju horizontální scroll bar a nastavím jej
    if( mu32_LongestLength > mu32_MaxInnerTextLength )
    {
        mb_HorizontalScrollbar = 1;
        
        // Pozice
        mC_HorizontalScrollbar.SetPositionX( GetPositionX() + mf_UnitSize );
        mC_HorizontalScrollbar.SetPositionY( GetPositionY() );
        // Velikost a typ
        mC_HorizontalScrollbar.Set( EE_GUI_SCROLLBAR_HORIZONTAL,
                                    mf_InnerWidth, mf_UnitSize,
                                    ms_BorderColor, ms_InteriorColor,
                                    0.7 );
        // Nastavení slideru
        mC_HorizontalScrollbar.UpdateSlider( (EE_FLOAT_t)mu32_MaxInnerTextLength, (EE_FLOAT_t)mu32_LongestLength );
    }
    else
        mb_HorizontalScrollbar = 0;
    
    // Pokud je pøíliš mnoho øádkù, nastavím vertikální scrollbar
    mu32_InnerTextNRows = mco_InnerText.size();
    if( mu32_InnerTextNRows > mu32_MaxInnerTextRows )
    {
        mb_VerticalScrollbar = 1;
        // Pozice
        mC_VerticalScrollbar.SetPositionX( GetPositionX() + GetWidth() - mf_UnitSize );
        mC_VerticalScrollbar.SetPositionY( GetPositionY() + mf_UnitSize );
        // Velikost a typ
        mC_VerticalScrollbar.Set( EE_GUI_SCROLLBAR_VERTICAL,
                                  mf_InnerHeight, mf_UnitSize,
                                  ms_BorderColor, ms_InteriorColor,
                                  0.7 );
        // Nastavení slideru
        mC_VerticalScrollbar.UpdateSlider( (EE_FLOAT_t)mu32_MaxInnerTextRows, (EE_FLOAT_t)mu32_InnerTextNRows );
    }
    else
        mb_VerticalScrollbar = 0;*/
    
}

void EE_GUI_WINDOW_C::ResizeProc( EE_FLOAT_t f_deltaX, EE_FLOAT_t f_deltaY )
{
    // Spoèítám novou pozici a velikost okna
    RecalcWindow( f_deltaX, f_deltaY );
    
    // Spoèítám novou pozici a velikost vnitøního okna    
    RecalcInnerWindow();
    
    // Aktualizuju title bar text
    RecalcTitleBarText();
    
    // Spoèítám novou velikost a pozici scrollbarù a jejich slidery
    RecalcScrollbars();    
}

void EE_GUI_WINDOW_C::RecalcWindow( EE_FLOAT_t f_deltaX, EE_FLOAT_t f_deltaY )
{
    // Zmìna velikost na ose X
    // Pokud je nová šíøka vìtší než je minimální, mùžu ji nastavit, jinak nastavím mnimální šíøku
    if( GetWidth() + f_deltaX >= 3.0 * mf_UnitSize + 3.0 * ( mf_UnitSize * EE_EXZOKI_n::cf_TextureFontRelativeWidth ) )
        SetWidth( GetWidth() + f_deltaX );
    else
        SetWidth( 3.0 * mf_UnitSize + 3.0 * ( mf_UnitSize * EE_EXZOKI_n::cf_TextureFontRelativeWidth ) );
    
    
    // Zmìna velikosti na ose Y     
    // Pokud je nová výška vìtší než je minimální, mùžu ji nastavit, jinak nastavím mnimální výšku  
    if( GetHeight() - f_deltaY >= 3.0 * mf_UnitSize )
    {
        SetHeight( GetHeight() - f_deltaY );        
        MoveY( f_deltaY );
    }
    else
    {                
        MoveY( GetHeight() - 3.0 * mf_UnitSize );
        SetHeight( 3.0 * mf_UnitSize );                    
    }    
}

void EE_GUI_WINDOW_C::RecalcTitleBarText( void )
{
    // Spoèítám maximální velikost title textu
    mu32_MaxTitleSize = EE_U32_t( ( GetWidth() - 2.0 * mf_UnitSize ) / 
                        ( mf_UnitSize * EE_EXZOKI_n::cf_TextureFontRelativeWidth ) );
    // Pokud je title text vìtší než je max. pøípustná velikost, oøežu jej
    if( mS_TitleText.size() > mu32_MaxTitleSize )
    {
        if( mu32_MaxTitleSize >= 3 )
        {
            mS_VisibleTitleText = std::string( mS_TitleText.c_str(), 
                                               mS_TitleText.c_str() + mu32_MaxTitleSize - 3 );
            mS_VisibleTitleText += "...";
        }
        else
            mS_VisibleTitleText = std::string( '.', mu32_MaxTitleSize );
        
    }
    else
        mS_VisibleTitleText = mS_TitleText;    
}

void EE_GUI_WINDOW_C::RecalcInnerWindow( void )
{
    // Pozice
    mf_InnerX = GetPositionX() + mf_UnitSize;
    mf_InnerY = GetPositionY() + mf_UnitSize;
        
    // Velikost
    mf_InnerWidth = GetWidth() - 2.0 * mf_UnitSize;
    mf_InnerHeight = GetHeight() - 2.0 * mf_UnitSize;
    
    // Spoèítám maximální délku øádku a maximální poèet øádkù, pøi kterých se ještì nebudou zobrazovat scrollbary
    mu32_MaxInnerTextLength = EE_U32_t( mf_InnerWidth / ( mf_UnitSize * EE_EXZOKI_n::cf_TextureFontRelativeWidth ) );
    mu32_MaxInnerTextRows = EE_U32_t( mf_InnerHeight / mf_UnitSize );
}

void EE_GUI_WINDOW_C::RecalcScrollbars( void )
{
    // Horizontální scrollbar    
    if( mu32_LongestLength <= mu32_MaxInnerTextLength )
    {
        mb_HorizontalScrollbar = 0;    
    }
    else 
    {   
       /* EE_BOOL_t b_HorizontalScrollbarOld = mb_HorizontalScrollbar;
        EE_FLOAT_t f_RelativeSliderPositionOld;
        if( b_HorizontalScrollbarOld )
            f_RelativeSliderPositionOld = mC_HorizontalScrollbar.GetRelativeSliderPosition();   
        */
        mb_HorizontalScrollbar = 1;
                 
        // Pozice
        mC_HorizontalScrollbar.SetPositionX( GetPositionX() + mf_UnitSize );
        mC_HorizontalScrollbar.SetPositionY( GetPositionY() );
        // Velikost a typ
        mC_HorizontalScrollbar.Set( EE_GUI_SCROLLBAR_HORIZONTAL,
                                    mf_InnerWidth, mf_UnitSize,
                                    ms_BorderColor, ms_InteriorColor,
                                    0.7 );
        mC_HorizontalScrollbar.UpdateSlider( (EE_FLOAT_t)mu32_MaxInnerTextLength, 
                                             (EE_FLOAT_t)mu32_LongestLength ); 
        
       /* if( b_HorizontalScrollbarOld )
            mC_HorizontalScrollbar.SetRelativeSliderPosition( f_RelativeSliderPositionOld );   */      
    } 
    
    // Vertikální scrollbar
    if( mco_InnerText.size() <= mu32_MaxInnerTextRows )
    {
        mb_VerticalScrollbar = 0;                    
    }
    else 
    {       
        /*EE_BOOL_t b_VerticalScrollbarOld = mb_VerticalScrollbar;
        EE_FLOAT_t f_RelativeSliderPositionOld;
        if( b_VerticalScrollbarOld )
            f_RelativeSliderPositionOld = mC_VerticalScrollbar.GetRelativeSliderPosition();        
         */
        mb_VerticalScrollbar = 1;
            
        // Pozice
        mC_VerticalScrollbar.SetPositionX( GetPositionX() + GetWidth() - mf_UnitSize );
        mC_VerticalScrollbar.SetPositionY( GetPositionY() + mf_UnitSize );
        // Velikost a typ
        mC_VerticalScrollbar.Set( EE_GUI_SCROLLBAR_VERTICAL,
                                  mf_InnerHeight, mf_UnitSize,
                                  ms_BorderColor, ms_InteriorColor,
                                  0.7 );   
        mC_VerticalScrollbar.UpdateSlider( (EE_FLOAT_t)mu32_MaxInnerTextRows, 
                                           (EE_FLOAT_t)mco_InnerText.size() );  
        
        /*if( b_VerticalScrollbarOld )
            mC_VerticalScrollbar.SetRelativeSliderPosition( f_RelativeSliderPositionOld );  */
    }      
}
