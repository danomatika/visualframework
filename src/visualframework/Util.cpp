/*==============================================================================

	Util.cpp

	visualframework: a simple 2d graphics framework
  
	Copyright (C) 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include "Util.h"

namespace visual {

bool Util::bUsingDataPath = true;
std::string Util::dataPath = "../../data/";

//
//	data path code from OpenFrameworks: http://openframeworks.cc
//
std::string Util::toDataPath(std::string path, bool absolute)
{
	if(bUsingDataPath)
	{
		// check if absolute path has been passed or if data path has already been applied
		if(path.length() == 0 || (path.substr(0,1) != "/" && path.substr(1,1) != ":" &&
		   path.substr(0, dataPath.length()) != dataPath))
		{
			path = dataPath+path;
		}

		if(absolute && (path.length()==0 || path.substr(0,1) != "/"))
		{
			#ifndef _MSC_VER
				char currDir[1024];
				path = "/"+path;
				path = getcwd(currDir, 1024)+path;
			#else // LINUX, MAC
				char currDir[1024];
				path = "\\"+path;
				path = getcwd(currDir, 1024)+path;
				std::replace(path.begin(), path.end(), '/', '\\' ); // fix any unixy paths...
			#endif
		}
	}
	return path;	
}

void Util::setDataPath(const std::string& path)
{
	dataPath = path;
}

std::string Util::getDataPath()
{
	return dataPath;
}

} // namespace
