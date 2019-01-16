#ifndef EE_SYSTEM_INPUT_MOUSE_H
#define EE_SYSTEM_INPUT_MOUSE_H

#include <exzoki/system/ee_system_types.h>

class EE_SYSTEM_INPUT_MOUSE_C
{
    public:
        EE_SYSTEM_INPUT_MOUSE_C( void );
        
        void SetPosition( EE_U32_t u32_x, EE_U32_t u32_y );
        void SetLeftButton( EE_BOOL_t b_state );
        void SetRightButton( EE_BOOL_t b_state );
        void SetMiddleButton( EE_BOOL_t b_state );
        
        EE_U32_t GetX( void ) const;
        EE_U32_t GetY( void ) const;
        EE_BOOL_t GetLeftButton( void ) const;
        EE_BOOL_t GetRightButton( void ) const;
        EE_BOOL_t GetMiddleButton( void ) const;
        
    private:
        EE_BOOL_t mb_LeftButtonPressed;
        EE_BOOL_t mb_RightButtonPressed;
        EE_BOOL_t mb_MiddleButtonPressed;
        EE_U32_t mu32_X;
        EE_U32_t mu32_Y;    
};

#endif
