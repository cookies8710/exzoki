#include <exzoki/texture/ee_texture.h>

EE_BYTE_t EE_TEXTURE_C::mb_Multitexturing;
EE_S32_t EE_TEXTURE_C::ms32_MaxTextureUnit;

EE_TEXTURE_C::EE_TEXTURE_C( void ): mps_Data( NULL ), mb_TextureLoaded( EE_FALSE )
{
}

EE_TEXTURE_C::~EE_TEXTURE_C( void )
{
 	Destroy();
}

void EE_TEXTURE_C::Load( EE_CCSTRING_t ccs_path, 
                         EE_TEXTURE_FILTERING_e e_filtering,
                         EE_TEXTURE_ALPHA_e e_alpha,
                         EE_BYTE_t b_r,
                         EE_BYTE_t b_g,
                         EE_BYTE_t b_b,
                         EE_S32_t s32_wrapS,
                         EE_S32_t s32_wrapT,
                         EE_S32_t s32_envMode )
{
 	if( mb_TextureLoaded == EE_TRUE )
 		Destroy();
 	
	// Nastavím data strukturu textury
 	mps_Data = new EE_TEXTURE_DATA_s;
 
 	mps_Data->e_Filtering = e_filtering;
 	mps_Data->e_Alpha = e_alpha;
	mps_Data->ab_RGB[ 0 ] = b_r;
 	mps_Data->ab_RGB[ 1 ] = b_g;
 	mps_Data->ab_RGB[ 2 ] = b_b;
 	mps_Data->s32_WrapS = s32_wrapS;
 	mps_Data->s32_WrapT = s32_wrapT;
	mps_Data->s32_EnvMode = s32_envMode;
 
 	// Podle koncovky souboru naètu texturu
 	EE_TEXTURE_TYPE_e e_TextureType = GetTextureType( ccs_path );
 	switch( e_TextureType )
 	{
  		case EE_TEXTURE_TYPE_BMP:
       		LoadBMP( ccs_path );
       		break;
  		case EE_TEXTURE_TYPE_JPG:
       		LoadJPEG( ccs_path );
       		break; 
  		case EE_TEXTURE_TYPE_TGA:
       		LoadTGA( ccs_path );
       		break;  
  		case EE_TEXTURE_TYPE_UNKNOWN:
       		EE_ERROR_C( "EE_TEXTURE_C", "Load", EE_ERROR_CODES_n::cS_UnknownFileFormat );
       		break; 
  		default:
       		EE_ERROR_C( "EE_TEXTURE_C", "Load", EE_ERROR_CODES_n::cS_Internal );
       		break; 
 	}
 	
 	mb_TextureLoaded = EE_TRUE;
 	
 	delete mps_Data;
 	return;
}

inline void EE_TEXTURE_C::Bind( EE_S32_t s32_layer ) const
{
 	// Zkontroluju, zda je textura naètena
	if( mb_TextureLoaded == EE_FALSE )
 		EE_ERROR_C( "EE_TEXTURE_C", "Load", EE_ERROR_CODES_n::cS_NoTextureLoaded );
	// Pokud je zapnutý multitexturing, zkontroluju zvolenou vrstvu a aktivuju ji
 	if( mb_Multitexturing )
 	{ 
  		if( s32_layer > ms32_MaxTextureUnit )
  		{
       		EE_CHAR_t ac_Buffer[ 256 ];
       		std::string S_Message;
       		S_Message = "Desired texture unit = ";
       		S_Message += itoa( s32_layer, ac_Buffer, 16 );
       		S_Message += "\nMax texture unit = ";
       		S_Message += itoa( ms32_MaxTextureUnit, ac_Buffer, 16 );
       		EE_ERROR_C( "EE_TEXTURE_C", "Bind", EE_ERROR_CODES_n::cS_BadTextureUnit, S_Message.c_str() );
  		}
  		else  
   		   glActiveTextureARB( s32_layer );
 	} 
 	// "Zaktivuju" texturu
//glEnable( GL_TEXTURE_2D );
 	glBindTexture( me_TextureType, mu32_TextureIndex );
 	return;
}


EE_BOOL_t EE_TEXTURE_C::EnableMultitexturing( void )
{
 	// Zjistím, zda stroj multitexturing podporuje
 	if( !strstr( (EE_PCHAR_t)glGetString( GL_EXTENSIONS ), "ARB_multitexture" ) )
 	{
 		ms32_MaxTextureUnit = GL_TEXTURE0_ARB;  
  		return( mb_Multitexturing = EE_FALSE );  
 	}    
	else
 	{
  		// Získám maximální poèet vrstev
		glGetIntegerv( GL_MAX_TEXTURE_UNITS_ARB, (GLint*)&ms32_MaxTextureUnit );
  		ms32_MaxTextureUnit += GL_TEXTURE0_ARB - 1;
  		// Získám adresy multitexturingových funkcí
		glMultiTexCoord1fARB = wglGetProcAddress( "glMultiTexCoord1fARB" );     
  		glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress( "glMultiTexCoord2fARB" ); 
  		glMultiTexCoord3fARB = wglGetProcAddress( "glMultiTexCoord3fARB" ); 
  		glMultiTexCoord4fARB = wglGetProcAddress( "glMultiTexCoord4fARB" ); 
  		glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress( "glActiveTextureARB" ); 
  		glClientActiveTextureARB = wglGetProcAddress( "glClientActiveTextureARB" ); 
  		return( mb_Multitexturing = EE_TRUE );  
 	}
}

EE_S32_t EE_TEXTURE_C::GetMaxTextureUnit( void ) 
{
 // napsat   
}

void EE_TEXTURE_C::Destroy( void )
{
	if( mb_TextureLoaded )
	{
		glDeleteTextures( 1, (GLuint*)&mu32_TextureIndex );
		mb_TextureLoaded = EE_FALSE;	
	}		
}


EE_TEXTURE_TYPE_e EE_TEXTURE_C::GetTextureType( EE_CCSTRING_t cpc_path )
{
 	EE_TEXTURE_TYPE_e e_TextureType = EE_TEXTURE_TYPE_UNKNOWN;
 
 	// Vyextrahuju z øetìzce koncovku - nalézá se za teèkou
	std::string S_Extension( cpc_path + std::string( cpc_path ).find( '.' ) + 1 ); // co když tam je více teèek ? -> napsat
  	for( EE_U32_t u32_Char( 0 ), u32_NChars( S_Extension.size() ); u32_Char < u32_NChars; u32_Char++ )
  		S_Extension[ u32_Char ] = tolower( S_Extension[ u32_Char ] );
	
	// Zjistím typ souboru podle koncovky
 	if( S_Extension == std::string( "bmp" ) )
  		e_TextureType = EE_TEXTURE_TYPE_BMP;
 	else if( S_Extension == std::string( "jpg" ) )
  		e_TextureType = EE_TEXTURE_TYPE_JPG;  
 	else if( S_Extension == std::string( "tga" ) )
  		e_TextureType = EE_TEXTURE_TYPE_TGA;   

 	return( e_TextureType ); 
}

void EE_TEXTURE_C::LoadBMP( EE_CCSTRING_t ccs_path )
{
 	EE_SYSTEM_FILE_C C_File;
 	EE_S32_t s32_Infosize, s32_BitsSize;
 	EE_S32_t s32_PaletteSize; //
 	EE_PBYTE_t pb_Bits = NULL;
 	BITMAPFILEHEADER s_Header;
 	BITMAPINFO s_Info;
 	RGBQUAD *ps_Palette( EE_NULL ); //
 
 	// Otevøe soubor
 	C_File.Open( ccs_path, EE_SYSTEM_FILE_READ, EE_SYSTEM_FILE_BINARY );
 	
 	// Naète hlavièku
 	C_File.Read( &s_Header, sizeof( BITMAPFILEHEADER ) );
 
 	// Naète informace o bitmapì
 	C_File.Read( &s_Info.bmiHeader, sizeof( BITMAPINFOHEADER ) );
 	s32_PaletteSize = s_Header.bfOffBits - ( sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) );
 	ps_Palette = (RGBQUAD*)new char[ s32_PaletteSize ];
 	C_File.Read( ps_Palette, s32_PaletteSize );
  
 	// Zjistí velikost obrázku bitmapy
 	if( s_Info.bmiHeader.biSizeImage == 0 )
  		s32_BitsSize = ( s_Info.bmiHeader.biWidth *
                    	  s_Info.bmiHeader.biBitCount + 7 ) /
                       8 * abs( s_Info.bmiHeader.biHeight );
 	else
  		s32_BitsSize = s_Info.bmiHeader.biSizeImage;
 
 	// Naète obrázek 
 	pb_Bits = new EE_BYTE_t[ s32_BitsSize ];
 	C_File.Read( pb_Bits, s32_BitsSize );
 	// Uzavøe soubor
 	C_File.Close();

 	// 
 	switch( s_Info.bmiHeader.biBitCount )
 	{
  		case 8: // 8-bitová barevná hloubka
      	mps_Data->s32_ColorFormat = GL_RGB;
   		mps_Data->s32_NBytes = 3;
   		// Pøevod z 8bitù na 24bitù
   		{
    			EE_U32_t u32_NPixels( s_Info.bmiHeader.biWidth * s_Info.bmiHeader.biHeight );
    			EE_PBYTE_t pb_24Bit( new EE_BYTE_t[ u32_NPixels * 3 ] );
    			for( EE_U32_t u32_Pixel( 0 ); u32_Pixel < u32_NPixels; u32_Pixel++ )
		   	{ 
     				static EE_BYTE_t b_8BitColor;
     				b_8BitColor = pb_Bits[ u32_Pixel ];
     				pb_24Bit[ u32_Pixel * 3 + 0 ] = ps_Palette[ b_8BitColor ].rgbRed;
     				pb_24Bit[ u32_Pixel * 3 + 1 ] = ps_Palette[ b_8BitColor ].rgbGreen;
     				pb_24Bit[ u32_Pixel * 3 + 2 ] = ps_Palette[ b_8BitColor ].rgbBlue;
    			}
    			delete[] pb_Bits;
    			pb_Bits = pb_24Bit;
   		}
  			break;          
  		case 24: // 24-bitová barevná hloubka
   		mps_Data->s32_ColorFormat = GL_BGR_EXT;
   		mps_Data->s32_NBytes = 3;
   		break;    
  		default: // Ostatní barevné hloubky (1, 4, 16, 32)  
   		EE_ERROR_C( "EE_TEXTURE_C", "LoadBMP", EE_ERROR_CODES_n::cS_BadColorDepth, ccs_path );                   
 	}

 	if( mps_Data->e_Alpha != EE_TEXTURE_ALPHA_FALSE )
  		ConvertToRGBA( s_Info.bmiHeader.biWidth, s_Info.bmiHeader.biHeight, &pb_Bits );
 
 	// Vytvoøí z obrázku texturu
 	Build( s_Info.bmiHeader.biWidth, s_Info.bmiHeader.biHeight, pb_Bits );

 	delete[] pb_Bits;
 	delete[] ps_Palette;
 	return;
}

void EE_TEXTURE_C::LoadJPEG( EE_CCSTRING_t cpc_path )
{
 
}

void EE_TEXTURE_C::LoadTGA( EE_CCSTRING_t ccs_path )
{
 	EE_TEXTURE_TGA_IMAGE_s *ps_ImageData( 0 );		
 	EE_U16_t u16_Width( 0 ), u16_Height( 0 );			
 	EE_BYTE_t b_Length = 0;				
 	EE_BYTE_t b_ImageType = 0;					
 	EE_BYTE_t b_Bits = 0;						
 	EE_S32_t s32_Channels = 0;					
 	EE_S32_t s32_Stride = 0;					
 	EE_S32_t s32_I = 0;						
 
 	EE_SYSTEM_FILE_C C_File;
	
	
 	C_File.Open( ccs_path, EE_SYSTEM_FILE_READ, EE_SYSTEM_FILE_BINARY );
 			
 	
 	ps_ImageData = new EE_TEXTURE_TGA_IMAGE_s;

 	C_File.Read( &b_Length, sizeof(EE_BYTE_t) );
 
 	C_File.Seek( 1, EE_SYSTEM_FILE_DIRECTION_CURRENT );
	
 	C_File.Read( &b_ImageType, sizeof(EE_BYTE_t) );
 
  	C_File.Seek( 9, EE_SYSTEM_FILE_DIRECTION_CURRENT );	
	// Read the width, height and bits per pixel (16, 24 or 32)
	C_File.Read( &u16_Width,  sizeof(EE_U16_t) );
	C_File.Read( &u16_Height, sizeof(EE_U16_t) );
	C_File.Read( &b_Bits,   sizeof(EE_BYTE_t) );
	C_File.Seek( b_Length + 1, EE_SYSTEM_FILE_DIRECTION_CURRENT );
	
	if( b_Bits != 16 && b_Bits != 24 && b_Bits != 32 )
		EE_ERROR_C( "EE_TEXTURE_C", "LoadTGA", EE_ERROR_CODES_n::cS_BadColorDepth, ccs_path );       
		// Check if the image is RLE compressed or not
	if( b_ImageType != EE_TEXTURE_TGA_RLE )
	{
		// Check if the image is a 24 or 32-bit image
		if(b_Bits == 24 || b_Bits == 32)
		{
			switch( b_Bits )
			{
             case 24:        
              mps_Data->s32_ColorFormat = GL_RGB;
              mps_Data->s32_NBytes = 3;
              break;
             case 32:        
              mps_Data->s32_ColorFormat = GL_RGBA;
              mps_Data->s32_NBytes = 4;
              break; 
            }
            // Calculate the channels (3 or 4) - (use bits >> 3 for more speed).
			// Next, we calculate the stride and allocate enough memory for the pixels.
			s32_Channels = b_Bits / 8;
			s32_Stride = s32_Channels * u16_Width;
			ps_ImageData->pb_Data = new EE_BYTE_t[s32_Stride * u16_Height];

			// Load in all the pixel data line by line
			for(int y = 0; y < u16_Height; y++)
			{
				// Store a pointer to the current line of pixels
				EE_PBYTE_t pb_Line = &(ps_ImageData->pb_Data[s32_Stride * y]);

				// Read in the current line of pixels
				C_File.Read( pb_Line, s32_Stride );
			
				// Go through all of the pixels and swap the B and R values since TGA
				// files are stored as BGR instead of RGB (or use GL_BGR_EXT verses GL_RGB)
				for(int i = 0; i < s32_Stride; i += s32_Channels)
				{
					int temp     = pb_Line[i];
					pb_Line[i]     = pb_Line[i + 2];
					pb_Line[i + 2] = temp;
				}
			}
		}
		// Check if the image is a 16 bit image (RGB stored in 1 unsigned short)
		else if(b_Bits == 16)
		{
			mps_Data->s32_ColorFormat = GL_RGB;
            mps_Data->s32_NBytes = 3;
            
            EE_U16_t u16_Pixels = 0;
			EE_S32_t s32_R=0, s32_G=0, s32_B=0;

			// Since we convert 16-bit images to 24 bit, we hardcode the channels to 3.
			// We then calculate the stride and allocate memory for the pixels.
			s32_Channels = 3;
			s32_Stride = s32_Channels * u16_Width;
			ps_ImageData->pb_Data = new EE_BYTE_t[s32_Stride * u16_Height];

			// Load in all the pixel data pixel by pixel
			for(int i = 0; i < u16_Width*u16_Height; i++)
			{
				// Read in the current pixel
				C_File.Read( &u16_Pixels, sizeof(EE_U16_t));
				
				// To convert a 16-bit pixel into an R, G, B, we need to
				// do some masking and such to isolate each color value.
				// 0x1f = 11111 in binary, so since 5 bits are reserved in
				// each unsigned short for the R, G and B, we bit shift and mask
				// to find each value.  We then bit shift up by 3 to get the full color.
				s32_B = (u16_Pixels & 0x1f) << 3;
				s32_G = ((u16_Pixels >> 5) & 0x1f) << 3;
				s32_R = ((u16_Pixels >> 10) & 0x1f) << 3;
				
				// This essentially assigns the color to our array and swaps the
				// B and R values at the same time.
				ps_ImageData->pb_Data[i * 3 + 0] = s32_R;
				ps_ImageData->pb_Data[i * 3 + 1] = s32_G;
				ps_ImageData->pb_Data[i * 3 + 2] = s32_B;
			}
		}	
		// Else return a NULL for a bad or unsupported pixel format
		else
			return;
	}
	// Else, it must be Run-Length Encoded (RLE)
	else
	{
		// First, let me explain real quickly what RLE is.  
		// For further information, check out Paul Bourke's intro article at: 
		// http://astronomy.swin.edu.au/~pbourke/dataformats/rle/
		// 
		// Anyway, we know that RLE is a basic type compression.  It takes
		// colors that are next to each other and then shrinks that info down
		// into the color and a integer that tells how much of that color is used.
		// For instance:
		// aaaaabbcccccccc would turn into a5b2c8
		// Well, that's fine and dandy and all, but how is it down with RGB colors?
		// Simple, you read in an color count (rleID), and if that number is less than 128,
		// it does NOT have any optimization for those colors, so we just read the next
		// pixels normally.  Say, the color count was 28, we read in 28 colors like normal.
		// If the color count is over 128, that means that the next color is optimized and
		// we want to read in the same pixel color for a count of (colorCount - 127).
		// It's 127 because we add 1 to the color count, as you'll notice in the code.

		// Create some variables to hold the rleID, current colors read, channels, & stride.
		EE_BYTE_t b_RLEID = 0;
		EE_S32_t s32_ColorsRead = 0;
		mps_Data->s32_NBytes = s32_Channels = b_Bits / 8;
		switch( s32_Channels )
		{
         case 24:
          mps_Data->s32_ColorFormat = GL_RGB;
          break;
         case 32:
          mps_Data->s32_ColorFormat = GL_RGBA;    
          break;                 
         default:
          EE_ERROR_C( "EE_TEXTURE_C", "LoadTGA", EE_ERROR_CODES_n::cS_BadColorDepth, ccs_path );        
        }
        s32_Stride = s32_Channels * u16_Width;

		// Next we want to allocate the memory for the pixels and create an array,
		// depending on the channel count, to read in for each pixel.
		ps_ImageData->pb_Data = new EE_BYTE_t[s32_Stride * u16_Height];
		EE_PBYTE_t pb_Colors = new EE_BYTE_t[s32_Channels];

		// Load in all the pixel data
		int i(0);
        while(i < u16_Width*u16_Height)
		{
			// Read in the current color count + 1
			C_File.Read(&b_RLEID, sizeof(EE_BYTE_t));
			
			// Check if we don't have an encoded string of colors
			if(b_RLEID < 128)
			{
				// Increase the count by 1
				b_RLEID++;

				// Go through and read all the unique colors found
				while(b_RLEID)
				{
					// Read in the current color
					C_File.Read(pb_Colors, sizeof(EE_BYTE_t) * s32_Channels);

					// Store the current pixel in our image array
					ps_ImageData->pb_Data[s32_ColorsRead + 0] = pb_Colors[2];
					ps_ImageData->pb_Data[s32_ColorsRead + 1] = pb_Colors[1];
					ps_ImageData->pb_Data[s32_ColorsRead + 2] = pb_Colors[0];

					// If we have a 4 channel 32-bit image, assign one more for the alpha
					if(b_Bits == 32)
						ps_ImageData->pb_Data[s32_ColorsRead + 3] = pb_Colors[3];

					// Increase the current pixels read, decrease the amount
					// of pixels left, and increase the starting index for the next pixel.
					i++;
					b_RLEID--;
					s32_ColorsRead += s32_Channels;
				}
			}
			// Else, let's read in a string of the same character
			else
			{
				// Minus the 128 ID + 1 (127) to get the color count that needs to be read
				b_RLEID -= 127;

				// Read in the current color, which is the same for a while
				C_File.Read( pb_Colors, sizeof(EE_BYTE_t) * s32_Channels );

				// Go and read as many pixels as are the same
				while(b_RLEID)
				{
					// Assign the current pixel to the current index in our pixel array
					ps_ImageData->pb_Data[s32_ColorsRead + 0] = pb_Colors[2];
					ps_ImageData->pb_Data[s32_ColorsRead + 1] = pb_Colors[1];
					ps_ImageData->pb_Data[s32_ColorsRead + 2] = pb_Colors[0];

					// If we have a 4 channel 32-bit image, assign one more for the alpha
					if(b_Bits == 32)
						ps_ImageData->pb_Data[s32_ColorsRead + 3] = pb_Colors[3];

					// Increase the current pixels read, decrease the amount
					// of pixels left, and increase the starting index for the next pixel.
					i++;
					b_RLEID--;
					s32_ColorsRead += s32_Channels;
				}
				
			}
				
		}

		// Free up pColors
		delete[] pb_Colors;
	}

	// Close the file pointer that opened the file
	C_File.Close();

	// Fill in our tImageTGA structure to pass back
	ps_ImageData->u16_Channels = s32_Channels;
	ps_ImageData->u16_Width    = u16_Width;
	ps_ImageData->u16_Height    = u16_Height;


    
    // B u i l d   
    Build( ps_ImageData->u16_Width, ps_ImageData->u16_Height, ps_ImageData->pb_Data );  
}

void EE_TEXTURE_C::Build( EE_U32_t u32_width, EE_U32_t u32_height, EE_PBYTE_t pb_bits )
{
 	// Nastavím typ textury (1D/2D)
	me_TextureType = ( u32_height == 1 ) ? GL_TEXTURE_1D : GL_TEXTURE_2D;
 
 	// Vygeneruju nový identifikátor
	glGenTextures( 1, (GLuint*)&mu32_TextureIndex );
 	glBindTexture( me_TextureType, mu32_TextureIndex );
   
   // Nastavím OpenGL
 	glTexParameteri( me_TextureType, GL_TEXTURE_WRAP_S, mps_Data->s32_WrapS );
 	if( me_TextureType == GL_TEXTURE_2D )
  		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mps_Data->s32_WrapT );
 
 	bool b_Mipmapping;
 	switch( mps_Data->e_Filtering )
 	{
  		case EE_TEXTURE_FILTERING_NEAREST:
   		glTexParameteri( me_TextureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
   		glTexParameteri( me_TextureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
   		b_Mipmapping = false;
   		break;
  		case EE_TEXTURE_FILTERING_BILINEAR_NO_MIPMAPPING:
   		glTexParameteri( me_TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   		glTexParameteri( me_TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
   		b_Mipmapping = false;
   		break; 
  		case EE_TEXTURE_FILTERING_BILINEAR:
   		glTexParameteri( me_TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   		glTexParameteri( me_TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
   		b_Mipmapping = true;
   		break;
  		case EE_TEXTURE_FILTERING_TRILINEAR:
   		glTexParameteri( me_TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   		glTexParameteri( me_TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
   		b_Mipmapping = true;
   		break;  
 	}
 /*
 EE_S32_t s32_ColorFormat;
 EE_S32_t s32_NBytes;
 switch( mps_Data->e_Alpha )
 {
  case EE_TEXTURE_ALPHA_FALSE:
   s32_ColorFormat = GL_BGR_EXT;
   s32_NBytes = 3;
   break;
  case EE_TEXTURE_ALPHA_TRUE:
  case EE_TEXTURE_ALPHA_BY_GREYSCALE:    
   s32_ColorFormat = GL_RGBA;
   s32_NBytes = 4;
  break;   
 } */
  
 	glTexEnvi( me_TextureType, GL_TEXTURE_ENV_MODE, mps_Data->s32_EnvMode );
	
	// Vytvoøím texturu z obrazových dat
 	if( !b_Mipmapping )
 	{
  		if( me_TextureType == GL_TEXTURE_1D )
   		glTexImage1D( GL_TEXTURE_1D, 0, mps_Data->s32_NBytes, 
                 		  u32_width,
                 		  0, mps_Data->s32_ColorFormat, GL_UNSIGNED_BYTE, pb_bits );
  		else if( me_TextureType == GL_TEXTURE_2D )
   		glTexImage2D( GL_TEXTURE_2D, 0, mps_Data->s32_NBytes, 
                 		  u32_width,
                 		  u32_height,
                 		  0, mps_Data->s32_ColorFormat, GL_UNSIGNED_BYTE, pb_bits );
 	}
 	else 
 	{ 
  		if( me_TextureType == GL_TEXTURE_1D )
   		gluBuild1DMipmaps( GL_TEXTURE_1D, mps_Data->s32_NBytes, 
                      		 u32_width,
                      	  	 mps_Data->s32_ColorFormat, GL_UNSIGNED_BYTE, pb_bits );
  		else if( me_TextureType == GL_TEXTURE_2D )  
   		gluBuild2DMipmaps( GL_TEXTURE_2D, mps_Data->s32_NBytes, 
                      		 u32_width,
                      		 u32_height,
                      		 mps_Data->s32_ColorFormat, GL_UNSIGNED_BYTE, pb_bits );
                                   
 	}
 
 	return;
}

void EE_TEXTURE_C::ConvertToRGBA( EE_U32_t u32_width, 
                                   EE_U32_t u32_height, 
                                   EE_PBYTE_t* ppb_bits )
{
 	EE_U32_t u32_NPixels = u32_width * u32_height;
 	EE_PBYTE_t pb_RGBA = NULL;
 
 	EE_U32_t u32_CurrentPixel;
 	EE_U32_t u32_CurrentPixelRGBA, u32_CurrentPixelBGR;
 
 	mps_Data->s32_ColorFormat = GL_RGBA;
 	mps_Data->s32_NBytes = 4;
 
 	pb_RGBA = new EE_BYTE_t[ u32_NPixels * 4 ];
 	for( EE_U32_t u32_Height = 0; u32_Height < u32_height; u32_Height++ )
  		for( EE_U32_t u32_Width = 0; u32_Width < u32_width; u32_Width++ )
  		{ 
   		u32_CurrentPixel = u32_Height * u32_width + u32_Width;
   		u32_CurrentPixelRGBA = u32_CurrentPixel * 4; 
   		u32_CurrentPixelBGR = u32_CurrentPixel * 3; 
   
   		pb_RGBA[ u32_CurrentPixelRGBA ] = (*ppb_bits)[ u32_CurrentPixelBGR + 2 ];
   		pb_RGBA[ u32_CurrentPixelRGBA + 1 ] = (*ppb_bits)[ u32_CurrentPixelBGR + 1 ];
   		pb_RGBA[ u32_CurrentPixelRGBA + 2 ] = (*ppb_bits)[ u32_CurrentPixelBGR ];
   		switch( mps_Data->e_Alpha )
   		{
    			case EE_TEXTURE_ALPHA_TRUE:
     				if( 
        			( (*ppb_bits)[ u32_CurrentPixelBGR + 2 ] == mps_Data->ab_RGB[ 0 ] ) &&
        			( (*ppb_bits)[ u32_CurrentPixelBGR + 1 ] == mps_Data->ab_RGB[ 1 ] ) &&
        			( (*ppb_bits)[ u32_CurrentPixelBGR ] == mps_Data->ab_RGB[ 2 ] ) )
      				pb_RGBA[ u32_CurrentPixelRGBA + 3 ] = 0;
     				else  
      				pb_RGBA[ u32_CurrentPixelRGBA + 3 ] = 255;
     				break;
    			case EE_TEXTURE_ALPHA_BY_GREYSCALE:
     				pb_RGBA[ u32_CurrentPixelRGBA + 3 ] = ( (*ppb_bits)[ u32_CurrentPixelBGR + 2 ] == mps_Data->ab_RGB[ 0 ] ) &&
        			( (*ppb_bits)[ u32_CurrentPixelBGR + 1 ] == mps_Data->ab_RGB[ 1 ] ) &&
        			( (*ppb_bits)[ u32_CurrentPixelBGR ] == mps_Data->ab_RGB[ 2 ] )?0:(*ppb_bits)[ u32_CurrentPixelBGR + 2 ];
     				break;   
   		}
  		} 
 
 	delete[] (*ppb_bits);
 	(*ppb_bits) = pb_RGBA;
 
 	return;
}
