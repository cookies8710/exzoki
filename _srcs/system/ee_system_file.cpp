#include <exzoki/system/ee_system_file.h>

EE_SYSTEM_FILE_C::EE_SYSTEM_FILE_C( void ): mb_FileOpened( EE_FALSE )
{
}

EE_SYSTEM_FILE_C::EE_SYSTEM_FILE_C( EE_CCSTRING_t ccs_filename, EE_SYSTEM_FILE_MODE_e e_openMode, EE_SYSTEM_FILE_TYPE_e e_openType ): mb_FileOpened( EE_FALSE )
{
	Open( ccs_filename, e_openMode, e_openType );	
}
		
void EE_SYSTEM_FILE_C::Open( EE_CCSTRING_t ccs_filename, EE_SYSTEM_FILE_MODE_e e_openMode, EE_SYSTEM_FILE_TYPE_e e_openType )
{
	// Pokud je n�jak� soubor otev�en, uzav�u jej
	if( mb_FileOpened )		
		Close();
	
	// Nastav�m vlajky podle m�du otev�en�
	std::ios_base::openmode t_OpenFlags;
	switch( me_OpenMode = e_openMode )
	{
	 	case EE_SYSTEM_FILE_WRITE:
			t_OpenFlags = std::ios::out;
			break;
		case EE_SYSTEM_FILE_READ:
			t_OpenFlags = std::ios::in;
			break;
		case EE_SYSTEM_FILE_APPEND:
			t_OpenFlags = std::ios::app | std::ios::out;
			break;
	 	default:
			EE_ERROR_C( "EE_SYSTEM_FILE_C", "Open", EE_ERROR_CODES_n::cS_Internal, ccs_filename );
			break;
	}
	// P�id�m vlajky podle typu otev�en�
	switch( e_openType )
	{
		case EE_SYSTEM_FILE_TEXT:
			break;
		case EE_SYSTEM_FILE_BINARY:
			t_OpenFlags |= std::ios::binary;
			break;
		default:
			EE_ERROR_C( "EE_SYSTEM_FILE_C", "Open", EE_ERROR_CODES_n::cS_Internal, ccs_filename );
			break;			
	}
	
	// Otev�u soubor
	mC_File.open( ccs_filename, t_OpenFlags );
	// Otestuju, zda v�e prob�hlo v po��dku
	if( !mC_File.good() )
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "Open", EE_ERROR_CODES_n::cS_ErrorWhileOpeningFile, ccs_filename );
	// Nastav�m vlajku otev�en� souboru na pravdu
	mb_FileOpened = EE_TRUE;
	// Ulo��m si jm�no souboru
	mS_Filename = ccs_filename;
	
	// Z�sk�m velikost souboru
	switch( e_openMode )
	{
	 	case EE_SYSTEM_FILE_WRITE:
			mu32_FileSize = 0;
			break;
		case EE_SYSTEM_FILE_READ:
			mC_File.seekg( 0, std::ios_base::end );
			mu32_FileSize = mC_File.tellg();
			mC_File.seekg( 0, std::ios_base::beg );
			break;
		case EE_SYSTEM_FILE_APPEND:
			mC_File.seekp( 0, std::ios_base::end );
			mu32_FileSize = mC_File.tellp();
			mC_File.seekp( 0, std::ios_base::beg );
			break;
	 	default:
			EE_ERROR_C( "EE_SYSTEM_FILE_C", "Open", EE_ERROR_CODES_n::cS_Internal, ccs_filename );
			break;
	}
	
	return;
}

void EE_SYSTEM_FILE_C::Close( void )
{
	// Pokud je n�jak� soubor otev�en, uzav�u ho a nastav�m vlajku otev�en� souboru na nepravdu
	if( mb_FileOpened )
	{
		mC_File.close();
		mb_FileOpened = EE_FALSE;
		mu32_FileSize = 0;
		mS_Filename = "";
	}		
	
	return;
}
		
void EE_SYSTEM_FILE_C::Read( EE_PVOID_t pv_destination, EE_U32_t u32_size )
{
	// Otestuju, zda je soubor otev�en
	if( !mb_FileOpened )
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "Read", EE_ERROR_CODES_n::cS_NoFileOpened );
	
	// Otestuju, zda byl soubor otev�en pro �ten�
	if( me_OpenMode != EE_SYSTEM_FILE_READ )	
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "Read", EE_ERROR_CODES_n::cS_FileWasntOpenedForReading, mS_Filename.c_str() );
	
	if( !mC_File.good() )
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "Read", EE_ERROR_CODES_n::cS_Internal, mS_Filename.c_str() );
	
	// Na�tu data ze souboru
	mC_File.read( (char*)pv_destination, u32_size );
	
	// Otestuju soubor pro p��padn� chyby
	if( !mC_File.good() )
	{
		if( mC_File.eof() )
			EE_ERROR_C( "EE_SYSTEM_FILE_C", "Read", EE_ERROR_CODES_n::cS_EOFReached, mS_Filename.c_str() );	
		else
			EE_ERROR_C( "EE_SYSTEM_FILE_C", "Read", EE_ERROR_CODES_n::cS_ErrorWhileReading, mS_Filename.c_str() );
	}
	
	return;
}

void EE_SYSTEM_FILE_C::Write( const EE_PVOID_t cpv_source, EE_U32_t u32_size )
{
	// Otestuju, zda je soubor otev�en
	if( !mb_FileOpened )
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "Write", EE_ERROR_CODES_n::cS_NoFileOpened );
	
	// Otestuju, zda byl soubor otev�en pro z�pis
	if( me_OpenMode != EE_SYSTEM_FILE_WRITE && me_OpenMode != EE_SYSTEM_FILE_APPEND )	
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "Write", EE_ERROR_CODES_n::cS_FileWasntOpenedForWriting, mS_Filename.c_str() );	

	if( !mC_File.good() )
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "Write", EE_ERROR_CODES_n::cS_Internal, mS_Filename.c_str() );
		
	// Zap�u data do souboru
	mC_File.write( (const char*)cpv_source, u32_size );
	
	// P�id�m po�et zapsan�ch byt� k celkov� velikosti souboru
	mu32_FileSize += u32_size;
	
	// Otestuju soubor pro p��padn� chyby
	if( !mC_File.good() )
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "Write", EE_ERROR_CODES_n::cS_ErrorWhileWriting, mS_Filename.c_str() );
		
	return;
}	

void EE_SYSTEM_FILE_C::Seek( EE_S32_t s32_offset, EE_SYSTEM_FILE_DIRECTION_e e_direction )
{
	// Otestuju, zda je soubor otev�en
	if( !mb_FileOpened )
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "Seek", EE_ERROR_CODES_n::cS_NoFileOpened );
	
	// Nastav�m vlajky
	std::ios_base::seekdir t_SeekDirection;
	switch( e_direction )
	{
		case EE_SYSTEM_FILE_DIRECTION_BEGIN:
			t_SeekDirection = std::ios_base::beg;
			break;		
		case EE_SYSTEM_FILE_DIRECTION_CURRENT:
			t_SeekDirection = std::ios_base::cur;
			break;
		case EE_SYSTEM_FILE_DIRECTION_END:
			t_SeekDirection = std::ios_base::end;
			break;
		default:
			EE_ERROR_C( "EE_SYSTEM_FILE_C", "Seek", EE_ERROR_CODES_n::cS_Internal );	
	}	
	
	// P�esunu ukazatel uvnit� souboru
	switch( me_OpenMode )
	{
		case EE_SYSTEM_FILE_WRITE:
		case EE_SYSTEM_FILE_APPEND:
			mC_File.seekp( s32_offset, t_SeekDirection );
			break;
		case EE_SYSTEM_FILE_READ:
			mC_File.seekg( s32_offset, t_SeekDirection );
			break;
		default:
			EE_ERROR_C( "EE_SYSTEM_FILE_C", "Seek", EE_ERROR_CODES_n::cS_Internal );	
	}	
	
	// Otestuju, zda je v�e v po��dku
	if( !mC_File.good() )
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "Seek", EE_ERROR_CODES_n::cS_ErrorWhileSeeking, mS_Filename.c_str() );	
	
	return;	
}

EE_CHAR_t EE_SYSTEM_FILE_C::GetChar( void )
{
	if( mb_FileOpened )
	{
		if( me_OpenMode == EE_SYSTEM_FILE_READ )	
			return( (EE_CHAR_t)mC_File.get() );
		else
			EE_ERROR_C( "EE_SYSTEM_FILE_C", "GetChar", EE_ERROR_CODES_n::cS_FileWasntOpenedForReading, mS_Filename.c_str() );	
	}
	else
		EE_ERROR_C( "EE_SYSTEM_FILE_C", "GetChar", EE_ERROR_CODES_n::cS_NoFileOpened );	
}

EE_BOOL_t EE_SYSTEM_FILE_C::IsOpened( void ) const
{
	return( mb_FileOpened );	
}

EE_CCSTRING_t EE_SYSTEM_FILE_C::GetFilename( void ) const
{
	if( mb_FileOpened )
		return( mS_Filename.c_str() );
	else
		return( EE_NULL );	
}

EE_U32_t EE_SYSTEM_FILE_C::GetSize( void ) const
{
	if( mb_FileOpened )
		return( mu32_FileSize );	
	else
		return( 0 );
}
