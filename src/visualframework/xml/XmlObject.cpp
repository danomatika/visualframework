/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#include "XmlObject.h"

#include <map>

#include "Xml.h"

namespace visual {

XmlObject::XmlObject(std::string elementName) :
    _bDocLoaded(false), _elementName(elementName) {}

XmlObject::~XmlObject()
{
    removeAllXmlElements();
    closeXmlFile();
}

bool XmlObject::loadXml(TiXmlElement* e)
{
    if(e == NULL)
    {
        return false;
    }

    // check if the element is correct
    if(e->ValueStr() != _elementName)
    {
        LOG_WARN << "Xml \"" << _elementName << "\": xml element value is not \"" << _elementName << "\"" << std::endl;
        return false;
    }

    TiXmlHandle h(e);
    TiXmlElement* child;

    // load attached elements
    for(unsigned int i = 0; i < _elementList.size(); ++i)
    {
        Element* elem = _elementList.at(i);

        // try to find a child with the same element name
        child = h.FirstChildElement(elem->name).Element();
        if(child != NULL)
        {
            // load the elements text
            if(elem->text != NULL)
            {
                elem->text->clear();
                elem->text->append(Xml::getText(child));
            }

            // load the attached attributes
            for(unsigned int j = 0; j < elem->attributeList.size(); ++j)
            {
                Attribute* attr = elem->attributeList.at(j);

                Xml::getAttr(child, attr->name, attr->type, attr->var);
            }
        }
    }

    // to keep track of how many elements with the same name
    std::map<std::string, int> elementMap;

    // load attached objects
    for(unsigned int i = 0; i < _objectList.size(); ++i)
    {
        XmlObject* o = _objectList.at(i);

        // try to find element name in map
        std::map<std::string, int>::iterator iter = elementMap.find(o->getXmlName());
        if(iter == elementMap.end())
        {
            // not found, so add element name to map
            elementMap.insert(make_pair(o->getXmlName(), 0));
            iter = elementMap.find(o->getXmlName());
        }
        else
            iter->second++; // found another

        // try to find an element with same name as the object by index (if multiples)
        child = h.ChildElement(o->getXmlName(), iter->second).Element();
        if(child->ValueStr() == o->getXmlName())
        {
            o->loadXml(child);  // found element
        }
        else
        {
            // not found
        }
    }

    // process user callback
    return readXml(e);
}

bool XmlObject::loadXmlFile(std::string filename)
{
    // close if loaded
    if(_bDocLoaded)
        closeXmlFile();

    // try to load the file
    _xmlDoc = new TiXmlDocument;
    if(!_xmlDoc->LoadFile(filename.c_str(), TIXML_ENCODING_UTF8))
    {
        LOG_ERROR << "Xml \"" << _elementName << "\": could not load \""
                  << filename << "\"" << std::endl;
        closeXmlFile();
        return false;
    }

    // get the root element
    TiXmlElement* root = _xmlDoc->RootElement();

    // check if the root is correct
    if(root->ValueStr() != _elementName)
    {
        LOG_ERROR << "Xml \"" << _elementName << "\": xml file \"" << filename
                  << "\" does not have \"" << _elementName << "\" as the root element"
                  << std::endl;
        closeXmlFile();
        return false;
    }

    _bDocLoaded = true;

    // load everything
    return loadXml(root);
}

bool XmlObject::saveXml(TiXmlElement* e)
{
    if(e == NULL)
    {
        return false;
    }

    // check if the element is correct
    if(e->ValueStr() != _elementName)
    {
        LOG_WARN << "Xml \"" << _elementName << "\": xml element value is not \""
                 << _elementName << "\"" << std::endl;
        return false;
    }

    TiXmlHandle h(e);

    // save attached elements
    for(unsigned int i = 0; i < _elementList.size(); ++i)
    {
        Element* elem = _elementList.at(i);

        // find element, add if it dosen't exit
        TiXmlElement* child = Xml::obtainElement(e, elem->name);

        // set the element's text if any
        if(elem->text != NULL)
        {
            TiXmlText* text = new TiXmlText(*elem->text);
            child->LinkEndChild(text);
        }

        // save the element's attached attributes
        for(unsigned int j = 0; j < elem->attributeList.size(); ++j)
        {
            Attribute* attr = elem->attributeList.at(j);
            if(attr->bReadOnly)
                Xml::setAttr(child, attr->name, attr->type, attr->var);
        }
    }

    // save all attached objects
    bool ret = true;
    for(unsigned int i = 0; i < _objectList.size(); ++i)
    {
        XmlObject* o = _objectList.at(i);
        ret = ret || o->saveXml(Xml::obtainElement(e, o->getXmlName()));
    }

    // process user callback
    return ret || writeXml(e);
}

bool XmlObject::saveXmlFile(std::string filename)
{
     TiXmlElement* root;

    // setup new doc if not loaded
    if(!_bDocLoaded)
    {
        // new doc
        _xmlDoc = new TiXmlDocument;

        // add the declaration
        _xmlDoc->LinkEndChild(new TiXmlDeclaration("1.0", "", ""));

        // add root element
        root = new TiXmlElement(getXmlName());
        _xmlDoc->LinkEndChild(root);

        _bDocLoaded = true;
    }
    else    // already loaded
    {
        root = _xmlDoc->RootElement();
    }

    // use the current filename?
    if(filename == "")
    {
        filename = _filename;
    }

    // load data into the elements
    bool ret = saveXml(root);

    // try saving
    if(!_xmlDoc->SaveFile(filename))
    {
        LOG_ERROR << "Xml \"" << _elementName << "\": could not save: "
                  << Xml::getErrorString(_xmlDoc) << std::endl;
        ret = false;
    }

    return ret;
}

void XmlObject::closeXmlFile()
{
    if(_bDocLoaded)
        delete _xmlDoc;

    _bDocLoaded = false;
}

void XmlObject::addXmlObject(XmlObject* object)
{
    if(object == NULL)
    {
        LOG_ERROR << "Xml: Cannot add NULL object" << std::endl;
        return;
    }

    _objectList.push_back(object);
}

void XmlObject::removeXmlObject(XmlObject* object)
{
    if(object == NULL)
    {
        LOG_ERROR << "Xml: Cannot remove NULL object" << std::endl;
        return;
    }

    std::vector<XmlObject*>::iterator iter;
    iter = find(_objectList.begin(), _objectList.end(), object);
    if(iter != _objectList.end())
    {
        _objectList.erase(iter);
    }
}

bool XmlObject::addXmlElement(std::string name, std::string* text, bool readOnly)
{
    if(name == "")
    {
        LOG_ERROR << "Xml \"" << _elementName << "\": cannot add element \"" << name
                  << "\", name is empty" << std::endl;
        return false;
    }

    Element* element = new Element;
    element->name = name;
    element->text = text;
    element->bReadOnly = readOnly;
    _elementList.push_back(element);

    return true;
}

bool XmlObject::removeXmlElement(std::string name)
{
    std::vector<Element*>::iterator iter;
    for(iter = _elementList.begin(); iter != _elementList.end(); ++iter)
    {
        if((*iter)->name == name)
        {
            delete (*iter);
            _elementList.erase(iter);
            return true;
        }
    }

    LOG_WARN << "Xml \"" << _elementName << "\": cannot remove element \"" << name
                  << "\", not found" << std::endl;

    return false;
}

void XmlObject::removeAllXmlElements()
{
    for(unsigned int i = 0; i < _elementList.size(); ++i)
    {
        Element* e = _elementList.at(i);

        for(unsigned int j = 0; j < e->attributeList.size(); ++j)
        {
            Attribute* attr = e->attributeList.at(j);
            delete attr;
        }

        delete e;
    }
    _elementList.clear();
}

bool XmlObject::addXmlAttribute(std::string name, std::string elementName, XmlType type, void* var, bool readOnly)
{
    if(name == "" || elementName == "")
    {
        LOG_ERROR << "Xml \"" << _elementName << "\": cannot add attribute \"" << name
                  << "\" to element \"" << elementName << "\", name and/or element name are empty"
                  << std::endl;
        return false;
    }

    if(var == NULL)
    {
        LOG_ERROR << "Xml \"" << _elementName << "\": attribute \"" << name
                  << "\" variable is NULL" << std::endl;
        return false;
    }

    // check if the requested element exists, if not add it
    Element* e = findElement(elementName);
    if(e == NULL)    // dosent exist
    {
        addXmlElement(elementName);
        e = _elementList.back();
    }

    Attribute* attribute = new Attribute;
    attribute->name = name;
    attribute->type = type;
    attribute->var = var;
    attribute->bReadOnly = readOnly;

    e->attributeList.push_back(attribute);

    return true;
}

bool XmlObject::removeXmlAttribute(std::string name, std::string elementName)
{
    Element* e = findElement(elementName);
    if(e == NULL)
        return false;

    std::vector<Attribute*>::iterator iter;
    for(iter = e->attributeList.begin(); iter != e->attributeList.end(); ++iter)
    {
        delete (*iter);
        e->attributeList.erase(iter);
        return true;
    }

    LOG_WARN << "Xml \"" << _elementName << "\": cannot remove attribute \"" << name
             << "\", not found" << std::endl;
    return false;
}

TiXmlElement* XmlObject::getXmlRootElement()
{
    if(_bDocLoaded)
        return _xmlDoc->RootElement();
    else
        return NULL;
}

} // namespace
