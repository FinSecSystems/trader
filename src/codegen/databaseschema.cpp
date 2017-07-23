#include "stdafx.h"

#include "config.h"
#include "fileoutputstream.h"
#include "endpoint.h"
#include "helpers.h"
#include "databaseschema.h"

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
	DatabaseSchema DatabaseSchema::instance;

	const char* getCppType(const string& dbType)
	{
		if (dbType.compare("INTEGER") == 0)
		{
			return "Poco::Int32";
		}
		else if (dbType.find("CHAR") != string::npos || dbType.find("TEXT") != string::npos)
		{
			return "std::string";
		}
		else if (dbType.compare("REAL") == 0)
		{
			return "double";
		}
		return nullptr;
	}

	const char* getCppDefaultVal(const string& dbType)
	{
		if (dbType.compare("INTEGER") == 0)
		{
			return "std::numeric_limits<Poco::Int32>::max()";
		}
		else if (dbType.find("CHAR") != string::npos || dbType.find("TEXT") != string::npos)
		{
			return "\"Empty\"";
		}
		else if (dbType.compare("REAL") == 0)
		{
			return "std::numeric_limits<double>::max()";
		}
		return nullptr;

	}

	void DatabaseSchema::process(const string& namespacename, const string& filename, const string& outputdirectory)
	{
		ostringstream ostr;
		FileInputStream fis(filename);
		StreamCopier::copyStream(fis, ostr);

		JSON::Parser parser;
		Dynamic::Var result = parser.parse(ostr.str());
		JSON::Object::Ptr api = result.extract<JSON::Object::Ptr>();
		JSON::Array::Ptr tables = api->getArray("tables");

		Config config;
		config.outputDir = outputdirectory;
		config.nameSpace = namespacename;
		getAPIName("database", filename, config.apiName);
		string apiFileName = config.apiName;
		std::transform(apiFileName.begin(), apiFileName.end(), apiFileName.begin(), ::tolower);
		config.headerFileName = outputdirectory + Path::separator() + apiFileName + ".h";
		config.cppFileName = outputdirectory + Path::separator() + apiFileName + ".cpp";

		string apiName;
		getAPIName("", filename, apiName);

		//Write

		ApiFileOutputStream header(config.headerFileName);
		ApiFileOutputStream cpp(config.cppFileName);

		startHeader(header, 0);
		{
			ScopedNamespace scopedNamesapce(header, config.nameSpace);
			for (auto& tableVar : *tables)
			{
				JSON::Object::Ptr table = tableVar.extract<JSON::Object::Ptr>();
				string name = table->getValue<std::string>("name");
				ostringstream nameStream;
				nameStream << type_name(name);

				JSON::Array::Ptr fields = table->getArray("fields");

				ScopedClass<1> scopedClass(header, nameStream.str().c_str(), "Poco::RefCountedObject");
				{
					{
						ScopedStruct<0, ApiFileOutputStream> scopedStruct(header, "Record");
						for (auto& fieldVar : *fields)
						{
							JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
							string fieldName = field->getValue<std::string>("name");
							string description = field->getValue<std::string>("description");
							string type = field->getValue<std::string>("type");
							header << "// " << description << endl;
							header << getCppType(type) << tabs(1) << var_name(fieldName) << cendl;
							header << endl;
							header << "bool isSet" << type_name(fieldName) << "() ";
							{
								ScopedStream<ApiFileOutputStream> isSetScope(header);
								header << "return (" << var_name(fieldName) << " != " << getCppDefaultVal(type) << ")" << cendl;
							}
						}

						header << "Record()" << endl;
						bool first = true;
						for (auto& fieldVar : *fields)
						{
							JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
							string fieldName = field->getValue<std::string>("name");
							string type = field->getValue<std::string>("type");
							if (first)
							{
								header << ": ";
							}
							else
							{
								header << ", ";
							}
							header << var_name(fieldName) << "(" << getCppDefaultVal(type) << ")" << endl;
							first = false;
						}
						{
							ScopedStream<ApiFileOutputStream> recordScope(header);
						}
					}
					header << endl;
					construct_header(header, nameStream.str().c_str(), 2,
						"Poco::Data::Session*", "_db"
						);
					header << "void init()" << cendl;
					header << endl;
					header << "void clear()" << cendl;
					header << endl;
					header << "void insert(" << nameStream.str() << "::Record& record)" << cendl;
					header << endl;
					header << "void insertOnce(" << nameStream.str() << "::Record& record)" << cendl;
					header << endl;
					header << "void insertMultiple(std::vector<" << nameStream.str() << "::Record>& records)" << cendl;
					header << endl;
					header << "void insertMultipleUnique(std::vector<" << nameStream.str() << "::Record>& records)" << cendl;
					header << endl;
					header << "void insertAndDeleteUnchanged(" << nameStream.str() << "::Record& record)" << cendl;
					header << endl;
					header << "void insertUnique(" << nameStream.str() << "::Record& record)" << cendl;
					header << endl;
					header << "void getLatest("<< nameStream.str() << "::Record& rec)" << cendl;
					header << endl;
					header << "Poco::Data::Session* db" << cendl;
					header << endl;
				}
			}

			{
				ScopedClass<1> scopedClass(header, config.apiName.c_str(), "Poco::RefCountedObject");
				construct_header(header, config.apiName.c_str(), 2,
					"Poco::Data::Session*", "_db"
				);
				header << "void init()" << cendl;
				header << endl;
				header << "void clear()" << cendl;
				header << endl;
				header << "Poco::Data::Session* db" << cendl;
				header << endl;
				for (auto& tableVar : *tables)
				{
					JSON::Object::Ptr table = tableVar.extract<JSON::Object::Ptr>();
					string name = table->getValue<std::string>("name");
					header << "Poco::AutoPtr<" << type_name(name) << "> " << var_name(name) << "Table" << cendl;
					header << endl;
				}
			}
		}
		header << endl;

		{//No namespace
			for (auto& tableVar : *tables)
			{
				JSON::Object::Ptr table = tableVar.extract<JSON::Object::Ptr>();
				string name = table->getValue<std::string>("name");
				ostringstream nameStream;
				nameStream << type_name(name);

				JSON::Array::Ptr fields = table->getArray("fields");

				header << "template <>" << endl;
				header << "class Poco::Data::TypeHandler<" << config.nameSpace << "::" << nameStream.str().c_str() << "::Record>" << endl;
				{
					ScopedStream<ApiFileOutputStream> typeHandlerScope(header);
					header << "public:" << endl;
					header << "static std::size_t size()" << endl;
					{
						ScopedStream<ApiFileOutputStream> sizeScope(header);
						header << "return " << (Poco::Int32)fields->size() << cendl;
					}
					header << endl;
					header << "static void bind(std::size_t pos, const " << config.nameSpace << "::" << type_name(nameStream.str()) << "::Record& record, Poco::Data::AbstractBinder::Ptr pBinder, Poco::Data::AbstractBinder::Direction dir)" << endl;
					{
						ScopedStream<ApiFileOutputStream> bindScope(header);
						for (auto& fieldVar : *fields)
						{
							JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
							string type = field->getValue<std::string>("type");
							string fieldName = field->getValue<std::string>("name");
							header << "Poco::Data::TypeHandler<" << getCppType(type) << ">::bind(pos++, record." << var_name(fieldName) << " , pBinder, dir)" << cendl;
						}
					}
					header << endl;
					header << "static void extract(std::size_t pos, " << config.nameSpace << "::" << type_name(nameStream.str()) << "::Record& record, " << config.nameSpace << "::" << type_name(nameStream.str()) << "::Record& deflt, Poco::Data::AbstractExtractor::Ptr pExtr)" << endl;
					{
						ScopedStream<ApiFileOutputStream> extractScope(header);
						for (auto& fieldVar : *fields)
						{
							JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
							string type = field->getValue<std::string>("type");
							string fieldName = field->getValue<std::string>("name");
							header << "Poco::Data::TypeHandler<" << getCppType(type) << ">::extract(pos++, record." << var_name(fieldName) << ", deflt." << var_name(fieldName) << ", pExtr)" << cendl;
						}
					}
					header << endl;
					header << "static void prepare(std::size_t pos, " << config.nameSpace << "::" << type_name(nameStream.str()) << "::Record& record, Poco::Data::AbstractPreparator::Ptr pPrep)" << endl;
					{
						ScopedStream<ApiFileOutputStream> extractScope(header);
						for (auto& fieldVar : *fields)
						{
							JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
							string type = field->getValue<std::string>("type");
							string fieldName = field->getValue<std::string>("name");
							header << "Poco::Data::TypeHandler<" << getCppType(type) << ">::prepare(pos++, record." << var_name(fieldName) << ", pPrep)" << cendl;
						}
					}
				}
				header << cendl;
				header << endl;
			}
		}

		startCpp(cpp, 2,
			config.headerFileName.c_str(),
			"trader/helper.h"
		);
		{
			ScopedNamespace scopedNamesapce(cpp, config.nameSpace);
			cpp << "using namespace Poco::Data::Keywords" << cendl;
			cpp << endl;

			construct_ex(cpp, config.apiName.c_str(), 2, 2, 0,
				"Poco::Data::Session*", "_db",
				"db", "_db");

			cpp << "void " << config.apiName << "::init()" << endl;
			{
				ScopedStream<ApiFileOutputStream> initStream(cpp);
				for (auto& tableVar : *tables)
				{
					JSON::Object::Ptr table = tableVar.extract<JSON::Object::Ptr>();
					string name = table->getValue<std::string>("name");
					cpp << var_name(name) << "Table = new " << type_name(name) << "(db)" << cendl;
					cpp << var_name(name) << "Table->init()" << cendl;
					cpp << endl;
				}
			}
			cpp << endl;

			cpp << "void " << config.apiName << "::clear()" << endl;
			{
				ScopedStream<ApiFileOutputStream> initStream(cpp);
				for (auto& tableVar : *tables)
				{
					JSON::Object::Ptr table = tableVar.extract<JSON::Object::Ptr>();
					string name = table->getValue<std::string>("name");
					cpp << var_name(name) << "Table->clear()" << cendl;
					cpp << endl;
				}
			}
			cpp << endl;

			for (auto& tableVar : *tables)
			{
				JSON::Object::Ptr table = tableVar.extract<JSON::Object::Ptr>();
				string name = table->getValue<std::string>("name");
				ostringstream nameStream;
				nameStream << type_name(name);
				
				JSON::Array::Ptr fields = table->getArray("fields");

				construct_ex(cpp, nameStream.str(), 2, 2, 0,
					"Poco::Data::Session*", "_db",
					"db", "_db");

				ostringstream keyStream;
				generateInit(cpp, nameStream, apiName, keyStream, table, fields, name);
				generateClear(cpp, nameStream, apiName, keyStream, table, fields, name);
				generateInsert(cpp, nameStream, apiName, keyStream, table, fields);
				generateInsertMultiple(cpp, nameStream, apiName, keyStream, table, fields);
				generateGetLatest(cpp, nameStream, apiName, keyStream, table, fields);
				generateInsertOnce(cpp, nameStream, apiName, keyStream, table, fields);
				generateInsertUnique(cpp, nameStream, apiName, keyStream, table, fields);
				generateInsertUniqueMultiple(cpp, nameStream, apiName, keyStream, table, fields);
				generateInsertAndDeleteUnchanged(cpp, nameStream, apiName, keyStream, table, fields);
				cpp << endl;
			}
		}
	}

	void DatabaseSchema::generateInit(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields, string& name)
	{
		cpp << "void " << nameStream.str() << "::init()" << endl;
		{
			ScopedStream<ApiFileOutputStream> initStream(cpp);
			// Create table
			cpp << "*db << \"CREATE TABLE IF NOT EXISTS " << apiName << "_" << name << " (";
			bool first = true;
			for (auto& fieldVar : *fields)
			{
				JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
				string type = field->getValue<std::string>("type");
				string fieldName = field->getValue<std::string>("name");
				if (!first)
				{
					cpp << ", ";
				}
				cpp << fieldName << " " << type;
				first = false;
			}
			cpp << ")\", now" << cendl;

			JSON::Array::Ptr primaryKeys = table->getArray("primaryKey");
			if (primaryKeys->size())
			{
				bool unique = true;
				for (auto& primaryKeyVar : *primaryKeys)
				{
					string primaryKeyField = primaryKeyVar.convert<string>();
					for (auto& fieldVar : *fields)
					{
						JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
						string fieldName = field->getValue<std::string>("name");
						if (fieldName.compare(primaryKeyField) == 0)
						{
							JSON::Object::Ptr constraints = field->getObject("constraints");
							Dynamic::Var uniqueVar = constraints->get("unique");
							if (!uniqueVar.isEmpty())
							{
								unique &= uniqueVar.convert<bool>();
							}
							if (keyStream.str().length())
							{
								keyStream << ", ";
							}
							keyStream << primaryKeyField;
							break;
						}
					}
				}
				if (keyStream.str().length())
				{
					cpp << "*db << \"CREATE " << (unique ? "UNIQUE" : "") << " INDEX IF NOT EXISTS " << apiName << "_" << name << "_Index on " << apiName << "_" << name << "(" << keyStream.str() << ")\", now" << cendl;
				}
			}
		}
		cpp << endl;
	}

	void DatabaseSchema::generateClear(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields, string& name)
	{
		(void)keyStream;
		(void)apiName;
		cpp << "void " << nameStream.str() << "::clear()" << endl;
		{
			ScopedStream<ApiFileOutputStream> clearStream(cpp);
			cpp << "*db << \"DELETE FROM "  << apiName << "_" << name << "\", now" << cendl;
			cpp << "*db << \"VACUUM\", now" << cendl;
		}
		cpp << endl;
	}

	void DatabaseSchema::generateInsert(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields)
	{
		(void)keyStream;
		cpp << "void " << nameStream.str() << "::insert(" << nameStream.str() << "::Record& record)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);
			JSON::Array::Ptr primaryKeys = table->getArray("primaryKey");
			cpp << "Poco::Data::Statement insert(*db)" << cendl;
			cpp << "insert << \"INSERT INTO " << apiName << "_" << type_name(nameStream.str()) << " VALUES(";
			for (Poco::UInt32 cnt = 0; cnt < fields->size(); cnt++)
			{
				if (cnt != 0) cpp << ", ";
				cpp << "?";
			}
			cpp << ")\"" << endl;
			for (auto& fieldVar : *fields)
			{
				JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
				string fieldName = field->getValue<std::string>("name");
				cpp << tabs(1) << ", use(record." << var_name(fieldName) << ")" << endl;
			}
			cpp << ", now" << cendl;
			cpp << "insert.execute()" << cendl;
		}
		cpp << endl;
	}

	void DatabaseSchema::generateInsertAndDeleteUnchanged(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields)
	{
		cpp << "void " << nameStream.str() << "::insertAndDeleteUnchanged(" << nameStream.str() << "::Record& record)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);
			JSON::Array::Ptr primaryKeys = table->getArray("primaryKey");
			if (primaryKeys->size())
			{
				cpp << "std::vector<" << type_name(nameStream.str()) << "::Record> " << var_name(nameStream.str()) << cendl;
				cpp << "*db << \"SELECT * FROM " << apiName << "_" << type_name(nameStream.str()) << " ORDER BY " << keyStream.str() << " DESC LIMIT 1\"," << endl;
				cpp << tabs(1) << "into(" << var_name(nameStream.str()) << ")," << endl;
				cpp << tabs(1) << "now" << cendl;
				cpp << endl;

				cpp << "if (";
				bool firstVar = true;
				for (auto& fieldVar : *fields)
				{
					JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
					string fieldName = field->getValue<std::string>("name");
					if (!firstVar)
					{
						cpp << " || ";
					}
					cpp << "!record.isSet" << type_name(fieldName) << "()";
					firstVar = false;
				}
				cpp << ")" << endl;
				{
					ScopedStream<ApiFileOutputStream> ifSetStream(cpp);
					cpp << "return" << cendl;
				}
				cpp << "if (!" << var_name(nameStream.str()) << ".empty())" << endl;
				{
					ScopedStream<ApiFileOutputStream> ifStream(cpp);
					cpp << "if(";
					bool first = true;
					for (auto& fieldVar : *fields)
					{
						JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
						string type = field->getValue<std::string>("type");
						string fieldName = field->getValue<std::string>("name");
						if (keyStream.str().find(fieldName) == string::npos)
						{
							if (!first)
							{
								cpp << " && ";
							}
							cpp << "equal<" << getCppType(type) << ">(" << var_name(nameStream.str()) << "[0]." << var_name(fieldName) << ", record." << var_name(fieldName) << ")" << endl;
							first = false;
						}
					}
					cpp << ")" << endl;
					{
						ScopedStream<ApiFileOutputStream> ifNotEmptyStream(cpp);
						cpp << "*db << \"DELETE FROM " << apiName << "_" << var_name(nameStream.str()) << " WHERE " << type_name(keyStream.str()) << " = ?\"," << endl;
						cpp << tabs(1) << "use(" << var_name(nameStream.str()) << "[0]." << var_name(keyStream.str()) << ")," << endl;
						cpp << tabs(1) << "now" << cendl;
					}
				}
				cpp << endl;
				cpp << "Poco::Data::Statement insert(*db)" << cendl;
				cpp << "insert << \"INSERT INTO " << apiName << "_" << type_name(nameStream.str()) << " VALUES(";
				for (Poco::UInt32 cnt = 0; cnt < fields->size(); cnt++)
				{
					if (cnt != 0) cpp << ", ";
					cpp << "?";
				}
				cpp << ")\"" << endl;
				for (auto& fieldVar : *fields)
				{
					JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
					string fieldName = field->getValue<std::string>("name");
					cpp << tabs(1) << ", use(record." << var_name(fieldName) << ")" << endl;
				}
				cpp << cendl;
				cpp << "insert.execute()" << cendl;
			}
			else
			{
				cpp << "(void)record" << cendl;
			}
		}
	}

	void DatabaseSchema::generateInsertOnce(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields)
	{
		(void)keyStream;
		cpp << "void " << nameStream.str() << "::insertOnce(" << nameStream.str() << "::Record& record)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);

			cpp << "Poco::UInt32 count" << cendl;
			cpp << "*db << \"SELECT count(*) FROM " << apiName << "_" << type_name(nameStream.str()) << "\"," << endl;
			cpp << tabs(1) << "into(count)," << endl;
			cpp << tabs(1) << "now" << cendl;
			cpp << endl;
			
			cpp << "if (!count)" << endl;
			{
				ScopedStream<ApiFileOutputStream> ifCountStream(cpp);
				cpp << "Poco::Data::Statement insert(*db)" << cendl;
				cpp << "insert << \"INSERT INTO " << apiName << "_" << type_name(nameStream.str()) << " VALUES(";
				for (Poco::UInt32 cnt = 0; cnt < fields->size(); cnt++)
				{
					if (cnt != 0) cpp << ", ";
					cpp << "?";
				}
				cpp << ")\"" << endl;
				for (auto& fieldVar : *fields)
				{
					JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
					string fieldName = field->getValue<std::string>("name");
					cpp << tabs(1) << ", use(record." << var_name(fieldName) << ")" << endl;
				}
				cpp << cendl;
				cpp << "insert.execute()" << cendl;
			}
		}
		cpp << endl;
	}

	void DatabaseSchema::generateInsertUnique(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields)
	{
		(void)keyStream;
		cpp << "void " << nameStream.str() << "::insertUnique(" << nameStream.str() << "::Record& record)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);

			JSON::Array::Ptr primaryKeys = table->getArray("primaryKey");
			if (primaryKeys->size())
			{
				cpp << "Poco::UInt32 count" << cendl;
				cpp << "*db << \"SELECT count(*) FROM " << apiName << "_" << type_name(nameStream.str()) << " WHERE " << type_name(keyStream.str()) << " = ?\"," << endl;
				cpp << tabs(1) << "use(record." << var_name(keyStream.str()) << ")," << endl;
				cpp << tabs(1) << "into(count)," << endl;
				cpp << tabs(1) << "now" << cendl;
				cpp << endl;

				cpp << "if (!count)" << endl;
				{
					ScopedStream<ApiFileOutputStream> ifCountStream(cpp);
					cpp << "Poco::Data::Statement insert(*db)" << cendl;
					cpp << "insert << \"INSERT INTO " << apiName << "_" << type_name(nameStream.str()) << " VALUES(";
					for (Poco::UInt32 cnt = 0; cnt < fields->size(); cnt++)
					{
						if (cnt != 0) cpp << ", ";
						cpp << "?";
					}
					cpp << ")\"" << endl;
					for (auto& fieldVar : *fields)
					{
						JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
						string fieldName = field->getValue<std::string>("name");
						cpp << tabs(1) << ", use(record." << var_name(fieldName) << ")" << endl;
					}
					cpp << cendl;
					cpp << "insert.execute()" << cendl;
				}
			}
			else
			{
				cpp << "(void)record" << cendl;
			}
		}
		cpp << endl;
	}

	void DatabaseSchema::generateInsertMultiple (ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields)
	{
		(void)keyStream;
		(void)apiName;
		cpp << "void " << nameStream.str() << "::insertMultiple(std::vector<" << nameStream.str() << "::Record>& records)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);
			JSON::Array::Ptr primaryKeys = table->getArray("primaryKey");
			cpp << "Poco::Data::Statement insert(*db)" << cendl;
			cpp << "insert << \"INSERT INTO " << apiName << "_" << type_name(nameStream.str()) << " VALUES(";
			for (Poco::UInt32 cnt = 0; cnt < fields->size(); cnt++)
			{
				if (cnt != 0) cpp << ", ";
				cpp << "?";
			}
			cpp << ")\"" << endl;
			cpp << ", use(records)" << endl;
			cpp << ", now" << cendl;
			cpp << "insert.execute()" << cendl;
		}
		cpp << endl;
	}

	void DatabaseSchema::generateInsertUniqueMultiple(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields)
	{
		(void)keyStream;
		(void)apiName;
		cpp << "void " << nameStream.str() << "::insertMultipleUnique(std::vector<" << nameStream.str() << "::Record>& records)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);
			cpp << "for (auto& record : records)" << endl;
			{
				ScopedStream<ApiFileOutputStream> forEachStream(cpp);
				cpp << "insertUnique(record)" << cendl;
			}
		}
		cpp << endl;
	}

	void DatabaseSchema::generateGetLatest(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields)
	{
		(void)apiName;
		(void)keyStream;
		cpp << "void " << nameStream.str() << "::getLatest(" << nameStream.str() << "::Record& rec)" << endl;
		{
			ScopedStream<ApiFileOutputStream> getLatestStream(cpp);
			JSON::Array::Ptr primaryKeys = table->getArray("primaryKey");
			cpp << "std::vector<" << type_name(nameStream.str()) << "::Record> " << var_name(nameStream.str()) << cendl;
			if (primaryKeys->size())
			{
				cpp << "*db << \"SELECT * FROM " << apiName << "_" << type_name(nameStream.str()) << " ORDER BY " << keyStream.str() << " DESC LIMIT 1\"," << endl;
			}
			else
			{
				cpp << "*db << \"SELECT * FROM " << apiName << "_" << type_name(nameStream.str()) << " ORDER BY ROWID ASC LIMIT 1\"," << endl;
			}
			cpp << tabs(1) << "into(" << var_name(nameStream.str()) << ")," << endl;
			cpp << tabs(1) << "now" << cendl;
			cpp << endl;
			cpp << "if (!" << var_name(nameStream.str()) << ".empty())" << endl;
			{
				ScopedStream<ApiFileOutputStream> emptyStream(cpp);
				cpp << "rec = " << var_name(nameStream.str()) << "[0]" << cendl;
			}
		}
		cpp << endl;
	}

}