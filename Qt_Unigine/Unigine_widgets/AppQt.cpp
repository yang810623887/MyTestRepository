/* Copyright (C) 2005-2018, UNIGINE Corp. All rights reserved.
 *
 * This file is a part of the UNIGINE 2.7.1 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE Corp. at http://unigine.com/
 */


#include <QClipboard>
#include <QLayout>
#include <QWindow>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <clocale>

#include <UnigineEngine.h>

#include "AppQt.h"

#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "user32.lib")
#endif

#ifdef _LINUX
	#include <GL/glx.h>
	#include <GL/glxext.h>
#endif

AppQt::AppQt(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	setlocale(LC_NUMERIC, "C");

	timer_resize = 0;
	timer_update = startTimer(0);

	window_width = 0;
	window_height = 0;
	window_flags = 0;
	window_frame = 0;
	stop_fps = 0;

	mouse_x = 0;
	mouse_y = 0;
	memset(mouse_axes, 0, sizeof(mouse_axes));
	mouse_button = 0;
	mouse_release = 0;
	mouse_grab = 0;
	mouse_show = 1;
	window_update = 1;

	memset(keys, 0, sizeof(keys));

#ifdef _WIN32
	setAttribute(Qt::WA_PaintOnScreen);
#endif
	setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_NativeWindow);
	setFocusPolicy(Qt::StrongFocus);

	qApp->installEventFilter(this);

	connect(qApp, &QApplication::applicationStateChanged, [this]() {
		if (qApp->applicationState() == Qt::ApplicationActive || this->getUpdate() == 1)
		{
			if (timer_update == -1)
				timer_update = startTimer(0);
		} else
		{
			killTimer(timer_update);
			timer_update = -1;
		}
	});
}

AppQt::~AppQt()
{
}

//////////////////////////////////////////////////////////////////////////
// Events
//////////////////////////////////////////////////////////////////////////

QPaintEngine *AppQt::paintEngine() const
{
	return NULL;
}

bool AppQt::eventFilter(QObject *obj, QEvent *event)
{
	Q_UNUSED(obj);

	if (event->type() == QEvent::MouseMove)
		mouseMoveEvent(static_cast<QMouseEvent *>(event));

	return false;
}

void AppQt::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == timer_update)
		update_engine();

	QWidget::timerEvent(event);
}

void AppQt::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event);

	timer_resize = 1;
	if (Unigine::Engine::isInitialized())
	{
		int width = size().width();
		int height = size().height();
		if (window_width != width || window_height != height)
		{
			window_width = width;
			window_height = height;
			resize_window();
		}
	}
}

void AppQt::mousePressEvent(QMouseEvent *event)
{
	if (event->button() & Qt::LeftButton)
	{
		mouse_button |= BUTTON_LEFT;
		buttonPress(BUTTON_LEFT);
	}
	if (event->button() & Qt::MidButton)
	{
		mouse_button |= BUTTON_MIDDLE;
		buttonPress(BUTTON_MIDDLE);
	}
	if (event->button() & Qt::RightButton)
	{
		mouse_button |= BUTTON_RIGHT;
		buttonPress(BUTTON_RIGHT);
	}
	QWidget::mousePressEvent(event);
}

void AppQt::mouseReleaseEvent(QMouseEvent *event)
{
	if ((event->button() & Qt::LeftButton) && (mouse_button & BUTTON_LEFT))
	{
		mouse_release |= BUTTON_LEFT;
		buttonRelease(BUTTON_LEFT);
	}
	if ((event->button() & Qt::MidButton) && (mouse_button & BUTTON_MIDDLE))
	{
		mouse_release |= BUTTON_MIDDLE;
		buttonRelease(BUTTON_MIDDLE);
	}
	if ((event->button() & Qt::RightButton) && (mouse_button & BUTTON_RIGHT))
	{
		mouse_release |= BUTTON_RIGHT;
		buttonRelease(BUTTON_RIGHT);
	}
	QWidget::mouseReleaseEvent(event);
}

void AppQt::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	mouse_button |= BUTTON_DCLICK;
	mouse_release |= BUTTON_LEFT;
	buttonPress(BUTTON_DCLICK);
}

void AppQt::wheelEvent(QWheelEvent *event)
{
	if (event->orientation() == Qt::Horizontal)
		mouse_axes[AXIS_X] += event->delta() / 120;
	else
		mouse_axes[AXIS_Y] += event->delta() / 120;
	QWidget::wheelEvent(event);
}

void AppQt::mouseMoveEvent(QMouseEvent *event)
{
	QPoint pos = mapFromGlobal(event->globalPos());
	mouse_x = pos.x();
	mouse_y = pos.y();
	QWidget::mouseMoveEvent(event);
}

void AppQt::update_engine()
{
#ifdef _LINUX
	QApplication::processEvents(QEventLoop::DialogExec);
#endif

	mouse_button &= ~mouse_release;
	mouse_release = 0;

	// update engine
	if (Unigine::Engine::isInitialized() && timer_resize == 0)
	{
		doUpdate();
		doRender();
		doSwap();
	}

	timer_resize = 0;

	// update widget
	QWidget::update();

	// clear mouse axes
	for (int i = 0; i < NUM_AXES; i++)
		mouse_axes[i] = 0;

	// release mouse button
	if (mouse_button & BUTTON_DCLICK)
	{
		mouse_button &= ~BUTTON_DCLICK;
		buttonRelease(BUTTON_DCLICK);
	}

	if (qApp->applicationState() == Qt::ApplicationActive)
	{
		Qt::KeyboardModifiers modifiers = qApp->queryKeyboardModifiers();
		if ((modifiers & Qt::ShiftModifier))
		{
			keys[KEY_SHIFT] = 1;
			keyPress(KEY_SHIFT);
		} else
		{
			keys[KEY_SHIFT] = 0;
			keyRelease(KEY_SHIFT);
		}
		if ((modifiers & Qt::AltModifier))
		{
			keys[KEY_ALT] = 1;
			keyPress(KEY_ALT);
		} else
		{
			keys[KEY_ALT] = 0;
			keyRelease(KEY_ALT);
		}
		unsigned int control_key = KEY_CTRL;
#ifdef _MACOS
		control_key = KEY_CMD;
		if ((modifiers & Qt::MetaModifier))
		{
			keys[KEY_CTRL] = 1;
			keyPress(KEY_CTRL);
		} else
		{
			keys[KEY_CTRL] = 0;
			keyRelease(KEY_CTRL);
		}
#endif
		if ((modifiers & Qt::ControlModifier))
		{
			keys[control_key] = 1;
			keyPress(control_key);
		} else
		{
			keys[control_key] = 0;
			keyRelease(control_key);
		}
	}

#ifdef _MACOS
	if (this->rect().contains(this->mapFromGlobal(this->cursor().pos())))
	{
		if (!mouse_show && parentWidget()->cursor().shape() != Qt::BlankCursor)
			parentWidget()->setCursor(QCursor(Qt::BlankCursor));
	} else
		parentWidget()->unsetCursor();
#endif
}

void AppQt::keyPressEvent(QKeyEvent *event)
{
	unsigned int key = translate_key_from_qt(event->key());
	if (key == 0)
		key = translate_native_key_from_event(event);

	if (key < NUM_KEYS)
		keys[key] = 1;
	if (key >= KEY_ESC && key <= KEY_F12)
		keyPressUnicode(key);
	else
	{
		const QChar *s = event->text().unicode();
		if (s)
			keyPressUnicode(s->unicode());
	}
	if (key)
		keyPress(key);
	QWidget::keyPressEvent(event);
}

void AppQt::keyReleaseEvent(QKeyEvent *event)
{
	unsigned int key = translate_key_from_qt(event->key());
	if (key == 0)
		key = translate_native_key_from_event(event);

	if (key < NUM_KEYS)
		keys[key] = 0;
	if (key)
		keyRelease(key);
	QWidget::keyReleaseEvent(event);
}

void AppQt::focusInEvent(QFocusEvent *event)
{
	QWidget::focusInEvent(event);
}

void AppQt::focusOutEvent(QFocusEvent *event)
{
	window_frame = 0;

	// release keys if switched to non interface window
	QWindow *obj = qApp->focusWindow();
	if (obj && obj->objectName() != "interface window")
	{
		for (int i = 0; i < NUM_KEYS; i++)
		{
			if (keys[i])
			{
				keyRelease(i);
				keys[i] = 0;
			}
		}
	}

	QWidget::focusOutEvent(event);
}

//////////////////////////////////////////////////////////////////////////
// App interface
//////////////////////////////////////////////////////////////////////////

void *AppQt::getHandle()
{
	return (void *)winId();
}

int AppQt::setPosition(int x, int y)
{
	if (parent())
		parentWidget()->move(mapFromParent({x, y}));
	else
		move(mapFromGlobal({x, y}));
	return 0;
}

int AppQt::getPositionX()
{
	return mapToGlobal({0, 0}).x();
}

int AppQt::getPositionY()
{
	return mapToGlobal({0, 0}).y();
}

int AppQt::setVideoMode(int width, int height, int flags, int refresh)
{
	Q_UNUSED(refresh);

	window_width = width;
	window_height = height;
	window_flags = flags;
	Unigine::Log::message("Set %s video mode\n", getVideoModeName());

	QWidget *parent_widget = parentWidget();

	setMinimumSize(640, 480);
	setMaximumSize(1000000, 1000000);

	if (parent_widget)
	{
		parent_widget->layout()->setSizeConstraint(QLayout::SetMinAndMaxSize);
		parent_widget->setMaximumSize(this->maximumSize());
		parent_widget->setWindowFlags(parent_widget->windowFlags() | Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint);

		if ((flags & App::FULLSCREEN) != 0)
		{
			parent_widget->showFullScreen();
			return 1;
		} else {
			parent_widget->showNormal();
			parent_widget->show();
		}

		int width_delta = parent_widget->size().width() - size().width();
		int height_delta = parent_widget->size().height() - size().height();
		parent_widget->resize(width + width_delta, height + height_delta);
	}
	resize(width, height);

	QCoreApplication::processEvents();

	create_context();

	return 1;
}

int AppQt::restoreVideoMode()
{
	return destroy_context();
}

int AppQt::setUpdate(int update)
{
	window_update = update;
	return 1;
}

int AppQt::setGamma(float value)
{
	Q_UNUSED(value);
	return 1;
}

int AppQt::setTitle(const char *title)
{
	QString t = title;

	if (parent())
	{
		QWidget *widget = qobject_cast<QWidget *>(parent());
		widget->setWindowTitle(t);
	} else
		setWindowTitle(t);
	return 1;
}

int AppQt::setIcon(const unsigned char *data, int size)
{
	Q_UNUSED(data);
	Q_UNUSED(size);
	return 0;
}

int AppQt::getWidth()
{
	return window_width;
}

int AppQt::getHeight()
{
	return window_height;
}

void AppQt::setWidth(int value)
{
	Q_UNUSED(value);
}

void AppQt::setHeight(int value)
{
	Q_UNUSED(value);
}

int AppQt::getFlags()
{
	return window_flags;
}

int AppQt::getUpdate()
{
	return window_update;
}

void AppQt::setMouse(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
	QCursor::setPos(mapToGlobal(QPoint(x, y)));
}

void AppQt::setMouseGrab(int grab)
{
	if (mouse_grab == grab)
		return;
	mouse_grab = grab;
	if (grab)
		grabMouse();
	else
		releaseMouse();
}

void AppQt::setMouseShow(int show)
{
	if (mouse_show == show)
		return;
	mouse_show = show;
	if (show)
		setCursor(QCursor(Qt::ArrowCursor));
	else
		setCursor(QCursor(Qt::BlankCursor));
}

int AppQt::setMouseCursor(const unsigned char *data, int size, int x, int y)
{
	Q_UNUSED(data);
	Q_UNUSED(size);
	Q_UNUSED(x);
	Q_UNUSED(y);
	return 0;
}

int AppQt::getMouseX()
{
	return mouse_x;
}

int AppQt::getMouseY()
{
	return mouse_y;
}

int AppQt::getMouseGrab()
{
	return mouse_grab;
}

int AppQt::getMouseShow()
{
	return mouse_show;
}

void AppQt::setMouseAxis(int axis, int value)
{
	if (axis < 0 || axis >= NUM_AXES)
		return;
	mouse_axes[axis] = value;
}

int AppQt::getMouseAxis(int axis)
{
	if (axis < 0 || axis >= NUM_AXES)
		return 0;
	return mouse_axes[axis];
}

int AppQt::clearMouseAxis(int axis)
{
	if (axis < 0 || axis >= NUM_AXES)
		return 0;
	int ret = mouse_axes[axis];
	mouse_axes[axis] = 0;
	return ret;
}

void AppQt::setMouseButton(int button)
{
	mouse_button = button;
}

int AppQt::getMouseButton()
{
	return mouse_button;
}

int AppQt::getMouseButtonState(int button)
{
	return ((mouse_button & button) != 0);
}

int AppQt::clearMouseButtonState(int button)
{
	int ret = ((mouse_button & button) != 0);
	mouse_button &= ~button;
	return ret;
}

int AppQt::getNumTouches()
{
	return 0;
}

int AppQt::getTouchX(int touch)
{
	Q_UNUSED(touch);
	return -1000000;
}

int AppQt::getTouchY(int touch)
{
	Q_UNUSED(touch);
	return -1000000;
}

void AppQt::setKeyState(int key, int state)
{
	if (key < 0 || key >= NUM_KEYS)
		return;
	keys[key] = state;
}

int AppQt::getKeyState(int key)
{
	if (key < 0 || key >= NUM_KEYS)
		return 0;
	return keys[key];
}

int AppQt::clearKeyState(int key)
{
	if (key < 0 || key >= NUM_KEYS)
		return 0;
	int ret = keys[key];
	keys[key] = 0;
	return ret;
}

void AppQt::setClipboard(const char *str)
{
	QApplication::clipboard()->setText(str);
}

const char *AppQt::getClipboard()
{
	static char clipboard[4096] = {0};

	const QByteArray &utf8_str = QApplication::clipboard()->text().toUtf8();
	const int size = qMin(4095, utf8_str.size());

	strncpy(clipboard, utf8_str.data(), size);
	clipboard[size] = '\0';

	return clipboard;
}

int AppQt::isDone()
{
	return 0;
}

void AppQt::doUpdate()
{
	App::update();
}

void AppQt::doRender()
{
	context->renderWindow();
	App::render();
}

void AppQt::doSwap()
{
	App::swap();
	swap_window();
}

void AppQt::exit()
{
	close();
	closed();
	QCoreApplication::quit();
}

int AppQt::dialogMessage(const char *title, const char *str, const char *flags)
{
	Q_UNUSED(flags);
	int ret = QMessageBox::warning(this, title, str, QMessageBox::Ok, QMessageBox::Cancel);
	return (ret == QMessageBox::Ok);
}

int AppQt::dialogFile(const char *title, char *name, int size, const char *filter, const char *flags)
{
	Q_UNUSED(flags);
	Q_UNUSED(filter);
	QString str = QFileDialog::getOpenFileName(this, title, name, QString::null, 0);
	strncpy(name, str.toUtf8().data(), size);
	name[size - 1] = '\0';
	return 1;
}

int AppQt::create_context()
{
	if (!context->isReady())
	{
		App::destroy();
		context->destroyContext();
		context->createVisual();
#ifdef _LINUX
		Window w = windowHandle()->winId();
		context->createContext(&w, getWidth(), getHeight());
#else
		context->createContext((void*)winId(), getWidth(), getHeight());
#endif
	} else {
		context->resizeWindow(getWidth(), getHeight());
	}

	return 1;
}

int AppQt::destroy_context()
{
	context->destroyContext();
	return 1;
}

int AppQt::resize_window()
{
	if (context)
		context->resizeWindow(getWidth(), getHeight());
	return 1;
}

int AppQt::swap_window()
{
	context->swapWindow();
	return 1;
}


unsigned int AppQt::translate_key_from_qt(int key) const
{
	using namespace Unigine;
	unsigned int ret = 0;
	switch (key)
	{
		case Qt::Key_Escape: ret = App::KEY_ESC; break;
		case Qt::Key_Tab: ret = App::KEY_TAB; break;
		case Qt::Key_Backspace: ret = App::KEY_BACKSPACE; break;
		case Qt::Key_Return: ret = App::KEY_RETURN; break;
		case Qt::Key_Enter: ret = App::KEY_RETURN; break;
		case Qt::Key_Delete: ret = App::KEY_DELETE; break;
		case Qt::Key_Insert: ret = App::KEY_INSERT; break;
		case Qt::Key_Home: ret = App::KEY_HOME; break;
		case Qt::Key_End: ret = App::KEY_END; break;
		case Qt::Key_PageUp: ret = App::KEY_PGUP; break;
		case Qt::Key_PageDown: ret = App::KEY_PGDOWN; break;
		case Qt::Key_Left: ret = App::KEY_LEFT; break;
		case Qt::Key_Right: ret = App::KEY_RIGHT; break;
		case Qt::Key_Up: ret = App::KEY_UP; break;
		case Qt::Key_Down: ret = App::KEY_DOWN; break;
		case Qt::Key_Shift: ret = App::KEY_SHIFT; break;
		case Qt::Key_Control: ret = App::KEY_CTRL; break;
		case Qt::Key_Alt: ret = App::KEY_ALT; break;
		case Qt::Key_F1: ret = App::KEY_F1; break;
		case Qt::Key_F2: ret = App::KEY_F2; break;
		case Qt::Key_F3: ret = App::KEY_F3; break;
		case Qt::Key_F4: ret = App::KEY_F4; break;
		case Qt::Key_F5: ret = App::KEY_F5; break;
		case Qt::Key_F6: ret = App::KEY_F6; break;
		case Qt::Key_F7: ret = App::KEY_F7; break;
		case Qt::Key_F8: ret = App::KEY_F8; break;
		case Qt::Key_F9: ret = App::KEY_F9; break;
		case Qt::Key_F10: ret = App::KEY_F10; break;
		case Qt::Key_F11: ret = App::KEY_F11; break;
		case Qt::Key_F12: ret = App::KEY_F12; break;
		default:
		{
			if (key < App::NUM_KEYS)
			{
				ret = key;
				if (ret >= 'A' && ret <= 'Z')
					ret -= 'A' - 'a';
				else if (ret == '!')
					ret = '1';
				else if (ret == '@')
					ret = '2';
				else if (ret == '#')
					ret = '3';
				else if (ret == '$')
					ret = '4';
				else if (ret == '%')
					ret = '5';
				else if (ret == '^')
					ret = '6';
				else if (ret == '&')
					ret = '7';
				else if (ret == '*')
					ret = '8';
				else if (ret == '(')
					ret = '9';
				else if (ret == ')')
					ret = '0';
				else if (ret == '_')
					ret = '-';
				else if (ret == '+')
					ret = '=';
				else if (ret == '{')
					ret = '[';
				else if (ret == '}')
					ret = ']';
				else if (ret == '|')
					ret = '\\';
				else if (ret == ':')
					ret = ';';
				else if (ret == '"')
					ret = '\'';
				else if (ret == '>')
					ret = '.';
				else if (ret == '?')
					ret = '/';
			}
		}
	}
	return ret;
}

int AppQt::translate_key_to_qt(unsigned int key) const
{
	using namespace Unigine;
	int ret = 0;
	switch (key)
	{
		case App::KEY_ESC: ret = Qt::Key_Escape; break;
		case App::KEY_TAB: ret = Qt::Key_Tab; break;
		case App::KEY_BACKSPACE: ret = Qt::Key_Backspace; break;
		case App::KEY_RETURN: ret = Qt::Key_Return; break;
		case App::KEY_DELETE: ret = Qt::Key_Delete; break;
		case App::KEY_INSERT: ret = Qt::Key_Insert; break;
		case App::KEY_HOME: ret = Qt::Key_Home; break;
		case App::KEY_END: ret = Qt::Key_End; break;
		case App::KEY_PGUP: ret = Qt::Key_PageUp; break;
		case App::KEY_PGDOWN: ret = Qt::Key_PageDown; break;
		case App::KEY_LEFT: ret = Qt::Key_Left; break;
		case App::KEY_RIGHT: ret = Qt::Key_Right; break;
		case App::KEY_UP: ret = Qt::Key_Up; break;
		case App::KEY_DOWN: ret = Qt::Key_Down; break;
		case App::KEY_SHIFT: ret = Qt::Key_Shift; break;
		case App::KEY_CTRL: ret = Qt::Key_Control; break;
		case App::KEY_CMD: ret = Qt::Key_Meta; break;
		case App::KEY_ALT: ret = Qt::Key_Alt; break;
		case App::KEY_SCROLL: ret = Qt::Key_ScrollLock; break;
		case App::KEY_CAPS: ret = Qt::Key_CapsLock; break;
		case App::KEY_NUM: ret = Qt::Key_NumLock; break;
		case App::KEY_F1: ret = Qt::Key_F1; break;
		case App::KEY_F2: ret = Qt::Key_F2; break;
		case App::KEY_F3: ret = Qt::Key_F3; break;
		case App::KEY_F4: ret = Qt::Key_F4; break;
		case App::KEY_F5: ret = Qt::Key_F5; break;
		case App::KEY_F6: ret = Qt::Key_F6; break;
		case App::KEY_F7: ret = Qt::Key_F7; break;
		case App::KEY_F8: ret = Qt::Key_F8; break;
		case App::KEY_F9: ret = Qt::Key_F9; break;
		case App::KEY_F10: ret = Qt::Key_F10; break;
		case App::KEY_F11: ret = Qt::Key_F11; break;
		case App::KEY_F12: ret = Qt::Key_F12; break;
		default:
		{
			if (key < App::NUM_KEYS)
			{
				ret = key;
				if (ret >= 'a' && ret <= 'z')
					ret -= 'a' - 'A';
			}
		}
	}
	return ret;
}

unsigned int AppQt::translate_native_key(unsigned int vkey) const
{
	using namespace Unigine;
	unsigned int ret = 0;
#ifdef _WIN32
	switch (vkey)
	{
		case VK_ESCAPE: ret = App::KEY_ESC; break;
		case VK_TAB: ret = App::KEY_TAB; break;
		case VK_RETURN: ret = App::KEY_RETURN; break;
		case VK_BACK: ret = App::KEY_BACKSPACE; break;
		case VK_DELETE: ret = App::KEY_DELETE; break;
		case VK_INSERT: ret = App::KEY_INSERT; break;
		case VK_HOME: ret = App::KEY_HOME; break;
		case VK_END: ret = App::KEY_END; break;
		case VK_PRIOR: ret = App::KEY_PGUP; break;
		case VK_NEXT: ret = App::KEY_PGDOWN; break;
		case VK_LEFT: ret = App::KEY_LEFT; break;
		case VK_RIGHT: ret = App::KEY_RIGHT; break;
		case VK_UP: ret = App::KEY_UP; break;
		case VK_DOWN: ret = App::KEY_DOWN; break;
		case VK_SHIFT: ret = App::KEY_SHIFT; break;
		case VK_CONTROL: ret = App::KEY_CTRL; break;
		case VK_MENU: ret = App::KEY_ALT; break;
		case VK_SCROLL: ret = App::KEY_SCROLL; break;
		case VK_CAPITAL: ret = App::KEY_CAPS; break;
		case VK_NUMLOCK: ret = App::KEY_NUM; break;
		case VK_F1: ret = App::KEY_F1; break;
		case VK_F2: ret = App::KEY_F2; break;
		case VK_F3: ret = App::KEY_F3; break;
		case VK_F4: ret = App::KEY_F4; break;
		case VK_F5: ret = App::KEY_F5; break;
		case VK_F6: ret = App::KEY_F6; break;
		case VK_F7: ret = App::KEY_F7; break;
		case VK_F8: ret = App::KEY_F8; break;
		case VK_F9: ret = App::KEY_F9; break;
		case VK_F10: ret = App::KEY_F10; break;
		case VK_F11: ret = App::KEY_F11; break;
		case VK_F12: ret = App::KEY_F12; break;
		case VK_LWIN: ret = App::KEY_CMD;
		case VK_RWIN: ret = App::KEY_CMD;
		default:
			ret = MapVirtualKeyW(vkey, 2);
			if (ret >= App::KEY_ESC)
				ret = 0;
			else if (ret >= 'A' && ret <= 'Z')
				ret -= (unsigned int)('A' - 'a');
	}
#elif _LINUX
	switch (vkey)
	{
		case 24: ret = 'q'; break;
		case 25: ret = 'w'; break;
		case 26: ret = 'e'; break;
		case 27: ret = 'r'; break;
		case 28: ret = 't'; break;
		case 29: ret = 'y'; break;
		case 30: ret = 'u'; break;
		case 31: ret = 'i'; break;
		case 32: ret = 'o'; break;
		case 33: ret = 'p'; break;
		case 34: ret = '['; break;
		case 35: ret = ']'; break;

		case 38: ret = 'a'; break;
		case 39: ret = 's'; break;
		case 40: ret = 'd'; break;
		case 41: ret = 'f'; break;
		case 42: ret = 'g'; break;
		case 43: ret = 'h'; break;
		case 44: ret = 'j'; break;
		case 45: ret = 'k'; break;
		case 46: ret = 'l'; break;
		case 47: ret = ';'; break;
		case 48: ret = '\''; break;
		case 49: ret = '`'; break;

		case 52: ret = 'z'; break;
		case 53: ret = 'x'; break;
		case 54: ret = 'c'; break;
		case 55: ret = 'v'; break;
		case 56: ret = 'b'; break;
		case 57: ret = 'n'; break;
		case 58: ret = 'm'; break;
		case 59: ret = ','; break;
		case 60: ret = '.'; break;
		case 61: ret = '/'; break;

		default: ret = 0;
	}
#endif
	return ret;
}

unsigned int AppQt::translate_native_key_from_event(QKeyEvent *event) const
{
#ifndef _LINUX
	unsigned int vkey = event->nativeVirtualKey();
#else
	unsigned int vkey = event->nativeScanCode();
#endif

	return translate_native_key(vkey);
}

int AppQt::translate_modifier_to_qt(unsigned int key) const
{
	int ret = 0;
	if ((key & (1 << 1)) != 0)
		ret += Qt::CTRL;
	if ((key & (1 << 0)) != 0)
		ret += Qt::SHIFT;
	if ((key & (1 << 2)) != 0)
		ret += Qt::ALT;
	return ret;
}
