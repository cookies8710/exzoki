#include <exzoki/log/ee_log.h>

EE_LOG_C::EE_LOG_C( void )
{
    Init();
}
    
EE_LOG_C& EE_LOG_C::Get( void )
{
    static EE_LOG_C C_Log;
    return( C_Log );
}
        
EE_BOOL_t EE_LOG_C::Init( void )
{
   mC_Output.open( EE_EXZOKI_n::ccs_LogFile ); 
   
   return( mC_Output.good() );
}
        
void EE_LOG_C::Write( EE_CCSTRING_t ccs_string, ... )
{
    va_list t_Args;
    va_start( t_Args, ccs_string ); 
    EE_CHAR_t ac_Buffer[ 1024 ];
    vsprintf( ac_Buffer, ccs_string, t_Args );   

    mC_Output << ac_Buffer << std::endl;
}   

