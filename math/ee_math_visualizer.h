#ifndef EE_MATH_VISUALIZER
#define EE_MATH_VISUALIZER

#include <exzoki/system/ee_system_types.h>
#include <exzoki/math/ee_math_types.h>
#include <exzoki/math/ee_math_point.h>

namespace EE_EXZOKI_n
{
    // Zborazovaè bodu
    void Visualize( const EE_SYSTEM_COLOR_s &crs_color, 
                    const EE_MATH_POINT_C &crC_point );  
    // Zobrazovaè vektoru
    void Visualize( const EE_SYSTEM_COLOR_s &crs_color, 
                    const EE_MATH_VECTOR_C &crC_vector, 
                    const EE_MATH_POINT_C &crC_place = EE_MATH_POINT_C( 0.0, 0.0, 0.0 ) );  
    // Zobrazovaè roviny
    void Visualize( const EE_SYSTEM_COLOR_s &crs_color, 
                    const EE_MATH_PLANE_C &crC_plane );        
    
};

#endif
