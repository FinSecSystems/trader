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

	void ObjectSchemaDefinition::read(JSON::Object::Ptr obj)
	{
		rootObj = obj;
	}

	const char* getCppType(const string& jsonType)
	{
		if (jsonType.compare("double") == 0)
		{
			return "double";
		}
		else if (jsonType.compare("int") == 0)
		{
			return "Poco::Int32";
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


	void ObjectSchemaDefinition::cppConstruct(UInt32 arrayCount, UInt32 objectCount, JSON::Object::Ptr obj, ApiFileOutputStream& stream, string depthName, string anonymousName, UInt32 objIndex, string prefix, bool useTemp)
	{
		string type = obj->get("type");
		if (isObject(type))
		{
			anonymousName += "Object";
			JSON::Object::Ptr properties = obj->getObject("properties");
			stringstream pref;
			pref << prefix;
			if (arrayCount)
			{
				stream << depthName << ".emplace_back()" << cendl;
				stream << anonymousName << "& obj" << objIndex+1 << " = " << depthName << ".back()" << cendl;
				pref.str("");
				pref.clear();
				pref << "obj" << objIndex + 1;
			}
			stream << "Poco::JSON::Object::Ptr obj" << objIndex+2 << " = obj" << objIndex << ".extract<Poco::JSON::Object::Ptr>()" << cendl;
			UInt32 nextIdx = 3;
			for (auto& property : *properties)
			{
				JSON::Object::Ptr propertyObject = property.second.extract<JSON::Object::Ptr>();
				++objectCount;
				{
					ScopedStream<ApiFileOutputStream> scopedStream(stream);
					stream << "Poco::Dynamic::Var obj" << objIndex + nextIdx << " = obj" << objIndex + 2 << "->get(\"" << property.first << "\")" << cendl;
					cppConstruct(arrayCount, objectCount, propertyObject, stream, property.first, anonymousName, objIndex + nextIdx, pref.str(), useTemp);
				}
				--objectCount;
				nextIdx++;
			}
		}
		else if (isArray(type))
		{
			anonymousName += "Array";
			JSON::Object::Ptr items = obj->getObject("items");
			stringstream obj1,obj2,obj3,obj4;
			obj1 << "obj" << objIndex;
			obj2 << "obj" << objIndex + 1;
			obj3 << "obj" << objIndex + 2;
			obj4 << "obj" << objIndex + 3;
			stream << "Poco::JSON::Array::Ptr " << obj2.str() << " = " << obj1.str() << ".extract<Poco::JSON::Array::Ptr>()" << cendl;
			if (arrayCount)
			{
				useTemp = true;
				stream << "std::vector<" << getCppType(items->get("type")) << "> obj" << objIndex + 13 - 2 << cendl;
			}
			stream << "for (Poco::JSON::Array::ConstIterator " << obj3.str() << " = " << obj2.str() << "->begin(); " << obj3.str() << " != " << obj2.str() << "->end(); ++" << obj3.str() << ")" << endl;
			{
				ScopedStream<ApiFileOutputStream> scopedStream(stream);
				stream << "Poco::Dynamic::Var " << obj4.str() << " = *" << obj3.str() << cendl;
				++arrayCount;
				cppConstruct(arrayCount, objectCount, items, stream, depthName, anonymousName, objIndex+3, prefix, useTemp);
				--arrayCount;
				if (arrayCount)
				{
					stream << "obj" << objIndex + 13 - 2 << ".push_back(tmp)" << cendl;
				}
				else
				{
					if (isArray(items->get("type")))
					{
						stream << depthName << ".push_back(obj" << objIndex + 14 << ")" << cendl;
					}
				}
			}
		}
		else
		{
			if (prefix.length())
			{
				stream << prefix << ".";
			}
			if (useTemp)
			{
				stream << getCppType(type) << " tmp = obj" << objIndex << ".convert<" << getCppType(type) << ">()" << cendl;
			}
			else
			{
				stream << depthName << " = obj" << objIndex << ".convert<" << getCppType(type) << ">()" << cendl;
			}
		}
	}


	void ObjectSchemaDefinition::cpp_construct(JSON::Object::Ptr obj, ApiFileOutputStream& stream, expansionstringstream expansionStream, string keyName, UInt32 idx, bool useAsType)
	{
		string type = obj->get("type");
		if (isObject(type))
		{
			if (!useAsType)
			{
				expansionStream << "Object";
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
					cpp_construct(propertyObject, stream, expansionStream, property.first, idx+nextIdx, false);
				}
				nextIdx++;
			}
		}
		else if (isArray(type))
		{
			expansionstringstream previousexpansionStream(expansionStream);
			if (!useAsType)
			{
				ostringstream temp;
				temp << "::" << type_name(keyName) << "Array";
				expansionStream << temp.str();
			}
			else
			{
				expansionStream << "Array";
			}

			JSON::Object::Ptr items = obj->getObject("items");
			stream << expansionStream.type_name_str() << " " << expansionStream.var_name_str() << cendl;
			stream << "Poco::JSON::Array::Ptr " << temp_name(idx+1) << " = " << temp_name(idx+0) << ".extract<Poco::JSON::Array::Ptr>()" << cendl;
			stream << "for (Poco::JSON::Array::ConstIterator " << temp_name(idx+2) << " = " << temp_name(idx+1) << "->begin(); " << temp_name(idx+2) << " != " << temp_name(idx+1) << "->end(); ++" << temp_name(idx+2) << ")" << endl;
			{
				ScopedStream<ApiFileOutputStream> scopedStream(stream);
				stream << "Poco::Dynamic::Var " << temp_name(idx+3) << " = *" << temp_name(idx+2) << cendl;
				cpp_construct(items, stream, expansionStream, keyName, idx+3, true);
			}
			if (useAsType)
			{
				stream << previousexpansionStream.var_name_str() << ".push_back(" << expansionStream.var_name_str() << ") " << cendl;
			}
			else
			{
				previousexpansionStream << keyName;
				stream << previousexpansionStream.prefix_str() << ".push_back(" << expansionStream.var_name_str() << ")" << cendl;
			}
		}
		else
		{
			const char* cppType = getCppType(type);
			if (cppType)
			{
				if (useAsType)
				{
					stream << expansionStream.var_name_str() << " = " << temp_name(idx) << ".convert<" << getCppType(type) << ">()" << cendl;
				}
				else
				{
					stream << expansionStream.prefix_str() << "." << keyName << " = " << temp_name(idx) << ".convert<" << getCppType(type) << ">()" << cendl;
				}
			}
		}
	}

	void ObjectSchemaDefinition::writeCpp(ApiFileOutputStream& cpp)
	{
		cpp << "void " << name << "::read(Poco::Dynamic::Var obj0) ";
		{
			ScopedStream<ApiFileOutputStream> scopedStream(cpp);
			//cppConstruct(0, 0, rootObj, cpp, "data", "", 0, "", false);
			expansionstringstream temp;
			cpp_construct(rootObj, cpp, temp, "data", 0, false);
		}
		
		cpp << endl;
	}



	void ObjectSchemaDefinition::header_construct(JSON::Object::Ptr obj, ApiFileOutputStream& stream, string expandedName, string keyName, bool useAsType)
	{
		string type = obj->get("type");
		if (isObject(type))
		{
			if (!useAsType)
			{
				expandedName += "Object";
			}
			JSON::Object::Ptr properties = obj->getObject("properties");
			{
				ScopedStruct<0, ApiFileOutputStream> scopedStream(stream, expandedName);
				for (auto& property : *properties)
				{
					JSON::Object::Ptr propertyObject = property.second.extract<JSON::Object::Ptr>();
					header_construct(propertyObject, stream, expandedName, property.first, false);
				}
			}
			if (useAsType)
			{
				//stream << "typedef " << expandedName << tabs(1) << type_name(keyName) << cendl;
			}
			else
			{
				stream << type_name(expandedName) << tabs(1) << var_name(expandedName) << cendl;
			}
		}
		else if (isArray(type))
		{
			if (!useAsType)
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
			header_construct(itemObj, stream, expandedName, expandedName, true);
			stream << "typedef std::vector<" << expandedName << "> " << type_name(keyName) << cendl;
			if (!useAsType)
			{
				stream << type_name(keyName) << tabs(1) << var_name(keyName) << cendl;
			}
		}
		else
		{
			const char* cppType = getCppType(type);
			if (cppType)
			{
				if (useAsType)
				{
					stream << "typedef " << getCppType(type) << tabs(1) << type_name(keyName) << cendl;
				}
				else
				{
					stream << getCppType(type) << tabs(1) << var_name(keyName) << cendl;
				}

			}
		}
	}

	void ObjectSchemaDefinition::writeHeader(ApiFileOutputStream& header)
	{
		/*
		header << "void read(Poco::Dynamic::Var val)" << cendl;
		header << endl;

		ApiStreamBuffer tempStreamMembers(header),
			tempStreamStructs(header);
		std::vector<ExpansionPair> toExpand;
		headerConstruct(toExpand, 0, 0, rootObj, tempStreamMembers, "data", "");
		while (toExpand.size()) {
			ExpansionPair exPair = toExpand.front();
			toExpand.erase(toExpand.begin());
			headerConstruct(toExpand, 0, 0, exPair._obj, tempStreamStructs, exPair._name, "xxx", true);
		};

		header << tempStreamStructs.str() << endl;
		header << tempStreamMembers.str() << endl;
		*/

		header << "void read(Poco::Dynamic::Var val)" << cendl;
		header << endl;

		header_construct(rootObj, header, "", "data", false);
	}

	void ObjectSchemaDefinition::headerConstructProperties(std::vector<ExpansionPair>& toExpand, UInt32 arrayCount, UInt32 objectCount, JSON::Object::Ptr obj, ApiStreamBuffer& stream, string depthName, string anoymousName)
	{
		JSON::Object::Ptr properties = obj->getObject("properties");
		for (auto& property : *properties)
		{
			JSON::Object::Ptr propertyObject = property.second.extract<JSON::Object::Ptr>();
			++objectCount;
			headerConstruct(toExpand, arrayCount, objectCount, propertyObject, stream, property.first, anoymousName);
			--objectCount;
		}
	}

	void ObjectSchemaDefinition::headerConstruct(std::vector<ExpansionPair>& toExpand, UInt32 arrayCount, UInt32 objectCount, JSON::Object::Ptr obj, ApiStreamBuffer& stream, string depthName, string anonymousName, bool newObject)
	{
		string type = obj->get("type");
		if (isObject(type))
		{
			anonymousName += "Object";
			if (objectCount || arrayCount)
			{
				toExpand.emplace_back(anonymousName, obj);
				if (arrayCount)
				{
					stream << toExpand.back()._name;
				}
				else
				{
					stream << tabs(1) << depthName << cendl;
				}
			}
			else
			{
				if (newObject)
				{
					ScopedStruct<0, ApiStreamBuffer> scopedStruct(stream, depthName);
					headerConstructProperties(toExpand, arrayCount, objectCount, obj, stream, depthName, anonymousName);
				}
				else
				{
					headerConstructProperties(toExpand, arrayCount, objectCount, obj, stream, depthName, anonymousName);
				}
			}
		}
		else if (isArray(type))
		{
			anonymousName += "Array";
			JSON::Object::Ptr items = obj->getObject("items");
			stream << "std::vector<";
			++arrayCount;
			headerConstruct(toExpand, arrayCount, objectCount, items, stream, depthName, anonymousName);
			--arrayCount;
			stream << ">";
			if (arrayCount == 0)
			{
				stream << tabs(1) << depthName << cendl;
			}
		}
		else
		{
			const char* cppType = getCppType(type);
			if (cppType)
			{
				stream << getCppType(type);
			}
			if (arrayCount == 0)
			{
				stream << tabs(1) << depthName << cendl;
			}
		}
	}

}


