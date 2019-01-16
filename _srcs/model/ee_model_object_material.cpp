#include <exzoki/model/ee_model_object_material.h>

EE_MODEL_OBJECT_MATERIAL_C::EE_MODEL_OBJECT_MATERIAL_C( void ): mps_TexCoords( EE_NULL ),
                                                                mu32_NFaces( 0 )
{
}

EE_MODEL_OBJECT_MATERIAL_C::~EE_MODEL_OBJECT_MATERIAL_C( void )
{
	Destroy();	
}

EE_MODEL_OBJECT_MATERIAL_C::EE_MODEL_OBJECT_MATERIAL_C( const EE_MODEL_OBJECT_MATERIAL_C& crC_objectMaterial ): mps_TexCoords( EE_NULL ),
                                                                                                                mu32_NFaces( 0 )
{
	Create( crC_objectMaterial );	
}

EE_MODEL_OBJECT_MATERIAL_C& EE_MODEL_OBJECT_MATERIAL_C::operator=( const EE_MODEL_OBJECT_MATERIAL_C& crC_objectMaterial )
{
	if( &crC_objectMaterial != this )
	{
		Destroy();
		Create( crC_objectMaterial );	
	}	
	
	return( *this );
}
		
void EE_MODEL_OBJECT_MATERIAL_C::SetMaterialIndex( EE_U32_t u32_materialIndex )
{
	mu32_MaterialIndex = u32_materialIndex;	
}

void EE_MODEL_OBJECT_MATERIAL_C::SetNFaces( EE_U32_t u32_nFaces )
{
	mu32_NFaces = u32_nFaces;	
}

void EE_MODEL_OBJECT_MATERIAL_C::SetTexCoords( const EE_MODEL_OBJECT_MATERIAL_TEXCOORDS_s *cps_texCoords )
{
	if( mps_TexCoords )
	{
		delete[] mps_TexCoords;
		mps_TexCoords = EE_NULL;	
	}	
	
	mps_TexCoords = new EE_MODEL_OBJECT_MATERIAL_TEXCOORDS_s[ mu32_NFaces ];
	for( EE_U32_t u32_Face( 0 ); u32_Face < mu32_NFaces; u32_Face++ )
		mps_TexCoords[ u32_Face ] = cps_texCoords[ u32_Face ];
}

EE_U32_t EE_MODEL_OBJECT_MATERIAL_C::GetMaterialIndex( void ) const
{
	return( mu32_MaterialIndex );	
}

EE_U32_t EE_MODEL_OBJECT_MATERIAL_C::GetNFaces( void ) const
{
	return( mu32_NFaces );	
}

EE_BOOL_t EE_MODEL_OBJECT_MATERIAL_C::HasTexCoords( void ) const
{
	return( (EE_BOOL_t)(bool)mps_TexCoords );	
}

const EE_MODEL_OBJECT_MATERIAL_TEXCOORDS_s* EE_MODEL_OBJECT_MATERIAL_C::GetTexCoords( void ) const
{
	return( mps_TexCoords );	
}

void EE_MODEL_OBJECT_MATERIAL_C::Read( EE_SYSTEM_FILE_C& rC_file )
{
	Destroy();
	
	rC_file.Read( &mu32_MaterialIndex, sizeof( mu32_MaterialIndex ) );
	rC_file.Read( &mu32_NFaces, sizeof( mu32_NFaces ) );
	EE_BOOL_t b_HasTexCoords( EE_FALSE );
	rC_file.Read( &b_HasTexCoords, sizeof( b_HasTexCoords ) );
	if( b_HasTexCoords )
	{
		mps_TexCoords = new EE_MODEL_OBJECT_MATERIAL_TEXCOORDS_s[ mu32_NFaces ];
		for( EE_U32_t u32_Face( 0 ); u32_Face < mu32_NFaces; u32_Face++ )
		{
			EE_MODEL_OBJECT_MATERIAL_TEXCOORDS_s& rs_TexCoords = mps_TexCoords[ u32_Face ];
			rC_file.Read( &rs_TexCoords.u32_VertexTexCoordA, sizeof( rs_TexCoords.u32_VertexTexCoordA ) );
			rC_file.Read( &rs_TexCoords.u32_VertexTexCoordB, sizeof( rs_TexCoords.u32_VertexTexCoordB ) );
			rC_file.Read( &rs_TexCoords.u32_VertexTexCoordC, sizeof( rs_TexCoords.u32_VertexTexCoordC ) );
		}
	}
}
/*
void EE_MODEL_OBJECT_MATERIAL_C::Write( EE_SYSTEM_FILE_C& rC_file ) const
{
	rC_file.Write( (EE_PVOID_t)&mu32_MaterialIndex, sizeof( mu32_MaterialIndex ) );	
	rC_file.Write( (EE_PVOID_t)&mu32_NFaces, sizeof( mu32_NFaces ) );	
	EE_BOOL_t b_HasTexCoords( (bool)mps_TexCoords );
	rC_file.Write( (EE_PVOID_t)&b_HasTexCoords, sizeof( b_HasTexCoords ) );
	if( b_HasTexCoords )
		for( EE_U32_t u32_Face( 0 ); u32_Face < mu32_NFaces; u32_Face++ )
		{
			EE_MODEL_OBJECT_MATERIAL_TEXCOORDS_s& rs_TexCoords = mps_TexCoords[ u32_Face ];
			rC_file.Write( (EE_PVOID_t)&rs_TexCoords.u32_VertexTexCoordA, sizeof( rs_TexCoords.u32_VertexTexCoordA ) );
			rC_file.Write( (EE_PVOID_t)&rs_TexCoords.u32_VertexTexCoordB, sizeof( rs_TexCoords.u32_VertexTexCoordB ) );
			rC_file.Write( (EE_PVOID_t)&rs_TexCoords.u32_VertexTexCoordC, sizeof( rs_TexCoords.u32_VertexTexCoordC ) );
		}
}*/

void EE_MODEL_OBJECT_MATERIAL_C::Create( const EE_MODEL_OBJECT_MATERIAL_C& crC_objectMaterial )
{
	mu32_MaterialIndex = crC_objectMaterial.mu32_MaterialIndex;
	mu32_NFaces = crC_objectMaterial.mu32_NFaces;
	if( crC_objectMaterial.mps_TexCoords )
		SetTexCoords( crC_objectMaterial.mps_TexCoords );
}

void EE_MODEL_OBJECT_MATERIAL_C::Destroy( void )
{
	if( mps_TexCoords )
	{
		delete[] mps_TexCoords;
		mps_TexCoords = EE_NULL;	
	}	
}
