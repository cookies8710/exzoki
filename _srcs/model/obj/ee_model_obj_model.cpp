#include <exzoki/model/obj/ee_model_obj_model.h>

void EE_MODEL_OBJ_MODEL_C::Load( EE_CCSTRING_t ccs_path )
{
    std::ifstream C_File( ccs_path );    
            
    if( !C_File.good() )
        EE_ERROR_C( "EE_MODEL_OBJ_MODEL_C", "Load", EE_ERROR_CODES_n::cS_Internal, ccs_path );
    EE_S32_t s32_CurrentObject( -1 );
                
    while( !C_File.eof() ) 
    {
        EE_CHAR_t c_Char;
        std::string S_Line;
        // Naètu celý jeden øádek
        while( ( c_Char = C_File.get() ) != '\n' && !C_File.eof() )  
            S_Line += c_Char;
        if( C_File.get() != '\n' )
            C_File.unget();
        if( C_File.eof() )
            break;
                
        std::vector< std::string > co_Parts( EE_EXZOKI_n::CutString( S_Line ) );    
                
        if( co_Parts[ 0 ] == std::string( "v" ) )
        {
            EE_MODEL_OBJ_VERTEX_C C_Vertex( co_Parts );
            mco_Objects[ s32_CurrentObject ].AddVertex( C_Vertex );                        
        }
        else if( co_Parts[ 0 ] == std::string( "vt" ) )
        {
            EE_MODEL_OBJ_TEXCOORD_C C_TexCoord( co_Parts );
            mco_Objects[ s32_CurrentObject ].AddTexCoord( C_TexCoord );          
        }
        else if( co_Parts[ 0 ] == std::string( "f" ) )
        {
            EE_MODEL_OBJ_FACE_C C_Face;
            EE_MODEL_OBJ_FACE_C *pC_Face( C_Face.Load( co_Parts ) );
            mco_Objects[ s32_CurrentObject ].AddFace( C_Face );
            if( pC_Face )
            {
                mco_Objects[ s32_CurrentObject ].AddFace( *pC_Face );
                delete pC_Face;   
            }                        
        }
        else if( co_Parts[ 0 ] == std::string( "o" ) )
        {
            mco_Objects.push_back( EE_MODEL_OBJ_OBJECT_C() );
            s32_CurrentObject = mco_Objects.size() - 1;
                    
            mco_Objects[ s32_CurrentObject ].SetName( co_Parts[ 1 ] );                    
        }
        else if( co_Parts[ 0 ] == std::string( "#" ) )
        {
        // nic   
        }
        else if( co_Parts[ 0 ] == std::string( "mtllib" ) )
        {
            std::ifstream C_MaterialFile( co_Parts[ 1 ].c_str() );
            EE_S32_t s32_CurrentMaterial(-1);
            while( !C_MaterialFile.eof() ) 
            {
                EE_CHAR_t c_Char;
                std::string S_Line2;                        
                // Naètu celý jeden øádek
                while( ( c_Char = C_MaterialFile.get() ) != '\n' && !C_MaterialFile.eof() )  
                    S_Line2 += c_Char;                        
                
                if( C_MaterialFile.eof() )
                    break;
                        
                std::vector< std::string > co_Parts2( EE_EXZOKI_n::CutString( S_Line2 ) );    
                if( co_Parts2[0]==std::string("newmtl") )
                {
                    mco_Materials.push_back(EE_MODEL_OBJ_MATERIAL_C());
                    s32_CurrentMaterial=mco_Materials.size()-1;   
                    mco_Materials[s32_CurrentMaterial].SetName(co_Parts2[1]); 
                }
                else if( co_Parts2[0]==std::string("Kd") )
                {
                    mco_Materials[s32_CurrentMaterial].SetColor(
                    atof(co_Parts2[1].c_str()),
                    atof(co_Parts2[2].c_str()),
                    atof(co_Parts2[3].c_str()) );
                }
                else if( co_Parts2[0]==std::string("map_Kd") )
                {
                    EE_U32_t u32_Filename(0);
                    std::string S_Tmp;
                    for( EE_U32_t u32_Part( 1 ); u32_Part < co_Parts2.size(); u32_Part++ )
		    	S_Tmp += co_Parts2[ u32_Part ];
                    bool t(true);
                    while( t )
                    {
                        if(S_Tmp.find("\\") < S_Tmp.size())
                        {
                            u32_Filename = S_Tmp.find("\\");   
                            S_Tmp = S_Tmp.substr( u32_Filename + 1, S_Tmp.size() );
                        }
                        else
                            t = false;         
                    }
                            
                    mco_Materials[s32_CurrentMaterial].SetTextureFilename(S_Tmp);
                   // S_Tmp.substr(u32_Filename+1,S_Tmp.size())  ); 
                }
            }
            C_MaterialFile.close();   
        }
        else if( co_Parts[ 0 ] == std::string( "usemtl" ) )
        {
            if( mco_Objects[ s32_CurrentObject ].GetMaterialName().size() == 0 )
                mco_Objects[ s32_CurrentObject ].SetMaterialName( co_Parts[ 1 ] );  
            else if( mco_Objects[ s32_CurrentObject ].GetMaterialName() != co_Parts[ 1 ] )
                EE_ERROR_C( "EE_MODEL_OBJ_MODEL_C", "Load", EE_ERROR_CODES_n::cS_Internal, "Different materials for 1 object" );         
        }
                
    }
        
        
    C_File.close();
}
        
const std::vector< EE_MODEL_OBJ_OBJECT_C >& EE_MODEL_OBJ_MODEL_C::GetObjects( void ) const
{return(mco_Objects);}
const std::vector< EE_MODEL_OBJ_MATERIAL_C >& EE_MODEL_OBJ_MODEL_C::GetMaterials( void ) const
{return(mco_Materials);}
