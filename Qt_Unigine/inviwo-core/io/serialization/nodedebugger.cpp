#include "nodedebugger.h"
#include "../../util/stringconversion.h"
#include "ticpp.h"

#include <sstream>

namespace inviwo {


	NodeDebugger::Node::Node(std::string k /*= ""*/, std::string i /*= ""*/, std::string t /*= ""*/, int l /*= 0*/)
		: key(k)
		, identifier(i)
		, type(t)
		, line(1){}

	NodeDebugger::NodeDebugger(ticpp::Element* elem)
	{
		while (elem)
		{
			nodes_.push_back(Node(elem->Value(),
								  elem->GetAttributeOrDefault("identifier", ""),
								  elem->GetAttributeOrDefault("type", ""),
				                  elem->Row()));

			TxNode* node = elem->Parent(false);
			if (node)
			{
				elem = dynamic_cast<TxElement*>(node);
			} 
			else
			{
				elem = nullptr;
			}
		}
	}

}