#ifndef ES_ERROR_CODES_H
#define EE_ERROR_CODES_H

#include <string>

namespace EE_ERROR_CODES_n
{
	const std::string // Obecné chyby
							cS_Internal( "Internal error" ),
							cS_BadIndex( "Bad index" ),
							cS_TooLongString( "Too long string" ),
							cS_BadVersion( "Bad version" ),
							cS_WrongNumber( "Wrong number" ),
							cS_BadOptions( "Bad settings" ),
							cS_DivisionByZero( "Division by zero" ),
							// Chyby pøi práci se soubory
							cS_FileIsDamaged( "File is damaged" ),
							cS_FileNotFound( "File not found" ),
							cS_WrongFileHeader( "Wrong file header" ),
							cS_UnknownFileFormat( "Unknown file format" ),
							cS_BadFileName( "Bad file name" ),
	                        cS_ErrorWhileOpeningFile( "An error occured while opening file" ),
							cS_FileWasntOpenedForReading( "File was not opened for reading" ),
							cS_FileWasntOpenedForWriting( "File was not opened for writing" ),
							cS_ErrorWhileReading( "An error occured while reading" ),
							cS_ErrorWhileWriting( "An error occured while writing" ),
							cS_NoFileOpened( "No file was opened" ),
							cS_EOFReached( "End of file reached" ),
							cS_ErrorWhileSeeking( "An error occured while moving inside file" ),
							// Chyby pøi práci s okny
							cS_CannotRegisterWindowClass( "Can not register window class" ),
							cS_CannotCreateWindow( "Can not create window" ),
							cS_CannotChoosePixelFormat( "Can not choose pixel format" ),
							cS_CannotSetPixelFormat( "Can not set pixel format" ),
							cS_CannotCreateRenderingContext( "Can not create rendering context" ),
							cS_CannotMakeCurrent( "Can not make current" ),
							cS_CannotSetFullscreen( "Can not set up fullscreen mode" ),
							// Textury
							cS_BadTextureUnit( "Bad texture unit" ),
							cS_BadColorDepth( "Bad color depth" ),
							cS_NoTextureLoaded( "No texture loaded" ),
							cS_TextureDoesntExist( "Texture was not loaded" ),
							cS_FontIsntSet( "Font not chosen" ),
							// Modely
							cS_MaterialHasNotTexture( "Material has not texture" ),
							cS_TextureNameIsTooLong( "Texture name is too long" ),
							cS_TextureManagerNotSet( "Texture manager not set" ),
							//Animace
							cS_BoneNotFound( "Bone not found" ),
							cS_ArmatureNotFound( "Skeleton not found" ),
							cS_AnimationNotFound( "Animation not found" ),
							// Mapy
							cS_InvalidPolygon( "Invalid polygon" ),
							cS_DuplicitPolygon( "Duplicit polygon" ),
							// XML Loader
							cS_UnknownXmlVersion( "Unknown XML version" ),
							cS_TagsDontExist( "Tags don't exist" ),
							cS_ParameterDoesntExist( "Parameter does not exist" ),
							cS_ParameterNotFound( "ParameterNotFound" );	
};

#endif
