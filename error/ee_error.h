#ifndef EE_ERRORC_H
#define EE_ERRORC_H

#include <string>
#include <exzoki/log/ee_log.h>
#include <exzoki/error/ee_error_codes.h>
#include <exzoki/system/ee_system_types.h>

class EE_ERROR_C
{
	public:
		// Implicitní konstruktor
		EE_ERROR_C( void );
		// Konstruktor, který zrovna vyhodí chybu
		EE_ERROR_C( EE_CCSTRING_t ccs_className,
		            EE_CCSTRING_t ccs_functionName,
				    const std::string& crS_error,
					EE_CCSTRING_t ccs_message = EE_NULL, 
                    ... );	
		
		// Get funkce
		EE_CCSTRING_t GetClass( void ) const;
		EE_CCSTRING_t GetFunction( void ) const;
		EE_CCSTRING_t GetError( void ) const;
		EE_CCSTRING_t GetErrorMessage( void ) const;
		EE_BOOL_t HasMessage( void ) const;
				 
	private:      
        // Pomocí throw vyhodí chybu
		void ThrowError( EE_CCSTRING_t ccs_className,
		                 EE_CCSTRING_t ccs_functionName,
		  			     const std::string& crS_error,
						 EE_CCSTRING_t ccs_message = EE_NULL );
          	
		std::string  mS_ClassName,
		             mS_FunctionName,
					 mS_Error,
					 mS_ErrorMessage;
		EE_BOOL_t mb_ErrorMessage;
};

#endif
