#include <exzoki/system/ee_system_window_opengl.h>

EE_SYSTEM_WINDOW_OPENGL_C::EE_SYSTEM_WINDOW_OPENGL_C( void ): mh_RC( NULL )
{
}

EE_SYSTEM_WINDOW_OPENGL_C::~EE_SYSTEM_WINDOW_OPENGL_C( void )
{
 	Destroy();                                                         
} 
  
void EE_SYSTEM_WINDOW_OPENGL_C::Create( HINSTANCE h_instance,
                                        EE_CCSTRING_t ccs_wndClassName,
                                        EE_CCSTRING_t ccs_wndName,
                                        const EE_SYSTEM_GRAPHICS_OPTIONS_s& crs_graphicsOptions,
                                        WNDPROC pf_WindowProcedure )
{
 	// Nejdøíve vytvoøím obyèejné okno
 	EE_SYSTEM_WINDOW_C::Create( h_instance, ccs_wndClassName, ccs_wndName, crs_graphicsOptions, pf_WindowProcedure );
	
	EE_EXZOKI_n::pv_CurrentWindow = (EE_PVOID_t)this;
		
	// Na vytvoøené okno navážu OpenGL
	EE_S32_t s32_PixelFormat;
 	HDC h_DC( EE_SYSTEM_WINDOW_C::GetHDC() );
 	mpC_LogFile->Write( "Getting Device Context handle...%d\n", h_DC );
 	
 	// Nastavím pixel format descriptor
 	PIXELFORMATDESCRIPTOR s_PFD = 
 	{
		sizeof(PIXELFORMATDESCRIPTOR),				
		1,										
		PFD_DRAW_TO_WINDOW |					
		PFD_SUPPORT_OPENGL |					
		PFD_DOUBLEBUFFER,							
		PFD_TYPE_RGBA,							
		ms_GraphicsOptions.u32_ColorDepth,									
		0, 0, 0, 0, 0, 0,							
		0,										
		0,											
		0,											
		0, 0, 0, 0,									
		32,	// Depth buffer bits									
		1, // Stencil buffer bits										
		0,										
		PFD_MAIN_PLANE,							
		0,										
		0, 0, 0									
	};
	
	// Najdu pixel format s požadovanými vlastnostmi
 	s32_PixelFormat = ChoosePixelFormat( h_DC, &s_PFD );
 	mpC_LogFile->Write( "Choosing pixel format..." );
     if( !s32_PixelFormat )
  		EE_ERROR_C( "EE_SYSTEM_WINDOW_OPENGL_C", "Create", EE_ERROR_CODES_n::cS_CannotChoosePixelFormat );
    mpC_LogFile->Write( "OK, pixel format = %d\n", s32_PixelFormat );
 
 	// Nastavím pixel format
 	mpC_LogFile->Write( "Setting pixel format..." );
 	if( !SetPixelFormat( h_DC, s32_PixelFormat, &s_PFD ) )
  		EE_ERROR_C( "EE_SYSTEM_WINDOW_OPENGL_C", "Create", EE_ERROR_CODES_n::cS_CannotSetPixelFormat );
    mpC_LogFile->Write( "OK\n" );
 
 	// Vytvoøím rendering kontext
 	mpC_LogFile->Write( "Creating rendering context..." );
	if( !( mh_RC = wglCreateContext( h_DC ) ) )
  		EE_ERROR_C( "EE_SYSTEM_WINDOW_OPENGL_C", "Create", EE_ERROR_CODES_n::cS_CannotCreateRenderingContext );
    mpC_LogFile->Write( "OK, rednering context = %d\n", mh_RC );
  
    mpC_LogFile->Write( "Binding RC with DC..." );
 	if( !wglMakeCurrent( h_DC, mh_RC ) )
  		EE_ERROR_C( "EE_SYSTEM_WINDOW_OPENGL_C", "Create", EE_ERROR_CODES_n::cS_CannotMakeCurrent );
    mpC_LogFile->Write( "OK\n" );
  
   // Pokud je v grafických nasatveních fullscreen mód, nastavím ho
 	if( crs_graphicsOptions.b_Fullscreen )
 	{
  		mpC_LogFile->Write( "Setting up fullscreen..." );
        DEVMODE s_FullscreenMode;
  		ZeroMemory( &s_FullscreenMode, sizeof( s_FullscreenMode ) );
  		s_FullscreenMode.dmSize = sizeof( s_FullscreenMode );
  		s_FullscreenMode.dmBitsPerPel = crs_graphicsOptions.u32_ColorDepth;
  		s_FullscreenMode.dmPelsWidth = crs_graphicsOptions.u32_WindowWidth;
  		s_FullscreenMode.dmPelsHeight = crs_graphicsOptions.u32_WindowHeight;
  		s_FullscreenMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
  		if( ChangeDisplaySettings( &s_FullscreenMode, 0x00000004 ) != DISP_CHANGE_SUCCESSFUL )
   		   EE_ERROR_C( "EE_SYSTEM_WINDOW_OPENGL_C", "Create", EE_ERROR_CODES_n::cS_CannotSetFullscreen );
  		mpC_LogFile->Write( "OK\n" );
        // Schovám kurzor myši
		ShowCursor( false );
 	}     
    
    return;
}                                  
                                                 
void EE_SYSTEM_WINDOW_OPENGL_C::ResizeProc( const EE_SYSTEM_OPENGL_PROJECTION_DESCRIPTOR_s& crs_projectionDescriptor )
{
 	glViewport( 0, 0, ms_GraphicsOptions.u32_WindowWidth, ms_GraphicsOptions.u32_WindowHeight );

 	// Nastavím projekèní matici podle požadavkù
	glMatrixMode( GL_PROJECTION );
 	glLoadIdentity();

 	switch( crs_projectionDescriptor.e_ProjectionType )
 	{
  		case EE_SYSTEM_OPENGL_ORTHO:
       		glOrtho( crs_projectionDescriptor.f_Left,
                		crs_projectionDescriptor.f_Right,
                		crs_projectionDescriptor.f_Bottom,
                		crs_projectionDescriptor.f_Top,
                		crs_projectionDescriptor.f_ZNearest,
                		crs_projectionDescriptor.f_ZFarest );
   		break;
  		case EE_SYSTEM_OPENGL_PERSPECTIVE:
       		gluPerspective( crs_projectionDescriptor.f_Fovy,
                       		4.0f / 3.0f,
                       		crs_projectionDescriptor.f_ZNearest,
                       		crs_projectionDescriptor.f_ZFarest );
       		break;
  		default:
   		   break;
 	}

 	// Pøepnu zpìt do modelview matice
	glMatrixMode( GL_MODELVIEW );
 	glLoadIdentity();
 	
 	return;
}

WPARAM EE_SYSTEM_WINDOW_OPENGL_C::Run( void(*pf_function)( void ) )
{
 	MSG s_Message;
 	EE_BYTE_t b_Exit = false;
 	HDC h_DC( EE_SYSTEM_WINDOW_C::GetHDC() );
 
 	while( !b_Exit )
 	{
  		if( PeekMessage( &s_Message, NULL, 0, 0, PM_REMOVE ) )
  		{
       		if( s_Message.message == WM_QUIT )
       		{
       			b_Exit = true;
        			continue;
       		}
       		else
       		{
        		TranslateMessage( &s_Message );
        		DispatchMessage( &s_Message );
       		}
  		}
  		else
  		{ 
           	pf_function(); 
    		SwapBuffers( h_DC );       		
  		}
 	}

 	return( s_Message.wParam );
}
 
inline HGLRC EE_SYSTEM_WINDOW_OPENGL_C::GetHRC( void )
{
 	return( mh_RC );
}

void EE_SYSTEM_WINDOW_OPENGL_C::Destroy( void )
{
 	if( ms_GraphicsOptions.b_Fullscreen )
 	{
 		ChangeDisplaySettings( NULL, 0x00000000 );
  		ShowCursor( true );
 	}
 	if( mh_RC )
 	{
  		wglMakeCurrent( EE_SYSTEM_WINDOW_C::GetHDC(), mh_RC );
  		wglDeleteContext( mh_RC );
 	}  
 	
 	PostQuitMessage( 0 );
 
 	return;
}

LRESULT CALLBACK EE_SYSTEM_WINDOW_OPENGL_C::EE_OpenGLWindowProcedure( HWND h_wnd, UINT ui_message, WPARAM t_wParam, LPARAM t_lParam )
{
 	switch( ui_message )
 	{
  		case WM_LBUTTONDOWN:
            ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetLeftButton( true );
            break;
        case WM_LBUTTONUP:
            ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetLeftButton( false );
            break;
        case WM_RBUTTONDOWN:
            ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetRightButton( true );
            break;
        case WM_RBUTTONUP:
            ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetRightButton( false );
            break;
        case WM_MBUTTONDOWN:
            ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetMiddleButton( true );
            break;
        case WM_MBUTTONUP:
            ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetMiddleButton( false );
            break;
        case WM_MOUSEMOVE:
            ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetPosition( LOWORD( t_lParam ), 
                                                                                       HIWORD( t_lParam ) );
            break;
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Keyboard.KeyDown( t_lParam );
            break;
        case WM_CHAR:
            ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Keyboard.CharacterPressed( LOBYTE( LOWORD( t_wParam ) ) );
            break;
        case WM_SYSKEYUP:
        case WM_KEYUP:
            ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Keyboard.KeyUp( t_lParam );
            break;  
  		case WM_DESTROY:
   		   ((EE_SYSTEM_WINDOW_OPENGL_C*)EE_EXZOKI_n::pv_CurrentWindow)->Destroy();
   		   break;
  		default:
   		   return( DefWindowProc( h_wnd, ui_message, t_wParam, t_lParam ) );
   		break; 
 	}
 	
	return( 0 );       
}      
