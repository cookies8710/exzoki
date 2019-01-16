#include <exzoki/math/ee_math_sphere.h>

EE_MATH_SPHERE_C::EE_MATH_SPHERE_C( void ): mt_Radius( EE_MATH_TYPE_ZERO )
{
}   
  
void EE_MATH_SPHERE_C::SetPosition( const EE_MATH_POINT_C& crC_position )
{
 	mC_Position = crC_position;    
}

void EE_MATH_SPHERE_C::SetPosition( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z )
{
 	mC_Position.Set( t_x, t_y, t_z );    
}

void EE_MATH_SPHERE_C::SetRadius( EE_MATH_TYPE_t t_radius )
{
 	mt_Radius = t_radius;    
}

EE_MATH_PLANE_C EE_MATH_SPHERE_C::GetTangentPlane( const EE_MATH_POINT_C& crC_point ) const
{
    EE_MATH_VECTOR_C C_TangentPlaneNormal( mC_Position - crC_point ); 
    C_TangentPlaneNormal.Normalize();
    return( EE_MATH_PLANE_C( C_TangentPlaneNormal, crC_point ) );
}

EE_MATH_TYPE_t EE_MATH_SPHERE_C::GetRadius( void ) const
{
 	return( mt_Radius );    
}

EE_MATH_TYPE_t EE_MATH_SPHERE_C::GetRadiusPow2( void ) const
{
 	return( mt_Radius * mt_Radius );         
}

const EE_MATH_POINT_C& EE_MATH_SPHERE_C::GetPosition( void ) const
{
 	return( mC_Position );    
}

EE_MATH_TYPE_t EE_MATH_SPHERE_C::GetX( void ) const
{
 	return( mC_Position.GetX() );    
}

EE_MATH_TYPE_t EE_MATH_SPHERE_C::GetY( void ) const
{
 	return( mC_Position.GetY() );    
}

EE_MATH_TYPE_t EE_MATH_SPHERE_C::GetZ( void ) const
{
 	return( mC_Position.GetZ() );    
}
