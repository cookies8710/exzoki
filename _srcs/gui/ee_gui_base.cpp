#include <exzoki/gui/ee_gui_base.h>

 
EE_GUI_BASE_C::EE_GUI_BASE_C( void )
{
}
        
EE_GUI_BASE_C::EE_GUI_BASE_C( EE_GUI_ID_t t_id ): mt_ID( t_id )
{            
}
        
void EE_GUI_BASE_C::Draw( void )
{
}

EE_U32_t EE_GUI_BASE_C::GuiProc( const EE_GUI_MOUSE_s &crs_mouse, 
                                        EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard )
{
    return( EE_GUI_SIGNAL_NOTHING );
}
        
EE_GUI_ID_t EE_GUI_BASE_C::GetID( void ) const
{
    return( mt_ID );    
}

EE_FLOAT_t EE_GUI_BASE_C::GetPositionX( void ) const
{
    return( mf_X );    
}

EE_FLOAT_t EE_GUI_BASE_C::GetPositionY( void ) const
{
    return( mf_Y );    
}

EE_GUI_ELEMENT_TYPE_e EE_GUI_BASE_C::GetElementType( void ) const
{
    return( EE_GUI_ELEMENT_TYPE_BASE );    
}

EE_GUI_RECTANGLE_s EE_GUI_BASE_C::GetActiveRect( void ) const
{
    EE_GUI_RECTANGLE_s s_ActiveRectangle = { mf_X, mf_X + mf_Width, mf_Y, mf_Y + mf_Height };
    return( s_ActiveRectangle );    
}
        
void EE_GUI_BASE_C::SetID( EE_GUI_ID_t t_id )
{
    mt_ID = t_id;    
}

void EE_GUI_BASE_C::SetPositionX( EE_FLOAT_t f_x )
{
    mf_X = f_x; 
}

void EE_GUI_BASE_C::SetPositionY( EE_FLOAT_t f_y ) 
{
    mf_Y = f_y; 
}

EE_BOOL_t EE_GUI_BASE_C::PointInRect( EE_FLOAT_t f_x, 
                                      EE_FLOAT_t f_y, 
                                      const EE_GUI_RECTANGLE_s &crs_rectangle ) const
{
    return( f_x >= crs_rectangle.f_Left && f_x <= crs_rectangle.f_Right &&
            f_y >= crs_rectangle.f_Bottom && f_y <= crs_rectangle.f_Top );    
}
        
void EE_GUI_BASE_C::DrawRectangle( EE_FLOAT_t f_left,
                                   EE_FLOAT_t f_right,
                                   EE_FLOAT_t f_bottom,
                                   EE_FLOAT_t f_top,
                                   const EE_SYSTEM_COLOR_s &crs_color,
                                   EE_BOOL_t b_filled ) const
{
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    
    if( b_filled )
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    else
    {
        glLineWidth( 2.5 );
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
    
    glColor4ub( crs_color.b_R, crs_color.b_G, crs_color.b_B, crs_color.b_A );
    glBegin( GL_QUADS );
        glVertex2f( f_left, f_bottom );
        glVertex2f( f_right, f_bottom );
        glVertex2f( f_right, f_top ); 
        glVertex2f( f_left, f_top );        
    glEnd();
    glPopAttrib();
}

inline EE_FLOAT_t EE_GUI_BASE_C::GetWidth( void ) const
{
    return( mf_Width );    
}

inline EE_FLOAT_t EE_GUI_BASE_C::GetHeight( void ) const
{
    return( mf_Height );    
}

inline void EE_GUI_BASE_C::SetWidth( EE_FLOAT_t f_w )
{
    mf_Width = f_w;   
}

inline void EE_GUI_BASE_C::SetHeight( EE_FLOAT_t f_h )
{
    mf_Height = f_h;  
}
  
inline void EE_GUI_BASE_C::MoveX( EE_FLOAT_t f_x )
{
    mf_X += f_x;     
}

inline void EE_GUI_BASE_C::MoveY( EE_FLOAT_t f_y )
{
    mf_Y += f_y;       
} 

