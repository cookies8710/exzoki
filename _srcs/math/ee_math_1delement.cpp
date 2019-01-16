#include <exzoki/math/EE_math_1delement.h>

EE_MATH_1DELEMENT_C::EE_MATH_1DELEMENT_C( void ): me_Type( EE_MATH_1DELEMENT_NOTSET ) 
{
}

/*EE_MATH_1DELEMENT_C::EE_MATH_1DELEMENT_C( const EE_MATH_POINT_C& crC_point1, 
                                          const EE_MATH_POINT_C& crC_point2 ): mC_Point1( crC_point1 ),
                                                                               mC_Point2( crC_point2 ),
                                                                               me_Type( EE_MATH_1DELEMENT_NOTSET ) 
{
}*/

EE_MATH_1DELEMENT_C::EE_MATH_1DELEMENT_C( const EE_MATH_POINT_C& crC_point1, 
                                          const EE_MATH_POINT_C& crC_point2, 
                                          EE_MATH_1DELEMENT_TYPE_e e_type ): mC_Point1( crC_point1 ),
                                                                             mC_Point2( crC_point2 ),
                                                                             me_Type( e_type ) 
{
}
  
/*void EE_MATH_1DELEMENT_C::Set( const EE_MATH_POINT_C& crC_point1, const EE_MATH_POINT_C& crC_point2 )
{
 	if( crC_point1 == crC_point2 )
  		EE_ERROR_C( "EE_MATH_1DELEMENT_C", "Set", EE_ERROR_CODES_n::cS_Internal, "crC_point1 = crC_point2" );       
 	mC_Point1 = crC_point1;    
 	mC_Point2 = crC_point2;    
}*/

void EE_MATH_1DELEMENT_C::Set( const EE_MATH_POINT_C& crC_point1, const EE_MATH_POINT_C& crC_point2, EE_MATH_1DELEMENT_TYPE_e e_type )
{
 	if( crC_point1 == crC_point2 )
  		EE_ERROR_C( "EE_MATH_1DELEMENT_C", "Set", EE_ERROR_CODES_n::cS_Internal, "crC_point1 = crC_point2" );       
 	mC_Point1 = crC_point1;    
 	mC_Point2 = crC_point2;    
 	me_Type = e_type;   
}

void EE_MATH_1DELEMENT_C::SetType( EE_MATH_1DELEMENT_TYPE_e e_type )
{
 	me_Type = e_type;    
}
  
const EE_MATH_POINT_C& EE_MATH_1DELEMENT_C::GetPoint1( void ) const
{
 	return( mC_Point1 );    
}

const EE_MATH_POINT_C& EE_MATH_1DELEMENT_C::GetPoint2( void ) const
{
 	return( mC_Point2 );    
}

EE_MATH_VECTOR_C EE_MATH_1DELEMENT_C::GetVector( void ) const
{
	return( mC_Point2 - mC_Point1 );	
}

EE_MATH_1DELEMENT_TYPE_e EE_MATH_1DELEMENT_C::GetType( void ) const
{
 return( me_Type );    
}

EE_MATH_POINT_C EE_MATH_1DELEMENT_C::ClosestPoint( const EE_MATH_POINT_C &crC_point ) const
{
   EE_MATH_VECTOR_C c = crC_point - mC_Point1;
   EE_MATH_VECTOR_C V( mC_Point2 - mC_Point1 );
   double d = V.Length();
   V.Normalize();
   double t = V * c;

   // Check to see if ‘t’ is beyond the extents of the line segment

   if (t < 0) return mC_Point1;
   if (t > d) return mC_Point2;
 
   // Return the point between ‘a’ and ‘b’
    
    double l=V.Length();
    V=V*(t/l);   
   
   return mC_Point1 + V;

   /* EE_MATH_VECTOR_C C_LineVector( mC_Point2 - mC_Point1 );
    EE_MATH_TYPE_t t_ClosetPointParameter( ( ( crC_point - mC_Point1 ) * C_LineVector ) / 
                                           ( C_LineVector.Pow2() ) );
    switch( me_Type )
    {
        case EE_MATH_1DELEMENT_LINESEGMENT:
            if( t_ClosetPointParameter > 1.0 )
                return( mC_Point2 );  
        case EE_MATH_1DELEMENT_RAY: 
            if( t_ClosetPointParameter < 0.0 )
                return( mC_Point1 );     
        case EE_MATH_1DELEMENT_LINE:
            EE_DEBUG_RTDS_C::GetRTDS( "collisiondebugger" ).UpdateInfo
                ("neco","closest*vector=%.2g",
                (mC_Point1 + C_LineVector * t_ClosetPointParameter)*C_LineVector);
                
            return( mC_Point1 + C_LineVector * t_ClosetPointParameter );
        default:
            EE_ERROR_C();      
        
    }  */
}
