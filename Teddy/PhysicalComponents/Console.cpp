
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2002  Timo Suoranta
	tksuoran@cc.helsinki.fi

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

	$Id: Console.cpp,v 1.5 2002/03/12 10:46:07 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/PhysicalComponents/Console.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/PhysicalComponents/GradientFill.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/PhysicalComponents/Label.h"
#include "Teddy/Graphics/Color.h"
#include "Teddy/Graphics/Font.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include <cstdlib>
using namespace std;
#endif
using namespace Teddy::Graphics;
using namespace Teddy::Signals;


namespace Teddy              {
namespace PhysicalComponents {


//!  Constructor; font, width (chars), height (chars) 
Console::Console( const std::string &name, const int w, const int h )
:Area( name )
{
	this->font_width       = style->monospace_font->getWidth();
	this->font_height      = style->monospace_font->getHeight();
	this->width_chars      = w;
	this->height_chars     = h;
	this->max_height_chars = h;

	//  This might need to be changed somehow
	buffer_lines.reserve( 200 );
	for( int i=0; i<h; i++ ){
		buffer_lines.push_back( new string("") );
	}

	topleft_x      = 0;
	topleft_y      = 0;
	cx             = 0;
	cy             = 0;
	cursor_visible = true;  //  FIX should be in Style
	text_color     = Color::GRAY_75;
//	logical_ui     = NULL;

    fill_base_pixels[0] = w * font_width;
    fill_base_pixels[1] = h * font_height;

	//  FIX  Don't do this in final Console
	//       Only while debugging when there is no decent
	//       source for LayoutConstraint
	GradientFill *fill = new GradientFill(
		Color( 0.2f, 0.3f, 0.4f, 0.99f ),
		Color( 0.2f, 0.3f, 0.4f, 0.99f ),
		Color( 0.1f, 0.2f, 0.3f, 0.66f ),
		Color( 0.1f, 0.2f, 0.3f, 0.66f )
	);
//	WindowFrame *frame = new WindowFrame( name );
	this->insert( fill );
//	this->insert( frame );

	drawing_ordering = post_self;

	bind( Event::WindowFocusActiveEvent_ID, functor( this, &Console::focusActive ) );
	bind( Event::KeyDownEvent_ID          , functor( this, &Console::keyDown     ) );
}

/*

C:\Work\Teddy-1.78\Teddy\PhysicalComponents\Console.cpp(89)
: error: more than one instance of overloaded function "functor" matches the argument list:

            function template "Teddy::Signals::functor(T *, void (T::*)(A1))"
            function template "Teddy::Signals::functor(T *, R (T::*)(A1))"

            argument types are: (Teddy::PhysicalComponents::Console *, void (Teddy::PhysicalComponents::Console::*)(const Teddy::PhysicalComponents::Event &))
   bind( WindowFocusActiveEvent_ID, functor( this, &Console::focusActive ) );
                                    ^

  */

/*
const int Event_ID                  =  0;
const int WindowEvent_ID            =  1;
const int WindowFocusActiveEvent_ID =  2;
const int WindowPopupOpenEvent_ID   =  3;
const int WindowPopupCloseEvent_ID  =  4;
const int WindowMoveEvent_ID        =  5;
const int WindowSizeEventEvent_ID   =  6;
const int WindowToFrontEvent_ID     =  7;
const int WindowToBackEvent_ID      =  8;
const int WindowSplitUpdateEvent_ID =  9;
const int MouseEvent_ID             = 10;
const int MouseButtonEvent_ID       = 11;
const int MouseMotionEvent_ID       = 12;
const int MouseDragEvent_ID         = 13;
const int MouseHoldDragEvent_ID     = 14;
const int KeyEvent_ID               = 15;
const int KeyDownEvent_ID           = 16;
const int KeyUpEvent_ID             = 17;
const int JoyEvent_ID               = 18;
const int JoyButtonEvent_ID         = 19;
const int JoyAxisEvent_ID           = 20;
const int JoyHatEvent_ID            = 21;
const int JoyBallEvent_ID           = 22;
*/



//!  Area Layout interface - Set Area size
/*!
	\param width Console width in characters
	\param height Console height in characters
	\todo  Support for variable width fonts
    */
#if 0
void Console::setSize( const int width, const int height ){
	Area::setSize( width, height );

	//  Calculate new size
	width_chars  = width  / style->monospace_font->getWidth ();
	height_chars = height / style->monospace_font->getHeight();

	//  Reposition view to last visible lines
	//  FIX could be configurable: first visible lines, last visible lines
	//  FIX actually should maintain topleft_y (adjust though - which direction?)
//	topleft_y = max_height_chars - height_chars;
	if( topleft_y < 0 ){
//		cout << "ERROR topleft_y < 0" << endl;
		topleft_y = 0;
	}
}
#endif


//!  Draw
/*virtual*/ void Console::drawSelf(){
	color( text_color );
	view->enable( View::BLEND );
	view->enable( View::TEXTURE_2D );
	view->setBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	//  Draw visible parts of lines

	for( int y=0; y<height_chars && (long)(y+topleft_y)<(long)(buffer_lines.size()); y++ ){
        string  line = buffer_lines[y+topleft_y]->substr( topleft_x, width_chars );
        Vector2 pos( 0.0f, (float)(font_height * y) );

		drawString( pos, line.c_str(), style->monospace_font );
	}

	//  FIX  Draw cursor if wanted
	if(
		cursor_visible &&
		(cx-topleft_x)< width_chars  &&
		(cy-topleft_y)< height_chars &&
		cx>=topleft_x &&
		cy>=topleft_y
    ){
        Vector2 cpos( (cx-topleft_x)*font_width, (cy-topleft_y)*font_height );
		drawString( cpos, "_", style->monospace_font );
	}

/*	char tmp[100];
	sprintf( tmp, "Cursor: %d, %d topleft_y: %d height_chars: %d", cx, cy, topleft_y, height_chars );
	drawString(  style->monospace_font, tmp, 0, -35 );
*/
}


//!  Received or lost keyboard focus
/*virtual*/ bool Console::focusActive( const Event &e ){
	if( e.state ){
		text_color = Color(0.95f,0.95f,1.00f);
	}else{				  
		text_color = Color(0.85f,0.85f,0.95f);
	}
	return true;
}


//!  Print string to buffer
Console &Console::operator<<( const string &s ){
	buffer_lines[cy]->append( s );  //  FIX  Should insert instead
	cx = buffer_lines[cy]->size();
	return *this;
}


//!  Append single char
void Console::append( int c ){
	switch( c ){
	case '\n':
		this->newLine();
		break;
	default:
//		buffer_lines[cy]
		*buffer_lines[cy] += c;
		break;
	}
}

//!  Append chars
void Console::append( const char *str, int count ){
	for( int i=0; i<count; i ++ ){
		char c = str[i];
		switch( c ){
		case '\n':
			this->newLine();
			break;
		default:
			*buffer_lines[cy] += c;
			break;
		}
	}
}


//!  Set contents of given line - no scrolling
Console &Console::setLine( const int l, const string &s ){
	buffer_lines[l]->assign( s );
	return *this;
}



void Console::scroll( int x1, int y1, int x2, int y2, int dx, int dy ){
	//  FIX
}


void Console::cursorDown(){
	if( (long)(cy)<(long)(buffer_lines.size())-1 ){
		cy++;
	}
	//printf( "Cursor: %d, %d topleft_y: %d height_chars: %d\n", cx, cy, topleft_y, height_chars );
	if( cy>topleft_y+height_chars-1 ){
		topleft_y++;
		//printf( "Scrolling down\n" );
		//printf( "Cursor: %d, %d topleft_y: %d height_chars: %d\n", cx, cy, topleft_y, height_chars );
	}
}


void Console::insertLine( const int y ){
	buffer_lines.insert( buffer_lines.begin() + y, new string("") );
}


void Console::killLine( const int y ){
	string *line = buffer_lines[y];
	delete line;
	buffer_lines.erase( buffer_lines.begin() + y );
}


void Console::killChar( const int x, const int y ){
	//  assert( x > 0 );
	int    right_part = buffer_lines[y]->size() - x;
	string new_line   = buffer_lines[y]->substr( 0, x-1 );
	if( right_part > 0 ){
		new_line.append( buffer_lines[y]->substr( x, right_part ) );
	}
	buffer_lines[y]->assign( new_line );
}


/*void Console::setLogicalUI( LogicalUI *lui ){
	this->logical_ui = lui;
}

void Console::parse( const char *commandline ){
	if( logical_ui!=NULL ){
		logical_ui->invoke( commandline );
	}
}*/


/*!
	Insert key

	\warning Pretty buggy - work in progress
	\warning Direct use of physical keys, no mapping :I
*/
/*virtual*/ bool Console::keyDown( const Event &e ){
	string old_line;
	string new_line;
	int    right_part;

	switch( e.key.sym ){

	//  Editing
	case SDLK_BACKSPACE:
		//  Kill prev char

		if( cx>0 ){
			killChar( cx, cy );
			cx--;
		}else{  //  Also join with previous line
			if( cy>0 ){
					
				cx = buffer_lines[cy-1]->size();
				buffer_lines[cy-1]->append( *buffer_lines[cy] );
				killLine( cy );
				cy--;
			}
		}
		break;

	case SDLK_DELETE:
		//  Kill next char
		if( (long)(cx)<(long)(buffer_lines[cy]->size()) ){
			killChar( cx+1, cy );

		}else{  //  Kill newline
			if( (long)(cy)<(long)(buffer_lines.size()-1) ){
				buffer_lines[cy]->append( *buffer_lines[cy+1] );
				killLine( cy+1 );
				/*					if( cy<topleft_y ){
						topleft_y
						}*/
			}
		}
		break;
								
	// 	Newline									
	case SDLK_RETURN:			
		insertLine( cy+1 );
		cursorDown();
		right_part = buffer_lines[cy-1]->size()-cx;

		if( right_part>0 ){
			buffer_lines[cy]->append( buffer_lines[cy-1]->substr( cx, right_part ) );
		}

		if( cx>0 ){
			buffer_lines[cy-1]->assign( buffer_lines[cy-1]->substr( 0, cx ) );
//			parse( buffer_lines[cy-1]->c_str() );
		}else{
			buffer_lines[cy-1]->assign( string("") );
		}

		cx = 0;
		break;

	//  Move cursor up / down
	case SDLK_UP:
		if( cy>0 ){
			cy--;
			if( topleft_y>cy ){
				topleft_y--;
			}
			right_part = buffer_lines[cy]->size()-cx;
			if( right_part<0 ){
				cx += right_part;
			}
		}
		break;
	case SDLK_DOWN:
        cursorDown();
		right_part = buffer_lines[cy]->size()-cx;
		if( right_part<0 ){
			cx += right_part;
		}
		break;

		//  Move cursor right / left
	case SDLK_RIGHT:
		if( (long)(cx) < (long)(buffer_lines[cy]->size()) ){
			cx++;
		}
		break;

	case SDLK_LEFT:
		if( cx>0 ){
			cx--;
			}
		break;

		//  Move cursor to start of / end of line
	case SDLK_HOME:
		cx = 0;
		break;

	case SDLK_END:
		cx = buffer_lines[cy]->size();
		break;

	case SDLK_INSERT:
	case SDLK_PAGEUP:
	case SDLK_PAGEDOWN:
	case SDLK_PAUSE:   //  ? Passthrough?
	case SDLK_ESCAPE:  //  ?
	case SDLK_TAB:     //  To next tab pos
	case SDLK_CLEAR:   //  ? clear line ?
	case SDLK_PRINT:
	case SDLK_SYSREQ:
	case SDLK_BREAK:
	case SDLK_MENU:
	case SDLK_POWER:
	case SDLK_HELP:
		break;

		//  Modifiers
	case SDLK_NUMLOCK:
	case SDLK_CAPSLOCK:
	case SDLK_SCROLLOCK:
	case SDLK_RSHIFT:
	case SDLK_LSHIFT:
	case SDLK_RCTRL:
	case SDLK_LCTRL:
	case SDLK_RALT:
	case SDLK_LALT:
	case SDLK_RMETA:
	case SDLK_LMETA:
	case SDLK_LSUPER:
	case SDLK_RSUPER:
	case SDLK_MODE:
		break;

		//  Function keys
	case SDLK_F1:
	case SDLK_F2:
	case SDLK_F3:
	case SDLK_F4:
	case SDLK_F5:
	case SDLK_F6:
	case SDLK_F7:
	case SDLK_F8:
	case SDLK_F9:
	case SDLK_F10:
	case SDLK_F11:
	case SDLK_F12:
	case SDLK_F13:
	case SDLK_F14:
	case SDLK_F15:
		break;

		//  Number keypad
	case SDLK_KP0:
	case SDLK_KP1:
	case SDLK_KP2:
	case SDLK_KP3:
	case SDLK_KP4:
	case SDLK_KP5:
	case SDLK_KP6:
	case SDLK_KP7:
	case SDLK_KP8:
	case SDLK_KP9:
		break;

		//  Insert character
	default:
		char buf[25];
		unsigned int sym = e.key.unicode;

		buf[1] = 0;
		if( (sym & 0xff80) == 0 ) {
			buf[0] = sym & 0x7f;
		}else{
			switch( sym ){
			case 167: buf[0] = '�'; break;
			case 196: buf[0] = '�'; break;
			case 197: buf[0] = '�'; break;
			case 214: buf[0] = '�'; break;
			case 228: buf[0] = '�'; break;
			case 229: buf[0] = '�'; break;
			case 246: buf[0] = '�'; break;
			default:
				sprintf( buf, " %d", sym );
				break;
			}
		}

		//  Insertion
		old_line = *buffer_lines[cy];
		right_part = old_line.size()-cx;
		if( right_part > 0 ){
			new_line = old_line.substr( 0, cx );
			new_line.append( string(buf) );
			new_line.append( old_line.substr( cx, right_part ) );
			buffer_lines[cy]->erase();
			buffer_lines[cy]->append( new_line );
		}else{
			buffer_lines[cy]->append( string(buf) );
		}
		cx += strlen( buf );
		break;
	}
	return true;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy

