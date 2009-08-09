/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#include "XmlFile.h"

#include <sstream>

XmlFile::XmlFile() : _xmlPtr(NULL)
{
    _xmlDoc = new TiXmlDocument();
}

XmlFile::~XmlFile()
{
    delete _xmlDoc;
}

bool XmlFile::loadFile(std::string filename)
{
    // reset element pointer
    _xmlPtr = NULL;

    if(!_xmlDoc->LoadFile(filename))
    {
        return false;
    }

    // set xml pointer to root node
    _xmlPtr = _xmlDoc->FirstChildElement();

    LOG << "|" << (std::string) _xmlPtr->Value() << "|" <<  std::endl;

    return true;
}

std::string XmlFile::getDocRootName()
{
    if(_xmlPtr == NULL)
    {
        LOG << "pointer is null" << std::endl;
        return "";
    }

    LOG << "|" << _xmlDoc->FirstChildElement()->Value() << "|" <<  std::endl;

    return (std::string) _xmlDoc->FirstChildElement()->Value();
}

/* ***** TRAVERSAL ***** */

bool XmlFile::gotoNextElement()
{
    if(_xmlPtr == NULL)
    {
        return false;
    }

    // try to go to the next element, returns 0 (NULL) if no more siblings
    TiXmlElement* tempXmlPtr = _xmlPtr->NextSiblingElement();
    if(tempXmlPtr == NULL)
    {
        return false;
    }

    _xmlPtr = tempXmlPtr;

    return true;
}

bool XmlFile::gotoPrevElement()
{
    if(_xmlPtr == NULL)
    {
        return false;
    }

    // try to go to the next child element, returns 0 (NULL) if no children
    TiXmlElement* tempXmlPtr = _xmlPtr->PreviousSibling()->ToElement();
    if(tempXmlPtr == NULL)
    {
        return false;
    }

    _xmlPtr = tempXmlPtr;

    return true;
}

bool XmlFile::gotoChildElement()
{
    if(_xmlPtr == NULL)
    {
        return false;
    }

    // try to go to the next child element, returns 0 (NULL) if no children
    TiXmlElement* tempXmlPtr = _xmlPtr->FirstChildElement();
    if(tempXmlPtr == NULL)
    {
        return false;
    }

    _xmlPtr = tempXmlPtr;

    return true;
}

bool XmlFile::gotoParentElement()
{
    if(_xmlPtr == NULL)
    {
        return false;
    }

    _xmlPtr = _xmlPtr->Parent()->ToElement();

    return true;
}

/* ***** READ ***** */

std::string XmlFile::getElementName()
{
    if(_xmlPtr == NULL)
    {
        return "";
    }

    return _xmlPtr->ValueStr();
}

std::string XmlFile::getElementText()
{
    if(_xmlPtr == NULL)
    {
        return "";
    }

    return (std::string) _xmlPtr->GetText();
}

bool XmlFile::getAttrString(std::string name, std::string& s)
{
    if(_xmlPtr == NULL)
    {
        return false;
    }

    // try to grab value, will be NULL if attr does not exist
    const char* pcValue = _xmlPtr->Attribute(name.c_str());
    if(pcValue == NULL)
    {
        return false;
    }

    s = (std::string) pcValue;
    return true;
}

bool XmlFile::getAttrInt(std::string name, int* i)
{
    if(_xmlPtr == NULL)
    {
        return false;
    }

    int iRet  = _xmlPtr->QueryIntAttribute(name.c_str(), i);

    switch(iRet)
    {
        case TIXML_WRONG_TYPE:
            LOG_WARN << "XmlFile::getAttrInt(): attribute \"" << name
                     << "\" is not of type int, ignoring" << std::endl;
            return false;

        case TIXML_NO_ATTRIBUTE:
            LOG_WARN << "XmlFile::getAttrInt(): int attribute \"" << name
                     << "\" was not found" << std::endl;
            return false;

        default:    // TIXML_SUCCESS:
            return true;
    }
}

bool XmlFile::getAttrDouble(std::string name, double* d)
{
    if(_xmlPtr == NULL)
    {
        return false;
    }

    int iRet = _xmlPtr->QueryDoubleAttribute(name.c_str(), d);

    switch(iRet)
    {
        case TIXML_WRONG_TYPE:
            LOG_WARN << "XmlFile::getAttrDouble(): attribute \"" << name
                     << "\" is not of type double, ignoring" << std::endl;
            return false;

        case TIXML_NO_ATTRIBUTE:
            LOG_WARN << "XmlFile::getAttrInt(): double attribute \"" << name
                     << "\" was not found" << std::endl;
            return false;

        default:    // TIXML_SUCCESS:
            return true;
    }
}

bool XmlFile::getAttrFloat(std::string name, float* f)
{
    if(_xmlPtr == NULL)
    {
        return false;
    }

    int iRet = _xmlPtr->QueryFloatAttribute(name.c_str(), f);

    switch(iRet)
    {
        case TIXML_WRONG_TYPE:
            LOG_WARN << "XmlFile::getAttrFloat(): attribute \"" << name
                     << "\" is not of type float, ignoring" << std::endl;
            return false;

        case TIXML_NO_ATTRIBUTE:
            LOG_WARN << "XmlFile::getAttrInt(): float attribute \"" << name
                     << "\" was not found" << std::endl;
            return false;

        default:    // TIXML_SUCCESS:
            return true;
    }
}

/* ***** UTIL ***** */

std::string XmlFile::getErrorString()
{
    std::stringstream error;
    error << " line " <<  _xmlDoc->ErrorRow() << " , " << (std::string) _xmlDoc->ErrorDesc();
    return error.str();
}
