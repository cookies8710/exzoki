#include <exzoki/model/ee_model_animation_armature.h>

EE_MODEL_ANIMATION_ARMATURE_C::EE_MODEL_ANIMATION_ARMATURE_C( void )
{
}
		
void EE_MODEL_ANIMATION_ARMATURE_C::Read( EE_SYSTEM_FILE_C& rC_file, EE_U32_t u32_nFrames )
{
	Clear();
	
	// Naètu jméno objektu
	EE_U32_t u32_NChars;
	rC_file.Read( &u32_NChars, sizeof( u32_NChars ) );
	for( EE_U32_t u32_Char( 0 ); u32_Char < u32_NChars; u32_Char++ )
		mS_ObjectName += rC_file.GetChar();

	mC_ArmatureSpaceMatrix.Read( rC_file );
	
	mC_InverseArmatureSpaceMatrix.Read( rC_file );
	
	EE_U32_t u32_NBones;
	rC_file.Read( &u32_NBones, sizeof( u32_NBones ) );
	
	// Naètu kosti
	for( EE_U32_t u32_Bone( 0 ); u32_Bone < u32_NBones; u32_Bone++ )
	{
		EE_MODEL_ANIMATION_BONE_C C_Bone;
		
		C_Bone.Read( rC_file, u32_nFrames );
					
		mco_Bones[ C_Bone.GetName() ] = C_Bone;
	}
	
	// Sestavení hierarchie kostí
	std::map< std::string, EE_MODEL_ANIMATION_BONE_C >::iterator I_Bone( mco_Bones.begin() ),
	                                                             I_BoneEnd( mco_Bones.end() );
	while( I_Bone != I_BoneEnd )
	{
		// Úložištì pro seznam pøedkù a potomkù
		std::vector< std::string > co_Hierarchy; 
		co_Hierarchy.push_back( I_Bone->second.GetName() );
			
		// Sestavení hierarchie	
		const EE_MODEL_ANIMATION_BONE_C* cpC_RootBone( &I_Bone->second );
		while( cpC_RootBone->HasParent() )
		{
			co_Hierarchy.push_back( cpC_RootBone->GetParent() );
			cpC_RootBone = &GetBone( cpC_RootBone->GetParent().c_str() );
		}	
		
		// Obrátím hierarchii, takže na zaèátku bude root, vlastní konci bude až na konci		
		std::vector< std::string > co_ReversedHierarchy; 
		EE_U32_t u32_HierarchySize( co_Hierarchy.size() );
		for( EE_U32_t u32_HierarchyBone( 0 ); u32_HierarchyBone < u32_HierarchySize; u32_HierarchyBone++ )
			co_ReversedHierarchy.push_back( co_Hierarchy[ u32_HierarchySize - 1 - u32_HierarchyBone ] );
		
		// Uložím ke kosti a jdu na další
		I_Bone->second.SetHierarchy( co_ReversedHierarchy );
		
		RecursivelyGatherChildren( I_Bone->second, I_Bone->second.mco_HierarchicalChildren );
				
		I_Bone++;
	}
	
	
	/*for( EE_U32_t u32_Frame( 0 ); u32_Frame < u32_nFrames; u32_Frame++ )
	{
		std::map< std::string, EE_MODEL_ANIMATION_BONE_C >::iterator I_Bone( mco_Bones.begin() ),
	                                                             	 I_BoneEnd( mco_Bones.end() );	
	    while( I_Bone != I_BoneEnd )
	    {	
			I_Bone->second.mco_HeadTemp.push_back( I_Bone->second.GetArmatureSpaceHead() );
			I_Bone->second.mco_TailTemp.push_back( I_Bone->second.GetArmatureSpaceTail() );
			I_Bone->second.mco_ASPosTemp.push_back( EE_MATH_VECTOR_C() );
			EE_MATH_MATRIX4X4_C C_IdentityMatrix;
			C_IdentityMatrix.LoadIdentity();			
			I_Bone->second.mco_TotMatTemp.push_back( C_IdentityMatrix );
			
			EE_MATH_QUATERNION_C C_IdentityQuaternion;
			C_IdentityQuaternion.LoadMulIdentity();	
			I_Bone->second.mco_TotQuatTemp.push_back( C_IdentityQuaternion );
					
			I_Bone++;	
		}
	}
	
	I_Bone = mco_Bones.begin();
	I_BoneEnd = mco_Bones.end();	
	
	while( I_Bone != I_BoneEnd )
	{	
		if( !I_Bone->second.HasParent() )
			RecursivelyMultiplyBones( I_Bone->second, u32_nFrames );
		I_Bone++;	
	}*/
	
	return;
}

std::string EE_MODEL_ANIMATION_ARMATURE_C::GetObjectName( void ) const
{
	return( mS_ObjectName );	
}

EE_MODEL_ANIMATION_BONE_C& EE_MODEL_ANIMATION_ARMATURE_C::GetBone( EE_CCSTRING_t ccs_boneName )
{
	std::map< std::string, EE_MODEL_ANIMATION_BONE_C >::iterator I_Bone( mco_Bones.find( std::string( ccs_boneName ) ) );
	if( I_Bone != mco_Bones.end() )	
		return( I_Bone->second );	
	else
		EE_ERROR_C( "EE_MODEL_ANIMATION_ARMATURE_C", "GetBone", EE_ERROR_CODES_n::cS_BoneNotFound, ccs_boneName );	
}
		
const EE_MODEL_ANIMATION_BONE_C& EE_MODEL_ANIMATION_ARMATURE_C::GetBone( EE_CCSTRING_t ccs_boneName ) const
{
	std::map< std::string, EE_MODEL_ANIMATION_BONE_C >::const_iterator cI_Bone( mco_Bones.find( std::string( ccs_boneName ) ) );
	if( cI_Bone != mco_Bones.end() )	
		return( cI_Bone->second );	
	else
		EE_ERROR_C( "EE_MODEL_ANIMATION_ARMATURE_C", "GetBone", EE_ERROR_CODES_n::cS_BoneNotFound, ccs_boneName );
}

const EE_MATH_MATRIX4X4_C& EE_MODEL_ANIMATION_ARMATURE_C::GetArmatureMatrix( void ) const
{
	return( mC_ArmatureSpaceMatrix );	
}

const EE_MATH_MATRIX4X4_C& EE_MODEL_ANIMATION_ARMATURE_C::GetInverseArmatureMatrix( void ) const
{
	return( mC_InverseArmatureSpaceMatrix );	
}
		
void EE_MODEL_ANIMATION_ARMATURE_C::Clear( void )
{
	mS_ObjectName.clear();
	mco_Bones.clear();	
}

EE_BYTE_t EE_MODEL_ANIMATION_ARMATURE_C::Dump( std::ofstream &rC_file ) const
{
	EE_XMLLOADER_TAG_C C_MainTag( "EE_MODEL_ANIMATION_ARMATURE_C" ),
	                   C_ArmatureMatrix( "ArmatureMatrix" ),
					   C_InverseArmatureMatrix( "InverseArmatureMatrix" ),
					   C_Bone( "Bone" );
	EE_XMLLOADER_ATTRIBUTE_C C_ObjectName( "Object", mS_ObjectName.c_str() ),
	                         C_NOfBones( "NumberOfBones", (EE_S32_t)mco_Bones.size() ),
							 C_BoneName( "Name", "" );
	
	// Hlavní tag
	C_MainTag.AddParameter( C_ObjectName );
	C_MainTag.AddParameter( C_NOfBones );
	
	C_MainTag.Write( rC_file );
	
	// Armature matrix
	C_ArmatureMatrix.Write( rC_file );
	mC_ArmatureSpaceMatrix.Dump( rC_file );
	C_ArmatureMatrix.WriteClosing( rC_file );
	
	// Inverse armature matrix
	C_InverseArmatureMatrix.Write( rC_file );
	mC_InverseArmatureSpaceMatrix.Dump( rC_file );
	C_InverseArmatureMatrix.WriteClosing( rC_file );
	
	// Kosti
	std::map< std::string, EE_MODEL_ANIMATION_BONE_C >::const_iterator cI_Bone( mco_Bones.begin() ), cI_BoneEnd( mco_Bones.end() );		
	while( cI_Bone != cI_BoneEnd )
	{
		C_BoneName.SetValue( cI_Bone->second.GetName().c_str() );
		
		C_Bone.DeleteAttributes();
		C_Bone.AddParameter( C_BoneName );
			   
		C_Bone.Write( rC_file );
		cI_Bone->second.Dump( rC_file );
		C_Bone.WriteClosing( rC_file );
		
		cI_Bone++;
	}
	
	// Uzavøu hlavní tag
	C_MainTag.WriteClosing( rC_file );	
	
}

void EE_MODEL_ANIMATION_ARMATURE_C::RecursivelyMultiplyBones( EE_MODEL_ANIMATION_BONE_C& rC_bone, EE_U32_t u32_nFrames )
{
	std::vector< std::string > co_Hierarchy( rC_bone.mco_HierarchicalChildren );
	EE_U32_t u32_HierarchySize( co_Hierarchy.size() );
		
	for( EE_U32_t u32_Frame( 0 ); u32_Frame < u32_nFrames; u32_Frame++ )
	{
		const EE_MATH_MATRIX4X4_C& crC_Matrix( rC_bone.GetMatrices()[ u32_Frame ] );
								
		rC_bone.mco_TotMatTemp[ u32_Frame ] = rC_bone.mco_TotMatTemp[ u32_Frame ] * crC_Matrix;
		rC_bone.mco_TotQuatTemp[ u32_Frame ] = rC_bone.mco_TotQuatTemp[ u32_Frame ] * rC_bone.mco_Quaternions[ u32_Frame ];
				EE_MATH_VECTOR_C C_RotatedBone( rC_bone.mco_TotQuatTemp[ u32_Frame ].ConvertToMatrix() * rC_bone.mco_TailTemp[ u32_Frame ] );
		
		rC_bone.mco_HeadTemp[ u32_Frame ] = rC_bone.mco_TotQuatTemp[ u32_Frame ].ConvertToMatrix() * rC_bone.mco_HeadTemp[ u32_Frame ];	
		rC_bone.mco_TailTemp[ u32_Frame ] = rC_bone.mco_TotQuatTemp[ u32_Frame ].ConvertToMatrix() * rC_bone.mco_TailTemp[ u32_Frame ];			
				
		for( EE_U32_t u32_HierarchyMember( 0 ); u32_HierarchyMember < u32_HierarchySize; u32_HierarchyMember++ )
		{
			EE_MODEL_ANIMATION_BONE_C& rC_ChildBone( GetBone( co_Hierarchy[ u32_HierarchyMember ].c_str() ) );
						
			rC_ChildBone.mco_HeadTemp[ u32_Frame ] = rC_bone.mco_TotQuatTemp[ u32_Frame ].ConvertToMatrix() * rC_ChildBone.mco_HeadTemp[ u32_Frame ];
			rC_ChildBone.mco_TailTemp[ u32_Frame ] = rC_bone.mco_TotQuatTemp[ u32_Frame ].ConvertToMatrix() * rC_ChildBone.mco_TailTemp[ u32_Frame ];
			
			rC_ChildBone.mco_HeadTemp[ u32_Frame ] = rC_ChildBone.mco_HeadTemp[ u32_Frame ] - C_RotatedBone;
			rC_ChildBone.mco_TailTemp[ u32_Frame ] = rC_ChildBone.mco_TailTemp[ u32_Frame ] - C_RotatedBone;
			
			rC_ChildBone.mco_ASPosTemp[ u32_Frame ] = rC_ChildBone.mco_ASPosTemp[ u32_Frame ] +	C_RotatedBone;	
			
			rC_ChildBone.mco_TotMatTemp[ u32_Frame ] = rC_bone.mco_TotMatTemp[ u32_Frame ];	
			rC_ChildBone.mco_TotQuatTemp[ u32_Frame ] = rC_bone.mco_TotQuatTemp[ u32_Frame ];	
		}			
	}
	

	std::vector< std::string > co_Hierarchy2( rC_bone.GetChildren() );
	for(int i(0);i<co_Hierarchy2.size(); i++)
		RecursivelyMultiplyBones( GetBone( co_Hierarchy2[ i ].c_str() ), u32_nFrames );	
}

void EE_MODEL_ANIMATION_ARMATURE_C::RecursivelyGatherChildren( EE_MODEL_ANIMATION_BONE_C& rC_bone, std::vector< std::string >& rco_children )
{
	std::vector< std::string > co_Children( rC_bone.GetChildren() );
	EE_U32_t u32_NChildren( co_Children.size() );
	
	for( EE_U32_t u32_Child( 0 ); u32_Child < u32_NChildren; u32_Child++ )
	{
		rco_children.push_back( co_Children[ u32_Child ] );	
		RecursivelyGatherChildren( GetBone( co_Children[ u32_Child ].c_str() ), rco_children );
	}
	
	return;
}
