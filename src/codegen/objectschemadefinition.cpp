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

	void ObjectSchemaDefinition::construct_properties(std::vector<ExpansionPair>& toExpand, UInt32 arrayCount, UInt32 objectCount, JSON::Object::Ptr obj, ostringstream& stream, string depthName)
	{
		JSON::Object::Ptr properties = obj->getObject("properties");
		for (auto& property : *properties)
		{
			JSON::Object::Ptr propertyObject = property.second.extract<JSON::Object::Ptr>();
			++objectCount;
			construct(toExpand, arrayCount, objectCount, propertyObject, stream, property.first);
			--objectCount;
		}
	}

	void ObjectSchemaDefinition::construct(std::vector<ExpansionPair>& toExpand, UInt32 arrayCount, UInt32 objectCount, JSON::Object::Ptr obj, ostringstream& stream, string depthName, bool newObject)
	{
		string type = obj->get("type");
		if (isObject(type))
		{
			if (objectCount || arrayCount)
			{
				toExpand.emplace_back(depthName, obj);
				if (arrayCount)
				{
					stream << toExpand.back()._name;
				}
				else
				{
					stream << tabs(1) << depthName << std::cendl;
				}
			}
			else
			{
				if (newObject)
				{
					stream << "struct " << depthName << "{" << std::endl;
					construct_properties(toExpand, arrayCount, objectCount, obj, stream, depthName);
					stream << "};" << std::endl;
				}
				else
				{
					construct_properties(toExpand, arrayCount, objectCount, obj, stream, depthName);
				}
			}
		}
		else if (isArray(type))
		{
			JSON::Object::Ptr items = obj->getObject("items");
			stream << "std::vector<";
			++arrayCount;
			construct(toExpand, arrayCount, objectCount, items, stream, depthName);
			--arrayCount;
			stream << ">";
			if (arrayCount == 0)
			{
				stream << tabs(1) << depthName << std::cendl;
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
				stream << tabs(1) << depthName << std::cendl;
			}
		}
	}

	void ObjectSchemaDefinition::writeHeader(ApiFileOutputStream& header)
	{
		header << "void read(Poco::Dynamic::Var::Ptr val)" << cendl;
		header << endl;

		ostringstream tempStreamMembers, tempStreamStructs;
		std::vector<ExpansionPair> toExpand;
		construct(toExpand, 0, 0, rootObj, tempStreamMembers, "data");
		while (toExpand.size()) {
			ExpansionPair exPair = toExpand.front();
			toExpand.erase(toExpand.begin());
			construct(toExpand, 0, 0, exPair._obj, tempStreamStructs, exPair._name, true);
		};

		header << tempStreamStructs.str();
		header << tempStreamMembers.str();
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


