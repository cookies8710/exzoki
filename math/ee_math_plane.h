#ifndef EE_MATH_PLANE_H
#define EE_MATH_PLANE_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/math/ee_math_types.h>
#include <exzoki/math/ee_math_point.h>
#include <exzoki/math/ee_math_vector.h>
#include <exzoki/math/ee_math_1delement.h>
#include <exzoki/math/ee_math_triangle.h>

class EE_MATH_PLANE_C
{
 	public:
  		EE_MATH_PLANE_C( void );
  		EE_MATH_PLANE_C( const EE_MATH_VECTOR_C& crC_normal, EE_MATH_TYPE_t t_d );  
  		EE_MATH_PLANE_C( const EE_MATH_VECTOR_C& crC_normal, const EE_MATH_POINT_C& crC_planePoint );
  		EE_MATH_PLANE_C( const EE_MATH_POINT_C& crC_pointA, 
                    	 const EE_MATH_POINT_C& crC_pointB, 
                    	 const EE_MATH_POINT_C& crC_pointC );
        EE_MATH_PLANE_C( const EE_MATH_TRIANGLE_C& crC_triangle );
  
		void Set( const EE_MATH_VECTOR_C& crC_normal, EE_MATH_TYPE_t t_d );  
  		void Set( const EE_MATH_VECTOR_C& crC_normal, const EE_MATH_POINT_C& crC_planePoint );
  		void Set( const EE_MATH_POINT_C& crC_pointA, 
            	  const EE_MATH_POINT_C& crC_pointB, 
            	  const EE_MATH_POINT_C& crC_pointC );
        void Set( const EE_MATH_TRIANGLE_C& crC_triangle );
 
  		/*EE_MATH_POINT_C LineIntersection( const EE_MATH_1DELEMENT_C& crC_line, 
                                        EE_BOOL_t& rb_collision ) const;*/
  		EE_MATH_POSITION_e PointPosition( const EE_MATH_POINT_C& crC_point ) const;
  		EE_MATH_POSITION_e TrianglePosition( const EE_MATH_POINT_C& crC_pointA, 
                                             const EE_MATH_POINT_C& crC_pointB, 
                                             const EE_MATH_POINT_C& crC_pointC ) const;
        EE_MATH_POSITION_e TrianglePosition( const EE_MATH_TRIANGLE_C& crC_triangle ) const;
  		EE_MATH_POINT_C ProjectPoint( const EE_MATH_POINT_C &crC_point ) const;
        
        EE_MATH_VECTOR_C GetNormal( void ) const;
  		inline EE_MATH_TYPE_t GetD( void ) const;
  		EE_MATH_TYPE_t GetDistance( const EE_MATH_POINT_C &crC_point ) const;
                
 	private:
  		EE_MATH_VECTOR_C mC_Normal;
  		EE_MATH_TYPE_t mt_D;
};

#endif
