#ifndef EE_MODEL_OBJECT_MESH_H
#define EE_MODEL_OBJECT_MESH_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/error/ee_error.h>
#include <gl/gl.h>

class EE_MODEL_OBJECT_MESH_C
{
	public:
		EE_MODEL_OBJECT_MESH_C( void );
		EE_MODEL_OBJECT_MESH_C( const EE_MODEL_OBJECT_MESH_C& crC_objectMesh );
		EE_MODEL_OBJECT_MESH_C& operator=( const EE_MODEL_OBJECT_MESH_C& crC_objectMesh );
		~EE_MODEL_OBJECT_MESH_C( void );
		
		void SetNFaces( EE_U32_t u32_nFaces );
		void SetVertexIndices( const EE_PU32_t cpu32_indices );
		void SetMaterialIndex( EE_U32_t u32_materialIndex );
		void SetTexCoordIndices( const EE_PU32_t cpu32_indices );
		
		EE_BOOL_t HasMaterial( void ) const;
		EE_U32_t GetMaterialIndex( void ) const;
		EE_U32_t GetNFaces( void ) const;
		const EE_PU32_t GetVertexIndices( void ) const;
		const EE_PU32_t GetTexCoordIndices( void ) const;
	
	   void Clear( void );
	
	private:
		void Create( const EE_MODEL_OBJECT_MESH_C& crC_objectMesh );
		void Destroy( void );
		
		EE_BOOL_t mb_HasMaterial;
		EE_U32_t mu32_MaterialIndex; 
		
		EE_PU32_t mpu32_VertexIndices;
		EE_PU32_t mpu32_TexCoordIndices;		
		EE_U32_t mu32_NFaces;
};

#endif
