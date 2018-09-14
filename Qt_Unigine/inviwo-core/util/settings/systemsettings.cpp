#include "systemsettings.h"

namespace inviwo {

	SystemSettings::SystemSettings()
		: Settings("System Settings")
	{
		addProperty(applicationUsageMode_);
		//addProperty(poolSize_);
		//addProperty(txtEditor_);
		//addProperty(enablePortInformation_);
		//addProperty(enablePortInspectors_);
		//addProperty(portInspectorSize_);
		//addProperty(enableTouchProperty_);
		//addProperty(enablePickingProperty_);
		//addProperty(enableSoundProperty_);
		//addProperty(useRAMPercentProperty_);
		//addProperty(logStackTraceProperty_);
		//addProperty(pythonSyntax_);
		//addProperty(glslSyntax_);
		//addProperty(followObjectDuringRotation_);
	}

}