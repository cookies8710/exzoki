#ifndef EE_MATH_AGOPS_H
#define EE_MATH_AGOPS_H

#include <math.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/math/ee_math_types.h>
#include <exzoki/math/ee_math_vector.h>
#include <exzoki/math/ee_math_point.h>
#include <exzoki/math/ee_math_1delement.h>
#include <exzoki/math/ee_math_plane.h>
#include <exzoki/math/ee_math_triangle.h>
#include <exzoki/math/ee_math_sphere.h>
#include <exzoki/math/ee_math_gem.h>
#include <vector>

enum EE_MATH_INTERSECTION_TYPE_e { EE_MATH_INTERSECTION_TYPE_NOTHING = 0,
                                   EE_MATH_INTERSECTION_TYPE_POINT,
                                   EE_MATH_INTERSECTION_TYPE_1DELEMENT };

namespace EE_MATH_AGOPS_n
{
	// INTERSECTIONS
 	EE_PVOID_t Intersection( const EE_MATH_1DELEMENT_C& crC_1delement, 
                            const EE_MATH_1DELEMENT_C& crC_1delement2, 
                            EE_MATH_INTERSECTION_TYPE_e& rC_intersectionType );
 	EE_PVOID_t Intersection( const EE_MATH_1DELEMENT_C& crC_1delement, 
                            const EE_MATH_PLANE_C& crC_plane, 
                            EE_MATH_INTERSECTION_TYPE_e& rC_intersectionType );
 	EE_PVOID_t Intersection( const EE_MATH_1DELEMENT_C& crC_1delement, 
                            const EE_MATH_TRIANGLE_C& crC_triangle, 
                            EE_MATH_INTERSECTION_TYPE_e& rC_intersectionType );
 
 
 	// DISTANCES
 	EE_MATH_TYPE_t Distance( const EE_MATH_POINT_C& crC_point, const EE_MATH_POINT_C& crC_point2 );
 	EE_MATH_TYPE_t Distance( const EE_MATH_POINT_C& crC_point, const EE_MATH_1DELEMENT_C& crC_1delement );
 	EE_MATH_TYPE_t Distance( const EE_MATH_POINT_C& crC_point, const EE_MATH_PLANE_C& crC_plane );
 	EE_MATH_TYPE_t Distance( const EE_MATH_POINT_C& crC_point, const EE_MATH_TRIANGLE_C& crC_triangle );
 	EE_MATH_TYPE_t Distance( const EE_MATH_POINT_C& crC_point, const EE_MATH_SPHERE_C& crC_sphere );
 
 	EE_MATH_TYPE_t Distance( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_1DELEMENT_C& crC_1delement2 );
 	EE_MATH_TYPE_t Distance( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_PLANE_C& crC_plane );
 	EE_MATH_TYPE_t Distance( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_TRIANGLE_C& crC_triangle );
 	EE_MATH_TYPE_t Distance( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_SPHERE_C& crC_sphere );
  
 	EE_MATH_TYPE_t Distance( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_PLANE_C& crC_plane2 );
 	EE_MATH_TYPE_t Distance( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_TRIANGLE_C& crC_triangle );
 	EE_MATH_TYPE_t Distance( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_SPHERE_C& crC_sphere );
  
 	EE_MATH_TYPE_t Distance( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_TRIANGLE_C& crC_triangle2 );
 	EE_MATH_TYPE_t Distance( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_SPHERE_C& crC_sphere );
  
 	EE_MATH_TYPE_t Distance( const EE_MATH_SPHERE_C& crC_sphere, const EE_MATH_SPHERE_C& crC_sphere2 );

 	// DISTANESPOW2
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_POINT_C& crC_point2 );
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_1DELEMENT_C& crC_1delement );
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_PLANE_C& crC_plane );
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_TRIANGLE_C& crC_triangle );
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_POINT_C& crC_point, const EE_MATH_SPHERE_C& crC_sphere );
  
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_1DELEMENT_C& crC_1delement2 );
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_PLANE_C& crC_plane );
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_TRIANGLE_C& crC_triangle );
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_SPHERE_C& crC_sphere );
  
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_PLANE_C& crC_plane2 );
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_TRIANGLE_C& crC_triangle );
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_SPHERE_C& crC_sphere );
  
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_TRIANGLE_C& crC_triangle2 );
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_SPHERE_C& crC_sphere );
  
 	EE_MATH_TYPE_t DistancePow2( const EE_MATH_SPHERE_C& crC_sphere, const EE_MATH_SPHERE_C& crC_sphere2 );
 
 	// COLLISIONS
 	EE_BOOL_t Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_POINT_C& crC_point2 );
 	EE_BOOL_t Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_1DELEMENT_C& crC_1delement );
 	EE_BOOL_t Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_PLANE_C& crC_plane );
 	EE_BOOL_t Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_TRIANGLE_C& crC_triangle );
 	EE_BOOL_t Collision( const EE_MATH_POINT_C& crC_point, const EE_MATH_SPHERE_C& crC_sphere );
  
 	EE_BOOL_t Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_1DELEMENT_C& crC_1delement2 );
 	EE_BOOL_t Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_PLANE_C& crC_plane );
 	EE_BOOL_t Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_TRIANGLE_C& crC_triangle );
 	EE_BOOL_t Collision( const EE_MATH_1DELEMENT_C& crC_1delement, const EE_MATH_SPHERE_C& crC_sphere );
 
 	EE_BOOL_t Collision( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_PLANE_C& crC_plane2 );
 	EE_BOOL_t Collision( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_TRIANGLE_C& crC_triangle );
 	EE_BOOL_t Collision( const EE_MATH_PLANE_C& crC_plane, const EE_MATH_SPHERE_C& crC_sphere );
 
  	EE_BOOL_t Collision( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_TRIANGLE_C& crC_triangle2 );
 	EE_BOOL_t Collision( const EE_MATH_TRIANGLE_C& crC_triangle, const EE_MATH_SPHERE_C& crC_sphere );
  
 	EE_BOOL_t Collision( const EE_MATH_SPHERE_C& crC_sphere, const EE_MATH_SPHERE_C& crC_sphere2 );
	 
	// MISC.
	void SplitTriangle( const EE_MATH_TRIANGLE_C &crC_triangle,
                        const EE_MATH_PLANE_C& crC_plane,
                        std::vector< EE_MATH_TRIANGLE_C >& rco_front,
                        std::vector< EE_MATH_TRIANGLE_C >& rco_back );
    void SetUpTriangleByNormal( EE_MATH_TRIANGLE_C& rC_triangle,
                                const EE_MATH_POINT_C &crC_point1,
                                const EE_MATH_POINT_C &crC_point2,
                                const EE_MATH_POINT_C &crC_point3,
                                const EE_MATH_VECTOR_C &crC_normal );
	//EE_MATH_SPHERE_C CollisionSphere( const std::vector< EE_MATH_POINT_C >& crco_poinEE );      		
};

#endif
