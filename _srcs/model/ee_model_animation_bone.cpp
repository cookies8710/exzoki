#include <exzoki/model/ee_model_animation_bone.h>

EE_MODEL_ANIMATION_BONE_C::EE_MODEL_ANIMATION_BONE_C( void )
{
}
		
void EE_MODEL_ANIMATION_BONE_C::Read( EE_SYSTEM_FILE_C& rC_file, EE_U32_t u32_nFrames )
{
	Clear();
	
	// Naètu jméno kosti
	EE_U32_t u32_NChars;
	rC_file.Read( &u32_NChars, sizeof( u32_NChars ) );

	for( EE_U32_t u32_Char( 0 ); u32_Char < u32_NChars; u32_Char++ )
		mS_Name += rC_file.GetChar();			
	EE_FLOAT_t f_X, f_Y, f_Z;
		
	rC_file.Read( &f_X, sizeof( f_X ) );
	rC_file.Read( &f_Y, sizeof( f_Y ) );
	rC_file.Read( &f_Z, sizeof( f_Z ) );
	mC_Head.Set( f_X, f_Y, f_Z );

	rC_file.Read( &f_X, sizeof( f_X ) );
	rC_file.Read( &f_Y, sizeof( f_Y ) );
	rC_file.Read( &f_Z, sizeof( f_Z ) );
	mC_Tail.Set( f_X, f_Y, f_Z );
	
	rC_file.Read( &f_X, sizeof( f_X ) );
	rC_file.Read( &f_Y, sizeof( f_Y ) );
	rC_file.Read( &f_Z, sizeof( f_Z ) );
	mC_ArmatureSpaceHead.Set( f_X, f_Y, f_Z );

	rC_file.Read( &f_X, sizeof( f_X ) );
	rC_file.Read( &f_Y, sizeof( f_Y ) );
	rC_file.Read( &f_Z, sizeof( f_Z ) );
	mC_ArmatureSpaceTail.Set( f_X, f_Y, f_Z );
	
	EE_U32_t u32_Parent;
	rC_file.Read( &u32_Parent, sizeof( u32_Parent ) );
	
	if( u32_Parent )
		mb_HasParent = 1;
	else
		mb_HasParent = 0;
	
	for( EE_U32_t u32_Char( 0 ); u32_Char < u32_Parent; u32_Char++ )
		mS_Parent += rC_file.GetChar();	
	
	EE_U32_t u32_NOfChildren;
	rC_file.Read( &u32_NOfChildren, sizeof( u32_NOfChildren ) );
	
	for( EE_U32_t u32_Child( 0 ); u32_Child < u32_NOfChildren; u32_Child++ )
	{
		EE_U32_t u32_NameLength;
		std::string S_ChildName;
		rC_file.Read( &u32_NameLength, sizeof( u32_NameLength ) );
		for( EE_U32_t u32_Char( 0 ); u32_Char < u32_NameLength; u32_Char++ )
			S_ChildName += rC_file.GetChar();	
		
		mco_Children.push_back( S_ChildName );	
	}	
	
	
	// Naètu transformaèní matice pro jednotlivé framy
	for( EE_U32_t u32_Frame( 0 ); u32_Frame < u32_nFrames; u32_Frame++ )
	{
		EE_MATH_MATRIX4X4_C C_Matrix;
		C_Matrix.Read( rC_file );
		
		mco_Matrices.push_back( C_Matrix );
	}
	
	// Naètu qaterniony pro jednotlivé framy
	for( EE_U32_t u32_Frame( 0 ); u32_Frame < u32_nFrames; u32_Frame++ )
	{
		EE_MATH_QUATERNION_C C_Quaternion;
		C_Quaternion.Read( rC_file );
		
		C_Quaternion.SetComment( "Reading %s - frame %d", mS_Name.c_str(), u32_Frame );
		C_Quaternion.Dump( C_XMLDebugFile );
		
		mco_Quaternions.push_back( C_Quaternion );
	}
	
	
	// 
/*	EE_MATH_VECTOR_C C_RestPosition( mC_Tail - mC_Head ); // ! mC_Head musí být [0,0,0]
	for( EE_U32_t u32_Frame( 0 ); u32_Frame < u32_nFrames; u32_Frame++ )
	{
		mco_BonePositions.push_back( mco_Matrices[ u32_Frame ] * C_RestPosition );	
		
		mco_TotalBonePositions.push_back( EE_MATH_VECTOR_C() );
	}*/
}	

void EE_MODEL_ANIMATION_BONE_C::SetHierarchy( const std::vector< std::string >& crco_hierarchy )
{
	mco_Hierarchy = crco_hierarchy;	
}

const std::vector< std::string >& EE_MODEL_ANIMATION_BONE_C::GetHierarchy( void ) const
{
	return( mco_Hierarchy );	
}

std::string EE_MODEL_ANIMATION_BONE_C::GetName( void ) const
{
	return( mS_Name );
}

const EE_MATH_POINT_C& EE_MODEL_ANIMATION_BONE_C::GetHead( void ) const
{
	return( mC_Head );	
}

const EE_MATH_POINT_C& EE_MODEL_ANIMATION_BONE_C::GetTail( void ) const
{
	return( mC_Tail );	
}

const EE_MATH_POINT_C& EE_MODEL_ANIMATION_BONE_C::GetArmatureSpaceHead( void ) const
{
	return( mC_ArmatureSpaceHead );
}

const EE_MATH_POINT_C& EE_MODEL_ANIMATION_BONE_C::GetArmatureSpaceTail( void ) const
{
	return( mC_ArmatureSpaceTail );
}

EE_BOOL_t EE_MODEL_ANIMATION_BONE_C::HasParent( void ) const
{
	return( mb_HasParent );	
}

std::string EE_MODEL_ANIMATION_BONE_C::GetParent( void ) const
{
	return( mS_Parent );	
}

const std::vector< std::string >& EE_MODEL_ANIMATION_BONE_C::GetChildren( void ) const
{
	return( mco_Children );	
}
		
const std::vector< EE_MATH_MATRIX4X4_C >& EE_MODEL_ANIMATION_BONE_C::GetMatrices( void ) const
{
	return( mco_Matrices );
}

std::vector< EE_MATH_MATRIX4X4_C >& EE_MODEL_ANIMATION_BONE_C::GetMatrices( void )
{
	return( mco_Matrices );
}

std::vector< EE_MATH_QUATERNION_C >& EE_MODEL_ANIMATION_BONE_C::GetQuaternions( void )
{
	return( mco_Quaternions );	
}

const std::vector< EE_MATH_QUATERNION_C >& EE_MODEL_ANIMATION_BONE_C::GetQuaternions( void ) const
{
	return( mco_Quaternions );	
}

std::vector< EE_MATH_VECTOR_C >& EE_MODEL_ANIMATION_BONE_C::GetAnimationPositions( void )
{
	return( mco_AnimationPositions );	
}

const std::vector< EE_MATH_VECTOR_C >& EE_MODEL_ANIMATION_BONE_C::GetAnimationPositions( void ) const
{
	return( mco_AnimationPositions );	
}

std::vector< EE_MATH_VECTOR_C >& EE_MODEL_ANIMATION_BONE_C::GetArmaturePositions( void )
{
	return( mco_ArmaturePositions );	
}

const std::vector< EE_MATH_VECTOR_C >& EE_MODEL_ANIMATION_BONE_C::GetArmaturePositions( void ) const
{
	return( mco_ArmaturePositions );	
}
		
void EE_MODEL_ANIMATION_BONE_C::Clear( void )
{
	mS_Name.clear();
	mco_Matrices.clear();	
	mco_Quaternions.clear();
	mC_Head.Set( 0.0, 0.0, 0.0 );
	mC_Tail.Set( 0.0, 0.0, 0.0 );
	
	mb_HasParent = 0;
	mS_Parent.clear();
	mco_Children.clear();
	mco_Hierarchy.clear();
	mco_AnimationPositions.clear();
	mco_ArmaturePositions.clear();
}

EE_BYTE_t EE_MODEL_ANIMATION_BONE_C::Read( std::ifstream &rC_file )
{}
EE_BYTE_t EE_MODEL_ANIMATION_BONE_C::Write( std::ofstream &rC_file ) const
{}
EE_BYTE_t EE_MODEL_ANIMATION_BONE_C::Dump( std::ofstream &rC_file ) const
{	
	EE_XMLLOADER_TAG_C C_MainTag( "EE_MODEL_ANIMATION_BONE_C" ),
	                   C_HeadTag( "Head" ),
					   C_TailTag( "Tail" ),
					   C_BSMatrix( "BoneSpaceMatrix" ),
					   C_ASMatrix( "ArmatureSpaceMatrix" ),
					   C_IBSMatrix( "InverseBoneSpaceMatrix" ),
					   C_IASMatrix( "InverseArmatureSpaceMatrix" ),
					   C_HeadMulBSMatrix( "Head_MUL_BSMatrix" ),
					   C_TailMulBSMatrix( "Tail_MUL_BSMatrix" );
	EE_XMLLOADER_ATTRIBUTE_C C_Name( "Name", mS_Name.c_str() ), 
			                 C_Parent( "Parent", ( mb_HasParent ) ? mS_Parent.c_str() : "Bone has NO parent" );
	
	C_MainTag.AddParameter( C_Name );
	C_MainTag.AddParameter( C_Parent );	
	
	// Zapíšu hlavní tag		
	C_MainTag.Write( rC_file );
	
	// Zapíšu souøadnice hlavy
	C_HeadTag.Write( rC_file );	
	mC_Head.Dump( rC_file );
	C_HeadTag.WriteClosing( rC_file );
	
	// Zapíšu souøadnice ocasu
	C_TailTag.Write( rC_file );	
	mC_Tail.Dump( rC_file );	
	C_TailTag.WriteClosing( rC_file );
		
	// Uzavøu hlavní tag
	C_MainTag.WriteClosing( rC_file );
}


