#ifndef EE_MODEL_OBJECT_H
#define EE_MODEL_OBJECT_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>
#include <vector>
#include <exzoki/model/ee_model_vertex.h>
#include <exzoki/model/ee_model_texcoord.h>
#include <exzoki/model/ee_model_face.h>
#include <exzoki/model/ee_model_object_material.h>
#include <exzoki/model/ee_model_object_mesh.h>
#include <exzoki/model/ee_model_bone.h>
#include <exzoki/model/ee_model_animation_bone.h>
#include <exzoki/model/ee_model_animation_armature.h>

class EE_MODEL_OBJECT_C
{
	public:
		EE_MODEL_OBJECT_C( void );
		EE_MODEL_OBJECT_C( const EE_MODEL_OBJECT_C& crC_object );
		EE_MODEL_OBJECT_C& operator=( const EE_MODEL_OBJECT_C& crC_object );
		~EE_MODEL_OBJECT_C( void );
		
		void Read( EE_SYSTEM_FILE_C& rC_file );
		void SetNVertices( EE_U32_t u32_nVerts );
		void SetVertices( const EE_PFLOAT_t pf_vertices );
		void SetNTexCoords( EE_U32_t u32_nTexCoords );
		void SetTexCoords( const EE_PFLOAT_t pf_texCoords );
        		
        void AddMesh( const EE_MODEL_OBJECT_MESH_C &crC_mesh );
        		
		const EE_PFLOAT_t GetVertices( void ) const;
		EE_U32_t GetNVertices( void ) const;
		const EE_PFLOAT_t GetTexCoords( void ) const;
		EE_U32_t GetNTexCoords( void ) const;
		const std::vector< EE_MODEL_OBJECT_MESH_C >& GetMeshes( void ) const;
			
		std::string GetName( void ) const;	
		EE_BOOL_t HasVertexBone( EE_U32_t u32_vertexIndex ) const;
		const EE_MODEL_BONE_C& GetVertexBone( EE_U32_t u32_vertexIndex ) const;
		
		void Clear( void );
		
		void DrawBones( const EE_SYSTEM_COLOR_s &crs_headColor, 
		                const EE_SYSTEM_COLOR_s &crs_tailColor ) const;
		void DrawAnimatedBones( const EE_SYSTEM_COLOR_s &crs_headColor, 
		                		const EE_SYSTEM_COLOR_s &crs_tailColor,
		                		const EE_MODEL_ANIMATION_ARMATURE_C &crC_skeleton,
								EE_U32_t u32_frame ) const;
		
	private:
		void Create( const EE_MODEL_OBJECT_C& crC_object );
		void Destroy( void );
		
		EE_U32_t mu32_NVertices;
		EE_PFLOAT_t mpf_Vertices;
		
		EE_U32_t mu32_NTexCoords;
		EE_PFLOAT_t mpf_TexCoords;
		
		std::string mS_Name;
		
		std::vector< EE_MODEL_BONE_C > mco_Bones;
		EE_PU32_t mpu32_VertexBones;
		EE_PBYTE_t mpb_VertexBones; 
		
		std::vector< EE_MODEL_OBJECT_MESH_C > mco_Meshes;		
};

#endif
