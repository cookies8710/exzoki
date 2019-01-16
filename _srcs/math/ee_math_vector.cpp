#include <exzoki/math/ee_math_vector.h>

EE_MATH_VECTOR_C::EE_MATH_VECTOR_C( void ): mt_X( EE_MATH_TYPE_ZERO ),
                                            mt_Y( EE_MATH_TYPE_ZERO ),
                                            mt_Z( EE_MATH_TYPE_ZERO )
{
}

EE_MATH_VECTOR_C::EE_MATH_VECTOR_C( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z ): mt_X( t_x ), mt_Y( t_y ), mt_Z( t_z )
{   
    /*mt_X = //trunc(t_x*1000.0)*0.001;    
    mt_Y = //trunc(t_y*1000.0)*0.001;    
    mt_Z = //trunc(t_z*1000.0)*0.001;    */
}

EE_MATH_VECTOR_C EE_MATH_VECTOR_C::operator+( const EE_MATH_VECTOR_C& crC_vector ) const
{
 	return( EE_MATH_VECTOR_C( this->mt_X + crC_vector.mt_X,
                              this->mt_Y + crC_vector.mt_Y,
                              this->mt_Z + crC_vector.mt_Z ) );
}

EE_MATH_VECTOR_C EE_MATH_VECTOR_C::operator-( void ) const
{
	return( EE_MATH_VECTOR_C( -mt_X, -mt_Y, -mt_Z ) );	
}

EE_MATH_VECTOR_C EE_MATH_VECTOR_C::operator-( const EE_MATH_VECTOR_C& crC_vector ) const
{
 	return( EE_MATH_VECTOR_C( this->mt_X - crC_vector.mt_X,
                              this->mt_Y - crC_vector.mt_Y,
                              this->mt_Z - crC_vector.mt_Z ) );
}

EE_MATH_VECTOR_C EE_MATH_VECTOR_C::operator*( EE_MATH_TYPE_t t_number ) const
{
 	return( EE_MATH_VECTOR_C( mt_X * t_number, 
                              mt_Y * t_number, 
                              mt_Z * t_number ) );
}

EE_MATH_VECTOR_C EE_MATH_VECTOR_C::operator/( EE_MATH_TYPE_t t_number ) const
{
    return( EE_MATH_VECTOR_C( mt_X / t_number, 
                              mt_Y / t_number, 
                              mt_Z / t_number ) );    
}

EE_MATH_TYPE_t EE_MATH_VECTOR_C::operator*( const EE_MATH_VECTOR_C& crC_vector ) const
{
 	return( mt_X * crC_vector.mt_X +
            mt_Y * crC_vector.mt_Y +
            mt_Z * crC_vector.mt_Z );
}

EE_MATH_VECTOR_C EE_MATH_VECTOR_C::operator%( const EE_MATH_VECTOR_C& crC_vector ) const
{
 	return( EE_MATH_VECTOR_C( mt_Y * crC_vector.mt_Z - mt_Z * crC_vector.mt_Y,
                             mt_Z * crC_vector.mt_X - mt_X * crC_vector.mt_Z,
                             mt_X * crC_vector.mt_Y - mt_Y * crC_vector.mt_X ) );
}

EE_BOOL_t EE_MATH_VECTOR_C::operator==( const EE_MATH_VECTOR_C& crC_vector ) const
{
	return( EE_MATH_VECTOR_C( crC_vector - *this ).LengthPow2() < EE_MATH_TYPE_PRECISION );
	
	/*float f_XDif( fabs( this->mt_X - crC_vector.mt_X ) ); 
 	float f_YDif( fabs( this->mt_Y - crC_vector.mt_Y ) ); 
 	float f_ZDif( fabs( this->mt_Z - crC_vector.mt_Z ) ); 
	float f_Dif( f_XDif + f_YDif + f_ZDif );
 	return( f_Dif < EE_MATH_TYPE_PRECISION );  */
	
	/*
 	EE_MATH_TYPE_t f_XDifPow2( this->mt_X - crC_vector.mt_X ); f_XDifPow2 *= f_XDifPow2;
 	EE_MATH_TYPE_t f_YDifPow2( this->mt_Y - crC_vector.mt_Y ); f_YDifPow2 *= f_YDifPow2;
 	EE_MATH_TYPE_t f_ZDifPow2( this->mt_Z - crC_vector.mt_Z ); f_ZDifPow2 *= f_ZDifPow2;
	EE_MATH_TYPE_t f_DifPow2( f_XDifPow2 + f_YDifPow2 + f_ZDifPow2 );
 	return( f_DifPow2 < EE_MATH_TYPE_PRECISION * EE_MATH_TYPE_PRECISION );  */
}

EE_BOOL_t EE_MATH_VECTOR_C::operator!=( const EE_MATH_VECTOR_C& crC_vector ) const
{
	return( !( *this == crC_vector ) );	
}

void EE_MATH_VECTOR_C::Normal( const EE_MATH_VECTOR_C& crC_pointA, 
                               const EE_MATH_VECTOR_C& crC_pointB, 
                               const EE_MATH_VECTOR_C& crC_pointC )
{
 	*this = ( crC_pointB - crC_pointA ) % ( crC_pointC - crC_pointA );
 	return;
}

void EE_MATH_VECTOR_C::Normalize( void )
{
 	EE_MATH_TYPE_t t_Length = this->Length();
 
 	if( t_Length )
 	{
  		mt_X /= t_Length;
  		mt_Y /= t_Length;
  		mt_Z /= t_Length;
 	} 
                                                        
 	return;
}

void EE_MATH_VECTOR_C::SetLength( EE_MATH_TYPE_t t_length )
{
    if( t_length < 0.0 )
        EE_ERROR_C( "EE_MATH_VECTOR_C", "SetLength", EE_ERROR_CODES_n::cS_WrongNumber, "Desired length = %.2g", t_length );
        
    EE_MATH_TYPE_t t_CurrentLength = this->Length();
 
 	if( t_CurrentLength )
 	{
        EE_MATH_TYPE_t t_Multiplier( t_length / t_CurrentLength );
        
  		mt_X *= t_Multiplier;
  		mt_Y *= t_Multiplier;
  		mt_Z *= t_Multiplier;
 	} 
    
    return;    
}

void EE_MATH_VECTOR_C::Set( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z )
{
 	mt_X = t_x;
 	mt_Y = t_y;
 	mt_Z = t_z;
 /*    mt_X = trunc(t_x*1000.0)*0.001;    
    mt_Y = trunc(t_y*1000.0)*0.001;    
    mt_Z = trunc(t_z*1000.0)*0.001;      */
}

bool EE_MATH_VECTOR_C::IsMultiple( const EE_MATH_VECTOR_C &crC_vector ) const
{
 	return( ( *this % crC_vector ).IsNull() );    
}

bool EE_MATH_VECTOR_C::IsNull( void ) const
{
 	return( ( fabs( mt_X ) + fabs( mt_Y ) + fabs( mt_Z ) ) < EE_MATH_TYPE_PRECISION );
}

inline EE_MATH_TYPE_t EE_MATH_VECTOR_C::Pow2( void ) const
{
    return( *this * *this );    
}

inline EE_MATH_TYPE_t EE_MATH_VECTOR_C::GetX( void ) const
{
 	return( this->mt_X );
}
     
inline EE_MATH_TYPE_t EE_MATH_VECTOR_C::GetY( void ) const
{
 	return( this->mt_Y );
}

inline EE_MATH_TYPE_t EE_MATH_VECTOR_C::GetZ( void ) const
{
 	return( this->mt_Z );
}

EE_MATH_TYPE_t EE_MATH_VECTOR_C::Length( void ) const
{
 	return( sqrt( LengthPow2() ) );
}

EE_MATH_TYPE_t EE_MATH_VECTOR_C::LengthPow2( void ) const
{
 	return( this->mt_X * this->mt_X +
           this->mt_Y * this->mt_Y +
           this->mt_Z * this->mt_Z );   
}

EE_MATH_TYPE_t EE_MATH_VECTOR_C::GetAngle( const EE_MATH_VECTOR_C& crC_vector )
{
        
}

EE_BYTE_t EE_MATH_VECTOR_C::Read( std::ifstream &rC_file )
{
	EE_FLOAT_t f_X, f_Y, f_Z;
			
	rC_file.read( (char*)&f_X, sizeof( f_X ) );
	rC_file.read( (char*)&f_Y, sizeof( f_Y ) );
	rC_file.read( (char*)&f_Z, sizeof( f_Z ) );
			
	mt_X = f_X;
	mt_Y = f_Y;
	mt_Z = f_Z;
			
	return( 1 );					
}

EE_BYTE_t EE_MATH_VECTOR_C::Write( std::ofstream &rC_file ) const
{				
	EE_FLOAT_t f_X( mt_X ), f_Y( mt_Y ), f_Z( mt_Z );
			
	rC_file.write( (char*)&f_X, sizeof( f_X ) );
	rC_file.write( (char*)&f_Y, sizeof( f_Y ) );
	rC_file.write( (char*)&f_Z, sizeof( f_Z ) );
			
	return( 1 );
}
		
EE_BYTE_t EE_MATH_VECTOR_C::Dump( std::ofstream &rC_file ) const
{
	EE_XMLLOADER_ATTRIBUTE_C C_X( "X", (EE_FLOAT_t)mt_X ), 
			                 C_Y( "Y", (EE_FLOAT_t)mt_Y ), 
							 C_Z( "Z", (EE_FLOAT_t)mt_Z ),
							 C_Length( "Length", (EE_FLOAT_t)this->Length() ),
							 C_Comment( "Comment", (EE_CCSTRING_t)mS_Comment.c_str() );
	EE_XMLLOADER_TAG_C C_Tag( "EE_MATH_VECTOR_C" );
	C_Tag.AddParameter( C_X );
	C_Tag.AddParameter( C_Y );
	C_Tag.AddParameter( C_Z );			
	C_Tag.AddParameter( C_Length );
	if( mS_Comment.size() )
		C_Tag.AddParameter( C_Comment );
	C_Tag.SetSingleTagFlag( 1 );
			
	C_Tag.Write( rC_file );
	
	return( 1 );
}
