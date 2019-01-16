#ifndef EE_MATH_SPHERE_H
#define EE_MATH_SPHERE_H

#include <exzoki/math/ee_math_types.h>
#include <exzoki/math/ee_math_point.h>
#include <exzoki/math/ee_math_plane.h>

class EE_MATH_SPHERE_C
{
 	public:
  		EE_MATH_SPHERE_C( void );   
  
  		void SetPosition( const EE_MATH_POINT_C& crC_position );
  		void SetPosition( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z );
  		void SetRadius( EE_MATH_TYPE_t t_radius );
  		
  		EE_MATH_PLANE_C GetTangentPlane( const EE_MATH_POINT_C& crC_point ) const;
  		
		EE_MATH_TYPE_t GetRadius( void ) const;
  		EE_MATH_TYPE_t GetRadiusPow2( void ) const;
  		const EE_MATH_POINT_C& GetPosition( void ) const;
  		EE_MATH_TYPE_t GetX( void ) const;
  		EE_MATH_TYPE_t GetY( void ) const;
  		EE_MATH_TYPE_t GetZ( void ) const;  		
              
 	private:
  		EE_MATH_POINT_C mC_Position;   
  		EE_MATH_TYPE_t mt_Radius;          
};

#endif
