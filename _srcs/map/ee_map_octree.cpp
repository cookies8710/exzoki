#include <exzoki/map/ee_map_octree.h>

EE_MAP_OCTREE_C::EE_MAP_OCTREE_C( void ): mpC_Root( 0 ),
                                          mpu32_BitMasks( 0 )
{
}

EE_MAP_OCTREE_C::~EE_MAP_OCTREE_C( void )
{
    Destroy();
}
        
EE_MAP_OCTREE_C EE_MAP_OCTREE_C::operator=( const EE_MAP_OCTREE_C &crC_octree )
{
    if( this != &crC_octree )
    {
        Destroy();
        Build( crC_octree );    
    }    
    
    return( *this );
}
        
void EE_MAP_OCTREE_C::Clear( void )
{
    Destroy();    
}   
  
void EE_MAP_OCTREE_C::Create( const EE_MODEL_C &crC_model,
                              EE_TEXTURE_FILTERING_e e_filtering )
{
    Clear();
      
    // Pøevedu materiály
    EE_U32_t u32_NMaterials( crC_model.GetMaterials().size() );
    for( EE_U32_t u32_Material( 0 ); u32_Material < u32_NMaterials; u32_Material++ )
        mco_Materials.push_back( crC_model.GetMaterials()[ u32_Material ] );
    
    // Nahraju textury
    mS_TextureDirectory = crC_model.GetTextureDirectory();	
	std::vector< EE_MODEL_MATERIAL_C >::const_iterator cI_Material( mco_Materials.begin() ),
	                                                   cI_MaterialEnd( mco_Materials.end() );
	while( cI_Material != cI_MaterialEnd )
	{
		if( cI_Material->HasTexture() )
			mC_TextureManager.Load( std::string( mS_TextureDirectory + std::string( cI_Material->GetTexture() ) ).c_str(),
			                        e_filtering );
		
		cI_Material++;	
	}
      
    // Všechny objekty    
    std::vector< EE_U32_t > co_Indices;   
    EE_U32_t u32_CurrentIndex( 0 ); 
    
    EE_U32_t u32_NObjects( crC_model.GetObjects().size() );
    for( EE_U32_t u32_Object( 0 ); u32_Object < u32_NObjects; u32_Object++ )
    {
        //const EE_MODEL_OBJECT_C &crC_Object( crC_model.GetObjects()[ u32_Object ] );
        
        // Pøidám vertexy
        EE_U32_t uz(crC_model.GetObjects()[ 0 ].GetNVertices());
        
        EE_U32_t u32_NOldVertices( mco_Vertices.size() );        
        EE_U32_t u32_NNewVertices( crC_model.GetObjects()[ u32_Object ].GetNVertices() );
        
        for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < u32_NNewVertices; u32_Vertex++ )
            mco_Vertices.push_back( 
                EE_MODEL_VERTEX_C( 
                    crC_model.GetObjects()[ u32_Object ].GetVertices()[ u32_Vertex * 3 + 0 ],
                    crC_model.GetObjects()[ u32_Object ].GetVertices()[ u32_Vertex * 3 + 1 ],
                    crC_model.GetObjects()[ u32_Object ].GetVertices()[ u32_Vertex * 3 + 2 ] ) );
        
        
        // Pøidám texturové koordináty
        EE_U32_t u32_NOldTexCoords( mco_TexCoords.size() );
        EE_U32_t u32_NNewTexCoords( crC_model.GetObjects()[ u32_Object ].GetNTexCoords() );
        
        for( EE_U32_t u32_TexCoord( 0 ); u32_TexCoord < u32_NNewTexCoords; u32_TexCoord++ )
            mco_TexCoords.push_back(
                EE_MODEL_TEXCOORD_C( 
                    crC_model.GetObjects()[ u32_Object ].GetTexCoords()[ u32_TexCoord * 2 + 0 ],
                    crC_model.GetObjects()[ u32_Object ].GetTexCoords()[ u32_TexCoord * 2 + 1 ] ) ); 
                    
        // Pøidám facy
        EE_U32_t u32_NMeshes( crC_model.GetObjects()[ u32_Object ].GetMeshes().size() );
        for( EE_U32_t u32_Mesh( 0 ); u32_Mesh < u32_NMeshes; u32_Mesh++ )  
        {
            //const EE_MODEL_OBJECT_MESH_C &crC_Mesh( crC_model.GetObjects()[ u32_Object ].GetMeshes()[ u32_Mesh ] );
            
            EE_U32_t u32_NFaces( crC_model.GetObjects()[ u32_Object ].GetMeshes()[ u32_Mesh ].GetNFaces() );
            EE_BOOL_t b_HasMaterial( crC_model.GetObjects()[ u32_Object ].GetMeshes()[ u32_Mesh ].HasMaterial() );
            EE_U32_t u32_MaterialIndex;
            EE_BOOL_t b_HasTexture( 0 );
            if( b_HasMaterial )
            {
                u32_MaterialIndex = crC_model.GetObjects()[ u32_Object ].GetMeshes()[ u32_Mesh ].GetMaterialIndex();
                if( !mco_Materials.size() )
                    EE_ERROR_C( "EE_MAP_OCTREE_C", "Create", EE_ERROR_CODES_n::cS_Internal,
                                "No materials; %d", u32_MaterialIndex );
                if( mco_Materials[ u32_MaterialIndex ].HasTexture() )
                    b_HasTexture = 1;
            }
            for( EE_U32_t u32_Face( 0 ); u32_Face < u32_NFaces; u32_Face++ )
            {
                co_Indices.push_back( u32_CurrentIndex++ );
                EE_MAP_FACE_C C_Face( 
                    crC_model.GetObjects()[ u32_Object ].GetMeshes()[ u32_Mesh ].GetVertexIndices()[ u32_Face * 3 + 0 ] + u32_NOldVertices,
                    crC_model.GetObjects()[ u32_Object ].GetMeshes()[ u32_Mesh ].GetVertexIndices()[ u32_Face * 3 + 1 ] + u32_NOldVertices,
                    crC_model.GetObjects()[ u32_Object ].GetMeshes()[ u32_Mesh ].GetVertexIndices()[ u32_Face * 3 + 2 ] + u32_NOldVertices );
                
                if( b_HasMaterial )
                    C_Face.SetMaterialIndex( u32_MaterialIndex );
                
                if( b_HasTexture )
                {
                    C_Face.SetTexCoordIndexA( crC_model.GetObjects()[ u32_Object ].GetMeshes()[ u32_Mesh ].GetTexCoordIndices()[ u32_Face * 3 + 0 ] + u32_NOldTexCoords );    
                    C_Face.SetTexCoordIndexB( crC_model.GetObjects()[ u32_Object ].GetMeshes()[ u32_Mesh ].GetTexCoordIndices()[ u32_Face * 3 + 1 ] + u32_NOldTexCoords );
                    C_Face.SetTexCoordIndexC( crC_model.GetObjects()[ u32_Object ].GetMeshes()[ u32_Mesh ].GetTexCoordIndices()[ u32_Face * 3 + 2 ] + u32_NOldTexCoords );
                }           
                
                mco_Faces.push_back( C_Face );    
                
            }
        }
    }
    
    
    EE_U32_t u32_NVertices( mco_Vertices.size() );
    if( !u32_NVertices )
        EE_ERROR_C( "EE_MAP_OCTREE_C", "Create", EE_ERROR_CODES_n::cS_Internal, "No vertices" );
    
    EE_FLOAT_t f_XMin( mco_Vertices[ 0 ].GetX() ), 
               f_XMax( mco_Vertices[ 0 ].GetX() ), 
               f_YMin( mco_Vertices[ 0 ].GetY() ), 
               f_YMax( mco_Vertices[ 0 ].GetY() ), 
               f_ZMin( mco_Vertices[ 0 ].GetZ() ), 
               f_ZMax( mco_Vertices[ 0 ].GetZ() ),
               f_Side, f_XSize, f_YSize, f_ZSize;
    
    for( EE_U32_t u32_Vertex( 0 ); u32_Vertex < u32_NVertices; u32_Vertex++ )
    {
        if( mco_Vertices[ u32_Vertex ].GetX() < f_XMin )
            f_XMin = mco_Vertices[ u32_Vertex ].GetX();
        else if( mco_Vertices[ u32_Vertex ].GetX() > f_XMax )
            f_XMax = mco_Vertices[ u32_Vertex ].GetX();
        
        if( mco_Vertices[ u32_Vertex ].GetY() < f_YMin )
            f_YMin = mco_Vertices[ u32_Vertex ].GetY();
        else if( mco_Vertices[ u32_Vertex ].GetY() > f_YMax )
            f_YMax = mco_Vertices[ u32_Vertex ].GetY();
            
        if( mco_Vertices[ u32_Vertex ].GetZ() < f_ZMin )
            f_ZMin = mco_Vertices[ u32_Vertex ].GetZ();
        else if( mco_Vertices[ u32_Vertex ].GetZ() > f_ZMax )
            f_ZMax = mco_Vertices[ u32_Vertex ].GetZ(); 
    }
    
    f_XSize = f_XMax - f_XMin;
    f_YSize = f_YMax - f_YMin;
    f_ZSize = f_ZMax - f_ZMin;
    
    if( f_XSize > f_YSize )
    {
        if( f_XSize > f_ZSize )
            f_Side = f_XSize;
        else
            f_Side = f_ZSize;
    }  
    else 
    {
        if( f_YSize > f_ZSize )
            f_Side = f_YSize;
        else
            f_Side = f_ZSize;
    }
            
    mpC_Root = new EE_MAP_OCTREE_NODE_C( EE_MATH_POINT_C(f_XMin,f_YMin,f_ZMin),f_Side );
    mpC_Root->Divide( co_Indices, mco_Vertices, mco_Faces );
}

void EE_MAP_OCTREE_C::Draw( void ) const
{
    if( mpC_Root )
        mpC_Root->Draw( mco_Vertices, mco_Faces, mco_TexCoords, mco_Materials, mC_TextureManager );    
}

EE_MATH_VECTOR_C EE_MAP_OCTREE_C::CollisionProc( const EE_COLLISION_SPHERE_C &crC_collisionSphere, 
                                    			 const EE_MATH_VECTOR_C &crC_velocity )
{
	if( !mpC_Root )
		return( crC_velocity );
	
	EE_MATH_VECTOR_C C_ActualVelocityVector( crC_velocity );
    EE_COLLISION_INFO_s s_EarliestCollision;
    EE_U32_t u32_NPasses( 0 );
    
    // Dokud koule koliduje s mapou a zároveò dokud, nebyl pøekroèen urèitý poèet rekurzí, pokraèuju v hledání kolizí
    while( u32_NPasses <= EE_EXZOKI_n::cu32_MaxCollisionDetectionPasses &&
        /* C_ActualVelocityVector.LengthPow2() > ??? && */
           mpC_Root->CheckCollision( crC_collisionSphere, 
                           			 C_ActualVelocityVector, 
                           			 s_EarliestCollision,
									 mco_Vertices,
									 mco_Faces ) )
    {
        C_ActualVelocityVector = EE_EXZOKI_n::SlidingVector( crC_collisionSphere, 
                                                             C_ActualVelocityVector, 
                                                             s_EarliestCollision );
                                                             
        u32_NPasses++;
    }
    
    return( C_ActualVelocityVector );     	
}  
 
EE_BOOL_t EE_MAP_OCTREE_C::StaticCheckCollision( const EE_COLLISION_SPHERE_C &crC_collisionSphere )
{
	if( mpC_Root )
        return( mpC_Root->StaticCheckCollision( crC_collisionSphere, mco_Vertices, mco_Faces ) );	
}

void EE_MAP_OCTREE_C::Build( const EE_MAP_OCTREE_C &crC_octree )
{
    if( crC_octree.mpC_Root )
        this->mpC_Root = new EE_MAP_OCTREE_NODE_C( *crC_octree.mpC_Root );
    
    this->mco_Vertices = crC_octree.mco_Vertices;
    this->mco_Faces = crC_octree.mco_Faces;
    this->mco_TexCoords = crC_octree.mco_TexCoords;
    this->mco_Materials = crC_octree.mco_Materials;  
    this->mC_TextureManager = crC_octree.mC_TextureManager;
    
    this->mpu32_BitMasks = new EE_U32_t[ crC_octree.mco_Faces.size() / 32 +
                                         ( crC_octree.mco_Faces.size() % 32 ) ? 1 :0 ];  
}

void EE_MAP_OCTREE_C::Destroy( void )
{
    if( this->mpC_Root )
    {
        delete this->mpC_Root;
        this->mpC_Root = 0;
    }  
    
    if( mpu32_BitMasks )
    {
        delete[] mpu32_BitMasks;    
        mpu32_BitMasks = 0;
    }
    
    mco_Vertices.clear();
    mco_Faces.clear();
    mco_TexCoords.clear();
    mco_Materials.clear();
    mC_TextureManager.Clear();
}
