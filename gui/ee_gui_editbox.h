#ifndef EE_GUI_EDITBOX_H
#define EE_GUI_EDITBOX_H

#include <string>
#include <exzoki/gui/ee_gui_base.h>
#include <exzoki/texture/ee_texture_font_manager.h>

class EE_GUI_EDITBOX_C: public EE_GUI_BASE_C
{
    public:
        EE_GUI_EDITBOX_C( void );
        
        void SetName( std::string S_name );
        void SetNameColor( const EE_SYSTEM_COLOR_s &crs_nameColor );
        
        void SetText( std::string S_text );
        void SetTextColor( const EE_SYSTEM_COLOR_s &crs_textColor );
        
        
        void SetTextSize( EE_FLOAT_t f_size );
        void SetTextFont( std::string S_font );
        
        void SetExteriorColor( const EE_SYSTEM_COLOR_s &crs_exteriorColor );
        void SetBorderColor( const EE_SYSTEM_COLOR_s &crs_borderColor );
        void SetInteriorColor( const EE_SYSTEM_COLOR_s &crs_interiorColor );
        void SetNInterpolationLevels( EE_BYTE_t b_il );
                
        std::string GetText( void ) const;
        
        virtual void Draw( void );
        virtual EE_U32_t GuiProc( const EE_GUI_MOUSE_s &crs_mouse, 
                                         EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard );
        virtual EE_GUI_ELEMENT_TYPE_e GetElementType( void ) const;
        
        static void SetFontManager( EE_TEXTURE_FONT_MANAGER_C& rC_fontManager );
               
    private:    
        std::string mS_Name;
        std::string mS_Text;
        
        EE_FLOAT_t mf_NameX, mf_NameY;
        
        EE_SYSTEM_COLOR_s ms_BorderColor,
                          ms_InteriorColor,
                          ms_ExteriorColor,
                          ms_NameColor,
                          ms_TextColor;
        EE_BYTE_t b_NInterpolationLevels;
        EE_FLOAT_t mf_TextSize;
        std::string mS_TextFont;
        
        EE_BOOL_t mb_Callback;
        
        EE_U32_t mu32_CursorPosition;
        
        EE_U32_t mu32_MaxTextSize;
        
        static EE_TEXTURE_FONT_MANAGER_C *pC_FontManager;
};

#endif
