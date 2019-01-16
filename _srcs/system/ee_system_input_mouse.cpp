#include <exzoki/system/ee_system_input_mouse.h>

EE_SYSTEM_INPUT_MOUSE_C::EE_SYSTEM_INPUT_MOUSE_C( void )
{
}
        
void EE_SYSTEM_INPUT_MOUSE_C::SetPosition( EE_U32_t u32_x, EE_U32_t u32_y )
{
    mu32_X = u32_x;
    mu32_Y = u32_y;
}

void EE_SYSTEM_INPUT_MOUSE_C::SetLeftButton( EE_BOOL_t b_state )
{
    mb_LeftButtonPressed = b_state;
}

void EE_SYSTEM_INPUT_MOUSE_C::SetRightButton( EE_BOOL_t b_state )
{
    mb_RightButtonPressed = b_state;
}

void EE_SYSTEM_INPUT_MOUSE_C::SetMiddleButton( EE_BOOL_t b_state )
{
    mb_MiddleButtonPressed = b_state;
}
        
EE_U32_t EE_SYSTEM_INPUT_MOUSE_C::GetX( void ) const
{
    return( mu32_X );
}

EE_U32_t EE_SYSTEM_INPUT_MOUSE_C::GetY( void ) const
{
    return( mu32_Y );
}

EE_BOOL_t EE_SYSTEM_INPUT_MOUSE_C::GetLeftButton( void ) const
{
    return( mb_LeftButtonPressed );
}


EE_BOOL_t EE_SYSTEM_INPUT_MOUSE_C::GetRightButton( void ) const
{
    return( mb_RightButtonPressed );
}

EE_BOOL_t EE_SYSTEM_INPUT_MOUSE_C::GetMiddleButton( void ) const
{
    return( mb_MiddleButtonPressed );
}
