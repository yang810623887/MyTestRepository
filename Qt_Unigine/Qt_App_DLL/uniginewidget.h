/*********************************************************************************
*
* NameSpace: Qt_App_DLL
* ClassName: uniginewidget
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-20 16:59:52
* --------------------------------------------------------------------------------
* DateTime : 2018/08/20
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/


#ifndef __APP_QT_H__
#define __APP_QT_H__
#include <QMainWindow>
#include <QtWidgets/QWidget>

#include <UnigineApp.h>
#include <UnigineEngine.h>
#include "uniginewidgetdefine.h"


class IVW_UNIGINE_API UnigineWidget : public QWidget, public Unigine::App
{
	Q_OBJECT
public:
	
	//************************************
	// Method     : UnigineWidget
	// FullName   : UnigineWidget::UnigineWidget
	// Parameter  : QWidget * parent 
	// Parameter  : Qt::WindowFlags flags
	// Description:
	//************************************
	UnigineWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~UnigineWidget();
protected:

	//window events
	//************************************
	// Method     : paintEngine
	// FullName   : UnigineWidget::paintEngine
	// Description: override Qt QPaintEngine,When widget repaint trigger this function
	//************************************
	virtual QPaintEngine *paintEngine() const;

	//************************************
	// Method     : timerEvent
	// FullName   : UnigineWidget::timerEvent
	// Parameter  : QTimerEvent * event QTimerEvent's instance
	// Description: override Qt timerEvent, When start TimerCounter trigger this function
	//************************************
	virtual void timerEvent(QTimerEvent *event);

	//************************************
	// Method     : resizeEvent
	// FullName   : UnigineWidget::resizeEvent
	// Parameter  : QResizeEvent * event QResizeEvent's instance
	// Description: override Qt resizeEvent, When Widget Change Shape trigger this function
	//************************************
	virtual void resizeEvent(QResizeEvent *event);

	// mouse events

	//************************************
	// Method     : mousePressEvent 
	// FullName   : UnigineWidget::mousePressEvent
	// Parameter  : QMouseEvent * event QMouseEvent's instance
	// Description: override Qt mousePressEvent, When mouse Pressed trigger this function
	//************************************
	virtual void mousePressEvent(QMouseEvent *event);

	//************************************
	// Method     : mouseReleaseEvent
	// FullName   : UnigineWidget::mouseReleaseEvent
	// Parameter  : QMouseEvent * event QMouseEvent's instance
	// Description: override Qt mouseReleaseEvent, When mouse Release trigger this function
	//************************************
	virtual void mouseReleaseEvent(QMouseEvent *event);

	//************************************
	// Method     : mouseDoubleClickEvent
	// FullName   : UnigineWidget::mouseDoubleClickEvent
	// Parameter  : QMouseEvent * event QMouseEvent's instance
	// Description: override Qt mouseDoubleClickEvent, When mouse DoubleClick trigger this function
	//************************************
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

	//************************************
	// Method     : mouseMoveEvent
	// FullName   : UnigineWidget::mouseMoveEvent
	// Parameter  : QMouseEvent * event QMouseEvent's instance
	// Description: override Qt mouseMoveEvent, When mouse Move trigger this function
	//************************************
	virtual void mouseMoveEvent(QMouseEvent *event);

	//************************************
	// Method     : wheelEvent
	// FullName   : UnigineWidget::wheelEvent
	// Parameter  : QWheelEvent * event QMouseEvent's instance
	// Description: override Qt wheelEvent, When mouse wheel Rolling trigger this function
	//************************************
	virtual void wheelEvent(QWheelEvent *event);


	// keyboard events

	//************************************
	// Method     : keyPressEvent
	// FullName   : UnigineWidget::keyPressEvent
	// Parameter  : QKeyEvent * event  QKeyEvent's instance
	// Description: override Qt keyPressEvent, When keyboard pressed trigger this function
	//************************************
	virtual void keyPressEvent(QKeyEvent *event);


	//************************************
	// Method     : keyReleaseEvent
	// FullName   : UnigineWidget::keyReleaseEvent
	// Parameter  : QKeyEvent * event  QKeyEvent's instance
	// Description: override Qt keyReleaseEvent, When keyboard Realease trigger this function
	//************************************
	virtual void keyReleaseEvent(QKeyEvent *event);

	//************************************
	// Method     : focusInEvent
	// FullName   : UnigineWidget::focusInEvent
	// Parameter  : QFocusEvent * event  QFocusEvent's instance
	// Description: override Qt focusInEvent, When focus in this widget trigger this function
	//************************************
	virtual void focusInEvent(QFocusEvent *event);

	//************************************
	// Method     : focusOutEvent
	// FullName   : UnigineWidget::focusOutEvent
	// Parameter  : QFocusEvent * event  QFocusEvent's instance
	// Description: override Qt focusOutEvent, When focus out this widget trigger this function
	//************************************
	virtual void focusOutEvent(QFocusEvent *event);

	//************************************
	// Method     : eventFilter
	// FullName   : UnigineWidget::eventFilter
	// Parameter  : QObject * obj
	// Parameter  : QEvent * event
	// Description:
	//************************************
	virtual bool eventFilter(QObject *obj, QEvent *event);

signals:

	// signals
	void closed();

public:
	// app handle
	virtual void *getHandle();

	// window position
	virtual int setPosition(int x, int y);
	virtual int getPositionX();
	virtual int getPositionY();

	// video mode
	virtual int setVideoMode(int width, int height, int flags = 0, int refresh = 0);
	virtual int restoreVideoMode();
	virtual int setUpdate(int update);
	virtual int setGamma(float gamma);
	virtual int setTitle(const char *title);
	virtual int setIcon(const unsigned char *data, int size);
	virtual int getWidth();
	virtual int getHeight();
	virtual void setWidth(int value);
	virtual void setHeight(int value);
	virtual int getFlags();
	virtual int getUpdate();

	// mouse
	virtual void setMouse(int x, int y);
	virtual void setMouseGrab(int grab);
	virtual void setMouseShow(int show);
	virtual int setMouseCursor(const unsigned char *data, int size, int x = 0, int y = 0);
	virtual int getMouseX();
	virtual int getMouseY();
	virtual int getMouseGrab();
	virtual int getMouseShow();
	virtual void setMouseAxis(int axis, int value);
	virtual int getMouseAxis(int axis);
	virtual int clearMouseAxis(int axis);
	virtual void setMouseButton(int button);
	virtual int getMouseButton();
	virtual int getMouseButtonState(int button);
	virtual int clearMouseButtonState(int button);

	// touches
	virtual int getNumTouches();
	virtual int getTouchX(int touch);
	virtual int getTouchY(int touch);

	// keyboard
	virtual void setKeyState(int key, int state);
	virtual int getKeyState(int key);
	virtual int clearKeyState(int key);

	// clipboard
	virtual void setClipboard(const char *str);
	virtual const char *getClipboard();

	// main loop

	virtual int isDone();
	virtual void doUpdate();
	virtual void doRender();
	virtual void doSwap();
	virtual void exit();

protected:
	Unigine::RenderContextPtr context; 

private:
	void update_engine();  // upadte Unigine Engine Context

	virtual int create_context();
	virtual int destroy_context();
	virtual int resize_window();
	virtual int swap_window();

	// common
	unsigned int translate_key_from_qt(int key) const;
	int translate_key_to_qt(unsigned int key) const;
	unsigned int translate_native_key(unsigned int vkey) const;
	unsigned int translate_native_key_from_event(QKeyEvent *event) const;
	int translate_modifier_to_qt(unsigned int key) const;

	int timer_resize; // timer on resize event
	int timer_update; // timer on update engine event


	// window
	int window_width; 
	int window_height;
	int window_flags;
	int window_update;
	int window_frame;
	int window_gamma;
	int stop_fps;

	//mouse
	int mouse_x;
	int mouse_y;
	int mouse_axes[NUM_AXES];
	int mouse_button;
	int mouse_release;
	int mouse_grab;
	int mouse_show;

	// keyboard
	int keys[NUM_KEYS]; 

	QWidget *ignore_focus;
	QString engine_clipboard;
};
#endif
