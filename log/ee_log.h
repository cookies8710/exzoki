#ifndef EE_LOG_H
#define EE_LOG_H

#include <fstream>
#include <stdio.h>
#include <exzoki/system/ee_system_types.h>

namespace EE_EXZOKI_n
{
    EE_CCSTRING_t ccs_LogFile = "exzoki.log";    
};

class EE_LOG_C
{
    public:
        static EE_LOG_C& Get( void );
                
        void Write( EE_CCSTRING_t ccs_string, ... );
        
    protected:
        EE_LOG_C( void );
        
        EE_BOOL_t Init( void );
        
        std::ofstream mC_Output;           
    
};

#endif
