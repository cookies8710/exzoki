#ifndef EE_MATH_TRIANGLE_H
#define EE_MATH_TRIANGLE_H

#include <exzoki/math/ee_math_point.h>
#include <exzoki/system/ee_system_types.h>

class EE_MATH_TRIANGLE_C
{
 	public:
  		EE_MATH_TRIANGLE_C( void );
  		EE_MATH_TRIANGLE_C( const EE_MATH_TRIANGLE_C &crC_triangle );
  		EE_MATH_TRIANGLE_C( const EE_MATH_POINT_C& crC_point1, const EE_MATH_POINT_C& crC_point2, const EE_MATH_POINT_C& crC_point3 );
  		EE_MATH_TRIANGLE_C& operator=( const EE_MATH_TRIANGLE_C &crC_triangle );   
     
  		// Nastaví bod
  		void Set( EE_BYTE_t b_index, EE_MATH_POINT_C C_point );
  
  		// Vrátí normálu
  		const EE_MATH_VECTOR_C Normal( void ) const;
  
  		// Vrátí bod
  		const EE_MATH_POINT_C& Get( EE_BYTE_t b_index ) const;
  		// Vrátí stranu
  		EE_MATH_1DELEMENT_C GetEdge( EE_BYTE_t b_index ) const;
        
 	private:  
  		EE_MATH_POINT_C maC_Points[ 3 ]; 
};

#endif
