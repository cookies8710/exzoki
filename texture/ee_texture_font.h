#ifndef EE_TEXTURE_FONT_H
#define EE_TEXTURE_FONT_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/texture/ee_texture.h>

namespace EE_EXZOKI_n
{
    EE_TEXTURE_FILTERING_e ce_TEXTURE_FONT_FILTERING = EE_TEXTURE_FILTERING_NEAREST; 
    const float cf_TextureFontRelativeWidth = 0.5f;   
};

class EE_TEXTURE_FONT_C: public EE_TEXTURE_C
{
	public:
  		EE_TEXTURE_FONT_C( void );
  		~EE_TEXTURE_FONT_C( void );
  		void Load( EE_CCSTRING_t ccs_path );
  		void Print( EE_FLOAT_t f_size, EE_CCSTRING_t ccs_format, ... ) const;
 
	private:
 		void Destroy( void );
 		
 		EE_BOOL_t mb_FontLoaded;
  		EE_U32_t mu32_Base; 
};

#endif
