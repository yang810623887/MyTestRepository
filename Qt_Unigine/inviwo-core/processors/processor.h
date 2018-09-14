
#ifndef IVW_PROCESSOR_H
#define IVW_PROCESSOR_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"
#include "processorinfo.h"

namespace inviwo {

	class ProcessorWidget;

	class ProcessorNetwork;

	class IVW_CORE_API Processor
	{
	public:
		Processor();
		virtual ~Processor();

		virtual const ProcessorInfo getProcessorInfo() const = 0;

		std::string getClassIdentifier() const { return getProcessorInfo().classIdentifier; }
		std::string getDisplayName() const { return getProcessorInfo().displayName; }
		std::string getCategory() const { return getProcessorInfo().category; }
		CodeState getCodeState() const { return getProcessorInfo().codeState; }
		Tags getTags() const { return getProcessorInfo().tags; }

		/**
		* Sets the identifier of the Processor. If there already exist a processor with that identifier
		* it will append a number, starting at 2 to ensure uniqueness of identifiers.
		* @param identifier the new identifier. Processor identifiers should only contain alpha
		numeric characters, "-", "_" and " ".
		* @return The identifier that was set including eventual appended number
		*/
		std::string setIdentifier(const std::string& identifier);
		std::string getIdentifier();
		//virtual std::vector<std::string> getPath() const override;

		//virtual void setProcessorWidget(std::unique_ptr<ProcessorWidget> processorWidget);


	//protected:
	//	std::unique_ptr<ProcessorWidget> processorWidget_;

	/**
	* Called when the network is evaluated and the processor is ready and not valid.
	* The work of the processor should be done here.
	*/
		virtual void process() {}

	private:
		std::string identifier_;


		ProcessorNetwork* network_;
	};

}
#endif