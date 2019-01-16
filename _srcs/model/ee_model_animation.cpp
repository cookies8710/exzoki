#include <exzoki/model/ee_model_animation.h>

EE_MODEL_ANIMATION_C::EE_MODEL_ANIMATION_C( void )
{
}

EE_MODEL_ANIMATION_C::EE_MODEL_ANIMATION_C( EE_CCSTRING_t ccs_path )
{
	Load( ccs_path );	
}
		
void EE_MODEL_ANIMATION_C::Load( EE_CCSTRING_t ccs_path )
{
	Clear();
	
	EE_SYSTEM_FILE_C C_File( ccs_path, EE_SYSTEM_FILE_READ, EE_SYSTEM_FILE_BINARY );	
	
	EE_U32_t u32_HeaderSize( EE_MODEL_ANIMATION_TAN_n::cS_Header.size() );
 	std::string S_Header;
 	for( EE_U32_t u32_Char( 0 ); u32_Char < u32_HeaderSize; u32_Char++ )
  		S_Header += C_File.GetChar();
 	if( S_Header != EE_MODEL_ANIMATION_TAN_n::cS_Header )
  		EE_ERROR_C( "EE_MODEL_ANIMATION_C", "Load", EE_ERROR_CODES_n::cS_WrongFileHeader, ccs_path );
 	// Kontrola verze
 	EE_U16_t u16_Version;
 	C_File.Read( &u16_Version, sizeof( u16_Version ) );
 	if( u16_Version != EE_MODEL_ANIMATION_TAN_n::cu16_Version )
	 	EE_ERROR_C( "EE_MODEL_ANIMATION_C", 
		            "Load", 
					EE_ERROR_CODES_n::cS_BadVersion, 
					"Version needed: %d; File \"%s\" version: %d", 
					EE_MODEL_ANIMATION_TAN_n::cu16_Version, ccs_path, u16_Version );
	
	// Naètu jméno animace
	EE_U32_t u32_NChars;
	C_File.Read( &u32_NChars, sizeof( u32_NChars ) );
	for( EE_U32_t u32_Char( 0 ); u32_Char < u32_NChars; u32_Char++ )
		mS_Name += C_File.GetChar();

	// Naètu poèet framù
	C_File.Read( &mu32_NFrames, sizeof( mu32_NFrames ) );

	// Naètu framerate
	C_File.Read( &mf_FrameRate, sizeof( mf_FrameRate ) );
	
	// Naètu armatury
	EE_U32_t u32_NArmatures;
	C_File.Read( &u32_NArmatures, sizeof( u32_NArmatures ) );

	for( EE_U32_t u32_Armature( 0 ); u32_Armature < u32_NArmatures; u32_Armature++ )
	{
		EE_MODEL_ANIMATION_ARMATURE_C C_Armature;
	
		C_Armature.Read( C_File, mu32_NFrames );
				
		//C_Armature.Dump( C_XMLDebugFile );
		
		mco_Armatures[ C_Armature.GetObjectName() ] =  C_Armature;

	}

	return;
}

std::string EE_MODEL_ANIMATION_C::GetName( void ) const
{
	return( mS_Name );	
}

EE_U32_t EE_MODEL_ANIMATION_C::GetNFrames( void ) const
{
	return( mu32_NFrames );	
}

EE_FLOAT_t EE_MODEL_ANIMATION_C::GetFrameRate( void ) const
{
	return( mf_FrameRate );	
}

const EE_MODEL_ANIMATION_ARMATURE_C& EE_MODEL_ANIMATION_C::GetSkeleton( EE_CCSTRING_t ccs_objectName ) const
{
	std::map< std::string, EE_MODEL_ANIMATION_ARMATURE_C >::const_iterator cI_Armature( mco_Armatures.find( std::string( ccs_objectName ) ) );
	if( cI_Armature != mco_Armatures.end() )
		return( cI_Armature->second );	
	else
		EE_ERROR_C( "EE_MODEL_ANIMATION_C", "GetSkeleton", EE_ERROR_CODES_n::cS_ArmatureNotFound, ccs_objectName );	
}

const EE_MODEL_ANIMATION_BONE_C& EE_MODEL_ANIMATION_C::GetBone( EE_CCSTRING_t ccs_objectName, EE_CCSTRING_t ccs_boneName ) const
{
	std::map< std::string, EE_MODEL_ANIMATION_ARMATURE_C >::const_iterator cI_Armature( mco_Armatures.find( std::string( ccs_objectName ) ) );
	if( cI_Armature != mco_Armatures.end() )
		return( cI_Armature->second.GetBone( ccs_boneName ) );	
	else
		EE_ERROR_C( "EE_MODEL_ANIMATION_C", "GetBone", EE_ERROR_CODES_n::cS_ArmatureNotFound, ccs_objectName );
}
		
void EE_MODEL_ANIMATION_C::Clear( void )
{
	mS_Name.clear();
	mu32_NFrames = 0;
	mf_FrameRate = 0.0;
	mco_Armatures.clear();	
}
