/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#include "Xml.h"

#include <sstream>

namespace visual {

/* ***** READ ***** */

bool Xml::getAttrString(const TiXmlElement* xmlPtr, std::string name, std::string* s)
{
    if(xmlPtr == NULL || s == NULL)
    {
        LOG_ERROR << "Xml::getAttrString(): element and/or variable are NULL" << std::endl;
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
    }

    s->clear();
    s->append((std::string) pcValue);
    return true;
}

bool Xml::getAttrInt(const TiXmlElement* xmlPtr, std::string name, int* i)
{
    if(xmlPtr == NULL || i == NULL)
    {
        LOG_ERROR << "Xml::getAttrInt(): element and/or variable are NULL" << std::endl;
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

bool Xml::getAttrUInt(const TiXmlElement* xmlPtr, std::string name, unsigned int* i)
{
    if(xmlPtr == NULL || i == NULL)
    {
        LOG_ERROR << "Xml::getAttrUInt(): element and/or variable are NULL" << std::endl;
        return false;
    }

    int value = 0;
    int iRet  = xmlPtr->QueryIntAttribute(name.c_str(), &value);
    switch(iRet)
    {
        case TIXML_WRONG_TYPE:
            LOG_WARN << "Xml::getAttrUInt(): attribute \"" << name
                     << "\" is not of type int in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;

        case TIXML_NO_ATTRIBUTE:
            LOG_WARN << "Xml::getAttrUInt(): int attribute \"" << name
                     << "\" was not found in element \"" << xmlPtr->ValueStr()
                     << "\"" << std::endl;
            return false;

        default:    // TIXML_SUCCESS:
            *i = (unsigned int) value;
            return true;
    }
}

bool Xml::getAttrDouble(const TiXmlElement* xmlPtr, std::string name, double* d)
{
    if(xmlPtr == NULL || d == NULL)
    {
        LOG_ERROR << "Xml::getAttrDouble(): element and/or variable are NULL" << std::endl;
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
    if(xmlPtr == NULL || f == NULL)
    {
        LOG_ERROR << "Xml::getAttrFloat(): element and/or variable are NULL" << std::endl;
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
    if(xmlPtr == NULL || b == NULL)
    {
        LOG_ERROR << "Xml::getAttrBool(): element and/or variable are NULL" << std::endl;
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
            *b = (bool) value;
            return true;
    }
}

bool Xml::getAttr(const TiXmlElement* xmlPtr, std::string name, XmlType type, void* var)
{
    if(xmlPtr == NULL || var == NULL)
    {
        LOG_ERROR << "Xml::getAttr(): element and/or variable are NULL" << std::endl;
        return false;
    }

    bool ret = false;
    switch(type)
    {
        case XML_TYPE_BOOL:
            ret = getAttrBool(xmlPtr, name, (bool*) var);
            break;

        case XML_TYPE_INT:
            ret = getAttrInt(xmlPtr, name, (int*) var);
            break;

        case XML_TYPE_UINT:
            ret = getAttrUInt(xmlPtr, name, (unsigned int*) var);
            break;

        case XML_TYPE_FLOAT:
            ret = getAttrFloat(xmlPtr, name, (float*) var);
            break;

        case XML_TYPE_DOUBLE:
            ret = getAttrDouble(xmlPtr, name, (double*) var);
            break;

        case XML_TYPE_STRING:
            ret = getAttrString(xmlPtr, name, (std::string*) var);
            break;

        default:
            break;
    }

    return ret;
}

std::string Xml::getText(const TiXmlElement* xmlPtr)
{
    if(xmlPtr == NULL)
    {
        return "";
    }

    return (std::string) xmlPtr->GetText();
}

std::string Xml::element2String(const TiXmlElement* xmlPtr, std::string indent)
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

TiXmlElement* Xml::getElement(TiXmlElement* xmlPtr, std::string name, int index)
{
    if(xmlPtr == NULL)
    {
        LOG_ERROR << "Xml::getElement(): element is NULL" << std::endl;
        return NULL;
    }

    TiXmlHandle h(xmlPtr);
    return h.ChildElement(name, index).Element();
}

/* ***** WRITE ***** */

void Xml::setAttrString(TiXmlElement* xmlPtr, std::string name, std::string s)
{
    if(xmlPtr == NULL)
    {
        LOG_ERROR << "Xml::setAttrString(): element is NULL" << std::endl;
        return;
    }

    xmlPtr->SetAttribute(name, s);
}

void Xml::setAttrInt(TiXmlElement* xmlPtr, std::string name, int i)
{
    if(xmlPtr == NULL)
    {
        LOG_ERROR << "Xml::setAttrInt(): element is NULL" << std::endl;
        return;
    }

    xmlPtr->SetAttribute(name, i);
}

void Xml::setAttrUInt(TiXmlElement* xmlPtr, std::string name, unsigned int i)
{
    if(xmlPtr == NULL)
    {
        LOG_ERROR << "Xml::setAttrUInt(): element is NULL" << std::endl;
        return;
    }

    xmlPtr->SetAttribute(name, (int) i);
}

void Xml::setAttrDouble(TiXmlElement* xmlPtr, std::string name, double d)
{
    if(xmlPtr == NULL)
    {
        LOG_ERROR << "Xml::setAttrDouble(): element is NULL" << std::endl;
        return;
    }

    xmlPtr->SetDoubleAttribute(name.c_str(), d);
}

void Xml::setAttrFloat(TiXmlElement* xmlPtr, std::string name, float f)
{
    if(xmlPtr == NULL)
    {
        LOG_ERROR << "Xml::setAttrFloat(): element is NULL" << std::endl;
        return;
    }

    xmlPtr->SetDoubleAttribute(name.c_str(), f);
}

void Xml::setAttrBool(TiXmlElement* xmlPtr, std::string name, bool b)
{
    if(xmlPtr == NULL)
    {
        LOG_ERROR << "Xml::setAttrBool(): element is NULL" << std::endl;
        return;
    }

    xmlPtr->SetAttribute(name, (int) b);
}

void Xml::setAttr(TiXmlElement* xmlPtr, std::string name, XmlType type, void* var)
{
    if(xmlPtr == NULL || var == NULL)
    {
        LOG_ERROR << "Xml::setAttr(): element and/or variable are NULL" << std::endl;
        return;
    }

    switch(type)
    {
        case XML_TYPE_BOOL:
        {
            bool* b = (bool*) var;
            setAttrBool(xmlPtr, name, *b);
            break;
        }

        case XML_TYPE_INT:
        {
            int* i = (int*) var;
            setAttrInt(xmlPtr, name, *i);
            break;
        }

        case XML_TYPE_UINT:
        {
            unsigned int* ui = (unsigned int*) var;
            setAttrUInt(xmlPtr, name, *ui);
            break;
        }

        case XML_TYPE_FLOAT:
        {
            float* f = (float*) var;
            setAttrFloat(xmlPtr, name, *f);
            break;
        }

        case XML_TYPE_DOUBLE:
        {
            double* d = (double*) var;
            setAttrDouble(xmlPtr, name, *d);
            break;
        }

        case XML_TYPE_STRING:
        {
            std::string* s = (std::string*) var;
            setAttrString(xmlPtr, name, *s);
            break;
        }

        default:
            break;
    }
}

void Xml::setText(TiXmlElement* xmlPtr, std::string text)
{
    if(xmlPtr == NULL)
    {
        LOG_ERROR << "Xml::setText(): element is NULL" << std::endl;
        return;
    }

    xmlPtr->LinkEndChild(new TiXmlText(text));
}

TiXmlElement* Xml::obtainElement(TiXmlElement* xmlPtr, std::string name, int index)
{
    if(xmlPtr == NULL)
    {
        LOG_ERROR << "Xml::addExistingElement(): element is NULL" << std::endl;
        return NULL;
    }

    TiXmlHandle h(xmlPtr);

    // if element doesnt exit, add it
    TiXmlElement* child = h.ChildElement(name, index).Element();
    if(child == NULL)
    {
        child = new TiXmlElement(name);
        xmlPtr->LinkEndChild(child);
    }

    return child;
}

/* ***** UTIL ***** */

std::string Xml::getErrorString(const TiXmlDocument* xmlDoc)
{
    if(xmlDoc == NULL)
        return "";

    std::stringstream error;
    error << " line " <<  xmlDoc->ErrorRow() << " , " << (std::string) xmlDoc->ErrorDesc();
    return error.str();
}

} // namespace
