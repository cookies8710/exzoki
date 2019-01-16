#ifndef EE_MODEL_OBJ_FACE_H
#define EE_MODEL_OBJ_FACE_H

#include <string>
#include <vector>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/error/ee_error.h>

class EE_MODEL_OBJ_FACE_C
{
    public:
        
        EE_MODEL_OBJ_FACE_C* Load( const std::vector< std::string > &crco_parts );
        
        EE_U32_t GetVertex1Index( void ) const;        
        EE_U32_t GetVertex2Index( void ) const;
        EE_U32_t GetVertex3Index( void ) const;
        
        EE_U32_t GetVertex1TexCoordIndex( void ) const;
        EE_U32_t GetVertex2TexCoordIndex( void ) const;
        EE_U32_t GetVertex3TexCoordIndex( void ) const;
        
    private:  
        void Decode( std::string S_src, 
                     EE_U32_t &ru32_vertexIndex,
                     EE_U32_t &ru32_texCoordIndex,
                     EE_U32_t &ru32_normalIndex );
                
        EE_U32_t mu32_V1, mu32_V2, mu32_V3;    
        EE_U32_t mu32_TC1, mu32_TC2, mu32_TC3;
};

#endif
