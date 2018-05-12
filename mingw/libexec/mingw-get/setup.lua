--
-- setup.lua
--
-- $Id: setup.lua,v 49e57abe7f83 2013/09/21 08:35:52 keithmarshall $
--
-- Lua 5.2 module providing common setup hooks for mingw-get.
--
--
-- This file is a component of mingw-get.
--
-- Written by Keith Marshall <keithmarshall@users.sourceforge.net>
-- Copyright (C) 2012, 2013, MinGW.org Project
--
--
-- Permission is hereby granted, free of charge, to any person obtaining a
-- copy of this software and associated documentation files (the "Software"),
-- to deal in the Software without restriction, including without limitation
-- the rights to use, copy, modify, merge, publish, distribute, sublicense,
-- and/or sell copies of the Software, and to permit persons to whom the
-- Software is furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included
-- in all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
-- OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
-- THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
-- FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
-- DEALINGS IN THE SOFTWARE.
--
   local M = {}
   local wsh = require "wsh"
--
   function M.libexec_path( script, subsystem )
     if not subsystem
     then
       subsystem = "mingw-get"
     end
     return wsh.libexec_path( script, subsystem )
   end
--
   function M.argwrap( arglist, ... )
     for argind, argval in ipairs {...}
     do
       arglist = arglist .. " " .. argval
     end
     return arglist
   end
--
   function M.shlink( args, ... )
     if args
     then
       wsh.execute( M.argwrap( M.libexec_path( "shlink.js" ), args, ... ) )
     end
   end
--
   function M.unlink( args, ... )
     if args
     then
       wsh.execute( M.argwrap( M.libexec_path( "unlink.js" ), args, ... ) )
     end
   end
--
   function M.create_shortcuts( ... )
     M.shlink( os.getenv( "MINGW_GET_DESKTOP_HOOK" ), ... )
     M.shlink( os.getenv( "MINGW_GET_START_MENU_HOOK" ), ... )
   end
--
   function M.delete_shortcuts( ... )
     M.unlink( "--desktop", ... )
     M.unlink( "--all-users --desktop", ... )
     M.unlink( "--all-users --start-menu", ... )
     M.unlink( "--start-menu", ... )
   end
--
   return M
--
-- $RCSfile: setup.lua,v $: end of file */
