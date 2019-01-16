#ifndef EE_MODEL_OBJ_MATERIAL_H
#define EE_MODEL_OBJ_MATERIAL_H

#include <string>
#include <vector>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/error/ee_error.h>

class EE_MODEL_OBJ_MATERIAL_C
{
    public:
        void SetName( const std::string &crS_name );
        void SetTextureFilename( const std::string &crS_name );
        void SetColor( EE_FLOAT_t f_r, EE_FLOAT_t f_g, EE_FLOAT_t f_b );
        
        const std::string& GetName( void ) const;
        const std::string& GetTextureFilename( void ) const;
        EE_FLOAT_t GetColorR( void ) const;
        EE_FLOAT_t GetColorG( void ) const;
        EE_FLOAT_t GetColorB( void ) const;
        
    private:
        EE_FLOAT_t mf_ColorR, mf_ColorG, mf_ColorB;
        std::string mS_Name;
        std::string mS_TextureFilename;    
};

#endif
