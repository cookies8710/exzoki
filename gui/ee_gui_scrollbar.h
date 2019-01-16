#ifndef EE_GUI_SCROLLBAR
#define EE_GUI_SCROLLBAR

#include <exzoki/gui/ee_gui_base.h>

enum EE_GUI_SCROLLBAR_TYPE_e{ EE_GUI_SCROLLBAR_HORIZONTAL = 1,
                              EE_GUI_SCROLLBAR_VERTICAL = 2 };

class EE_GUI_SCROLLBAR_C: public EE_GUI_BASE_C
{
    public:
        
        void Set( EE_GUI_SCROLLBAR_TYPE_e e_type,
                  EE_FLOAT_t f_length, EE_FLOAT_t f_size,
                  const EE_SYSTEM_COLOR_s &crs_borderColor, const EE_SYSTEM_COLOR_s &crs_interiorColor,
                  EE_FLOAT_t f_k );
        void UpdateSlider( EE_FLOAT_t f_outterObjectLength, EE_FLOAT_t f_outterObjectTotal );
        
        virtual void Draw( void );
        virtual EE_U32_t GuiProc( const EE_GUI_MOUSE_s &crs_mouse, 
                                         EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard );        
        virtual EE_GUI_ELEMENT_TYPE_e GetElementType( void ) const;
        
        void SetLength( EE_FLOAT_t f_length );
        
        EE_FLOAT_t GetLength( void ) const;
        
        void SetRelativeSliderPosition( EE_FLOAT_t f_position );
        
        // Vrací relativní pozici slideru (0.0=zaèátek, 1.0=konec)
        EE_FLOAT_t GetRelativeSliderPosition( void ) const;
        
        EE_FLOAT_t GetRelativeSliderLength( void ) const;
        
    private:
        // Typ scrollbaru (horizontální/vertikální)
        EE_GUI_SCROLLBAR_TYPE_e me_ScrollbarType;
        
        // Barvy okraje a vniøního prostoru
        EE_SYSTEM_COLOR_s ms_BorderColor, 
                          ms_InteriorColor;
        
        // Délka a velikost
        EE_FLOAT_t mf_Length, mf_Size;
        
        // Konstanta K, vzdálenost Space prvkù od okraje
        EE_FLOAT_t mf_K, // 0 < K < 1
                   mf_Space; // Space=Size(1-K)*0.5
        
        // Šíøka slideru
        EE_FLOAT_t mf_SliderLength;
        
        // Limity pozice slider
        EE_FLOAT_t mf_MinSliderPosition, 
                   mf_MaxSliderPosition;
        
        // Velikost strany prvkù
        EE_FLOAT_t mf_ElementSize; // K * Size
        
        // Pozice prvkù (vždy levý spodní roh)
        EE_FLOAT_t mf_ButtonMinusX, mf_ButtonMinusY;
        EE_FLOAT_t mf_ButtonPlusX, mf_ButtonPlusY;
        EE_FLOAT_t mf_SliderX, mf_SliderY;
        
        
        
        // Callback vlajka
        EE_BOOL_t mb_Callback;
        
};


#endif
