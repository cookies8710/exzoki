#ifndef EE_MODEL_OBJ_TEXCOORD_H
#define EE_MODEL_OBJ_TEXCOORD_H

#include <string>
#include <vector>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/error/ee_error.h>

class EE_MODEL_OBJ_TEXCOORD_C
{
    public:
        EE_MODEL_OBJ_TEXCOORD_C( void );
        EE_MODEL_OBJ_TEXCOORD_C( const std::vector< std::string > &crco_parts );
        
        void Load( const std::vector< std::string > &crco_parts );
        
        EE_FLOAT_t GetU( void ) const;
        EE_FLOAT_t GetV( void ) const;
        EE_FLOAT_t GetW( void ) const;
        
    private:
        EE_FLOAT_t mf_U, mf_V, mf_W;     
};

#endif
