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

EE_MATH_MATRIX4X4_C& EE_MATH_MATRIX4X4_C::operator=( const EE_FLOAT_t *cpf_matrix4x4 )
{
	Build( cpf_matrix4x4 );
	
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
		   C_Result.mat_Matrix[ b_Row + b_Column * 4 ] = 0.0f;
		   for( EE_BYTE_t b_Component( 0 ); b_Component < 4; b_Component++ )
		      C_Result.mat_Matrix[ b_Row + b_Column * 4 ] += 
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
	
	C_Result.Set( mat_Matrix[0]*crC_vector.GetX()+mat_Matrix[4]*crC_vector.GetY()+mat_Matrix[8]*crC_vector.GetZ()+mat_Matrix[12],
	              mat_Matrix[1]*crC_vector.GetX()+mat_Matrix[5]*crC_vector.GetY()+mat_Matrix[9]*crC_vector.GetZ()+mat_Matrix[13],
				  mat_Matrix[2]*crC_vector.GetX()+mat_Matrix[6]*crC_vector.GetY()+mat_Matrix[10]*crC_vector.GetZ()+mat_Matrix[14] );
	
	return( C_Result );
}
				
void EE_MATH_MATRIX4X4_C::Inverse( void )
{	
	*this = this->GetInverse();
	
	return;
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::GetInverse( void ) const
{
	EE_MATH_MATRIX4X4_C C_InversedMatrix;
	
	for( EE_BYTE_t b_Row( 0 ); b_Row < 3; b_Row++ )
		for( EE_BYTE_t b_Column( 0 ); b_Column < 3; b_Column++ )
			C_InversedMatrix.mat_Matrix[ b_Row + b_Column * 4 ] = this->mat_Matrix[ b_Column + b_Row * 4 ];
	
	C_InversedMatrix.mat_Matrix[ 0 + 3 * 4 ] = -this->mat_Matrix[ 0 + 3 * 4 ];
	C_InversedMatrix.mat_Matrix[ 1 + 3 * 4 ] = -this->mat_Matrix[ 1 + 3 * 4 ];
	C_InversedMatrix.mat_Matrix[ 2 + 3 * 4 ] = -this->mat_Matrix[ 2 + 3 * 4 ];
	
	return( C_InversedMatrix );		
}
		
void EE_MATH_MATRIX4X4_C::LoadIdentity( void )
{
	for( EE_BYTE_t b_I( 0 ); b_I < 4; b_I++ )
		for( EE_BYTE_t b_J( 0 ); b_J < 4; b_J++ )
		mat_Matrix[ b_I * 4 + b_J ] = ( b_I == b_J ) ? 1.0 : 0.0;
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

void EE_MATH_MATRIX4X4_C::Set( EE_BYTE_t b_row, EE_BYTE_t b_column, EE_MATH_TYPE_t t_value )
{
	mat_Matrix[ b_row + b_column * 4 ] = t_value;	
}

EE_MATH_TYPE_t EE_MATH_MATRIX4X4_C::Get( EE_BYTE_t b_row, EE_BYTE_t b_column ) const
{
	return( mat_Matrix[ b_row + b_column * 4 ] );	
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

void EE_MATH_MATRIX4X4_C::Build( const EE_FLOAT_t *cpf_matrix4x4 )
{
	for( EE_BYTE_t b_I( 0 ); b_I < 16; b_I++ )
		mat_Matrix[ b_I ] = cpf_matrix4x4[ b_I ];		
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::TranslationMatrix(  EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z  )
{
	EE_MATH_MATRIX4X4_C C_TranslationMatrix;	
	
	C_TranslationMatrix.LoadIdentity();
	
	C_TranslationMatrix.mat_Matrix[ 0 + 3 * 4 ] = t_x;
	C_TranslationMatrix.mat_Matrix[ 1 + 3 * 4 ] = t_y;
	C_TranslationMatrix.mat_Matrix[ 2 + 3 * 4 ] = t_z;
	
	return( C_TranslationMatrix );
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::ScalationMatrix(  EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z  )
{
	EE_MATH_MATRIX4X4_C C_ScalationMatrix;	
	
	C_ScalationMatrix.LoadIdentity();
	
	C_ScalationMatrix.mat_Matrix[ 0 + 0 * 4 ] = t_x;
	C_ScalationMatrix.mat_Matrix[ 1 + 1 * 4 ] = t_y;
	C_ScalationMatrix.mat_Matrix[ 2 + 2 * 4 ] = t_z;
	
	return( C_ScalationMatrix );
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::RotationXMatrix(  EE_MATH_TYPE_t t_theta )
{
	EE_MATH_MATRIX4X4_C C_RotationMatrix;	
	
	C_RotationMatrix.LoadIdentity();
	
	C_RotationMatrix.mat_Matrix[ 1 + 1 * 4 ] = cos( t_theta );
	C_RotationMatrix.mat_Matrix[ 1 + 2 * 4 ] = -sin( t_theta );
	C_RotationMatrix.mat_Matrix[ 2 + 1 * 4 ] = sin( t_theta );
	C_RotationMatrix.mat_Matrix[ 2 + 2 * 4 ] = cos( t_theta );
	
	return( C_RotationMatrix );
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::RotationYMatrix(  EE_MATH_TYPE_t t_theta )
{
	EE_MATH_MATRIX4X4_C C_RotationMatrix;	
	
	C_RotationMatrix.LoadIdentity();
	
	C_RotationMatrix.mat_Matrix[ 0 + 0 * 4 ] = cos( t_theta );
	C_RotationMatrix.mat_Matrix[ 0 + 2 * 4 ] = sin( t_theta );
	C_RotationMatrix.mat_Matrix[ 2 + 0 * 4 ] = -sin( t_theta );
	C_RotationMatrix.mat_Matrix[ 2 + 2 * 4 ] = cos( t_theta );
	
	return( C_RotationMatrix );
}

EE_MATH_MATRIX4X4_C EE_MATH_MATRIX4X4_C::RotationZMatrix(  EE_MATH_TYPE_t t_theta )
{
	EE_MATH_MATRIX4X4_C C_RotationMatrix;	
	
	C_RotationMatrix.LoadIdentity();
	
	C_RotationMatrix.mat_Matrix[ 0 + 0 * 4 ] = cos( t_theta );
	C_RotationMatrix.mat_Matrix[ 0 + 1 * 4 ] = -sin( t_theta ); 
	C_RotationMatrix.mat_Matrix[ 1 + 0 * 4 ] = sin( t_theta );  
	C_RotationMatrix.mat_Matrix[ 1 + 1 * 4 ] = cos( t_theta );
	
	return( C_RotationMatrix );
}

void EE_MATH_MATRIX4X4_C::Read( EE_SYSTEM_FILE_C& rC_file )
{
	rC_file.Read( mat_Matrix, 16 * sizeof( EE_FLOAT_t ) );
}

EE_BYTE_t EE_MATH_MATRIX4X4_C::Read( std::ifstream &rC_file )
{}

EE_BYTE_t EE_MATH_MATRIX4X4_C::Write( std::ofstream &rC_file ) const
{}

EE_BYTE_t EE_MATH_MATRIX4X4_C::Dump( std::ofstream &rC_file ) const
{
	EE_XMLLOADER_TAG_C C_Matrix( "EE_MATH_MATRIX4X4_C" ), 
	                   aC_Rows[] = { EE_XMLLOADER_TAG_C( "Row0" ),	
					                 EE_XMLLOADER_TAG_C( "Row1" ), 
									 EE_XMLLOADER_TAG_C( "Row2" ),
									 EE_XMLLOADER_TAG_C( "Row3" ) };
	EE_XMLLOADER_ATTRIBUTE_C C_Comment( "Comment", (EE_CCSTRING_t)mS_Comment.c_str() );
										
	std::string aS_Datas[ 4 ];
	
	int i_DecimalPoint, i_MinusSign;
	std::string S_Buffer; 
	
	for( EE_BYTE_t b_Row( 0 ); b_Row < 4; b_Row++ )
	{
		for( EE_BYTE_t b_Column( 0 ); b_Column < 4; b_Column++ )
		{			
			EE_CHAR_t ac_Buffer[ 32 ];
	
			sprintf( ac_Buffer, "%.6g", Get( b_Row, b_Column ) );
					
			aS_Datas[ b_Row ] += ac_Buffer;				
			
			if( b_Column != 3 )
				aS_Datas[ b_Row ] += ", ";
		}
		
		aC_Rows[ b_Row ].SetData( aS_Datas[ b_Row ].c_str() );
	}
	
	if( mS_Comment.size() )
		C_Matrix.AddParameter( C_Comment );
	C_Matrix.Write( rC_file );
	
	for( EE_BYTE_t b_Row( 0 ); b_Row < 4; b_Row++ )
	{
		aC_Rows[ b_Row ].Write( rC_file );
		
		aC_Rows[ b_Row ].SetClosingTagFlag( 1 );
		aC_Rows[ b_Row ].Write( rC_file );	
	}
	
	
	C_Matrix.SetClosingTagFlag( 1 );
	C_Matrix.Write( rC_file );
	
}

