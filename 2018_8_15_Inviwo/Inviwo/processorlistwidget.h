#ifndef IVW_PROCESSORLISTWIDGET_H
#define IVW_PROCESSORLISTWIDGET_H

#include "InviwoDockWidget.h"
#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>
#include <QTreeWidget>
#include <QMouseEvent>
#include <QDrag>

namespace inviwo {

	class HelpWidget;

	class ProcessorTree : public QTreeWidget {
	public:
		ProcessorTree(QWidget* parent);
		~ProcessorTree() = default;

		static const int IDENTIFIER_ROLE;

	protected:
		virtual void mousePressEvent(QMouseEvent* e) override;
		virtual void mouseMoveEvent(QMouseEvent* e) override;
	private:
		QPoint dragStartPosition_;
	};


	class ProcessorTreeWidget : public InviwoDockWidget
	{
		Q_OBJECT
	public:
		ProcessorTreeWidget(QWidget* parent, HelpWidget* helpWidget);
		~ProcessorTreeWidget() = default;

		void focusSearch();
		void addSelectedProcessor();
	private:
		HelpWidget * helpWidget_;
	};

	class ProcessorDragObject : public QDrag {
	public:
		ProcessorDragObject(QWidget* source, const QString className);

		static bool canDecode(const QMimeData* mimeData);//QMimeData���������������ڼ��а�����Ϣ��������קԭ��
		static bool decode(const QMimeData* mimeData, QString& className);

	};

}
#endif