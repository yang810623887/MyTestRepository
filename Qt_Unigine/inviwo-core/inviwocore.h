#ifndef IVW_INVIWOCORE_H
#define IVW_INVIWOCORE_H

#include "inviwocoredefine.h"
#include "inviwomodule.h"

namespace inviwo {

	class InviwoApplication;

	class IVW_CORE_API InviwoCore : public InviwoModule
	{
	public:
		InviwoCore( InviwoApplication *app);

		virtual std::string getPath() const override;
	};

}
#endif