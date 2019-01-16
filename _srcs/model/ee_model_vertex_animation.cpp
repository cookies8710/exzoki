#include <exzoki/model/ee_model_vertex_animation.h>

EE_MODEL_VERTEX_ANIMATION_C::EE_MODEL_VERTEX_ANIMATION_C(): mu16_NFrames( 0 ),
                                                     mf_FrameRate( 0.0 ), 
													 mu32_NVertices( 0 )
{
}

EE_MODEL_VERTEX_ANIMATION_C::EE_MODEL_VERTEX_ANIMATION_C( EE_CCSTRING_t ccs_path )
{
	Load( ccs_path );	
}
		
void EE_MODEL_VERTEX_ANIMATION_C::Load( EE_CCSTRING_t ccs_path )
{
	Clear();
	
	// Otevøu soubor
	EE_SYSTEM_FILE_C C_File( ccs_path, EE_SYSTEM_FILE_READ, EE_SYSTEM_FILE_BINARY );
	
	// Naètu a zkontroluju hlavièku
	std::string S_Header;
	for( EE_BYTE_t b_Char( 0 ); b_Char < EE_MODEL_VERTEX_ANIMATION_TVA_n::cS_Header.size(); b_Char++ )	
		S_Header += C_File.GetChar();
	
	
	if( S_Header != EE_MODEL_VERTEX_ANIMATION_TVA_n::cS_Header )
		EE_ERROR_C( "EE_MODEL_VERTEX_ANIMATION_C", "Load", EE_ERROR_CODES_n::cS_WrongFileHeader, "File \"%s\" header = \"%s\"",
		            ccs_path, S_Header.c_str() );
	
	// Naètu a zkontroluju verzi
	EE_U16_t u16_Version;
	C_File.Read( &u16_Version, 2 );
	if( u16_Version != EE_MODEL_VERTEX_ANIMATION_TVA_n::cu16_Version )
		EE_ERROR_C( "EE_MODEL_VERTEX_ANIMATION_C", "Load", EE_ERROR_CODES_n::cS_BadVersion, "File \"%s\" version = %d; version needed = %d",
		            ccs_path, u16_Version, EE_MODEL_VERTEX_ANIMATION_TVA_n::cu16_Version );
		 
	// Naètu jméno animace           
	EE_BYTE_t b_AnimationNameLength;
	C_File.Read( &b_AnimationNameLength, 1 );
	
	for( EE_BYTE_t b_Char( 0 ); b_Char < b_AnimationNameLength; b_Char++ )
		mS_Name += C_File.GetChar();
		
	// Naètu poèet framù
	C_File.Read( &mu16_NFrames, 2 );
C_DebugFile << "nframes="<<mu16_NFrames<<endl;	
	// Naètu framerate
	C_File.Read( &mf_FrameRate, 4 );
C_DebugFile << "framerate="<<mf_FrameRate<<endl;
	// Naètu poèet vertexù
	C_File.Read( &mu32_NVertices, 4 );
C_DebugFile << "nvertices="<<mu32_NVertices<<endl;
	// Naètu jednotlivé framy
	for( EE_U16_t u16_Frame( 0 ); u16_Frame < mu16_NFrames; u16_Frame++ ) 
	{
		EE_MODEL_VERTEX_ANIMATION_FRAME_t t_Frame;
		
		for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < mu32_NVertices; u32_Vertex++ ) 
		{
			EE_MODEL_VERTEX_ANIMATION_VERTEX_t	t_Vertex;
			
			t_Vertex.Read( C_File );
			
			t_Frame.push_back( t_Vertex );
		}
		
		mco_Vertices.push_back( t_Frame );
	}
	
	C_File.Close();
}
		
std::string EE_MODEL_VERTEX_ANIMATION_C::GetName( void ) const
{
	return( mS_Name );	
}

EE_U16_t EE_MODEL_VERTEX_ANIMATION_C::GetNFrames( void ) const
{
	return( mu16_NFrames );	
}

EE_FLOAT_t EE_MODEL_VERTEX_ANIMATION_C::GetFrameRate( void ) const
{
	return( mf_FrameRate );	
}

EE_U32_t EE_MODEL_VERTEX_ANIMATION_C::GetNVertices( void ) const
{
	return( mu32_NVertices );	
}

const EE_MODEL_VERTEX_ANIMATION_FRAME_t& EE_MODEL_VERTEX_ANIMATION_C::GetVertexFrame( EE_U16_t u16_frame ) const
{
	if( u16_frame < mu16_NFrames )
		return( mco_Vertices[ u16_frame ] );
	else
		EE_ERROR_C( "EE_MODEL_VERTEX_ANIMATION_C", 
		            "GetVertexFrame", 
					EE_ERROR_CODES_n::cS_BadIndex, 
					"Index desired = %d; Number of frames = %d", u16_frame, mu16_NFrames );	
}
		
void EE_MODEL_VERTEX_ANIMATION_C::Clear( void )
{
	mS_Name.clear();
	mu16_NFrames= 0;
	mf_FrameRate = 0.0;
	mu32_NVertices = 0;
	mco_Vertices.clear();	
}
	
