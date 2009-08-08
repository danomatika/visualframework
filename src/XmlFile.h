/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef XMLFILE_H
#define XMLFILE_H

#include <string>

#include "Common.h"

#define TIXML_USE_STL
#include "tinyxml.h"

class XmlFile
{
    public:

        XmlFile();

        virtual ~XmlFile();

        /** \name Reading Member Functions **/

        // returns true if file loaded, false if error
        bool loadFile(std::string filename);

        // returns doc root name, empty string "" if doc not loaded
        std::string getDocRootName();

        // tree traversal, returns true if traversal successful, false if not
        bool gotoNextElement();
        bool gotoPrevElement();
        bool gotoChildElement(); // go to first child
        bool gotoParentElement(); // go to parent

        // element access
        std::string getElementName();
        std::string getElementText();

        /// attribute access by type, returns true if value found & set, false if not
        bool getAttrString(std::string name, std::string &s);   // converts numbers to text
        bool getAttrInt(std::string name, int* i);
        bool getAttrDouble(std::string name, double* d);
        bool getAttrFloat(std::string name, float* f);

        // return element as string
        std::string printElement();

        /** \name Writing Member Functions **/

        // returns true if file was saved, false if error
        //bool saveFile();

        /** \name Utility Member Functions **/

        // returns the current error as a string
        std::string getErrorString();

        // if the error was handled, clear it
        void clearError() {_xmlDoc->ClearError();}

    protected:

    private:

        // have to use a pointer and new/delete with the TiXmlDocument
        // because, for some reason, there are double free & mem corruption problems
        TiXmlDocument*      _xmlDoc;
        TiXmlElement*       _xmlPtr;    // if NULL, doc is not valid
};

#endif // XMLFILE_H
