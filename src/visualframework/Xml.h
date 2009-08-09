/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_XML_H
#define VISUAL_XML_H

#include <string>

#include "Common.h"

#define TIXML_USE_STL
#include <tinyxml/tinyxml.h>

namespace visual {

/**
    \class  Xml
    \brief  convenience wrapper for some of the TinyXml functions
**/
class Xml
{
    public:

        /** \name Reading Member Functions **/

        // returns root element if file loaded, NULL if error
        static TiXmlElement* loadFile(TiXmlDocument* xmlDoc, std::string filename);

        /// attribute access by type, returns true if value found & set, false if not
        static bool getAttrString(const TiXmlElement* xmlPtr, std::string name, std::string& s);    // converts numbers to text
        static bool getAttrInt(const TiXmlElement* xmlPtr, std::string name, int* i);
        static bool getAttrDouble(const TiXmlElement* xmlPtr, std::string name, double* d);
        static bool getAttrFloat(const TiXmlElement* xmlPtr, std::string name, float* f);
        static bool getAttrBool(const TiXmlElement* xmlPtr, std::string name, bool* b);

        // return element as string
        static std::string element2String(const TiXmlElement* xmlPtr);

        /** \name Writing Member Functions **/

        // returns true if file was saved, false if error
        //static bool saveFile();

        /** \name Utility Member Functions **/

        // returns the current error as a string
        static std::string getErrorString(const TiXmlDocument xmlDoc);
};

} // namespace

#endif // VISUAL_XML_H
