#ifndef EE_TEXTUREC_H
#define EE_TEXTUREC_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>

PROC glMultiTexCoord1fARB = EE_NULL;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = EE_NULL;
PROC glMultiTexCoord3fARB = EE_NULL;
PROC glMultiTexCoord4fARB = EE_NULL;
PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = EE_NULL;
PROC glClientActiveTextureARB = EE_NULL;	

enum EE_TEXTURE_TYPE_e
{
 	EE_TEXTURE_TYPE_UNKNOWN,
 	EE_TEXTURE_TYPE_BMP,
 	EE_TEXTURE_TYPE_JPG,
 	EE_TEXTURE_TYPE_TGA
};

enum EE_TEXTURE_FILTERING_e
{
 	EE_TEXTURE_FILTERING_NEAREST,
 	EE_TEXTURE_FILTERING_BILINEAR,
 	EE_TEXTURE_FILTERING_BILINEAR_NO_MIPMAPPING,
 	EE_TEXTURE_FILTERING_TRILINEAR
};

enum EE_TEXTURE_ALPHA_e
{
 	EE_TEXTURE_ALPHA_FALSE,
 	EE_TEXTURE_ALPHA_TRUE,
 	EE_TEXTURE_ALPHA_BY_GREYSCALE
};

struct EE_TEXTURE_DATA_s
{
 	EE_TEXTURE_FILTERING_e e_Filtering;
 	EE_TEXTURE_ALPHA_e e_Alpha;
 	EE_BYTE_t ab_RGB[ 3 ];
 	EE_S32_t s32_WrapS;
 	EE_S32_t s32_WrapT;
 	EE_S32_t s32_EnvMode;
 	EE_S32_t s32_ColorFormat; // Barevný formát obrázku
 	EE_S32_t s32_NBytes; // Poèet bytù na pixel
};

#define EE_TEXTURE_TGA_RGB		 2		// This tells us it's a normal RGB (really BGR) file
#define EE_TEXTURE_TGA_A		 3		// This tells us it's a ALPHA file
#define EE_TEXTURE_TGA_RLE		10		// This tells us that the targa is Run-Length Encoded (RLE)

struct EE_TEXTURE_TGA_IMAGE_s
{
 	EE_U16_t u16_Channels;			// 3 = RGB, 4 = RGBA
 	EE_U16_t u16_Width;			
 	EE_U16_t u16_Height;				
 	EE_PBYTE_t pb_Data;       
};

class EE_TEXTURE_C
{
 	public:
  		// Implicitní konstruktor
  		EE_TEXTURE_C( void );
  		// Destruktor
  		~EE_TEXTURE_C( void );
  		// Metoda na naètení textury
  		void Load( EE_CCSTRING_t ccs_path, 
             	   EE_TEXTURE_FILTERING_e e_filtering = EE_TEXTURE_FILTERING_BILINEAR,
             	   EE_TEXTURE_ALPHA_e e_alpha = EE_TEXTURE_ALPHA_FALSE,
             	   EE_BYTE_t b_r = 0,
            	   EE_BYTE_t b_g = 0,
             	   EE_BYTE_t b_b = 0,
             	   EE_S32_t s32_wrapS = GL_REPEAT,
            	   EE_S32_t s32_wrapT = GL_REPEAT,
             	   EE_S32_t s32_envMode = GL_MODULATE );
  		// Metoda na zvolení aktuální textury
  		inline void Bind( EE_S32_t s32_layer = GL_TEXTURE0_ARB ) const;
 
		// Zapínaè multitexturingu
  		static EE_BOOL_t EnableMultitexturing( void );
  		// Vrátí maximální poèet multitextur
  		static EE_S32_t GetMaxTextureUnit( void );
 	
 	protected:
		void Destroy( void );
		
 	private:
  		static EE_BOOL_t mb_Multitexturing;
  		static EE_S32_t ms32_MaxTextureUnit;
		
		// Metoda na získání typu textury v souboru
  		EE_TEXTURE_TYPE_e GetTextureType( EE_CCSTRING_t cpc_path );
  		// Metoda pro naètení BMP textury 
  		void LoadBMP( EE_CCSTRING_t ccs_path );
  		// Metoda pro naètení JPEG textury
  		void LoadJPEG( EE_CCSTRING_t cpc_path );
  		// Metoda pro naètení TGA textury
  		void LoadTGA( EE_CCSTRING_t ccs_path );
  		// Metoda na pøidání alfa kanálu
  		void ConvertToRGBA( EE_U32_t u32_width, 
                      	    EE_U32_t u32_height, 
                      	    EE_PBYTE_t* ppb_bits );
  
  		// Metoda na vytvoøení textury
  		void Build( EE_U32_t u32_width, 
              		EE_U32_t u32_height, 
              		EE_PBYTE_t pb_bits );
  
  		// Typ textury (1D, nebo 2D)
  		GLenum me_TextureType;
  		// OGL identifikátor textury
  		EE_U32_t mu32_TextureIndex;
   	    EE_BOOL_t mb_TextureLoaded;
  		// Doèasná data používaná pøi vytváøení textury    
  		EE_TEXTURE_DATA_s *mps_Data;
};

#endif
