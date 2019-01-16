#include <exzoki/model/ee_model_face.h>

EE_MODEL_FACE_C::EE_MODEL_FACE_C( void )
{
}

EE_MODEL_FACE_C::EE_MODEL_FACE_C( EE_U32_t u32_vertexIndexA, EE_U32_t u32_vertexIndexB, EE_U32_t u32_vertexIndexC ): mu32_VertexIndexA( u32_vertexIndexA ),
                                                                                                                             mu32_VertexIndexB( u32_vertexIndexB ),
																																									  mu32_VertexIndexC( u32_vertexIndexC )     
{
}
		
void EE_MODEL_FACE_C::Set( EE_U32_t u32_vertexIndexA, EE_U32_t u32_vertexIndexB, EE_U32_t u32_vertexIndexC )
{
	mu32_VertexIndexA = u32_vertexIndexA;	
	mu32_VertexIndexB = u32_vertexIndexB;	
	mu32_VertexIndexC = u32_vertexIndexC;	
}

EE_U32_t EE_MODEL_FACE_C::GetVertexIndex( EE_U32_t u32_index ) const
{
	switch( u32_index )
	{
		case 0:
			return( mu32_VertexIndexA );
			break;
		case 1:
			return( mu32_VertexIndexB );
			break;
		case 2:
			return( mu32_VertexIndexC );
			break;	
	}	
}
		
void EE_MODEL_FACE_C::Read( EE_SYSTEM_FILE_C& rC_file )
{
	rC_file.Read( &mu32_VertexIndexA, sizeof( mu32_VertexIndexA ) );	
	rC_file.Read( &mu32_VertexIndexB, sizeof( mu32_VertexIndexB ) );	
	rC_file.Read( &mu32_VertexIndexC, sizeof( mu32_VertexIndexC ) );
}
/*
void EE_MODEL_FACE_C::Write( EE_SYSTEM_FILE_C& rC_file ) const
{
	rC_file.Write( (EE_PVOID_t)&mu32_VertexIndexA, sizeof( mu32_VertexIndexA ) );	
	rC_file.Write( (EE_PVOID_t)&mu32_VertexIndexB, sizeof( mu32_VertexIndexB ) );	
	rC_file.Write( (EE_PVOID_t)&mu32_VertexIndexC, sizeof( mu32_VertexIndexC ) );
}


*/
