#ifndef EE_MODEL_OBJ_OBJECT_H
#define EE_MODEL_OBJ_OBJECT_H

#include <string>
#include <vector>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/model/obj/ee_model_obj_vertex.h>
#include <exzoki/model/obj/ee_model_obj_texcoord.h>
#include <exzoki/model/obj/ee_model_obj_face.h>

class EE_MODEL_OBJ_OBJECT_C
{
    public:        
        void SetName( const std::string &crS_name );
        void AddVertex( const EE_MODEL_OBJ_VERTEX_C &crC_vertex );
        void AddTexCoord( const EE_MODEL_OBJ_TEXCOORD_C &crC_texCoord );
        void AddFace( const EE_MODEL_OBJ_FACE_C &crC_face );
        void SetMaterialName( const std::string &crS_matName  );
        
        void Clear( void );
        
        const std::string& GetName( void ) const;
        const std::string& GetMaterialName( void ) const;
        const std::vector< EE_MODEL_OBJ_VERTEX_C >& GetVertices( void ) const;
        const std::vector< EE_MODEL_OBJ_TEXCOORD_C >& GetTexCoords( void ) const;
        const std::vector< EE_MODEL_OBJ_FACE_C >& GetFaces( void ) const;
        
    private:    
        std::string mS_Name;
        std::string mS_MaterialName;
        
        std::vector< EE_MODEL_OBJ_VERTEX_C > mco_Vertices;   
        std::vector< EE_MODEL_OBJ_TEXCOORD_C > mco_TexCoords;  
        std::vector< EE_MODEL_OBJ_FACE_C > mco_Faces;  
};

#endif
