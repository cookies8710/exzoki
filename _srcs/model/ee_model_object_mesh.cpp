#include <exzoki/model/ee_model_object_mesh.h>

EE_MODEL_OBJECT_MESH_C::EE_MODEL_OBJECT_MESH_C( void ): mb_HasMaterial( EE_FALSE ),
                                                        mu32_MaterialIndex( 0 ),
                                                        mpu32_VertexIndices( EE_NULL ),
                                                        mpu32_TexCoordIndices( EE_NULL ),
                                                        mu32_NFaces( 0 )
{
}

EE_MODEL_OBJECT_MESH_C::EE_MODEL_OBJECT_MESH_C( const EE_MODEL_OBJECT_MESH_C& crC_objectMesh ): mb_HasMaterial( EE_FALSE ),
                                                                                                mu32_MaterialIndex( 0 ),
                                                                                                mpu32_VertexIndices( EE_NULL ),
                                                                                                mpu32_TexCoordIndices( EE_NULL ),
                                                                                                mu32_NFaces( 0 )
{	
	Create( crC_objectMesh );
}

EE_MODEL_OBJECT_MESH_C& EE_MODEL_OBJECT_MESH_C::operator=( const EE_MODEL_OBJECT_MESH_C& crC_objectMesh )
{
	if( &crC_objectMesh != this )
	{
		Destroy();
		Create( crC_objectMesh );	
	}	
	
	return( *this );
}

EE_MODEL_OBJECT_MESH_C::~EE_MODEL_OBJECT_MESH_C( void )
{
	Destroy();	
}
		
void EE_MODEL_OBJECT_MESH_C::SetNFaces( EE_U32_t u32_nFaces )
{
	mu32_NFaces = u32_nFaces;
}

void EE_MODEL_OBJECT_MESH_C::SetVertexIndices( const EE_PU32_t cpu32_indices )
{
	if( !mu32_NFaces )	
		EE_ERROR_C( "EE_MODEL_OBJECT_MESH_C", "SetVertexIndices", EE_ERROR_CODES_n::cS_Internal );
	else
	{
		mpu32_VertexIndices = new EE_U32_t[ mu32_NFaces * 3 ];	
		memcpy( mpu32_VertexIndices, cpu32_indices, mu32_NFaces * 3 * sizeof( EE_U32_t ) );
	}
}

void EE_MODEL_OBJECT_MESH_C::SetMaterialIndex( EE_U32_t u32_materialIndex )
{
	mb_HasMaterial = EE_TRUE;
	mu32_MaterialIndex = u32_materialIndex;	
}

void EE_MODEL_OBJECT_MESH_C::SetTexCoordIndices( const EE_PU32_t cpu32_indices )
{
	if( !mu32_NFaces )	
		EE_ERROR_C( "EE_MODEL_OBJECT_MESH_C", "SetTexCoordIndices", EE_ERROR_CODES_n::cS_Internal );
	else
	{
		mpu32_TexCoordIndices = new EE_U32_t[ mu32_NFaces * 3 ];	
		memcpy( mpu32_TexCoordIndices, cpu32_indices, mu32_NFaces * 3 * sizeof( EE_U32_t ) );
	/*	G << "dump_TC1:\n\t";
		for( EE_U32_t u(0);u<mu32_NFaces*3;u++ )
		 G << mpu32_TexCoordIndices[u]<<"\t";
		G<<std::endl;*/
	}
}

EE_BOOL_t EE_MODEL_OBJECT_MESH_C::HasMaterial( void ) const
{
	return( mb_HasMaterial );	
}
		
EE_U32_t EE_MODEL_OBJECT_MESH_C::GetMaterialIndex( void ) const
{
	if( !mb_HasMaterial )	
		EE_ERROR_C( "EE_MODEL_OBJECT_MESH_C", "GetMaterialIndex", EE_ERROR_CODES_n::cS_Internal );
	else
		return( mu32_MaterialIndex );
}

EE_U32_t EE_MODEL_OBJECT_MESH_C::GetNFaces( void ) const
{
	return( mu32_NFaces );
}

const EE_PU32_t EE_MODEL_OBJECT_MESH_C::GetVertexIndices( void ) const
{
	return( mpu32_VertexIndices );	
}

const EE_PU32_t EE_MODEL_OBJECT_MESH_C::GetTexCoordIndices( void ) const
{
	return( mpu32_TexCoordIndices );	
}

void EE_MODEL_OBJECT_MESH_C::Clear( void )
{
    Destroy();    
}
	
void EE_MODEL_OBJECT_MESH_C::Create( const EE_MODEL_OBJECT_MESH_C& crC_objectMesh )
{
	if( mb_HasMaterial = crC_objectMesh.mb_HasMaterial )
		mu32_MaterialIndex = crC_objectMesh.mu32_MaterialIndex;	
	
	mu32_NFaces = crC_objectMesh.mu32_NFaces;
	if( crC_objectMesh.mpu32_VertexIndices )
	{
		mpu32_VertexIndices = new EE_U32_t[ crC_objectMesh.mu32_NFaces * 3 ];	
		memcpy( mpu32_VertexIndices, crC_objectMesh.mpu32_VertexIndices, crC_objectMesh.mu32_NFaces * 3 * sizeof( EE_U32_t ) );
	/*	G << "dump2:\n\t";
		for( EE_U32_t u(0);u<mu32_NFaces*3;u++ )
		 G << mpu32_VertexIndices[u]<<"\t";
		G<<std::endl;*/
	}
	
	if( crC_objectMesh.mpu32_TexCoordIndices )
	{
		mpu32_TexCoordIndices = new EE_U32_t[ crC_objectMesh.mu32_NFaces * 3 ];	
		memcpy( mpu32_TexCoordIndices, crC_objectMesh.mpu32_TexCoordIndices, crC_objectMesh.mu32_NFaces * 3 * sizeof( EE_U32_t ) );
	}
}

void EE_MODEL_OBJECT_MESH_C::Destroy( void )
{
	delete[] mpu32_VertexIndices;
	mpu32_VertexIndices = EE_NULL;
	
	delete[] mpu32_TexCoordIndices;
	mpu32_TexCoordIndices = EE_NULL;
	
	mu32_NFaces = 0;
	
	mb_HasMaterial = EE_FALSE;
	mu32_MaterialIndex = 0;
}
		










