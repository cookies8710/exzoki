#ifndef EE_MODEL_ANIMATION_BONE_H
#define EE_MODEL_ANIMATION_BONE_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/math/ee_math_point.h>
#include <exzoki/math/ee_math_matrix4x4.h>
#include <exzoki/math/ee_math_quaternion.h>
#include <string>
#include <exzoki/base/ee_base.h>
#include <exzoki/xmlloader/ee_xmlloader_attribute.h>
#include <exzoki/xmlloader/ee_xmlloader_tag.h>

class EE_MODEL_ANIMATION_BONE_C: public EE_BASE_C
{
	public:
		EE_MODEL_ANIMATION_BONE_C( void );
		
		void Read( EE_SYSTEM_FILE_C& rC_file, EE_U32_t u32_nFrames );	
		
		void SetHierarchy( const std::vector< std::string >& crco_hierarchy );
		const std::vector< std::string >& GetHierarchy( void ) const;
		
		// Get metody
		std::string GetName( void ) const;
		
		const EE_MATH_POINT_C& GetHead( void ) const;
		const EE_MATH_POINT_C& GetTail( void ) const;
		
		const EE_MATH_POINT_C& GetArmatureSpaceHead( void ) const;
		const EE_MATH_POINT_C& GetArmatureSpaceTail( void ) const;
		
		EE_BOOL_t HasParent( void ) const;
		std::string GetParent( void ) const;
		const std::vector< std::string >& GetChildren( void ) const;
				
		std::vector< EE_MATH_MATRIX4X4_C >& GetMatrices( void );
		const std::vector< EE_MATH_MATRIX4X4_C >& GetMatrices( void ) const;
		
		std::vector< EE_MATH_QUATERNION_C >& GetQuaternions( void );
		const std::vector< EE_MATH_QUATERNION_C >& GetQuaternions( void ) const;
		
		std::vector< EE_MATH_VECTOR_C >& GetAnimationPositions( void );
		const std::vector< EE_MATH_VECTOR_C >& GetAnimationPositions( void ) const;
		
		std::vector< EE_MATH_VECTOR_C >& GetArmaturePositions( void );
		const std::vector< EE_MATH_VECTOR_C >& GetArmaturePositions( void ) const;
			
		// Vymaže kost		
		void Clear( void );
		
		// 
		virtual EE_BYTE_t Read( std::ifstream &rC_file );
		virtual EE_BYTE_t Write( std::ofstream &rC_file ) const;
		virtual EE_BYTE_t Dump( std::ofstream &rC_file ) const;		
		
		std::vector< EE_MATH_VECTOR_C > mco_HeadTemp;
		std::vector< EE_MATH_VECTOR_C > mco_TailTemp;
		std::vector< EE_MATH_VECTOR_C > mco_ASPosTemp;
		std::vector< EE_MATH_MATRIX4X4_C > mco_TotMatTemp;
		std::vector< EE_MATH_QUATERNION_C > mco_TotQuatTemp;
		
		std::vector< std::string > mco_HierarchicalChildren;
		
		std::vector< EE_MATH_QUATERNION_C > mco_Quaternions;
	private:			
		std::string mS_Name;
		EE_MATH_POINT_C mC_Head, mC_Tail;
		EE_MATH_POINT_C mC_ArmatureSpaceHead, mC_ArmatureSpaceTail;
		
		EE_BOOL_t mb_HasParent;
		std::string mS_Parent;
		
		
		
		std::vector< std::string > mco_Children;
		std::vector< std::string > mco_Hierarchy;
		
		std::vector< EE_MATH_MATRIX4X4_C > mco_Matrices;
		
		
		std::vector< EE_MATH_VECTOR_C >	mco_AnimationPositions;	
		std::vector< EE_MATH_VECTOR_C >	mco_ArmaturePositions;	
};

#endif
