#include "networkeditor.h"
#include "inviwomainwindow.h"
#include "../inviwo-core/inviwoapplication.h"

namespace inviwo {

	NetworkEditor::NetworkEditor(InviwoMainWindow* mainwindow)
		: QGraphicsScene()
		, modified_(false)
		//, network_(mainwindow->getInviwoApplication()->getProce)
	{

	}

	bool NetworkEditor::isModified() const
	{
		return modified_;
	}

	void NetworkEditor::setModified(const bool modified /*= true*/)
	{
		if (modified != modified_)
		{
			modified_ = modified;
			/*forEachObserver([&](NetworkEditorObserver *o)
			{
				o->onModifiedStatusChanged(modified);
			});*/
		}
	}

}