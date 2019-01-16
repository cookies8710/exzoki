#include <exzoki/model/obj/ee_model_obj_object.h>

void EE_MODEL_OBJ_OBJECT_C::SetName( const std::string &crS_name )
{
    mS_Name = crS_name;
}
        
void EE_MODEL_OBJ_OBJECT_C::AddVertex( const EE_MODEL_OBJ_VERTEX_C &crC_vertex )
{
    mco_Vertices.push_back( crC_vertex );
}
        
void EE_MODEL_OBJ_OBJECT_C::AddTexCoord( const EE_MODEL_OBJ_TEXCOORD_C &crC_texCoord )
{
    mco_TexCoords.push_back( crC_texCoord );
}
        
void EE_MODEL_OBJ_OBJECT_C::AddFace( const EE_MODEL_OBJ_FACE_C &crC_face )
{
    mco_Faces.push_back( crC_face );
}

void EE_MODEL_OBJ_OBJECT_C::SetMaterialName( const std::string &crS_matName  )
{
    mS_MaterialName = crS_matName; 
}
        
void EE_MODEL_OBJ_OBJECT_C::Clear( void )
{
    mS_Name.clear();
    mS_MaterialName.clear();
    mco_Vertices.clear();
    mco_TexCoords.clear();
    mco_Faces.clear();    
}
        
const std::string& EE_MODEL_OBJ_OBJECT_C::GetName( void ) const
{
    return( mS_Name );
}

const std::string& EE_MODEL_OBJ_OBJECT_C::GetMaterialName( void ) const
{
    return( mS_MaterialName );
}
        
const std::vector< EE_MODEL_OBJ_VERTEX_C >& EE_MODEL_OBJ_OBJECT_C::GetVertices( void ) const
{
    return( mco_Vertices );
}
        
const std::vector< EE_MODEL_OBJ_TEXCOORD_C >& EE_MODEL_OBJ_OBJECT_C::GetTexCoords( void ) const
{
    return( mco_TexCoords );
}
        
const std::vector< EE_MODEL_OBJ_FACE_C >& EE_MODEL_OBJ_OBJECT_C::GetFaces( void ) const
{
    return( mco_Faces );
}
