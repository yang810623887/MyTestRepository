#ifndef IVW_NODEDEBUGGER_H
#define IVW_NODEDEBUGGER_H

#include "../../inviwocoredefine.h"

#include <string>
#include <vector>

namespace ticpp {
	class Element;
}

namespace inviwo {

	struct IVW_CORE_API NodeDebugger {
		struct Node {
			Node(std::string k = "", std::string i = "", std::string t = "", int l = 0);
			std::string key;
			std::string identifier;
			std::string type;
			int line;
		};

		NodeDebugger(ticpp::Element* node);

		const Node& operator[](std::size_t idx) const;
		std::string toString(std::size_t idx) const;
		std::vector<std::string> getPath() const;
		std::string getDescription() const;
		size_t size() const;

		std::vector<Node> nodes_;
	}
}

#endif
