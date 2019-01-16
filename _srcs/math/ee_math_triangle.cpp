#include <exzoki/math/ee_math_triangle.h>

EE_MATH_TRIANGLE_C::EE_MATH_TRIANGLE_C( void )
{
}

EE_MATH_TRIANGLE_C::EE_MATH_TRIANGLE_C( const EE_MATH_TRIANGLE_C &crC_triangle )
{
 	for( EE_BYTE_t b_Index( 0 ); b_Index < 3; b_Index++ )   
  		this->maC_Points[ b_Index ] = crC_triangle.maC_Points[ b_Index ];
}

EE_MATH_TRIANGLE_C::EE_MATH_TRIANGLE_C( const EE_MATH_POINT_C& crC_point1, const EE_MATH_POINT_C& crC_point2, const EE_MATH_POINT_C& crC_point3 )
{
	maC_Points[ 0 ] = crC_point1;
	maC_Points[ 1 ] = crC_point2;
	maC_Points[ 2 ] = crC_point3;
}

EE_MATH_TRIANGLE_C& EE_MATH_TRIANGLE_C::operator=( const EE_MATH_TRIANGLE_C &crC_triangle )
{
 	if( &crC_triangle != this )
 	{
  		for( EE_BYTE_t b_Index( 0 ); b_Index < 3; b_Index++ )   
   		this->maC_Points[ b_Index ] = crC_triangle.maC_Points[ b_Index ];
 	}
 	return( *this ); 
} 

void EE_MATH_TRIANGLE_C::Set( EE_BYTE_t b_index, EE_MATH_POINT_C C_point )
{
 	if( b_index > 2 )
  		EE_ERROR_C( "EE_MATH_TRIANGLE_C", "Set", EE_ERROR_CODES_n::cS_BadIndex );    
 	else
  		maC_Points[ b_index ] = C_point;
}

const EE_MATH_VECTOR_C EE_MATH_TRIANGLE_C::Normal( void ) const
{
	EE_MATH_VECTOR_C C_Normal( ( maC_Points[ 1 ] - maC_Points[ 0 ] ) % ( maC_Points[ 2 ] - maC_Points[ 0 ] ) );
	C_Normal.Normalize();
	return( C_Normal );    
}

const EE_MATH_POINT_C& EE_MATH_TRIANGLE_C::Get( EE_BYTE_t b_index ) const
{
 	if( b_index > 2 )
  		EE_ERROR_C( "EE_MATH_TRIANGLE_C", "Set", EE_ERROR_CODES_n::cS_BadIndex );    
 	else
  		return( maC_Points[ b_index ] );
}

EE_MATH_1DELEMENT_C EE_MATH_TRIANGLE_C::GetEdge( EE_BYTE_t b_index ) const
{
    if( b_index > 2 )
  		EE_ERROR_C( "EE_MATH_TRIANGLE_C", "GetEdge", EE_ERROR_CODES_n::cS_BadIndex );    
 	else
        return( EE_MATH_1DELEMENT_C( maC_Points[ b_index ], 
                                     maC_Points[ ( b_index == 2 ) ? 0 : b_index + 1 ], 
                                     EE_MATH_1DELEMENT_LINESEGMENT ) );    
}
