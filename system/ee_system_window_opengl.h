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

// Typ projek�n� matice
enum EE_SYSTEM_OPENGL_PROJECTION_TYPE_e
{
 	EE_SYSTEM_OPENGL_ORTHO,
 	EE_SYSTEM_OPENGL_PERSPECTIVE
};

// Nastaven� projek�n� matice
struct EE_SYSTEM_OPENGL_PROJECTION_DESCRIPTOR_s
{
 	EE_SYSTEM_OPENGL_PROJECTION_TYPE_e e_ProjectionType;

 	// Perspektivn�
 	EE_FLOAT_t f_Fovy;

 	// Ortogon�ln�
 	EE_FLOAT_t f_Left;
 	EE_FLOAT_t f_Right;
 	EE_FLOAT_t f_Bottom;
 	EE_FLOAT_t f_Top;

 	// Ob�
 	EE_FLOAT_t f_ZNearest;
 	EE_FLOAT_t f_ZFarest;
};

class EE_SYSTEM_WINDOW_OPENGL_C: public EE_SYSTEM_WINDOW_C
{
	public:
		EE_SYSTEM_WINDOW_OPENGL_C( void );
		virtual ~EE_SYSTEM_WINDOW_OPENGL_C( void );
		
		// Vytvo�en� okna
		virtual void Create( HINSTANCE h_instance,
               				 EE_CCSTRING_t ccs_wndClassName,
               				 EE_CCSTRING_t ccs_wndName,
               				 const EE_SYSTEM_GRAPHICS_OPTIONS_s& crs_graphicsOptions,
                             WNDPROC pf_WindowProcedure = EE_SYSTEM_WINDOW_OPENGL_C::EE_OpenGLWindowProcedure );
  		// Metoda na zm�nu velikosti okna 
  		virtual void ResizeProc( const EE_SYSTEM_OPENGL_PROJECTION_DESCRIPTOR_s& crs_projectionDescriptor );
  		// Metoda pro hlavn� smy�ku programu - jako parametr fce, kter� prob�h� a� do konce programu
  		virtual WPARAM Run( void(*pf_function)( void ) );
  		// Metoda na skon�en� programu
  		virtual void Destroy( void );
  
  		// P��stupov� metoda - na z�sk�n� handle na rendering context
  		inline HGLRC GetHRC( void );	
	
	private:	
		static LRESULT CALLBACK EE_OpenGLWindowProcedure( HWND h_wnd, UINT ui_message, WPARAM t_wParam, LPARAM t_lParam );       
         
  		HGLRC mh_RC;
};

#endif
