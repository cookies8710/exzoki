#ifndef EE_SYSTEM_WINDOW_OPENGL_H
#define EE_SYSTEM_WINDOW_OPENGL_H

#include <windows.h>
#include <exzoki/error/ee_error.h>
#include <exzoki/system/ee_system_types.h>
#include <exzoki/system/ee_system_input_keyboard.h>
#include <exzoki/system/ee_system_input_mouse.h>
#include <exzoki/system/ee_system_window.h>
#include <gl/gl.h>
#include <gl/glu.h>

// Typ projekèní matice
enum EE_SYSTEM_OPENGL_PROJECTION_TYPE_e
{
 	EE_SYSTEM_OPENGL_ORTHO,
 	EE_SYSTEM_OPENGL_PERSPECTIVE
};

// Nastavení projekèní matice
struct EE_SYSTEM_OPENGL_PROJECTION_DESCRIPTOR_s
{
 	EE_SYSTEM_OPENGL_PROJECTION_TYPE_e e_ProjectionType;

 	// Perspektivní
 	EE_FLOAT_t f_Fovy;

 	// Ortogonální
 	EE_FLOAT_t f_Left;
 	EE_FLOAT_t f_Right;
 	EE_FLOAT_t f_Bottom;
 	EE_FLOAT_t f_Top;

 	// Obì
 	EE_FLOAT_t f_ZNearest;
 	EE_FLOAT_t f_ZFarest;
};

class EE_SYSTEM_WINDOW_OPENGL_C: public EE_SYSTEM_WINDOW_C
{
	public:
		EE_SYSTEM_WINDOW_OPENGL_C( void );
		virtual ~EE_SYSTEM_WINDOW_OPENGL_C( void );
		
		// Vytvoøení okna
		virtual void Create( HINSTANCE h_instance,
               				 EE_CCSTRING_t ccs_wndClassName,
               				 EE_CCSTRING_t ccs_wndName,
               				 const EE_SYSTEM_GRAPHICS_OPTIONS_s& crs_graphicsOptions,
                             WNDPROC pf_WindowProcedure = EE_SYSTEM_WINDOW_OPENGL_C::EE_OpenGLWindowProcedure );
  		// Metoda na zmìnu velikosti okna 
  		virtual void ResizeProc( const EE_SYSTEM_OPENGL_PROJECTION_DESCRIPTOR_s& crs_projectionDescriptor );
  		// Metoda pro hlavní smyèku programu - jako parametr fce, která probíhá až do konce programu
  		virtual WPARAM Run( void(*pf_function)( void ) );
  		// Metoda na skonèení programu
  		virtual void Destroy( void );
  
  		// Pøístupová metoda - na získání handle na rendering context
  		inline HGLRC GetHRC( void );	
	
	private:	
		static LRESULT CALLBACK EE_OpenGLWindowProcedure( HWND h_wnd, UINT ui_message, WPARAM t_wParam, LPARAM t_lParam );       
         
  		HGLRC mh_RC;
};

#endif
