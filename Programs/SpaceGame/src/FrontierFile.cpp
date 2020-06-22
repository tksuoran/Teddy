
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


#include "Teddy/SysSupport/EndianIn.h"
#include "Teddy/SysSupport/Exception.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdString.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include <cstdlib>
#include <cctype>
#endif
#include "FrontierFile.h"
using namespace Teddy::SysSupport;


//!  FrontierFile constructor
FrontierFile::FrontierFile( const char *fname, Uint32 options ){
	EndianIn *is;             //!<  Input file stream

    stack_pointer = 0;
	is = new EndianIn( fname );
	is->set_bigendian();

	int len = is->len();
	buf = new char[ len ];
	is->read_all( buf );
	buf[len] = 0; 
	is->close(), is = NULL;
	pos = buf;

}


//!  Seek to spesified label position
void FrontierFile::seek( const char *label ){
	pos = strstr( (char*)(pos), label );
	if( pos == 0 ){
        throw( Exception("Label not found") );
	}
}


//!  Seek to spesified byte offset file position
void FrontierFile::seek( const Sint32 bytes ){
	pos += bytes;
}


//!  Seek to previously set file start
void FrontierFile::reset(){
	pos = buf;
}


//!  Seek to next non-white character
void FrontierFile::skip_white(){
	while( isspace(*pos) ){
		pos++;
	}
}


//!  Determine type of next element
int FrontierFile::get_type(){
	char *mark_beg;
	char  a;
	char  b;

	skip_white();
	mark_beg = pos;

//	cout << "? ";
//	cout.flush();

	while( true ){
		a = *pos;
//		cout << a;
//		cout.flush();

		if( pos != mark_beg ){
			//  End of label reference;
			//
			//  Unrecogniced strings from end of white spaces
			//  up to end of line or comma are intepreted as
			//  label references as label references
			if( a==13 || a==10 || a==13 || a==',' ){
//				cout << " !lr "; cout.flush();
				pos = mark_beg;
//                printf( " -FF_LABEL_REF- " );
				return FF_LABEL_REF;
			}

			//  Check if we hit unrecogniced element
			//  not terminated by newline or comma;
			//  simply skip those (db, dd, resb etc.)
			if( isspace(a) ){
				skip_white();
				mark_beg = pos;
				continue;
			}
		}

		//  Byte
		if( a=='0' ){
			pos++;
			b = *pos;
			if( b=='x' ){
				pos++;
//				cout << " !b "; cout.flush();
//                printf( " -FF_BYTE- " );
				return FF_BYTE;
			}else{
				continue;
			}
		}

		//  Start of string
		if( a=='\'' ){
//			cout << " !s "; cout.flush();
//			printf( " -FF_STRING- " );
			return FF_STRING;
		}

		//  End of label definition
		if( a==':' ){
//			cout << " !ld "; cout.flush();
			pos = mark_beg;
//			printf( " -FF_LABEL_DEF- " );
			return FF_LABEL_DEF;
		}
		pos++;
	}
}


//!  Interprete byte from file, encoded either into string or hex code
Uint8 FrontierFile::get_byte(){
	static char         *s;
	static int           string_size = 0;
	static int           string_pos  = 0;
	static bool          use_string  = false;
	static const char   *str;

	if( use_string ){
		string_pos++;
//		cout <<  "string_pos = "  << (int)(string_pos);
//		cout << " string_size = " << (int)(string_size) << endl;
		if( string_pos==string_size ){
			string_size = 0;
			string_pos  = 0;
			use_string  = false;
			pos++;
		}
	}

	if( use_string==false ){
		switch( get_type() ){

		case FF_BYTE:
			return get_byte_low( false );
			break;

		case FF_STRING:
			s           = get_string();
			string_size = strlen(s);
			string_pos  = 0;
			use_string  = true;
			str         = s;
//			cout << "String '" << s << "'" << endl;
			break;

		default:
			msg( M_FFE, "unexpected data in file" );
			return 0;
			break;
		}
	}

	if( use_string ){
        dprint( M_FFE, " '%c' ",  (char)(str[string_pos]) );
		return (Uint8)(str[string_pos]);
	}else{
		dprint( M_FFE, " Hmm? " );
		return 0;
	}
}


//!  Get first character of byte
Uint8 FrontierFile::get_byte_low( bool gt ){
	char  a;
	char  b;
	char *hex_digits = "0123456789abcdef";
	int   a_val = 0;
	int   b_val = 0;
	int   val   = 0;
	int   len   = 0;
	int   i;
	int   typ;

	if( gt ){
		typ = get_type();
	}else{
		typ = FF_BYTE;
	}
	switch( typ ){
	case FF_BYTE:
		//  Get value of first digit
		a = *pos++;
//		cout << "First digit is '" << a << endl; cout.flush();
		for( i=0; i<16; i++ ){
			if( hex_digits[i] == a ){
				a_val = i;
				len = 1;
				break;
			}
		}

		//  Not even first hex digit found? (Should not happen in valid files)
		if( len!=1 ){
			break;
		}

		//  Look for second digit, get value
		b = *pos++;
//		cout << "Second digit is '" << b << endl; cout.flush();
		for( i=0; i<16; i++ ){
			if( hex_digits[i] == b ){
				b_val = i;
				len = 2;
				break;
			}
		}

		//  Determine return value as either single or double char hex number
		if( len==2 ){
			val = (a_val<<4) + b_val;
		}else{
			pos--;  //  Back one char; it wasn't a hex digit
			if( len==1 ){
				val = a_val;
			}
		}
		break;

	case FF_STRING:    throw(  Exception("Found String, was looking for Byte")            ); break;
	case FF_LABEL_DEF: throw(  Exception("Found Label Definition, was looking for Byte")  ); break;
	case FF_LABEL_REF: throw(  Exception("Found Label Reference, was looking for Byte")   ); break;
	case FF_UNKNOWN:
	default:           throw(  Exception("Found unknown, was looking for Byte")           ); break;
	}

	if( val >255 )     throw(  Exception("VAL>255!")                                      );
	return val;

}


//!  Read signed 8-bit integer
Sint8 FrontierFile::read_Sint8(){
	Sint8 i = get_byte();
	return i;
}


//!  Read signed 16-bit integer
Sint16 FrontierFile::read_Sint16(){
	Sint32 b1 = get_byte();
	Sint32 b2 = get_byte();
	Sint32 i = b1 + (b2<<8);
	return i;
}


//!  Read signed 32-bit integer
Sint32 FrontierFile::read_Sint32(){
	Sint32 b1 = get_byte();
	Sint32 b2 = get_byte();
	Sint32 b3 = get_byte();
	Sint32 b4 = get_byte();
	Sint32 i = b1 + (b2<<8) + (b3<<16) + (b4<<24);
	return i;
}


//!  Read unsigned 8-bit integer
Uint8 FrontierFile::read_Uint8 (){
	Uint8 i = get_byte();
	return i;
}


//!  Read unsigned 16-bit integer
Uint16 FrontierFile::read_Uint16(){
	Uint32 b1 = get_byte();
	Uint32 b2 = get_byte();
	Uint16 i = b1 + (b2<<8);
	return i;
}


//!  Read unsigned 32-bit integer
Uint32 FrontierFile::read_Uint32(){
	Uint32 b1 = get_byte();
	Uint32 b2 = get_byte();
	Uint32 b3 = get_byte();
	Uint32 b4 = get_byte();
	Uint32 i = b1 + (b2<<8) + (b3<<16) + (b4<<24);
	return i;
}


//!  Read 32-bit floating point number
float FrontierFile::read_float(){
	Uint32 i = get_byte() + (get_byte()<<8) + (get_byte()<<16) + (get_byte()<<24);
	float f = *(float*)(&i);
	return f;
}


//!  Read string which ends at ' or : or , or 
char *FrontierFile::get_string(){
	char  *s   = new char[256];
	char  *beg = pos;
	int    len = 0;

//	cout << "S: ";
	switch( get_type() ){
	case FF_LABEL_DEF: throw( Exception("Found Label Definition, was looking for String") ); break;
	case FF_LABEL_REF: throw( Exception("Found Label Reference, was looking for String")  ); break;
	case FF_STRING:
		pos++;
		beg = pos;
		while( (*pos!='\'') && (*pos!=':') && (*pos!=10) && (*pos!=13) && (*pos!=',') ){
			s[len] = *pos;
			pos++;
			if( len<255 ){
				len++;
			}
		}
		s[len] = 0;
		break;

	case FF_BYTE: throw( Exception("Found Byte, was looking for String") );  break;
	case FF_UNKNOWN:
	default:      throw( Exception("Unknown, was looking for String" ) ); break;
	}
	return s;
}


//!  Read label definition
char *FrontierFile::get_label_def(){
	char *s   = new char[256];
	char *beg = pos;
	int   len = 0;

//	cout << "LD: ";
	switch( get_type() ){
	case FF_LABEL_DEF:
		while( (*pos!=':') && (*pos!=10) && (*pos!=13) ){
			s[len] = *pos;
			pos++;
			if( len<255 ){
				len++;
			}
		}
		s[len] = 0;
		pos++;
		break;

	case FF_LABEL_REF: throw( Exception("Found Label Reference, was looking for Label Definition") ); break;
	case FF_STRING:    throw( Exception("Found String, was looking for Label Definition")          ); break;
	case FF_BYTE:      throw( Exception("Found Byte, was looking for Label Definition")            ); break;
	case FF_UNKNOWN:
	default:           throw( Exception("Unknown, was looking for Label Definition")               ); break;
	}
//	cout << " D: '" << s << "' "<< endl;
	return s;
}


void FrontierFile::dump( int head, int tail ){
	char *tmp = new char[head+tail+3];
	memcpy( tmp, pos-head, head+tail );
	tmp[head+tail-1] = 0;
	dprint( M_FFE, "\n---begin file dump---\n%s---end file dump---\n", tmp );
    delete[] tmp;
}



//!  Read reference to a label
char *FrontierFile::get_label_ref(){
	char *s   = new char[ 80 ];
	int   len = 0;
	char *beg;

	switch( get_type() ){
	case FF_LABEL_DEF:
	case FF_LABEL_REF:
	case FF_STRING:
		beg = pos;
		while( (isspace(*pos)==0) && (*pos!=',') && (*pos!=10) && (*pos!=13) ){
			s[len] = *pos;
			pos++;
			if( len<72 ){
				len++;
			}
		}
		s[len] = 0;
		break;

	case FF_BYTE:
		get_byte_low( false );
		get_byte();
		get_byte();
		get_byte();
		strcpy( s, "NULL" );
		break;

	case FF_UNKNOWN:
	default:
		break;
	}
	return s;
}


void FrontierFile::push(){
	stack[stack_pointer] = pos;
    stack_pointer++;
    if( stack_pointer>31 ) throw( Exception("Stack overflow") );
}


void FrontierFile::pop(){
    stack_pointer--;
    if( stack_pointer<0 ) throw( Exception("Stack underflow") );
    pos = stack[stack_pointer];
}

