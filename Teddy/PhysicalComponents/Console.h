
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


#ifndef TEDDY__PHYSICAL_COMPONENTS__CONSOLE__H
#define TEDDY__PHYSICAL_COMPONENTS__CONSOLE__H


#include "Teddy/TeddyConfig.h"
#include "Teddy/PhysicalComponents/Area.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/SysSupport/StdVector.h"
#include "Teddy/SysSupport/Types.h"
using namespace Teddy::PhysicalComponents;
using namespace std;


namespace Teddy              {
namespace PhysicalComponents {


/*!
	\brief   Text (fixed width font) console userinterface component
	\warning Current console class is more instance than general console
	\todo    Selection
	\todo    Support for variable width font
	
	Console com7ponent can be used for standard input and output in
	simple text form.

	At the moment MouseListener is used for window dragging, but
	that will change into selection later, and dragging will be
	put into Frame Label.

	The basic input and output is working now, but there are still
	a number of cliches, so be aware.

	Console may or may not be connected to a parser. Currently
	I have plugged in Kamin Scheme interpreter as parser. If you
	enable it, be sure not to try to parse lines that are not
	complete, legal scheme statements. At the moment it is only
	small subset of scheme, and you can only send one line at time
	to it.
*/
class Console
:
public Area,
public EventListener
{
public:
    Console( const std::string &name, const int w, const int h );

	//	Console interface
	Console &setLine   ( const int l, const string &s );	
	Console &operator<<( const string &s );

	void append      ( const char *str, int count );
	void append      ( int c );
	void cursorDown  ();
	void newLine     (){ insertLine(cy+1); cursorDown(); cx=0; };
	void insertLine  ( const int y );                                     //!<  Insert new line
	void killLine    ( const int y );                                     //!<  Kill line
	void killChar    ( const int x, const int y );                        //!<  Kill character
	void scroll      ( int x1, int y1, int x2, int y2, int dx, int dy );  //!<  Scroll area

	virtual void drawSelf   ();  //!<  Area interface;	const? Area::		

	bool focusActive( const Event &e );
	bool keyDown    ( const Event &e );
	bool keyUp      ( const Event &e );

protected:
//	void         parse  ( const char *commandline );
	virtual void setSize( const int width, const int height );
	
	vector<string*>  buffer_lines;      //!<  Buffer
	int              font_width;        //!<  For quick access.. FIX? Observer?
	int              font_height;       //!<  For quick access.. FIX? Observer?
	int              width_chars;       //!<  Number of visible chars per line
	int              height_chars;      //!<  Number of visible lines
	int              max_height_chars;  //!<  Number of lines in buffer
	int              topleft_x;         //!<  Current scroll x-position - first visible char
	int              topleft_y;         //!<  Current scroll y-position - first visible line
	int              cx;                //!<  Cursor X position
	int              cy;                //!<  Cursor Y position
	bool             cursor_visible;    //!<  Do we want visible cursor?
	Color            text_color;        //!<  Text color
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__CONSOLE__H

