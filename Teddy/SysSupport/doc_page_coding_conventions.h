
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

	$Id: doc_page_coding_conventions.h,v 1.1 2002/01/16 13:31:22 tksuoran Exp $
*/


/*********************************************************************************/
/*! \page page_coding_conventions Teddy coding conventions

I would very much like that you would use real tabs for
indentation. And never use tabs for anything else.
It does not matter what value for tabs you use.
Linux kernel coding conventions have not yet figured
it out, but it is possible to write sourcecode which
looks perfectly good with variable tab settings. The way
to do it is to:

<ul>
<li>use tabs for indentation
<li>use tabs <em>only</em> for indentation
<li>don't use tabs to align something that needs spaces to align
</ul>

For other things (naming, layout..), you have two options.
Use consistently your own conventions; this is fine - or
look at my source code. It is not good example at some places,
but looking around here and there you should get the idea.
One thing is that I hate is prefixing class names with C,
but I can live with that if you really have to do it.

I would like to have one class per .h / .cpp file.
Large classes can be divided into several .cpp files.

 *********************************************************************************/


