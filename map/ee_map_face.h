#ifndef EE_MAP_FACE_H
#define EE_MAP_FACE_H

#include <exzoki/model/ee_model_face.h>

class EE_MAP_FACE_C: public EE_MODEL_FACE_C
{
	public:
        EE_MAP_FACE_C( void );
        EE_MAP_FACE_C( EE_U32_t u32_vi1, EE_U32_t u32_vi2, EE_U32_t u32_vi3 );
        
        void SetMaterialIndex( EE_U32_t u32_material );
        void SetTexCoordIndexA( EE_U32_t u32_tca );
        void SetTexCoordIndexB( EE_U32_t u32_tcb );
        void SetTexCoordIndexC( EE_U32_t u32_tcc );
        
        EE_U32_t GetMaterialIndex( void ) const;
        EE_U32_t GetTexCoordIndex( EE_BYTE_t b_vertex ) const;
        EE_U32_t GetTexCoordIndexA( void ) const;
        EE_U32_t GetTexCoordIndexB( void ) const;
        EE_U32_t GetTexCoordIndexC( void ) const;
        
	private:	
		EE_U32_t mu32_MaterialIndex;
        EE_U32_t mu32_TexCoordIndexA,
                 mu32_TexCoordIndexB,
                 mu32_TexCoordIndexC;		
};

#endif
