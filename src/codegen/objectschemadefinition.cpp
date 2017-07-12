#include "stdafx.h"

#include "config.h"
#include "fileoutputstream.h"
#include "endpoint.h"
#include "helpers.h"
#include "objectschemadefinition.h"

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Path;
using namespace Poco;
using namespace std;

namespace trader {

	ObjectSchemaDefinition::ObjectSchemaDefinition(const string& _name)
		: name(_name)
	{

	}

	const string& ObjectSchemaDefinition::getName()
	{
		return name;
	}

	void ObjectSchemaDefinition::read(JSON::Object::Ptr obj)
	{
		rootObj = obj;
	}

	const char* getCppType(const string& jsonType, JSON::Object::Ptr obj)
	{
		if (jsonType.compare("double") == 0)
		{
			return "double";
		}
		else if (jsonType.compare("int") == 0)
		{
			Poco::Dynamic::Var formatVar = obj->get("format");
			if (!formatVar.isEmpty())
			{
				string format = formatVar.convert<string>();
				if (format.compare("epochtime") == 0)
				{
					return "std::time_t";
				}
			}
			return "Poco::Int32";
		}
		else if (jsonType.compare("string") == 0)
		{
			return "std::string";
		}
		return nullptr;
	}

	bool isArray(const string& jsonType)
	{
		if (jsonType.compare("array") == 0)
		{
			return true;
		}
		return false;
	}

	bool isObject(const string& jsonType)
	{
		if (jsonType.compare("object") == 0)
		{
			return true;
		}
		return false;
	}

	void ObjectSchemaDefinition::cppConstruct(JSON::Object::Ptr obj, ApiFileOutputStream& stream, expansionstringstream expansionStream, string keyName, UInt32 idx, bool previousArray)
	{
		string type = obj->get("type");
		if (isObject(type))
		{
			//if (!previousArray)
			{
				expansionStream << expansionstringstream::OBJECT;
			}
			JSON::Object::Ptr properties = obj->getObject("properties");
			stream << "Poco::JSON::Object::Ptr " << temp_name(idx+1) << " = " << temp_name(idx+0) << ".extract<Poco::JSON::Object::Ptr>()" << cendl;
			UInt32 nextIdx = 2;
			for (auto& property : *properties)
			{
				JSON::Object::Ptr propertyObject = property.second.extract<JSON::Object::Ptr>();
				{
					ScopedStream<ApiFileOutputStream> scopedStream(stream);
					stream << "Poco::Dynamic::Var " << temp_name(idx+nextIdx) << " = " << temp_name(idx+1) << "->get(\"" << property.first << "\")" << cendl;
					cppConstruct(propertyObject, stream, expansionStream, property.first, idx+nextIdx, false);
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
			stream << "Poco::JSON::Array::Ptr " << temp_name(idx+1) << " = " << temp_name(idx+0) << ".extract<Poco::JSON::Array::Ptr>()" << cendl;
			stream << "for (Poco::JSON::Array::ConstIterator " << temp_name(idx+2) << " = " << temp_name(idx+1) << "->begin(); " << temp_name(idx+2) << " != " << temp_name(idx+1) << "->end(); ++" << temp_name(idx+2) << ")" << endl;
			{
				ScopedStream<ApiFileOutputStream> scopedStream(stream);
				stream << expansionStream.type_name_str() << " " << expansionStream.var_name_str() << cendl;
				stream << "Poco::Dynamic::Var " << temp_name(idx+3) << " = *" << temp_name(idx+2) << cendl;
				cppConstruct(items, stream, expansionStream, keyName, idx+3, true);
				if (previousArray)
				{
					stream << previousexpansionStream.var_name_str() << ".push_back(" << expansionStream.var_name_str() << ") " << cendl;
				}
				else
				{
					previousexpansionStream << keyName;
					stream << previousexpansionStream.prefix_str() << ".push_back(" << expansionStream.var_name_str() << ")" << cendl;
				}
			}
		}
		else
		{
			const char* cppType = getCppType(type, obj);
			if (cppType)
			{
				if (expansionStream.has(expansionstringstream::ARRAY))
				{
					if (expansionStream.wasPrevious(expansionstringstream::ARRAY))
					{
						stream << expansionStream.var_name_str() << " = " << temp_name(idx) << ".convert<" << getCppType(type, obj) << ">()" << cendl;
					}
					else
					{
						stream << expansionStream.var_name_str() << "." << keyName << " = " << temp_name(idx) << ".convert<" << getCppType(type, obj) << ">()" << cendl;
					}
				}
				else
				{
					stream << expansionStream.prefix_str() << "." << keyName << " = " << temp_name(idx) << ".convert<" << getCppType(type, obj) << ">()" << cendl;
				}
			}
		}
	}

	void ObjectSchemaDefinition::writeCpp(ApiFileOutputStream& cpp)
	{
		cpp << "void " << name << "::readFile(const std::string& _fileName)";
		{
			ScopedStream<ApiFileOutputStream> scopedStream(cpp);
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
			ScopedStream<ApiFileOutputStream> scopedStream(cpp);
			expansionstringstream temp;
			cppConstruct(rootObj, cpp, temp, "data", 0, false);
		}
		cpp << endl;
	}



	void ObjectSchemaDefinition::headerConstruct(JSON::Object::Ptr obj, ApiFileOutputStream& stream, string expandedName, string keyName, bool previousArray)
	{
		string type = obj->get("type");
		if (isObject(type))
		{
			if (!previousArray)
			{
				expandedName += "Object";
			}
			JSON::Object::Ptr properties = obj->getObject("properties");
			{
				ScopedStruct<0, ApiFileOutputStream> scopedStream(stream, expandedName);
				for (auto& property : *properties)
				{
					JSON::Object::Ptr propertyObject = property.second.extract<JSON::Object::Ptr>();
					headerConstruct(propertyObject, stream, expandedName, property.first, false);
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
		else
		{
			const char* cppType = getCppType(type, obj);
			if (cppType)
			{
				if (previousArray)
				{
					stream << "typedef " << getCppType(type, obj) << tabs(1) << type_name(keyName) << cendl;
				}
				else
				{
					stream << getCppType(type, obj) << tabs(1) << var_name(keyName) << cendl;
				}

			}
		}
	}

	void ObjectSchemaDefinition::writeHeader(ApiFileOutputStream& header)
	{
		header << "void readFile(const std::string& _fileName)" << cendl;
		header << endl;
		header << "void read(Poco::Dynamic::Var val)" << cendl;
		header << endl;

		headerConstruct(rootObj, header, "", "data", false);
	}

	void ObjectSchemaDefinition::writeRestEncodedParams(ApiFileOutputStream& stream)
	{
		string type = rootObj->get("type");
		if (isObject(type))
		{
			JSON::Object::Ptr properties = rootObj->getObject("properties");
			{
				UInt32 count = 0;
				for (auto& property : *properties)
				{
					JSON::Object::Ptr propertyObject = property.second.extract<JSON::Object::Ptr>();
					stream << "std::ostringstream var" << count << cendl;
					stream << "var" << count << " << " << var_name(name) << "->object." << property.first << cendl;
					stream << "uri.addQueryParameter(std::string(\"" << property.first << "\"), var" << count << ".str())" << cendl;
					count++;
				}
			}
		}
	}

}


