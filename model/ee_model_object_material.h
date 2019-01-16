#ifndef EE_MODEL_OBJECT_MATERIAL_H
#define EE_MODEL_OBJECT_MATERIAL_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>

struct EE_MODEL_OBJECT_MATERIAL_TEXCOORDS_s
{
	EE_U32_t u32_VertexTexCoordA;	
	EE_U32_t u32_VertexTexCoordB;	
	EE_U32_t u32_VertexTexCoordC;	
};

class EE_MODEL_OBJECT_MATERIAL_C
{
	public:
		EE_MODEL_OBJECT_MATERIAL_C( void );
		~EE_MODEL_OBJECT_MATERIAL_C( void );
		EE_MODEL_OBJECT_MATERIAL_C( const EE_MODEL_OBJECT_MATERIAL_C& crC_objectMaterial );
		EE_MODEL_OBJECT_MATERIAL_C& operator=( const EE_MODEL_OBJECT_MATERIAL_C& crC_objectMaterial );
		
		void SetMaterialIndex( EE_U32_t u32_materialIndex );
		void SetNFaces( EE_U32_t u32_nFaces );
		void SetTexCoords( const EE_MODEL_OBJECT_MATERIAL_TEXCOORDS_s *cps_texCoords );
		
		EE_U32_t GetMaterialIndex( void ) const;
		EE_U32_t GetNFaces( void ) const;
		EE_BOOL_t HasTexCoords( void ) const;
		const EE_MODEL_OBJECT_MATERIAL_TEXCOORDS_s* GetTexCoords( void ) const;
		
		void EE_MODEL_OBJECT_MATERIAL_C::Read( EE_SYSTEM_FILE_C& rC_file );
			
	private:
		void Create( const EE_MODEL_OBJECT_MATERIAL_C& crC_objectMaterial );
		void Destroy( void );
		
		EE_U32_t mu32_MaterialIndex;
		EE_U32_t mu32_NFaces;
		EE_MODEL_OBJECT_MATERIAL_TEXCOORDS_s *mps_TexCoords;
};

#endif
