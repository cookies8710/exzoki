#include <exzoki/utils/ee_utils_synchronizer.h>

EE_UTILS_SYNCHRONIZER_C::EE_UTILS_SYNCHRONIZER_C( void ): mb_FirstRun( EE_TRUE )
{
}
        
void EE_UTILS_SYNCHRONIZER_C::SynchronizerProc( void )
{
    if( mb_FirstRun )
    {
        mb_FirstRun = EE_FALSE; 
        mu32_MilisecondsOld = GetTickCount();
        return;   
    }
    
    mu32_MilisecondsActual = GetTickCount();
    mu32_Difference = mu32_MilisecondsActual - mu32_MilisecondsOld;
    mu32_MilisecondsOld = mu32_MilisecondsActual;
    
    mu32_FPSDifference += mu32_Difference;
    if( mu32_FPSDifference > EE_EXZOKI_n::cu16_FPSActualization )
    {
        mu32_FPSDifference = 0;
        mf_FPS = 1000.0 / mu32_Difference;    
    }
    
    mf_Synchro = 0.001 * mu32_Difference;
}
        
inline EE_FLOAT_t EE_UTILS_SYNCHRONIZER_C::GetSynchro( void ) const
{
    return( mf_Synchro );    
}

inline EE_FLOAT_t EE_UTILS_SYNCHRONIZER_C::GetFPS( void ) const
{
    return( mf_FPS );    
}
