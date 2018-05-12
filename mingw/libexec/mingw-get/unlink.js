/*
 * unlink.js
 *
 * $Id: unlink.js,v cd9a9ac85727 2013/09/20 08:43:04 keithmarshall $
 *
 * Invoke the Windows Scripting Host to remove specified files, typically
 * from the user's or all users' start menu or desktop directories.
 *
 * Usage:
 *   cscript -nologo unlink.js [--option ...] file ...
 *
 * Options:
 *   --all-users
 *		references to desktop or start menu files apply
 *		to the directories serving all users
 *
 *   --desktop	remove files from the user's desktop directory, (or
 *		from all users' desktop directory, with --all-users)
 *
 *   --start-menu
 *		remove files from the user's start menu directory, (or
 *		from all users' start menu directory, with --all-users)
 *
 *   --if-linked=target_path
 *		do not remove any matched file which is not a shortcut
 *		(.lnk or .url) referring to the specified target path;
 *		when this option is specified, any specified file name
 *		which does not already have a .lnk or .url extension
 *		will have .lnk appended, before seeking any match
 *
 *   --force	override read-only attributes when removing files.
 *
 * Parameters:
 *   file	the path name for a file to be removed; if --desktop
 *		or --start-menu is specified, it should be a relative
 *		path name, which will then be resolved relative to the
 *		appropriate system directory path.
 *
 *
 * This file is a component of mingw-get.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2012, 2013, MinGW.org Project
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
var cmdName = WScript.ScriptName;
var FileSystem = WScript.CreateObject("Scripting.FileSystemObject");
var WinShell = WScript.CreateObject("WScript.Shell");

/* Strip ".js" suffix from command name.
 */
var i = cmdName.lastIndexOf( ".js" );
if( (i > 0) &&  (cmdName.substr( i ) == ".js") )
  cmdName = cmdName.substr( 0, i );

/* Specify the keywords which identify command line options.
 */
var options = Array(
    /*
     *  Option		    Effect
     *  -------------	    -------------------------
     */
	"all-users",	 /* Resolve file path names in all-users domain... */
	"start-menu",	 /* ...relative to user's or all-users' start menu... */
	"desktop",	 /* ...or desktop directories. */
	"if-linked",     /* Only delete shortcuts with specified target path */
	"force"  	 /* Forcibly override read-only attribute */
    );

/* Initialise all options as "unassigned".
 */
var unassigned = "+++unassigned+++";
var assigned = Array( options.length );
for( i = 0; i < assigned.length; i++ )
  assigned[i] = unassigned;

/* The "complain" function provides a mechanism for writing
 * diagnostic messages to stderr, and optionally aborting the
 * calling script.
 */
function complain( condition, message )
{
  WScript.StdErr.WriteLine( cmdName + ": " + message );
  if( condition < 0 )
    WScript.Quit( -condition );
  return condition;
}

/* Parse the command line, to identify any specified options.
 */
var chklink = "";
var argv = WScript.Arguments;
for( i = 0; i < argv.length; i++ )
{
  if( argv( i ).indexOf( "--" ) == 0 )
  {
    /* Handle arguments specifying options...
     */
    var optind;
    var matched = 0;
    var optname = argv( i ).substr( 2 );
    var optarg = "";
    for( var k = 0; k < options.length; k++ )
    {
      /* Try to match each defined option in turn...
       */
      var argind = optname.indexOf( "=" );
      if( argind > 0 )
      {
	optarg = optname.substr( argind + 1 );
	optname = optname.substr( 0, argind );
      }

      if( optname == options[k] )
      {
	/* A exact (complete) match trumps any possible abbreviation...
	 */
	matched = 1;
	assigned[optind = k] = optname;
	k = options.length;
      }

      else if( options[k].indexOf( optname ) == 0 )
      {
	/* Otherwise abbreviations are allowed, but must uniquely
	 * identify only one defined option name...
	 */
	if( matched++ > 0 )
	  complain( -2, "option '" + argv( i ) + "' is ambiguous" );
	assigned[optind = k] = options[k];
      }
    }
    if( matched == 0 )
      /*
       * Bail out, if no match identified.
       */
      complain( -2, "option '" + argv( i ) + "' is undefined" );

    if( assigned[optind] == "if-linked" )
      chklink = optarg;
  }
}

/* Establish prefix for resolving paths relative to desktop
 * or start menu directories, and handle the --force option.
 */
var prefix = "";
var allusers = false;
var force = false;
for( i = 0; i < options.length; i++ )
{
  switch( assigned[i] )
  {
    case "force":
      force = true;
      break;

    case "all-users":
      allusers = true;
      break;

    case "start-menu":
      prefix = WinShell.SpecialFolders( allusers ? "AllUsersStartMenu"
	  : "StartMenu"
	) + "\\";
      break;

    case "desktop":
      if( prefix != "" )
	complain( -2, "options '--start-menu' and '--desktop' are incompatible" );
      prefix = WinShell.SpecialFolders( allusers ? "AllUsersDesktop"
	  : "Desktop"
	) + "\\";
  }
}

/* Parse the command line again, to process path name arguments,
 * and delete the specified files.
 */
for( i = 0; i < argv.length; i++ )
{
  if( argv( i ).indexOf( "--" ) != 0 )
  {
    /* Not an option argument, so assume it's a path name.
     */
    var filename = prefix + argv( i );
    if( chklink != "" )
    {
      /* The "--if-linked" option is in effect, and a viable
       * target path has been defined.  The file to be deleted
       * MUST be a shortcut file, (i.e. it MUST bear a ".lnk" or
       * ".url" extension); supply ".lnk" as default, if this is
       * not so.
       */
      var l = filename.length - 4;
      var suffix = (l > 0) ? filename.substr( l ) : 0;
      if( (suffix != ".lnk") && (suffix != ".url") )
	filename += ".lnk";
    }
    if( FileSystem.FileExists( filename ) )
    {
      /* The requisite file DOES exist...
       */
      if( chklink != "" )
      {
	/* ...but when "--if-linked is in effect, we must verify that
	 * the link target is matched (case-insensitively), before...
	 */
	var ref = WinShell.CreateShortcut( filename );
	var chk = WinShell.CreateShortcut( filename ); chk.TargetPath = chklink;
	if( ref.TargetPath.toLowerCase() == chk.TargetPath.toLowerCase() )
	  /*
	   * ...we may proceed with deletion.
	   */
	  FileSystem.DeleteFile( filename, force );
      }
      else
	/* When "--if-linked" is NOT in effect, we may simply
	 * proceed with deletion, without further ado.
	 */
	FileSystem.DeleteFile( filename, force );
    }
  }
}

/* $RCSfile: unlink.js,v $: end of file */
