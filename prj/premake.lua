--[[
	
	Dan Wilcox <danomatika@gmail.com>

--]]

project.name 		= "visualframework"
project.bindir	 	= "../bin"
project.libdir 		= "../lib"

project.configs		= { "Debug", "Release" }

---------------------------------------------------------
--- build the externals
---------------------------------------------------------
package = newpackage()
package.name 		= "externals"
package.kind 		= "lib"
package.language 	= "c++"

package.postbuildcommands = {
	"cd ../externals/oscpack/prj && make",
    "cd ../externals/tinyxml/prj && make"
}

---------------------------------------------------------
--- build the visual framework lib
---------------------------------------------------------
package = newpackage()
package.name 		= "visualframework"
package.kind 		= "lib"
package.language 	= "c++"

package.files = { 
    matchfiles( "../src/*.h", "../src/*.cpp" ),
	matchfiles( "../src/visualframework/*.h", "../src/visualframework/*.cpp" )
}

package.includepaths = {
	"../src",
	"../src/classes",
    "/usr/include",
	"../externals",	
	"../externals/include"
}

package.libpaths = {
	"../lib",
	"../externals/lib",
    "/usr/lib"
}

package.config["Debug"].objdir   = "../obj/visualframework/Debug"
package.config["Release"].objdir = "../obj/visualframework/Release"

package.config["Debug"].target   = "visualframeworkD"
package.config["Release"].target = "visualframework"

package.defines                   = { "LINUX" };
package.config["Debug"].defines   = { "DEBUG", "_DEBUG" };
package.config["Release"].defines = { "NDEBUG" };

package.buildflags                   = { "extra-warnings" }
package.buildoptions                 = { "-Wno-unknown-pragmas" }
package.config["Debug"].buildoptions = { "-ggdb" }


package.links = { "SDL", "SDL_gfx", "SDL_net" }
package.config["Debug"].links = { "tinyxmlD", "oscpackD" }
package.config["Release"].links = { "tinyxml", "oscpack" }

---------------------------------------------------------
--- build some tests
---------------------------------------------------------
package = newpackage()
package.name 		= "vftests"
package.kind 		= "exe"
package.language 	= "c++"

package.files = { 
	matchfiles( "../src/tests/*.h", "../src/tests/*.cpp" )
}

package.includepaths = {
	"../src",
    "/usr/include",
	"../externals",	
	"../externals/include"
}

package.libpaths = {
	"../lib",
	"../externals/lib",
    "/usr/lib"
}

package.config["Debug"].objdir   = "../obj/vftests/Debug"
package.config["Release"].objdir = "../obj/vftests/Release"

package.config["Debug"].target   = "vftestsD"
package.config["Release"].target = "vftests"

package.defines                   = { "LINUX" };
package.config["Debug"].defines   = { "DEBUG", "_DEBUG" };
package.config["Release"].defines = { "NDEBUG" };

package.buildflags                   = { "extra-warnings" }
package.buildoptions                 = { "-Wno-unknown-pragmas" }
package.config["Debug"].buildoptions = { "-ggdb" }


package.links = { "SDL", "SDL_gfx", "SDL_net" }
package.config["Debug"].links = { "visualframeworkD", "tinyxmlD", "oscpackD" }
package.config["Release"].links = { "visualframework", "tinyxml", "oscpack" }

