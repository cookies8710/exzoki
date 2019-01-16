#ifndef EE_COLLISION_FUNCTIONS_H
#define EE_COLLISION_FUNCTIONS_H

#include <exzoki/collision/ee_collision_sphere.h>
#include <exzoki/math/ee_math_triangle.h>
#include <exzoki/math/ee_math_1delement.h>
#include <exzoki/math/ee_math_agops.h>
#include <exzoki/math/ee_math_plane.h>
#include <exzoki/math/ee_math_vector.h>

struct EE_COLLISION_INFO_s
{
    EE_MATH_TYPE_t t_Time;
    EE_MATH_POINT_C C_Position;
};

namespace EE_EXZOKI_n
{
    // Vytvoøí kolizní kouli pro trojúhelník
    EE_COLLISION_SPHERE_C CollisionSphere( const EE_MATH_TRIANGLE_C &crC_triangle );    
    // Spoèítá kolizi pohybující se koule a trojúhelníku 
    EE_BOOL_t CollisionSphereTriangle( const EE_COLLISION_SPHERE_C &crC_sphere, 
                                       const EE_MATH_VECTOR_C &crC_velocity, 
                                       const EE_MATH_TRIANGLE_C &crC_triangle,
                                       EE_COLLISION_INFO_s &rs_collisionInfo );                                       
    // Spoèítá sliding vector
    EE_MATH_VECTOR_C SlidingVector( const EE_COLLISION_SPHERE_C &crC_sphere, 
                                    const EE_MATH_VECTOR_C &crC_velocity, 
                                    EE_COLLISION_INFO_s &rs_collisionInfo );   
                                    
    const EE_U32_t cu32_MaxCollisionDetectionPasses( 5 );   
};

#endif
