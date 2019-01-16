#include <exzoki/system/ee_system_input_keyboard.h>

EE_SYSTEM_INPUT_KEYBOARD_C::EE_SYSTEM_INPUT_KEYBOARD_C( void )
{
    // Získám jména kláves
    GetKeyNames();
}

EE_SYSTEM_INPUT_KEYBOARD_C::EE_SYSTEM_INPUT_KEYBOARD_C( const EE_SYSTEM_INPUT_KEYBOARD_C& crC_keyb )
{
    // Kopíruju
    CopyProc( crC_keyb );
}

EE_SYSTEM_INPUT_KEYBOARD_C EE_SYSTEM_INPUT_KEYBOARD_C::operator=( const EE_SYSTEM_INPUT_KEYBOARD_C& crC_keyb )
{
    // Ujistím se že nekopíruju sebe sama
    if( &crC_keyb != this )
    {
        CopyProc( crC_keyb );    
    }    
    
    return( crC_keyb );
}

EE_SYSTEM_INPUT_KEYBOARD_C::~EE_SYSTEM_INPUT_KEYBOARD_C( void )
{
}
        
void EE_SYSTEM_INPUT_KEYBOARD_C::KeyDown( LPARAM t_lParam )
{
    // Získám z lParamu potøebné informace
    EE_BYTE_t b_ScanCode( ( t_lParam & 16711680 ) >> 16 );
    EE_BOOL_t b_ExtendedKey( ( t_lParam & 16777216 )?1:0 );
    EE_BOOL_t b_PressedBefore( ( t_lParam & 1073741824 )?1:0 );
        
    // Zjistím, jaká klávesa to je
    EE_U16_t u16_Key( b_ScanCode + 256 * b_ExtendedKey );
        
    // Nastavím stav klávesy
    mae_KeyStates[ u16_Key ] = ( b_PressedBefore ) ? 
                                    ( EE_SYSTEM_INPUT_KEYBOARD_KEY_STATE_PRESSED_BEFORE ) : 
                                    ( EE_SYSTEM_INPUT_KEYBOARD_KEY_STATE_PRESSED_FIRST_TIME );
                            
    // Nastavím naposledy stisknutou klávesu        
    mu16_LastKeyPressed = u16_Key;
}

void EE_SYSTEM_INPUT_KEYBOARD_C::KeyUp( LPARAM t_lParam )
{
    // Získám z lParamu potøebné informace
    EE_BYTE_t b_ScanCode( ( t_lParam & 16711680 ) >> 16 );
    EE_BOOL_t b_ExtendedKey( ( t_lParam & 16777216 )?1:0 );
    EE_BOOL_t b_PressedBefore( ( t_lParam & 1073741824 )?1:0 );
    
    // Zjistím, jaká klávesa to je
    EE_U16_t u16_Key( b_ScanCode + 256 * b_ExtendedKey );
    
    // Nastavím stav klávesy
    mae_KeyStates[ u16_Key ] = EE_SYSTEM_INPUT_KEYBOARD_KEY_STATE_NOT_PRESSED;
    
    // Pokud je poslednì stisknutá klávesa právì tato, nastavím tuto hodnotu na 0
    if( mu16_LastKeyPressed == u16_Key )
        mu16_LastKeyPressed = 0;    
}

void EE_SYSTEM_INPUT_KEYBOARD_C::CharacterPressed( EE_CHAR_t c_char )
{
    mc_LastCharacter = c_char;    
}

void EE_SYSTEM_INPUT_KEYBOARD_C::ClearLastKeyPressed( void )
{
    mu16_LastKeyPressed = 0;    
} 

void EE_SYSTEM_INPUT_KEYBOARD_C::ClearLastCharacterPressed( void )
{
    mc_LastCharacter = 0;    
}      
        
EE_SYSTEM_INPUT_KEYBOARD_KEY_STATE_e EE_SYSTEM_INPUT_KEYBOARD_C::GetKeyState( EE_U16_t u16_key ) const
{
    return( mae_KeyStates[ u16_key ] );
}

EE_U16_t EE_SYSTEM_INPUT_KEYBOARD_C::GetLastKeyPressed( void ) const
{
    return( mu16_LastKeyPressed );    
}

std::string EE_SYSTEM_INPUT_KEYBOARD_C::GetKeyName( EE_U16_t u16_key ) const
{
    return( maS_KeyNames[ u16_key ] );    
}

EE_CHAR_t EE_SYSTEM_INPUT_KEYBOARD_C::GetLastCharacterPressed( void ) const
{
    return( mc_LastCharacter );
}
        
void EE_SYSTEM_INPUT_KEYBOARD_C::CopyProc( const EE_SYSTEM_INPUT_KEYBOARD_C& crC_keyb )
{
    for( EE_U32_t u32_Key( 0 ); u32_Key < 512; u32_Key++ )
    {
        mae_KeyStates[ u32_Key ] = crC_keyb.mae_KeyStates[ u32_Key ];  
        maS_KeyNames[ u32_Key ] = crC_keyb.maS_KeyNames[ u32_Key ];  
    }
            
    mu16_LastKeyPressed = crC_keyb.mu16_LastKeyPressed;    
}

void EE_SYSTEM_INPUT_KEYBOARD_C::GetKeyNames( void )
{
    // Non-extended klávesy
    for( EE_U32_t u32_Key( 0 ); u32_Key < 256; u32_Key++ )
    {
        EE_CHAR_t ac_Buffer[ 256 ];
        EE_U32_t u32_LParam( u32_Key << 16 );
        GetKeyNameText( u32_LParam, ac_Buffer, 256 );
        maS_KeyNames[ u32_Key ] = ac_Buffer;
    }
    
    // Extended klávesy
    for( EE_U32_t u32_Key( 0 ); u32_Key < 256; u32_Key++ )
    {
        EE_CHAR_t ac_Buffer[ 256 ];
        EE_U32_t u32_LParam( ( u32_Key << 16 ) + ( 1 << 24 ) );
        GetKeyNameText( u32_LParam, ac_Buffer, 256 );
        maS_KeyNames[ u32_Key + 256 ] = ac_Buffer;  
    }
}
      
