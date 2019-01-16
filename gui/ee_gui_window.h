#ifndef EE_GUI_WINDOW_H
#define EE_GUI_WINDOW_H

#include <string>
#include <vector> 
#include <exzoki/math/ee_math_point.h>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/gui/ee_gui_types.h>
#include <exzoki/gui/ee_gui_base.h>
#include <exzoki/gui/ee_gui_scrollbar.h>
#include <exzoki/gui/ee_gui_button.h>
#include <exzoki/gui/ee_gui_editbox.h>

class EE_GUI_WINDOW_C: public EE_GUI_BASE_C
{
    public:
        EE_GUI_WINDOW_C( void );
        
        virtual void Draw( void );
        virtual EE_U32_t GuiProc( const EE_GUI_MOUSE_s &crs_mouse, 
                                  EE_SYSTEM_INPUT_KEYBOARD_C *pC_keyboard );
        virtual EE_GUI_ELEMENT_TYPE_e GetElementType( void ) const;
        
        void SetColors( const EE_SYSTEM_COLOR_s &crs_border,
                        const EE_SYSTEM_COLOR_s &crs_interior,
                        const EE_SYSTEM_COLOR_s &crs_exterior,
                        const EE_SYSTEM_COLOR_s &crs_titleText,
                        const EE_SYSTEM_COLOR_s &crs_innerText,
                        const EE_SYSTEM_COLOR_s &crs_innerWindow );
                
        void Set( EE_FLOAT_t f_unitSize,
                  EE_BYTE_t b_nInterpolationLvls,
                  std::string S_titleText,
                  std::string mS_TitleTextFont,
                  std::string mS_InnerTextFont );
        
        void SetInnerText( std::string S_innerText );
        
        static void SetFontManager( EE_TEXTURE_FONT_MANAGER_C& rC_fontManager );
        
    private:    
        void ResizeProc( EE_FLOAT_t f_deltaX, EE_FLOAT_t f_deltaY );
        
        void RecalcWindow( EE_FLOAT_t f_deltaX, EE_FLOAT_t f_deltaY );
        void RecalcTitleBarText( void );
        void RecalcInnerWindow( void );
        void RecalcScrollbars( void );
        
        EE_SYSTEM_COLOR_s ms_BorderColor,
                          ms_InteriorColor,
                          ms_ExteriorColor,
                          ms_TitleTextColor,
                          ms_InnerTextColor,
                          ms_InnerColor;
        EE_BYTE_t mb_NInterpolationLevels;
        
        std::string mS_TitleText;
        std::string mS_VisibleTitleText;
        
        EE_BOOL_t mb_Minimalized;
        
        // Vnitøní text rozdìlený na øádky
        std::vector< std::string > mco_InnerText;
        // Poèet øádkù vnitøního textu
        EE_U32_t mu32_InnerTextNRows;
        
        EE_FLOAT_t mf_UnitSize;
        
        EE_FLOAT_t mf_InnerX, mf_InnerY, // Inner = Position + UnitSize
                   mf_InnerWidth, mf_InnerHeight; // InnerDim = Dim - 2*UnitSize
        
        EE_U32_t mu32_MaxTitleSize;
        
        
        EE_U32_t mu32_MaxInnerTextLength, 
                 mu32_MaxInnerTextRows,
                 mu32_LongestLength;           
         
        EE_BOOL_t mb_MoveCallback,
                  mb_ResizeCallback,
                  mb_VerticalScrollbarCallback,
                  mb_HorizontalScrollbarCallback;
         
        EE_BOOL_t mb_VerticalScrollbar,
                  mb_HorizontalScrollbar;   
        EE_GUI_SCROLLBAR_C mC_VerticalScrollbar,
                           mC_HorizontalScrollbar;
        
        std::string mS_InnerTextFont, mS_TitleTextFont;
        
        static EE_TEXTURE_FONT_MANAGER_C *pC_FontManager;
};


#endif
