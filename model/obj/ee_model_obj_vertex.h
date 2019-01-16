#ifndef EE_MODEL_OBJ_VERTEX_H
#define EE_MODEL_OBJ_VERTEX_H

#include <string>
#include <vector>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/error/ee_error.h>

class EE_MODEL_OBJ_VERTEX_C
{
    public:
        EE_MODEL_OBJ_VERTEX_C( void );
        EE_MODEL_OBJ_VERTEX_C( const std::vector< std::string > &crco_parts );
        
        void Load( const std::vector< std::string > &crco_parts );
        
        EE_FLOAT_t GetX( void ) const;
        EE_FLOAT_t GetY( void ) const;
        EE_FLOAT_t GetZ( void ) const;
        
    private:
        EE_FLOAT_t mf_X, mf_Y, mf_Z;    
};

#endif
