#ifndef EE_TEXTURE_FONT_MANAGER_H
#define EE_TEXTURE_FONT_MANAGER_H

#include <exzoki/texture/ee_texture_font.h>
#include <exzoki/template/ee_template_file_manager.h>

class EE_TEXTURE_FONT_MANAGER_C: public EE_TEMPLATE_FILE_MANAGER_C< EE_TEXTURE_FONT_C >
{
    public:
        EE_TEXTURE_FONT_MANAGER_C( void );
        ~EE_TEXTURE_FONT_MANAGER_C( void );
        
        void SetFont( EE_CCSTRING_t ccs_path );
        void Print( EE_FLOAT_t f_size, EE_CCSTRING_t ccs_format, ... ) const;
    
    private:
        std::map< std::string, EE_TEXTURE_FONT_C >::const_iterator mcI_CurrentFont;     
};


#endif
