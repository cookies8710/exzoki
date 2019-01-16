#ifndef EE_SYSTEM_FILE_H
#define EE_SYSTEM_FILE_H

#include <fstream>
#include <string>
#include <exzoki/error/ee_error.h>
#include <exzoki/system/ee_system_types.h>

enum EE_SYSTEM_FILE_MODE_e
{
	EE_SYSTEM_FILE_WRITE = 1,
	EE_SYSTEM_FILE_READ = 2,	
	EE_SYSTEM_FILE_APPEND = 3
};

enum EE_SYSTEM_FILE_TYPE_e
{
	EE_SYSTEM_FILE_TEXT = 4,
	EE_SYSTEM_FILE_BINARY = 5
};

enum EE_SYSTEM_FILE_DIRECTION_e
{
	EE_SYSTEM_FILE_DIRECTION_BEGIN = 6,
	EE_SYSTEM_FILE_DIRECTION_CURRENT = 7,
	EE_SYSTEM_FILE_DIRECTION_END = 8
};

class EE_SYSTEM_FILE_C
{
	public:
		EE_SYSTEM_FILE_C( void );
		EE_SYSTEM_FILE_C( EE_CCSTRING_t ccs_filename, EE_SYSTEM_FILE_MODE_e e_openMode, EE_SYSTEM_FILE_TYPE_e e_openType );
		
		// Otev�e soubor
		void Open( EE_CCSTRING_t ccs_filename, EE_SYSTEM_FILE_MODE_e e_openMode, EE_SYSTEM_FILE_TYPE_e e_openType );
		// Zav�e soubor
		void Close( void );
		
		// Na�te data ze souboru
		void Read( EE_PVOID_t pv_destination, EE_U32_t u32_size );
		// Zap�e data do souboru
		void Write( const EE_PVOID_t cpv_source, EE_U32_t u32_size );	
		
		// Nastav� ukazatel na ur�it� m�sto v souboru
		void Seek( EE_S32_t s32_offset, EE_SYSTEM_FILE_DIRECTION_e e_direction );
		
		// Na�te jeden znak
		EE_CHAR_t GetChar( void );
		
		// Vr�t� pravdu, pokud je soubor otev�en
		EE_BOOL_t IsOpened( void ) const;
		// Vr�t� jm�no souboru
		EE_CCSTRING_t GetFilename( void ) const;
		
		// Vr�t� velikost souboru
		EE_U32_t GetSize( void ) const;
		
	private:
		std::fstream mC_File;
		EE_BOOL_t mb_FileOpened;
		EE_SYSTEM_FILE_MODE_e me_OpenMode;
		std::string mS_Filename;
		EE_U32_t mu32_FileSize;		
};


#endif
