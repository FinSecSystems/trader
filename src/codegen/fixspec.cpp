#include "stdafx.h"

#include "config.h"
#include "fileoutputstream.h"
#include "endpoint.h"
#include "helpers.h"
#include "fixspec.h"

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Path;
using Poco::XML::DOMParser;
using Poco::XML::InputSource;
using Poco::XML::Document;
using Poco::XML::NodeIterator;
using Poco::XML::NodeFilter;
using Poco::XML::Node;
using Poco::XML::NodeList;
using Poco::XML::AutoPtr;
using Poco::Exception;
using namespace Poco;
using namespace std;
using namespace Poco::XML;

namespace trader {
	FixSpec FixSpec::instance;

	const char* FixSpec::getCppType(const string& dbType)
	{
		if (dbType.compare("STRING") == 0
            || dbType.compare("CHAR") == 0
            || dbType.compare("CURRENCY") == 0
            || dbType.compare("EXCHANGE") == 0
            || dbType.compare("MULTIPLECHARVALUE") == 0
            || dbType.compare("MULTIPLESTRINGVALUE") == 0
            || dbType.compare("COUNTRY") == 0
            || dbType.compare("DATA") == 0
            || dbType.compare("XMLDATA") == 0
            )
		{
			return "std::string";
		}
		else if (dbType.compare("PRICE") == 0
            || dbType.compare("QTY") == 0
            || dbType.compare("AMT") == 0
            || dbType.compare("PRICEOFFSET") == 0
            )
		{
			return "double";
		}
        else if (dbType.compare("FLOAT") == 0
            || dbType.compare("PERCENTAGE") == 0
            )
        {
            return "float";
        }
		else if (dbType.compare("SEQNUM") == 0
			|| dbType.compare("INT") == 0
			|| dbType.compare("UTCTIMESTAMP") == 0
			|| dbType.compare("LENGTH") == 0
            || dbType.compare("LOCALMKTDATE") == 0
            || dbType.compare("MONTHYEAR") == 0
            || dbType.compare("NUMINGROUP") == 0
            || dbType.compare("UTCDATEONLY") == 0
            || dbType.compare("UTCTIMEONLY") == 0
            || dbType.compare("TZTIMEONLY") == 0
            || dbType.compare("TZTIMESTAMP") == 0
            || dbType.compare("LANGUAGE") == 0
            )
		{
			return "Poco::Int32";
		}
		else if (dbType.compare("BOOLEAN") == 0)
		{
			return "bool";
		}
		return dbType.c_str();
	}

    // Class to represent a graph
    template<class Vertex>
    class Graph
    {
        typedef std::map < Vertex, std::list<Vertex> > AdjMat;
        AdjMat adjMat;

        void topologicalSortUtil(Vertex v, std::map<Vertex, bool> visited, std::stack<Vertex> &Stack);
    public:

        void addEdge(Vertex v, Vertex w);

        void addVertex(Vertex v);

        void topologicalSort(std::stack<Vertex>& Stack);
    };

    template<class Vertex>
    void Graph<Vertex>::addVertex(Vertex v)
    {
        std::list<Vertex> dummy;
        adjMat.insert({ v, dummy });
    }

    template<class Vertex>
    void Graph<Vertex>::addEdge(Vertex v, Vertex w)
    {
        AdjMat::iterator it = adjMat.find(v);
        if (it == adjMat.end())
        {
            std::list<Vertex> dummy;
            dummy.push_back(w);
            adjMat.insert({ v, dummy });
        }
        else
        {
            it->second.push_back(w); // Add w to v’s list.
        }
    }

    template<class Vertex>
    void Graph<Vertex>::topologicalSortUtil(Vertex v, std::map<Vertex, bool> visited , std::stack<Vertex> &Stack)
    {
        // Mark the current node as visited.
        visited[v] = true;

        // Recur for all the vertices adjacent to this vertex
        std::list<Vertex>::iterator it;
        for (it = adjMat[v].begin(); it != adjMat[v].end(); ++it)
            if (!visited[*it])
                topologicalSortUtil(*it, visited, Stack);

        // Push current vertex to stack which stores result
        Stack.push(v);
    }

    template<class Vertex>
    void Graph<Vertex>::topologicalSort(std::stack<Vertex>& Stack)
    {
        // Mark all the vertices as not visited
        std::map<Vertex, bool> visited;
        for (std::map<Vertex, bool>::iterator it = visited.begin(); it != visited.end(); it++)
        {
            it->second = false;
        }

        // Call the recursive helper function to store Topological
        // Sort starting from all vertices one by one
        for (AdjMat::iterator it = adjMat.begin(); it != adjMat.end(); it++)
        {
            if (visited[it->first] == false)
            {
                topologicalSortUtil(it->first, visited, Stack);
            }
        }

    }


	void FixSpec::process(const string& namespacename, const string& filename, const string& outputdirectory)
	{
		InputSource src(filename);
		DOMParser parser;
		AutoPtr<Document> pDoc = parser.parse(&src);

		Element* root = (Element*)pDoc->firstChild();

		Config config;
		config.outputDir = outputdirectory;
		config.nameSpace = namespacename;
		config.headerFileName = outputdirectory + Path::separator() + "interface.h";
		//config.cppFileName = outputdirectory + Path::separator() + "interface.cpp";
	

		ApiFileOutputStream header(config.headerFileName);
		//ApiFileOutputStream cpp(config.cppFileName);

        startHeader(header, 0);
        {
            ScopedNamespace scopedNamespaceTrader(header, config.nameSpace);
            {
                std::string interfaceName = "Interface";
                ScopedNamespace scopedNamespaceInterface(header, interfaceName);

                Element* fieldsNode = root->getChildElement("fields");
                NodeList* fieldNodeList = fieldsNode->childNodes();

                for (UInt32 i = 0; i < fieldNodeList->length(); i++)
                {
                    Node* child = fieldNodeList->item(i);
                    if (child->nodeType() == Node::ELEMENT_NODE)
                    {
                        Element* fieldNode = (Element*)child;
                        string name = fieldNode->getAttribute("name");
                        if (fieldNode->hasChildNodes())
                        {
                            header << "enum " << name << " ";
                            {
                                ScopedStream<ApiFileOutputStream> enumScope(header);
                                NodeList* enumNodeList = fieldNode->childNodes();
                                for (UInt32 j = 0; j < enumNodeList->length(); j++)
                                {
                                    Node* valueNode = enumNodeList->item(j);
                                    if (valueNode->nodeType() == Node::ELEMENT_NODE)
                                    {
                                        Element* value = (Element*)valueNode;
                                        string description = value->getAttribute("description");
                                        header << name << "_" << description << "," << endl;
                                    }
                                }
                                header << "NUM_" << name << endl;
                            }
                            header << cendl;
                        }
                        else
                        {
                            string type = fieldNode->getAttribute("type");
                            string cppType = getCppType(type);
                            header << "typedef " << cppType << " " << name << cendl;
                        }
                        header << endl;
                    }
                }

                Element* componentsNode = root->getChildElement("components");
                NodeList* componentsNodeList = componentsNode->childNodes();

                Graph<Node*> nodeGraph;
                std::map<std::string, Node*> nodeNameToVertexMap;

                for (UInt32 i = 0; i < componentsNodeList->length(); i++)
                {
                    Node* componentNode = componentsNodeList->item(i);
                    if (componentNode->nodeType() == Node::ELEMENT_NODE)
                    {
                        Element* component = (Element*)componentNode;
                        string name = component->getAttribute("name");
                        ostringstream structName;
                        structName << name << "Object";
                        nodeGraph.addVertex(componentNode);
                        nodeNameToVertexMap.insert({ structName.str(), componentNode });
                    }
                }

                for (UInt32 i = 0; i < componentsNodeList->length(); i++)
                {
                    Node* componentNode = componentsNodeList->item(i);
                    if (componentNode->nodeType() == Node::ELEMENT_NODE)
                    {
                        Element* component = (Element*)componentNode;
                        string name = component->getAttribute("name");
                        ostringstream structName;
                        structName << name << "Object";
                        NodeList* componentChildNodeList = componentNode->childNodes();
                        for (UInt32 j = 0; j < componentChildNodeList->length(); j++)
                        {
                            Node* componentChildNode = componentChildNodeList->item(j);
                            if (componentChildNode->nodeType() == Node::ELEMENT_NODE)
                            {
                                Element* groupOrField = (Element*)componentChildNode;
                                std::string tagName = groupOrField->tagName();
                                string groupOrFieldName = groupOrField->getAttribute("name");
                                if (tagName.compare("group") == 0)
                                {
                                    {
                                        NodeList* componentChildNodeList2 = componentChildNode->childNodes();
                                        {
                                            for (UInt32 k = 0; k < componentChildNodeList2->length(); k++)
                                            {
                                                Node* fieldChildNode = componentChildNodeList2->item(k);
                                                if (fieldChildNode->nodeType() == Node::ELEMENT_NODE)
                                                {
                                                    Element* field = (Element*)fieldChildNode;
                                                    string fieldName = field->getAttribute("name");
                                                    string fieldTagName = field->tagName();
                                                    ostringstream structName2;
                                                    if (fieldTagName.compare("field") != 0)
                                                    {
                                                        structName2 << fieldName << "Object";
                                                        std::map<std::string, Node*>::iterator it = nodeNameToVertexMap.find(structName2.str());
                                                        if (it != nodeNameToVertexMap.end())
                                                        {
                                                            nodeGraph.addEdge(componentChildNode, it->second);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                else if (tagName.compare("field") != 0)
                                {
                                    std::map<std::string, Node*>::iterator it = nodeNameToVertexMap.find(structName.str());
                                    if (it != nodeNameToVertexMap.end())
                                    {
                                        nodeGraph.addEdge(componentChildNode, it->second);
                                    }
                                }
                            }
                        }
                    }
                }

                std::stack<Node*> nodeStack;
                nodeGraph.topologicalSort(nodeStack);

                std::stack<Node*> nodeStackReverse;
                while (!nodeStack.empty())
                {
                    nodeStackReverse.push(nodeStack.top());
                    nodeStack.pop();
                }

                while (!nodeStackReverse.empty())
                {
                    Node* componentNode = nodeStackReverse.top();
                    nodeStackReverse.pop();
                    if (componentNode && componentNode->nodeType() == Node::ELEMENT_NODE)
                    {
                        Element* component = (Element*)componentNode;
                        string name = component->getAttribute("name");
                        ostringstream structName;
                        structName << name << "Object";
                        ScopedStruct<0, ApiFileOutputStream> scopedStruct(header, structName.str().c_str());
                        NodeList* componentChildNodeList = componentNode->childNodes();
                        for (UInt32 j = 0; j < componentChildNodeList->length(); j++)
                        {
                            Node* componentChildNode = componentChildNodeList->item(j);
                            if (componentChildNode->nodeType() == Node::ELEMENT_NODE)
                            {
                                Element* groupOrField = (Element*)componentChildNode;
                                std::string tagName = groupOrField->tagName();
                                string groupOrFieldName = groupOrField->getAttribute("name");
                                if (tagName.compare("group") == 0)
                                {
                                    {
                                        ScopedStruct<0, ApiFileOutputStream> scopedStructGroup(header, groupOrFieldName.c_str());
                                        NodeList* componentChildNodeList2 = componentChildNode->childNodes();
                                        {
                                            for (UInt32 k = 0; k < componentChildNodeList2->length(); k++)
                                            {
                                                Node* fieldChildNode = componentChildNodeList2->item(k);
                                                if (fieldChildNode->nodeType() == Node::ELEMENT_NODE)
                                                {
                                                    Element* field = (Element*)fieldChildNode;
                                                    string fieldName = field->getAttribute("name");
                                                    string fieldTagName = field->tagName();
                                                    if (fieldTagName.compare("field") == 0)
                                                    {
                                                        header << fieldName << " " << var_name(fieldName) << cendl;
                                                    }
                                                    else
                                                    {
                                                        header << fieldName << "Object " << var_name(fieldName) << cendl;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    header << "std::vector<" << groupOrFieldName << "> " << var_name(groupOrFieldName) << cendl;
                                }
                                else if (tagName.compare("field") == 0)
                                {
                                    header << groupOrFieldName << " " << var_name(groupOrFieldName) << cendl;
                                }
                                else
                                {
                                    header << groupOrFieldName << "Object " << var_name(groupOrFieldName) << cendl;
                                }
                            }
                        }
                    }
                }

                {
                    ScopedClass<0> scopedClass(header, "IConnection");
                    header << "virtual void ProcessMessage(Poco::AutoPtr<IMessageData>> _messageData) = 0" << cendl;
                }

                {
                    ScopedClass<1> scopedConnectionClass(header, "Connection", "IConnection, public Poco::RefCountedObject");

                    Element* messagesNode = root->getChildElement("messages");
                    NodeList* messagesNodelist = messagesNode->childNodes();

                    header << comment("Messages Enum") << endl;
                    header << "enum MESSAGES ";
                    {
                        ScopedStream<ApiFileOutputStream> enumScope(header);
                        for (UInt32 i = 0; i < messagesNodelist->length(); i++)
                        {
                            Node* messageNode = messagesNodelist->item(i);
                            if (messageNode->nodeType() == Node::ELEMENT_NODE)
                            {
                                Element* message = (Element*)messageNode;
                                string name = message->getAttribute("name");
                                header << name << "_TYPE ," << endl;
                            }
                        }
                        header << "NUM_MESSAGES" << cendl;
                    }
                    header << cendl;

                    {
                        ScopedClass<0> scopedMessageDataClass(header, "IMessageData");
                        header << "virtual enum MESSAGES GetType() = 0" << cendl;
                    }

                    header << comment("Message Data") << endl;
                    for (UInt32 i = 0; i < messagesNodelist->length(); i++)
                    {
                        Node* messageNode = messagesNodelist->item(i);
                        if (messageNode->nodeType() == Node::ELEMENT_NODE)
                        {
                            Element* message = (Element*)messageNode;
                            string attribName = message->getAttribute("name");
                            ostringstream className;
                            className << attribName << "Data";
                            ScopedStruct<0, ApiFileOutputStream> scopedStruct(header, className.str().c_str());
                            header << "virtual enum MESSAGES GetType()" << endl;
                            {
                                ScopedStream<ApiFileOutputStream> funcScope(header);
                                header << "return MESSAGES::" << attribName << "_TYPE" << cendl;
                            }
                            NodeList* messageChildNodeList = messageNode->childNodes();
                            for (UInt32 j = 0; j < messageChildNodeList->length(); j++)
                            {
                                Node* messageChildNode = messageChildNodeList->item(j);
                                if (messageChildNode->nodeType() == Node::ELEMENT_NODE)
                                {
                                    Element* groupOrField = (Element*)messageChildNode;
                                    std::string tagName = groupOrField->tagName();
                                    string attribName2 = groupOrField->getAttribute("name");
                                    if (tagName.compare("group") == 0)
                                    {
                                        {
                                            ScopedStruct<0, ApiFileOutputStream> scopedStruct3(header, attribName2.c_str());
                                            NodeList* fieldNodeList2 = messageChildNode->childNodes();
                                            {
                                                for (UInt32 k = 0; k < fieldNodeList2->length(); k++)
                                                {
                                                    Node* fieldChildNode = fieldNodeList2->item(k);
                                                    if (fieldChildNode->nodeType() == Node::ELEMENT_NODE)
                                                    {
                                                        Element* field = (Element*)fieldChildNode;
                                                        string name3 = field->getAttribute("name");
                                                        header << name3 << " " << var_name(name3) << cendl;
                                                    }
                                                }
                                            }
                                        }
                                        header << "std::vector<" << attribName2 << "> " << var_name(attribName2) << cendl;
                                    }
                                    else
                                    {
                                        header << attribName2 << " " << var_name(attribName2) << cendl;
                                    }
                                }
                            }
                        }
                    }

                    for (UInt32 i = 0; i < messagesNodelist->length(); i++)
                    {
                        Node* messageNode = messagesNodelist->item(i);
                        if (messageNode->nodeType() == Node::ELEMENT_NODE)
                        {
                            Element* message = (Element*)messageNode;
                            string name = message->getAttribute("name");
                            header << "virtual " << name << "(Poco::AutoPtr<" << name << "Data>> " << var_name(name) << "Data)";
                            {
                                ScopedStream<ApiFileOutputStream> funcScope(header);
                                header << "poco_bugcheck_msg(\"" << name << " not supported.\")" << cendl;
                            }
                        }
                    }

                    header << "void ProcessMessage(Poco::AutoPtr<IMessageData>> _messageData)" << endl;
                    {
                        ScopedStream<ApiFileOutputStream> funcScope(header);
                        header << "switch (_messageData->GetType())";
                        {
                            ScopedStream<ApiFileOutputStream> switchScope(header);
                            for (UInt32 i = 0; i < messagesNodelist->length(); i++)
                            {
                                Node* messageNode = messagesNodelist->item(i);
                                if (messageNode->nodeType() == Node::ELEMENT_NODE)
                                {
                                    Element* message = (Element*)messageNode;
                                    string name = message->getAttribute("name");
                                    header << "case MESSAGES::" << name << "_TYPE: ";
                                    {
                                        ScopedStream<ApiFileOutputStream> caseScope(header);
                                        header << name << "(_messageData)" << cendl;
                                        header << "break" << cendl;
                                    }
                                }
                            }
                        }
                    }

                    header << "virtual void SetReceivingConnection(Connection* _connection)";
                    {
                        ScopedStream<ApiFileOutputStream> enumScope(header);
                        header << "connection = _connection" << cendl;
                    }
                    header << endl;
                    header << "Connection* connection" << cendl;

                }

            }
        }


		//Write


		header << endl;

		//cpp << endl;
	}

}