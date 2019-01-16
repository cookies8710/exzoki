#ifndef EE_TEXTURE_MANAGER_H
#define EE_TEXTURE_MANAGER_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/texture/ee_texture.h>
#include <exzoki/template/ee_template_file_manager.h>

class EE_TEXTURE_MANAGER_C: public EE_TEMPLATE_FILE_MANAGER_C< EE_TEXTURE_C >
{
    public:
        EE_TEXTURE_MANAGER_C( void );
        ~EE_TEXTURE_MANAGER_C( void );
        
        virtual void Load( EE_CCSTRING_t ccs_path, 
                           EE_TEXTURE_FILTERING_e e_filtering = EE_TEXTURE_FILTERING_BILINEAR,
                           EE_TEXTURE_ALPHA_e e_alpha = EE_TEXTURE_ALPHA_FALSE,
                           EE_BYTE_t b_r = 0,
                           EE_BYTE_t b_g = 0,
                           EE_BYTE_t b_b = 0,
                           EE_S32_t s32_wrapS = GL_REPEAT,
                           EE_S32_t s32_wrapT = GL_REPEAT,
                           EE_S32_t s32_envMode = GL_MODULATE );
        inline void operator[]( EE_CCSTRING_t ccs_path ) const;
        inline void Bind( EE_CCSTRING_t ccs_path, EE_S32_t s32_layer = GL_TEXTURE0_ARB ) const;    
};

#endif
