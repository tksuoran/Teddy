
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2020  Timo Suoranta
	tksuoran@gmail.com

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#ifndef TEDDY__GRAPHICS__TEXTURE__H
#define TEDDY__GRAPHICS__TEXTURE__H


#include "Teddy/Graphics/Color.h"
#include "Teddy/Graphics/Device.h"
#include "Teddy/Maths/Vector2.h"
#include "Teddy/MixIn/Named.h"
#include "Teddy/MixIn/Options.h"


namespace Teddy    {
namespace Graphics {


//!  Texture
class Texture : public Teddy::MixIn::Named, public Teddy::MixIn::Options {
public:
	static const unsigned long TX_RESERVED       ;
	static const unsigned long TX_BLIT_NO_SCALE  ;
	static const unsigned long TX_GENERATE_ALPHA ;
	static const unsigned long TX_ALPHA_ONLY     ;
	static const unsigned long TX_NO_ALPHA       ;

	static const unsigned long WRAP_REPEAT             ;
	static const unsigned long WRAP_CLAMP              ;
													   
	static const unsigned long ENV_BLEND               ;
	static const unsigned long ENV_REPLACE             ;
	static const unsigned long ENV_DECAL               ;
	static const unsigned long ENV_MODULATE            ;
													   
	static const unsigned long FORMAT_INTENSITY        ;
	static const unsigned long FORMAT_LUMINANCE        ;
	static const unsigned long FORMAT_LUMINANCE_ALPHA  ;
	static const unsigned long FORMAT_ALPHA            ;
	static const unsigned long FORMAT_RGB              ;
	static const unsigned long FORMAT_RGBA             ;
													   
	static const unsigned long FILTER_NEAREST              ;
	static const unsigned long FILTER_LINEAR               ;
	static const unsigned long FILTER_NEAREST_MIPMAP_LINEAR;
	static const unsigned long FILTER_LINEAR_MIPMAP_LINEAR ;

public:
	Texture( const std::string &name );
	virtual ~Texture();

    void putData     ( unsigned char *data, const Teddy::Maths::IntVector2 &size, int format, unsigned long modify );
	void apply       ();
	bool isBad       ();
    bool isGood      ();
	void setWrap     ( int wrap_s, int wrap_t );
	void setEnv      ( int env );
	void setEnv      ( int env, const Color &c );
	void setFilter   ( const unsigned long filter );
	void setMagFilter( const unsigned long filter );
	void setMinFilter( const unsigned long filter );

    const Teddy::Maths::IntVector2 &getSize();

public:
	bool         doFormat           ();
	bool         doSize             ();
	virtual bool doBind             ();
	void         setWorkData        ( void *data, bool alloc = true );

	void convert_to_a       ();
	void convert_to_rgb     ();
	void convert_rgba       ();

	void convert_rgb_to_a   ();
	void convert_rgba_to_a  ();
	void convert_a_to_rgb   ();
	void convert_rgba_to_rgb();
	void convert_rgb_to_rgba();

protected:
	unsigned char            *work_data;               //!<  Current working image data for Texture
	int                       work_data_pixel_format;  //!<  Working image format
	bool                      work_data_allocated;     //!<  Flag true if work_data was internally allocated
    bool                      is_good;                 //!<  If true, the texture is ready to be used
	bool                      is_bad;                  //!<  If true, the texture is known to be bad
    Teddy::Maths::IntVector2  size;
	int                       wrap_s;                  //!<  Texture s-axis wrap mode
	int                       wrap_t;                  //!<  Texture t-axis wrap mode
	unsigned long             mag_filter;              //!<  Texture filter mode for maginification
	unsigned long             min_filter;              //!<  Texture filter mode for minification
	int                       env_function;            //!<  Texture function
	Color                     env_color;               //!<  Color for Texture function
	Teddy::MixIn::Options     modify;                  //!<  Allowed and requested image modifications
	int                       gl_internal_format;      //!<  OpenGL image data format
	GLuint                    gl_texture_id;           //!<  OpenGL Texture id
};


};  //  namespace Graphics
};  //  namespace Teddy


#endif  //  TEDDY__GRAPHICS__TEXTURE__H

