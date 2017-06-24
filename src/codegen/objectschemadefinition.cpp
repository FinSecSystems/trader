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


	void ObjectSchemaDefinition::cppConstruct(UInt32 arrayCount, UInt32 objectCount, JSON::Object::Ptr obj, ApiFileOutputStream& stream, string depthName, string anonymousName)
	{
		string type = obj->get("type");
		if (isObject(type))
		{
			anonymousName += "Object";
			JSON::Object::Ptr properties = obj->getObject("properties");
			stream << "Poco::JSON::Object::Ptr obj = val->extract<Poco::JSON::Object::Ptr>()" << cendl;
			for (auto& property : *properties)
			{
				JSON::Object::Ptr propertyObject = property.second.extract<JSON::Object::Ptr>();
				++objectCount;
				cppConstruct(arrayCount, objectCount, propertyObject, stream, property.first, anonymousName);
				--objectCount;
			}
		}
		else if (isArray(type))
		{
			anonymousName += "Array";
			JSON::Object::Ptr items = obj->getObject("items");
			stream << "Poco::JSON::Array::Ptr obj = val->extract<Poco::JSON::Array::Ptr>()" << cendl;
			stream << "for (Poco::JSON::Array::Iterator it = obj->begin(); it != obj->end(); ++it)" << endl;
			{
				ScopedStream<ApiFileOutputStream> scopedStream(stream);
				stream << ".emplace_back()";
				++arrayCount;
				cppConstruct(arrayCount, objectCount, items, stream, depthName, anonymousName);
				--arrayCount;
				stream << depthName << ".push_back(" << depthName << "Array->getElement<>(idx))" << cendl;
			}

			/*		Poco::JSON::Array::Ptr obj = val->extract<Poco::JSON::Array::Ptr>();
		for (Poco::JSON::Array::Iterator it = obj->begin(); it != obj->end(); ++it)
		{
			data.emplace_back();
			ArrayObject& arrayObject = data.back();
			Poco::JSON::Object::Ptr obj = it->extract<Poco::JSON::Object::Ptr>();
			arrayObject.amount = obj->getValue<double>("amount");
			arrayObject.date = obj->getValue<Poco::Int32>("date");
			arrayObject.price = obj->getValue<double>("price");
			arrayObject.tid = obj->getValue<Poco::Int32>("tid");
		}*/
		}
		else
		{
			stream << depthName << " = obj->getValue<" << getCppType(type) << ">(\"" << depthName << "\")" << cendl;
		}
	}


	void ObjectSchemaDefinition::writeCpp(ApiFileOutputStream& cpp)
	{
		cpp << "void " << name << "::read(Poco::Dynamic::Var::Ptr val) ";
		{
			ScopedStream<ApiFileOutputStream> scopedStream(cpp);
			cppConstruct(0, 0, rootObj, cpp, "data", "");
		}
		
		/*
		cpp << "void " << name << "::read(Poco::Dynamic::Var::Ptr val) ";
		{
			ScopedStream stream(cpp);
			std::vector<string> propertyNames;
			rootObj->getNames(propertyNames);
			for (auto& propertyName : propertyNames)
			{
				JSON::Object::Ptr propertyVal = rootObj->getObject(propertyName);
				string type = propertyVal->get("type");
				const char* cppType = getCppType(type);
				if (cppType)
				{
					cpp << propertyName << " = val->getValue<" << cppType << ">(\"" << propertyName << "\")" << cendl;
				}
				else if (isArray(type))
				{
					JSON::Object::Ptr items = propertyVal->getObject("items");
					string type = items->get("type");
					const char* cppType = getCppType(type);
					if (cppType)
					{
						cpp << "JSON::Array::Ptr " << propertyName << "Array = val->getArray(\"" << propertyName << "\")" << cendl;
						cpp << "for (UInt32 idx = 0; idx < " << propertyName << "Array->size(); ++idx)" << endl;
						{
							ScopedStream stream(cpp);
							cpp << propertyName << ".push_back(" << propertyName << "Array->getElement<" << cppType << ">(idx))" << cendl;
						}
					}
					else if (isArray(type))
					{
						JSON::Object::Ptr innerItems = items->getObject("items");
						string type = innerItems->get("type");
						const char* cppType = getCppType(type);
						cpp << "JSON::Array::Ptr " << propertyName << "Array = val->getArray(\"" << propertyName << "\")" << cendl;
						cpp << "for (UInt32 idx = 0; idx < " << propertyName << "Array->size(); ++idx)" << endl;
						{
							ScopedStream stream(cpp);
							cpp << "JSON::Array::Ptr inner" << propertyName << "Array = " << propertyName << "Array->getArray(idx)" << cendl;
							cpp << "std::vector<" << cppType << "> inner" << propertyName << cendl;
							cpp << "for (UInt32 innerIdx = 0; innerIdx < inner" << propertyName << "Array->size(); ++innerIdx)" << endl;
							{
								ScopedStream stream(cpp);
								cpp << "inner" << propertyName << ".push_back(inner" << propertyName << "Array->getElement<" << cppType << ">(innerIdx))" << cendl;
							}
							cpp << propertyName << ".push_back(inner" << propertyName << ")" << cendl;							}
					}
				}
			}
		}
		*/
		cpp << endl;
	}

	void ObjectSchemaDefinition::headerConstructProperties(std::vector<ExpansionPair>& toExpand, UInt32 arrayCount, UInt32 objectCount, JSON::Object::Ptr obj, ApiStreamBuffer& stream, string depthName, string anoymousName )
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
				stream << tabs(1) << depthName <<cendl;
			}
		}
	}

	void ObjectSchemaDefinition::writeHeader(ApiFileOutputStream& header)
	{
		header << "void read(Poco::Dynamic::Var::Ptr val)" << cendl;
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
	}

}


