#ifndef EE_MATH_1DELEMENT_H
#define EE_MATH_1DELEMENT_H

#include <exzoki/error/ee_error.h>
#include <exzoki/math/ee_math_vector.h>
#include <exzoki/math/ee_math_point.h>

enum EE_MATH_1DELEMENT_TYPE_e
{
 	EE_MATH_1DELEMENT_NOTSET, // Nenastaveno
 	EE_MATH_1DELEMENT_LINESEGMENT, // Úseèka   
 	EE_MATH_1DELEMENT_RAY, // Polopøímka - poèáteèní bod je bod èíslo 1 
 	EE_MATH_1DELEMENT_LINE // Pøímka
};

class EE_MATH_1DELEMENT_C
{
 	public:
  		EE_MATH_1DELEMENT_C( void );
  	//	EE_MATH_1DELEMENT_C( const EE_MATH_POINT_C& crC_point1, const EE_MATH_POINT_C& crC_point2 );
  		EE_MATH_1DELEMENT_C( const EE_MATH_POINT_C& crC_point1, const EE_MATH_POINT_C& crC_point2, EE_MATH_1DELEMENT_TYPE_e e_type );
  
  	//	void Set( const EE_MATH_POINT_C& crC_point1, const EE_MATH_POINT_C& crC_point2 );
  		void Set( const EE_MATH_POINT_C& crC_point1, const EE_MATH_POINT_C& crC_point2, EE_MATH_1DELEMENT_TYPE_e e_type );
  		void SetType( EE_MATH_1DELEMENT_TYPE_e e_type );
  
  		const EE_MATH_POINT_C& GetPoint1( void ) const;
  		const EE_MATH_POINT_C& GetPoint2( void ) const;
  		EE_MATH_VECTOR_C GetVector( void ) const;
  		EE_MATH_1DELEMENT_TYPE_e GetType( void ) const;
  		
  		EE_MATH_POINT_C ClosestPoint( const EE_MATH_POINT_C &crC_point ) const;
 
 	private:
  		EE_MATH_1DELEMENT_TYPE_e me_Type;
  		EE_MATH_POINT_C mC_Point1, mC_Point2;
};

#endif
