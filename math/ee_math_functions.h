#ifndef EE_MATH_FUNCTIONS_H
#define EE_MATH_FUNCTIONS_H

#include <math.h>/*
#include <exzoki/error/ee_error.h>*/
#include <exzoki/math/ee_math_types.h>

namespace EE_EXZOKI_n
{
	EE_MATH_TYPE_t at_SinusTable[ (EE_U32_t)( EE_MATH_SINUS_PERIOD / EE_MATH_GONIOMETRIC_PRECISION ) ];	
	EE_MATH_TYPE_t at_TangensTable[ (EE_U32_t)( EE_MATH_TANGENS_PERIOD / EE_MATH_GONIOMETRIC_PRECISION ) ];	
	
	// Vytvoøí tabulky s hodnotami fcí
	void BuildUpTables( void );		
	
	inline EE_MATH_TYPE_t SinusFast( EE_MATH_TYPE_t t_angle );
	inline EE_MATH_TYPE_t CosinusFast( EE_MATH_TYPE_t t_angle );
	
	inline EE_MATH_TYPE_t Power( EE_MATH_TYPE_t t_number, EE_U32_t u32_power );
	
	inline EE_MATH_POINT_C CubicBeziereCurve( EE_MATH_TYPE_t t_parameter, 
	                                          const EE_MATH_POINT_C& crC_p0,
											  const EE_MATH_POINT_C& crC_p1,
											  const EE_MATH_POINT_C& crC_p2,
											  const EE_MATH_POINT_C& crC_p3 );
	
	// Faktoriál z urèitého èísla
	inline EE_U64_t Factorial( EE_U32_t u32_number );
	
	// Binomický koeficient (poèet k-èlenných kombinací n objektù)
	inline EE_U32_t BinomialCoefficient( EE_U32_t u32_n, EE_U32_t u32_k );
	
	// Fce pro øešení kvadratické rovnice v R - vrací poèet koøenù
	inline EE_BYTE_t QuadraticEquation( EE_MATH_TYPE_t t_a, 
                                        EE_MATH_TYPE_t t_b, 
                                        EE_MATH_TYPE_t t_c,
                                        EE_MATH_TYPE_t &rt_x1,
                                        EE_MATH_TYPE_t &rt_x2 );
};

#endif
