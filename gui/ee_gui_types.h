#ifndef EE_GUI_TYPES_H
#define EE_GUI_TYPES_H

#include <exzoki/system/ee_system_types.h>

struct EE_GUI_RECTANGLE_s
{
    EE_FLOAT_t f_Left, f_Right, f_Bottom, f_Top;    
};

struct EE_GUI_MOUSE_s
{
    EE_FLOAT_t f_X, f_Y, f_XBefore, f_YBefore;
    EE_BOOL_t b_LB, b_LBBefore;
};

typedef EE_U32_t EE_GUI_ID_t;
enum EE_GUI_SIGNAL_e{ EE_GUI_SIGNAL_NOTHING = 1,
                      EE_GUI_SIGNAL_ACTIVATED, 
                      EE_GUI_SIGNAL_CALLBACK,
                      EE_GUI_SIGNAL_DELETE,
                      EE_GUI_SIGNAL_ACTIVECALLBACK };

class EE_GUI_BASE_C;
class EE_GUI_BUTTON_C;
class EE_GUI_EDITBOX_C;
class EE_GUI_WINDOW_C;

#endif
