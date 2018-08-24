#ifndef __GL_APP_QT_H__
#define __GL_APP_QT_H__

#include "uniginewidget.h"

#include <UnigineApp.h>
#include <UnigineEngine.h>

class IVW_UNIGINE_API GLAppQt : public UnigineWidget
{
	Q_OBJECT

public:
	GLAppQt(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~GLAppQt();

	virtual void *getHandle();
	virtual const char *getName();
};

#endif // __GL_APP_QT_H__
