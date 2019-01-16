#include <exzoki/collision/ee_collision_functions.h>

EE_BOOL_t EE_EXZOKI_n::CollisionSphereTriangle( const EE_COLLISION_SPHERE_C &crC_sphere, 
                                                const EE_MATH_VECTOR_C &crC_velocity, 
                                                const EE_MATH_TRIANGLE_C &crC_triangle,
                                                EE_COLLISION_INFO_s &rs_collisionInfo )
{
    EE_COLLISION_INFO_s s_PlaneCollisionInfo;    
    
    // Kolize koule s troj�heln�kem v �ase 0 nesm� b�t
    if( EE_MATH_AGOPS_n::Collision( crC_triangle, crC_sphere ) )
        EE_ERROR_C( "EE_EXZOKI_n", "CollisionSphereTriangle", EE_ERROR_CODES_n::cS_Internal, "Collision in time 0");
            
    // Rovina troj�heln�ku
    EE_MATH_PLANE_C C_TrianglePlane( crC_triangle );  
    // Vzd�lenost st�edu koule od roviny  
    EE_MATH_TYPE_t t_SphereCenterDistance( C_TrianglePlane.GetDistance( crC_sphere.GetPosition() ) );
   
    // �as kolize s rovinou
    EE_MATH_TYPE_t t_PlaneCollisionTime;
    // Bod kolize s rovinou
    EE_MATH_POINT_C C_PlaneCollisionPoint;
 
    // Pokud koule v �ase 0 nekoliduje s rovinou...    
    if( fabs( t_SphereCenterDistance ) > crC_sphere.GetRadius() )
    {      
        // Spo��t�m, kter� bod koule se roviny dotkne jako prvn�
        EE_MATH_POINT_C C_SphereCollisionPoint;        
        if( t_SphereCenterDistance > 0.0 )
            C_SphereCollisionPoint = crC_sphere.GetPosition() - C_TrianglePlane.GetNormal() * crC_sphere.GetRadius();
        else 
            C_SphereCollisionPoint = crC_sphere.GetPosition() + C_TrianglePlane.GetNormal() * crC_sphere.GetRadius();
        
        // Sestroj�m trajektorii pohybu tohoto bodu
        EE_MATH_1DELEMENT_C C_SCPMovement( C_SphereCollisionPoint,
                                           C_SphereCollisionPoint + crC_velocity,        
                                           EE_MATH_1DELEMENT_LINESEGMENT );
        EE_MATH_INTERSECTION_TYPE_e e_IntersectionType;
        EE_PVOID_t pv_Intersection;
       
        // Spo��t�m pr�nik trajektorie a roviny
        pv_Intersection = EE_MATH_AGOPS_n::Intersection( C_SCPMovement, 
                                                         C_TrianglePlane, 
                                                         e_IntersectionType );
   
        switch( e_IntersectionType )
        {
            case EE_MATH_INTERSECTION_TYPE_NOTHING: 
                // ��dn� pr�nik -> kolize nen�                
                return( 0 );
                break;
            case EE_MATH_INTERSECTION_TYPE_POINT:
                {
                    // Prvn� bod roviny, kter�ho se koule dotkne
                    C_PlaneCollisionPoint = *(EE_MATH_POINT_C*)pv_Intersection;
                    
                    delete (EE_MATH_POINT_C*)pv_Intersection;
                    
                    // Spo��t�m, za jak dlouho kolize s rovinou nastane
                    EE_MATH_TYPE_t t_Dist1( ( C_PlaneCollisionPoint - C_SphereCollisionPoint ).Length() );
                    EE_MATH_TYPE_t t_Dist0( crC_velocity.Length() );
                  
                    t_PlaneCollisionTime = t_Dist1 / t_Dist0;                              
                }
                break;
            case EE_MATH_INTERSECTION_TYPE_1DELEMENT:    
                // Tento p��pad nastat nem��e
                EE_ERROR_C( "kua","EE_EXZOKI_n::CollisionSphereTriangle",std::string("sprav to !") );
                break;
        }
        
        // Pokud je bod kolize s rovinou uvnit� troj�heln�ku, m�m kolizi
        if( EE_MATH_AGOPS_n::Collision( C_PlaneCollisionPoint, crC_triangle ) )
        {
            rs_collisionInfo.t_Time = t_PlaneCollisionTime;
            rs_collisionInfo.C_Position = C_PlaneCollisionPoint; 
            //
            s_PlaneCollisionInfo.t_Time = t_PlaneCollisionTime;
            s_PlaneCollisionInfo.C_Position = C_PlaneCollisionPoint;
            return( 1 );           
    	}
        
    }
    
    // Kolize bod� troj�heln�ku a koule -> pohybuj�c� se kouli a statick� bod p�evedu na pohybuj�c� se bod (�se�ku) a statickou kouli
    EE_COLLISION_INFO_s s_PointCollisionInfo;
    EE_BOOL_t b_PointCollision( 0 );          
    for( EE_BYTE_t b_TrianglePoint( 0 ); b_TrianglePoint < 3; b_TrianglePoint++ )
    {    
        EE_MATH_TYPE_t t_Time0, t_Time1;    	
        EE_MATH_VECTOR_C C_CenterToBase( crC_triangle.Get( b_TrianglePoint ) - crC_sphere.GetPosition() );
        EE_BYTE_t b_NRoots( QuadraticEquation( crC_velocity.Pow2(),
		                                       C_CenterToBase * crC_velocity * ( -2.0 ),
											   C_CenterToBase.Pow2() - crC_sphere.GetRadiusPow2(),
											   t_Time0, t_Time1 ) );		
		if( b_NRoots )
		{
			if( ( t_Time0 < s_PointCollisionInfo.t_Time || !b_PointCollision ) && t_Time0 >= 0.0 && t_Time0 <= 1.0  )	
			{
				b_PointCollision = 1;	
                
                s_PointCollisionInfo.t_Time = t_Time0;
                s_PointCollisionInfo.C_Position = crC_triangle.Get( b_TrianglePoint ) /*- crC_velocity * t_Time0*/;
			}
			
			if( ( b_NRoots == 2 ) && ( t_Time1 < s_PointCollisionInfo.t_Time || !b_PointCollision ) && t_Time1 >= 0.0 && t_Time1 <= 1.0  )	
			{
				b_PointCollision = 1;
				
				s_PointCollisionInfo.t_Time = t_Time1;
                s_PointCollisionInfo.C_Position = crC_triangle.Get( b_TrianglePoint ) /*- crC_velocity * t_Time1*/; 
			}
		}		
	}
		 
    // Kolize stran troj�heln�ku a koule -> pro ka�dou p��mku strany zjist�m, kdy od n� bude koule vzd�lena pr�v� 1 polom�r 
    EE_COLLISION_INFO_s s_EdgeCollisionInfo;
    EE_BOOL_t b_EdgeCollision( 0 );
	EE_MATH_1DELEMENT_C aC_Edge[ 3 ] = { crC_triangle.GetEdge( 0 ), crC_triangle.GetEdge( 1 ), crC_triangle.GetEdge( 2 ) };
    
    for( EE_BYTE_t b_TriangleEdge( 0 ); b_TriangleEdge < 3; b_TriangleEdge++ )
    {
		EE_MATH_1DELEMENT_C C_Edge( crC_triangle.GetEdge( b_TriangleEdge ) );
		EE_MATH_TYPE_t t_R( crC_sphere.GetRadius() );
		EE_MATH_POINT_C C_EdgePoint( C_Edge.GetPoint1() );
		EE_MATH_VECTOR_C C_EdgeVector( C_Edge.GetVector() ),
		                 C_EdgeToSphere( crC_sphere.GetPosition() - C_EdgePoint );
		EE_MATH_TYPE_t t_I( ( crC_velocity * C_EdgeVector ) / C_EdgeVector.Pow2() ), 
	                   t_J( C_EdgeToSphere * C_EdgeVector / C_EdgeVector.Pow2() );
		
		EE_MATH_TYPE_t t_Time0, t_Time1;
        EE_BYTE_t b_NRoots( QuadraticEquation( ( crC_velocity - C_EdgeVector * t_I ).Pow2(),
		                                       2.0 * ( crC_velocity * C_EdgeToSphere - C_EdgeVector * t_I * C_EdgeToSphere - crC_velocity * C_EdgeVector * t_J + t_I * t_J * C_EdgeVector.Pow2() ),
											   C_EdgeToSphere.Pow2() - C_EdgeVector * t_J * 2.0 * C_EdgeToSphere + t_J * t_J * C_EdgeVector.Pow2() - crC_sphere.GetRadiusPow2(),
											   t_Time0, t_Time1 ) );
			
		if( b_NRoots )
		{
			if( ( t_Time0 < s_EdgeCollisionInfo.t_Time || !b_EdgeCollision ) && t_Time0 >= 0.0 && t_Time0 <= 1.0  )	
			{  
                // Najdu bod na p��mce, kter�ho se koule dotkne
				EE_MATH_POINT_C C_SpherePositionInTime0( crC_sphere.GetPosition() + crC_velocity * t_Time0 );
				EE_MATH_TYPE_t t_S( C_EdgeVector * ( C_SpherePositionInTime0 - C_EdgePoint ) / C_EdgeVector.Pow2() );
				
				// Pokud bod le�� na use�ce strany (jeho parametr je mezi 0 a 1, kolize je platn�)
                if( t_S >= 0.0 && t_S <= 1.0 )
                {                
                    b_EdgeCollision = 1;
                    s_EdgeCollisionInfo.C_Position = C_EdgePoint + C_EdgeVector * t_S;                
				    s_EdgeCollisionInfo.t_Time = t_Time0;	
                }
			}
			
			if( ( b_NRoots == 2 ) && ( t_Time1 < s_EdgeCollisionInfo.t_Time || !b_EdgeCollision ) && t_Time1 >= 0.0 && t_Time1 <= 1.0  )	
			{
                // Najdu bod na p��mce, kter�ho se koule dotkne
				EE_MATH_POINT_C C_SpherePositionInTime1( crC_sphere.GetPosition() + crC_velocity * t_Time1 );
				EE_MATH_TYPE_t t_S( C_EdgeVector * ( C_SpherePositionInTime1 - C_EdgePoint ) / C_EdgeVector.Pow2() );
				
				// Pokud bod le�� na use�ce strany (jeho parametr je mezi 0 a 1, kolize je platn�)
                if( t_S >= 0.0 && t_S <= 1.0 )
                {                
                    b_EdgeCollision = 1;
                    s_EdgeCollisionInfo.C_Position = C_EdgePoint + C_EdgeVector * t_S;                
				    s_EdgeCollisionInfo.t_Time = t_Time1;	
                }		
			}
		}
	}
       
    if( b_PointCollision && b_EdgeCollision )
    {
		if( s_PointCollisionInfo.t_Time < s_EdgeCollisionInfo.t_Time )
			rs_collisionInfo = s_PointCollisionInfo;
		else
			rs_collisionInfo = s_EdgeCollisionInfo;
		
		return( 1 );	
	}
	else if( b_PointCollision )
	{
		rs_collisionInfo = s_PointCollisionInfo;	
		
		return( 1 );
	}
	else if( b_EdgeCollision )
	{
		rs_collisionInfo = s_EdgeCollisionInfo;	
        		
		return( 1 );
	}
	
	return( 0 );    
}

// CollisionSphere
EE_COLLISION_SPHERE_C EE_EXZOKI_n::CollisionSphere( const EE_MATH_TRIANGLE_C &crC_triangle )
{
   EE_COLLISION_SPHERE_C C_CollisionSphere;
   
   EE_MATH_VECTOR_C aC[6]={
                    EE_MATH_VECTOR_C( crC_triangle.Get( 0 ) - crC_triangle.Get( 2 ) ), 
                    EE_MATH_VECTOR_C( crC_triangle.Get( 1 ) - crC_triangle.Get( 2 ) ), 
                    EE_MATH_VECTOR_C( crC_triangle.Get( 0 ) - crC_triangle.Get( 1 ) ), 
                    EE_MATH_VECTOR_C( crC_triangle.Get( 2 ) - crC_triangle.Get( 1 ) ),
                    EE_MATH_VECTOR_C( crC_triangle.Get( 2 ) - crC_triangle.Get( 0 ) ), 
                    EE_MATH_VECTOR_C( crC_triangle.Get( 1 ) - crC_triangle.Get( 0 ) )}; 
   EE_MATH_TYPE_t t_A1((aC[0] * aC[1]) /(aC[0].Length()*aC[1].Length())), 
                  t_A2((aC[2] * aC[3]) /(aC[2].Length()*aC[3].Length())), 
                  t_A3((aC[4] * aC[5]) /(aC[4].Length()*aC[5].Length()));
   if(t_A1<=0.0 || t_A2<=0.0 || t_A3<=0.0 )
   {
        const EE_MATH_VECTOR_C *cpc_longest( &aC[0] );
        int l(0),k(0);
        for(;l<6;l++)
            if(aC[l].LengthPow2() > cpc_longest->LengthPow2())
            {
                cpc_longest=&aC[l];
                k=l;
            }
            
        switch( k )
        {
            case 0:
            case 1:
                C_CollisionSphere.SetPosition(crC_triangle.Get( 2 ) + *cpc_longest / 2.0);    
                break;   
            case 2:
            case 3:
                C_CollisionSphere.SetPosition(crC_triangle.Get( 1 ) + *cpc_longest / 2.0);    
                break;    
            case 4:
            case 5:
                C_CollisionSphere.SetPosition(crC_triangle.Get( 0 ) + *cpc_longest / 2.0);    
                break;     
        } 
        
        C_CollisionSphere.SetRadius( (*cpc_longest/2.0).Length() );   
        
         
        return( C_CollisionSphere );
   } 
   
   EE_MATH_VECTOR_C C_A( crC_triangle.Get( 0 ) - crC_triangle.Get( 2 ) ), 
                    C_B( crC_triangle.Get( 1 ) - crC_triangle.Get( 2 ) ),
                    C_ACrossB( C_A % C_B );
   EE_MATH_TYPE_t t_Denominator( 2.0 * ( C_ACrossB * C_ACrossB ) );
   
   EE_MATH_VECTOR_C C_O( 
                        ( 
                            ( C_ACrossB % C_A ) * ( C_B * C_B ) +
                            ( C_B % C_ACrossB ) * ( C_A * C_A )
                        ) 
                        / t_Denominator 
                       );
   
   C_CollisionSphere.SetRadius( sqrtf( C_O * C_O ) );
   
   C_CollisionSphere.SetPosition( C_O + crC_triangle.Get( 2 ) );
   
   return( C_CollisionSphere );
}

EE_MATH_VECTOR_C EE_EXZOKI_n::SlidingVector( const EE_COLLISION_SPHERE_C &crC_sphere, 
                                             const EE_MATH_VECTOR_C &crC_velocity, 
                                             EE_COLLISION_INFO_s &rs_collisionInfo )
{
    // Posunu kouli k m�stu kolize
    EE_COLLISION_SPHERE_C C_MovedSphere( crC_sphere );
    C_MovedSphere.SetPosition( crC_sphere.GetPosition() + crC_velocity * rs_collisionInfo.t_Time );
    // Vytvo��m sliding plane
    EE_MATH_PLANE_C C_SlidingPlane( C_MovedSphere.GetTangentPlane( rs_collisionInfo.C_Position ) );
    
    EE_MATH_POINT_C C_StartPoint( C_SlidingPlane.ProjectPoint( crC_sphere.GetPosition() ) ),
                    C_DestinationPoint( C_SlidingPlane.ProjectPoint( crC_sphere.GetPosition() + crC_velocity * 1.0 ) );
    EE_MATH_VECTOR_C C_SlidingVector( C_DestinationPoint - C_StartPoint );
  
    return( C_SlidingVector );      
}

