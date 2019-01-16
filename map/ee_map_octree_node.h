#ifndef EE_MAP_OCTREE_NODE_H
#define EE_MAP_OCTREE_NODE_H

#include <vector>
#include <exzoki/error/ee_error.h>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/math/ee_math_point.h>
#include <exzoki/math/ee_math_triangle.h>
#include <exzoki/math/ee_math_plane.h>
#include <exzoki/map/ee_map_face.h>
#include <exzoki/texture/ee_texture_manager.h>

namespace EE_EXZOKI_n
{
    const EE_U32_t cu32_OctreeMaxFacesPerNode( 100 );    
};

class EE_MAP_OCTREE_NODE_C
{
    public:
        EE_MAP_OCTREE_NODE_C( void );
        EE_MAP_OCTREE_NODE_C( const EE_MATH_POINT_C &crC_position,
                              EE_FLOAT_t f_side );
        ~EE_MAP_OCTREE_NODE_C( void );
        
        EE_MAP_OCTREE_NODE_C( const EE_MAP_OCTREE_NODE_C &crC_node );
        EE_MAP_OCTREE_NODE_C operator=( const EE_MAP_OCTREE_NODE_C& crC_node  );
        
        void Clear( void );        
        
        void Set( const EE_MATH_POINT_C &crC_position,
                  EE_FLOAT_t f_side );                  
        void SetFaces( const std::vector< EE_U32_t > &crco_faces );
        
        void Divide( const std::vector< EE_U32_t > &crco_faceIndices,
                     const std::vector< EE_MODEL_VERTEX_C > &crco_vertices,
                     const std::vector< EE_MAP_FACE_C > &crco_faces );
        
        void Draw( const std::vector< EE_MODEL_VERTEX_C > &crco_vertices,
                   const std::vector< EE_MAP_FACE_C > &crco_faces,
                   const std::vector< EE_MODEL_TEXCOORD_C > &crco_texcoords,
                   const std::vector< EE_MODEL_MATERIAL_C > &crco_materials,
                   const EE_TEXTURE_MANAGER_C& crC_textureManager ) const;
        
        EE_BOOL_t FastCollisionWithSphere( const EE_MATH_SPHERE_C &crC_sphere );
             
        // Test pohybující se koule vùèi mapì (OCTREE) - pokud kolize nastává, vrací èas a pozici
    	EE_BOOL_t CheckCollision( const EE_COLLISION_SPHERE_C &crC_collisionSphere, 
                              	  EE_MATH_VECTOR_C C_velocity, 
                              	  EE_COLLISION_INFO_s &rs_collisionInfo,
		                          const std::vector< EE_MODEL_VERTEX_C > &crco_vertices,
                   				  const std::vector< EE_MAP_FACE_C > &crco_faces );   
        
        EE_BOOL_t StaticCheckCollision( const EE_COLLISION_SPHERE_C &crC_collisionSphere,
		                                const std::vector< EE_MODEL_VERTEX_C > &crco_vertices,
                   						const std::vector< EE_MAP_FACE_C > &crco_faces );
        
    private:
        void Build( const EE_MAP_OCTREE_NODE_C &crC_node );
        void Destroy( void );  
        
        EE_BOOL_t Collision( const EE_MATH_TRIANGLE_C &crC_triangle ) const;
        
        // Dceøinné nody
        EE_MAP_OCTREE_NODE_C *mapC_Children[ 8 ];
        
        // Face index
        EE_PU32_t mpu32_FaceIndices;
        EE_U32_t mu32_NFaces; 
        
        // Pozice nodu
        EE_MATH_POINT_C mC_Position;
        // Strana krychle ohranièující node
        EE_FLOAT_t mf_Side;         
};

#endif
