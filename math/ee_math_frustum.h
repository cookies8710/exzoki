#ifndef EE_MATH_FRUSTUM_H
#define EE_MATH_FRUSTUM_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/math/ee_math_types.h>
#include <exzoki/math/ee_math_plane.h>
#include <exzoki/math/ee_math_matrix4x4.h>
#include <gl/gl.h>

enum EE_MATH_FRUSTUM_PLANE_e
{
	EE_MATH_FRUSTUM_PLANE_NEAR = 0,	
	EE_MATH_FRUSTUM_PLANE_FAR = 1,	
	EE_MATH_FRUSTUM_PLANE_LEFT = 2,	
	EE_MATH_FRUSTUM_PLANE_RIGHT = 3,	
	EE_MATH_FRUSTUM_PLANE_BOTTOM = 4,	
	EE_MATH_FRUSTUM_PLANE_TOP = 5
};

class EE_MATH_FRUSTUM_C
{
	public:
		EE_MATH_FRUSTUM_C( void );
		EE_MATH_FRUSTUM_C( const EE_MATH_FRUSTUM_C& crC_frustum2 );
		EE_MATH_FRUSTUM_C& operator=( const EE_MATH_FRUSTUM_C& crC_frustum2 );
		
		void LoadFromOpenGL( void );
		
		const EE_MATH_PLANE_C& GetPlane( EE_MATH_FRUSTUM_PLANE_e e_plane ) const;
		
	private:
		void Build( const EE_MATH_FRUSTUM_C& crC_frustum2 );
		
		EE_MATH_PLANE_C maC_Planes[ 6 ];	
	
};

#endif
