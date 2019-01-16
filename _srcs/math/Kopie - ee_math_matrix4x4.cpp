#include <exzoki/math/ee_math_matrix4x4.h>

EE_MATH_MATRIX4X4_C::EE_MATH_MATRIX4X4_C( void )
{
	for( EE_BYTE_t b_I( 0 ); b_I < 16; b_I++ )
		mat_Matrix[ b_I ] = 0.0;
}

EE_MATH_MATRIX4X4_C::~EE_MATH_MATRIX4X4_C( void )
{
}
		
EE_MATH_MATRIX4X4_C::EE_MATH_MATRIX4X4_C( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 )
{
	Build( crC_matrix4x4 );
}

EE_MATH_MATRIX4X4_C& EE_MATH_MATRIX4X4_C::operator=( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 )
{
	if( &crC_matrix4x4 != this )
		Build( crC_matrix4x4 );
	
	return( *this );	
}
		

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::operator+( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 ) const
{
	EE_MATH_MATRIX4X4_C C_Result;
	
	for( EE_BYTE_t b_I( 0 ); b_I < 16; b_I++ )
		C_Result.mat_Matrix[ b_I ] = this->mat_Matrix[ b_I ] + crC_matrix4x4.mat_Matrix[ b_I ];
		
	return( C_Result );
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::operator-( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 ) const
{
	EE_MATH_MATRIX4X4_C C_Result;
	
	for( EE_BYTE_t b_I( 0 ); b_I < 16; b_I++ )
		C_Result.mat_Matrix[ b_I ] = this->mat_Matrix[ b_I ] - crC_matrix4x4.mat_Matrix[ b_I ];
		
	return( C_Result );
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::operator*( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 ) const
{
	EE_MATH_MATRIX4X4_C C_Result;
	
	for( EE_BYTE_t b_Column( 0 ); b_Column < 4; b_Column++ )
		for( EE_BYTE_t b_Row( 0 ); b_Row < 4; b_Row++ )
	   { 
		   C_Result.mat_Matrix[ b_Row * 4 + b_Column ] = 0.0f;
		   for( EE_BYTE_t b_Component( 0 ); b_Component < 4; b_Component++ )
		      C_Result.mat_Matrix[ b_Row * 4 + b_Column ] += 
                this->Get( b_Row, b_Component ) * 
                crC_matrix4x4.Get( b_Component, b_Column );
	   }
	
	return( C_Result );	
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::operator*( EE_MATH_TYPE_t t_number ) const
{
	EE_MATH_MATRIX4X4_C C_Result;
	
	for( EE_BYTE_t b_I( 0 ); b_I < 16; b_I++ )
		C_Result.mat_Matrix[ b_I ] = this->mat_Matrix[ b_I ] * t_number;
		
	return( C_Result );
}
		
EE_MATH_VECTOR_C EE_MATH_MATRIX4X4_C::operator*( const EE_MATH_VECTOR_C &crC_vector ) const
{
	EE_MATH_VECTOR_C C_Result;	
	
	C_Result.Set( mat_Matrix[0]*crC_vector.GetX()+mat_Matrix[1]*crC_vector.GetY()+mat_Matrix[2]*crC_vector.GetZ()+mat_Matrix[3],
	              mat_Matrix[4]*crC_vector.GetX()+mat_Matrix[5]*crC_vector.GetY()+mat_Matrix[6]*crC_vector.GetZ()+mat_Matrix[7],
				  mat_Matrix[8]*crC_vector.GetX()+mat_Matrix[9]*crC_vector.GetY()+mat_Matrix[10]*crC_vector.GetZ()+mat_Matrix[11] );
	
	return( C_Result );
}
		
//void EE_MATH_MATRIX4X4_C::Transponse( void );		
		
void EE_MATH_MATRIX4X4_C::LoadIdentity( void )
{
	for( EE_BYTE_t b_I( 0 ); b_I < 4; b_I++ )
		for( EE_BYTE_t b_J( 0 ); b_J < 4; b_J++ )
		mat_Matrix[ b_I * 4 + b_J ] = ( b_I == b_J )	? 1.0 : 0.0;
}
		
void EE_MATH_MATRIX4X4_C::Translate( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z )
{
	this->operator*( TranslationMatrix( t_x, t_y, t_z ) );	
}

void EE_MATH_MATRIX4X4_C::Scale( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z )
{
	this->operator*( ScalationMatrix( t_x, t_y, t_z ) );
}

void EE_MATH_MATRIX4X4_C::RotateX( EE_MATH_TYPE_t t_theta )
{
	this->operator*( RotationXMatrix( t_theta ) );
}

void EE_MATH_MATRIX4X4_C::RotateY( EE_MATH_TYPE_t t_theta )
{
	this->operator*( RotationYMatrix( t_theta ) );
}

void EE_MATH_MATRIX4X4_C::RotateZ( EE_MATH_TYPE_t t_theta )
{
	this->operator*( RotationZMatrix( t_theta ) );
}

EE_MATH_TYPE_t EE_MATH_MATRIX4X4_C::Get( EE_BYTE_t b_row, EE_BYTE_t b_column ) const
{
	return( mat_Matrix[ b_row * 4 + b_column ] );	
}

const EE_MATH_TYPE_t* EE_MATH_MATRIX4X4_C::GetMatrix( void ) const
{
	return( mat_Matrix );	
}

void EE_MATH_MATRIX4X4_C::Build( const EE_MATH_MATRIX4X4_C& crC_matrix4x4 )
{
	for( EE_BYTE_t b_I( 0 ); b_I < 16; b_I++ )
		mat_Matrix[ b_I ] = crC_matrix4x4.mat_Matrix[ b_I ];	
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::TranslationMatrix(  EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z  )
{
	EE_MATH_MATRIX4X4_C C_TranslationMatrix;	
	
	C_TranslationMatrix.LoadIdentity();
	
	C_TranslationMatrix.mat_Matrix[ 0 * 4 + 3 ] = t_x;
	C_TranslationMatrix.mat_Matrix[ 1 * 4 + 3 ] = t_y;
	C_TranslationMatrix.mat_Matrix[ 2 * 4 + 3 ] = t_z;
	
	return( C_TranslationMatrix );
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::ScalationMatrix(  EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z  )
{
	EE_MATH_MATRIX4X4_C C_ScalationMatrix;	
	
	C_ScalationMatrix.LoadIdentity();
	
	C_ScalationMatrix.mat_Matrix[ 0 * 4 + 0 ] = t_x;
	C_ScalationMatrix.mat_Matrix[ 1 * 4 + 1 ] = t_y;
	C_ScalationMatrix.mat_Matrix[ 2 * 4 + 2 ] = t_z;
	
	return( C_ScalationMatrix );
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::RotationXMatrix(  EE_MATH_TYPE_t t_theta )
{
	EE_MATH_MATRIX4X4_C C_RotationMatrix;	
	
	C_RotationMatrix.LoadIdentity();
	
	C_RotationMatrix.mat_Matrix[ 1 * 4 + 1 ] = cos( t_theta );
	C_RotationMatrix.mat_Matrix[ 1 * 4 + 2 ] = -sin( t_theta );
	C_RotationMatrix.mat_Matrix[ 2 * 4 + 1 ] = sin( t_theta );
	C_RotationMatrix.mat_Matrix[ 2 * 4 + 2 ] = cos( t_theta );
	
	return( C_RotationMatrix );
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::RotationYMatrix(  EE_MATH_TYPE_t t_theta )
{
	EE_MATH_MATRIX4X4_C C_RotationMatrix;	
	
	C_RotationMatrix.LoadIdentity();
	
	C_RotationMatrix.mat_Matrix[ 0 * 4 + 0 ] = cos( t_theta );
	C_RotationMatrix.mat_Matrix[ 0 * 4 + 2 ] = sin( t_theta );
	C_RotationMatrix.mat_Matrix[ 2 * 4 + 0 ] = -sin( t_theta );
	C_RotationMatrix.mat_Matrix[ 2 * 4 + 2 ] = cos( t_theta );
	
	return( C_RotationMatrix );
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::RotationZMatrix(  EE_MATH_TYPE_t t_theta )
{
	EE_MATH_MATRIX4X4_C C_RotationMatrix;	
	
	C_RotationMatrix.LoadIdentity();
	
	C_RotationMatrix.mat_Matrix[ 0 * 4 + 0 ] = cos( t_theta );
	C_RotationMatrix.mat_Matrix[ 0 * 4 + 1 ] = -sin( t_theta ); 
	C_RotationMatrix.mat_Matrix[ 1 * 4 + 0 ] = sin( t_theta );  
	C_RotationMatrix.mat_Matrix[ 1 * 4 + 1 ] = cos( t_theta );
	
	return( C_RotationMatrix );
}
