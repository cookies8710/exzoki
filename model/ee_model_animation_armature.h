#ifndef EE_MODEL_ANIMATION_ARMATURE_H
#define EE_MODEL_ANIMATION_ARMATURE_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/model/ee_model_animation_bone.h>
#include <exzoki/base/ee_base.h>
#include <string>

class EE_MODEL_ANIMATION_ARMATURE_C: public EE_BASE_C
{
	public:
		EE_MODEL_ANIMATION_ARMATURE_C( void );
		
		void Read( EE_SYSTEM_FILE_C& rC_file, EE_U32_t u32_nFrames );	
		
		std::string GetObjectName( void ) const;
		
		EE_MODEL_ANIMATION_BONE_C& GetBone( EE_CCSTRING_t ccs_boneName );
		const EE_MODEL_ANIMATION_BONE_C& GetBone( EE_CCSTRING_t ccs_boneName ) const;
		
		const EE_MATH_MATRIX4X4_C& GetArmatureMatrix( void ) const;
		const EE_MATH_MATRIX4X4_C& GetInverseArmatureMatrix( void ) const;
		
		void Clear( void );		
		
		virtual EE_BYTE_t Read( std::ifstream &rC_file ){}
		virtual EE_BYTE_t Write( std::ofstream &rC_file ) const	{}		
		virtual EE_BYTE_t Dump( std::ofstream &rC_file ) const;
		
	private:	
		void RecursivelyMultiplyMatrices( EE_MODEL_ANIMATION_BONE_C& rC_bone );
		void RecursivelyMultiplyBones( EE_MODEL_ANIMATION_BONE_C& rC_bone, EE_U32_t u32_nFrames );
		void RecursivelyGatherChildren( EE_MODEL_ANIMATION_BONE_C& rC_bone, std::vector< std::string >& rco_children );
		//void RecursivelyAddBoneVectors( EE_MODEL_ANIMATION_BONE_C& rC_bone, EE_U32_t u32_frame );
		
		// Jméno objektu
		std::string mS_ObjectName;
		
		EE_MATH_MATRIX4X4_C mC_ArmatureSpaceMatrix, mC_InverseArmatureSpaceMatrix;
		
		// Kosti
		std::map< std::string, EE_MODEL_ANIMATION_BONE_C > mco_Bones;	
		
};

#endif
