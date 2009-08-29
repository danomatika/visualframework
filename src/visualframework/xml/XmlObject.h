/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef EQF_XML_OBJECT_H
#define EQF_XML_OBJECT_H

#include "Log.h"

#include <vector>

#include <tinyxml.h>

namespace visual {

enum XmlType
{
    XML_TYPE_UNDEF = 0,
    XML_TYPE_BOOL,
    XML_TYPE_INT,
    XML_TYPE_UINT,
    XML_TYPE_FLOAT,
    XML_TYPE_DOUBLE,
    XML_TYPE_STRING
};

class XmlObject
{
    public:

        XmlObject(std::string elementName);
        virtual ~XmlObject();

        /* ***** LOAD ***** */

        /// load from an xml element, checks if the element name is correct
        bool loadXml(TiXmlElement* e);

        /// load from an xml file
        bool loadXmlFile(std::string filename);

        /* ***** SAVE ***** */

        /// save to an xml element, checks if the element name is correct
        bool saveXml(TiXmlElement* e);

        /// save to a new xml file
        bool saveXmlFile(std::string filename="");

        /// close the current file (does not save, call load to open again)
        void closeXmlFile();

        /* ***** ADD OTHER OBJECTS ***** */

        /// attach/remove an XMlObject to this one
        void addXmlObject(XmlObject* object);
        void removeXmlObject(XmlObject* object);

        /* ***** ELEMENTS ***** */

        /// add/remove an element, element names are singular
        bool addXmlElement(std::string name, std::string* text=NULL, bool readOnly=false);
        bool removeXmlElement(std::string name);   /// also removes attached attributes
        void removeAllXmlElements();   /// alsa removes attached attributes

        /* ***** ATTRIBUTES ***** */

        /// add/remove an attribute, element names are singular
        /// if element does not exist, it will be created
        /// if it exists, attribute will be atatched to it
        bool addXmlAttribute(std::string name, std::string elementName, XmlType type, void* var, bool readOnly=false);
        bool removeXmlAttribute(std::string name, std::string elementName);

        /* ***** UTIL ***** */

        /// get/set the filename
        inline std::string getXmlFilename() {return _filename;}
        inline void setXmlFilename(std::string name) {_filename = name;}

        /// get/set this objects xml element name
        inline std::string getXmlName() {return _elementName;}
        inline void setXmlName(std::string name) {_elementName = name;}

        /// get the root element (for direct access)
        TiXmlElement* getXmlRootElement();

    protected:

        /* ***** USER CALLBACKS ***** */
        /// derive these callbacks for direct access to loading/saving
        /// these are called after attached elements, then objects are processed

        /// callback to process xml children when loaded, returns true if element handled
        /// param   e   root element of this object aka <getXmlName()> ...
        virtual bool readXml(TiXmlElement* e) {return false;}

        /// callback to save to xml when saved, returns true if successful
        /// param   e   root element of this object aka <getXmlName()> ...
        virtual bool writeXml(TiXmlElement* e) {return false;}

    private:

        struct Attribute
        {
            Attribute() : type(XML_TYPE_UNDEF) {}

            std::string name;
            XmlType type;
            void* var;
            bool bReadOnly;
        };

        struct Element
        {
            std::string name;
            std::string* text;
            bool bReadOnly;
            std::vector<Attribute*> attributeList;
        };

        // find an element in the list by its name, returns NULL if not found
        Element* findElement(std::string name)
        {
            std::vector<Element*>::iterator iter;
            for(iter = _elementList.begin(); iter != _elementList.end(); ++iter)
            {
                if((*iter)->name == name)
                {
                    return (*iter);
                }
            }

            return NULL;
        }

        bool _bDocLoaded;       /// is this doc loaded?
//        bool _bLoaded;          /// is this object loaded?
        std::string _filename;  /// current filename
        TiXmlDocument* _xmlDoc; /// the xml document

        std::string _elementName;   /// name of the root element
        std::vector<Element*> _elementList;     /// attached elements/attributes
        std::vector<XmlObject*> _objectList;    /// attached xml objects to process
};

} // namespace

#endif // EQF_XML_OBJECT_H
