#ifndef EE_GUI_BASE_H
#define EE_GUI_BASE_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_input_keyboard.h>
#include <exzoki/gui/ee_gui_types.h>
#include <gl/gl.h>

enum EE_GUI_ELEMENT_TYPE_e{ EE_GUI_ELEMENT_TYPE_BASE = 0,
                            EE_GUI_ELEMENT_TYPE_BUTTON = 1,
                            EE_GUI_ELEMENT_TYPE_EDITBOX,
                            EE_GUI_ELEMENT_TYPE_WINDOW,
                            EE_GUI_ELEMENT_TYPE_SCROLLBAR };

class EE_GUI_BASE_C
{
    public: 
        EE_GUI_BASE_C( void );
        EE_GUI_BASE_C( EE_GUI_ID_t t_id );
        
        virtual void Draw( void );
        virtual EE_U32_t GuiProc( const EE_GUI_MOUSE_s &crs_mouse, 
                                  EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard );
        
        inline EE_GUI_ID_t GetID( void ) const;
        inline EE_FLOAT_t GetPositionX( void ) const;
        inline EE_FLOAT_t GetPositionY( void ) const;
        inline EE_FLOAT_t GetWidth( void ) const;
        inline EE_FLOAT_t GetHeight( void ) const; 
        virtual EE_GUI_ELEMENT_TYPE_e GetElementType( void ) const;
        EE_GUI_RECTANGLE_s GetActiveRect( void ) const;
        
        
        inline void SetID( EE_GUI_ID_t t_id );
        inline void SetPositionX( EE_FLOAT_t f_x );
        inline void SetPositionY( EE_FLOAT_t f_y ); 
        inline void SetWidth( EE_FLOAT_t f_w );
        inline void SetHeight( EE_FLOAT_t f_h );
        inline void MoveX( EE_FLOAT_t f_x );
        inline void MoveY( EE_FLOAT_t f_y );
    
    protected:
        EE_BOOL_t PointInRect( EE_FLOAT_t f_x, EE_FLOAT_t f_y, const EE_GUI_RECTANGLE_s &crs_rectangle ) const;
        
        void DrawRectangle( EE_FLOAT_t f_left,
                            EE_FLOAT_t f_right,
                            EE_FLOAT_t f_bottom,
                            EE_FLOAT_t f_top,
                            const EE_SYSTEM_COLOR_s &crs_color,
                            EE_BOOL_t b_filled ) const;
               
        
    private:        
        EE_GUI_ELEMENT_TYPE_e me_ElementType;        
                     
        // Pozice a rozmìry
        EE_FLOAT_t mf_X, mf_Y;
        EE_FLOAT_t mf_Width, mf_Height;      
        
        // ID
        EE_GUI_ID_t mt_ID;
};

#endif
