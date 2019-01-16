#ifndef EE_MODEL_OBJ_MODEL_H
#define EE_MODEL_OBJ_MODEL_H

#include <string>
#include <vector>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/model/obj/ee_model_obj_vertex.h>
#include <exzoki/model/obj/ee_model_obj_texcoord.h>
#include <exzoki/model/obj/ee_model_obj_face.h>
#include <exzoki/model/obj/ee_model_obj_object.h>
#include <exzoki/model/obj/ee_model_obj_material.h>
#include <exzoki/utils/ee_utils_parser_functions.h>

class EE_MODEL_OBJ_MODEL_C
{
    public:
        void Load( EE_CCSTRING_t ccs_path );
        
        const std::vector< EE_MODEL_OBJ_OBJECT_C >& GetObjects( void ) const;
        const std::vector< EE_MODEL_OBJ_MATERIAL_C >& GetMaterials( void ) const;
        
    private:    
        std::vector< EE_MODEL_OBJ_OBJECT_C > mco_Objects;
        std::vector< EE_MODEL_OBJ_MATERIAL_C > mco_Materials;        
};

#endif
