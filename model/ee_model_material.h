#ifndef EE_MODEL_MATERIAL_H
#define EE_MODEL_MATERIAL_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>

class EE_MODEL_MATERIAL_C
{
 	public:
  		EE_MODEL_MATERIAL_C( void );
  		EE_MODEL_MATERIAL_C( const EE_MODEL_MATERIAL_C& crC_material );
  		EE_MODEL_MATERIAL_C& operator=( const EE_MODEL_MATERIAL_C& crC_material );
 
  		void SetColor( EE_BYTE_t b_r, EE_BYTE_t b_g, EE_BYTE_t b_b );
  		void SetColor( EE_BYTE_t ab_color[ 3 ] );
  		void SetTexture( EE_CCSTRING_t cpc_texturePath );
  		void SetTexture( const std::string& crS_texturePath );
 
  		EE_BYTE_t GetColor( EE_U32_t u32_index ) const;
  		EE_BYTE_t HasTexture( void ) const;
  		EE_CCSTRING_t GetTexture( void ) const;
  		
  		
        inline void EE_MODEL_MATERIAL_C::Read( EE_SYSTEM_FILE_C& rC_file );
 
	 private:   
  		EE_BYTE_t mab_Color[ 3 ]; 
  		EE_BYTE_t mb_HasTexture;
  		std::string mS_TexturePath;  
};

#endif
