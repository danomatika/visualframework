/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "Xml.h"

#include <sstream>

namespace visual {

TiXmlElement* Xml::loadFile(TiXmlDocument* xmlDoc, std::string filename)
{

    if(xmlDoc == NULL)
    {
        return NULL;
    }

    if(!xmlDoc->LoadFile(filename.c_str(), TIXML_ENCODING_UTF8))
    {
        return NULL;
    }

    TiXmlElement* xmlPtr = xmlDoc->RootElement();//FirstChildElement();
    // set xml pointer to root node
    return xmlPtr;
}

/* ***** READ ***** */

bool Xml::getAttrString(const TiXmlElement* xmlPtr, std::string name, std::string& s)
{
    if(xmlPtr == NULL)
    {
        return false;
    }

    // try to grab value, will be NULL if attr does not exist
    const char* pcValue = xmlPtr->Attribute(name.c_str());
    if(pcValue == NULL)
    {
        LOG_WARN << "Xml::getAttrString(): string attribute \"" << name
                     << "\" was not found in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;
        return false;
    }

    s = (std::string) pcValue;
    return true;
}

bool Xml::getAttrInt(const TiXmlElement* xmlPtr, std::string name, int* i)
{
    if(xmlPtr == NULL)
    {
        return false;
    }

    int iRet  = xmlPtr->QueryIntAttribute(name.c_str(), i);

    switch(iRet)
    {
        case TIXML_WRONG_TYPE:
            LOG_WARN << "Xml::getAttrInt(): attribute \"" << name
                     << "\" is not of type int in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;

        case TIXML_NO_ATTRIBUTE:
            LOG_WARN << "Xml::getAttrInt(): int attribute \"" << name
                     << "\" was not found in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;

        default:    // TIXML_SUCCESS:
            return true;
    }
}

bool Xml::getAttrDouble(const TiXmlElement* xmlPtr, std::string name, double* d)
{
    if(xmlPtr == NULL)
    {
        return false;
    }

    int iRet = xmlPtr->QueryDoubleAttribute(name.c_str(), d);

    switch(iRet)
    {
        case TIXML_WRONG_TYPE:
            LOG_WARN << "Xml::getAttrDouble(): attribute \"" << name
                     << "\" is not of type double in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;

        case TIXML_NO_ATTRIBUTE:
            LOG_WARN << "Xml::getAttrDouble(): double attribute \"" << name
                     << "\" was not found in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;

        default:    // TIXML_SUCCESS:
            return true;
    }
}

bool Xml::getAttrFloat(const TiXmlElement* xmlPtr, std::string name, float* f)
{
    if(xmlPtr == NULL)
    {
        return false;
    }

    int iRet = xmlPtr->QueryFloatAttribute(name.c_str(), f);

    switch(iRet)
    {
        case TIXML_WRONG_TYPE:
            LOG_WARN << "Xml::getAttrFloat(): attribute \"" << name
                     << "\" is not of type float in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;

        case TIXML_NO_ATTRIBUTE:
            LOG_WARN << "Xml::getAttrFloat(): float attribute \"" << name
                     << "\" was not found in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;

        default:    // TIXML_SUCCESS:
            return true;
    }
}

bool Xml::getAttrBool(const TiXmlElement* xmlPtr, std::string name, bool* b)
{
    if(xmlPtr == NULL)
    {
        return false;
    }

    int value = 0;
    int iRet = xmlPtr->QueryIntAttribute(name.c_str(), &value);

    switch(iRet)
    {
        case TIXML_WRONG_TYPE:
            LOG_WARN << "Xml::getAttrBool(): attribute \"" << name
                     << "\" is not of type int in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;

        case TIXML_NO_ATTRIBUTE:
            LOG_WARN << "Xml::getAttrBool(): int attribute \"" << name
                     << "\" was not found in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;

        default:    // TIXML_SUCCESS:
            //b = (bool*) value;
            return true;
    }
}

std::string element2String(const TiXmlElement* xmlPtr, std::string indent)
{
    if(xmlPtr == NULL)
    {
        return "";
    }

	const TiXmlAttribute* xmlAttr = xmlPtr->FirstAttribute();

	std::stringstream stream;
	stream << "Elem: " << xmlPtr->Value() << std::endl;

    // loop through attributes
	while(xmlAttr != NULL)
	{
        stream << indent << "Attr: " << xmlAttr->Name() << " " << xmlAttr->Value();
		xmlAttr = xmlAttr->Next();
	}

	return stream.str();
}

/* ***** UTIL ***** */

std::string Xml::getErrorString(const TiXmlDocument xmlDoc)
{
    std::stringstream error;
    error << " line " <<  xmlDoc.ErrorRow() << " , " << (std::string) xmlDoc.ErrorDesc();
    return error.str();
}

} // namespace
