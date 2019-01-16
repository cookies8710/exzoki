#include <exzoki/system/ee_system_window.h>

EE_SYSTEM_WINDOW_C::EE_SYSTEM_WINDOW_C( void ): mh_Wnd( NULL )
{
    mpC_LogFile = &EE_LOG_C::Get();
}

EE_SYSTEM_WINDOW_C::~EE_SYSTEM_WINDOW_C()
{
	Destroy();        
} 
 
void EE_SYSTEM_WINDOW_C::Create( HINSTANCE h_instance,
                                 EE_CCSTRING_t ccs_wndClassName,
                                 EE_CCSTRING_t ccs_wndName,
                                 const EE_SYSTEM_GRAPHICS_OPTIONS_s& crs_graphicsOptions,
                                 WNDPROC pf_WindowProcedure )
{
	WNDCLASSEX s_WinClEx;
 	DWORD t_WindowStyle, t_WindowExStyle;
 	EE_S32_t s32_XOrigin, s32_YOrigin;
 
 	// Uložím si požadované grafické nastavení
	ms_GraphicsOptions = crs_graphicsOptions;      
    
    mpC_LogFile->Write( "Graphics options: %d x %d @ %d bits, fullscreen=%d\n", 
                        ms_GraphicsOptions.u32_WindowWidth,
                        ms_GraphicsOptions.u32_WindowHeight,
                        ms_GraphicsOptions.u32_ColorDepth,
                        ms_GraphicsOptions.b_Fullscreen );
    
	// Nastavím styly a pozici okna i s ohledem na to, zda je fullscreenové  
 	t_WindowStyle = WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
 	t_WindowExStyle = WS_EX_APPWINDOW;
 	if( crs_graphicsOptions.b_Fullscreen )
 	{
 		t_WindowStyle |= WS_POPUP;
  		s32_XOrigin = 0;
  		s32_YOrigin = 0;
 	}
 	else
 	{
  		t_WindowStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
  		t_WindowExStyle |= WS_EX_WINDOWEDGE;
  		s32_XOrigin = CW_USEDEFAULT;
  		s32_YOrigin = CW_USEDEFAULT;
 	}
	
	// Nastavím tøídu okna
 	s_WinClEx.cbSize = sizeof( WNDCLASSEX );
 	s_WinClEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
 	s_WinClEx.lpfnWndProc = pf_WindowProcedure;
 	s_WinClEx.cbClsExtra = 0;
 	s_WinClEx.cbWndExtra = 0;
 	s_WinClEx.hInstance = h_instance;
 	s_WinClEx.hIcon = LoadIcon( h_instance, MAKEINTRESOURCE( 500 ) );
 	s_WinClEx.hIconSm = ( crs_graphicsOptions.b_Fullscreen ) ? NULL : LoadIcon( h_instance, MAKEINTRESOURCE( 500 ) );
 	s_WinClEx.hCursor = LoadCursor( h_instance, MAKEINTRESOURCE(666) );
 	s_WinClEx.hbrBackground = NULL;
 	s_WinClEx.lpszMenuName = NULL;
 	s_WinClEx.lpszClassName = ccs_wndClassName;
    
    // Zaregistruju tøídu okna
    mpC_LogFile->Write( "Registering window class..." );
	if( !RegisterClassEx( &s_WinClEx ) )
  		EE_ERROR_C( "EE_SYSTEM_OPENGL_WINDOW_C", "Create", EE_ERROR_CODES_n::cS_CannotRegisterWindowClass );
    mpC_LogFile->Write( "OK\n" );
     
    // Vytvoøím okno 
    mpC_LogFile->Write( "Creating window..." );
 	mh_Wnd = CreateWindowEx( t_WindowExStyle,
          	                 ccs_wndClassName,
                 	         ccs_wndName,
                   	         t_WindowStyle,
                     	     s32_XOrigin, s32_YOrigin,
                        	 crs_graphicsOptions.u32_WindowWidth, 
                             crs_graphicsOptions.u32_WindowHeight,
                          	 NULL,
               	             NULL,
                	         h_instance,
                 	         NULL );                    
 	if( !mh_Wnd )
  		EE_ERROR_C( "EE_SYSTEM_OPENGL_WINDOW_C", "Create", EE_ERROR_CODES_n::cS_CannotCreateWindow );
    mpC_LogFile->Write( "OK\n" );
    
    mpC_LogFile->Write( "Window info: handle=%d, title=%s\n", (EE_U32_t)mh_Wnd, ccs_wndName );
    
    EE_EXZOKI_n::pv_CurrentWindow = (EE_PVOID_t)this;
    
	return;
}
  
void EE_SYSTEM_WINDOW_C::ResizeProc( void )
{
}
  
void EE_SYSTEM_WINDOW_C::Destroy( void )
{
    PostQuitMessage( 0 );       
}
  
WPARAM EE_SYSTEM_WINDOW_C::Run( void(*pf_function)( void ) )
{
 	MSG s_Message;
	bool b_Exit = false;
 
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
		}
	}
 
 	return( s_Message.wParam );      
}

HWND EE_SYSTEM_WINDOW_C::GetHWnd( void )
{
	return( mh_Wnd );       
}

HDC EE_SYSTEM_WINDOW_C::GetHDC( void )
{
	return( GetDC( mh_Wnd ) );       
}

inline EE_SYSTEM_INPUT_KEYBOARD_C* EE_SYSTEM_WINDOW_C::GetKeyboard( void )
{
	return( &mC_Keyboard );       
}

inline const EE_SYSTEM_INPUT_MOUSE_C* EE_SYSTEM_WINDOW_C::GetMouse( void ) const
{
	return( &mC_Mouse );       
}

LRESULT CALLBACK EE_SYSTEM_WINDOW_C::EE_WindowProcedure( HWND h_wnd, UINT ui_message, WPARAM t_wParam, LPARAM t_lParam )
{
 	switch( ui_message )
 	{
  		case WM_LBUTTONDOWN:
            ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetLeftButton( true );
            break;
        case WM_LBUTTONUP:
            ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetLeftButton( false );
            break;
        case WM_RBUTTONDOWN:
            ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetRightButton( true );
            break;
        case WM_RBUTTONUP:
            ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetRightButton( false );
            break;
        case WM_MBUTTONDOWN:
            ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetMiddleButton( true );
            break;
        case WM_MBUTTONUP:
            ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetMiddleButton( false );
            break;
        case WM_MOUSEMOVE:
            ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Mouse.SetPosition( LOWORD( t_lParam ), 
                                                                                HIWORD( t_lParam ) );
            break;
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Keyboard.KeyDown( t_lParam );
            break;
        case WM_CHAR:
            ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Keyboard.CharacterPressed( LOBYTE( LOWORD( t_wParam ) ) );
            break;
        case WM_SYSKEYUP:
        case WM_KEYUP:
            ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->mC_Keyboard.KeyUp( t_lParam );
            break;
  		case WM_DESTROY:
   		   ((EE_SYSTEM_WINDOW_C*)EE_EXZOKI_n::pv_CurrentWindow)->Destroy();
   		   break;
  		default:
   		   return( DefWindowProc( h_wnd, ui_message, t_wParam, t_lParam ) );
   		break; 
	}
 	
	return( 0 );       
}

