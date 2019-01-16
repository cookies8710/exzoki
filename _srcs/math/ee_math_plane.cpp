#include <exzoki/math/ee_math_plane.h>

EE_MATH_PLANE_C::EE_MATH_PLANE_C( void ): mt_D( EE_MATH_TYPE_ZERO )
{
}

EE_MATH_PLANE_C::EE_MATH_PLANE_C( const EE_MATH_VECTOR_C& crC_normal, EE_MATH_TYPE_t t_d )
{
	Set( crC_normal, t_d );	
}

EE_MATH_PLANE_C::EE_MATH_PLANE_C( const EE_MATH_VECTOR_C& crC_normal, const EE_MATH_POINT_C& crC_planePoint )
{
 	Set( crC_normal, crC_planePoint );
}

EE_MATH_PLANE_C::EE_MATH_PLANE_C( const EE_MATH_POINT_C& crC_pointA, 
                                  const EE_MATH_POINT_C& crC_pointB, 
                                  const EE_MATH_POINT_C& crC_pointC )
{
 	Set( crC_pointA, crC_pointB, crC_pointC );
}                                    

EE_MATH_PLANE_C::EE_MATH_PLANE_C( const EE_MATH_TRIANGLE_C& crC_triangle )
{
	Set( crC_triangle );	
}

void EE_MATH_PLANE_C::Set( const EE_MATH_VECTOR_C& crC_normal, EE_MATH_TYPE_t t_d )
{
	mC_Normal = crC_normal;
	mt_D = t_d;
}
  
void EE_MATH_PLANE_C::Set( const EE_MATH_VECTOR_C& crC_normal, const EE_MATH_POINT_C& crC_planePoint )
{
 	mC_Normal = crC_normal;
 	mC_Normal.Normalize();
 	mt_D = - ( mC_Normal * crC_planePoint );
}

void EE_MATH_PLANE_C::Set( const EE_MATH_POINT_C& crC_pointA, 
                           const EE_MATH_POINT_C& crC_pointB, 
                           const EE_MATH_POINT_C& crC_pointC )
{
 	mC_Normal.Normal( crC_pointA, crC_pointB, crC_pointC );
 	mC_Normal.Normalize();
 	mt_D = - ( mC_Normal * crC_pointA ); 
}                            

void EE_MATH_PLANE_C::Set( const EE_MATH_TRIANGLE_C& crC_triangle )
{
	Set( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), crC_triangle.Get( 2 ) );	
}

EE_MATH_POSITION_e EE_MATH_PLANE_C::PointPosition( const EE_MATH_POINT_C& crC_point ) const
{
 	EE_MATH_TYPE_t t_Position;

 	t_Position = GetDistance( crC_point );

 	if( t_Position < -EE_MATH_TYPE_PRECISION )
  		return( EE_MATH_POSITION_BEHIND );
 	else if( t_Position > EE_MATH_TYPE_PRECISION )
  		return( EE_MATH_POSITION_FRONT );
 	else 
  		return( EE_MATH_POSITION_SAME );
}

EE_MATH_POSITION_e EE_MATH_PLANE_C::TrianglePosition( const EE_MATH_POINT_C& crC_pointA, 
                                                      const EE_MATH_POINT_C& crC_pointB, 
                                                      const EE_MATH_POINT_C& crC_pointC ) const
{
 	EE_MATH_POSITION_e e_Position;
 	EE_MATH_POSITION_e ae_VertexPositions[ 3 ];

 	ae_VertexPositions[ 0 ] = this->PointPosition( crC_pointA );
 	ae_VertexPositions[ 1 ] = this->PointPosition( crC_pointB );
 	ae_VertexPositions[ 2 ] = this->PointPosition( crC_pointC );
 
  	unsigned char uc_Front = 0, uc_Behind = 0; 
  
 	for( unsigned char uc_Vertex = 0; uc_Vertex < 3; uc_Vertex++ )
  	if( ae_VertexPositions[ uc_Vertex ] == EE_MATH_POSITION_FRONT )
   	uc_Front++;
  	else if( ae_VertexPositions[ uc_Vertex ] == EE_MATH_POSITION_BEHIND )
   	uc_Behind++;

  	if( uc_Front && uc_Behind )
   	e_Position = EE_MATH_POSITION_COLLISION;
  	else if( uc_Front )
   	e_Position = EE_MATH_POSITION_FRONT;
  	else if( uc_Behind )
   	e_Position = EE_MATH_POSITION_BEHIND;
  	else
   	e_Position = EE_MATH_POSITION_SAME;
 	
 	return( e_Position );
}   

EE_MATH_POSITION_e EE_MATH_PLANE_C::TrianglePosition( const EE_MATH_TRIANGLE_C& crC_triangle ) const
{
	return( TrianglePosition( crC_triangle.Get( 0 ), crC_triangle.Get( 1 ), crC_triangle.Get( 2 ) ) );	
}          

EE_MATH_POINT_C EE_MATH_PLANE_C::ProjectPoint( const EE_MATH_POINT_C &crC_point ) const
{
    return( crC_point - mC_Normal * ( ( mC_Normal * crC_point + mt_D ) / ( mC_Normal.Pow2() ) ) );    
}                                         

EE_MATH_VECTOR_C EE_MATH_PLANE_C::GetNormal( void ) const
{
 	return( mC_Normal );    
}

EE_MATH_TYPE_t EE_MATH_PLANE_C::GetD( void ) const
{
 	return( mt_D );    
}

EE_MATH_TYPE_t EE_MATH_PLANE_C::GetDistance( const EE_MATH_POINT_C &crC_point ) const
{
 	return( mC_Normal * crC_point + mt_D );   
}
