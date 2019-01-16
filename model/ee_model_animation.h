#ifndef EE_MODEL_ANIMATION_H
#define EE_MODEL_ANIMATION_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/model/ee_model_animation_bone.h>
#include <exzoki/model/ee_model_animation_armature.h>
#include <string>
#include <map>

namespace EE_MODEL_ANIMATION_TAN_n
{
	const std::string cS_Header( "tan" );
 	const EE_U16_t cu16_Version( 0x1000 );	
};

class EE_MODEL_ANIMATION_C
{
	public:
		EE_MODEL_ANIMATION_C( void );
		EE_MODEL_ANIMATION_C( EE_CCSTRING_t ccs_path );
		
		void Load( EE_CCSTRING_t ccs_path );	
		
		std::string GetName( void ) const;
		EE_U32_t GetNFrames( void ) const;
		EE_FLOAT_t GetFrameRate( void ) const;
		
		const EE_MODEL_ANIMATION_ARMATURE_C& GetSkeleton( EE_CCSTRING_t ccs_objectName ) const;
		const EE_MODEL_ANIMATION_BONE_C& GetBone( EE_CCSTRING_t ccs_objectName, EE_CCSTRING_t ccs_boneName ) const;
		
		void Clear( void );
		
	private:	
				
		std::string mS_Name;
		EE_U32_t mu32_NFrames;
		EE_FLOAT_t mf_FrameRate;
		std::map< std::string, EE_MODEL_ANIMATION_ARMATURE_C > mco_Armatures;	
};

#endif
