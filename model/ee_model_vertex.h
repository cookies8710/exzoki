#ifndef EE_MODEL_VERTEX_H
#define EE_MODEL_VERTEX_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/math/ee_math_point.h>

class EE_MODEL_VERTEX_C
{
	public:
		EE_MODEL_VERTEX_C( void );
		EE_MODEL_VERTEX_C( EE_FLOAT_t f_x, EE_FLOAT_t f_y, EE_FLOAT_t f_z );
		
		void Set( EE_FLOAT_t f_x, EE_FLOAT_t f_y, EE_FLOAT_t f_z );
			
		EE_MATH_POINT_C GetPosition( void ) const;
		
		EE_FLOAT_t GetX( void ) const;
		EE_FLOAT_t GetY( void ) const;
		EE_FLOAT_t GetZ( void ) const;
		
		void Read( EE_SYSTEM_FILE_C& rC_file );
		
	private:		
		EE_FLOAT_t mf_X;
		EE_FLOAT_t mf_Y;
		EE_FLOAT_t mf_Z;
};

#endif
