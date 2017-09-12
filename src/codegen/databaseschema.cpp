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
			ScopedNamespace scopedNamespaceTrader(header, config.nameSpace);
            {
                ScopedNamespace scopedNamespaceDb(header, config.apiName);

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
                                header << endl;
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
                        {
                            ScopedStruct<0, ApiFileOutputStream> scopedStruct(header, "RecordWithId");
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
                                header << endl;
                            }

                            header << "//Record ID in database" << endl;
                            header << getCppType("INTEGER") << tabs(1) << "id" << cendl;
                            header << endl;

                            header << "RecordWithId()" << endl;
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
                            header << (first ? ": " : ", ");
                            header << "id(" << getCppDefaultVal("INTEGER") << ")" << endl;
                            {
                                ScopedStream<ApiFileOutputStream> recordScope(header);
                            }
                        }
                        header << endl;
                        construct_header(header, nameStream.str().c_str(), 4,
                            "Poco::Data::Session*", "_db",
                            "std::string", "_suffix = \"\""
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
                        header << "void insertMultiple(std::vector<" << nameStream.str() << "::RecordWithId>& records)" << cendl;
                        header << endl;
                        header << "void insertMultipleUnique(std::vector<" << nameStream.str() << "::Record>& records)" << cendl;
                        header << endl;
                        header << "void deleteMultiple(std::vector<" << nameStream.str() << "::RecordWithId>& records)" << cendl;
                        header << endl;
                        header << "void insertAndDeleteUnchanged(" << nameStream.str() << "::Record& record)" << cendl;
                        header << endl;
                        header << "void insertUnique(" << nameStream.str() << "::Record& record)" << cendl;
                        header << endl;
                        header << "void getLatest(" << nameStream.str() << "::RecordWithId& rec)" << cendl;
                        header << endl;
                        header << "std::size_t getAll(std::vector<" << nameStream.str() << "::RecordWithId>& records, std::string condition)" << cendl;
                        header << endl;
                        header << "Poco::Data::Session* db" << cendl;
                        header << endl;
                        header << "std::string tableName" << cendl;
                        header << endl;
                    }
                }

                {
                    ScopedClass<1> scopedClass(header, "Tables", "Poco::RefCountedObject");
                    construct_header(header, "Tables", 2,
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
				header << "class Poco::Data::TypeHandler<" << config.nameSpace << "::" << config.apiName << "::" << nameStream.str().c_str() << "::Record>" << endl;
				{
					ScopedStream<ApiFileOutputStream> typeHandlerScope(header);
					header << "public:" << endl;
					header << "static std::size_t size()" << endl;
					{
						ScopedStream<ApiFileOutputStream> sizeScope(header);
						header << "return " << (Poco::Int32)fields->size() << cendl;
					}
					header << endl;
					header << "static void bind(std::size_t pos, const " << config.nameSpace << "::" << config.apiName << "::" << type_name(nameStream.str()) << "::Record& record, Poco::Data::AbstractBinder::Ptr pBinder, Poco::Data::AbstractBinder::Direction dir)" << endl;
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
					header << "static void extract(std::size_t pos, " << config.nameSpace << "::" << config.apiName << "::" << type_name(nameStream.str()) << "::Record& record, " << config.nameSpace << "::" << config.apiName << "::" << type_name(nameStream.str()) << "::Record& deflt, Poco::Data::AbstractExtractor::Ptr pExtr)" << endl;
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
					header << "static void prepare(std::size_t pos, " << config.nameSpace << "::" << config.apiName << "::" << type_name(nameStream.str()) << "::Record& record, Poco::Data::AbstractPreparator::Ptr pPrep)" << endl;
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

				header << "template <>" << endl;
				header << "class Poco::Data::TypeHandler<" << config.nameSpace << "::" << config.apiName << "::" << nameStream.str().c_str() << "::RecordWithId>" << endl;
				{
					ScopedStream<ApiFileOutputStream> typeHandlerScope(header);
					header << "public:" << endl;
					header << "static std::size_t size()" << endl;
					{
						ScopedStream<ApiFileOutputStream> sizeScope(header);
						header << "return " << (Poco::Int32)fields->size() + 1 << cendl;
					}
					header << endl;
					header << "static void bind(std::size_t pos, const " << config.nameSpace << "::" << config.apiName << "::" << type_name(nameStream.str()) << "::RecordWithId& record, Poco::Data::AbstractBinder::Ptr pBinder, Poco::Data::AbstractBinder::Direction dir)" << endl;
					{
						ScopedStream<ApiFileOutputStream> bindScope(header);
						for (auto& fieldVar : *fields)
						{
							JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
							string type = field->getValue<std::string>("type");
							string fieldName = field->getValue<std::string>("name");
							header << "Poco::Data::TypeHandler<" << getCppType(type) << ">::bind(pos++, record." << var_name(fieldName) << " , pBinder, dir)" << cendl;
						}
						header << "Poco::Data::TypeHandler<" << getCppType("INTEGER") << ">::bind(pos++, record.id, pBinder, dir)" << cendl;
					}
					header << endl;
					header << "static void extract(std::size_t pos, " << config.nameSpace << "::" << config.apiName << "::" << type_name(nameStream.str()) << "::RecordWithId& record, " << config.nameSpace << "::" << config.apiName << "::" << type_name(nameStream.str()) << "::RecordWithId& deflt, Poco::Data::AbstractExtractor::Ptr pExtr)" << endl;
					{
						ScopedStream<ApiFileOutputStream> extractScope(header);
						for (auto& fieldVar : *fields)
						{
							JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
							string type = field->getValue<std::string>("type");
							string fieldName = field->getValue<std::string>("name");
							header << "Poco::Data::TypeHandler<" << getCppType(type) << ">::extract(pos++, record." << var_name(fieldName) << ", deflt." << var_name(fieldName) << ", pExtr)" << cendl;
						}
						header << "Poco::Data::TypeHandler<" << getCppType("INTEGER") << ">::extract(pos++, record.id, deflt.id, pExtr)" << cendl;
					}
					header << endl;
					header << "static void prepare(std::size_t pos, " << config.nameSpace << "::" << config.apiName << "::" << type_name(nameStream.str()) << "::RecordWithId& record, Poco::Data::AbstractPreparator::Ptr pPrep)" << endl;
					{
						ScopedStream<ApiFileOutputStream> extractScope(header);
						for (auto& fieldVar : *fields)
						{
							JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
							string type = field->getValue<std::string>("type");
							string fieldName = field->getValue<std::string>("name");
							header << "Poco::Data::TypeHandler<" << getCppType(type) << ">::prepare(pos++, record." << var_name(fieldName) << ", pPrep)" << cendl;
						}
						header << "Poco::Data::TypeHandler<" << getCppType("INTEGER") << ">::prepare(pos++, record.id, pPrep)" << cendl;
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
            ScopedNamespace scopedNamespace(cpp, config.nameSpace);
            cpp << "using namespace Poco::Data::Keywords" << cendl;
            cpp << endl;
            {
                ScopedNamespace scopedDb(cpp, config.apiName);

                construct_ex(cpp, "Tables", 2, 2, 0,
                    "Poco::Data::Session*", "_db",
                    "db", "_db");

                cpp << "void Tables::init()" << endl;
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

                cpp << "void Tables::clear()" << endl;
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
                    std::ostringstream tableNameStr;
                    tableNameStr << "tableNameStr << \"" << apiName << "_" << name << "\";";

                    ostringstream nameStream;
                    nameStream << type_name(name);

                    JSON::Array::Ptr fields = table->getArray("fields");

                    construct_ex(cpp, nameStream.str(), 4, 2, 4,
                        "Poco::Data::Session*", "_db",
                        "std::string", "_suffix",
                        "db", "_db",
                        "std::ostringstream tableNameStr;",
                        tableNameStr.str().c_str(),
                        "if (_suffix.length()) tableNameStr << \"_\" << _suffix;",
                        "tableName = tableNameStr.str();"
                    );

                    ostringstream keyStream;
                    generateInit(cpp, nameStream, apiName, keyStream, table, fields, name);
                    generateClear(cpp, nameStream, apiName, keyStream, table, fields, name);
                    generateInsert(cpp, nameStream, apiName, keyStream, table, fields);
                    generateInsertMultiple(cpp, nameStream, apiName, keyStream, table, fields);
                    generateDeleteMultiple(cpp, nameStream, apiName, keyStream, table, fields);
                    generateGetLatest(cpp, nameStream, apiName, keyStream, table, fields);
                    generateGetAll(cpp, nameStream, apiName, keyStream, table, fields);
                    generateInsertOnce(cpp, nameStream, apiName, keyStream, table, fields);
                    generateInsertUnique(cpp, nameStream, apiName, keyStream, table, fields);
                    generateInsertUniqueMultiple(cpp, nameStream, apiName, keyStream, table, fields);
                    generateInsertAndDeleteUnchanged(cpp, nameStream, apiName, keyStream, table, fields);
                    cpp << endl;
                }
            }
        }
	}

	void DatabaseSchema::generateInit(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields, string& name)
	{
		(void)apiName;
		(void)name;
		cpp << "void " << nameStream.str() << "::init()" << endl;
		{
			ScopedStream<ApiFileOutputStream> initStream(cpp);
			// Create table
            cpp << "Logger::get(\"Logs\").information(\"DB Check and Create : %s\", tableName)" << cendl;
			cpp << "*db << \"CREATE TABLE IF NOT EXISTS \\\"\" << tableName << \"\\\" (";
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
					cpp << "*db << \"CREATE " << (unique ? "UNIQUE" : "") << " INDEX IF NOT EXISTS \\\"\" << tableName << \"_Index\\\" on \\\"\" << tableName << \"\\\"(" << keyStream.str() << ")\", now" << cendl;
				}
			}
		}
		cpp << endl;
	}

	void DatabaseSchema::generateClear(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields, string& name)
	{
		(void)keyStream;
		(void)apiName;
		(void)name;
		cpp << "void " << nameStream.str() << "::clear()" << endl;
		{
			ScopedStream<ApiFileOutputStream> clearStream(cpp);
            cpp << "Logger::get(\"Logs\").information(\"DB Clear : %s\", tableName)" << cendl;
			cpp << "*db << \"DELETE FROM \\\"\" << tableName << \"\\\"\", now" << cendl;
			cpp << "*db << \"VACUUM\", now" << cendl;
		}
		cpp << endl;
	}

	void DatabaseSchema::generateInsert(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields)
	{
		(void)keyStream;
		(void)apiName;
		cpp << "void " << nameStream.str() << "::insert(" << nameStream.str() << "::Record& record)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);
			JSON::Array::Ptr primaryKeys = table->getArray("primaryKey");
            cpp << "Logger::get(\"Logs\").information(\"DB Insert : %s\", tableName)" << cendl;
			cpp << "Poco::Data::Statement insert(*db)" << cendl;
			cpp << "insert << \"INSERT INTO \\\"\" << tableName << \"\\\" VALUES(";
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
		(void)apiName;
		cpp << "void " << nameStream.str() << "::insertAndDeleteUnchanged(" << nameStream.str() << "::Record& record)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);
            cpp << "Logger::get(\"Logs\").information(\"DB Insert and Delete Unchanged : %s\", tableName)" << cendl;
            JSON::Array::Ptr primaryKeys = table->getArray("primaryKey");
			if (primaryKeys->size())
			{
				cpp << "std::vector<" << type_name(nameStream.str()) << "::Record> " << var_name(nameStream.str()) << cendl;
				cpp << "*db << \"SELECT * FROM \\\"\" << tableName << \"\\\" ORDER BY " << keyStream.str() << " DESC LIMIT 1\"," << endl;
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
						cpp << "*db << \"DELETE FROM \\\"\" << tableName << \"\\\" WHERE " << type_name(keyStream.str()) << " = ?\"," << endl;
						cpp << tabs(1) << "use(" << var_name(nameStream.str()) << "[0]." << var_name(keyStream.str()) << ")," << endl;
						cpp << tabs(1) << "now" << cendl;
					}
				}
				cpp << endl;
				cpp << "Poco::Data::Statement insert(*db)" << cendl;
				cpp << "insert << \"INSERT INTO \\\"\" << tableName << \"\\\" VALUES(";
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
		(void)apiName;
		(void)keyStream;
		cpp << "void " << nameStream.str() << "::insertOnce(" << nameStream.str() << "::Record& record)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);
            cpp << "Logger::get(\"Logs\").information(\"DB Insert Once : %s\", tableName)" << cendl;
			cpp << "Poco::UInt32 count" << cendl;
			cpp << "*db << \"SELECT count(*) FROM \\\"\" << tableName << \"\\\"\"," << endl;
			cpp << tabs(1) << "into(count)," << endl;
			cpp << tabs(1) << "now" << cendl;
			cpp << endl;
			
			cpp << "if (!count)" << endl;
			{
				ScopedStream<ApiFileOutputStream> ifCountStream(cpp);
				cpp << "Poco::Data::Statement insert(*db)" << cendl;
				cpp << "insert << \"INSERT INTO \\\"\" << tableName << \"\\\" VALUES(";
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
		(void)apiName;
		(void)keyStream;
		cpp << "void " << nameStream.str() << "::insertUnique(" << nameStream.str() << "::Record& record)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);

			JSON::Array::Ptr primaryKeys = table->getArray("primaryKey");
			if (primaryKeys->size())
			{
                cpp << "Logger::get(\"Logs\").information(\"DB Insert Unique : %s\", tableName)" << cendl;
				cpp << "Poco::UInt32 count" << cendl;
				cpp << "*db << \"SELECT count(*) FROM \\\"\" << tableName << \"\\\" WHERE " << type_name(keyStream.str()) << " = ?\"," << endl;
				cpp << tabs(1) << "use(record." << var_name(keyStream.str()) << ")," << endl;
				cpp << tabs(1) << "into(count)," << endl;
				cpp << tabs(1) << "now" << cendl;
				cpp << endl;

				cpp << "if (!count)" << endl;
				{
					ScopedStream<ApiFileOutputStream> ifCountStream(cpp);
					cpp << "Poco::Data::Statement insert(*db)" << cendl;
					cpp << "insert << \"INSERT INTO \\\"\" << tableName << \"\\\" VALUES(";
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
            cpp << "Logger::get(\"Logs\").information(\"DB Insert Multiple : %s\", tableName)" << cendl;
			cpp << "if (records.empty()) return" << cendl;
			cpp << "Poco::Data::Statement insert(*db)" << cendl;
			cpp << "insert << \"INSERT INTO \\\"\" << tableName << \"\\\" VALUES(";
			for (Poco::UInt32 cnt = 0; cnt < fields->size(); cnt++)
			{
				if (cnt != 0) cpp << ", ";
				cpp << "?";
			}
			cpp << ")\"" << endl;
			cpp << ", use(records)" << endl;
			cpp << ", now" << cendl;
		}
		cpp << endl;
		cpp << "void " << nameStream.str() << "::insertMultiple(std::vector<" << nameStream.str() << "::RecordWithId>& recordWithIds)" << endl;
		{
			ScopedStream<ApiFileOutputStream> insertStream(cpp);
            cpp << "Logger::get(\"Logs\").information(\"DB Insert Multiple with Ids : %s\", tableName)" << cendl;
			cpp << "if (recordWithIds.empty()) return" << cendl;
			cpp << "Poco::Data::Statement insert(*db)" << cendl;
			cpp << "std::vector<" << nameStream.str() << "::Record> records" << cendl;
			cpp << "for(auto& recWithId : recordWithIds)" << endl;
			{
				ScopedStream<ApiFileOutputStream> convertStream(cpp);
				cpp << nameStream.str() << "::Record record" << cendl;
				for (auto& fieldVar : *fields)
				{
					JSON::Object::Ptr field = fieldVar.extract<JSON::Object::Ptr>();
					string fieldName = field->getValue<std::string>("name");
					cpp << "record." << var_name(fieldName) << " = recWithId." << var_name(fieldName) << cendl;
				}
				cpp << "records.push_back(record)" << cendl;
			}
			cpp << "insert << \"INSERT INTO \\\"\" << tableName << \"\\\" VALUES(";
			for (Poco::UInt32 cnt = 0; cnt < fields->size(); cnt++)
			{
				if (cnt != 0) cpp << ", ";
				cpp << "?";
			}
			cpp << ")\"" << endl;
			cpp << ", use(records)" << endl;
			cpp << ", now" << cendl;
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
            cpp << "Logger::get(\"Logs\").information(\"DB Insert Multiple Unique : %s\", tableName)" << cendl;
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
		cpp << "void " << nameStream.str() << "::getLatest(" << nameStream.str() << "::RecordWithId& rec)" << endl;
		{
			ScopedStream<ApiFileOutputStream> getLatestStream(cpp);
            cpp << "Logger::get(\"Logs\").information(\"DB Get Latest : %s\", tableName)" << cendl;
			JSON::Array::Ptr primaryKeys = table->getArray("primaryKey");
			cpp << "std::vector<" << type_name(nameStream.str()) << "::RecordWithId> " << var_name(nameStream.str()) << cendl;
			if (primaryKeys->size())
			{
				cpp << "*db << \"SELECT *,rowid FROM \\\"\" << tableName << \"\\\" ORDER BY " << keyStream.str() << " DESC LIMIT 1\"," << endl;
			}
			else
			{
				cpp << "*db << \"SELECT *,rowid FROM \\\"\" << tableName << \"\\\" ORDER BY ROWID ASC LIMIT 1\"," << endl;
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

	void DatabaseSchema::generateGetAll(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields)
	{
		(void)apiName;
		(void)keyStream;
		cpp << "std::size_t " << nameStream.str() << "::getAll(std::vector<" << nameStream.str() << "::RecordWithId>& records, std::string condition)" << endl;
		{
			ScopedStream<ApiFileOutputStream> getLatestStream(cpp);
            cpp << "Logger::get(\"Logs\").information(\"DB Get All : %s\", tableName)" << cendl;
			cpp << "Poco::Data::Statement select(*db)" << cendl;
			cpp << "select << \"SELECT *,rowid FROM \\\"\" << tableName << \"\\\"\"" << cendl;
			cpp << "if (condition.length())" << endl;
			cpp << tabs(1) << "select << \" WHERE \" << condition" << cendl;
			cpp << "select << \" ORDER BY ROWID ASC\"," << endl;
			cpp << tabs(1) << "into(records)" << cendl;
			cpp << "return select.execute()" << cendl;
		}
		cpp << endl;
	}

	void DatabaseSchema::generateDeleteMultiple(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields)
	{
		(void)keyStream;
		(void)apiName;
		cpp << "void " << nameStream.str() << "::deleteMultiple(std::vector<" << nameStream.str() << "::RecordWithId>& records)" << endl;
		{
			ScopedStream<ApiFileOutputStream> deleteStream(cpp);
            cpp << "Logger::get(\"Logs\").information(\"DB Generate Delete Multiple : %s\", tableName)" << cendl;
			cpp << "Poco::Data::Statement statement(*db)" << cendl;
			cpp << "statement << \"DELETE FROM \\\"\" << tableName << \"\\\" WHERE rowid IN(\"" << cendl;
			cpp << "bool first = true" << cendl;
			cpp << "for (auto& rec : records)";
			{
				ScopedStream<ApiFileOutputStream> forEachStream(cpp);
				cpp << "if (!first) statement << \",\"" << cendl;
				cpp << "statement << rec.id" << cendl;
				cpp << "first = false" << cendl;
			}
			cpp << "statement << \")\"" << cendl;
			cpp << "statement.execute()" << cendl;
		}
		cpp << endl;
	}

}