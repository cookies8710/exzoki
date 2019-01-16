#include <exzoki/template/ee_template_file_manager.h>

template <class T>
EE_TEMPLATE_FILE_MANAGER_C<T>::EE_TEMPLATE_FILE_MANAGER_C( void )
{
}

template <class T>
EE_TEMPLATE_FILE_MANAGER_C<T>::~EE_TEMPLATE_FILE_MANAGER_C( void )
{
    Clear();    
}

template <class T>        
void EE_TEMPLATE_FILE_MANAGER_C<T>::Load( EE_CCSTRING_t ccs_path )
{
    if( ++mco_Counter[ std::string( ccs_path ) ] == 1 ) // ? mozna chyba
        mco_Storage[ std::string( ccs_path ) ].Load( ccs_path );    
}

template <class T>
void EE_TEMPLATE_FILE_MANAGER_C<T>::Delete( EE_CCSTRING_t ccs_path )
{
    // test na pritomnost !
    
    if( --mco_Counter[ std::string( ccs_path ) ] == 0 ) // ? mozna chyba
    {
        mco_Storage.erase( std::string( ccs_path ) );         
        mco_Counter.erase( std::string( ccs_path ) );       
    }
}

template <class T>
void EE_TEMPLATE_FILE_MANAGER_C<T>::Clear( void )
{
    mco_Storage.clear();
    mco_Counter.clear();    
}

template <class T>        
const T* EE_TEMPLATE_FILE_MANAGER_C<T>::Get( EE_CCSTRING_t ccs_path ) const
{
    // zpomalení kvùli zkurvenosti devc++
    if( mco_Storage.find( std::string( ccs_path ) ) != mco_Storage.end() )
        return( &( mco_Storage.find( std::string( ccs_path ) )->second ) );
    else
        return( 0 );    
}
   
