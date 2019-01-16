#ifndef EE_DEBUG_RTDS
#define EE_DEBUG_RTDS

#include <string>
#include <vector>
#include <map>
#include <ostream>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <exzoki/texture/ee_texture_font_manager.h>

// Runt-time debug system
class EE_DEBUG_RTDS_C
{
    public:               
        // P�id�n� RTDS
        static void AddRTDS( EE_CCSTRING_t ccs_name );
        // Z�sk�n� RTDS dle jm�na
        static EE_DEBUG_RTDS_C& GetRTDS( EE_CCSTRING_t ccs_name );
        // Smaz�n� RTDS
        static void DeleteRTDS( EE_CCSTRING_t ccs_name );
        // Nastaven� font mana�eru
        static void SetFontManager( EE_TEXTURE_FONT_MANAGER_C &rC_fontManager );
        // Nastaven� fontu
        static void SetFont( EE_CCSTRING_t ccs_fontName );
        
        // Vy�i�t�n�
        void Clear( void );
        
        // Aktualizace debugovac�ch dat
        void UpdateInfo( EE_CCSTRING_t ccs_id, EE_CCSTRING_t ccs_data, ... );
        // Smaz�n� debugovac�ch dat
        void DeleteInfo( EE_CCSTRING_t ccs_id );
        // Z�sk�n� debugovac�ch dat
        EE_CCSTRING_t GetInfo( EE_CCSTRING_t ccs_id ) const;
        
        // Tisk na obrazovku
        void Print( void );
        // Tisk do souboru
        void Print( std::ostream &rC_outputStream ) const;
        
    private:
        std::map< std::string, std::string > mco_Infos;
        std::string mS_Name;
        
        static std::string S_FontName;
        static EE_TEXTURE_FONT_MANAGER_C* pC_FontManager;
        static std::map< std::string, EE_DEBUG_RTDS_C > co_RTDS;
 
};

#endif
