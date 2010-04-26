--[[ A solution contains projects, and defines the available configurations

http://industriousone.com/premake/user-guide

example: http://opende.svn.sourceforge.net/viewvc/opende/trunk/build/premake4.lua?revision=1708&view=markup

http://bitbucket.org/anders/lightweight/src/tip/premake4.lua

]]
solution "visualframework"
	configurations { "Debug", "Release" }
	objdir "../obj"
 
-- convenience library
project "visualframework"
	kind "StaticLib"
	language "C++"
	targetdir "../lib"
	files { "../src/visualframework/**.h", "../src/visualframework/**.cpp", "../src/visualframework/**.c" }
	
	includedirs { "../src", "../src/visualframework" }
	libdirs {  }
	
	configuration "linux"
		buildoptions { "`pkg-config --cflags sdl`",
					   "`pkg-config --cflags SDL_gfx`",
					   "`pkg-config --cflags SDL_image`" }
		linkoptions { "`pkg-config --libs sdl`",
					  "`pkg-config --libs SDL_gfx`",
					  "`pkg-config --cflags SDL_image`" }
	
	configuration "macosx"
		-- get rid of visibilty warnings
		buildoptions { "-fvisibility-inlines-hidden" }
		-- MacPorts
		includedirs { "/opt/local/include" }
		libdirs { "/opt/local/lib" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" } 

-- visual test
project "vftest"
	kind "ConsoleApp"
	language "C++"
	targetdir "../bin"
	files { "../src/test/**.h", "../src/test/**.cpp" }
	
	includedirs { "../src", "../src/visualframework" }

	libdirs { }
	links { "visualframework" }

	configuration "linux"
		buildoptions { "`pkg-config --cflags sdl`",
					   "`pkg-config --cflags SDL_gfx`",
					   "`pkg-config --cflags SDL_image`" }
		linkoptions { "`pkg-config --libs sdl`",
					  "`pkg-config --libs SDL_gfx`",
					  "`pkg-config --cflags SDL_image`" }

	configuration "macosx"
		-- MacPorts
		includedirs { "/opt/local/include"}
		libdirs { "/opt/local/lib" }
		links { "lo", "pthread", "SDLmain", "SDL", "SDL_gfx", "SDL_image", "SDL_ttf", "SDL_net" }
		linkoptions { "-Wl,-framework,Cocoa", "-Wl,-framework,OpenGL",
					  "-Wl,-framework,ApplicationServices",
					  "-Wl,-framework,Carbon", "-Wl,-framework,AudioToolbox",
					  "-Wl,-framework,AudioUnit", "-Wl,-framework,IOKit" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
		
