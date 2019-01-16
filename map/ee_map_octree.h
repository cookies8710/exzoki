#ifndef EE_MAP_OCTREE_H
#define EE_MAP_OCTREE_H

#include <exzoki/model/ee_model_material.h>
#include <exzoki/model/ee_model_vertex.h>
#include <exzoki/model/ee_model.h>
#include <exzoki/map/ee_map_octree_node.h>
#include <exzoki/map/ee_map_face.h>
#include <exzoki/texture/ee_texture_manager.h>
#include <exzoki/collision/ee_collision_functions.h>

class EE_MAP_OCTREE_C
{
    public:
        EE_MAP_OCTREE_C( void );
        ~EE_MAP_OCTREE_C( void );
        
        EE_MAP_OCTREE_C operator=( const EE_MAP_OCTREE_C &crC_octree );
                
        void Clear( void );
        
        void Create( const EE_MODEL_C &crC_model,
                     EE_TEXTURE_FILTERING_e e_filtering = EE_TEXTURE_FILTERING_BILINEAR );
        
        void Draw( void ) const;        
        
        // Procedure detekce kolizí a reakcí na nì - vrací pohybový vektor koule
    	EE_MATH_VECTOR_C CollisionProc( const EE_COLLISION_SPHERE_C &crC_collisionSphere, 
                                    	const EE_MATH_VECTOR_C &crC_velocity );  
        // Zkonroluje, zda statická koule nekoliduje s nìkterým polygonem mapy (OCTREE) 
    	EE_BOOL_t StaticCheckCollision( const EE_COLLISION_SPHERE_C &crC_collisionSphere );        
    
	private:
        void Build( const EE_MAP_OCTREE_C &crC_octree );
        void Destroy( void );
        
        EE_MAP_OCTREE_NODE_C *mpC_Root;
        std::vector< EE_MODEL_VERTEX_C > mco_Vertices;            
        std::vector< EE_MAP_FACE_C > mco_Faces;
        std::vector< EE_MODEL_TEXCOORD_C > mco_TexCoords;
        std::vector< EE_MODEL_MATERIAL_C > mco_Materials;
        EE_PU32_t mpu32_BitMasks;   
        
        EE_TEXTURE_MANAGER_C mC_TextureManager;
        std::string mS_TextureDirectory;
           
};


#endif
