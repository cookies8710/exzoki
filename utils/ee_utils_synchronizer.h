#ifndef EE_UTILS_SYNCHRONIZER_H
#define EE_UTILS_SYNCHRONIZER_H

#include <windows.h>
#include <exzoki/system/ee_system_types.h>

namespace EE_EXZOKI_n
{
    const EE_U32_t cu16_FPSActualization = 500; 
    
};

class EE_UTILS_SYNCHRONIZER_C
{
    public:
        EE_UTILS_SYNCHRONIZER_C( void );
        
        void SynchronizerProc( void );
        
        inline EE_FLOAT_t GetSynchro( void ) const;
        inline EE_FLOAT_t GetFPS( void ) const;
        
    private:
        EE_U32_t mu32_MilisecondsOld, 
                 mu32_MilisecondsActual, 
                 mu32_Difference, 
                 mu32_FPSDifference; 
        EE_FLOAT_t mf_Synchro,
                   mf_FPS;
        EE_BOOL_t mb_FirstRun;
        
            
};

#endif
