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

        void topologicalSortUtil(Vertex v, std::map<Vertex, bool>& visited, std::stack<Vertex>& resultStack);

        bool hasCycleUtil(Vertex v, std::vector<Vertex> &traversedVertices);

    public:

        void addEdge(Vertex v, Vertex w);

        void addVertex(Vertex v);

        void topologicalSort(std::stack<Vertex>& Stack);

        bool findCycles(std::vector<Vertex>& traversedVertices);

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
        typename AdjMat::iterator it = adjMat.find(v);
        poco_assert(it != adjMat.end());
        it->second.push_back(w); // Add w to v’s list.
    }

    template<class Vertex>
    void Graph<Vertex>::topologicalSortUtil(Vertex v, typename std::map<Vertex, bool>& visited , typename std::stack<Vertex> &resultStack)
    {
        // Mark the current node as visited.
        visited[v] = true;

        // Recur for all the vertices adjacent to this vertex
        typename std::list<Vertex>::iterator it;
        for (it = adjMat[v].begin(); it != adjMat[v].end(); ++it)
            if (!visited[*it])
                topologicalSortUtil(*it, visited, resultStack);

        // Push current vertex to stack which stores result
        resultStack.push(v);
    }

    template<class Vertex>
    bool Graph<Vertex>::hasCycleUtil(Vertex v, typename std::vector<Vertex> &traversedVertices)
    {
        // Recur for all the vertices adjacent to this vertex
        typename std::list<Vertex>::iterator it;
        for (it = adjMat[v].begin(); it != adjMat[v].end(); ++it)
        {
            typename std::vector<Vertex>::iterator itVertex = std::find(traversedVertices.begin(), traversedVertices.end(), *it);
            if (itVertex != traversedVertices.end())
            {
                traversedVertices.push_back(*it);
                return true;
            }
            traversedVertices.push_back(*it);
            if (hasCycleUtil(*it, traversedVertices))
            {
                return true;
            }
        }
        return false;
    }

    template<class Vertex>
    bool Graph<Vertex>::findCycles(typename std::vector<Vertex>& traversedVertices)
    {
        traversedVertices.clear();
        for (typename AdjMat::iterator it = adjMat.begin(); it != adjMat.end(); it++)
        {
            traversedVertices.push_back(it->first);
            if (hasCycleUtil(it->first, traversedVertices))
            {
                return true;
            }
            traversedVertices.clear();
        }
        return false;
    }

    template<class Vertex>
    void Graph<Vertex>::topologicalSort(typename std::stack<Vertex>& resultStack)
    {
        // Mark all the vertices as not visited
        typename std::map<Vertex, bool> visited;
        for (typename std::map<Vertex, bool>::iterator it = visited.begin(); it != visited.end(); it++)
        {
            it->second = false;
        }

        // Call the recursive helper function to store Topological
        // Sort starting from all vertices one by one
        for (typename AdjMat::iterator it = adjMat.begin(); it != adjMat.end(); it++)
        {
            if (visited[it->first] == false)
            {
                topologicalSortUtil(it->first, visited, resultStack);
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
	

		ApiFileOutputStream header(config.headerFileName);

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
                        {
                            std::map<std::string, Node*>::iterator it = nodeNameToVertexMap.find(structName.str());
                            poco_assert(it != nodeNameToVertexMap.end());
                        }
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
                                                        poco_assert(it != nodeNameToVertexMap.end());
                                                        if (it != nodeNameToVertexMap.end())
                                                        {
                                                            nodeGraph.addEdge(componentNode, it->second);

                                                            //ostringstream debugStr;
                                                            //debugStr << "Add Edge " << structName.str() << " -> " << structName2.str() << std::endl;
                                                            //Debugger::message(debugStr.str());
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                else if (tagName.compare("field") != 0)
                                {
                                    ostringstream structName2;
                                    structName2 << groupOrFieldName << "Object";
                                    std::map<std::string, Node*>::iterator it = nodeNameToVertexMap.find(structName2.str());
                                    poco_assert(it != nodeNameToVertexMap.end());
                                    if (it != nodeNameToVertexMap.end())
                                    {
                                        nodeGraph.addEdge(componentNode, it->second);

                                        //ostringstream debugStr;
                                        //debugStr << "Add Edge " << structName.str() << " -> " << structName2.str() << std::endl;
                                        //Debugger::message(debugStr.str());
                                    }
                                }
                            }
                        }
                    }
                }

                std::vector<Node*> traversedVertices;
                if (nodeGraph.findCycles(traversedVertices))
                {
                    for (std::vector<Node*>::iterator itVertices = traversedVertices.begin(); itVertices != traversedVertices.end(); itVertices++)
                    {
                        Element* component = (Element*)*itVertices;
                        string name = component->getAttribute("name");
                        ostringstream structName;
                        structName << name << "Object";
                        std::cout << structName.str() << ",";
                    }
                    std::cout << std::endl;
                    poco_assert(0);
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
                    header << "NUM_MESSAGES" << endl;
                }
                header << cendl;

                header << "typedef Poco::UInt64 MessageId" << cendl;

                {
                    ScopedClass<1> scopedMessageDataClass(header, "IMessageData", "Poco::RefCountedObject");
                    header << "virtual enum MESSAGES GetType() = 0" << cendl;
                    header << endl;
                    header << "MessageId getUniqueMessageId()" << endl;
                    {
                        ScopedStream<ApiFileOutputStream> funcScope(header);
                        header << "static std::atomic<MessageId> nextMessageId" << cendl;
                        header << "return ++nextMessageId" << cendl;
                    }
                    header << "MessageId messageId" << cendl;
                }

                {
                    ScopedClass<0> scopedClass(header, "IConnection");

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
                            ScopedStruct<1, ApiFileOutputStream> scopedStruct(header, className.str().c_str(), "IMessageData");
                            if (className.str().find("Request") != std::string::npos)
                            {
                                header << className.str().c_str() << "()" << endl;
                                {
                                    ScopedStream<ApiFileOutputStream> funcScope(header);
                                    header << "messageId = getUniqueMessageId()" << cendl;
                                }
                            }

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
                                    else if (tagName.compare("field") == 0)
                                    {
                                        header << attribName2 << " " << var_name(attribName2) << cendl;
                                    }
                                    else
                                    {
                                        header << attribName2 << "Object " << var_name(attribName2) << cendl;
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
                            header << "virtual void " << name << "(Poco::AutoPtr<" << name << "Data> " << var_name(name) << "Data) = 0" << cendl;
                        }
                    }

                    header << "virtual void ProcessMessage(Poco::AutoPtr<IMessageData> _messageData) = 0" << cendl;

                    header << "virtual void DoOperation(Poco::Int32 operation) = 0" << cendl;
                }

                {
                    ScopedClass<1> scopedConnectionClass(header, "Connection", "IConnection, public Poco::RefCountedObject");

                    header << "virtual void SetReceivingConnection(Poco::AutoPtr<Connection> _connection)";
                    {
                        ScopedStream<ApiFileOutputStream> enumScope(header);
                        header << "receivingConnection = _connection" << cendl;
                    }
                    header << endl;
                    header << "Poco::AutoPtr<Connection> receivingConnection" << cendl;

                }

                {
                    ScopedClass<1> scopedConnectionClass(header, "MessageReceivingConnection", "Connection");

                    header << "void ProcessMessage(Poco::AutoPtr<IMessageData> _messageData)" << endl;
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
                                        header << "Poco::AutoPtr<" << name << "Data> ptr = _messageData.unsafeCast<" << name << "Data>()" << cendl;
                                        header << name << "(ptr)" << cendl;
                                        header << "break" << cendl;
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
                            header << "virtual void " << name << "(Poco::AutoPtr<" << name << "Data> " << var_name(name) << "Data) override";
                            {
                                ScopedStream<ApiFileOutputStream> funcScope(header);
                                header << "poco_bugcheck_msg(\"" << var_name(name) << " not supported.\")" << cendl;
                            }
                        }
                    }

                    header << "void DoOperation(Poco::Int32 operation)" << endl;
                    {
                        ScopedStream<ApiFileOutputStream> funcScope(header);
                        header << "(void)operation" << cendl;
                        header << "poco_bugcheck_msg(\"DoOperation not implemented.\")" << cendl;
                    }

                }

                {
                    ScopedClass<1> scopedConnectionClass(header, "CallConnection", "Connection");

                    for (UInt32 i = 0; i < messagesNodelist->length(); i++)
                    {
                        Node* messageNode = messagesNodelist->item(i);
                        if (messageNode->nodeType() == Node::ELEMENT_NODE)
                        {
                            Element* message = (Element*)messageNode;
                            string name = message->getAttribute("name");
                            header << "virtual void " << name << "(Poco::AutoPtr<" << name << "Data> " << var_name(name) << "Data) override";
                            {
                                ScopedStream<ApiFileOutputStream> funcScope(header);
                                header << "ProcessMessage(" << var_name(name) << "Data)" << cendl;
                            }
                        }
                    }

                    header << "void ProcessMessage(Poco::AutoPtr<IMessageData> _messageData)" << endl;
                    {
                        ScopedStream<ApiFileOutputStream> funcScope(header);
                        header << "poco_bugcheck_msg(\"ProcessMessage not implemented.\")" << cendl;
                    }

                    header << "void DoOperation(Poco::Int32 operation)" << endl;
                    {
                        ScopedStream<ApiFileOutputStream> funcScope(header);
                        header << "(void)operation" << cendl;
                        header << "poco_bugcheck_msg(\"DoOperation not implemented.\")" << cendl;
                    }

                }

            }
        }


		//Write


		header << endl;

		//cpp << endl;
	}

}