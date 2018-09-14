#include "processor.h"

namespace inviwo {

	Processor::Processor()
		: identifier_("")
		, network_(nullptr)
	{
	}


	Processor::~Processor()
	{
	}

	std::string Processor::setIdentifier(const std::string& identifier)
	{
		return identifier;
	}

	std::string Processor::getIdentifier()
	{
		return identifier_;
	}

}