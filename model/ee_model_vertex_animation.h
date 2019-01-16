#ifndef EE_MODEL_VERTEX_ANIMATION_H
#define EE_MODEL_VERTEX_ANIMATION_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/model/ee_model_vertex.h>
#include <string>
#include <vector>

typedef EE_MODEL_VERTEX_C EE_MODEL_VERTEX_ANIMATION_VERTEX_t;
typedef std::vector< EE_MODEL_VERTEX_ANIMATION_VERTEX_t > EE_MODEL_VERTEX_ANIMATION_FRAME_t;

namespace EE_MODEL_VERTEX_ANIMATION_TVA_n
{
	const std::string cS_Header( "tva" );
 	const EE_U16_t cu16_Version( 0x1000 );	
};

class EE_MODEL_VERTEX_ANIMATION_C
{
	public:
		EE_MODEL_VERTEX_ANIMATION_C( void );
		EE_MODEL_VERTEX_ANIMATION_C( EE_CCSTRING_t ccs_path );
		
		void Load( EE_CCSTRING_t ccs_path );	
		
		std::string GetName( void ) const;
		EE_U16_t GetNFrames( void ) const;
		EE_FLOAT_t GetFrameRate( void ) const;
		EE_U32_t GetNVertices( void ) const;
		
		const EE_MODEL_VERTEX_ANIMATION_FRAME_t& GetVertexFrame( EE_U16_t u16_frame ) const;
		
		void Clear( void );
		
	private:	
				
		std::string mS_Name;
		EE_U16_t mu16_NFrames;
		EE_FLOAT_t mf_FrameRate;
		EE_U32_t mu32_NVertices;
		std::vector< EE_MODEL_VERTEX_ANIMATION_FRAME_t > mco_Vertices;	
};

#endif
