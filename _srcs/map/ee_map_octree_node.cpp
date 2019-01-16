#include <exzoki/map/ee_map_octree_node.h>

EE_MAP_OCTREE_NODE_C::EE_MAP_OCTREE_NODE_C( void ): mpu32_FaceIndices( 0 ),
                                                    mu32_NFaces( 0 )
{
    for( EE_BYTE_t b_ChildNode( 0 ); b_ChildNode < 8; b_ChildNode++ )
        mapC_Children[ b_ChildNode ] = 0;    
}

EE_MAP_OCTREE_NODE_C::EE_MAP_OCTREE_NODE_C( const EE_MATH_POINT_C &crC_position,
                                            EE_FLOAT_t f_side ): mpu32_FaceIndices( 0 ),
                                                                 mf_Side( f_side ),
                                                                 mC_Position( crC_position ),
                                                                 mu32_NFaces( 0 )
{
    for( EE_BYTE_t b_ChildNode( 0 ); b_ChildNode < 8; b_ChildNode++ )
        mapC_Children[ b_ChildNode ] = 0;   
}

EE_MAP_OCTREE_NODE_C::~EE_MAP_OCTREE_NODE_C( void )
{
    Destroy();    
}
        
EE_MAP_OCTREE_NODE_C::EE_MAP_OCTREE_NODE_C( const EE_MAP_OCTREE_NODE_C &crC_node )
{
    Build( crC_node );
}

EE_MAP_OCTREE_NODE_C EE_MAP_OCTREE_NODE_C::operator=( const EE_MAP_OCTREE_NODE_C& crC_node  )
{
    if( &crC_node != this )
    {
        Destroy();
        Build( crC_node );    
    }    
    
    return( *this );
}
        
void EE_MAP_OCTREE_NODE_C::Clear( void )
{
    Destroy();    
}
        
void EE_MAP_OCTREE_NODE_C::Set( const EE_MATH_POINT_C &crC_position,
                                EE_FLOAT_t f_side )
{
    mC_Position = crC_position;
    mf_Side = f_side; 
}                                
                                                 
void EE_MAP_OCTREE_NODE_C::SetFaces( const std::vector< EE_U32_t > &crco_faces )
{
    mu32_NFaces = crco_faces.size();
    
    if( mu32_NFaces == 0 )
        EE_ERROR_C( "EE_MAP_OCTREE_NODE_C", "SetFaces", EE_ERROR_CODES_n::cS_Internal, "no faces" );  
    
    if( mpu32_FaceIndices )
        EE_ERROR_C( "EE_MAP_OCTREE_NODE_C", "SetFaces", EE_ERROR_CODES_n::cS_Internal, "non null face pointer" ); 
    
    mpu32_FaceIndices = new EE_U32_t[ mu32_NFaces ];
    
    for( EE_U32_t u32_Face( 0 ); u32_Face < mu32_NFaces; u32_Face++ )
        mpu32_FaceIndices[ u32_Face ] = crco_faces[ u32_Face ]; 
        
    // razeni dle materialu          
}
        
void EE_MAP_OCTREE_NODE_C::Divide( const std::vector< EE_U32_t > &crco_faceIndices,
                                   const std::vector< EE_MODEL_VERTEX_C > &crco_vertices,
                                   const std::vector< EE_MAP_FACE_C > &crco_faces )
{
    // Pokud mám rozdìlit více facù, než je maximální poèet facù na node, dìlím
    if( crco_faceIndices.size() > EE_EXZOKI_n::cu32_OctreeMaxFacesPerNode )
    {
        // Vytvoøím 8 nových krychlí
        
        // Velikost strany nových krychlí
        EE_FLOAT_t f_ChildSide( mf_Side * 0.5 );    
        // Pomocné vektory pro urèení pozic nových krychlí   
        EE_MATH_VECTOR_C C_Right( f_ChildSide, 0.0, 0.0 ),
                         C_Up( 0.0, f_ChildSide, 0.0 ),
                         C_Forward( 0.0, 0.0, f_ChildSide );
        // Vytvoøení nových krychlí
        EE_MAP_OCTREE_NODE_C *apC_Children[ 8 ] = 
        {
            new EE_MAP_OCTREE_NODE_C( mC_Position, f_ChildSide ),
            new EE_MAP_OCTREE_NODE_C( mC_Position + C_Right, f_ChildSide ),
            new EE_MAP_OCTREE_NODE_C( mC_Position + C_Forward, f_ChildSide ),
            new EE_MAP_OCTREE_NODE_C( mC_Position + C_Right + C_Forward, f_ChildSide ),
            new EE_MAP_OCTREE_NODE_C( mC_Position + C_Up, f_ChildSide ),
            new EE_MAP_OCTREE_NODE_C( mC_Position + C_Up + C_Right, f_ChildSide ),
            new EE_MAP_OCTREE_NODE_C( mC_Position + C_Up + C_Forward, f_ChildSide ),
            new EE_MAP_OCTREE_NODE_C( mC_Position + C_Up + C_Right + C_Forward, f_ChildSide )     
        };
        
        // Pøerozdìlení facù
        EE_U32_t u32_NFaces( crco_faceIndices.size() );
        std::vector< std::vector< EE_U32_t > > co_Faces( 8 );
        for( EE_U32_t u32_Face( 0 ); u32_Face < u32_NFaces; u32_Face++ )
        {
            EE_U32_t u32_FaceIndex( crco_faceIndices[ u32_Face ] );
            const EE_MODEL_FACE_C &crC_face( crco_faces[ u32_FaceIndex ] ); 
            EE_MATH_TRIANGLE_C C_FaceTriangle( crco_vertices[ crC_face.GetVertexIndex( 0 ) ].GetPosition(),
                                               crco_vertices[ crC_face.GetVertexIndex( 1 ) ].GetPosition(),
                                               crco_vertices[ crC_face.GetVertexIndex( 2 ) ].GetPosition() );
            
            // Pro všechny nové krychle
            for( EE_BYTE_t b_ChildNode( 0 ); b_ChildNode < 8; b_ChildNode++ ) 
                // Pokud face koliduje s krychlí, pøidám jej do jejího seznamu               
                if( apC_Children[ b_ChildNode ]->Collision( C_FaceTriangle ) )
                    co_Faces[ b_ChildNode ].push_back( u32_FaceIndex );            
        }
        
        // Pro všechny nové krychle
        for( EE_BYTE_t b_ChildNode( 0 ); b_ChildNode < 8; b_ChildNode++ )  
        {
            // Pokud node nemá žádné facy, smažu ho
            if( co_Faces[ b_ChildNode ].size() == 0 )
            {
                delete apC_Children[ b_ChildNode ];
                apC_Children[ b_ChildNode ] = 0;
            }             
            // Pokud má node facy, rekurzivnì pokraèuju v dìlení
            if( mapC_Children[ b_ChildNode ] = apC_Children[ b_ChildNode ] )
                mapC_Children[ b_ChildNode ]->Divide( co_Faces[ b_ChildNode ], 
                                                      crco_vertices,
                                                      crco_faces );
        }
        
    }
    // Jinak facy nodu pøiøadím
    else
    {
        SetFaces( crco_faceIndices );    
    }
    
    return;
}
        
void EE_MAP_OCTREE_NODE_C::Draw( const std::vector< EE_MODEL_VERTEX_C > &crco_vertices,
                                 const std::vector< EE_MAP_FACE_C > &crco_faces,
                                 const std::vector< EE_MODEL_TEXCOORD_C > &crco_texcoords,
                                 const std::vector< EE_MODEL_MATERIAL_C > &crco_materials,
                                 const EE_TEXTURE_MANAGER_C& crC_textureManager ) const
{
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    if( EE_TEST_n::b_ShowOctreeNodeStructure )
    {
    //if( EE_TEST_n::b_ShowOctreeNodeStructureCollidingOnly && !mb_TempCollided );
    //else
	{
        glLineWidth(5.0);
        
    	glDisable(GL_TEXTURE_2D);
    	
    	// Pokud nod poslednì zkolidoval s koulí (fce FastCollisionWithSphere)
    /*	if( mb_TempCollided )  
			glColor3f(1.0,0.0,0.0);  	
    	else*/
    		glColor3f(1.0,1.0,0.0);
    	
    	// nakreslim okraje krychle
    	EE_MATH_VECTOR_C C_RightVector( mf_Side, 0.0, 0.0 ), 
                     	C_UpVector( 0.0, mf_Side, 0.0 ),
                     	C_ForwardVector( 0.0, 0.0, mf_Side );
    	EE_MATH_POINT_C aC_CubePoints[ 8 ] = 
    	{
	        EE_MATH_POINT_C( mC_Position ),//0
	        EE_MATH_POINT_C( mC_Position + C_RightVector ),//1  
	        EE_MATH_POINT_C( mC_Position + C_ForwardVector ),   //2
	        EE_MATH_POINT_C( mC_Position + C_ForwardVector + C_RightVector ),  //3 
	        EE_MATH_POINT_C( mC_Position + C_UpVector ),//4
	        EE_MATH_POINT_C( mC_Position + C_RightVector + C_UpVector ), //5
	        EE_MATH_POINT_C( mC_Position + C_ForwardVector + C_UpVector ),//6  
	        EE_MATH_POINT_C( mC_Position + C_ForwardVector + C_RightVector + C_UpVector ) //7    
	    };
	    
	    EE_BYTE_t ab_Lines[24]=
	    {
	        0, 1,
	        1, 3,
	        3, 2,
	        2, 0, 
	        
	        0, 4,
	        1, 5,
	        2, 6,
	        3, 7,
	        
	        4, 5,
	        5, 7,
	        7, 6,
	        6, 4    
	    };
	    
	    glBegin(GL_LINES);
	        for(int j(0);j<12;j++)
	        {
	            glVertex3f( aC_CubePoints[ab_Lines[2*j+0]].GetX(),
	                        aC_CubePoints[ab_Lines[2*j+0]].GetY(),
	                        aC_CubePoints[ab_Lines[2*j+0]].GetZ() ); 
	            glVertex3f( aC_CubePoints[ab_Lines[2*j+1]].GetX(),
	                        aC_CubePoints[ab_Lines[2*j+1]].GetY(),
	                        aC_CubePoints[ab_Lines[2*j+1]].GetZ() );       
	        }
	    glEnd();
	    
	    glLineWidth(1.0);
	}}
    
    // pokud nemam facy, kreslim dalsi nody
    if(!mu32_NFaces)
    {
        for(EE_BYTE_t b_Child( 0 ); b_Child < 8; b_Child++ )
            if( mapC_Children[ b_Child ] )
                mapC_Children[ b_Child ]->Draw( crco_vertices,crco_faces,crco_texcoords,crco_materials,crC_textureManager);
    }
    else
    {
        for(EE_U32_t u32_Face( 0 ); u32_Face < mu32_NFaces; u32_Face++ )
        {              
            if( !mpu32_FaceIndices )
                EE_ERROR_C( "EE_MAP_OCTREE_NODE_C", "Draw", EE_ERROR_CODES_n::cS_Internal,
                            "mpu32_FaceIndices = 0, nFaces = %d", mu32_NFaces );
            
            if( mpu32_FaceIndices[ u32_Face ] >= crco_faces.size() )
                EE_ERROR_C( "EE_MAP_OCTREE_NODE_C", "Draw", EE_ERROR_CODES_n::cS_Internal,
                            "Face index is equal or larger than number of faces: %d >= %ï",
                            u32_Face, crco_faces.size() );
            const EE_MAP_FACE_C &crC_Face( crco_faces[ mpu32_FaceIndices[ u32_Face ] ] );
            
            glColor3ub( crco_materials[ crC_Face.GetMaterialIndex() ].GetColor( 0 ),
                        crco_materials[ crC_Face.GetMaterialIndex() ].GetColor( 1 ),
                        crco_materials[ crC_Face.GetMaterialIndex() ].GetColor( 2 ) );
            
            
            EE_BOOL_t b_HasTexture;
            if( crco_materials[ crC_Face.GetMaterialIndex() ].HasTexture() )
            {
    			glEnable( GL_TEXTURE_2D );
    			b_HasTexture = EE_TRUE;
    			crC_textureManager[ crco_materials[ crC_Face.GetMaterialIndex() ].GetTexture() ];
    		}
    		else
    		{
    			glDisable( GL_TEXTURE_2D );	
    			b_HasTexture = EE_FALSE;
    		}
            
            glBegin(GL_TRIANGLES);            
            for( EE_BYTE_t b_Vertex( 0 ); b_Vertex < 3; b_Vertex++ )
            {
                if( b_HasTexture )                
                    glTexCoord2f( crco_texcoords[ crC_Face.GetTexCoordIndex(b_Vertex) ].GetU(),
                                  crco_texcoords[ crC_Face.GetTexCoordIndex(b_Vertex) ].GetV() );
                glVertex3f(crco_vertices[crC_Face.GetVertexIndex(b_Vertex)].GetX(),
                           crco_vertices[crC_Face.GetVertexIndex(b_Vertex)].GetY(),
                           crco_vertices[crC_Face.GetVertexIndex(b_Vertex)].GetZ());
                           
            }
            glEnd();           
        }    
        
        
        
        
    }
    
    glPopAttrib();
}
        
void EE_MAP_OCTREE_NODE_C::Build( const EE_MAP_OCTREE_NODE_C &crC_node )
{
    for( EE_BYTE_t b_ChildNode( 0 ); b_ChildNode < 8; b_ChildNode++ )
        if( crC_node.mapC_Children[ b_ChildNode ] )
            this->mapC_Children[ b_ChildNode ] = new EE_MAP_OCTREE_NODE_C
                                                      ( 
                                                        *crC_node.mapC_Children[ b_ChildNode ] 
                                                      ); 
    this->mu32_NFaces = crC_node.mu32_NFaces;
    
    if( crC_node.mpu32_FaceIndices ) 
    {            
        this->mpu32_FaceIndices = new EE_U32_t[ this->mu32_NFaces ]; 
        
        for( EE_U32_t u32_Face( 0 ); u32_Face < this->mu32_NFaces; u32_Face++ )
            this->mpu32_FaceIndices[ u32_Face ] = crC_node.mpu32_FaceIndices[ u32_Face ];             
    }
    else
        this->mpu32_FaceIndices = 0;
    
    
    this->mC_Position = crC_node.mC_Position;    
    this->mf_Side = crC_node.mf_Side;       
}

void EE_MAP_OCTREE_NODE_C::Destroy( void )
{
    for( EE_BYTE_t b_ChildNode( 0 ); b_ChildNode < 8; b_ChildNode++ )
        if( mapC_Children[ b_ChildNode ] )
        {
            delete mapC_Children[ b_ChildNode ];
            mapC_Children[ b_ChildNode ] = 0; 
        }          
    
    if( mpu32_FaceIndices )
    {
        delete[] mpu32_FaceIndices;
        mpu32_FaceIndices = 0;    
    }
    
    mu32_NFaces = 0;
    
    mf_Side = 0.0;
}     

EE_BOOL_t EE_MAP_OCTREE_NODE_C::Collision( const EE_MATH_TRIANGLE_C &crC_triangle ) const
{
    static EE_MATH_VECTOR_C C_RightNormal( 1.0, 0.0, 0.0 ),
                            C_UpNormal( 0.0, 1.0, 0.0 ),
                            C_ForwardNormal( 0.0, 0.0, 1.0 ),
                            C_LeftNormal( -1.0, 0.0, 0.0 ),
                            C_DownNormal( 0.0, -1.0, 0.0 ),
                            C_BackwardNormal( 0.0, 0.0, -1.0 );
    
    EE_MATH_VECTOR_C C_RightVector( mf_Side, 0.0, 0.0 ), 
                     C_UpVector( 0.0, mf_Side, 0.0 ),
                     C_ForwardVector( 0.0, 0.0, mf_Side );
    
    // Sestrojím roviny
    EE_MATH_PLANE_C aC_CubePlanes[ 6 ] = 
    {
        // Pravá strana
        EE_MATH_PLANE_C( C_RightNormal, mC_Position + C_RightVector ),
        // Levá strana
        EE_MATH_PLANE_C( C_LeftNormal, mC_Position ), 
        // Horní strana 
        EE_MATH_PLANE_C( C_UpNormal, mC_Position + C_UpVector ), 
        // Dolní strana
        EE_MATH_PLANE_C( C_DownNormal, mC_Position ),
        // Pøední strana
        EE_MATH_PLANE_C( C_ForwardNormal, mC_Position + C_ForwardVector ), 
        // Zadní strana 
        EE_MATH_PLANE_C( C_BackwardNormal, mC_Position )     
    };
    
    std::vector< EE_MATH_TRIANGLE_C > co_Triangles;
    
    co_Triangles.push_back( crC_triangle );
    
    for( EE_BYTE_t b_Plane( 0 ); b_Plane < 6; b_Plane++ )
    {
        EE_U32_t u32_NTriangles( co_Triangles.size() );   
        
        std::vector< EE_MATH_TRIANGLE_C > co_Temp;
        
        for( EE_U32_t u32_Triangle( 0 ); u32_Triangle < u32_NTriangles; u32_Triangle++ )
        {
            EE_MATH_POSITION_e  e_TrianglePosition = 
                aC_CubePlanes[ b_Plane ].TrianglePosition( co_Triangles[ u32_Triangle ] );
            
            switch( e_TrianglePosition ) 
            {
                case EE_MATH_POSITION_BEHIND:
                case EE_MATH_POSITION_SAME:
                    co_Temp.push_back( co_Triangles[ u32_Triangle ] );
                    break;
                case EE_MATH_POSITION_FRONT:
                    // zahodit
                    break;
                case EE_MATH_POSITION_COLLISION:
                    // Rozdìlit, èást pøed rovinou zahodit, èást za ní pøidat
                    {
                        std::vector< EE_MATH_TRIANGLE_C > co_Front, co_Back;
                        EE_MATH_AGOPS_n::SplitTriangle( co_Triangles[ u32_Triangle ],
                                                        aC_CubePlanes[ b_Plane ],
                                                        co_Front,
                                                        co_Back );  
                                                        
                        for( EE_U32_t u32_Part( 0 ); u32_Part < co_Back.size(); u32_Part++ )
                            co_Temp.push_back( co_Back[ u32_Part ] );
                              
                    }
                    
                    break;    
            }   
        } 
        
        co_Triangles = co_Temp;    
            
    }
    
    return( ( co_Triangles.size() > 0 ) ? 1 : 0 );    
}

EE_BOOL_t EE_MAP_OCTREE_NODE_C::FastCollisionWithSphere( const EE_MATH_SPHERE_C &crC_sphere )
{
	for(EE_BYTE_t b_Child( 0 ); b_Child < 8; b_Child++ )
            if( mapC_Children[ b_Child ] )
                mapC_Children[ b_Child ]->FastCollisionWithSphere( crC_sphere );
	
	return( ( ( crC_sphere.GetPosition().GetX() >= mC_Position.GetX() - crC_sphere.GetRadius() ) &&
			( crC_sphere.GetPosition().GetX() <= mC_Position.GetX() + mf_Side + crC_sphere.GetRadius() ) &&
			( crC_sphere.GetPosition().GetY() >= mC_Position.GetY() - crC_sphere.GetRadius() ) &&
			( crC_sphere.GetPosition().GetY() <= mC_Position.GetY() + mf_Side + crC_sphere.GetRadius() ) &&
			( crC_sphere.GetPosition().GetZ() >= mC_Position.GetZ() - crC_sphere.GetRadius() ) &&
			( crC_sphere.GetPosition().GetZ() <= mC_Position.GetZ() + mf_Side + crC_sphere.GetRadius() ) ) );	
}

EE_BOOL_t EE_MAP_OCTREE_NODE_C::CheckCollision( const EE_COLLISION_SPHERE_C &crC_collisionSphere, 
                              	  				EE_MATH_VECTOR_C C_velocity, 
                              	  				EE_COLLISION_INFO_s &rs_collisionInfo,
		                          				const std::vector< EE_MODEL_VERTEX_C > &crco_vertices,
                   				  				const std::vector< EE_MAP_FACE_C > &crco_faces )   
{
	// Pokud node nemá facy, postupuju v child nodech
	if( !mu32_NFaces )
	{
		std::vector< EE_COLLISION_INFO_s > co_Collisions;
		EE_COLLISION_INFO_s s_CurrentCollisionTest;
		
		// Projdu dceøinné nody
		for( EE_BYTE_t b_Child( 0 ); b_Child < 8; b_Child++ )
            if( mapC_Children[ b_Child ] )
                if( mapC_Children[ b_Child ]->FastCollisionWithSphere( crC_collisionSphere ) )
                {
					// Pokud je v nodu nalezena kolize, uložím si ji
					if( mapC_Children[ b_Child ]->CheckCollision( crC_collisionSphere, 
					                                              C_velocity, 
																  s_CurrentCollisionTest, 
																  crco_vertices, 
																  crco_faces  ) )
						co_Collisions.push_back( s_CurrentCollisionTest );						
				}
		
		// Pokud jsou nìjaké kolize, najdu nejdøívìjší a vrátím ji
		if( co_Collisions.size() )
		{
			EE_BYTE_t b_NCollisions( co_Collisions.size() ),
			          b_EarliestCollision( 0 );			    
			EE_MATH_TYPE_t t_EarliestCollisionTime( 2.0 ); // Inicializuji 2.0, protože èas mùže být maximálnì 1.0
			for( EE_BYTE_t b_Collision( 0 ); b_Collision < b_NCollisions; b_Collision++ )
				if( co_Collisions[ b_Collision ].t_Time < t_EarliestCollisionTime )
				{
					t_EarliestCollisionTime = co_Collisions[ b_Collision ].t_Time;
					b_EarliestCollision = b_Collision;	
				}
			
			rs_collisionInfo = co_Collisions[ b_EarliestCollision ];
			
			return( 1 );
			
		}
		else
		// Pokud nejsou nalezeny žádné kolize, vratím 0
			return( 0 );  
	}
	else
	// Node má facy, testují kolizi proti nim
	{
		if( C_velocity.Length() < 0.001 )
        	return( 0 );
    
    	EE_COLLISION_INFO_s s_EarliestCollision,
                        	s_ActualCollision;
                                
	    EE_BOOL_t b_Collision( 0 ),
	              b_Set( 0 );    
	              
	    // Projdu všechny trojuhelniky objektu   
	    for( EE_U32_t u32_Face( 0 ); 
	         u32_Face < mu32_NFaces; 
	         u32_Face++ )
	    {               
	        EE_BOOL_t b_ActualCollision( 0 );      
	        
	        const EE_MAP_FACE_C &crC_Face( crco_faces[ mpu32_FaceIndices[ u32_Face ] ] );
	        
	        // Spoèítám kolizi  
	        b_ActualCollision = EE_EXZOKI_n::CollisionSphereTriangle(
	            crC_collisionSphere,
	            C_velocity,
	            EE_MATH_TRIANGLE_C(
	                crco_vertices[ crC_Face.GetVertexIndex( 0 ) ].GetPosition(),
	                crco_vertices[ crC_Face.GetVertexIndex( 1 ) ].GetPosition(),
	                crco_vertices[ crC_Face.GetVertexIndex( 2 ) ].GetPosition() ),
	                s_ActualCollision );
	         
	          
	        // Pokud nastala kolize, tak pokud je døíve než dosavadní nejdøívìjší kolize, uložím ji        
	        if( b_ActualCollision )
	        {            
	            b_Collision = 1;
	            if( s_ActualCollision.t_Time < s_EarliestCollision.t_Time || !b_Set)
	            {
	                b_Set = 1;
	                s_EarliestCollision = s_ActualCollision;
	            }
	        }
	    }
	     
	    rs_collisionInfo = s_EarliestCollision;
	    
	    return( b_Collision );
	}
}  

EE_BOOL_t EE_MAP_OCTREE_NODE_C::StaticCheckCollision( const EE_COLLISION_SPHERE_C &crC_collisionSphere,
                                                      const std::vector< EE_MODEL_VERTEX_C > &crco_vertices,
                   									  const std::vector< EE_MAP_FACE_C > &crco_faces )
{
	// Pokud node nemá facy, postupuju v child nodech
	if( !mu32_NFaces )
    {
        for( EE_BYTE_t b_Child( 0 ); b_Child < 8; b_Child++ )
            if( mapC_Children[ b_Child ] )
                if( mapC_Children[ b_Child ]->StaticCheckCollision( crC_collisionSphere, crco_vertices, crco_faces ) )
                	return( 1 );
        
        return( 0 );
    }
    else
    {
		
		
	    for( EE_U32_t u32_Face( 0 ); u32_Face < mu32_NFaces; u32_Face++ )
		{      
			const EE_MAP_FACE_C &crC_Face( crco_faces[ mpu32_FaceIndices[ u32_Face ] ] );
			  
	        if( EE_MATH_AGOPS_n::Collision(
	                EE_MATH_TRIANGLE_C(
	                crco_vertices[ crC_Face.GetVertexIndex( 0 ) ].GetPosition(),
	                crco_vertices[ crC_Face.GetVertexIndex( 1 ) ].GetPosition(),
	                crco_vertices[ crC_Face.GetVertexIndex( 2 ) ].GetPosition() ),
	                crC_collisionSphere ) 
	          )
	        return( 1 );
		}	                
	   	
		return( 0 );			
	}		
}
