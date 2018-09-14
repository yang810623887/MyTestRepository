#ifndef IVW_COLLAPSIVEGROUPBOXWIDGETQT_H
#define IVW_COLLAPSIVEGROUPBOXWIDGETQT_H

#include "../qtwidgetsmoduledefine.h"
#include "propertywidgetqt.h"
#include "../inviwo-core/properties/propertyownerobserver.h"
#include "../inviwo-core/properties/propertyobserver.h"


class QLineEdit;
class QToolButton;
class QGroupBox;
class QPushButton;
class QLabel;
class QGridLayout;
class QCheckBox;

namespace inviwo {

	class Property;
	class PropertyOwner;
	class EditableLabelQt;

	class IVW_MODULE_QTWIDGETS_API CollapsibleGroupBoxWidgetQt : public PropertyWidgetQt
		, public PropertyOwnerObserver
		, public PropertyObserver
	{
	public:
		CollapsibleGroupBoxWidgetQt(Property* property, bool isCheckable = false);
		CollapsibleGroupBoxWidgetQt(std::string displayName = "", bool isCheckable = false);


		void addProperty(Property* tmpProperty);

		virtual bool isCollapsed() const;
		void toggleCollapsed();

	protected:
		void updatePropertyWidgetSemantics(PropertyWidgetQt*);
		virtual void setCollapsed(bool value);

		void generateWidget();

		std::string displayName_;
		bool collapsed_;
		bool checked_;
		EditableLabelQt* label_;

		std::vector<Property*> properties_;
	private:
		QToolButton* btnCollapse_;
		QWidget* propertyWidgetGroup_;
		QGridLayout* propertyWidgetGroupLayout_;
		QLabel* defaultLabel_;
		QCheckBox *checkBox_;
//		PropertyOwner* propertyOwner_;
		bool showIfEmpty_;
		bool checkable_;

	};
}

#endif
