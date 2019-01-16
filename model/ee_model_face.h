#ifndef EE_MODEL_FACE_H
#define EE_MODEL_FACE_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>

class EE_MODEL_FACE_C
{
	public:
		EE_MODEL_FACE_C( void );
		EE_MODEL_FACE_C( EE_U32_t u32_vertexIndexA, EE_U32_t u32_vertexIndexB, EE_U32_t u32_vertexIndexC );
		
		void Set( EE_U32_t u32_vertexIndexA, EE_U32_t u32_vertexIndexB, EE_U32_t u32_vertexIndexC );
		
		EE_U32_t GetVertexIndex( EE_U32_t u32_index ) const;
				
		void EE_MODEL_FACE_C::Read( EE_SYSTEM_FILE_C& rC_file );
	private:	
		EE_U32_t mu32_VertexIndexA;
		EE_U32_t mu32_VertexIndexB;
		EE_U32_t mu32_VertexIndexC;
};

#endif
