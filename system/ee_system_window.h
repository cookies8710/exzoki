/*
  Name: Exzoki engine
  Copyright: Tomas Surovec
  Author: Tomas Surovec
  Date: 18.11.05 15:37
  Description: ts_system_window.h
*/


#ifndef EE_SYSTEM_WINDOW_H
#define EE_SYSTEM_WINDOW_H

#include <windows.h>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_input_keyboard.h>
#include <exzoki/system/ee_system_input_mouse.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/log/ee_log.h>

// Grafické nastavení
struct EE_SYSTEM_GRAPHICS_OPTIONS_s
{
 	EE_U32_t u32_WindowWidth;
 	EE_U32_t u32_WindowHeight;
 	EE_U32_t u32_ColorDepth;
 	EE_BOOL_t b_Fullscreen;
};

namespace EE_EXZOKI_n
{
    // Ukazatel na aktivní okno
    EE_PVOID_t pv_CurrentWindow( NULL );
};

// Okno
class EE_SYSTEM_WINDOW_C
{
	public:
		EE_SYSTEM_WINDOW_C( void );  
  		virtual ~EE_SYSTEM_WINDOW_C();
  
  		// Metoda na vytvoøení okna
 		virtual void Create( HINSTANCE h_instance,
             	          	 EE_CCSTRING_t ccs_wndClassName,
                      		 EE_CCSTRING_t ccs_wndName,
                      		 const EE_SYSTEM_GRAPHICS_OPTIONS_s& crs_graphicsOptions,
                             WNDPROC pf_WindowProcedure = EE_SYSTEM_WINDOW_C::EE_WindowProcedure );
  		// Metoda na zmìnu velikosti okna 
  		virtual void ResizeProc( void );
  		// Metoda na skonèení programu
  		virtual void Destroy( void );
  		// Metoda pro hlavní smyèku programu - jako parametr fce, která probíhá až do konce programu
  		virtual WPARAM Run( void(*pf_function)( void ) );  
    
  		// Pøístupová metoda - na získání handle na okno  
  		inline HWND GetHWnd( void );
  		// Pøístupová metoda - na získání handle na device context
  		inline HDC GetHDC( void );
  
  		inline EE_SYSTEM_INPUT_KEYBOARD_C* GetKeyboard( void );
  		inline const EE_SYSTEM_INPUT_MOUSE_C* GetMouse( void ) const;
   
	protected:
		EE_SYSTEM_GRAPHICS_OPTIONS_s ms_GraphicsOptions; 
  		EE_SYSTEM_INPUT_MOUSE_C mC_Mouse;
  		EE_SYSTEM_INPUT_KEYBOARD_C mC_Keyboard; 
        EE_LOG_C *mpC_LogFile; 
         
 	private:
  		static LRESULT CALLBACK EE_WindowProcedure( HWND h_wnd, UINT ui_message, WPARAM t_wParam, LPARAM t_lParam );
     	HWND mh_Wnd;     	
};

#endif
