#include <exzoki/gui/ee_gui_scrollbar.h>

void EE_GUI_SCROLLBAR_C::Set( EE_GUI_SCROLLBAR_TYPE_e e_type,
                              EE_FLOAT_t f_length, EE_FLOAT_t f_size,
                              const EE_SYSTEM_COLOR_s &crs_borderColor, const EE_SYSTEM_COLOR_s &crs_interiorColor,
                              EE_FLOAT_t f_k )
{
    // Nastavím požadovaný typ, délku a velikost (výšku/šíøku)
    me_ScrollbarType = e_type;
    mf_Length = f_length;
    mf_Size = f_size;
            
    // Nastavím skuteènou výšku a šíøku dle typu scrollbaru
    if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )
    {
        SetWidth( mf_Length );
        SetHeight( mf_Size );
    }
    else
    {
        SetWidth( mf_Size );
        SetHeight( mf_Length );
    }
    
    // Nastavím barvy
    ms_BorderColor = crs_borderColor;
    ms_InteriorColor = crs_interiorColor;
    
    mf_K = f_k;
    
    // Vypoèítám mezeru mezi okrajem a vnitøními prvky (buttony, slider)        
    mf_Space = mf_Size * ( 1.0 - mf_K ) * 0.5;
            
    // Vypoèítám velikost vnitøních prvkù
    mf_ElementSize = mf_K * mf_Size;
    
    // Spoèítám umístìní buttonù  
    if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )
    {
        mf_ButtonMinusX = mf_Space;
        mf_ButtonMinusY = mf_Space;  
        
        mf_ButtonPlusX = mf_Length - mf_Space - mf_ElementSize;
        mf_ButtonPlusY =  mf_Space;      
    }
    else
    {
        mf_ButtonMinusX = mf_Space;
        mf_ButtonMinusY = mf_Length - mf_Space - mf_ElementSize; 
        
        mf_ButtonPlusX = mf_Space;
        mf_ButtonPlusY = mf_Space; 
    }
        
    // Nastavím velikost slideru na maximum
    mf_SliderLength = ( mf_Length - 2.0 * mf_Size );
    
    // Nastavím polohu slideru k levému/hornímu buttonu
    if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )
    {
        mf_SliderX = mf_ButtonMinusX + mf_ElementSize + mf_Space;
        mf_SliderY = mf_ButtonMinusY;
        
        mf_MinSliderPosition = mf_MaxSliderPosition = mf_SliderX;
    }
    else
    {
        mf_SliderX = mf_ButtonMinusX;
        mf_SliderY = mf_ButtonMinusY - mf_Space - mf_SliderLength; 
                
        mf_MinSliderPosition = mf_MaxSliderPosition = mf_SliderY;           
    }  
}

void EE_GUI_SCROLLBAR_C::UpdateSlider( EE_FLOAT_t f_outterObjectLength, EE_FLOAT_t f_outterObjectTotal )
{
    if( f_outterObjectLength > f_outterObjectTotal )
        EE_ERROR_C(  );
    
    mf_SliderLength = ( mf_Length - 2.0 * mf_Size ) * ( f_outterObjectLength / f_outterObjectTotal );
    
    if( me_ScrollbarType == EE_GUI_SCROLLBAR_VERTICAL )
        mf_SliderY = mf_ButtonMinusY - mf_Space - mf_SliderLength; 
  
    
    mf_MaxSliderPosition = mf_MinSliderPosition + ( mf_Length - 2.0 * mf_Size ) - mf_SliderLength;     
}
                  
void EE_GUI_SCROLLBAR_C::Draw( void )
{
    // Vnìjší rám
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
                           
    // Levý/spodní button
    DrawRectangle( GetPositionX() + mf_ButtonMinusX, 
                   GetPositionX() + mf_ButtonMinusX + mf_ElementSize, 
                   GetPositionY() + mf_ButtonMinusY, 
                   GetPositionY() + mf_ButtonMinusY + mf_ElementSize,
                   ms_BorderColor, 
                   0 ); 
            
    // Pravý/horní button
    DrawRectangle( GetPositionX() + mf_ButtonPlusX, 
                   GetPositionX() + mf_ButtonPlusX + mf_ElementSize, 
                   GetPositionY() + mf_ButtonPlusY, 
                   GetPositionY() + mf_ButtonPlusY + mf_ElementSize,
                   ms_BorderColor, 
                   0 ); 
                           
    // Slider
    if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )
    {
        DrawRectangle( GetPositionX() + mf_SliderX, 
                       GetPositionX() + mf_SliderX + mf_SliderLength, 
                       GetPositionY() + mf_SliderY, 
                       GetPositionY() + mf_SliderY + mf_ElementSize,
                       ms_InteriorColor, 
                       1 ); 
                       
        DrawRectangle( GetPositionX() + mf_SliderX, 
                       GetPositionX() + mf_SliderX + mf_SliderLength, 
                       GetPositionY() + mf_SliderY, 
                       GetPositionY() + mf_SliderY + mf_ElementSize,
                       ms_BorderColor, 
                       0 ); 
    }
    else
    {
        DrawRectangle( GetPositionX() + mf_SliderX, 
                       GetPositionX() + mf_SliderX + mf_ElementSize, 
                       GetPositionY() + mf_SliderY, 
                       GetPositionY() + mf_SliderY + mf_SliderLength,
                       ms_InteriorColor, 
                       1 ); 
                       
        DrawRectangle( GetPositionX() + mf_SliderX, 
                       GetPositionX() + mf_SliderX + mf_ElementSize, 
                       GetPositionY() + mf_SliderY, 
                       GetPositionY() + mf_SliderY + mf_SliderLength,
                       ms_BorderColor, 
                       0 ); 
    }
    
                
                
}

EE_U32_t EE_GUI_SCROLLBAR_C::GuiProc( const EE_GUI_MOUSE_s &crs_mouse, 
                                      EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard ) 
{
    if( mb_Callback )
    {
        if( !crs_mouse.b_LB ) 
        {
            mb_Callback = 0;
            return( EE_GUI_SIGNAL_NOTHING );
        }
           
        if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )
        {
            mf_SliderX += crs_mouse.f_X - crs_mouse.f_XBefore;
            
            if( mf_SliderX < mf_MinSliderPosition )
                mf_SliderX = mf_MinSliderPosition;
            if( mf_SliderX > mf_MaxSliderPosition )
                mf_SliderX = mf_MaxSliderPosition;
        }
        else 
        {
            mf_SliderY += crs_mouse.f_Y - crs_mouse.f_YBefore;  
            
            if( mf_SliderY < mf_MinSliderPosition )
                mf_SliderY = mf_MinSliderPosition;
            if( mf_SliderY > mf_MaxSliderPosition )
                mf_SliderY = mf_MaxSliderPosition;  
        }    
        
        return( EE_GUI_SIGNAL_ACTIVECALLBACK );
    }
    
    
    if( PointInRect( crs_mouse.f_X, crs_mouse.f_Y, GetActiveRect() ) && crs_mouse.b_LB && !crs_mouse.b_LBBefore )
    {
        if( GetPositionX() + mf_ButtonMinusX <= crs_mouse.f_X && GetPositionX() + mf_ButtonMinusX + mf_ElementSize >= crs_mouse.f_X &&
            GetPositionY() + mf_ButtonMinusY <= crs_mouse.f_Y && GetPositionY() + mf_ButtonMinusY + mf_ElementSize >= crs_mouse.f_Y )
        {
            if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )
            {
                mf_SliderX -= mf_SliderLength * 0.2;
                
                if( mf_SliderX < mf_MinSliderPosition )
                    mf_SliderX = mf_MinSliderPosition;
                
            }
            else 
            {
                mf_SliderY += mf_SliderLength * 0.2; 
                
                if( mf_SliderY > mf_MaxSliderPosition )
                    mf_SliderY = mf_MaxSliderPosition;   
            }  
            
            return( EE_GUI_SIGNAL_ACTIVATED );       
        } 
        
        if( GetPositionX() + mf_ButtonPlusX <= crs_mouse.f_X && GetPositionX() + mf_ButtonPlusX + mf_ElementSize >= crs_mouse.f_X &&
            GetPositionY() + mf_ButtonPlusY <= crs_mouse.f_Y && GetPositionY() + mf_ButtonPlusY + mf_ElementSize >= crs_mouse.f_Y )
        {
            if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )
            {
                mf_SliderX += mf_SliderLength * 0.2;
                
                if( mf_SliderX > mf_MaxSliderPosition )
                    mf_SliderX = mf_MaxSliderPosition;
                
            }
            else 
            {
                mf_SliderY -= mf_SliderLength * 0.2; 
                
                if( mf_SliderY < mf_MinSliderPosition )
                    mf_SliderY = mf_MinSliderPosition;   
            }
            
            return( EE_GUI_SIGNAL_ACTIVATED );      
        }   
        
        
        if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )
        {           
            if( GetPositionX() + mf_SliderX <= crs_mouse.f_X && GetPositionX() + mf_SliderX + mf_SliderLength >= crs_mouse.f_X &&
                GetPositionY() + mf_SliderY <= crs_mouse.f_Y && GetPositionY() + mf_SliderY + mf_ElementSize >= crs_mouse.f_Y )
            {
                mb_Callback = 1;
                return( EE_GUI_SIGNAL_ACTIVECALLBACK );                
            }
        }
        else
        {
            if( GetPositionX() + mf_SliderX <= crs_mouse.f_X && GetPositionX() + mf_SliderX + mf_ElementSize >= crs_mouse.f_X &&
                GetPositionY() + mf_SliderY <= crs_mouse.f_Y && GetPositionY() + mf_SliderY + mf_SliderLength >= crs_mouse.f_Y )
            {
                mb_Callback = 1;
                return( EE_GUI_SIGNAL_ACTIVECALLBACK );
            }
            
        }
        
    }
        
    
    return( EE_GUI_SIGNAL_NOTHING );    
}
                                                            
EE_GUI_ELEMENT_TYPE_e EE_GUI_SCROLLBAR_C::GetElementType( void ) const
{
    return( EE_GUI_ELEMENT_TYPE_SCROLLBAR );    
}

void EE_GUI_SCROLLBAR_C::SetLength( EE_FLOAT_t f_length )
{
    EE_FLOAT_t f_OldLength( mf_Length );
    mf_Length = f_length;
    
    // Nastavím skuteènou výšku a šíøku dle typu scrollbaru
    if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )
    {
        SetWidth( mf_Length );
        SetHeight( mf_Size );
        
        mf_ButtonPlusX = mf_Length - mf_Space - mf_ElementSize;
        
    }
    else
    {
        SetWidth( mf_Size );
        SetHeight( mf_Length );
        
        mf_ButtonMinusY = mf_Length - mf_Space - mf_ElementSize;       
       
    }
        
}
        
EE_FLOAT_t EE_GUI_SCROLLBAR_C::GetLength( void ) const
{
    return( mf_Length );    
}

void EE_GUI_SCROLLBAR_C::SetRelativeSliderPosition( EE_FLOAT_t f_position )
{    
    if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )    
    {
        mf_SliderX = f_position * ( mf_MaxSliderPosition - mf_MinSliderPosition ) + mf_MinSliderPosition;
    }
    else
    {
        mf_SliderY = f_position * ( mf_MaxSliderPosition - mf_MinSliderPosition ) + mf_MaxSliderPosition;          
    }        
}

EE_FLOAT_t EE_GUI_SCROLLBAR_C::GetRelativeSliderPosition( void ) const
{
    if( me_ScrollbarType == EE_GUI_SCROLLBAR_HORIZONTAL )    
    {
        return( ( mf_SliderX - mf_MinSliderPosition ) / ( mf_MaxSliderPosition - mf_MinSliderPosition ) );    
    }
    else
    {
        return( ( mf_SliderY - mf_MaxSliderPosition ) / ( mf_MaxSliderPosition - mf_MinSliderPosition ) );           
    }
}

EE_FLOAT_t EE_GUI_SCROLLBAR_C::GetRelativeSliderLength( void ) const
{
    return( mf_SliderLength / ( mf_MaxSliderPosition - mf_MinSliderPosition ) );    
}



