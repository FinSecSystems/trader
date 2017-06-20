#include "stdafx.h"

#include "config.h"
#include "fileoutputstream.h"
#include "endpoint.h"
#include "utils.h"
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
			return "Int32";
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

	void ObjectSchemaDefinition::writeCpp(ApiFileOutputStream& cpp)
	{/*
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

	void ObjectSchemaDefinition::construct(std::vector<ExpansionPair>& toExpand, UInt32 arrayCount, UInt32 objectCount, JSON::Object::Ptr obj, ApiFileOutputStream& stream, string depthName)
	{
		string type = obj->get("type");
		if (isObject(type))
		{
			JSON::Object::Ptr properties = obj->getObject("properties");
			for (auto& property : *properties)
			{
				JSON::Object::Ptr propertyObject = property.second.extract<JSON::Object::Ptr>();
				if (objectCount || arrayCount)
				{
					toExpand.emplace_back(property.first, propertyObject);
					stream << toExpand.back()._name;
					if (arrayCount == 0)
					{
						stream << tabs(1) << property.first << cendl;
					}
				}
				else
				{
					++objectCount;
					construct(toExpand, arrayCount, objectCount, propertyObject, stream, property.first);
					--objectCount;
				}
			}
		}
		else if (isArray(type))
		{
			JSON::Object::Ptr items = obj->getObject("items");
			stream << "std::vector<";
			++arrayCount;
			construct(toExpand, arrayCount, objectCount, items, stream, "");
			--arrayCount;
			stream << "> ";
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

	void ObjectSchemaDefinition::writeHeader(ApiFileOutputStream& header)
	{
		header << "void read(Poco::Dynamic::Var::Ptr val)" << cendl;
		header << endl;

		header << "//Test" << endl;
		std::vector<ExpansionPair> toExpand;
		construct(toExpand, 0, 0, rootObj, header, "");
		while (toExpand.size()) {
			ExpansionPair exPair = toExpand.front();
			toExpand.erase(toExpand.begin());
			construct(toExpand, 0, 0, exPair._obj, header, exPair._name);
		};
		header << "//Test" << endl;
		/*
		vector<string> propertyNames;
		rootObj->getNames(propertyNames);
		for (auto& it : propertyNames)
		{
			JSON::Object::Ptr propertyVal = rootObj->getObject(it);
			string type = propertyVal->get("type");
			const char* cppType = getCppType(type);
			if (cppType)
			{
				header << cppType << tabs(1) << it << cendl;
			}
			else if (isArray(type))
			{
				JSON::Object::Ptr items = propertyVal->getObject("items");
				string type = items->get("type");
				const char* cppType = getCppType(type);
				if (cppType)
				{
					header << "std::vector<" << cppType << "> " << tabs(1) << it << cendl;
				}
				else if (isArray(type))
				{
					JSON::Object::Ptr innerItems = items->getObject("items");
					string type = innerItems->get("type");
					const char* cppType = getCppType(type);
					header << "std::vector<std::vector<" << cppType << ">> " << tabs(1) << it << cendl;
				}
			}
		}
		*/
	}

}


