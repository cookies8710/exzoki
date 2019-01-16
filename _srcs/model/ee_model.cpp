#include <exzoki/model/ee_model.h>

EE_MODEL_C::EE_MODEL_C( void ): mb_Valid( EE_FALSE ),
                                mpC_TextureManager( 0 ) 
{
}

EE_MODEL_C::~EE_MODEL_C( void )
{
	Destroy();
} 
  
void EE_MODEL_C::Load( EE_CCSTRING_t ccs_path )
{
 	std::string S_Path( ccs_path );
 	std::string S_Extension;
 	std::string::const_iterator cI_Dot, cI_End( S_Path.end() );
    
    // Vyèistím model
 	Destroy();
 
 	cI_Dot = find( S_Path.begin(), S_Path.end(), '.' );
 	if( cI_Dot == cI_End )
  		EE_ERROR_C( "EE_MODEL_C", "Load", EE_ERROR_CODES_n::cS_BadFileName, S_Path.c_str() );
 	else
  		S_Extension = std::string( cI_Dot + 1, cI_End );
 
 	if( S_Extension == EE_MODEL_TMD_n::cS_TMD )
  		LoadTMD( ccs_path );
  	else if( S_Extension == std::string( "obj" ) )
  	    LoadOBJ( ccs_path );
  	else
  		EE_ERROR_C( "EE_MODEL_C", "Load", EE_ERROR_CODES_n::cS_UnknownFileFormat, S_Path.c_str() );
	
	
	// kolizni koule	
	for(int i(0);i<mco_Objects.size();i++)
	{
        const EE_MODEL_OBJECT_C &crC_Object(mco_Objects[i]);
        for(int j(0);j<crC_Object.GetMeshes().size();j++)
        {
            const EE_MODEL_OBJECT_MESH_C &crC_Mesh(crC_Object.GetMeshes()[j]);
            for(int k(0);k<crC_Mesh.GetNFaces();k++)
            {
                EE_U32_t v1(crC_Mesh.GetVertexIndices()[3*k+0]),
                         v2(crC_Mesh.GetVertexIndices()[3*k+1]),
                         v3(crC_Mesh.GetVertexIndices()[3*k+2]);
                
                EE_MATH_TRIANGLE_C tri( 
                EE_MATH_POINT_C(crC_Object.GetVertices()[v1*3+0], 
                                crC_Object.GetVertices()[v1*3+1], 
                                crC_Object.GetVertices()[v1*3+2]),
                EE_MATH_POINT_C(crC_Object.GetVertices()[v2*3+0], 
                                crC_Object.GetVertices()[v2*3+1], 
                                crC_Object.GetVertices()[v2*3+2]),
                EE_MATH_POINT_C(crC_Object.GetVertices()[v3*3+0], 
                                crC_Object.GetVertices()[v3*3+1], 
                                crC_Object.GetVertices()[v3*3+2]) );
                co_CSs.push_back(EE_EXZOKI_n::CollisionSphere(tri));
                
            }    
            
        }    
        
    }
}

void EE_MODEL_C::LoadWithTextures( EE_CCSTRING_t ccs_path,
		                           EE_CCSTRING_t ccs_textureDirectory,
								   EE_TEXTURE_FILTERING_e e_filtering )
{
	if( !mpC_TextureManager )
		EE_ERROR_C( "EE_MODEL_C", "LoadWithTextures", EE_ERROR_CODES_n::cS_TextureManagerNotSet );
	
	Load( ccs_path );
	
	mS_TextureDirectory = ccs_textureDirectory;
	
	std::vector< EE_MODEL_MATERIAL_C >::const_iterator cI_Material( mco_Materials.begin() ),
	                                                   cI_MaterialEnd( mco_Materials.end() );
	while( cI_Material != cI_MaterialEnd )
	{
		if( cI_Material->HasTexture() )
			mpC_TextureManager->Load( std::string( mS_TextureDirectory + std::string( cI_Material->GetTexture() ) ).c_str(),
			                          e_filtering );
		
		cI_Material++;	
	}
		
}

void EE_MODEL_C::SetTextureManager( EE_TEXTURE_MANAGER_C& rC_textureManager )
{
	mpC_TextureManager = &rC_textureManager;	
}

void EE_MODEL_C::LoadVertexAnimation( EE_CCSTRING_t ccs_path )
{
	EE_MODEL_VERTEX_ANIMATION_C C_Animation( ccs_path );
	mco_VertexAnimations[ C_Animation.GetName() ] = C_Animation;	
	return;	
}

void EE_MODEL_C::LoadSkeletalAnimation( EE_CCSTRING_t ccs_path )
{
	EE_MODEL_ANIMATION_C C_Animation( ccs_path );
	mco_SkeletalAnimations[ C_Animation.GetName() ] = C_Animation;	
	return;	
}

void EE_MODEL_C::PlayVertexAnimation( EE_CCSTRING_t ccs_path, EE_U32_t u32_repeats )
{
	mb_AnimationRunning = 1;
    mS_CurrentAnimation = ccs_path;
    mf_AnimationTime = 0.0;
	mu32_AnimationRepeatsLeft = u32_repeats;
	me_AnimationType = EE_MODEL_ANIMATION_VERTEX;
	
	if( mco_VertexAnimations.find( mS_CurrentAnimation ) == mco_VertexAnimations.end() )	
		EE_ERROR_C( "EE_MODEL_C", "PlayVertexAnimation", EE_ERROR_CODES_n::cS_AnimationNotFound, ccs_path );
	
			
	mC_Synchro.SynchronizerProc();	
}

void EE_MODEL_C::PlayAnimation( EE_CCSTRING_t ccs_path, EE_U32_t u32_repeats )
{
	mb_AnimationRunning = 1;
    mS_CurrentAnimation = ccs_path;
    mf_AnimationTime = 0.0;
	mu32_AnimationRepeatsLeft = u32_repeats;
	
	if( mco_VertexAnimations.find( mS_CurrentAnimation ) == mco_VertexAnimations.end() )	
	{
		if( mco_SkeletalAnimations.find( mS_CurrentAnimation ) == mco_SkeletalAnimations.end() )
			EE_ERROR_C( "EE_MODEL_C", "PlayAnimation", EE_ERROR_CODES_n::cS_AnimationNotFound, ccs_path );
		else
		{
			me_AnimationType = EE_MODEL_ANIMATION_SKELETAL;
		}
	}	
	else 
	{
		me_AnimationType = EE_MODEL_ANIMATION_VERTEX;
	}
			
	mC_Synchro.SynchronizerProc();	
}

void EE_MODEL_C::StopAnimation( void )
{
	mb_AnimationRunning = 0;
    mS_CurrentAnimation.clear();
    mf_AnimationTime = 0.0;
	mu32_AnimationRepeatsLeft = 0;
	me_AnimationType = EE_MODEL_ANIMATION_NONE;	
}

void EE_MODEL_C::Draw( void )
{			
	if( mb_AnimationRunning )	
		DrawAnimation();
	else
		DrawStatic();
	return;
}

void EE_MODEL_C::DrawBones( const EE_SYSTEM_COLOR_s &crs_headColor, 
		                	const EE_SYSTEM_COLOR_s &crs_tailColor )
{
	// Zjistím frame animace
	EE_U32_t u32_Frame;
	u32_Frame = mf_AnimationTime * mco_SkeletalAnimations[ mS_CurrentAnimation ].GetFrameRate();
		
	// Pokud je index framu vyšší, než kolik jich animace má, animace skonèila
	if( u32_Frame >= mco_SkeletalAnimations[ mS_CurrentAnimation ].GetNFrames() )
	{	
		// Frame na 0
		u32_Frame = 0;      
	}
	
	std::vector< EE_MODEL_OBJECT_C >::const_iterator cI_Object( mco_Objects.begin() ), cI_End( mco_Objects.end() );
	
	while( cI_Object != cI_End )
	{
		if( mb_AnimationRunning )	
			cI_Object->DrawAnimatedBones( crs_headColor, 
			                              crs_tailColor, 
										  mco_SkeletalAnimations[ mS_CurrentAnimation ].GetSkeleton( cI_Object->GetName().c_str() ), 
										  u32_Frame );
		else
			cI_Object->DrawBones( crs_headColor, crs_tailColor );
		
		
		cI_Object++;	
	}		
}

void EE_MODEL_C::DrawBones( const EE_SYSTEM_COLOR_s &crs_staticHeadColor, 
		                	const EE_SYSTEM_COLOR_s &crs_staticTailColor,
							const EE_SYSTEM_COLOR_s &crs_animatedHeadColor, 
		                	const EE_SYSTEM_COLOR_s &crs_animatedTailColor )
{
	// Zjistím frame animace
	EE_U32_t u32_Frame;
	u32_Frame = mf_AnimationTime * mco_SkeletalAnimations[ mS_CurrentAnimation ].GetFrameRate();
		
	// Pokud je index framu vyšší, než kolik jich animace má, animace skonèila
	if( u32_Frame >= mco_SkeletalAnimations[ mS_CurrentAnimation ].GetNFrames() )
	{	
		// Frame na 0
		u32_Frame = 0;      
	}
	
	std::vector< EE_MODEL_OBJECT_C >::const_iterator cI_Object( mco_Objects.begin() ), cI_End( mco_Objects.end() );
	
	while( cI_Object != cI_End )
	{
		if( mb_AnimationRunning )	
			cI_Object->DrawAnimatedBones( crs_animatedHeadColor, 
			                              crs_animatedTailColor, 
										  mco_SkeletalAnimations[ mS_CurrentAnimation ].GetSkeleton( cI_Object->GetName().c_str() ), 
										  u32_Frame );
		else
			cI_Object->DrawBones( crs_staticHeadColor, crs_staticTailColor );
		
		
		cI_Object++;	
	}	
}

void EE_MODEL_C::DrawAnimation( void )
{
	// Zjistím frame animace
	EE_U32_t u32_Frame;
	if( me_AnimationType == EE_MODEL_ANIMATION_SKELETAL )
	{
		u32_Frame = mf_AnimationTime * mco_SkeletalAnimations[ mS_CurrentAnimation ].GetFrameRate();
		
		// Pokud je index framu vyšší, než kolik jich animace má, animace skonèila
		if( u32_Frame >= mco_SkeletalAnimations[ mS_CurrentAnimation ].GetNFrames() )
		{
			// Frame na 0
			u32_Frame = 0;
			// Snížím poèet opakování animace
			mu32_AnimationRepeatsLeft--;
			// Vynuluju èas animace
			mf_AnimationTime = 0.0;	
		
			// Pokud tohle bylo poslední opakování, zastavím animacei
			if( mu32_AnimationRepeatsLeft == 0 )
				StopAnimation();
			      	
      		return;
		}
	}
	else if( me_AnimationType == EE_MODEL_ANIMATION_VERTEX )
	{
		u32_Frame = mf_AnimationTime * mco_VertexAnimations[ mS_CurrentAnimation ].GetFrameRate();
		
		// Pokud je index framu vyšší, než kolik jich animace má, animace skonèila
		if( u32_Frame >= mco_VertexAnimations[ mS_CurrentAnimation ].GetNFrames() )
		{
			// Frame na 0
			u32_Frame = 0;
			// Snížím poèet opakování animace
			mu32_AnimationRepeatsLeft--;
			// Vynuluju èas animace
			mf_AnimationTime = 0.0;	
		
			// Pokud tohle bylo poslední opakování, zastavím animacei
			if( mu32_AnimationRepeatsLeft == 0 )
				StopAnimation();
			      	
      		return;
		}
	}
	
	
	// Projdu všechny objekty
	std::vector< EE_MODEL_OBJECT_C >::const_iterator cI_Object = mco_Objects.begin(),
	                                                 cI_ObjectEnd = mco_Objects.end();
	while( cI_Object != cI_ObjectEnd )
	{			
		const EE_PFLOAT_t cpf_Vertices( cI_Object->GetVertices() ),
		                  cpf_TexCoords( cI_Object->GetTexCoords() );
		std::vector< EE_MODEL_OBJECT_MESH_C >::const_iterator cI_Mesh( cI_Object->GetMeshes().begin() ),
		                                                      cI_MeshEnd( cI_Object->GetMeshes().end() );
		EE_BOOL_t b_HasTexture( EE_FALSE );
		// Projdu všechny meshe
		while( cI_Mesh != cI_MeshEnd )
		{	
			// Pokud má mesh materiál, nastavím ho
			if( cI_Mesh->HasMaterial() )
			{
				glColor3ub( mco_Materials[ cI_Mesh->GetMaterialIndex() ].GetColor( 0 ),
				            mco_Materials[ cI_Mesh->GetMaterialIndex() ].GetColor( 1 ),
							mco_Materials[ cI_Mesh->GetMaterialIndex() ].GetColor( 2 ) );
				if( mco_Materials[ cI_Mesh->GetMaterialIndex() ].HasTexture() )
				{
					glEnable( GL_TEXTURE_2D );
					b_HasTexture = EE_TRUE;
					( *mpC_TextureManager )[ mco_Materials[ cI_Mesh->GetMaterialIndex() ].GetTexture() ];
				}
				else
				{
					glDisable( GL_TEXTURE_2D );	
					b_HasTexture = EE_FALSE;
				}
			}
			else
			{
				glDisable( GL_TEXTURE_2D );
				glColor3f( 0.5f, 0.5f, 0.5f );	
				b_HasTexture = EE_FALSE;
			}
					
			// Vykreslím triangly
			glBegin( GL_TRIANGLES );
				EE_U32_t u32_NFaces( cI_Mesh->GetNFaces() );
				const EE_PU32_t cpu32_VertexIndices( cI_Mesh->GetVertexIndices() ),
				                cpu32_TexCoordIndices( cI_Mesh->GetTexCoordIndices() );
				EE_U32_t u32_Index;
				for( EE_U32_t u32_Face( 0 ); u32_Face < u32_NFaces; u32_Face++ )
					for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < 3; u32_Vertex++ )
					{
						u32_Index = u32_Face * 3 + u32_Vertex;
						// Nastavím texturové koordináty, pokud jsou
						if( b_HasTexture )
							glTexCoord2fv( &cpf_TexCoords[ 2 * cpu32_TexCoordIndices[ u32_Index ] ] );
						
						EE_U32_t u32_VertexIndex( cpu32_VertexIndices[ u32_Index ] );
						if( me_AnimationType == EE_MODEL_ANIMATION_SKELETAL )
						{						
							const EE_MODEL_ANIMATION_C &crC_Animation( mco_SkeletalAnimations[ mS_CurrentAnimation ] );
						
							// Pokud vertex ovlivòujé nìjaká kost, musím vypoèítat jeho pozici; jinak vykreslím statický vertex
							if( cI_Object->HasVertexBone( u32_VertexIndex ) )
							{
					
								EE_MODEL_BONE_C crC_Bone( cI_Object->GetVertexBone( u32_VertexIndex ) );
								const EE_MODEL_ANIMATION_BONE_C &crC_AnimationBone( crC_Animation.GetBone( cI_Object->GetName().c_str(), 
							                                                           		  crC_Bone.GetName().c_str() ) );					
								const std::vector< EE_MATH_MATRIX4X4_C >& crco_Matrices( crC_AnimationBone.GetMatrices() ); 
							
								EE_MATH_VECTOR_C C_Vertex( cpf_Vertices[ 3 * cpu32_VertexIndices[ u32_Index ] ], 
						                           	   		cpf_Vertices[ 3 * cpu32_VertexIndices[ u32_Index ] + 1 ],
												       		cpf_Vertices[ 3 * cpu32_VertexIndices[ u32_Index ] + 2 ]);
							
								// Transformaèní matice pro tento vertex
							//	EE_MATH_MATRIX4X4_C C_Matrix = crco_Matrices[ u32_Frame ];
						
								//// Transformace v Bone prostoru
								//EE_MATH_MATRIX4X4_C C_BoneSpaceTransformation( C_Matrix );
						
								//// Spoèítám finální matici
								//EE_MATH_MATRIX4X4_C C_Final( C_BoneSpaceTransformation );
							
								// Spoèítám koncovou pozici vertexu
								//C_Vertex = crC_AnimationBone.ToWorldSpace( C_Final * crC_AnimationBone.ToBoneSpace( C_Vertex ) );
								
								
								//C_Vertex = C_Matrix * crC_AnimationBone.ToBoneSpace( C_Vertex );								
								//C_Vertex = /*crC_Animation.GetSkeleton( cI_Object->GetName().c_str() ).GetArmatureMatrix()*/crC_AnimationBone.ToWorldSpace( C_Vertex);	
								
								
								// pøevedu vertex do BS root kosti
								/*C_Vertex = crC_Animation.GetSkeleton( cI_Object->GetName().c_str() ).GetInverseArmatureMatrix() * C_Vertex;
								EE_U32_t u32_NBones( crC_AnimationBone.GetHierarchy().size() );
								EE_MATH_VECTOR_C C_TotalTransaltion;
								
								for( EE_U32_t u32_Bone( 0 ); u32_Bone < u32_NBones; u32_Bone++ )
								{
									const EE_MODEL_ANIMATION_BONE_C& crC_HieararchyBone( crC_Animation.GetBone( cI_Object->GetName().c_str(), 
							                                                           	 crC_AnimationBone.GetHierarchy()[ u32_Bone ].c_str() ) );
							        
									// Aplikuju animaci kosti
									C_Vertex = crC_HieararchyBone.GetMatrices()[ u32_Frame ] * C_Vertex;
									// Pøesunu se k další kosti
							        C_Vertex = C_Vertex - crC_HieararchyBone.GetMatrices()[ u32_Frame ] * crC_HieararchyBone.GetTail();
							        // Pøiètu k celkové translaci
							        C_TotalTransaltion = C_TotalTransaltion + crC_HieararchyBone.GetMatrices()[ u32_Frame ] * crC_HieararchyBone.GetTail();
								}
								
								
								C_Vertex = C_Vertex + C_TotalTransaltion;
								C_Vertex = crC_Animation.GetSkeleton( cI_Object->GetName().c_str() ).GetArmatureMatrix() * C_Vertex;
								//*/
								
															
								C_Vertex = crC_Animation.GetSkeleton( cI_Object->GetName().c_str() ).GetInverseArmatureMatrix() * C_Vertex;
							
								//C_Vertex = C_Vertex - crC_AnimationBone.GetArmaturePositions()[ u32_Frame ];
								
								C_Vertex = /*crco_Matrices[ u32_Frame ]*/crC_AnimationBone.GetQuaternions()[u32_Frame].ConvertToMatrix() * C_Vertex;
								
								//C_Vertex = C_Vertex + crC_AnimationBone.GetArmaturePositions()[ u32_Frame ];
								
								C_Vertex = crC_Animation.GetSkeleton( cI_Object->GetName().c_str() ).GetArmatureMatrix() * C_Vertex;		
								
								// Vykreslím vertex	
								glVertex3f( C_Vertex.GetX(), C_Vertex.GetY(), C_Vertex.GetZ() );
								
								
								/*EE_MATH_VECTOR_C C_Test(-1.0,0.0,0.0);
								
								C_Test = crC_Animation.GetSkeleton( cI_Object->GetName().c_str() ).GetArmatureMatrix() * crC_AnimationBone.GetMatrices()[ u32_Frame ] * C_Test;
								
								C_Test = C_Test-EE_MATH_VECTOR_C(0.0,-2.0,0.0);
								C_Test = C_Test;
								
								glPushAttrib(GL_ALL_ATTRIB_BITS);
								glPointSize(5.0);
								
								glBegin(GL_POINTS);
								
								glColor3f( 0.0,1.0,0.0);
								glVertex3f( C_Test.GetX(), C_Test.GetY(), C_Test.GetZ() );
								
								glEnd();
								glPopAttrib();*/
							}
							else
								glVertex3fv( &cpf_Vertices[ 3 * cpu32_VertexIndices[ u32_Index ] ] );
						
						}
						else if( me_AnimationType == EE_MODEL_ANIMATION_VERTEX )
						{
							const EE_MODEL_VERTEX_ANIMATION_C& crC_VertexAnimation( mco_VertexAnimations[ mS_CurrentAnimation ] );
							const EE_MODEL_VERTEX_ANIMATION_FRAME_t& crC_Frame( crC_VertexAnimation.GetVertexFrame( u32_Frame ) );
														
							glVertex3f( crC_Frame[ u32_VertexIndex ].GetX(), 
							            crC_Frame[ u32_VertexIndex ].GetY(),
										crC_Frame[ u32_VertexIndex ].GetZ() );	
						}
					}
			glEnd();
			cI_Mesh++;	
		}
		
		cI_Object++;	
	}	
	
	
	mC_Synchro.SynchronizerProc();
	mf_AnimationTime += mC_Synchro.GetSynchro();
}

void EE_MODEL_C::DrawStatic( void )
{
	// Projdu všechny objekty
	std::vector< EE_MODEL_OBJECT_C >::const_iterator cI_Object = mco_Objects.begin(),
	                                                 cI_ObjectEnd = mco_Objects.end();
	while( cI_Object != cI_ObjectEnd )
	{
		const EE_PFLOAT_t cpf_Vertices( cI_Object->GetVertices() ),
		                  cpf_TexCoords( cI_Object->GetTexCoords() );
		std::vector< EE_MODEL_OBJECT_MESH_C >::const_iterator cI_Mesh( cI_Object->GetMeshes().begin() ),
		                                                      cI_MeshEnd( cI_Object->GetMeshes().end() );
		EE_BOOL_t b_HasTexture( EE_FALSE );
		// Projdu všechny meshe
		while( cI_Mesh != cI_MeshEnd )
		{
			// Poku má mesh materiál, nastavím ho
			if( cI_Mesh->HasMaterial() )
			{
				glColor3ub( mco_Materials[ cI_Mesh->GetMaterialIndex() ].GetColor( 0 ),
				            mco_Materials[ cI_Mesh->GetMaterialIndex() ].GetColor( 1 ),
								mco_Materials[ cI_Mesh->GetMaterialIndex() ].GetColor( 2 ) );
				if( mco_Materials[ cI_Mesh->GetMaterialIndex() ].HasTexture() )
				{
					glEnable( GL_TEXTURE_2D );
					b_HasTexture = EE_TRUE;
					( *mpC_TextureManager )[ mco_Materials[ cI_Mesh->GetMaterialIndex() ].GetTexture() ];
				}
				else
				{
					glDisable( GL_TEXTURE_2D );	
					b_HasTexture = EE_FALSE;
				}
			}
			else
			{
				glDisable( GL_TEXTURE_2D );
				glColor3f( 0.5f, 0.5f, 0.5f );	
				b_HasTexture = EE_FALSE;
			}
			
			// Vykreslím triangly
			glBegin( GL_TRIANGLES );
				EE_U32_t u32_NFaces( cI_Mesh->GetNFaces() );
				const EE_PU32_t cpu32_VertexIndices( cI_Mesh->GetVertexIndices() ),
				                cpu32_TexCoordIndices( cI_Mesh->GetTexCoordIndices() );
				EE_U32_t u32_Index;
				for( EE_U32_t u32_Face( 0 ); u32_Face < u32_NFaces; u32_Face++ )
					for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < 3; u32_Vertex++ )
					{					
						u32_Index = u32_Face * 3 + u32_Vertex;
						if( b_HasTexture )
							glTexCoord2fv( &cpf_TexCoords[ 2 * cpu32_TexCoordIndices[ u32_Index ] ] );
						glVertex3fv( &cpf_Vertices[ 3 * cpu32_VertexIndices[ u32_Index ] ] );	
					}
			glEnd();
			
			cI_Mesh++;	
		}
		
		cI_Object++;	
	}	
	
}

std::vector< EE_MODEL_OBJECT_C > EE_MODEL_C::GetObjects( void ) const
{
	return( mco_Objects );	
}

std::vector< EE_MODEL_MATERIAL_C > EE_MODEL_C::GetMaterials( void ) const
{
	return( mco_Materials );	
}

std::string EE_MODEL_C::GetTextureDirectory( void ) const
{
    return( mS_TextureDirectory );    
}

void EE_MODEL_C::LoadTMD( EE_CCSTRING_t ccs_path )
{
	Destroy();
	
	EE_SYSTEM_FILE_C C_File( ccs_path, EE_SYSTEM_FILE_READ, EE_SYSTEM_FILE_BINARY );
 
 	// Kontrola textového ID
 	EE_U32_t u32_HeaderSize( EE_MODEL_TMD_n::cS_Header.size() );
 	std::string S_Header;
 	for( EE_U32_t u32_Char( 0 ); u32_Char < u32_HeaderSize; u32_Char++ )
  		S_Header += C_File.GetChar();
 	if( S_Header != EE_MODEL_TMD_n::cS_Header )
  		EE_ERROR_C( "EE_MODEL_C", "LoadTMD", EE_ERROR_CODES_n::cS_WrongFileHeader, ccs_path );
 	// Kontrola verze
 	EE_U16_t u16_Version;
 	C_File.Read( &u16_Version, sizeof( u16_Version ) );
 	if( u16_Version != EE_MODEL_TMD_n::cu16_Version )
	 	EE_ERROR_C( "EE_MODEL_C", 
		            "LoadTMD", 
					EE_ERROR_CODES_n::cS_BadVersion, 
					"Version needed: %d; File \"%s\" version: %d", 
					EE_MODEL_TMD_n::cu16_Version, ccs_path, u16_Version );

 
 	EE_U32_t u32_NObjects;
 	EE_U32_t u32_NMaterials;
 	C_File.Read( &u32_NObjects, sizeof( u32_NObjects ) );
 	C_File.Read( &u32_NMaterials, sizeof( u32_NMaterials ) );
 
 	// Objekty
 	EE_MODEL_OBJECT_C C_Object;
 	for( EE_U32_t u32_Object( 0 ); u32_Object < u32_NObjects; u32_Object++ )
 	{
  		C_Object.Read( C_File );
  		mco_Objects.push_back( C_Object );
 	}  
 
 	// Materiály
 	EE_MODEL_MATERIAL_C C_Material;
 	for( EE_U32_t u32_Material( 0 ); u32_Material < u32_NMaterials; u32_Material++ )
 	{
  		C_Material.Read( C_File );
  		mco_Materials.push_back( C_Material );    
 	}
 
 	C_File.Close();	
}
/*
void EE_MODEL_C::SaveTMD( EE_CCSTRING_t ccs_path ) const
{
	EE_SYSTEM_FILE_C C_File( ccs_path, EE_SYSTEM_FILE_WRITE, EE_SYSTEM_FILE_BINARY );
                
 	// Zápis textového ID
  	EE_U32_t u32_HeaderSize( EE_MODEL_TMD_n::cS_Header.size() );
 	C_File.Write( (EE_PVOID_t)EE_MODEL_TMD_n::cS_Header.data(), u32_HeaderSize );
 	// Zápis verze
 	C_File.Write( (EE_PVOID_t)&EE_MODEL_TMD_n::cu16_Version, sizeof( EE_MODEL_TMD_n::cu16_Version ) );
 	 
 	EE_U32_t u32_NObjects( mco_Objects.size() );
 	EE_U32_t u32_NMaterials( mco_Materials.size() );
 	C_File.Write( (EE_PVOID_t)&u32_NObjects, sizeof( u32_NObjects ) );
 	C_File.Write( (EE_PVOID_t)&u32_NMaterials, sizeof( u32_NMaterials ) );
 
 	// Objekty
 	EE_ERROR_C( "EE_MODEL_C", "SaveTMD", EE_ERROR_CODES_n::cS_Internal );
	 //for( EE_U32_t u32_Object( 0 ); u32_Object < u32_NObjects; u32_Object++ )
 	//	mco_Objects[ u32_Object ].Write( C_File );  
 
 	// Materiály
 	EE_MODEL_MATERIAL_C C_Material;
 	for( EE_U32_t u32_Material( 0 ); u32_Material < u32_NMaterials; u32_Material++ )
 		mco_Materials[ u32_Material ].Write( C_File );  
 
 	C_File.Close();		
}
*/
void EE_MODEL_C::LoadOBJ( EE_CCSTRING_t ccs_path )
{
    
    // clear !!!
    
    EE_MODEL_OBJ_MODEL_C C_OBJModel;
    
    // Naètu model    
    C_OBJModel.Load( ccs_path );
    
    // Pøekopíruju materiály
    std::vector< EE_MODEL_OBJ_MATERIAL_C >::const_iterator cI_Materials( C_OBJModel.GetMaterials().begin() ),
                                                           cI_MaterialsEnd( C_OBJModel.GetMaterials().end() );
    while( cI_Materials != cI_MaterialsEnd )
    {
        mco_Materials.push_back( EE_MODEL_MATERIAL_C() );
        EE_MODEL_MATERIAL_C &rC_Material( mco_Materials[ mco_Materials.size() - 1 ] );
        
        // Pøedám bravu
        rC_Material.SetColor( EE_BYTE_t( cI_Materials->GetColorR() * 255.0 ),
                              EE_BYTE_t( cI_Materials->GetColorG() * 255.0 ),
                              EE_BYTE_t( cI_Materials->GetColorB() * 255.0 ) );
        // Pokud má materiál texturu, pøedám ji
        if( cI_Materials->GetTextureFilename().size() )
            rC_Material.SetTexture( cI_Materials->GetTextureFilename() );
        
        cI_Materials++;    
    }
    
    // Pøekopíruju objekty
    std::vector< EE_MODEL_OBJ_OBJECT_C >::const_iterator cI_Objects( C_OBJModel.GetObjects().begin() ),
                                                         cI_ObjectsEnd( C_OBJModel.GetObjects().end() );
    while( cI_Objects != cI_ObjectsEnd )
    {
        mco_Objects.push_back( EE_MODEL_OBJECT_C() );
        EE_MODEL_OBJECT_C &rC_Object( mco_Objects[ mco_Objects.size() - 1 ] );
        
        // Vertexy
        EE_U32_t u32_NVertices( cI_Objects->GetVertices().size() );
        EE_PFLOAT_t pf_Vertices( new EE_FLOAT_t[ 3 * u32_NVertices ] );
        for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < u32_NVertices; u32_Vertex++ )
        {
            pf_Vertices[ u32_Vertex * 3 + 0  ] = cI_Objects->GetVertices()[ u32_Vertex ].GetX(); 
            pf_Vertices[ u32_Vertex * 3 + 1  ] = cI_Objects->GetVertices()[ u32_Vertex ].GetY(); 
            pf_Vertices[ u32_Vertex * 3 + 2  ] = cI_Objects->GetVertices()[ u32_Vertex ].GetZ();  
        }
        rC_Object.SetNVertices( u32_NVertices );
        rC_Object.SetVertices( pf_Vertices );
        delete[] pf_Vertices;
        
        // Texturové koordináty
        EE_U32_t u32_NTexCoords( cI_Objects->GetTexCoords().size() );
        EE_PFLOAT_t pf_TexCoords( new EE_FLOAT_t[ 2 * u32_NTexCoords ] );
        for( EE_U32_t u32_TexCoord( 0 ); u32_TexCoord < u32_NTexCoords; u32_TexCoord++ )
        {
            pf_TexCoords[ u32_TexCoord * 2 + 0  ] = cI_Objects->GetTexCoords()[ u32_TexCoord ].GetU(); 
            pf_TexCoords[ u32_TexCoord * 2 + 1  ] = cI_Objects->GetTexCoords()[ u32_TexCoord ].GetV(); 
        }
        rC_Object.SetNTexCoords( u32_NTexCoords );
        rC_Object.SetTexCoords( pf_TexCoords );
        delete[] pf_TexCoords;
        
        // Mesh        
        // Pokud má objekt materiál, najdu jeho èíslo
        EE_U32_t u32_MaterialIndex;
        EE_BOOL_t b_Material( 0 );
        if( cI_Objects->GetMaterialName().size() )
        {
            EE_U32_t u32_NMaterials( C_OBJModel.GetMaterials().size() );
            
            for( EE_U32_t u32_Material( 0 ); 
                 u32_Material < u32_NMaterials && !b_Material; 
                 u32_Material++ )
            {
                if( C_OBJModel.GetMaterials()[ u32_Material ].GetName() == 
                    cI_Objects->GetMaterialName() )
                {
                    b_Material = 1;
                    u32_MaterialIndex = u32_Material;
                }        
            }      
        }    
        EE_MODEL_OBJECT_MESH_C C_Mesh;
        // Pokud má, nastavím materiál
        if( b_Material )
            C_Mesh.SetMaterialIndex( u32_MaterialIndex ); 
        // Nakopíruju facy       
        EE_U32_t u32_NFaces( cI_Objects->GetFaces().size() );
        EE_PU32_t pu32_VertexIndices( new EE_U32_t[ u32_NFaces * 3 ] );
        EE_PU32_t pu32_TexCoordIndices( 0 );
        EE_BOOL_t b_HasTexCoords( b_Material && mco_Materials[ u32_MaterialIndex ].HasTexture() );
        if( b_HasTexCoords )
            pu32_TexCoordIndices = new EE_U32_t[ u32_NFaces * 3 ];
        for( EE_U32_t u32_Face( 0 ); u32_Face < u32_NFaces; u32_Face++ )
        {
            pu32_VertexIndices[ u32_Face * 3 + 0 ] = cI_Objects->GetFaces()[ u32_Face ].GetVertex1Index();  
            pu32_VertexIndices[ u32_Face * 3 + 1 ] = cI_Objects->GetFaces()[ u32_Face ].GetVertex2Index();          
            pu32_VertexIndices[ u32_Face * 3 + 2 ] = cI_Objects->GetFaces()[ u32_Face ].GetVertex3Index(); 
            
            if( b_HasTexCoords )
            {
                pu32_TexCoordIndices[ u32_Face * 3 + 0 ] = cI_Objects->GetFaces()[ u32_Face ].GetVertex1TexCoordIndex();
                pu32_TexCoordIndices[ u32_Face * 3 + 1 ] = cI_Objects->GetFaces()[ u32_Face ].GetVertex2TexCoordIndex();
                pu32_TexCoordIndices[ u32_Face * 3 + 2 ] = cI_Objects->GetFaces()[ u32_Face ].GetVertex3TexCoordIndex();     
            }                   
        }
        
        C_Mesh.SetNFaces( u32_NFaces );
        C_Mesh.SetVertexIndices( pu32_VertexIndices );
        if( b_HasTexCoords )
            C_Mesh.SetTexCoordIndices( pu32_TexCoordIndices );
        
        delete[] pu32_VertexIndices;
        if( b_HasTexCoords )
            delete[] pu32_TexCoordIndices;
        rC_Object.AddMesh( C_Mesh );
        
        
        cI_Objects++;  
    } 
    
}

void EE_MODEL_C::Destroy( void )
{
	mco_Objects.clear();
	mco_Materials.clear();
	mS_TextureDirectory = "";
	
	if( mpC_TextureManager )
	{
		std::vector< EE_MODEL_MATERIAL_C >::const_iterator cI_Material( mco_Materials.begin() ),
	                                                   	   cI_MaterialEnd( mco_Materials.end() );
		while( cI_Material != cI_MaterialEnd )
		{
			if( cI_Material->HasTexture() )
				mpC_TextureManager->Delete( std::string( mS_TextureDirectory + std::string( cI_Material->GetTexture() ) ).c_str() );
		
			cI_Material++;	
		}	
	}	
	mb_Valid = EE_FALSE;
	
	mco_SkeletalAnimations.clear();	
	mco_VertexAnimations.clear();
	
	mb_AnimationRunning = 0;
    mS_CurrentAnimation.clear();
    mf_AnimationTime = 0.0;
}
