/*
  Name: Exzoki engine 
  Copyright: Tomas Surovec
  Author: Tomas Surovec
  Date: 18.11.05 15:24
  Description: ee_system_input_keyboard.h
*/

#ifndef EE_SYSTEM_INPUT_KEYBOARD_H
#define EE_SYSTEM_INPUT_KEYBOARD_H

#include <windows.h>
#include <string>
#include <exzoki/system/ee_system_types.h>

/*
speciální hodnoty - konstanty pro
esc, enter, mezerník, backspace, 

*/

enum EE_SYSTEM_INPUT_KEYBOARD_KEY_STATE_e
{
    EE_SYSTEM_INPUT_KEYBOARD_KEY_STATE_NOT_PRESSED = 0,
    EE_SYSTEM_INPUT_KEYBOARD_KEY_STATE_PRESSED_FIRST_TIME = 1,
    EE_SYSTEM_INPUT_KEYBOARD_KEY_STATE_PRESSED_BEFORE = 2   
};

namespace EE_EXZOKI_n
{
    const EE_CHAR_t cc_KeyEnter( 13 ),
                    cc_KeyEscape( 27 ),
                    cc_KeyBackspace( 8 ),
                    cc_KeySpace( 32 ); 
    
    const EE_U16_t cu16_LeftArrow( 331 ), 
                   cu16_RightArrow( 333 ),
                   cu16_UpArrow( 328 ),
                   cu16_DownArrow( 336 ),
                   cu16_DeleteKey( 339 );    
};

class EE_SYSTEM_INPUT_KEYBOARD_C
{
    public:
        EE_SYSTEM_INPUT_KEYBOARD_C( void );
        EE_SYSTEM_INPUT_KEYBOARD_C( const EE_SYSTEM_INPUT_KEYBOARD_C& crC_keyb );
        EE_SYSTEM_INPUT_KEYBOARD_C operator=( const EE_SYSTEM_INPUT_KEYBOARD_C& crC_keyb );
        ~EE_SYSTEM_INPUT_KEYBOARD_C( void );
               
        void KeyDown( LPARAM t_lParam );
        void KeyUp( LPARAM t_lParam );
        void CharacterPressed( EE_CHAR_t c_char );
        
        void ClearLastKeyPressed( void );
        void ClearLastCharacterPressed( void );
        
        EE_SYSTEM_INPUT_KEYBOARD_KEY_STATE_e GetKeyState( EE_U16_t u16_key ) const;
        EE_U16_t GetLastKeyPressed( void ) const;
        std::string GetKeyName( EE_U16_t u16_key ) const;
        EE_CHAR_t GetLastCharacterPressed( void ) const;
                
    private:
        void CopyProc( const EE_SYSTEM_INPUT_KEYBOARD_C& crC_keyb );
        
        void GetKeyNames( void );
               
        EE_SYSTEM_INPUT_KEYBOARD_KEY_STATE_e mae_KeyStates[ 512 ];  
        std::string maS_KeyNames[ 512 ];
        
        EE_U16_t mu16_LastKeyPressed;
        EE_CHAR_t mc_LastCharacter;
};

#endif
