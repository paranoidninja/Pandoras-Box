/*
 * shlink.js
 *
 * $Id: shlink.js,v 0f864a5cad9e 2012/04/06 22:49:36 keithmarshall $
 *
 * Invoke the Windows Scripting Host to create or modify a windows shortcut,
 * with specified parameters.
 *
 * Usage:
 *   cscript -nologo shlink.js [--option[=value] ...] target name
 *
 * Options:
 *   --verbose	report shortcut parameter assignments on stdout
 *
 *   --all-users
 *   		create the shortcut in the start menu, or on the
 *   		desktop available to all users; (has no effect,
 *   		unless --start-menu or --desktop is specified)
 *
 *   --desktop	create the shortcut on the desktop of the current
 *   		user, (or for all users, with --all-users)
 *
 *   --start-menu
 *   		create the shortcut in the user's start menu, (or
 *   		all users' start menu, with --all-users)
 *
 *   --arguments="argument list ..."
 *		specify arguments to be passed to the command
 *		invoked by the shortcut
 *
 *   --description="text ..."
 *		specify the "tool tip" for the shortcut
 *
 *   --hotkey="[SHIFT+][CTRL+][ALT+]key"
 *   		specify a hot-key combination which may be used
 *   		to invoke the shortcut command
 *
 *   --icon="d:\path\to\icon\file[,index]"
 *   		specify an icon to associate with the shortcut;
 *   		if unspecified, the first icon in the target file,
 *   		or failing that, a system default is used
 *
 *   --show=normal|maximised|minimised
 *   		specify the style of window in which the program
 *   		invoked by the shortcut will start running
 *
 *   --workingdir="d:\path\to\working\directory"
 *   		specify the absolute path name for the directory
 *   		which will become the current working directory when
 *   		the program invoked by the shortcut is started
 *
 * Parameters:
 *   target	the path name to the program to invoke, or the file
 *		to be opened, when the shortcut is activated.
 *
 *   name	the path name for the shortcut file itself; if this
 *		does not end with either a ".lnk" or ".url" extension,
 *		then ".lnk" will be appended, so creating a regular
 *		file system link type shortcut.
 *
 *
 * This file is a component of mingw-get.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2012, MinGW Project
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
var WinShell = WScript.CreateObject("WScript.Shell");

/* Properties for the shortcut may be specified as arguments
 * to command line options, each of which is represented in the
 * GNU long option form, by keywords with property associations
 * as specified by:
 */
var options = Array(
      "name",		/*  File name/path of .lnk file	*/
      "all-users",
      "start-menu",
      "desktop",
      "verbose",
  /* 
   *  Option		    Property
   *  -------------	    -------------------------
   */ 
      "arguments",	/*  Shortcut.Arguments		*/
      "description",	/*  Shortcut.Description	*/
      "hotkey",		/*  Shortcut.HotKey		*/
      "icon",		/*  Shortcut.IconLocation	*/
      "show",		/*  Shortcut.WindowStyle	*/
      "target",		/*  Shortcut.TargetPath		*/
      "workingdir"	/*  Shortcut.WorkingDirectory	*/
    );

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

/* Strip ".js" suffix from command name.
 */
var i = cmdName.lastIndexOf( ".js" );
if( (i > 0) &&  (cmdName.substr( i ) == ".js") )
  cmdName = cmdName.substr( 0, i );

/* Initialise all options to "unassigned" state.
 */
var target = -1;
var lnkname = -1;
var desktop = -1;
var allusers = -1;
var startmenu = -1;
var verbosity = -1;
var unassigned = "+++unassigned+++";
var assigned = Array( options.length );
for( var k = 0; k < assigned.length; k++ )
{
  switch( options[k] )
  {
    case "name":
      lnkname = k;
      break;

    case "desktop":
      desktop = k;
      break;

    case "start-menu":
      startmenu = k;
      break;

    case "all-users":
      allusers = k;
      break;

    case "target":
      target = k;
      break;

    case "verbose":
      verbosity = k;
  }
  assigned[k] = unassigned;
}

/* Define the prefix, which will qualify the location
 * of the shortcut; initialise it to nothing, so that by
 * default shortcuts will be located by absolute path name,
 * as specified, or relative to current working directory.
 */
var prefix = "";

var j;
function assign_option( name, value )
{
  switch( name )
  {
    case "desktop":
    case "start-menu":
    case "all-users":
    case "verbose":
      j = i;
      return "set";
  }
  return value;
}

/* Parse the command line.
 */
var argv = WScript.Arguments;
for( i = 0; i < argv.length; i++ )
{
  if( argv( i ).indexOf( "--" ) == 0 )
  {
    /* Handle arguments specifying options...
     */
    if( (optind = argv( j = i ).indexOf( "=" ) + 1) > 3 )
    {
      optnam = argv( j ).substr( 2, optind - 3 );
      optarg = argv( j ).substr( optind );
    }
    else
    {
      optnam = argv( j ).substr( 2 );
      if( ++j < argv.length )
	optarg = argv( j );
      else
	optarg = unassigned;
    }

    var matched = 0;
    for( var k = 0; k < options.length; k++ )
    {
      if( optnam == options[k] )
      {
	matched = 1;
	assigned[k] = assign_option( options[k], optarg );
	k = options.length;
      }
      else if( options[k].indexOf(optnam) == 0 )
      {
	if( ++matched > 1 )
	  complain( -2, cmdName + "option '" + argv( i ) + "' is ambiguous" );
	assigned[k] = assign_option( options[k], optarg );
      }
    }
    if( matched == 1 )
    {
      i = j;
    }
    else
      complain( -2, "option '" + argv( i ) + "' is not supported" );
  }

  /* Handle non-option arguments...
   */
  else if( (target >= 0) && (assigned[target] == unassigned) )
    /*
     * ...the first of which is the target to which the
     * (shortcut) link is to refer...
     */
    assigned[target] = argv( i );

  else if( (lnkname >= 0) && (assigned[lnkname] == unassigned) )
    /*
     * ...the second is the file system path name at which
     * the link file itself is to be saved...
     */
    assigned[lnkname] = argv( i );

  else
    /* ...and any more than two is an error.
     */
    complain( -2, "too many arguments" );
}

/* Verify that mandatory arguments have been specified...
 */
if( assigned[target] == unassigned )
  /*
   * First of these, the TargetPath specification, is required;
   * diagnose and abort, if missing.
   */
  complain( -2, "missing argument: no target path specified" );

if( assigned[lnkname] == unassigned )
  /*
   * Second, the path name for the link file itself is essential;
   * again, diagnose and abort if missing.
   */
  complain( -2, "missing argument: no shortcut name specified" );

/* We have both the mandatory arguments; check that the link name
 * is properly terminated by a ".lnk" or ".url" suffix...
 */
var suffix = "";
if( (i = assigned[lnkname].length - 4) > 0 )
  suffix = assigned[lnkname].substr( i );

/* ...and append ".lnk" as default, if not already present.
 */
if( (suffix != ".lnk") && (suffix != ".url") )
  assigned[lnkname] += ".lnk";

/* Add the appropriate prefix for '--desktop' or '--start-menu' shortcuts.
 */
if( assigned[desktop] != unassigned )
{
  if( assigned[startmenu] != unassigned )
    complain( -2, "options '--desktop' and '--start-menu' are incompatible" );
  else prefix = WinShell.SpecialFolders( (assigned[allusers] == unassigned)
      ? "Desktop" : "AllUsersDesktop" ) + "\\";
}
else if( assigned[startmenu] != unassigned )
  prefix = WinShell.SpecialFolders( (assigned[allusers] == unassigned)
      ? "StartMenu" : "AllUsersStartMenu" ) + "\\";

else if( assigned[allusers] != unassigned )
  complain( -2,
      "option '--all-users' also requires '--desktop' or '--start-menu'"
    );

/* Handle verbosity...
 */
function verbose_assignment( property, value )
{
  if( assigned[verbosity] == "set" )
    WScript.Echo( cmdName + ": set " + property + " = " + value );
}

/* Initialise the shortcut entity reference.
 */
if( assigned[verbosity] == "set" )
  WScript.Echo( cmdName + ": create shortcut: " + prefix + assigned[lnkname] );

var Shortcut = WinShell.CreateShortcut( prefix + assigned[lnkname] );

for( var k = 0; k < options.length; k++ )
{
  if( assigned[k] != unassigned )
    switch( options[k] )
    {
      case "arguments":
	verbose_assignment( "Shortcut.Arguments", assigned[k] );
	Shortcut.Arguments = assigned[k];
	break;

      case "description":
	verbose_assignment( "Shortcut.Description", assigned[k] );
	Shortcut.Description = assigned[k];
	break;

      case "hotkey":
	verbose_assignment( "Shortcut.HotKey", assigned[k] );
	Shortcut.HotKey = assigned[k];
	break;

      case "icon":
	verbose_assignment( "Shortcut.IconLocation", assigned[k] );
	Shortcut.IconLocation = assigned[k];
	break;

      case "show":
	verbose_assignment( "Shortcut.WindowStyle", assigned[k] );
        var style = Array(
	    "normal",     1,
	    "maximised",  3,
	    "maximized",  3,
	    "minimised",  7,
	    "minimized",  7
	  );
	for( j = 0; j < style.length; j++ )
	  if( style[j++].indexOf( assigned[k] ) == 0 )
	  {
	    Shortcut.WindowStyle = style[j];
	    j = 100;
	  }
	if( j < 100 )
	  complain( 1, "unrecognised mode '--show=" + assigned[k] + "' ignored" );
	break;

      case "target":
	verbose_assignment( "Shortcut.TargetPath", assigned[k] );
	Shortcut.TargetPath = assigned[k];
	break;

      case "workingdir":
	verbose_assignment( "Shortcut.WorkingDirectory", assigned[k] );
	Shortcut.WorkingDirectory = assigned[k];
    }
  else if( assigned[verbosity] == "set" )
    WScript.Echo( cmdName + ": option '--" + options[k] + "' is unassigned" );
}

/* Commit the shortcut entity to disk.
 */
Shortcut.Save();

/* $RCSfile: shlink.js,v $: end of file */
