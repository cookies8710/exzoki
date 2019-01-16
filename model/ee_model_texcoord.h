#ifndef EE_MODEL_TEXCOORD_H
#define EE_MODEL_TEXCOORD_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>

class EE_MODEL_TEXCOORD_C
{
	public:
		EE_MODEL_TEXCOORD_C( void );
		EE_MODEL_TEXCOORD_C( EE_FLOAT_t f_u, EE_FLOAT_t f_v );
		
		void Set( EE_FLOAT_t f_u, EE_FLOAT_t f_v );
		void SetU( EE_FLOAT_t f_u );
		void SetV( EE_FLOAT_t f_v );
		
		EE_FLOAT_t GetU( void ) const;
		EE_FLOAT_t GetV( void ) const;
		
		void EE_MODEL_TEXCOORD_C::Read( EE_SYSTEM_FILE_C& rC_file );
				
	private:	
		EE_FLOAT_t mf_U;
		EE_FLOAT_t mf_V;
};

#endif
