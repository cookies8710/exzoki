#ifndef EE_GUI_SYSTEM_H
#define EE_GUI_SYSTEM_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_input_mouse.h>
#include <exzoki/system/ee_system_input_keyboard.h>
#include <exzoki/gui/ee_gui_types.h>
#include <exzoki/gui/ee_gui_base.h>
#include <exzoki/gui/ee_gui_button.h>
#include <exzoki/gui/ee_gui_editbox.h>
#include <exzoki/gui/ee_gui_base.h>
#include <exzoki/gui/ee_gui_scrollbar.h>
#include <exzoki/gui/ee_gui_window.h>
#include <gl/gl.h>
#include <map>
#include <list>

typedef void (*EE_GUI_PROC_t)( EE_GUI_ID_t );

class EE_GUI_SYSTEM_C
{
    public:
        EE_GUI_SYSTEM_C( void );
        EE_GUI_SYSTEM_C( const EE_SYSTEM_INPUT_MOUSE_C *cpC_mouse,
                         EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard,
                         EE_FLOAT_t f_left, EE_FLOAT_t f_right, EE_FLOAT_t f_bottom, EE_FLOAT_t f_top,
                         EE_U32_t u32_screenWidth, EE_U32_t u32_screenHeight,
                         EE_GUI_PROC_t pf_guiProc );
        ~EE_GUI_SYSTEM_C( void );
        
        void SetUp( const EE_SYSTEM_INPUT_MOUSE_C *cpC_mouse,
                    EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard,
                    EE_FLOAT_t f_left, EE_FLOAT_t f_right, EE_FLOAT_t f_bottom, EE_FLOAT_t f_top,
                    EE_U32_t u32_screenWidth, EE_U32_t u32_screenHeight,
                    EE_GUI_PROC_t pf_guiProc );
        
        EE_GUI_ID_t CreateGuiElement( const EE_GUI_BASE_C &crC_guiElement );
        void DeleteGuiElement( EE_GUI_ID_t t_id );
        
        void Clear( void );
        
        void GuiProc( void );
        
        const EE_GUI_BASE_C* GetGuiElement( EE_GUI_ID_t t_id ) const;
        EE_GUI_BASE_C* GetGuiElement( EE_GUI_ID_t t_id );
                
    private:
        const EE_SYSTEM_INPUT_MOUSE_C *mcpC_Mouse;
        EE_GUI_MOUSE_s ms_MouseData;
        
        EE_SYSTEM_INPUT_KEYBOARD_C *mpC_Keyboard;
        
        EE_GUI_PROC_t mpf_GuiProc;
        
        std::map< EE_GUI_ID_t, EE_GUI_BASE_C* > mco_GuiElements;
        std::list< EE_GUI_ID_t > mco_GuiElementsZ; 
        
        EE_GUI_RECTANGLE_s ms_ScreenRectangle;
        EE_U32_t mu32_ScreenWidth, mu32_ScreenHeight; 
        
        EE_PU32_t mpu32_IDs;
        EE_U32_t mu32_NIDAlocated;   
        
        EE_BOOL_t mb_Callback;
        EE_GUI_ID_t mu32_CallbackElement;                     
};

#endif
