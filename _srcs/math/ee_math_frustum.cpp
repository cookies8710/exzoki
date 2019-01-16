#include <exzoki/math/ee_math_frustum.h>

EE_MATH_FRUSTUM_C::EE_MATH_FRUSTUM_C( void )
{
}

EE_MATH_FRUSTUM_C::EE_MATH_FRUSTUM_C( const EE_MATH_FRUSTUM_C& crC_frustum2 )
{
	Build( crC_frustum2 );	
}

EE_MATH_FRUSTUM_C& EE_MATH_FRUSTUM_C::operator=( const EE_MATH_FRUSTUM_C& crC_frustum2 )
{
	if( &crC_frustum2 != this )
		Build( crC_frustum2 );	
	
	return( *this );
}
		
void EE_MATH_FRUSTUM_C::LoadFromOpenGL( void )
{
	GLfloat af_Matrix[ 16 ];
	
	glMatrixMode( GL_PROJECTION_MATRIX );
	
	glPushMatrix();
	
	glGetFloatv( GL_PROJECTION_MATRIX, af_Matrix );
	
	EE_MATH_MATRIX4X4_C C_Matrix;
	C_Matrix = af_Matrix;
	
	maC_Planes[ EE_MATH_FRUSTUM_PLANE_NEAR ].Set( EE_MATH_VECTOR_C( 
													C_Matrix.Get( 3, 0 ) + C_Matrix.Get( 2, 0 ),
													C_Matrix.Get( 3, 1 ) + C_Matrix.Get( 2, 1 ),
													C_Matrix.Get( 3, 2 ) + C_Matrix.Get( 2, 2 ) ),
												 C_Matrix.Get( 3, 3 ) + C_Matrix.Get( 2, 3 ) );
	maC_Planes[ EE_MATH_FRUSTUM_PLANE_FAR ].Set( EE_MATH_VECTOR_C( 
													C_Matrix.Get( 3, 0 ) - C_Matrix.Get( 2, 0 ),
													C_Matrix.Get( 3, 1 ) - C_Matrix.Get( 2, 1 ),
													C_Matrix.Get( 3, 2 ) - C_Matrix.Get( 2, 2 ) ),
												 C_Matrix.Get( 3, 3 ) - C_Matrix.Get( 2, 3 ) );
	maC_Planes[ EE_MATH_FRUSTUM_PLANE_LEFT ].Set( EE_MATH_VECTOR_C( 
													C_Matrix.Get( 3, 0 ) + C_Matrix.Get( 0, 0 ),
													C_Matrix.Get( 3, 1 ) + C_Matrix.Get( 0, 1 ),
													C_Matrix.Get( 3, 2 ) + C_Matrix.Get( 0, 2 ) ),
												 C_Matrix.Get( 3, 3 ) + C_Matrix.Get( 0, 3 ) );
	maC_Planes[ EE_MATH_FRUSTUM_PLANE_RIGHT ].Set( EE_MATH_VECTOR_C( 
													C_Matrix.Get( 3, 0 ) - C_Matrix.Get( 0, 0 ),
													C_Matrix.Get( 3, 1 ) - C_Matrix.Get( 0, 1 ),
													C_Matrix.Get( 3, 2 ) - C_Matrix.Get( 0, 2 ) ),
												 C_Matrix.Get( 3, 3 ) - C_Matrix.Get( 0, 3 ) );
	maC_Planes[ EE_MATH_FRUSTUM_PLANE_BOTTOM ].Set( EE_MATH_VECTOR_C( 
													C_Matrix.Get( 3, 0 ) + C_Matrix.Get( 2, 0 ),
													C_Matrix.Get( 3, 1 ) + C_Matrix.Get( 2, 1 ),
													C_Matrix.Get( 3, 2 ) + C_Matrix.Get( 2, 2 ) ),
												 C_Matrix.Get( 3, 3 ) + C_Matrix.Get( 2, 3 ) );
	maC_Planes[ EE_MATH_FRUSTUM_PLANE_TOP ].Set( EE_MATH_VECTOR_C( 
													C_Matrix.Get( 3, 0 ) - C_Matrix.Get( 2, 0 ),
													C_Matrix.Get( 3, 1 ) - C_Matrix.Get( 2, 1 ),
													C_Matrix.Get( 3, 2 ) - C_Matrix.Get( 2, 2 ) ),
												 C_Matrix.Get( 3, 3 ) - C_Matrix.Get( 2, 3 ) );									 
												 
	
	glPopMatrix();
	
	glMatrixMode( GL_MODELVIEW_MATRIX );
}
		
const EE_MATH_PLANE_C& EE_MATH_FRUSTUM_C::GetPlane( EE_MATH_FRUSTUM_PLANE_e e_plane ) const
{
	return( maC_Planes[ e_plane ] );	
}

void EE_MATH_FRUSTUM_C::Build( const EE_MATH_FRUSTUM_C& crC_frustum2 )
{
	for( EE_BYTE_t b_Plane( 0 ); b_Plane < 6; b_Plane++ )
		this->maC_Planes[ b_Plane ]	= crC_frustum2.maC_Planes[ b_Plane ];
}
