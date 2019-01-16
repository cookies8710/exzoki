#include <exzoki/model/ee_model_bone.h>

EE_MODEL_BONE_C::EE_MODEL_BONE_C( void ): mu32_NParent( 0 ), mpu32_Parents( 0 ),
                                          mu32_NChildren( 0 ), mpu32_Children( 0 )
{
}

EE_MODEL_BONE_C::~EE_MODEL_BONE_C( void )
{
	Destroy();	
}

EE_MODEL_BONE_C::EE_MODEL_BONE_C( const EE_MODEL_BONE_C& crC_bone )
{
	Create( crC_bone );	
}

EE_MODEL_BONE_C& EE_MODEL_BONE_C::operator=( const EE_MODEL_BONE_C& crC_bone )
{
	if( &crC_bone != this )
	{
		Destroy();
		Create( crC_bone );	
	}
	
	return( *this );	
}
		
void EE_MODEL_BONE_C::Read( EE_SYSTEM_FILE_C& rC_file )
{
	Clear();
	
	// Naètu jméno kosti
	EE_U32_t u32_NChars;
	rC_file.Read( &u32_NChars, sizeof( u32_NChars ) );
	for( EE_U32_t u32_Char( 0 ); u32_Char < u32_NChars; u32_Char++ )
		mS_Name += rC_file.GetChar();
	
	// Naètu souøadnice hlavy
	EE_FLOAT_t f_X, f_Y, f_Z;
	
	rC_file.Read( &f_X, sizeof( f_X ) );	
	rC_file.Read( &f_Y, sizeof( f_Y ) );	
	rC_file.Read( &f_Z, sizeof( f_Z ) );

	mC_Head.Set( f_X, f_Y, f_Z );
	
	// Naètu souøadnice koncové èásti
	rC_file.Read( &f_X, sizeof( f_X ) );	
	rC_file.Read( &f_Y, sizeof( f_Y ) );	
	rC_file.Read( &f_Z, sizeof( f_Z ) );

	mC_Tail.Set( f_X, f_Y, f_Z );
	
	
	// Naètu poèet vertexù
	EE_U32_t u32_NVertices;
	rC_file.Read( &u32_NVertices, sizeof( u32_NVertices ) );
	
	// Naètu vertexy
	EE_U32_t u32_VertexIndex;
	for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < u32_NVertices; u32_Vertex++ )
	{
		rC_file.Read( &u32_VertexIndex, sizeof( u32_VertexIndex ) );
		mco_Vertices.push_back( u32_VertexIndex );	
	}
		
	
}

void EE_MODEL_BONE_C::Draw( const EE_SYSTEM_COLOR_s &crs_headColor, 
		           			const EE_SYSTEM_COLOR_s &crs_tailColor ) const
{
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	glDisable( GL_TEXTURE_2D );
	
	glLineWidth( 5.0 );
	glBegin( GL_LINES );
		glColor4ub( crs_headColor.b_R, crs_headColor.b_G, crs_headColor.b_B, crs_headColor.b_A );
		glVertex3f( mC_Head.GetX(), mC_Head.GetY(), mC_Head.GetZ() );
		
		glColor4ub( crs_tailColor.b_R, crs_tailColor.b_G, crs_tailColor.b_B, crs_tailColor.b_A );
		glVertex3f( mC_Tail.GetX(), mC_Tail.GetY(), mC_Tail.GetZ() );	
	
	glEnd();
	
	glPopAttrib();
	
	return;	
}

const EE_MATH_POINT_C& EE_MODEL_BONE_C::GetHead( void ) const
{	
	return( mC_Head );	
}

const EE_MATH_POINT_C& EE_MODEL_BONE_C::GetTail( void ) const
{	
	return( mC_Tail );	
}

const std::vector< EE_U32_t >& EE_MODEL_BONE_C::GetVertices( void ) const
{
	return( mco_Vertices );
}

std::string EE_MODEL_BONE_C::GetName( void ) const
{
	return( mS_Name );	
}

void EE_MODEL_BONE_C::Clear( void )
{
	Destroy();	
}

EE_BYTE_t EE_MODEL_BONE_C::Dump( std::ofstream &rC_file ) const
{
	EE_XMLLOADER_TAG_C C_MainTag( "EE_MODEL_BONE_C" ),
	                   C_Vertices( "Vertices" ),
					   C_HeadTag( "Head" ),
					   C_TailTag( "Tail" );
	EE_XMLLOADER_ATTRIBUTE_C C_Name( "Name", mS_Name.c_str() );	
	
	std::string S_Data;	
	
	for( EE_U32_t u32_VertexIndex( 0 ); u32_VertexIndex < mco_Vertices.size(); u32_VertexIndex++ )
	{
		EE_CHAR_t ac_Buffer[ 256 ];
		
		S_Data += itoa( mco_Vertices[ u32_VertexIndex ], ac_Buffer, 10 );
		
		if( u32_VertexIndex + 1 != mco_Vertices.size() )
			S_Data += ", ";	
	}
	
	C_MainTag.AddParameter( C_Name );
	
	C_MainTag.Write( rC_file );
	
	C_Vertices.SetData( S_Data.c_str() );
	C_Vertices.Write( rC_file );
	C_Vertices.WriteClosing( rC_file );
	
	C_HeadTag.Write( rC_file );	
	mC_Head.Dump( rC_file );	
	C_HeadTag.WriteClosing( rC_file );
	
	C_TailTag.Write( rC_file );	
	mC_Tail.Dump( rC_file );	
	C_TailTag.WriteClosing( rC_file );
	
	C_MainTag.WriteClosing( rC_file );
}

void EE_MODEL_BONE_C::Destroy( void )
{
	mco_Vertices.clear();
	
	if( mu32_NParent )	
		delete[] mpu32_Parents;
		
	if( mu32_NChildren )	
		delete[] mpu32_Children;
}

void EE_MODEL_BONE_C::Create( const EE_MODEL_BONE_C& crC_bone )
{
	this->mS_Name = crC_bone.mS_Name;
	
	// ??? ID ???
	if( this->mu32_NParent = crC_bone.mu32_NParent )
	{
		this->mpu32_Parents = new EE_U32_t[ this->mu32_NParent ];	
		memcpy( this->mpu32_Parents, crC_bone.mpu32_Parents, sizeof( EE_U32_t ) * this->mu32_NParent );
	}
	
	if( this->mu32_NChildren = crC_bone.mu32_NChildren )
	{
		this->mpu32_Children = new EE_U32_t[ this->mu32_NChildren ];	
		memcpy( this->mpu32_Children, crC_bone.mpu32_Children, sizeof( EE_U32_t ) * this->mu32_NParent );
	}	
	
	this->mco_Vertices = crC_bone.mco_Vertices;
	
	this->mC_Head = crC_bone.mC_Head;
	this->mC_Tail = crC_bone.mC_Tail;
}
