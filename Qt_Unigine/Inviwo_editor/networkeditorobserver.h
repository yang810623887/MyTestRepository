
#ifndef IVW_NETWORKEDITOROBSERVER_H
#define IVW_NETWORKEDITOROBSERVER_H

#include <inviwoqteditordefine.h>
#include <../inviwo-core/inviwo.h>
#include <../inviwo-core/util/observer.h>

namespace inviwo {

	class IVW_QTEDITOR_API NetworkEditorObserver : public Observer {
	public:
		virtual void onNetworkEditorFileChanged(const std::string& /*newFilename*/) {};
		virtual void onModifiedStatusChanged(const bool& /*newStatus*/) {};
	};

}  // namespace

#endif  // IVW_NETWORKEDITOROBSERVER_H