#include <exzoki/model/ee_model_object.h>

EE_MODEL_OBJECT_C::EE_MODEL_OBJECT_C( void ): mu32_NVertices( 0 ),
                                              mpf_Vertices( EE_NULL ),
                                              mu32_NTexCoords( 0 ),
                                              mpf_TexCoords( EE_NULL ),
                                              mpu32_VertexBones( EE_NULL )
{
}

EE_MODEL_OBJECT_C::EE_MODEL_OBJECT_C( const EE_MODEL_OBJECT_C& crC_object ): mu32_NVertices( 0 ),
                                                                             mpf_Vertices( EE_NULL ),
                                                                             mu32_NTexCoords( 0 ),
                                                                             mpf_TexCoords( EE_NULL ),
                                              								 mpu32_VertexBones( EE_NULL )
{
	Create( crC_object );	
}

EE_MODEL_OBJECT_C& EE_MODEL_OBJECT_C::operator=( const EE_MODEL_OBJECT_C& crC_object )
{
	if( &crC_object != this )
	{
		Destroy();
		Create( crC_object );
	}
	
	return( *this );	
}

EE_MODEL_OBJECT_C::~EE_MODEL_OBJECT_C( void )
{
	Destroy();	
}

		
void EE_MODEL_OBJECT_C::Read( EE_SYSTEM_FILE_C& rC_file )
{
	Clear();
	
	std::vector< EE_MODEL_VERTEX_C > co_Vertices;
	std::vector< EE_MODEL_FACE_C > co_Faces;
	std::vector< EE_MODEL_TEXCOORD_C > co_TexCoords;
	std::vector< EE_MODEL_OBJECT_MATERIAL_C > co_Materials;
	
	EE_U32_t u32_NFaces;
	
//	EE_LOG_C::Get().Write( "Reading object name..." );
	
	// Naètu jméno objektu
	EE_U32_t u32_NChars;
	rC_file.Read( &u32_NChars, sizeof( u32_NChars ) );
	for( EE_U32_t u32_Char( 0 ); u32_Char < u32_NChars; u32_Char++ )
		mS_Name += rC_file.GetChar();
	
//	EE_LOG_C::Get().Write( "OK, Name = %s\n", mS_Name.c_str() );
	
	// Naètu poèty vertexù, facù a texturových koordinát
	rC_file.Read( &mu32_NVertices, sizeof( mu32_NVertices ) );
	rC_file.Read( &u32_NFaces, sizeof( u32_NFaces ) );
	rC_file.Read( &mu32_NTexCoords, sizeof( mu32_NTexCoords ) );
	
	//EE_LOG_C::Get().Write( "Object has: %d vertices, %d faces, %d tex coords\n", mu32_NVertices, u32_NFaces, mu32_NTexCoords );
	
//	EE_LOG_C::Get().Write( "Reading vertices...\n" );
	// Naètu vertexy
	EE_MODEL_VERTEX_C C_Vertex;
	for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < mu32_NVertices; u32_Vertex++ )
	{
		C_Vertex.Read( rC_file );
		co_Vertices.push_back( C_Vertex );
	}
		
	//EE_LOG_C::Get().Write( "Reading faces...\n" );
	// Naètu facy
	EE_MODEL_FACE_C C_Face;
	for( EE_U32_t u32_Face( 0 ); u32_Face < u32_NFaces; u32_Face++ )
	{
		C_Face.Read( rC_file );
		co_Faces.push_back( C_Face );
	}
		
	//EE_LOG_C::Get().Write( "Reading tex coords...\n" );
	// Naètu texturové koordináty	
	EE_MODEL_TEXCOORD_C C_TexCoord;
	for( EE_U32_t u32_TexCoord( 0 ); u32_TexCoord < mu32_NTexCoords; u32_TexCoord++ )
	{
		C_TexCoord.Read( rC_file );
		co_TexCoords.push_back( C_TexCoord );
	}
	
	// Naètu poèet facù bez materiálu
	EE_U32_t u32_NFacesWithoutMaterial;
	rC_file.Read( &u32_NFacesWithoutMaterial, sizeof( u32_NFacesWithoutMaterial ) );

	
	// Naètu materiály
	EE_U32_t u32_NMaterials;
	rC_file.Read( &u32_NMaterials, sizeof( u32_NMaterials ) );
	
//	EE_LOG_C::Get().Write( "Object has %d materials\nReading materials...\n", u32_NMaterials );
	
	EE_MODEL_OBJECT_MATERIAL_C C_Material;
	for( EE_U32_t u32_Material( 0 ); u32_Material < u32_NMaterials; u32_Material++ )
	{
		C_Material.Read( rC_file );
		co_Materials.push_back( C_Material );
	}
	
	// Naètu kosti, pokud jsou
	EE_U32_t u32_NBones;
	rC_file.Read( &u32_NBones, sizeof( u32_NBones ) );
	
//	EE_LOG_C::Get().Write( "Object has %d bones\nReading bones...", u32_NBones );
	
	for( EE_U32_t u32_Bone( 0 ); u32_Bone < u32_NBones; u32_Bone++ )
	{
		EE_MODEL_BONE_C C_Bone; 
		
		C_Bone.Read( rC_file );	
		
		//C_Bone.Dump( C_XMLDebugFile );
		
		mco_Bones.push_back( C_Bone );		
	}
	
	// Alokuju pamì pro vertexy - potøebuju 3 * sizeof( float ) * poèet_vertexù bajtù
	mpf_Vertices = new EE_FLOAT_t[ mu32_NVertices * 3 ];
	// Vytvoøím pole vertexù
	for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < mu32_NVertices; u32_Vertex++ )
	{
		mpf_Vertices[ u32_Vertex * 3 + 0 ] = co_Vertices[ u32_Vertex ].GetX();
		mpf_Vertices[ u32_Vertex * 3 + 1 ] = co_Vertices[ u32_Vertex ].GetY();
		mpf_Vertices[ u32_Vertex * 3 + 2 ] = co_Vertices[ u32_Vertex ].GetZ();
	}
	co_Vertices.clear();
	
	// Alokuju pamì pro texturové koordináty - potøebuju 2 * sizeof( float ) * poèet_texcoordù bajtù
	mpf_TexCoords = new EE_FLOAT_t[ mu32_NTexCoords * 2 ];
	// Vytvoøím pole texcoordù
	for( EE_U32_t u32_TexCoord( 0 ); u32_TexCoord < mu32_NTexCoords; u32_TexCoord++ )
	{
		mpf_TexCoords[ u32_TexCoord * 2 + 0 ] = co_TexCoords[ u32_TexCoord ].GetU();
		mpf_TexCoords[ u32_TexCoord * 2 + 1 ] = co_TexCoords[ u32_TexCoord ].GetV();
	}
	co_TexCoords.clear();
	
	// Pokud jsou nìjaké facy bez materiálu, vytvoøím mesh
	if( u32_NFacesWithoutMaterial )
	{
		EE_MODEL_OBJECT_MESH_C C_Mesh;
		
		C_Mesh.SetNFaces( u32_NFacesWithoutMaterial );
		// Alokuju místo pro vertex indexy - potøebuju 3 * sizeof( unsigned long int ) * poèet_facù bajtù
		EE_PU32_t pu32_VertexIndices = new EE_U32_t[ u32_NFacesWithoutMaterial * 3 ];	
		// Nakopíruju tam vertex indexy
		for( EE_U32_t u32_Face( 0 ); u32_Face < u32_NFacesWithoutMaterial; u32_Face++ )
		{
			pu32_VertexIndices[ u32_Face * 3 + 0 ] = co_Faces[ u32_Face ].GetVertexIndex( 0 );	
			pu32_VertexIndices[ u32_Face * 3 + 1 ]	= co_Faces[ u32_Face ].GetVertexIndex( 1 );	
			pu32_VertexIndices[ u32_Face * 3 + 2 ]	= co_Faces[ u32_Face ].GetVertexIndex( 2 );	
		}
		// Pøedám to meshi
		C_Mesh.SetVertexIndices( pu32_VertexIndices );
		// Smažu alokovanou pamì
		delete[] pu32_VertexIndices;
	
		// Pøidám mesh k ostatním
		mco_Meshes.push_back( C_Mesh );
	}
	
	EE_U32_t u32_FacesProcessed = u32_NFacesWithoutMaterial;

	// Projdu všechny object materiály a vytvoøím meshe
	std::vector< EE_MODEL_OBJECT_MATERIAL_C >::const_iterator cI_ObjectMaterial = co_Materials.begin(),
	                                                          cI_ObjectMaterialEnd = co_Materials.end();
	EE_PU32_t pu32_VertexIndices = EE_NULL,
	          pu32_TexCoordIndices = EE_NULL;	
	while( cI_ObjectMaterial != cI_ObjectMaterialEnd )
	{
		EE_MODEL_OBJECT_MESH_C C_Mesh;
		
		C_Mesh.SetMaterialIndex( cI_ObjectMaterial->GetMaterialIndex() );
		C_Mesh.SetNFaces( cI_ObjectMaterial->GetNFaces() );
		// Alokuju místo pro vertex indexy
		pu32_VertexIndices = new EE_U32_t[ cI_ObjectMaterial->GetNFaces() * 3 ];	
		// Nakopíruju tam vertex indexy
		for( EE_U32_t u32_Face( 0 ); u32_Face < cI_ObjectMaterial->GetNFaces(); u32_Face++ )
		{
			pu32_VertexIndices[ u32_Face * 3 + 0 ] = co_Faces[ u32_Face + u32_FacesProcessed ].GetVertexIndex( 0 );	
			pu32_VertexIndices[ u32_Face * 3 + 1 ]	= co_Faces[ u32_Face + u32_FacesProcessed ].GetVertexIndex( 1 );	
			pu32_VertexIndices[ u32_Face * 3 + 2 ]	= co_Faces[ u32_Face + u32_FacesProcessed ].GetVertexIndex( 2 );	
		}
		// Pøedám to meshi
		C_Mesh.SetVertexIndices( pu32_VertexIndices );
		
		u32_FacesProcessed += cI_ObjectMaterial->GetNFaces();
		
		// Pokud má objekt materiál i texturové koordináty, zpracuju i je
		if( cI_ObjectMaterial->HasTexCoords() )
		{
			pu32_TexCoordIndices = new EE_U32_t[ cI_ObjectMaterial->GetNFaces() * 3 ];	
			for( EE_U32_t u32_Face( 0 ); u32_Face < cI_ObjectMaterial->GetNFaces(); u32_Face++ )
			{
				pu32_TexCoordIndices[ u32_Face * 3 + 0 ] = cI_ObjectMaterial->GetTexCoords()[ u32_Face ].u32_VertexTexCoordA;	
				pu32_TexCoordIndices[ u32_Face * 3 + 1 ] = cI_ObjectMaterial->GetTexCoords()[ u32_Face ].u32_VertexTexCoordB;	
				pu32_TexCoordIndices[ u32_Face * 3 + 2 ] = cI_ObjectMaterial->GetTexCoords()[ u32_Face ].u32_VertexTexCoordC;	
			}
			C_Mesh.SetTexCoordIndices( pu32_TexCoordIndices );
		}
		
		// Pøidám k vertexùm ID kostí
		EE_U32_t u32_NBones( mco_Bones.size() );
		mpu32_VertexBones = new EE_U32_t[ mu32_NVertices ];
		mpb_VertexBones = new EE_BYTE_t[ mu32_NVertices ];
		
		// Vynuluju
		for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < mu32_NVertices; u32_Vertex++ )
			mpb_VertexBones[ u32_Vertex ] = 0;
			
		for( EE_U32_t u32_BoneID( 0 ); u32_BoneID < u32_NBones; u32_BoneID++ )
		{
			const std::vector< EE_U32_t >& crco_Vertices( mco_Bones[ u32_BoneID ].GetVertices() );
			EE_U32_t u32_NVertices( crco_Vertices.size() );
			for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < u32_NVertices; u32_Vertex++ )
			{
				EE_U32_t u32_VertexIndex( crco_Vertices[ u32_Vertex ] );
				
				if( u32_VertexIndex >= mu32_NVertices )
					EE_ERROR_C( "EE_MODEL_OBJECT_C", "Read", EE_ERROR_CODES_n::cS_BadIndex, "Bad bone vertex index" );
				
				mpu32_VertexBones[ u32_VertexIndex ] = u32_BoneID;
				mpb_VertexBones[ u32_VertexIndex ] = 1;
			}
		}
		
		// Uklidím po sobì
		delete[] pu32_VertexIndices;
		pu32_VertexIndices = EE_NULL;
		delete[] pu32_TexCoordIndices;
		pu32_TexCoordIndices = EE_NULL;
		
		// Pøidám mesh k ostatním
		mco_Meshes.push_back( C_Mesh );
		
		cI_ObjectMaterial++;	
	}
}

void EE_MODEL_OBJECT_C::SetNVertices( EE_U32_t u32_nVerts )
{
    mu32_NVertices = u32_nVerts;    
}

void EE_MODEL_OBJECT_C::SetVertices( const EE_PFLOAT_t pf_vertices )
{
    mpf_Vertices = new EE_FLOAT_t[ mu32_NVertices * 3 ];   
    memcpy( mpf_Vertices, pf_vertices, mu32_NVertices * 3 * sizeof( EE_FLOAT_t ) ); 
}

void EE_MODEL_OBJECT_C::SetNTexCoords( EE_U32_t u32_nTexCoords )
{
    mu32_NTexCoords = u32_nTexCoords;    
}

void EE_MODEL_OBJECT_C::SetTexCoords( const EE_PFLOAT_t pf_texCoords )
{
    mpf_TexCoords = new EE_FLOAT_t[ mu32_NTexCoords * 3 ];   
    memcpy( mpf_TexCoords, pf_texCoords, mu32_NTexCoords * 3 * sizeof( EE_FLOAT_t ) ); 
}
        		
void EE_MODEL_OBJECT_C::AddMesh( const EE_MODEL_OBJECT_MESH_C &crC_mesh )
{
    mco_Meshes.push_back( crC_mesh );    
}

const EE_PFLOAT_t EE_MODEL_OBJECT_C::GetVertices( void ) const
{
	return( mpf_Vertices );	
}

EE_U32_t EE_MODEL_OBJECT_C::GetNVertices( void ) const
{
    return( mu32_NVertices );    
}

const EE_PFLOAT_t EE_MODEL_OBJECT_C::GetTexCoords( void ) const
{
	return( mpf_TexCoords );	
}

EE_U32_t EE_MODEL_OBJECT_C::GetNTexCoords( void ) const
{
    return( mu32_NTexCoords );    
}


const std::vector< EE_MODEL_OBJECT_MESH_C >& EE_MODEL_OBJECT_C::GetMeshes( void ) const
{
	return( mco_Meshes );	
}

std::string EE_MODEL_OBJECT_C::GetName( void ) const
{
	return( mS_Name );	
}

EE_BOOL_t EE_MODEL_OBJECT_C::HasVertexBone( EE_U32_t u32_vertexIndex ) const
{
	return( mpb_VertexBones[ u32_vertexIndex ] );	
}
	
const EE_MODEL_BONE_C& EE_MODEL_OBJECT_C::GetVertexBone( EE_U32_t u32_vertexIndex ) const
{
	if( u32_vertexIndex >= mu32_NVertices )
		EE_ERROR_C( "EE_MODEL_OBJECT_C", "GetVertexBone", EE_ERROR_CODES_n::cS_BadIndex, "Desired vertex index = %d; Max vertex index = %d", u32_vertexIndex, mu32_NVertices - 1 );
	
	if( mpu32_VertexBones[ u32_vertexIndex ] >= mco_Bones.size() )
		EE_ERROR_C( "EE_MODEL_OBJECT_C", "GetVertexBone", EE_ERROR_CODES_n::cS_BadIndex, "Desired bone index = %d; Max bone index = %d", mpu32_VertexBones[ u32_vertexIndex ], mco_Bones.size() - 1 );
	
	const EE_MODEL_BONE_C& crC_Bone( mco_Bones[ mpu32_VertexBones[ u32_vertexIndex ] ] );
	
	return( crC_Bone );	
}

void EE_MODEL_OBJECT_C::Clear( void )
{
	Destroy();
}

void EE_MODEL_OBJECT_C::DrawBones( const EE_SYSTEM_COLOR_s &crs_headColor, 
		                		   const EE_SYSTEM_COLOR_s &crs_tailColor ) const
{
	std::vector< EE_MODEL_BONE_C >::const_iterator cI_Bone( mco_Bones.begin() ),
	                                               cI_BoneEnd( mco_Bones.end() );
	while( cI_Bone != cI_BoneEnd )	
		cI_Bone++->Draw( crs_headColor, crs_tailColor );	
}

void EE_MODEL_OBJECT_C::DrawAnimatedBones( const EE_SYSTEM_COLOR_s &crs_headColor, 
		                				   const EE_SYSTEM_COLOR_s &crs_tailColor,
		                				   const EE_MODEL_ANIMATION_ARMATURE_C &crC_skeleton,
										   EE_U32_t u32_frame ) const
{
	std::vector< EE_MODEL_BONE_C >::const_iterator cI_Bone( mco_Bones.begin() ),
	                                               cI_BoneEnd( mco_Bones.end() );
	while( cI_Bone != cI_BoneEnd )	
	{	
		const EE_MODEL_ANIMATION_BONE_C &crC_AnimationBone( crC_skeleton.GetBone( cI_Bone->GetName().c_str() ) ); 		
		
		if( u32_frame >= crC_AnimationBone.GetMatrices().size() )
			EE_ERROR_C( "EE_MODEL_OBJECT_C", "DrawAnimatedBones", EE_ERROR_CODES_n::cS_BadIndex, "Frame index out of range" );
		
		const EE_MATH_MATRIX4X4_C &crC_Matrix( crC_AnimationBone.GetMatrices()[ u32_frame ] );
		
		EE_MATH_POINT_C C_Head, C_Tail;		
									
		C_Head = crC_AnimationBone.GetHead();
		C_Tail = crC_AnimationBone.GetTail();		
		
	/*	// kost do BS root kosti
		C_Head = C_Head + crC_AnimationBone.GetArmaturePositions()[ 0 ];
		C_Tail = C_Tail + crC_AnimationBone.GetArmaturePositions()[ 0 ];
					
		// Postupuju v hierarchii a pøitom násobím
		std::vector< std::string > co_BoneHierarchy( crC_skeleton.GetBone( cI_Bone->GetName().c_str() ).GetHierarchy() );
		EE_MATH_VECTOR_C C_ArmaturePosition; 
	
		for( EE_U32_t u32_Bone( 0 ); u32_Bone < co_BoneHierarchy.size() - 1; u32_Bone++ )
		{				
			const EE_MODEL_ANIMATION_BONE_C &crC_HierarchyBone( crC_skeleton.GetBone( co_BoneHierarchy[ u32_Bone ].c_str() ) );
									
			C_Head = crC_HierarchyBone.GetMatrices()[ u32_frame ] * C_Head;
			C_Tail = crC_HierarchyBone.GetMatrices()[ u32_frame ] * C_Tail;
						
			C_Head = C_Head - crC_HierarchyBone.GetMatrices()[ u32_frame ]*crC_HierarchyBone.GetTail();
			C_Tail = C_Tail - crC_HierarchyBone.GetMatrices()[ u32_frame ]*crC_HierarchyBone.GetTail();
			
			C_ArmaturePosition = C_ArmaturePosition + crC_HierarchyBone.GetMatrices()[ u32_frame ]*crC_HierarchyBone.GetTail();			
		}	
		*/
		
	/*	if(crC_AnimationBone.HasParent())	
		{
			const EE_MODEL_ANIMATION_BONE_C &crC_RootBone( crC_skeleton.GetBone( crC_AnimationBone.GetParent().c_str() ) );
			const EE_MATH_MATRIX4X4_C &crC_RootMatrix( crC_RootBone.GetMatrices()[ u32_frame ] );
			EE_MATH_POINT_C C_RootHead( crC_RootBone.GetHead() ), C_RootTail( crC_RootBone.GetTail() );		
			
			C_Head = crC_RootMatrix * crC_AnimationBone.GetArmatureSpaceHead() - crC_RootBone.mco_TotMatTemp[u32_frame] * C_RootTail;
			C_Tail = crC_RootMatrix * crC_AnimationBone.GetArmatureSpaceTail() - crC_RootBone.mco_TotMatTemp[u32_frame] * C_RootTail;
						
			C_Head = crC_AnimationBone.mco_TotMatTemp[u32_frame] * C_Head;
			C_Tail = crC_AnimationBone.mco_TotMatTemp[u32_frame] * C_Tail;
			
			C_Head = C_Head + crC_RootBone.mco_TotMatTemp[u32_frame] * C_RootTail;
			C_Tail = C_Tail + crC_RootBone.mco_TotMatTemp[u32_frame] * C_RootTail;
		}
		else		
		
		{*/		
		static bool ab[100];
		
		EE_MATH_POINT_C bod(1.0,1.0,1.0);
		
		if(!ab[u32_frame])
		{
			EE_MATH_QUATERNION_C m(crC_AnimationBone.GetQuaternions()[u32_frame]);
			m.SetComment(crC_AnimationBone.GetName().c_str());
			m.Dump(C_XMLDebugFile);
						
			ab[u32_frame] = true;
					
			C_Head = m.ConvertToMatrix() * C_Head;
			C_Tail = m.ConvertToMatrix() * C_Tail;
			
			bod = m.ConvertToMatrix()*bod;
			
			C_Head.Dump(C_XMLDebugFile);
			C_Tail.Dump(C_XMLDebugFile);
		}
		else
		{
			bod = crC_AnimationBone.GetQuaternions()[u32_frame].ConvertToMatrix()*bod;
			C_Head = /*crC_Matrix*/crC_AnimationBone.GetQuaternions()[u32_frame].ConvertToMatrix() * C_Head;
			C_Tail = /*crC_Matrix*/crC_AnimationBone.GetQuaternions()[u32_frame].ConvertToMatrix() * C_Tail;		
		}
		
		/*}*/
		//C_Head = C_Head + C_ArmaturePosition;
		//C_Tail = C_Tail + C_ArmaturePosition;
		
		// !!!
	/*	C_Head = crC_AnimationBone.mco_ASPosTemp[u32_frame];
		C_Tail = crC_AnimationBone.mco_ASPosTemp[u32_frame] + crC_AnimationBone.mco_TailTemp[u32_frame];
	*/	// !!!
				
		//Pøenesu do WS
		C_Head = crC_skeleton.GetArmatureMatrix() * C_Head;
		C_Tail = crC_skeleton.GetArmatureMatrix() * C_Tail;					
		bod	 = crC_skeleton.GetArmatureMatrix() * bod;					
		
		glPushMatrix();	
		
		// Vykreslím kost
		glPushAttrib( GL_ALL_ATTRIB_BITS );
		glDisable( GL_TEXTURE_2D );
		
		glLineWidth( 5.0 );
		glBegin( GL_LINES );
			glColor4ub( crs_headColor.b_R, crs_headColor.b_G, crs_headColor.b_B, crs_headColor.b_A );
			glVertex3f( C_Head.GetX(), C_Head.GetY(), C_Head.GetZ() );
			
			glColor4ub( crs_tailColor.b_R, crs_tailColor.b_G, crs_tailColor.b_B, crs_tailColor.b_A );
			glVertex3f( C_Tail.GetX(), C_Tail.GetY(), C_Tail.GetZ() );	
		
		glEnd();
		
		glPointSize( 5.0 );
		glBegin( GL_POINTS );
			glColor4ub( 0, 255,0,255 );
			glVertex3f( bod.GetX(), bod.GetY(), bod.GetZ() );		
		glEnd();
		/*EE_SYSTEM_COLOR_s c1={0,255,0,255},c2={0,0,255,255};
		EE_MATH_POINT_C T1(2.0,0.0,0.0),T2(0.0,2.0,0.0),T3(0.0,0.0,2.0);
		T1=crC_Matrix*T1;T1=crC_skeleton.GetArmatureMatrix() * T1;
		T2=crC_Matrix*T2;T2=crC_skeleton.GetArmatureMatrix() * T2;
		T3=crC_Matrix*T3;T3=crC_skeleton.GetArmatureMatrix() * T3;
		
		glDisable(GL_DEPTH_TEST);
		glPointSize( 5.0 );
		glBegin( GL_POINTS );
			if(cI_Bone->GetName()==std::string("Bone.001"))
				glColor4ub( c1.b_R, c1.b_G, c1.b_B, c1.b_A );
			else
				glColor4ub( c2.b_R, c2.b_G, c2.b_B, c2.b_A );
			
			glVertex3f( T1.GetX(), T1.GetY(), T1.GetZ() );
			glVertex3f( T2.GetX(), T2.GetY(), T2.GetZ() );
			glVertex3f( T3.GetX(), T3.GetY(), T3.GetZ() );
		glEnd();*/
		
		glPopAttrib();
		
		cI_Bone++;
		glPopMatrix();
	}		
}

void EE_MODEL_OBJECT_C::Create( const EE_MODEL_OBJECT_C& crC_object )
{
	mu32_NVertices = crC_object.mu32_NVertices;
	if( mu32_NVertices )
	{
		mpf_Vertices = new EE_FLOAT_t[ crC_object.mu32_NVertices * 3 ];
		memcpy( mpf_Vertices, crC_object.mpf_Vertices, crC_object.mu32_NVertices * 3 * sizeof( EE_FLOAT_t ) );
	}
	
	mu32_NTexCoords = crC_object.mu32_NTexCoords;
	if( mu32_NTexCoords )
	{
		mpf_TexCoords = new EE_FLOAT_t[ crC_object.mu32_NTexCoords * 2 ];
		memcpy( mpf_TexCoords, crC_object.mpf_TexCoords, crC_object.mu32_NTexCoords * 2 * sizeof( EE_FLOAT_t ) );
	}
	
	if( crC_object.mpu32_VertexBones )
	{
		mpu32_VertexBones = new EE_U32_t[ mu32_NVertices ];
		memcpy( mpu32_VertexBones, crC_object.mpu32_VertexBones, mu32_NVertices * sizeof( EE_U32_t ) );
	}
	
	if( crC_object.mpb_VertexBones )
	{
		mpb_VertexBones = new EE_BYTE_t[ mu32_NVertices ];
		memcpy( mpb_VertexBones, crC_object.mpb_VertexBones, mu32_NVertices * sizeof( EE_BYTE_t ) );
	}
	
	mco_Meshes = crC_object.mco_Meshes;
	
	mco_Bones = crC_object.mco_Bones;
	
	mS_Name = crC_object.mS_Name;
}

void EE_MODEL_OBJECT_C::Destroy( void )
{
	delete[] mpu32_VertexBones;
	mpu32_VertexBones = EE_NULL;
	
	delete[] mpb_VertexBones;
	mpb_VertexBones = EE_NULL;
	
	delete[] mpf_Vertices;
	mpf_Vertices = EE_NULL;
	
	delete[] mpf_TexCoords;
	mpf_TexCoords = EE_NULL;
	
	mu32_NVertices = 0;
	mu32_NTexCoords = 0;
	
	mco_Meshes.clear();	
	
	mco_Bones.clear();
	
	mS_Name = "";
}
