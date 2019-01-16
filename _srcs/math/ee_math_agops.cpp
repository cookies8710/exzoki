#include <exzoki/math/ee_math_agops.h>

// INTERSECTIONS

EE_PVOID_t EE_MATH_AGOPS_n::Intersection( const EE_MATH_1DELEMENT_C& crC_1delement, 
                                          const EE_MATH_1DELEMENT_C& crC_1delement2, 
                                          EE_MATH_INTERSECTION_TYPE_e& rC_intersectionType )
{
    EE_ERROR_C( "EE_MATH_AGOPS_n", "Intersection( const EE_MATH_1DELEMENT_C&, const EE_MATH_1DELEMENT_C&, EE_MATH_INTERSECTION_TYPE_e& )",
                                EE_ERROR_CODES_n::cS_Internal,
                                "rewrite" );
	/*std::vector< EE_MATH_GEM_LINE_C > co_Lines( 3 ); 
    
    EE_MATH_POINT_C C_C( crC_1delement2.GetPoint1() - crC_1delement.GetPoint1() ); 
    
    co_Lines[ 0 ].co_Coefs.push_back( crC_1delement.GetVector().GetX() );  
    co_Lines[ 0 ].co_Coefs.push_back( -crC_1delement2.GetVector().GetX() );  
    co_Lines[ 0 ].t_Result = C_C.GetX();  
    
    
    co_Lines[ 1 ].co_Coefs.push_back( crC_1delement.GetVector().GetY() );  
    co_Lines[ 1 ].co_Coefs.push_back( -crC_1delement2.GetVector().GetY() );  
    co_Lines[ 1 ].t_Result = C_C.GetY(); 
    
    co_Lines[ 2 ].co_Coefs.push_back( crC_1delement.GetVector().GetZ() );  
    co_Lines[ 2 ].co_Coefs.push_back( -crC_1delement2.GetVector().GetZ() );  
    co_Lines[ 2 ].t_Result = C_C.GetZ();    
  
    EE_MATH_GEM_RESULT_s s_Result = EE_EXZOKI_n::GaussEliminationMethod( co_Lines );
    
    EE_MATH_POINT_C C_IntersectionA, C_IntersectionB;
   
    switch(s_Result.e_ResultType)
    {
        case EE_MATH_GEM_RESULT_TYPE_ONE_SOLUTION:
                C_DebugFile << "Gem -> 1" << endl;
                C_IntersectionA = crC_1delement.GetPoint1() + crC_1delement.GetVector() * s_Result.co_Results[ 0 ]; 
                C_IntersectionB = crC_1delement2.GetPoint1() + crC_1delement2.GetVector() * s_Result.co_Results[ 1 ];

                if( !( C_IntersectionA == C_IntersectionB ) )
                {
                    C_DebugFile<< "C_IntersectionA != C_IntersectionB: "<<endl;
                    C_IntersectionA.Dump(C_DebugFile);
                    C_IntersectionB.Dump(C_DebugFile);
                    
                    EE_ERROR_C( "EE_MATH_AGOPS_n", "Intersection( const EE_MATH_1DELEMENT_C&, const EE_MATH_1DELEMENT_C&, EE_MATH_INTERSECTION_TYPE_e& )",
                                EE_ERROR_CODES_n::cS_Internal,
                                "C_IntersectionA != C_IntersectionB" );
                }
                rC_intersectionType = EE_MATH_INTERSECTION_TYPE_POINT;
                return( (EE_PVOID_t)( new EE_MATH_POINT_C( C_IntersectionA ) ) );
                break;
        case EE_MATH_GEM_RESULT_TYPE_NO_SOLUTION:
                C_DebugFile << "Gem -> 0" << endl;
                rC_intersectionType = EE_MATH_INTERSECTION_TYPE_NOTHING;
                return( (EE_PVOID_t)( 0 ) );
                break;
        case EE_MATH_GEM_RESULT_TYPE_INFINITE_SOLUTIONS:
                rC_intersectionType = EE_MATH_INTERSECTION_TYPE_1DELEMENT;
                EE_ERROR_C( "EE_MATH_AGOPS_n", "Intersection( const EE_MATH_1DELEMENT_C&, const EE_MATH_1DELEMENT_C&, EE_MATH_INTERSECTION_TYPE_e& )",
                                EE_ERROR_CODES_n::cS_Internal, "kurwa, nedodelany kod" );
                return( 0 );
                break; 
        default:                
                break;  
    }    */           
}

EE_PVOID_t EE_MATH_AGOPS_n::Intersection( const EE_MATH_1DELEMENT_C& crC_1delement, 
                                          const EE_MATH_PLANE_C& crC_plane, 
                                          EE_MATH_INTERSECTION_TYPE_e& rC_intersectionType )
{
 	EE_MATH_TYPE_t t_S;
 	EE_MATH_INTERSECTION_TYPE_e e_IntersectionType;
 
 	// Skalární souèin vektoru 1delementu a normály roviny
 	t_S = crC_1delement.GetVector() * crC_plane.GetNormal();
 	// Pokud jsou vektory kolmé (jejich skalární souèin je nulový), 1delement je s rovinou rovnobìžný
 	if( !t_S )
 	{	
  		// Pokud jakýkoliv bod 1delementu NEleží na rovinì, celý 1delement NEleží na rovinì (protože je s ní rovnobìžný)
  		if( crC_1delement.GetPoint1() * crC_plane.GetNormal() + crC_plane.GetD() )
  		{
   		rC_intersectionType = EE_MATH_INTERSECTION_TYPE_NOTHING;
   		return( EE_NULL );   
  		}
  		// Pokud leží jakýkoliv bod 1delementu na rovinì, leží celý 1delement na rovinì (protože je s ní rovnobìžný)
  		else
  		{
   		rC_intersectionType = EE_MATH_INTERSECTION_TYPE_1DELEMENT;
   		return( new EE_MATH_1DELEMENT_C( crC_1delement ) );   
  		}
 	}
 	// Jinak je 1delement s rovinou rùznobìžný a protíná ji v 1 bodu (u polopøímky a úseèky nemusí platit)
	else
 	{
  		// Vypoèítám parametr prùseèíku
/*		EE_MATH_TYPE_t t_T( 
									( -( crC_1delement.GetPoint1() * crC_plane.GetNormal() ) - crC_plane.GetD() ) / 
									( crC_plane.GetNormal() * crC_plane.GetNormal() ) 
		                  );
*/		
		EE_MATH_TYPE_t t_T( 
									( -( crC_1delement.GetPoint1() * crC_plane.GetNormal() ) - crC_plane.GetD() ) / 
									t_S
		                  );
		EE_MATH_1DELEMENT_TYPE_e e_Type( crC_1delement.GetType() );
  		// Zkontroluju hodnotu parametru pro rùzné typy 1delementu
		switch( e_Type )   
  		{
   		case EE_MATH_1DELEMENT_LINESEGMENT:
    			if( t_T < 0.0 || t_T > 1.0 )
    			{
     				rC_intersectionType = EE_MATH_INTERSECTION_TYPE_NOTHING;
     				return( EE_NULL );    
    			}
    			else
    			{
     				rC_intersectionType = EE_MATH_INTERSECTION_TYPE_POINT;
     				return( new EE_MATH_POINT_C( crC_1delement.GetPoint1() + ( crC_1delement.GetPoint2() - crC_1delement.GetPoint1() ) * t_T ) );     
    			}
    			break;
   		case EE_MATH_1DELEMENT_RAY:
    			if( t_T < 0.0 )
    			{
     				rC_intersectionType = EE_MATH_INTERSECTION_TYPE_NOTHING;
     				return( EE_NULL );    
    			}
    			else
    			{
     				rC_intersectionType = EE_MATH_INTERSECTION_TYPE_POINT;
     				return( new EE_MATH_POINT_C( crC_1delement.GetPoint1() + ( crC_1delement.GetPoint2() - crC_1delement.GetPoint1() ) * t_T ) );     
    			}
    			break;
   		case EE_MATH_1DELEMENT_LINE:
    			rC_intersectionType = EE_MATH_INTERSECTION_TYPE_POINT;
    			return( new EE_MATH_POINT_C( crC_1delement.GetPoint1() + crC_1delement.GetVector() * t_T ) );  
    			break;      
   		default:
    			EE_ERROR_C( "EE_MATH_AGOPS_n", "Intersection( const EE_MATH_1DELEMENT_C& crC_1delement, "  
                                           "const EE_MATH_PLANE_C& crC_plane, EE_MATH_INTERSECTION_TYPE_e& rC_intersectionType )",
                  		EE_ERROR_CODES_n::cS_Internal );          
    			break;           
		}
 	}
}

EE_PVOID_t EE_MATH_AGOPS_n::Intersection( const EE_MATH_1DELEMENT_C& crC_1delement, 
                                          const EE_MATH_TRIANGLE_C& crC_triangle, 
                                          EE_MATH_INTERSECTION_TYPE_e& rC_intersectionType )
{
                                                  
}

// DISTANCES - POINT

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_POINT_C& crC_point, const EE_MATH_POINT_C& crC_point2 )
{
 	return( sqrtf( DistancePow2( crC_point, crC_point2 ) ) );   
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_POINT_C& crC_point, const EE_MATH_1DELEMENT_C& crC_1delement )
{
 	return( sqrtf( DistancePow2( crC_point, crC_1delement ) ) );   
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_POINT_C& crC_point, const EE_MATH_PLANE_C& crC_plane )
{
 	return( sqrtf( DistancePow2( crC_point, crC_plane ) ) ); 
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_POINT_C& crC_point, const EE_MATH_TRIANGLE_C& crC_triangle )
{
 	return( sqrtf( DistancePow2( crC_point, crC_triangle ) ) ); 
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_POINT_C& crC_point, const EE_MATH_SPHERE_C& crC_sphere )
{
 	return( sqrtf( DistancePow2( crC_point, crC_sphere ) ) ); 
}

// DISTANCES - 1D ELEMENTS

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_1DELEMENT_C& crC_1delement2 )
{
 	return( sqrtf( DistancePow2( crC_1delement, crC_1delement2 ) ) );       
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_PLANE_C& crC_plane )
{
 	return( sqrtf( DistancePow2( crC_1delement, crC_plane ) ) );  
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_TRIANGLE_C& crC_triangle )
{
 	return( sqrtf( DistancePow2( crC_1delement, crC_triangle ) ) );       
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_SPHERE_C& crC_sphere )
{
 	return( sqrtf( DistancePow2( crC_1delement, crC_sphere ) ) );            
}

// DISTANCES - PLANE

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_PLANE_C& crC_plane2 )
{
 	return( sqrtf( DistancePow2( crC_plane, crC_plane2 ) ) );    
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_TRIANGLE_C& crC_triangle )
{
 	return( sqrtf( DistancePow2( crC_plane, crC_triangle ) ) );    
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_SPHERE_C& crC_sphere )
{
 	return( sqrtf( DistancePow2( crC_plane, crC_sphere ) ) );    
}

// DISTANCES - TRIANGLE

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_TRIANGLE_C& crC_triangle2 )
{
 	return( sqrtf( DistancePow2( crC_triangle, crC_triangle2 ) ) );    
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_SPHERE_C& crC_sphere )
{
 	return( sqrtf( DistancePow2( crC_triangle, crC_sphere ) ) );    
}

// DISTANCES - SPHERE

EE_MATH_TYPE_t EE_MATH_AGOPS_n::Distance( const EE_MATH_SPHERE_C& crC_sphere, const EE_MATH_SPHERE_C& crC_sphere2 )
{
 	return( sqrtf( DistancePow2( crC_sphere, crC_sphere2 ) ) );    
}

// DISTANCESPOW2 - POINT


EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_POINT_C& crC_point2 )
{
 	return( EE_MATH_VECTOR_C( crC_point2 - crC_point ).LengthPow2() );   
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_1DELEMENT_C& crC_1delement )
{
 	EE_MATH_POINT_C C_Q;
 	EE_MATH_VECTOR_C C_Temp, C_LineVector( crC_1delement.GetPoint2() - crC_1delement.GetPoint1() );
 	EE_MATH_TYPE_t t_T;
 	EE_MATH_1DELEMENT_TYPE_e e_1DElementType( crC_1delement.GetType() );
 
 	t_T = ( C_LineVector * ( crC_point - crC_1delement.GetPoint1() ) ) / ( C_LineVector * C_LineVector ); 
 	// Bod Q je bod na pøímce, který je nejblíže bodu point 
	C_Q = crC_1delement.GetPoint1() + C_LineVector * t_T;
 
 	// Dále postupuju podle toho, zda se jedná o pøímku, polopøímku nebo úseèku
 	switch( e_1DElementType )
 	{
  		// Úseèka: pokud je parametr vìtší než 1, vrátím vzdálenost mezi bodem point a druhým bodem úseèky, jinak postupuju dál
  		case EE_MATH_1DELEMENT_LINESEGMENT:
   		if( t_T > 1 )
   		{
    			C_Temp = crC_point - crC_1delement.GetPoint2();
    			return( C_Temp.LengthPow2() );
   		}  
  		// Polopøímka: pokud je parametr menší než 0, vrátím vzdálenost mezi bodem "point" a prvním bodem polopøímky (resp. úseèky), jinak postupuju dál
  		case EE_MATH_1DELEMENT_RAY:
   		if( t_T < 0 )
   		{
    			C_Temp = crC_point - crC_1delement.GetPoint1();
    			return( C_Temp.LengthPow2() );
   		}
  		// Pøímka: vrátím vzdálenost bodu "point" od nejbližšího bodu "Q" na pøímce (resp. polopøímce, úseèce)   
  		case EE_MATH_1DELEMENT_LINE:        
   		C_Temp = C_Q - crC_point;
   		return( C_Temp.LengthPow2() );   
  		// 1D element není nastaven
  		default:
   		EE_ERROR_C( "EE_MATH_AGOPS_n", "DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_1DELEMENT_C& crC_1delement )",
                		EE_ERROR_CODES_n::cS_Internal );       
 	}
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_PLANE_C& crC_plane )
{
 	EE_MATH_TYPE_t t_T;
 
 	t_T = -( crC_point * crC_plane.GetNormal() + crC_plane.GetD() ) / ( crC_plane.GetNormal() * crC_plane.GetNormal() ) ;    
 	EE_MATH_VECTOR_C C_Temp( crC_plane.GetNormal() * t_T );
 	return( C_Temp.LengthPow2() );    
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_TRIANGLE_C& crC_triangle )
{
 	EE_MATH_PLANE_C C_TrianglePlane( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), crC_triangle.Get( 2 ) );   
 	EE_MATH_TYPE_t t_PointTrianglePlaneDistancePow2( DistancePow2( crC_point, C_TrianglePlane ) );
 	// Teï musím najít bod na rovinì trojúhelníku nejblíže bodu crC_point
 	EE_MATH_TYPE_t t_T( -( crC_point * C_TrianglePlane.GetNormal() + C_TrianglePlane.GetD() ) / ( C_TrianglePlane.GetNormal() * C_TrianglePlane.GetNormal() ) );
 	EE_MATH_POINT_C C_PointOnPlane( C_TrianglePlane.GetNormal() * t_T + crC_point );
 	EE_MATH_VECTOR_C C_PointToPlane( crC_point - C_PointOnPlane );
 	// Zjistím, zda tento bod náhodou neleží v trojúhelníku, pokud ano, vrátím vzdálenost crC_point, C_TrianglePlane 
 	EE_MATH_PLANE_C C_Plane1( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), crC_triangle.Get( 1 ) + C_TrianglePlane.GetNormal() ),        
                   C_Plane2( crC_triangle.Get( 1 ), crC_triangle.Get( 2 ), crC_triangle.Get( 2 ) + C_TrianglePlane.GetNormal() ),    
                   C_Plane3( crC_triangle.Get( 2 ), crC_triangle.Get( 0 ), crC_triangle.Get( 0 ) + C_TrianglePlane.GetNormal() );   
 	EE_MATH_POSITION_e ae_Position[] = { C_Plane1.PointPosition( C_PointOnPlane ) , 
                                        C_Plane2.PointPosition( C_PointOnPlane ) , 
                                        C_Plane3.PointPosition( C_PointOnPlane ) };
 	if( ae_Position[ 0 ] == ae_Position[ 1 ] && ae_Position[ 1 ] == ae_Position[ 2 ] && ae_Position[ 2 ] == EE_MATH_POSITION_BEHIND ) 
  		return( C_PointToPlane.LengthPow2() );   
 	else if( ae_Position[ 0 ] == EE_MATH_POSITION_SAME && ae_Position[ 1 ] == ae_Position[ 2 ] && ae_Position[ 2 ] == EE_MATH_POSITION_BEHIND )
  		return( C_PointToPlane.LengthPow2() );
 	else if( ae_Position[ 1 ] == EE_MATH_POSITION_SAME && ae_Position[ 0 ] == ae_Position[ 2 ] && ae_Position[ 2 ] == EE_MATH_POSITION_BEHIND )
  		return( C_PointToPlane.LengthPow2() );
 	else if( ae_Position[ 2 ] == EE_MATH_POSITION_SAME && ae_Position[ 0 ] == ae_Position[ 1 ] && ae_Position[ 1 ] == EE_MATH_POSITION_BEHIND )
  		return( C_PointToPlane.LengthPow2() );
 	else 
  		// Pokud je bod totožný s nìkterým z bodù trojúhelníku, tento test vrátí true
  		for( EE_BYTE_t b_Side( 0 ), b_NSame( 0 ); b_Side < 3; b_Side++ )
   		if( ae_Position[ b_Side ] == EE_MATH_POSITION_SAME )
    			if( ++b_NSame == 2 )
     				return( C_PointToPlane.LengthPow2() );
 
 	// Jinak zjistím vzdálenosti tohoto bodu od všech tøí stran trojúhelníku a uchovám tu nejmenší
 	EE_MATH_1DELEMENT_C aC_TriangleLineSegments[] = { EE_MATH_1DELEMENT_C( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), EE_MATH_1DELEMENT_LINESEGMENT ),
                                                	  EE_MATH_1DELEMENT_C( crC_triangle.Get( 1 ), crC_triangle.Get( 2 ), EE_MATH_1DELEMENT_LINESEGMENT ),
                                                	  EE_MATH_1DELEMENT_C( crC_triangle.Get( 2 ), crC_triangle.Get( 0 ), EE_MATH_1DELEMENT_LINESEGMENT ) };
 	EE_MATH_TYPE_t at_Lengths[] = { DistancePow2( C_PointOnPlane, aC_TriangleLineSegments[ 0 ] ),
                                   DistancePow2( C_PointOnPlane, aC_TriangleLineSegments[ 1 ] ),
                                   DistancePow2( C_PointOnPlane, aC_TriangleLineSegments[ 2 ] ) };
 	EE_MATH_TYPE_t *pt_Length( at_Lengths );
 	for( EE_BYTE_t b_Side( 0 ); b_Side < 3; b_Side++ )
		if( at_Lengths[ b_Side ] < *pt_Length )
   		pt_Length = &at_Lengths[ b_Side ];
 
 	// Vrátím t_PointTrianglePlaneDistancePow2^2 + nejmenší_vzdálenost_od_stran^2
 	return( C_PointToPlane.LengthPow2() + *pt_Length * *pt_Length );
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_SPHERE_C& crC_sphere )
{
 	return( DistancePow2( crC_point, crC_sphere.GetPosition() ) - crC_sphere.GetRadius() );  
}

// DISTANCESPOW2 - 1D ELEMENTS

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_1DELEMENT_C& crC_1delement2 )
{

 
      
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_PLANE_C& crC_plane )
{
 
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_TRIANGLE_C& crC_triangle )
{
      
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_SPHERE_C& crC_sphere )
{
 	return( DistancePow2( crC_sphere.GetPosition(), crC_1delement ) - crC_sphere.GetRadius() * crC_sphere.GetRadius() );        
}

// DISTANCESPOW2 - PLANE

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_PLANE_C& crC_plane2 )
{

}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_TRIANGLE_C& crC_triangle )
{

}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_SPHERE_C& crC_sphere )
{
 	return( DistancePow2( crC_sphere.GetPosition(), crC_plane ) - crC_sphere.GetRadius() );      
}

// DISTANCESPOW2 - TRIANGLE

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_TRIANGLE_C& crC_triangle2 )
{
 
}

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_SPHERE_C& crC_sphere )
{
 	return( DistancePow2( crC_sphere.GetPosition(), crC_triangle ) - crC_sphere.GetRadius() * crC_sphere.GetRadius() );  
}

// DISTANCESPOW2 - SPHERE

EE_MATH_TYPE_t EE_MATH_AGOPS_n::DistancePow2( const EE_MATH_SPHERE_C& crC_sphere, const EE_MATH_SPHERE_C& crC_sphere2 )
{
 	return( DistancePow2( crC_sphere.GetPosition(), crC_sphere2.GetPosition() ) - ( crC_sphere.GetRadius() + crC_sphere2.GetRadius() ) );
}

// COLLISION - POINT

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_POINT_C& crC_point2 )
{
 	return( crC_point == crC_point2 );           
}

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_1DELEMENT_C& crC_1delement )
{
 	EE_MATH_TYPE_t t_T;
 	EE_MATH_POINT_C C_Temp( crC_point - crC_1delement.GetPoint1() ), 
                   C_LineVector( crC_1delement.GetPoint2() - crC_1delement.GetPoint1() );
 	EE_MATH_1DELEMENT_TYPE_e e_1DElementType( crC_1delement.GetType() );
 
 	if( C_LineVector.GetX() )
  		t_T = C_Temp.GetX() / C_LineVector.GetX();
 	else if( C_LineVector.GetY() )
  		t_T = C_Temp.GetY() / C_LineVector.GetY();
 	else if( C_LineVector.GetZ() )
  		t_T = C_Temp.GetZ() / C_LineVector.GetZ();
 	else   
 	{
  	/*	G<<"0vec:"<<C_LineVector.GetX()<<", "<<C_LineVector.GetY()<<", "<<C_LineVector.GetZ()<<std::endl;
  		G<<"p1:"<<crC_1delement.GetPoint1().GetX()<<", "<<crC_1delement.GetPoint1().GetY()<<", "<<crC_1delement.GetPoint1().GetZ()<<std::endl;
  		G<<"p2:"<<crC_1delement.GetPoint2().GetX()<<", "<<crC_1delement.GetPoint2().GetY()<<", "<<crC_1delement.GetPoint2().GetZ()<<std::endl;
		  EE_ERROR_C( "EE_MATH_AGOPS_n", "Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_POINT_C& crC_point2 )",
                	EE_ERROR_CODES_n::cS_Internal,
   	           	"Line vector is null" );     
		*/
	}
  
 	switch( e_1DElementType )
 	{
  		case EE_MATH_1DELEMENT_LINESEGMENT:
   		if( t_T > 1 )
    			return( false );       
  		case EE_MATH_1DELEMENT_RAY:
   		if( t_T < 0 )
    			return( false );
  		case EE_MATH_1DELEMENT_LINE:
   		return( ( C_LineVector * t_T + crC_1delement.GetPoint1() ) == crC_point );
   		break; 
  		default:
   		EE_ERROR_C( "EE_MATH_AGOPS_n", "Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_POINT_C& crC_point2 )",
                		EE_ERROR_CODES_n::cS_Internal );                 
 	}
}

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_PLANE_C& crC_plane )
{
 	return( crC_plane.PointPosition( crC_point ) == EE_MATH_POSITION_SAME );           
}

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_TRIANGLE_C& crC_triangle )
{
 	EE_MATH_PLANE_C C_TrianglePlane( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), crC_triangle.Get( 2 ) );  
 	if( C_TrianglePlane.PointPosition( crC_point ) != EE_MATH_POSITION_SAME )
  		return( false );
 
 	EE_MATH_PLANE_C C_Plane1( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), crC_triangle.Get( 1 ) + C_TrianglePlane.GetNormal() ),        
                   C_Plane2( crC_triangle.Get( 1 ), crC_triangle.Get( 2 ), crC_triangle.Get( 2 ) + C_TrianglePlane.GetNormal() ),    
                   C_Plane3( crC_triangle.Get( 2 ), crC_triangle.Get( 0 ), crC_triangle.Get( 0 ) + C_TrianglePlane.GetNormal() );   
 
 	EE_MATH_POSITION_e ae_Position[] = { C_Plane1.PointPosition( crC_point ) , 
                                        C_Plane2.PointPosition( crC_point ) , 
                                        C_Plane3.PointPosition( crC_point ) };
 
 	if( ae_Position[ 0 ] == EE_MATH_POSITION_FRONT || ae_Position[ 1 ] == EE_MATH_POSITION_FRONT || ae_Position[ 2 ] == EE_MATH_POSITION_FRONT ) 
  		return( false );   
 	else if( ae_Position[ 0 ] == ae_Position[ 1 ] && ae_Position[ 1 ] == ae_Position[ 2 ] && ae_Position[ 2 ] == EE_MATH_POSITION_BEHIND ) 
  		return( true );   
 	else if( ae_Position[ 0 ] == EE_MATH_POSITION_SAME && ae_Position[ 1 ] == ae_Position[ 2 ] && ae_Position[ 2 ] == EE_MATH_POSITION_BEHIND )
  		return( true );
 	else if( ae_Position[ 1 ] == EE_MATH_POSITION_SAME && ae_Position[ 0 ] == ae_Position[ 2 ] && ae_Position[ 2 ] == EE_MATH_POSITION_BEHIND )
  		return( true );
 	else if( ae_Position[ 2 ] == EE_MATH_POSITION_SAME && ae_Position[ 0 ] == ae_Position[ 1 ] && ae_Position[ 1 ] == EE_MATH_POSITION_BEHIND )
  		return( true );
 	else 
  		// Pokud je bod totožný s nìkterým z bodù trojúhelníku, tento test vrátí true
  		for( EE_BYTE_t b_Side( 0 ), b_NSame( 0 ); b_Side < 3; b_Side++ )
   		if( ae_Position[ b_Side ] == EE_MATH_POSITION_SAME )
    			if( ++b_NSame == 2 )
     				return( true );
 
 	EE_ERROR_C( "EE_MATH_AGOPS_n", "Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_TRIANGLE_C& crC_triangle )",
               EE_ERROR_CODES_n::cS_Internal );   
}

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_SPHERE_C& crC_sphere )
{
 	EE_MATH_POINT_C C_Distance( crC_sphere.GetPosition() - crC_point );
 	return( C_Distance.LengthPow2() <= crC_sphere.GetRadiusPow2() );           
}

// COLLISION - 1D ELEMENTS

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_1DELEMENT_C& crC_1delement2 )
{
 	EE_MATH_POINT_C C_A( crC_1delement.GetPoint1() ), C_B( crC_1delement2.GetPoint1() ), C_C( C_A - C_B );
 	EE_MATH_VECTOR_C C_U( crC_1delement.GetPoint2() - crC_1delement.GetPoint1() ), C_V( crC_1delement2.GetPoint2() - crC_1delement2.GetPoint1() );
 	EE_MATH_TYPE_t t_T, t_S, t_Temp;
 
 	if( t_Temp = C_U.GetX() * C_V.GetY() - C_V.GetX() * C_U.GetY() )
  		t_T = ( C_C.GetY() * C_V.GetX() - C_C.GetX() * C_V.GetY() ) / t_Temp;
 	else if( t_Temp = C_U.GetX() * C_V.GetZ() - C_V.GetX() * C_U.GetZ() )
  		t_T = ( C_C.GetZ() * C_V.GetX() - C_C.GetX() * C_V.GetZ() ) / t_Temp;
 	else if( t_Temp = C_U.GetY() * C_V.GetZ() - C_V.GetY() * C_U.GetZ() )
  		t_T = ( C_C.GetZ() * C_V.GetY() - C_C.GetY() * C_V.GetZ() ) / t_Temp;
 	else
  		EE_ERROR_C( "EE_MATH_AGOPS_n", "Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_1DELEMENT_C& crC_1delement2 )",
               EE_ERROR_CODES_n::cS_Internal );       
 	if( C_V.GetX() )
  		t_S = ( C_C.GetX() + t_T * C_U.GetX() ) / C_V.GetX();
 	else if( C_V.GetY() )
  		t_S = ( C_C.GetY() + t_T * C_U.GetY() ) / C_V.GetY();
 	else if( C_V.GetZ() )
  		t_S = ( C_C.GetZ() + t_T * C_U.GetZ() ) / C_V.GetZ(); 
  
 	EE_MATH_1DELEMENT_TYPE_e e_1DElement1( crC_1delement.GetType() ), e_1DElement2( crC_1delement2.GetType() );
 	switch( e_1DElement1 )     
 	{
  		case EE_MATH_1DELEMENT_LINESEGMENT:
   		if( t_T > 1 )
    			return( false ); 
  		case EE_MATH_1DELEMENT_RAY:
   		if( t_T < 0 )
    			return( false );             
 	}
 	
	switch( e_1DElement2 )     
 	{
  		case EE_MATH_1DELEMENT_LINESEGMENT:
   		if( t_S > 1 )
    			return( false ); 
  		case EE_MATH_1DELEMENT_RAY:
   		if( t_S < 0 )
    			return( false );             
 	}
 
 	return( ( C_A + C_U * t_T ) == ( C_B + C_V * t_S ) );
}

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_PLANE_C& crC_plane )
{
 	EE_MATH_TYPE_t t_S;
 
 	t_S = ( crC_1delement.GetPoint2() - crC_1delement.GetPoint1() ) * crC_plane.GetNormal();
 	if( !t_S )
  		return( !( crC_1delement.GetPoint1() * crC_plane.GetNormal() + crC_plane.GetD() ) );
 	else if( crC_1delement.GetType() == EE_MATH_1DELEMENT_LINE )
  		return( true );
 	else
 	{
  		EE_MATH_TYPE_t t_T;
  		t_T = -( ( crC_plane.GetD() + crC_1delement.GetPoint1() * crC_plane.GetNormal() ) / t_S );
  		switch( crC_1delement.GetType() )   
  		{
   		case EE_MATH_1DELEMENT_RAY:
    			return( t_T >= 0 );
    			break;      
   		case EE_MATH_1DELEMENT_LINESEGMENT:
    			return( t_T >= 0.0 && t_T <= 1.0 );
    			break;   
   		default:
    			EE_ERROR_C( "EE_MATH_AGOPS_n", "Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_PLANE_C& crC_plane )",
                  		EE_ERROR_CODES_n::cS_Internal );          
    			break;           
  		}
 	} 
}

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_TRIANGLE_C& crC_triangle )
{
 	EE_MATH_PLANE_C C_TrianglePlane( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), crC_triangle.Get( 2 ) );
 	EE_MATH_TYPE_t t_S;
 
 	t_S = ( crC_1delement.GetPoint2() - crC_1delement.GetPoint1() ) * C_TrianglePlane.GetNormal();
 	// 1D útvar je rovnobìžný s rovinou -> buï leží na rovinì, nebo ne 
 	if( !t_S )
 	{
  		// Bod 1D útvaru neleží na rovinì -> 1D útvar nemá s rovinou žádný prùnik 
  		if( crC_1delement.GetPoint1() * C_TrianglePlane.GetNormal() + C_TrianglePlane.GetD() )
   		return( false );
  		// 1D útvar leží na rovinì
  		EE_MATH_1DELEMENT_C C_Side1( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), EE_MATH_1DELEMENT_LINESEGMENT ),
                          C_Side2( crC_triangle.Get( 1 ), crC_triangle.Get( 2 ), EE_MATH_1DELEMENT_LINESEGMENT ),
                          C_Side3( crC_triangle.Get( 2 ), crC_triangle.Get( 0 ), EE_MATH_1DELEMENT_LINESEGMENT );
  		// Zkontroluju, zda 1D útvar koliduje s nìkterou stranou, pokud ano, koliduje s trojúhelníkem
  		if( Collision( crC_1delement, C_Side1 ) || Collision( crC_1delement, C_Side2 ) || Collision( crC_1delement, C_Side3 ) )
   		return( true );
  		// Jinak, ale pouze pokud se jedná o úseèku, mùže ležet uvnitø trojúhelníku (polopøímka a pøímka jsou útvary nekoneèné, nemùžou tedy ležet v koneèné ploše trojúhelníku)
  		if( crC_1delement.GetType() == EE_MATH_1DELEMENT_LINESEGMENT )
   		if( Collision( crC_1delement.GetPoint1(), crC_triangle ) && Collision( crC_1delement.GetPoint2(), crC_triangle ) )
    			return( true );
  		// Jinak kolize není
  		return( false );
 	}
 	else
 	{
  		EE_MATH_TYPE_t t_T;
  		t_T = -( ( C_TrianglePlane.GetD() + crC_1delement.GetPoint1() * C_TrianglePlane.GetNormal() ) / t_S );
  		switch( crC_1delement.GetType() )   
  		{
   		case EE_MATH_1DELEMENT_RAY:
    			if( t_T < 0 );
     				return( false );
    			break;      
   		case EE_MATH_1DELEMENT_LINESEGMENT:
    			if( t_T < 0 && t_T > 1 );
     				return( false );
    			break;   
  		}
  
  		EE_MATH_POINT_C C_PointOnPlane( crC_1delement.GetPoint1() + C_TrianglePlane.GetNormal() * t_T );
  		if(!Collision( C_PointOnPlane, C_TrianglePlane ))
   		EE_ERROR_C( "EE_MATH_AGOPS_n", "Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_TRIANGLE_C& crC_triangle )",
                		EE_ERROR_CODES_n::cS_Internal );    
  		return( Collision( C_PointOnPlane, crC_triangle ) );   
 	}
}

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_SPHERE_C& crC_sphere )
{
    EE_ERROR_C( "neni naprogramovano","EE_MATH_AGOPS_n::Collision",
                		EE_ERROR_CODES_n::cS_Internal );    
 	//return( DistancePow2( crC_1delement, crC_sphere ) <= 0 );           
}

// COLLISION - PLANE

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_PLANE_C& crC_plane2 )
{
 	if( crC_plane.GetNormal() * crC_plane2.GetNormal() )   
  		return( true );
 	else
  		return( crC_plane.GetD() == crC_plane2.GetD() ); 
}

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_TRIANGLE_C& crC_triangle )
{
 	EE_MATH_POSITION_e e_TrianglePosition( crC_plane.TrianglePosition( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), crC_triangle.Get( 2 ) ) );
 	if( e_TrianglePosition == EE_MATH_POSITION_COLLISION || e_TrianglePosition == EE_MATH_POSITION_SAME )
  		return( true );
 
 	return( false ); 
}

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_SPHERE_C& crC_sphere )
{
 	return( Distance( crC_plane, crC_sphere ) <= 0 );       
}

// COLLISION - TRIANGLE

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_TRIANGLE_C& crC_triangle2 )
{
 	EE_MATH_PLANE_C C_Triangle1Plane( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), crC_triangle.Get( 2 ) ), 
                   C_Triangle2Plane( crC_triangle2.Get( 0 ), crC_triangle2.Get( 1 ), crC_triangle2.Get( 2 ) );
 

 	if( !Collision( C_Triangle1Plane, crC_triangle2 ) || !Collision( C_Triangle2Plane, crC_triangle ) )
  		return( false );
 
 	// Trojúhelníky JSOU na jedné rovinì
 	if( C_Triangle1Plane.GetNormal().IsMultiple( C_Triangle1Plane.GetNormal() ) ) 
 	{
  		EE_MATH_1DELEMENT_C aC_T1Sides[ 3 ] = { EE_MATH_1DELEMENT_C( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), EE_MATH_1DELEMENT_LINESEGMENT ),
                                              EE_MATH_1DELEMENT_C( crC_triangle.Get( 1 ), crC_triangle.Get( 2 ), EE_MATH_1DELEMENT_LINESEGMENT ),
                                              EE_MATH_1DELEMENT_C( crC_triangle.Get( 2 ), crC_triangle.Get( 0 ), EE_MATH_1DELEMENT_LINESEGMENT ) };
  		EE_MATH_1DELEMENT_C aC_T2Sides[ 3 ] = { EE_MATH_1DELEMENT_C( crC_triangle2.Get( 0 ), crC_triangle2.Get( 1 ), EE_MATH_1DELEMENT_LINESEGMENT ),
                                              EE_MATH_1DELEMENT_C( crC_triangle2.Get( 1 ), crC_triangle2.Get( 2 ), EE_MATH_1DELEMENT_LINESEGMENT ),
                                              EE_MATH_1DELEMENT_C( crC_triangle2.Get( 2 ), crC_triangle2.Get( 0 ), EE_MATH_1DELEMENT_LINESEGMENT ) };
  		for( EE_BYTE_t b_T1Side( 0 ); b_T1Side < 3; b_T1Side++ )
   		for( EE_BYTE_t b_T2Side( 0 ); b_T2Side < 3; b_T2Side++ )
    			if( Collision( aC_T1Sides[ b_T1Side ], aC_T2Sides[ b_T2Side ] ) )
     				return( true );
  
  		if( Collision( crC_triangle.Get( 0 ), crC_triangle2 ) && Collision( crC_triangle.Get( 1 ), crC_triangle2 ) && Collision( crC_triangle.Get( 2 ), crC_triangle2 ) )   
   		return( true );
  		if( Collision( crC_triangle2.Get( 0 ), crC_triangle ) && Collision( crC_triangle2.Get( 1 ), crC_triangle ) && Collision( crC_triangle2.Get( 2 ), crC_triangle ) )   
   		return( true );
  
  		return( false ); 
 	}
 	// Trojúhelníky jsou NEJSOU jedné rovinì
 	else
 	{
  		EE_MATH_POINT_C aC_T1Points[ 3 ] = { crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), crC_triangle.Get( 2 ) },
                   	 aC_T2Points[ 3 ] = { crC_triangle2.Get( 0 ), crC_triangle2.Get( 1 ), crC_triangle2.Get( 2 ) },
                   	 ap_T1PointSideA, ap_T1Point1SideB, ap_T1Point2SideB,
                   	 ap_T2PointSideA, ap_T2Point1SideB, ap_T2Point2SideB;
  		EE_MATH_POSITION_e ae_T1PointPositions[ 3 ] = { C_Triangle2Plane.PointPosition( aC_T1Points[ 0 ] ),
                                                   	C_Triangle2Plane.PointPosition( aC_T1Points[ 1 ] ),
                                                   	C_Triangle2Plane.PointPosition( aC_T1Points[ 2 ] ) }, 
                      	 ae_T2PointPositions[ 3 ] = { C_Triangle1Plane.PointPosition( aC_T2Points[ 0 ] ),
                                                   	C_Triangle1Plane.PointPosition( aC_T2Points[ 1 ] ),
                                                   	C_Triangle1Plane.PointPosition( aC_T2Points[ 2 ] ) };
     
  		EE_MATH_TYPE_t at_PT1[ 3 ],
                  	at_PT2[ 3 ],
                  	at_DT1[ 3 ],
                  	at_DT2[ 3 ]; 
                  ////////////////////
 // enne
  
  		EE_MATH_VECTOR_C C_LineVector;
  		EE_MATH_POINT_C aC_Triangle1Projected[ 3 ], aC_Triangle2Projected[ 3 ];
  
  		C_LineVector = C_Triangle1Plane.GetNormal() % C_Triangle2Plane.GetNormal();
     
 	}     
}

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_SPHERE_C& crC_sphere )
{
    EE_MATH_PLANE_C C_TrianglePlane( crC_triangle );
    
    // Pokud je vzdálenost støedu koule od roviny trojúhelníku vìtší než její polomìr, kolize není
    if( fabs( C_TrianglePlane.GetDistance( crC_sphere.GetPosition() ) ) > crC_sphere.GetRadius() )
        return( 0 );
    else
    {
        // Pokud leží nejbližší bod roviny od stødu koule v trojúhelníku, kolize je
        EE_MATH_POINT_C C_SphereCenterOnPlane( C_TrianglePlane.ProjectPoint( crC_sphere.GetPosition() ) );
        if( EE_MATH_AGOPS_n::Collision( C_SphereCenterOnPlane, crC_triangle ) )
            return( 1 );            
    }
    
    for( EE_BYTE_t t_Edge( 0 ); t_Edge < 3; t_Edge++ )
    {       
        EE_MATH_1DELEMENT_C C_Edge( crC_triangle.GetEdge( t_Edge ) );
        EE_MATH_POINT_C C_ClosestPoint( C_Edge.ClosestPoint( crC_sphere.GetPosition() ) );
        // Pokud je vzdálenost od nìkteré strany trojúhelníku menší než polomìr, kolize je
        if( ( C_ClosestPoint - crC_sphere.GetPosition() ).LengthPow2() < crC_sphere.GetRadiusPow2() )
           return( 1 );
    }
    
    return( 0 );
}

// COLLISION - SPHERE

EE_BOOL_t EE_MATH_AGOPS_n::Collision( const EE_MATH_SPHERE_C& crC_sphere, const EE_MATH_SPHERE_C& crC_sphere2 )
{
 	return( 
        		EE_MATH_VECTOR_C( crC_sphere2.GetPosition() - crC_sphere.GetPosition() ).LengthPow2() <= 
        		( crC_sphere.GetRadius() + crC_sphere2.GetRadius() ) * ( crC_sphere.GetRadius() + crC_sphere2.GetRadius() ) 
       	);     
}

// MISC.

void EE_MATH_AGOPS_n::SplitTriangle( const EE_MATH_TRIANGLE_C &crC_triangle,
                                     const EE_MATH_PLANE_C& crC_plane,
                                     std::vector< EE_MATH_TRIANGLE_C >& rco_front,
                                     std::vector< EE_MATH_TRIANGLE_C >& rco_back )
{
    EE_MATH_INTERSECTION_TYPE_e e_IntersectionType;
    
    EE_MATH_VECTOR_C C_Normal( crC_triangle.Normal() );

    EE_MATH_POSITION_e ae_PointPositions[ 3 ];
     
    // Získám pozici bodù vùèi rovinì
    ae_PointPositions[ 0 ] = crC_plane.PointPosition( crC_triangle.Get( 0 ) );
    ae_PointPositions[ 1 ] = crC_plane.PointPosition( crC_triangle.Get( 1 ) );
    ae_PointPositions[ 2 ] = crC_plane.PointPosition( crC_triangle.Get( 2 ) );
    
    bool b_PointIndexFrontSet( false ),
         b_PointIndexBackSet( false ),
         b_PointIndexThirdSet( false );
    EE_BYTE_t b_PointIndexFront, b_PointIndexBack, b_PointIndexThird;
    EE_MATH_POSITION_e e_PointPositionThird;
    
    for( EE_BYTE_t b_Point( 0 ); b_Point < 3; b_Point++ )
        switch( ae_PointPositions[ b_Point ] )
        {
            case EE_MATH_POSITION_FRONT:
                if( !b_PointIndexFrontSet )  
                {
                    b_PointIndexFront = b_Point; 
                    b_PointIndexFrontSet = true;
                }
                else
                {
                    b_PointIndexThird = b_Point; 
                    e_PointPositionThird = EE_MATH_POSITION_FRONT;
                }    
                break;   
           case EE_MATH_POSITION_BEHIND:   
                if( !b_PointIndexBackSet )  
                {
                     b_PointIndexBack = b_Point; 
                     b_PointIndexBackSet = true;
                }
                else
                {
                    b_PointIndexThird = b_Point; 
                    e_PointPositionThird = EE_MATH_POSITION_BEHIND;
                }       
                break;        
           case EE_MATH_POSITION_SAME:
                {   
                    b_PointIndexThird = b_Point; 
                    e_PointPositionThird = EE_MATH_POSITION_SAME; 
                }    
                break;       
        }
 
     
     EE_MATH_TRIANGLE_C C_Front( crC_triangle ), C_Back( crC_triangle );
     EE_MATH_POINT_C C_NewPoint;
     EE_BYTE_t b_FrontIndex, b_BackIndex, b_ThirdIndex, b_NewIndex;
     
     // Vypoèítám pozici nového bodu
     EE_PVOID_t pv_Intersection( 
        EE_MATH_AGOPS_n::Intersection( 
            EE_MATH_1DELEMENT_C(             
                crC_triangle.Get( b_PointIndexFront ),
                crC_triangle.Get( b_PointIndexBack ),
                EE_MATH_1DELEMENT_LINE ),
            crC_plane,
            e_IntersectionType ) ); // Typ pøímka dávám, protože už je jisté, že úseèka s rovinou koliduje
     
     if( e_IntersectionType != EE_MATH_INTERSECTION_TYPE_POINT ) 
        EE_ERROR_C( "EE_MATH_AGOPS_n", "SplitTriangle", EE_ERROR_CODES_n::cS_Internal, "(assert) Intersection is not point: %", e_IntersectionType );    
           
     C_NewPoint = *(EE_MATH_POINT_C*)pv_Intersection;      

    // Musím odlišit, zda je tøetí vertex na dìlící rovinì -> pak vznikají jen 2 nové facy
    if( e_PointPositionThird == EE_MATH_POSITION_SAME )   
    {
          // Pøední face
          SetUpTriangleByNormal( C_Front, 
                                 crC_triangle.Get( b_PointIndexFront ), 
                                 C_NewPoint,
                                 crC_triangle.Get( b_PointIndexThird ),                         
                                 C_Normal );    
           
          // Zadní face
          SetUpTriangleByNormal( C_Back, 
                                 crC_triangle.Get( b_PointIndexBack ), 
                                 C_NewPoint,
                                 crC_triangle.Get( b_PointIndexThird ),                         
                                 C_Normal );      
    }  
    // Tøetí vertex není na dìlící rovinì -> vznikají 3 nové facy
    else
    {
        EE_MATH_POINT_C C_NewPoint2;
        if( e_PointPositionThird == EE_MATH_POSITION_FRONT )
        {
           EE_MATH_TRIANGLE_C C_Front2( crC_triangle );
           EE_PVOID_t pv_Intersection2( 
                EE_MATH_AGOPS_n::Intersection( 
                    EE_MATH_1DELEMENT_C( 
                        crC_triangle.Get( b_PointIndexThird ),                                       
                        crC_triangle.Get( b_PointIndexBack ),
                        EE_MATH_1DELEMENT_LINE ),
                    crC_plane,
                    e_IntersectionType ) ); // Typ pøímka dávám, protože už je jisté, že úseèka s rovinou koliduje
            
            if( e_IntersectionType != EE_MATH_INTERSECTION_TYPE_POINT ) 
                EE_ERROR_C( "EE_MATH_AGOPS_n", "SplitTriangle", EE_ERROR_CODES_n::cS_Internal, "(assert) Intersection is not point: %", e_IntersectionType );    
            
            C_NewPoint2 = *(EE_MATH_POINT_C*)pv_Intersection2;   
          
           
           // Pøední face 1
           SetUpTriangleByNormal( C_Front, 
                                  C_NewPoint,
                                  crC_triangle.Get( b_PointIndexFront ),
                                  crC_triangle.Get( b_PointIndexThird ),
                                  C_Normal );            
           // Pøední face 2
           SetUpTriangleByNormal( C_Front2, 
                                  C_NewPoint,
                                  crC_triangle.Get( b_PointIndexThird ),
                                  C_NewPoint2, 
                                  C_Normal );              
           // Zadní face
           SetUpTriangleByNormal( C_Back, 
                                  C_NewPoint,
                                  crC_triangle.Get( b_PointIndexBack ), 
                                  C_NewPoint2,
                                  C_Normal );
                                  
           rco_front.push_back( C_Front2 );
        }
      else
      {
           EE_MATH_TRIANGLE_C C_Back2( crC_triangle );
           EE_PVOID_t pv_Intersection2( 
                EE_MATH_AGOPS_n::Intersection( 
                    EE_MATH_1DELEMENT_C( 
                        crC_triangle.Get( b_PointIndexThird ),
                        crC_triangle.Get( b_PointIndexFront ),
                        EE_MATH_1DELEMENT_LINE ),
                    crC_plane,
                    e_IntersectionType ) ); // Typ pøímka dávám, protože už je jisté, že úseèka s rovinou koliduje
            
            if( e_IntersectionType != EE_MATH_INTERSECTION_TYPE_POINT ) 
                EE_ERROR_C( "EE_MATH_AGOPS_n", "SplitTriangle", EE_ERROR_CODES_n::cS_Internal, "(assert) Intersection is not point: %", e_IntersectionType );    
     
           C_NewPoint2 = *(EE_MATH_POINT_C*)pv_Intersection2;
           
           // Pøední face
           SetUpTriangleByNormal( C_Front, 
                                  crC_triangle.Get( b_PointIndexFront ),
                                  C_NewPoint,
                                  C_NewPoint2,
                                  C_Normal ); 
           
            // Zadní face 1
            SetUpTriangleByNormal( C_Back, 
                                   crC_triangle.Get( b_PointIndexThird ), 
                                   C_NewPoint,
                                   C_NewPoint2,
                                   C_Normal );              
            // Zadní face 2
            SetUpTriangleByNormal( C_Back2, 
                                   crC_triangle.Get( b_PointIndexBack ), 
                                   C_NewPoint,
                                   crC_triangle.Get( b_PointIndexThird ), 
                                   C_Normal );
           
            rco_back.push_back( C_Back2 );     
        }       
    }                     
 
    rco_front.push_back( C_Front ); 
    rco_back.push_back( C_Back );  

    return;           
}

void EE_MATH_AGOPS_n::SetUpTriangleByNormal( EE_MATH_TRIANGLE_C& rC_triangle,
                                             const EE_MATH_POINT_C &crC_point1,
                                             const EE_MATH_POINT_C &crC_point2,
                                             const EE_MATH_POINT_C &crC_point3,
                                             const EE_MATH_VECTOR_C& crC_normal )
{
    EE_MATH_VECTOR_C C_Normal;
    C_Normal.Normal( crC_point1, crC_point2, crC_point3 );   
    C_Normal.Normalize(); 
     
    if( C_Normal == crC_normal )
    {
        rC_triangle.Set( 0, crC_point1 );
        rC_triangle.Set( 1, crC_point2 );     
        rC_triangle.Set( 2, crC_point3 );          
    } 
    else
    {
        rC_triangle.Set( 0, crC_point1 );
        rC_triangle.Set( 1, crC_point3 );     
        rC_triangle.Set( 2, crC_point2 );    
    } 
    
    return;    
}        
                        
