#include <exzoki/camera/ee_camera.h>

EE_CAMERA_C::EE_CAMERA_C( void ): mt_RotationX( 0.0 ),
                                  mt_RotationY( 0.0 ),
                                  mt_RotationZ( 0.0 ),
                                  mt_Velocity( 1.0 ),
                                  mcpC_Mouse( 0 ),
                                  mcpC_Synchronizer( 0 ),
                                  mb_RotationLimitFlag( 0 )
{
    ms_MouseSettings.f_XRatio = 1.0;
    ms_MouseSettings.f_YRatio = 1.0;
    ms_MouseSettings.f_Sensitivity = 1.0;
}
		
void EE_CAMERA_C::SetSynchronizer( const EE_UTILS_SYNCHRONIZER_C *cpC_synchro )
{
    mcpC_Synchronizer = cpC_synchro;       
}
		
void EE_CAMERA_C::BindMouse( const EE_SYSTEM_INPUT_MOUSE_C *cpC_mouse,
                             const EE_SYSTEM_GRAPHICS_OPTIONS_s &crs_gfxSettings )
{
    mcpC_Mouse = cpC_mouse;
    mu32_ScreenCenterX = crs_gfxSettings.u32_WindowWidth / 2;
    mu32_ScreenCenterY = crs_gfxSettings.u32_WindowHeight / 2;        
}                             
                             
void EE_CAMERA_C::SetMouseSettings( EE_FLOAT_t f_sensitivity,
                                    EE_BYTE_t b_invertedX,
                                    EE_BYTE_t b_invertedY )
{
    ms_MouseSettings.f_XRatio = ( b_invertedX ) ? -1.0 : 1.0;
    ms_MouseSettings.f_YRatio = ( b_invertedY ) ? -1.0 : 1.0;
    ms_MouseSettings.f_Sensitivity = f_sensitivity;        
}
                               
void EE_CAMERA_C::SetPosition( EE_MATH_TYPE_t t_x, EE_MATH_TYPE_t t_y, EE_MATH_TYPE_t t_z )
{
    mC_Position.Set( t_x, t_y, t_z );    
}

void EE_CAMERA_C::SetPosition( const EE_MATH_POINT_C &crC_position )
{
    mC_Position = crC_position;        
}
        
inline void EE_CAMERA_C::MoveForward( void )
{
    mC_Position = mC_Position + mC_LookVector * mcpC_Synchronizer->GetSynchro();        
}

inline void EE_CAMERA_C::MoveBackward( void )
{
    mC_Position = mC_Position - mC_LookVector * mcpC_Synchronizer->GetSynchro();        
}

inline void EE_CAMERA_C::MoveLeft( void )
{
    mC_Position = mC_Position - mC_RightVector * mcpC_Synchronizer->GetSynchro();        
}

inline void EE_CAMERA_C::MoveRight( void )
{
    mC_Position = mC_Position + mC_RightVector * mcpC_Synchronizer->GetSynchro();        
}

inline void EE_CAMERA_C::Move( const EE_MATH_VECTOR_C &crC_moveVector )
{
    mC_Position = mC_Position + crC_moveVector;    
}
     
void EE_CAMERA_C::SetRotationLimit( EE_BYTE_t b_axis, 
                                    EE_MATH_TYPE_t t_bottom, 
                                    EE_MATH_TYPE_t t_top )
{
    switch( b_axis )
    {
        case 0:
            mb_RotationLimitFlag |= EE_EXZOKI_n::cb_RotationLimitX;
            mt_RotationXLimitBottom = t_bottom;
            mt_RotationXLimitTop = t_top;
            break;
        case 1:
            mb_RotationLimitFlag |= EE_EXZOKI_n::cb_RotationLimitY;
            mt_RotationYLimitBottom = t_bottom;
            mt_RotationYLimitTop = t_top;
            break;
        case 2:
            mb_RotationLimitFlag |= EE_EXZOKI_n::cb_RotationLimitZ;
            mt_RotationZLimitBottom = t_bottom;
            mt_RotationZLimitTop = t_top;
            break;    
    }
    
    return;    
}     
          
void EE_CAMERA_C::CameraProc( void )
{
    static const EE_MATH_TYPE_t ct_DegsToRads = 3.141592f / 180.0f;
    static EE_MATH_TYPE_t t_Ratio;
    static EE_MATH_TYPE_t at_RotationRadians[ 3 ];
  	static EE_FLOAT_t f_Time( 0.0 );   
  
    if( mcpC_Mouse && f_Time >= 0.015  )
    {
        POINT s_MousePosition;
        GetCursorPos( &s_MousePosition );
        mt_RotationX -= EE_MATH_TYPE_t( (EE_S32_t)s_MousePosition.y - (EE_S32_t)mu32_ScreenCenterY ) * 
                        ms_MouseSettings.f_Sensitivity * f_Time
                        /*mcpC_Synchronizer->GetSynchro()*/;
        mt_RotationY -= EE_MATH_TYPE_t( (EE_S32_t)s_MousePosition.x - (EE_S32_t)mu32_ScreenCenterX ) * 
                        ms_MouseSettings.f_Sensitivity * f_Time 
                        /*mcpC_Synchronizer->GetSynchro()*/;
        SetCursorPos( mu32_ScreenCenterX, mu32_ScreenCenterY ); 
		
		f_Time = 0.0;   
    }
    
    f_Time += mcpC_Synchronizer->GetSynchro(); 
    
  
    if( mb_RotationLimitFlag & EE_EXZOKI_n::cb_RotationLimitX )
    {
        if( mt_RotationX < mt_RotationXLimitBottom )
            mt_RotationX = mt_RotationXLimitBottom;  
        else if( mt_RotationX > mt_RotationXLimitTop )
            mt_RotationX = mt_RotationXLimitTop;     
    }
    if( mb_RotationLimitFlag & EE_EXZOKI_n::cb_RotationLimitY )
    {
        if( mt_RotationY < mt_RotationYLimitBottom )
            mt_RotationY = mt_RotationYLimitBottom;  
        else if( mt_RotationY > mt_RotationYLimitTop )
            mt_RotationY = mt_RotationYLimitTop;     
    }
    if( mb_RotationLimitFlag & EE_EXZOKI_n::cb_RotationLimitZ )
    {
        if( mt_RotationZ < mt_RotationZLimitBottom )
            mt_RotationZ = mt_RotationZLimitBottom;  
        else if( mt_RotationZ > mt_RotationZLimitTop )
            mt_RotationZ = mt_RotationZLimitTop;     
    }
 
    at_RotationRadians[ 0 ] = mt_RotationX * ct_DegsToRads;
    at_RotationRadians[ 1 ] = mt_RotationY * ct_DegsToRads;
    at_RotationRadians[ 2 ] = mt_RotationZ * ct_DegsToRads;   
    
    mC_LookVector = EE_MATH_MATRIX4X4_C::RotationXMatrix((3.1415/180.0) * mt_RotationX) * 
                    EE_MATH_VECTOR_C(0.0,0.0,-1.0);	
    mC_LookVector = EE_MATH_MATRIX4X4_C::RotationYMatrix((3.1415/180.0) * mt_RotationY) * 
                    mC_LookVector;
	mC_LookVector = EE_MATH_MATRIX4X4_C::RotationZMatrix((3.1415/180.0) * mt_RotationZ) * 
                    mC_LookVector;
    
    mC_UpVector = EE_MATH_MATRIX4X4_C::RotationXMatrix((3.1415/180.0) * mt_RotationX) * 
                     EE_MATH_VECTOR_C(0.0,1.0,0.0);	
    mC_UpVector = EE_MATH_MATRIX4X4_C::RotationYMatrix((3.1415/180.0) * mt_RotationY) * 
                     mC_UpVector;
	mC_UpVector = EE_MATH_MATRIX4X4_C::RotationZMatrix((3.1415/180.0) * mt_RotationZ) * 
                     mC_UpVector;
                     
    mC_RightVector = mC_LookVector % mC_UpVector;
        
    mC_LookVector = mC_LookVector * mt_Velocity;
    mC_RightVector = mC_RightVector * mt_Velocity;
    mC_UpVector = mC_UpVector * mt_Velocity;
}

void EE_CAMERA_C::DoTransforms( void ) const
{
    glRotatef( -mt_RotationX, 1.0, 0.0, 0.0 );  
    glRotatef( -mt_RotationY, 0.0, 1.0, 0.0 );  
    glRotatef( -mt_RotationZ, 0.0, 0.0, 1.0 );  
	glTranslatef( -mC_Position.GetX(), -mC_Position.GetY(), -mC_Position.GetZ() );    
}
		
void EE_CAMERA_C::SetVelocity( EE_MATH_TYPE_t t_velocity )
{
    mt_Velocity = t_velocity; 
}

EE_MATH_TYPE_t EE_CAMERA_C::GetVelocity( void ) const
{
	return( mt_Velocity );	
}

const EE_MATH_POINT_C& EE_CAMERA_C::GetPosition( void ) const
{
    return( mC_Position );    
}

const EE_MATH_VECTOR_C& EE_CAMERA_C::GetLookVector( void ) const
{
    return( mC_LookVector );    
}

const EE_MATH_VECTOR_C& EE_CAMERA_C::GetRightVector( void ) const
{
	return( mC_RightVector );	
}
		
const EE_MATH_VECTOR_C& EE_CAMERA_C::GetUpVector( void ) const
{
	return( mC_UpVector );	
}

const EE_MATH_VECTOR_C EE_CAMERA_C::GetCurrentMoveVector( void ) const
{
    return( mC_LookVector * mcpC_Synchronizer->GetSynchro() );    
}

