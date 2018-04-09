#include "stdafx.h"

#include "config.h"
#include "endpoint.h"
#include "fileoutputstream.h"
#include "helpers.h"
#include "objectschemadefinition.h"

namespace trader
{

    ObjectSchemaDefinition::ObjectSchemaDefinition(const string &_name)
        : name(_name)
    {
    }

    const string &ObjectSchemaDefinition::getName() { return name; }

    void ObjectSchemaDefinition::read(JSON::Object::Ptr obj) { rootObj = obj; }

    const char *getCppType(const string &jsonType, JSON::Object::Ptr obj)
    {
        if (jsonType.compare("number") == 0)
        {
            Poco::Dynamic::Var formatVar = obj->get("format");
            if (!formatVar.isEmpty())
            {
                string format = formatVar.convert< string >();
                if (format.compare("epochtime") == 0)
                {
                    return "std::time_t";
                }
                else if (format.compare("double") == 0)
                {
                    return "double";
                }
                else if (format.compare("int64") == 0)
                {
                    return "Poco::Int64";
                }
            }
            return "Poco::Int32";
        }
        else if (jsonType.compare("string") == 0)
        {
            Poco::Dynamic::Var formatVar = obj->get("format");
            if (!formatVar.isEmpty())
            {
                string format = formatVar.convert< string >();
                if (format.compare("char") == 0)
                {
                    return "char";
                }
                else if (format.compare("time") == 0)
                {
                    return "FormattedTime";
                }
            }
            return "std::string";
        }
        else if (jsonType.compare("bool") == 0)
        {
            return "bool";
        }
        return nullptr;
    }

    const char *getJsonLibType(const string &jsonType, JSON::Object::Ptr obj)
    {
        if (jsonType.compare("string") == 0)
        {
            Poco::Dynamic::Var formatVar = obj->get("format");
            if (!formatVar.isEmpty())
            {
                string format = formatVar.convert< string >();
                if (format.compare("time") == 0)
                {
                    return "std::string";
                }
            }
        }
        return getCppType(jsonType, obj);
    }

    bool useIsSet(const string &jsonType, JSON::Object::Ptr obj)
    {
        if (jsonType.compare("string") == 0)
        {
            Poco::Dynamic::Var formatVar = obj->get("format");
            if (!formatVar.isEmpty())
            {
                string format = formatVar.convert< string >();
                if (format.compare("time") == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    std::string getCppDefaultVal(const string &jsonType, JSON::Object::Ptr obj)
    {
        if (jsonType.compare("number") == 0)
        {
            Poco::Dynamic::Var formatVar = obj->get("format");
            if (!formatVar.isEmpty())
            {
                string format = formatVar.convert< string >();
                if (format.compare("epochtime") == 0)
                {
                    return "std::numeric_limits<time_t>::max()";
                }
                else if (format.compare("double") == 0)
                {
                    return "std::numeric_limits<double>::max()";
                }
                else if (format.compare("int64") == 0)
                {
                    return "std::numeric_limits<Poco::Int64>::max()";
                }
            }
            return "std::numeric_limits<Poco::Int32>::max()";
        }
        else if (jsonType.compare("string") == 0)
        {
            Poco::Dynamic::Var formatVar = obj->get("format");
            if (!formatVar.isEmpty())
            {
                string format = formatVar.convert< string >();
                if (format.compare("char") == 0)
                {
                    return "std::numeric_limits<char>::max()";
                }
                else if (format.compare("time") == 0)
                {
                    Poco::Dynamic::Var patternVar = obj->get("pattern");
                    if (!patternVar.isEmpty())
                    {
                        string pattern = patternVar.convert< string >();
                        ostringstream stream;
                        stream << "\"" << pattern << "\"";
                        return stream.str().c_str();
                    }
                }
            }
            return "\"Empty\"";
        }
        else if (jsonType.compare("bool") == 0)
        {
            return "false";
        }
        return nullptr;
    }

    bool isArray(const string &jsonType)
    {
        if (jsonType.compare("array") == 0)
        {
            return true;
        }
        return false;
    }

    bool isObject(const string &jsonType)
    {
        if (jsonType.compare("object") == 0)
        {
            return true;
        }
        return false;
    }

    bool isMap(const string &jsonType)
    {
        if (jsonType.compare("map") == 0)
        {
            return true;
        }
        return false;
    }

    void ObjectSchemaDefinition::cppConstruct(JSON::Object::Ptr obj, ApiFileOutputStream &stream,
                                              expansionstringstream expansionStream, string keyName, UInt32 idx,
                                              bool previousArray)
    {
        string type = obj->get("type");
        if (isObject(type))
        {
            if (!previousArray)
            {
                ostringstream temp;
                temp << "::" << type_name(keyName) << expansionStream.getTypeString(expansionstringstream::OBJECT);
                expansionStream << temp.str();
            }
            else
            {
                expansionStream << expansionstringstream::OBJECT;
            }
            JSON::Object::Ptr properties = obj->getObject("properties");
            stream << "Poco::JSON::Object::Ptr " << temp_name(idx + 1) << " = " << temp_name(idx + 0)
                   << ".extract<Poco::JSON::Object::Ptr>()" << cendl;
            UInt32 nextIdx = 2;
            for (auto &property : *properties)
            {
                JSON::Object::Ptr propertyObject = property.second.extract< JSON::Object::Ptr >();
                {
                    ScopedStream< ApiFileOutputStream > scopedStream(stream);
                    stream << "Poco::Dynamic::Var " << temp_name(idx + nextIdx) << " = " << temp_name(idx + 1)
                           << "->get(\"" << property.first << "\")" << cendl;
                    cppConstruct(propertyObject, stream, expansionStream, property.first, idx + nextIdx, false);
                }
                nextIdx++;
            }
        }
        else if (isArray(type))
        {
            expansionstringstream previousexpansionStream(expansionStream);
            if (!previousArray)
            {
                ostringstream temp;
                temp << "::" << type_name(keyName) << expansionStream.getTypeString(expansionstringstream::ARRAY);
                expansionStream << temp.str();
            }
            else
            {
                expansionStream << expansionstringstream::ARRAY;
            }
            JSON::Object::Ptr items = obj->getObject("items");
            stream << "Poco::JSON::Array::Ptr " << temp_name(idx + 1) << " = " << temp_name(idx + 0)
                   << ".extract<Poco::JSON::Array::Ptr>()" << cendl;
            stream << "for (Poco::JSON::Array::ConstIterator " << temp_name(idx + 2) << " = " << temp_name(idx + 1)
                   << "->begin(); " << temp_name(idx + 2) << " != " << temp_name(idx + 1) << "->end(); ++"
                   << temp_name(idx + 2) << ")" << endl;
            {
                ScopedStream< ApiFileOutputStream > scopedStream(stream);
                stream << expansionStream.type_name_str() << " " << expansionStream.var_name_str() << cendl;
                stream << "Poco::Dynamic::Var " << temp_name(idx + 3) << " = *" << temp_name(idx + 2) << cendl;
                cppConstruct(items, stream, expansionStream, keyName, idx + 3, true);
                if (previousArray)
                {
                    CODEGEN_DEBUG(stream << comment("Case Array 1"));
                    stream << previousexpansionStream.var_name_str() << ".push_back(" << expansionStream.var_name_str()
                           << ") " << cendl;
                }
                else
                {
                    if (previousexpansionStream.var_name_str().size() &&
                        (previousexpansionStream.wasPrevious(expansionstringstream::ARRAY) ||
                         previousexpansionStream.wasPreviousPrevious(expansionstringstream::MAP)))
                    {
                        CODEGEN_DEBUG(stream << comment("Case Array 2"));
                        stream << previousexpansionStream.var_name_str() << "." << keyName << ".push_back("
                               << expansionStream.var_name_str() << ")" << cendl;
                    }
                    else
                    {
                        CODEGEN_DEBUG(stream << comment("Case Array 3"));
                        previousexpansionStream << keyName;
                        stream << previousexpansionStream.prefix_str() << ".push_back("
                               << expansionStream.var_name_str() << ")" << cendl;
                    }
                }
                CODEGEN_DEBUG(stream << "/*" << previousexpansionStream.debug_stack_str() << "*/" << endl);
                // expansionstringstream newExpansionStream(expansionStream);
                // newExpansionStream << keyName;
                // CODEGEN_DEBUG(stream << "/*" << newExpansionStream.debug_str_2() << "*/" << endl);
            }
        }
        else if (isMap(type))
        {
            expansionstringstream previousexpansionStream(expansionStream);
            if (!previousArray)
            {
                ostringstream temp;
                temp << "::" << type_name(keyName) << expansionStream.getTypeString(expansionstringstream::MAP);
                expansionStream << temp.str();
            }
            else
            {
                expansionStream << expansionstringstream::MAP;
            }
            JSON::Object::Ptr properties = obj->getObject("properties");
            std::vector< string > specialKeys;
            for (auto &property : *properties)
            {
                if (property.first.compare("key") != 0)
                {
                    specialKeys.push_back(property.first);
                }
            }
            stream << "Poco::JSON::Object::Ptr " << temp_name(idx + 1) << " = " << temp_name(idx + 0)
                   << ".extract<Poco::JSON::Object::Ptr>()" << cendl;
            stream << "for (Poco::JSON::Object::ConstIterator " << temp_name(idx + 2) << " = " << temp_name(idx + 1)
                   << "->begin(); " << temp_name(idx + 2) << " != " << temp_name(idx + 1) << "->end(); ++"
                   << temp_name(idx + 2) << ")" << endl;
            {
                ScopedStream< ApiFileOutputStream > scopedStream2(stream);
                stream << "Poco::Dynamic::Var " << temp_name(idx + 3) << " = " << temp_name(idx + 2) << "->second"
                       << cendl;
                for (auto &specialKey : specialKeys)
                {
                    stream << "if (" << temp_name(idx + 2) << "->first.compare(\"" << specialKey << "\")==0)" << endl;
                    {
                        ScopedStream< ApiFileOutputStream > scopedStream3(stream);
                        JSON::Object::Ptr propertyObject = properties->getObject(specialKey);
                        cppConstruct(propertyObject, stream, previousexpansionStream, specialKey, idx + 3, true);
                    }
                }
                if (specialKeys.size())
                {
                    stream << "else" << endl;
                }
                {
                    ScopedStream< ApiFileOutputStream > scopedStream(stream);
                    stream << expansionStream.type_name_str() << " " << expansionStream.var_name_str() << cendl;
                    JSON::Object::Ptr propertyObject = properties->getObject("key");
                    cppConstruct(propertyObject, stream, expansionStream, keyName, idx + 3, true);
                    if (previousArray)
                    {
                        CODEGEN_DEBUG(stream << comment("Case Map A"));
                        stream << previousexpansionStream.var_name_str() << ".insert(std::pair<property.first, "
                               << expansionStream.var_name_str() << "))" << cendl;
                    }
                    else
                    {
                        CODEGEN_DEBUG(stream << comment("Case Map B"));
                        previousexpansionStream << keyName;
                        stream << previousexpansionStream.prefix_str() << ".insert(std::pair<std::string,"
                               << expansionStream.type_name_str() << ">(" << temp_name(idx + 2) << "->first, "
                               << expansionStream.var_name_str() << "))" << cendl;
                    }
                    expansionstringstream newExpansionStream(expansionStream);
                    newExpansionStream << keyName;
                    CODEGEN_DEBUG(stream << "/*" << newExpansionStream.debug_str_2() << "*/" << endl);
                }
            }
        }
        else
        {
            const char *cppType = getCppType(type, obj);
            if (cppType)
            {
                stream << "if (!" << temp_name(idx) << ".isEmpty())" << endl;
                {
                    ScopedStream< ApiFileOutputStream > scopedStream(stream);
                    if (expansionStream.has(expansionstringstream::ARRAY) ||
                        expansionStream.has(expansionstringstream::MAP))
                    {
                        if (expansionStream.wasPrevious(expansionstringstream::ARRAY) ||
                            expansionStream.wasPrevious(expansionstringstream::MAP))
                        {
                            CODEGEN_DEBUG(stream << comment("Case Var 1"));
                            stream << expansionStream.var_name_str() << " = " << temp_name(idx) << ".convert<"
                                   << getJsonLibType(type, obj) << ">()" << cendl;
                        }
                        else
                        {
                            CODEGEN_DEBUG(stream << comment("Case Var 2"));
                            stream << expansionStream.var_name_str() << "." << var_name(keyName) << " = "
                                   << temp_name(idx) << ".convert<" << getJsonLibType(type, obj) << ">()" << cendl;
                        }
                    }
                    else
                    {
                        CODEGEN_DEBUG(stream << comment("Case Var 3"));
                        stream << expansionStream.prefix_str() << "." << var_name(keyName) << " = " << temp_name(idx)
                               << ".convert<" << getJsonLibType(type, obj) << ">()" << cendl;
                    }
                }
                expansionstringstream newExpansionStream(expansionStream);
                newExpansionStream << keyName;
                CODEGEN_DEBUG(stream << "/*" << newExpansionStream.debug_str_2() << "*/" << endl);
            }
        }
    }

    void ObjectSchemaDefinition::writeCpp(ApiFileOutputStream &cpp)
    {
        cpp << "void " << name << "::readFile(const std::string& _fileName)";
        {
            ScopedStream< ApiFileOutputStream > scopedStream(cpp);
            cpp << "std::ostringstream ostr" << cendl;
            cpp << "Poco::FileInputStream fis(_fileName)" << cendl;
            cpp << "Poco::StreamCopier::copyStream(fis, ostr)" << cendl;

            cpp << "Poco::JSON::Parser parser" << cendl;
            cpp << "Poco::Dynamic::Var result = parser.parse(ostr.str())" << cendl;
            cpp << "read(result)" << cendl;
        }
        cpp << endl;

        cpp << "void " << name << "::read(Poco::Dynamic::Var obj0) ";
        {
            ScopedStream< ApiFileOutputStream > scopedStream(cpp);
            expansionstringstream temp;
            cppConstruct(rootObj, cpp, temp, "data", 0, false);
        }
        cpp << endl;
    }

    void ObjectSchemaDefinition::headerConstructorConstruct(JSON::Object::Ptr obj, ApiFileOutputStream &stream,
                                                            string expandedName, string keyName, bool previousArray,
                                                            bool &first)
    {
        string type = obj->get("type");
        if (!isObject(type) && !isArray(type) && !isMap(type) && !previousArray)
        {
            if (first)
            {
                stream << ": ";
                first = false;
            }
            else
            {
                stream << ", ";
            }
            stream << var_name(keyName) << "(" << getCppDefaultVal(type, obj) << ")" << endl;
        }
    }

    void ObjectSchemaDefinition::headerConstruct(JSON::Object::Ptr obj, ApiFileOutputStream &stream,
                                                 string expandedName, string keyName, bool previousArray)
    {
        string type = obj->get("type");
        if (isObject(type))
        {
            if (!previousArray)
            {
                ostringstream temp;
                temp << type_name(keyName) << "Object";
                expandedName = temp.str();
            }
            JSON::Object::Ptr properties = obj->getObject("properties");
            {
                ScopedStruct< 0, ApiFileOutputStream > scopedStruct(stream, expandedName);
                for (auto &property : *properties)
                {
                    JSON::Object::Ptr propertyObject = property.second.extract< JSON::Object::Ptr >();
                    headerConstruct(propertyObject, stream, expandedName, property.first, false);
                }
                stream << type_name(expandedName) << "()" << endl;
                bool first = true;
                for (auto &property : *properties)
                {
                    JSON::Object::Ptr propertyObject = property.second.extract< JSON::Object::Ptr >();
                    headerConstructorConstruct(propertyObject, stream, expandedName, property.first, false, first);
                }
                {
                    ScopedStream< ApiFileOutputStream > scopedStream(stream);
                }
            }
            if (!previousArray)
            {
                stream << type_name(expandedName) << tabs(1) << var_name(expandedName) << cendl;
            }
        }
        else if (isArray(type))
        {
            if (!previousArray)
            {
                ostringstream temp;
                temp << type_name(keyName) << "Array";
                expandedName = temp.str();
            }
            else
            {
                expandedName += "Array";
            }
            JSON::Object::Ptr itemObj = obj->getObject("items");
            headerConstruct(itemObj, stream, expandedName, expandedName, true);
            stream << "typedef std::vector<" << expandedName << "> " << type_name(keyName) << cendl;
            if (!previousArray)
            {
                stream << type_name(keyName) << tabs(1) << var_name(keyName) << cendl;
            }
        }
        else if (isMap(type))
        {
            string previousExpandedName = expandedName;
            if (!previousArray)
            {
                ostringstream temp;
                temp << type_name(keyName) << "Map";
                expandedName = temp.str();
            }
            else
            {
                expandedName += "Map";
            }
            JSON::Object::Ptr properties = obj->getObject("properties");
            for (auto &property : *properties)
            {
                JSON::Object::Ptr propertyObject = property.second.extract< JSON::Object::Ptr >();
                if (property.first.compare("key") == 0)
                {
                    headerConstruct(propertyObject, stream, expandedName, expandedName, true);
                    stream << "typedef std::map<std::string, " << expandedName << "> " << type_name(keyName) << cendl;
                    if (!previousArray)
                    {
                        stream << type_name(keyName) << tabs(1) << var_name(keyName) << cendl;
                    }
                }
                else
                {
                    headerConstruct(propertyObject, stream, previousExpandedName, property.first, false);
                }
            }
        }
        else
        {
            const char *cppType = getCppType(type, obj);
            if (cppType)
            {
                if (previousArray)
                {
                    stream << "typedef " << getCppType(type, obj) << tabs(1) << type_name(keyName) << cendl;
                }
                else
                {
                    Poco::Dynamic::Var formatVar = obj->get("description");
                    if (!formatVar.isEmpty())
                    {
                        string description = formatVar.convert< string >();
                        stream << comment(description);
                    }
                    stream << "void Set" << type_name(keyName) << "(" << getCppType(type, obj) << " val)" << endl;
                    {
                        ScopedStream< ApiFileOutputStream > scopedStream(stream);
                        Poco::Dynamic::Var patternVar = obj->get("pattern");
                        if (!patternVar.isEmpty() && useIsSet(type, obj))
                        {
                            string pattern = patternVar.convert< string >();
                            trader::replace(pattern, "\\", "\\\\");
                            stream << "std::regex valRegex(\"" << pattern << "\")" << cendl;
                            if (strcmp(getCppType(type, obj), "char") == 0)
                            {
                                stream << "std::string valMatch(1, val)" << cendl;
                            }
                            else
                            {
                                stream << "std::string valMatch(val)" << cendl;
                            }
                            stream << "if (std::regex_match(valMatch, valRegex))" << endl;
                            {
                                ScopedStream< ApiFileOutputStream > scopedStreamRegex(stream);
                                stream << var_name(keyName) << " = val" << cendl;
                            }
                            stream << "else" << endl;
                            {
                                ScopedStream< ApiFileOutputStream > scopedStreamRegex(stream);
                                stream << "throw Poco::RegularExpressionException(\"" << var_name(keyName)
                                       << " invalid.\")" << cendl;
                            }
                        }
                        else
                        {
                            stream << var_name(keyName) << " = val" << cendl;
                        }
                    }
                    stream << endl;
                    if (useIsSet(type, obj))
                    {
                        stream << "bool isSet" << type_name(keyName) << "() ";
                        {
                            ScopedStream< ApiFileOutputStream > isSetScope(stream);
                            stream << "return (" << var_name(keyName) << " != " << getCppDefaultVal(type, obj) << ")"
                                   << cendl;
                        }
                        stream << endl;
                    }
                    stream << getCppType(type, obj) << tabs(1) << var_name(keyName) << cendl;
                }
                stream << endl;
            }
        }
    }

    void ObjectSchemaDefinition::writeHeader(ApiFileOutputStream &header)
    {
        header << "void readFile(const std::string& _fileName)" << cendl;
        header << endl;
        header << "void read(Poco::Dynamic::Var val)" << cendl;
        header << endl;

        headerConstruct(rootObj, header, "", "data", false);
    }

    void ObjectSchemaDefinition::writeRestEncodedParams(ApiFileOutputStream &stream)
    {
        string type = rootObj->get("type");
        if (isObject(type))
        {
            JSON::Array::Ptr required;
            Dynamic::Var requiredVar = rootObj->get("required");
            if (!requiredVar.isEmpty())
            {
                required = requiredVar.extract< JSON::Array::Ptr >();
            }
            JSON::Object::Ptr properties = rootObj->getObject("properties");
            {
                UInt32 count = 0;
                for (auto &property : *properties)
                {
                    bool isRequired = false;
                    if (required)
                    {
                        for (auto requiredProperty : *required)
                        {
                            string reqPropStr = requiredProperty.convert< string >();
                            if (reqPropStr.compare(property.first) == 0)
                            {
                                isRequired = true;
                                break;
                            }
                        }
                    }
                    JSON::Object::Ptr propertyObject = property.second.extract< JSON::Object::Ptr >();
                    stream << "if (" << var_name(name) << "->dataObject." << var_name(property.first)
                           << " != " << getCppDefaultVal(propertyObject->get("type"), propertyObject) << ") ";
                    {
                        ScopedStream< ApiFileOutputStream > scopedStream(stream);
                        stream << var_name(name) << "->dataObject.Set" << type_name(property.first) << "("
                               << var_name(name) << "->dataObject." << var_name(property.first) << ")" << cendl;
                        stream << "std::ostringstream var" << count << cendl;
                        stream << "var" << count << " << " << var_name(name) << "->dataObject."
                               << var_name(property.first) << cendl;
                        stream << "uri.addQueryParameter(std::string(\"" << property.first << "\"), var" << count
                               << ".str())" << cendl;
                    }
                    if (isRequired)
                    {
                        stream << "else ";
                        {
                            ScopedStream< ApiFileOutputStream > scopedStream(stream);
                            stream << "throw Poco::NullValueException(\"" << property.first << " must be set.\")"
                                   << cendl;
                        }
                    }
                    count++;
                }
            }
        }
    }

} // namespace trader
