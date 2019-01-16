#ifndef EE_GUI_BUTTON_H
#define EE_GUI_BUTTON_H

#include <exzoki/gui/ee_gui_base.h>
#include <exzoki/texture/ee_texture_font_manager.h>

class EE_GUI_BUTTON_C: public EE_GUI_BASE_C
{
    public:
        EE_GUI_BUTTON_C( void );
        
        void SetText( std::string S_text,
                      std::string S_font,
                      const EE_SYSTEM_COLOR_s &crs_color,
                      EE_FLOAT_t f_size,
                      EE_FLOAT_t f_space );                      
        void UpdateText( std::string S_text );              
        void SetExteriorColor( const EE_SYSTEM_COLOR_s &crs_exteriorColor );
        void SetBorderColor( const EE_SYSTEM_COLOR_s &crs_borderColor );
        void SetInteriorColor( const EE_SYSTEM_COLOR_s &crs_interiorColor );
        void SetNInterpolationLevels( EE_BYTE_t b_il );
        
        virtual void Draw( void );
        virtual EE_U32_t GuiProc( const EE_GUI_MOUSE_s &crs_mouse, 
                                         EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard );
        virtual EE_GUI_ELEMENT_TYPE_e GetElementType( void ) const;
        
        static void SetFontManager( EE_TEXTURE_FONT_MANAGER_C& rC_fontManager );              
      
    private: 
        void CalculateDimensions( void );
           
        EE_SYSTEM_COLOR_s ms_BorderColor,
                          ms_InteriorColor,
                          ms_ExteriorColor,
                          ms_TextColor;
        EE_BYTE_t mb_NInterpolationLevels;
        EE_FLOAT_t mf_TextSize;
        EE_FLOAT_t mf_TextSpacing;
        std::string mS_Text;
        std::string mS_TextFont;        
        
        static EE_TEXTURE_FONT_MANAGER_C *pC_FontManager;
};

#endif
