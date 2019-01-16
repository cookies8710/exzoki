#ifndef EE_TEMPLATE_FILE_MANAGER_H
#define EE_TEMPLATE_FILE_MANAGER_H

#include <map>
#include <string>
#include <exzoki/system/ee_system_types.h>

/*
tøída T musí poskytovat:
    Load( EE_CCSTRING_t );
*/


template <class T>
class EE_TEMPLATE_FILE_MANAGER_C
{
    public:
        EE_TEMPLATE_FILE_MANAGER_C( void );
        ~EE_TEMPLATE_FILE_MANAGER_C( void );
       
        virtual void Load( EE_CCSTRING_t ccs_path );
        void Delete( EE_CCSTRING_t ccs_path );
        
        void Clear( void );
        
        const T* Get( EE_CCSTRING_t ccs_path ) const;
        
    protected:
        typedef std::map< std::string, T > EE_TEMPLATE_FILE_MANAGER_STORAGE_t;
        typedef std::map< std::string, EE_U32_t > EE_TEMPLATE_FILE_MANAGER_COUNTER_t;
        
        EE_TEMPLATE_FILE_MANAGER_STORAGE_t mco_Storage;
        EE_TEMPLATE_FILE_MANAGER_COUNTER_t mco_Counter;
            
};

#endif
