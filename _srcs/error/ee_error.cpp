#include <exzoki/error/ee_error.h>

EE_ERROR_C::EE_ERROR_C( void ): mb_ErrorMessage( EE_FALSE )
{
    ThrowError( "Unspecified class", "Unspecified function", EE_ERROR_CODES_n::cS_Internal );
}


EE_ERROR_C::EE_ERROR_C( EE_CCSTRING_t ccs_className,
            			EE_CCSTRING_t ccs_functionName,
		      			const std::string& crS_error,
			   			EE_CCSTRING_t ccs_message, 
                        ... )
{
    va_list p_Argument;
 	EE_CHAR_t ac_OutputString[ 1024 ]; // 1024 ?
 
 	if( ccs_message )
 	{
        va_start( p_Argument, ccs_message );
     	vsprintf( ac_OutputString, ccs_message, p_Argument );
     	va_end( p_Argument ); 
    }
    
	ThrowError( ccs_className, ccs_functionName, crS_error, ac_OutputString );	
}

void EE_ERROR_C::ThrowError( EE_CCSTRING_t ccs_className,
		            		 EE_CCSTRING_t ccs_functionName,
						  	 const std::string& crS_error,
							 EE_CCSTRING_t ccs_message )
{
	// Uložím do datových struktur
	mS_ClassName = ccs_className;
	mS_FunctionName = ccs_functionName;
	mS_Error = crS_error;
	if( ccs_message )	
	{
		mb_ErrorMessage = EE_TRUE;
		mS_ErrorMessage = ccs_message;
	}
	
	// Zapíšu do logu
	EE_LOG_C &rC_Log( EE_LOG_C::Get() );
    rC_Log.Write( "============================================\nERROR:\n"  
                  "Class name: %s\nFunction name: %s\nError: %s\n", 
                  mS_ClassName.c_str(), mS_FunctionName.c_str(), mS_Error.c_str() );
    if( mb_ErrorMessage )
        rC_Log.Write( "Error message: %s\n", mS_ErrorMessage.c_str() );       
    rC_Log.Write( "============================================\n" );   
	
	// A vyhodím tuto instanci
	throw( *this );
}
		

EE_CCSTRING_t EE_ERROR_C::GetClass( void ) const
{
	return( mS_ClassName.c_str() );	
}

EE_CCSTRING_t EE_ERROR_C::GetFunction( void ) const
{
	return( mS_FunctionName.c_str() );	
}

EE_CCSTRING_t EE_ERROR_C::GetError( void ) const
{
	return( mS_Error.c_str() );	
}

EE_CCSTRING_t EE_ERROR_C::GetErrorMessage( void ) const
{
	return( mS_ErrorMessage.c_str() );	
}

EE_BOOL_t EE_ERROR_C::HasMessage( void ) const
{
	return( mb_ErrorMessage );	
}
