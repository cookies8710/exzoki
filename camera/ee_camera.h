#ifndef EE_CAMERA_H
#define EE_CAMERA_H

#include <exzoki/math/ee_math_vector.h> 
#include <exzoki/math/ee_math_point.h> 
#include <exzoki/math/ee_math_matrix4x4.h> 
#include <exzoki/system/ee_system_input_mouse.h>
#include <exzoki/utils/ee_utils_synchronizer.h>

struct EE_CAMERA_MOUSE_SETTINGS_s
{
    EE_FLOAT_t f_Sensitivity, 
               f_XRatio,
               f_YRatio;       
};

namespace EE_EXZOKI_n
{
    const EE_BYTE_t cb_RotationLimitX = 1,
                    cb_RotationLimitY = 2,
                    cb_RotationLimitZ = 4;    
};

class EE_CAMERA_C
{
	public:
		EE_CAMERA_C( void );
		
		void SetSynchronizer( const EE_UTILS_SYNCHRONIZER_C *cpC_synchro );
		
		void BindMouse( const EE_SYSTEM_INPUT_MOUSE_C *cpC_mouse,
                        const EE_SYSTEM_GRAPHICS_OPTIONS_s &crs_gfxSettings );
		void SetMouseSettings( EE_FLOAT_t f_sensitivity,
                               EE_BYTE_t b_invertedX,
                               EE_BYTE_t b_invertedY );
                               
        void SetPosition( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z );
        void SetPosition( const EE_MATH_POINT_C &crC_position );
        
        inline void MoveForward( void );
        inline void MoveBackward( void );
        inline void MoveLeft( void );
        inline void MoveRight( void );
        inline void Move( const EE_MATH_VECTOR_C &crC_moveVector );
        
        // lookat, follow(world_object,chase=true)
        
        void SetRotationLimit( EE_BYTE_t b_axis, EE_MATH_TYPE_t t_bottom, EE_MATH_TYPE_t t_top );
        
        void CameraProc( void );
        void DoTransforms( void ) const;
		
		void SetVelocity( EE_MATH_TYPE_t t_velocity );
		
		EE_MATH_TYPE_t GetVelocity( void ) const;
		// Vrací pozici kamery
        const EE_MATH_POINT_C& GetPosition( void ) const;
        // Vrací pøesný smìr, kterým se kamera dívá
		const EE_MATH_VECTOR_C& GetLookVector( void ) const;
		
		const EE_MATH_VECTOR_C& GetRightVector( void ) const;
		
		const EE_MATH_VECTOR_C& GetUpVector( void ) const;
		
		// Vrací pohybový vektor (Look*Synchro)
		const EE_MATH_VECTOR_C GetCurrentMoveVector( void ) const;
		
	private:
        // Pozice, rotace
		EE_MATH_POINT_C mC_Position;
		EE_MATH_TYPE_t mt_RotationX, mt_RotationY, mt_RotationZ;
	    EE_MATH_TYPE_t mt_RotationXLimitBottom, mt_RotationXLimitTop,
		               mt_RotationYLimitBottom, mt_RotationYLimitTop,
		               mt_RotationZLimitBottom, mt_RotationZLimitTop;
        EE_BYTE_t mb_RotationLimitFlag;               
                           
        // Promenne pro ovladani mysi
        EE_U32_t mu32_ScreenCenterX, mu32_ScreenCenterY;
		const EE_SYSTEM_INPUT_MOUSE_C *mcpC_Mouse;
		EE_CAMERA_MOUSE_SETTINGS_s ms_MouseSettings;
		
		// Synchronizace
		EE_MATH_TYPE_t mt_Velocity;
		const EE_UTILS_SYNCHRONIZER_C *mcpC_Synchronizer;
		
        // Look vektor (pro pohyb, aj.)
        EE_MATH_VECTOR_C mC_LookVector;  
		
		EE_MATH_VECTOR_C mC_UpVector;
		
		EE_MATH_VECTOR_C mC_RightVector;
		
};

#endif
