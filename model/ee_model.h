#ifndef EE_MODELC_H
#define EE_MODELC_H

#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_file.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/model/ee_model_object.h>
#include <exzoki/model/ee_model_material.h> 
#include <exzoki/texture/ee_texture_manager.h>
#include <exzoki/model/obj/ee_model_obj_model.h>
#include <exzoki/model/ee_model_animation.h>
#include <exzoki/utils/ee_utils_synchronizer.h>
#include <exzoki/model/ee_model_vertex_animation.h>
#include <string>
#include <map>

namespace EE_MODEL_TMD_n
{
 	const std::string cS_Header( "tmd" ),
	                  cS_TMD( "tmd" );
 	const EE_U16_t cu16_Version( 0x1005 );
};

enum EE_MODEL_ANIMATION_TYPE_e { EE_MODEL_ANIMATION_NONE = 0,
                                 EE_MODEL_ANIMATION_VERTEX = 1, 
								 EE_MODEL_ANIMATION_SKELETAL = 2 };

std::vector<EE_COLLISION_SPHERE_C> co_CSs;

class EE_MODEL_C
{
 	public:
  		EE_MODEL_C( void );
  		~EE_MODEL_C( void );
  
  		void Load( EE_CCSTRING_t ccs_path );
  		void LoadWithTextures( EE_CCSTRING_t ccs_path,
		                       EE_CCSTRING_t ccs_textureDirectory,
							   EE_TEXTURE_FILTERING_e e_filtering );			  
		void SetTextureManager( EE_TEXTURE_MANAGER_C& rC_textureManager );
    
    	void LoadVertexAnimation( EE_CCSTRING_t ccs_path );    	
    	void LoadSkeletalAnimation( EE_CCSTRING_t ccs_path );
    	
    	void PlayVertexAnimation( EE_CCSTRING_t ccs_path, EE_U32_t u32_repeats = 1 );
    	void PlayAnimation( EE_CCSTRING_t ccs_path, EE_U32_t u32_repeats = 1 );
		void StopAnimation( void );
		
		void Draw( void );
		
		void DrawBones( const EE_SYSTEM_COLOR_s &crs_headColor, 
		                const EE_SYSTEM_COLOR_s &crs_tailColor );
		void DrawBones( const EE_SYSTEM_COLOR_s &crs_staticHeadColor, 
		                const EE_SYSTEM_COLOR_s &crs_staticTailColor,
						const EE_SYSTEM_COLOR_s &crs_animatedHeadColor, 
		                const EE_SYSTEM_COLOR_s &crs_animatedTailColor );
		    
 		std::vector< EE_MODEL_OBJECT_C > GetObjects( void ) const;
 		std::vector< EE_MODEL_MATERIAL_C > GetMaterials( void ) const;
 		
 		std::string GetTextureDirectory( void ) const;
 
 	private: 		
		void DrawStatic( void );
		void DrawAnimation( void );
			  
        void LoadOBJ( EE_CCSTRING_t ccs_path );	
  		void LoadTMD( EE_CCSTRING_t ccs_path );
        
        
  		void Destroy( void );
  
  		std::vector< EE_MODEL_OBJECT_C > mco_Objects;   
  		std::vector< EE_MODEL_MATERIAL_C > mco_Materials;   
        EE_TEXTURE_MANAGER_C *mpC_TextureManager;
        std::string mS_TextureDirectory;
      	
      	
      	
		EE_BOOL_t mb_AnimationRunning;
      	std::string mS_CurrentAnimation;
      	EE_FLOAT_t mf_AnimationTime;
      	EE_U32_t mu32_AnimationRepeatsLeft;
		EE_MODEL_ANIMATION_TYPE_e me_AnimationType;      
      
      	EE_UTILS_SYNCHRONIZER_C mC_Synchro;
      
      	// Vertexové animace
      	std::map< std::string, EE_MODEL_VERTEX_ANIMATION_C > mco_VertexAnimations;
      
		// Skeletální animace
		std::map< std::string, EE_MODEL_ANIMATION_C > mco_SkeletalAnimations;
      
    	EE_BOOL_t mb_Valid;
};

#endif
