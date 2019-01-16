#include <exzoki/math/ee_math_quaternion.h>

EE_MATH_QUATERNION_C::EE_MATH_QUATERNION_C( void ): mt_W( 0.0 )
{
}		
	
EE_MATH_QUATERNION_C EE_MATH_QUATERNION_C::operator+( const EE_MATH_QUATERNION_C& crC_quaternion ) const
{
	EE_MATH_QUATERNION_C C_Result;
	
	C_Result.mt_W = this->mt_W + crC_quaternion.mt_W;
	C_Result.mC_Vector = this->mC_Vector + crC_quaternion.mC_Vector;
	
	return( C_Result );
}
  	
EE_MATH_QUATERNION_C EE_MATH_QUATERNION_C::operator-( const EE_MATH_QUATERNION_C& crC_quaternion ) const
{
	EE_MATH_QUATERNION_C C_Result;
	
	C_Result.mt_W = this->mt_W - crC_quaternion.mt_W;
	C_Result.mC_Vector = this->mC_Vector - crC_quaternion.mC_Vector;
	
	return( C_Result );
}

EE_MATH_QUATERNION_C EE_MATH_QUATERNION_C::operator*( const EE_MATH_QUATERNION_C& crC_quaternion ) const
{
	EE_MATH_QUATERNION_C C_Result;
	
	EE_MATH_TYPE_t t_W( this->mt_W ), t_X( this->mC_Vector.GetX() ), t_Y( this->mC_Vector.GetY() ), t_Z( this->mC_Vector.GetZ() ), 
	               t_A( crC_quaternion.mt_W ), t_B( crC_quaternion.mC_Vector.GetX() ), t_C( crC_quaternion.mC_Vector.GetY() ), t_D( crC_quaternion.mC_Vector.GetZ() );
	
	C_Result.mt_W = this->mt_W * crC_quaternion.mt_W - this->mC_Vector * crC_quaternion.mC_Vector;
	C_Result.mC_Vector = crC_quaternion.mC_Vector * this->mt_W  +
	                     this->mC_Vector * crC_quaternion.mt_W +
	                     this->mC_Vector % crC_quaternion.mC_Vector;
	
	/*.Set( t_W * t_B + t_X * t_A + t_Y * t_D - t_Z * t_C,
	                        t_W * t_C - t_X * t_D + t_Y * t_A - t_Z * t_B,
							t_W * t_D + t_X * t_C - t_Y * t_B + t_Z * t_A ); */
	
	return( C_Result );
}
/*
EE_MATH_QUATERNION_C EE_MATH_QUATERNION_C::operator/( const EE_MATH_QUATERNION_C& crC_quaternion ) const
{
	
}
*/
EE_MATH_QUATERNION_C EE_MATH_QUATERNION_C::operator/( EE_MATH_TYPE_t t_number ) const
{
	EE_MATH_QUATERNION_C C_Result;
	
	if( t_number != 0.0 )
	{
		C_Result.mt_W = this->mt_W / t_number;
		C_Result.mC_Vector = this->mC_Vector / t_number;
		
		return( C_Result );
	}		
	else
		EE_ERROR_C( "EE_MATH_QUATERNION_C", "operator/", EE_ERROR_CODES_n::cS_DivisionByZero );
}


void EE_MATH_QUATERNION_C::LoadMulIdentity( void )
{
	mt_W = 1.0;
	mC_Vector.Set( 0.0, 0.0, 0.0 );
	
	return;	
}

void EE_MATH_QUATERNION_C::LoadAddIdentity( void )
{
	mt_W = 0.0;
	mC_Vector.Set( 0.0, 0.0, 0.0 );
	
	return;	
}

EE_MATH_TYPE_t EE_MATH_QUATERNION_C::GetMagnitude( void ) const
{
	return( mt_W * mt_W + mC_Vector * mC_Vector );
}
  		
void EE_MATH_QUATERNION_C::Normalize( void )
{
	*this = *this / GetMagnitude();
	
	return;
}

void EE_MATH_QUATERNION_C::Conjugate( void )
{
	mC_Vector = -mC_Vector;
}
/*
void EE_MATH_QUATERNION_C::Inverse( void )
{
	
}*/
		
EE_MATH_MATRIX4X4_C EE_MATH_QUATERNION_C::ConvertToMatrix( void ) const
{
	EE_MATH_MATRIX4X4_C C_Matrix;
	EE_MATH_TYPE_t t_X( mC_Vector.GetX() ),
	               t_Y( mC_Vector.GetY() ),
	               t_Z( mC_Vector.GetZ() );
	
	C_Matrix.Set( 0, 0, mt_W * mt_W + t_X * t_X - t_Y * t_Y - t_Z * t_Z );	
	C_Matrix.Set( 0, 1, 2.0 * t_X * t_Y - 2.0 * mt_W * t_Z );
	C_Matrix.Set( 0, 2, 2.0 * t_X * t_Z + 2.0 * mt_W * t_Y );
	
	C_Matrix.Set( 1, 0, 2.0 * t_X * t_Y + 2.0 * mt_W * t_Z );	
	C_Matrix.Set( 1, 1, mt_W * mt_W - t_X * t_X + t_Y * t_Y - t_Z * t_Z );
	C_Matrix.Set( 1, 2, 2.0 * t_Y * t_Z - 2.0 * mt_W * t_X );
	
	C_Matrix.Set( 2, 0, 2.0 * t_X * t_Z - 2.0 * mt_W * t_Y );	
	C_Matrix.Set( 2, 1, 2.0 * t_Y * t_Z + 2.0 * mt_W * t_X );
	C_Matrix.Set( 2, 2, mt_W * mt_W - t_X * t_X - t_Y * t_Y + t_Z * t_Z );
	
	return( C_Matrix );
}
	
void EE_MATH_QUATERNION_C::Read( EE_SYSTEM_FILE_C& rC_file )
{
	EE_FLOAT_t f_W, f_X, f_Y, f_Z;
	
	rC_file.Read( &f_W, sizeof( f_W ) );
	rC_file.Read( &f_X, sizeof( f_X ) );
	rC_file.Read( &f_Y, sizeof( f_Y ) );
	rC_file.Read( &f_Z, sizeof( f_Z ) );
	
	mt_W = f_W;
	mC_Vector.Set( f_X, f_Y, f_Z );	
	
	return;
}
		
EE_BYTE_t EE_MATH_QUATERNION_C::Read( std::ifstream &rC_file )
{
	EE_FLOAT_t f_W, f_X, f_Y, f_Z;
	EE_BYTE_t b_NOfBytes( 0 );	
			
	rC_file.read( (char*)&f_W, sizeof( f_W ) );
	rC_file.read( (char*)&f_X, sizeof( f_X ) );
	rC_file.read( (char*)&f_Y, sizeof( f_Y ) );
	rC_file.read( (char*)&f_Z, sizeof( f_Z ) );
	
	mt_W = f_W;
	mC_Vector.Set( f_X, f_Y, f_Z );	
	
	return( b_NOfBytes );
}

EE_BYTE_t EE_MATH_QUATERNION_C::Write( std::ofstream &rC_file ) const
{
	EE_FLOAT_t f_W( mt_W ), 
	           f_X( mC_Vector.GetX() ), f_Y( mC_Vector.GetY() ), f_Z( mC_Vector.GetZ() );
	EE_BYTE_t b_NOfBytes( 0 );	
	
	rC_file.write( (char*)&f_W, sizeof( f_W ) );
	rC_file.write( (char*)&f_X, sizeof( f_X ) );
	rC_file.write( (char*)&f_Y, sizeof( f_Y ) );
	rC_file.write( (char*)&f_Z, sizeof( f_Z ) );	
	
	return( b_NOfBytes );
}

EE_BYTE_t EE_MATH_QUATERNION_C::Dump( std::ofstream &rC_file ) const
{
	EE_XMLLOADER_TAG_C C_Quaternion( "EE_MATH_QUATERNION_C" );
	EE_XMLLOADER_ATTRIBUTE_C C_W( "W", (EE_FLOAT_t)mt_W ),
	                         C_X( "X", (EE_FLOAT_t)mC_Vector.GetX() ),
	                         C_Y( "Y", (EE_FLOAT_t)mC_Vector.GetY() ),
	                         C_Z( "Z", (EE_FLOAT_t)mC_Vector.GetZ() ),
							 C_Comment( "Comment", (EE_CCSTRING_t)mS_Comment.c_str() );	
	
	C_Quaternion.AddParameter( C_W );
	C_Quaternion.AddParameter( C_X );	
	C_Quaternion.AddParameter( C_Y );	
	C_Quaternion.AddParameter( C_Z );		
		
	if( mS_Comment.size() )
		C_Quaternion.AddParameter( C_Comment );	
							 
	C_Quaternion.SetSingleTagFlag( 1 );
	C_Quaternion.Write( rC_file );
}
