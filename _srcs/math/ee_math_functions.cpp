#include <exzoki/math/ee_math_functions.h>

void EE_EXZOKI_n::BuildUpTables( void )
{
	// Sinus
	
	// Poèet hodnot, které budu ukládat
	EE_U32_t u32_NValues( (EE_U32_t)( EE_MATH_SINUS_PERIOD / EE_MATH_GONIOMETRIC_PRECISION ) );
	// Uložím hodnoty
	for( EE_U32_t u32_SinusValue( 0 ); u32_SinusValue < u32_NValues; u32_SinusValue++ )
		at_SinusTable[ u32_SinusValue ] = sin( u32_SinusValue * EE_MATH_GONIOMETRIC_PRECISION * EE_MATH_DEGTORAD );
}

inline EE_MATH_TYPE_t EE_EXZOKI_n::SinusFast( EE_MATH_TYPE_t t_angle )
{
	if( t_angle > EE_MATH_SINUS_PERIOD )
		t_angle -= ( (EE_U32_t)( t_angle /  EE_MATH_SINUS_PERIOD ) ) * EE_MATH_SINUS_PERIOD;
	else if( t_angle < 0.0f )
		t_angle += ( (EE_U32_t)( -t_angle /  EE_MATH_SINUS_PERIOD ) + 1 ) * EE_MATH_SINUS_PERIOD;
		
	return( at_SinusTable[ (EE_U32_t)( t_angle / EE_MATH_GONIOMETRIC_PRECISION ) ] );
}

inline EE_MATH_TYPE_t EE_EXZOKI_n::CosinusFast( EE_MATH_TYPE_t t_angle )
{
	return( SinusFast( t_angle + 90.0f ) );
}

inline EE_MATH_TYPE_t EE_EXZOKI_n::Power( EE_MATH_TYPE_t t_number, EE_U32_t u32_power )
{
	EE_MATH_TYPE_t t_Power( t_number );
	
	if( u32_power == 0 )
		return( 1.0 );
	else
		for( EE_U32_t u32_N( 1 ); u32_N < u32_power; u32_N++ )
			t_Power *= t_number;
	
	return( t_Power );
}

inline EE_MATH_POINT_C EE_EXZOKI_n::CubicBeziereCurve( EE_MATH_TYPE_t t_parameter, 
	                                          		   const EE_MATH_POINT_C& crC_p0,
											  		   const EE_MATH_POINT_C& crC_p1,
											  	   	   const EE_MATH_POINT_C& crC_p2,
											  		   const EE_MATH_POINT_C& crC_p3 )
{
	if( t_parameter < 0.0 || t_parameter > 1.0 )
		EE_ERROR_C( "EE_EXZOKI_n", 
					"CubicBeziereCurve", 
					EE_ERROR_CODES_n::cS_WrongNumber, 
					"Parameter has to between 0.0 and 1.0. Parameter obtained: %.2g", t_parameter );
	
	
	return( crC_p0 * Power( 1.0 - t_parameter, 3 ) + 
	        crC_p1 * 3.0 * t_parameter * Power( 1.0 - t_parameter, 2 ) +
	        crC_p2 * 3.0 * Power( t_parameter, 2 ) * ( 1.0 - t_parameter ) +
	        crC_p3 * Power( t_parameter, 3 ) );	
}

inline EE_U64_t EE_EXZOKI_n::Factorial( EE_U32_t u32_number )
{
	if( u32_number > 20 )
		EE_ERROR_C( "EE_EXZOKI_n", 
					"Factorial", 
					EE_ERROR_CODES_n::cS_WrongNumber, 
					"Only factorials from range 1-20 are in range. "
					"Desired factorial from number: %d is out of 64-bit integer range", u32_number );
	
	EE_U64_t u64_Factorial( 1 );
	
	for( EE_U32_t u32_Pass( 2 ); u32_Pass <= u32_number; u32_Pass++ )
		u64_Factorial *= u32_Pass;
	
	return( u64_Factorial );
}
	
// Binomický koeficient (poèet k-èlenných kombinací n objektù)
inline EE_U32_t EE_EXZOKI_n::BinomialCoefficient( EE_U32_t u32_n, EE_U32_t u32_k )
{
	return( EE_EXZOKI_n::Factorial( u32_n ) / ( EE_EXZOKI_n::Factorial( u32_k ) * EE_EXZOKI_n::Factorial( u32_n - u32_k ) ) );
}

inline EE_BYTE_t EE_EXZOKI_n::QuadraticEquation( EE_MATH_TYPE_t t_a, 
                                                 EE_MATH_TYPE_t t_b, 
                                                 EE_MATH_TYPE_t t_c,
                                                 EE_MATH_TYPE_t &rt_x1,
                                                 EE_MATH_TYPE_t &rt_x2 )
{
    EE_MATH_TYPE_t t_D( t_b * t_b - 4 * t_a * t_c );
    if( t_D > 0.0001 )
    {
        EE_MATH_TYPE_t t_SqrtD( sqrtf( t_D ) );
        rt_x1 = ( -t_b + t_SqrtD ) / ( 2.0 * t_a );   
        rt_x2 = ( -t_b - t_SqrtD ) / ( 2.0 * t_a );   
        
        if( rt_x1 > rt_x2 )
        {
            EE_MATH_TYPE_t t_Temp( rt_x2 );
            rt_x2 = rt_x1;
            rt_x1 = t_Temp;        
        }
        
        return( 2 );     
    } 
    else if( t_D < -0.0001 )
        return( 0 );
    else
    {
        rt_x1 = ( -t_b ) / ( 2.0 * t_a );           
        return( 1 );
    }       
}

