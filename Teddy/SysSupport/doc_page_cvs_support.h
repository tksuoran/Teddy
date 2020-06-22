
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


/*********************************************************************************/
/*! \page page_cvs_support Support information for CVS

CVS is concurrent version control system. It maintains file
consistency when multiple users are working on the project
at same time. It even enables to users to modify same files
at the same time. <em>It is essential that everyone uses CVS when
working with %Teddy</em>.

When you use CVS, everyone has his or her own <em>working copy</em>
of all files. Additionally there is a single <em>repository</em>,
which maintains official version of files. The repository is maintained
and located in Sourceforge. There are few important basic operations that
you need.

Two most important operations are <em>update</em> and <em>commit</em>.
Commit command compares your files to the reposity and sends the
changes you have made to the repository. Update commands gets the
latest versions of files from the reposity to your working copy.
The changes that others have committed are now in your working
copy.

You may wonder: If I make some changes and use update, will I
lose my changes? No. Good. Wait. What if someone else has also
changed the file, and committed changes before I have? Still
no problems; when you make commit, CVS may tries to merge your
changes. Sometimes it is not sure how this should be done, and
you may have to manually decide what to do; CVS commit will abort
and ask you to solve the conflict. Just open the file and edit it
so that it will build again. You will notice that CVS has included
both versions of parts that you both have changed.

You will have to manually <em>add</em> each new files to the CVS.
Same applies to <em>remove</em>. Note that CVS interpretes files
as text by default, and expects that it can make some changes to
the file. This means that binary files are effectively corrupted
by CVS unless you explicitly tell CVS that it should leavy this
file exactly as it is given. To do this, add files using -kb
options.

It would be a good convention to <em>always update before commit</em>,
and never do commit until you are sure that it builds without
any errors - at least on your favorite platform.

\section section_practical_use Practical use

Instructions how to check out your working copy are on separate
page \ref page_getting.

Once you have made some modifications and you thing it would be
time to commit your changes, do the following:

<em>Notice:</em> On Finnish/Swedish keyboard layout, the `-key is
on the left side of backspace-key.

<ul>
 <li>Clean up everything by make clean

 <li>Retry building everything. Fix any problems.

 <li>Clean up again by make clean

 <li>cd to the directory
 <li>cvs -n update >../log 2>../log2<br>
 This will compare your working copy with the CVS repository and write
 difference reports. It will not actually change any files in anywhere.

 <li>Examine ../log and ../log2
 <ul>
  <li>If there are any files marked with U,<br>
  you have deleted that file from your working copy on purpose or
  by accident - or that is a new file in the CVS added by someone else.
  Make a list of those files which you know you have deleted on purpose
  and save it as ../rmlist. Then execute the command
  <ul>
   <li>cvs remove -f `cat ../rmlist`
  </ul>
  This will mark old files to be removed from the CVS reposity.

  <li>If there are any files marked with ?,<br>
  you have created a new file which neeeds to be added to CVS - or
  you have not cleaned up all files (or the distclean.sh scripts need
  updating..). First clean up by removing those files you know which
  are result of building. Then make a list of those files you have
  added on purpose. Usually you can use a single list when you work
  only with source files, but binary files must be added separately.
  Thus, if you have any binary files, put them to another liest.
  Save new text-only files list to ../addlist and new binary files
  list to ../addkblist. Then execute the command
  <ul>
   <li>cvs add `cat ../addlist`
   <li>cvs add -kb `cat ../addkblist`
  </ul>
  If you do not have either of the list, do not exacuta that command.
  These will mark new files to be added to the CVS repository.

 </ul>

 <li>Again do cvs -n update >../log 2>../log2 and examine the logs.
 If there are no longer ? and U marked files, you can proceed, otherwise
 you must repeat the previous step.

 <li>cvs update<br>
 This will indeed bring any new files from the CVS repository to
 your working copy.

 <li>Optional: retry building and redo above steps

 <li>cvs commit -m "a brief description what you did to the sources"<br>
 This will indeed upload your working copy to the CVS repository. That is,
 if you had no problems. If you get a list of merge conflicts, open those
 files to editor, examine, and make up a new version which compiles and
 builds. Once all conflicts are solved, cleanup and retry the commit command.

 <li>Once the commit is passed, do<br>
 cvs update<br>
 To make sure your working copy are actually in sync. If you get reports
 of ? or U files, step back to resolve them.
</ul>

Congratulations, the CVS is now up to date with your working copy :)

 *********************************************************************************/


