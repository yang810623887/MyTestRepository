/*********************************************************************************
*
* NameSpace: Qt_App_DLL
* ClassName: uniginewidget
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-20 17:49:01
* --------------------------------------------------------------------------------
* DateTime : 2018/08/20
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/
#include "uniginewidget.h"

#include <QtGui/QMouseEvent>
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QLayout>
#include <QClipboard>

#include <UnigineEngine.h>

#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "user32.lib")
#endif

UnigineWidget::UnigineWidget(QWidget *parent, Qt::WindowFlags flags)
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

	connect(qApp, &QApplication::applicationStateChanged,
		[this]()
			{
				if (timer_update == -1)
				{
					timer_update = startTimer(0);
				}
				else
				{
					killTimer(timer_update);
					timer_update = -1;
				}
			}
	);
}


UnigineWidget::~UnigineWidget()
{
}

QPaintEngine * UnigineWidget::paintEngine() const
{
	return NULL;
}

bool UnigineWidget::eventFilter(QObject *obj, QEvent *event)
{
	Q_UNUSED(obj);

	if (event->type() == QEvent::MouseMove)
	{
		mouseMoveEvent(static_cast<QMouseEvent *>(event));
	}
	return false;
}

void UnigineWidget::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == timer_update)
	{
		update_engine();
	}
	QWidget::timerEvent(event);
}

void UnigineWidget::resizeEvent(QResizeEvent *event)
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

void UnigineWidget::mousePressEvent(QMouseEvent *event)
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

void UnigineWidget::mouseReleaseEvent(QMouseEvent *event)
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

void UnigineWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	mouse_button |= BUTTON_DCLICK;
	mouse_release |= BUTTON_LEFT;
	buttonPress(BUTTON_DCLICK);
}

void UnigineWidget::wheelEvent(QWheelEvent *event)
{
	if (event->orientation() == Qt::Horizontal)
	{
		mouse_axes[AXIS_X] += event->delta() / 120;
	}
	else
	{
		mouse_axes[AXIS_Y] += event->delta() / 120;
	}
	QWidget::wheelEvent(event);
}

void UnigineWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint pos = mapFromGlobal(event->globalPos());
	mouse_x = pos.x();
	mouse_y = pos.y();
	QWidget::mouseMoveEvent(event);
}

void UnigineWidget::keyPressEvent(QKeyEvent *event)
{
	//if key not consist in Qt ,It will find in windows
	unsigned int key = translate_key_from_qt(event->key());
	if (key == 0)
	{
		key = translate_native_key_from_event(event);
	}
	if (key < NUM_KEYS)
	{
		keys[key] = 1;
	}
	if (key >= KEY_ESC && key <= KEY_F12)
	{
		keyPressUnicode(key);
	}
	else
	{
		const QChar *s = event->text().unicode();
		if (s)
		{
			keyPressUnicode(s->unicode());
		}
	}
	if (key)
	{
		keyPress(key);
	}
	QWidget::keyPressEvent(event);
}

void UnigineWidget::keyReleaseEvent(QKeyEvent *event)
{
	unsigned int key = translate_key_from_qt(event->key());
	if (key == 0)
	{
		key = translate_native_key_from_event(event);
	}
	if (key < NUM_KEYS)
	{
		keys[key] = 0;
	}
	if (key)
	{
		keyRelease(key);
	}
	QWidget::keyReleaseEvent(event);
}

void UnigineWidget::focusInEvent(QFocusEvent *event)
{
	QWidget::focusInEvent(event);
}




void UnigineWidget::update_engine()
{
#ifdef _LINUX
	QApplication::processEvents(QEventLoop::DialogExec);
#endif
	mouse_button &= ~mouse_release; //0000 0000 & 0111 1111 = 0000 0000
	mouse_release = 0;

	//update engine
	if (Unigine::Engine::isInitialized() && timer_resize == 0);
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
	{
		mouse_axes[i] = 0;
	}

	// release mouse button

	if (mouse_button & BUTTON_DCLICK) // 0000 0000 & 0000 0100 = 0000 0000 certify mouse_button state is not DClick
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
		} 
		else
		{
			keys[KEY_SHIFT] = 0;
			keyRelease(KEY_SHIFT);
		}

		if ((modifiers & Qt::AltModifier))
		{
			keys[KEY_ALT] = 1;
			keyPress(KEY_ALT);
		}
		else
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
		}
		else
		{
			keys[KEY_CTRL] = 0;
			keyRelease(KEY_CTRL);
		}
#endif
		if ((modifiers & Qt::ControlModifier))
		{
			keys[control_key] = 1;
			keyPress(control_key);
		}
		else
		{
			keys[control_key] = 0;
			keyRelease(control_key);
		}

	}
#ifdef _MACOS //if cursor is not in this widget unset Cursor else hide cursor
	if (this->rect().contains(this->mapFromGlobal(this->cursor().pos())))
	{
		if (!mouse_show && parentWidget()->cursor().shape() != Qt::BlankCursor)
			parentWidget()->setCursor(QCursor(Qt::BlankCursor));
	}
	else
		parentWidget()->unsetCursor();
#endif
}

int UnigineWidget::create_context()
{
	return 0;
}

int UnigineWidget::destroy_context()
{
	return 0;
}

int UnigineWidget::isDone()
{
	return 0;
}

void UnigineWidget::doUpdate()
{
	App::update();
}

void UnigineWidget::doRender()
{
	context->renderWindow();
	App::render();
}

void UnigineWidget::doSwap()
{
	App::swap();
	swap_window();
}

void UnigineWidget::exit()
{
}

int UnigineWidget::swap_window()
{
	context->swapWindow();
	return 1;
}

int UnigineWidget::resize_window()
{
	if (context)
	{
		context->resizeWindow(getWidth(), getHeight());
	}
	return 1;
}

int UnigineWidget::getWidth()
{
	return window_width;
}

int UnigineWidget::getHeight()
{
	return window_height;
}

void UnigineWidget::focusOutEvent(QFocusEvent *event)
{
	window_frame = 0;
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

unsigned int UnigineWidget::translate_key_from_qt(int key) const
{
	using namespace Unigine;
	unsigned int ret = 0;
	switch (key)
	{
		case Qt::Key_Escape:ret = App::KEY_ESC; break;
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

int UnigineWidget::translate_key_to_qt(unsigned int key) const
{
	return 0;
}

unsigned int UnigineWidget::translate_native_key_from_event(QKeyEvent *event) const
{
#ifndef _LINUX
	unsigned int vkey = event->nativeVirtualKey();
#else
	unsigned int vkey = event->nativeScanCode();//本地代码
#endif

	return translate_native_key(vkey);
}

int UnigineWidget::translate_modifier_to_qt(unsigned int key) const
{
	return 0;
}

unsigned int UnigineWidget::translate_native_key(unsigned int vkey) const
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




void * UnigineWidget::getHandle()
{
	return (void *)winId();
}

int UnigineWidget::setPosition(int x, int y)
{
	if (parent())
	{
		parentWidget()->move(mapFromParent({ x, y }));
	}
	else
	{
		move(mapFromGlobal({ x, y }));
	}
	return 0;

}

int UnigineWidget::getPositionX()
{
	return mapToGlobal({ 0, 0 }).x();
}

int UnigineWidget::getPositionY()
{
	return mapToGlobal({ 0, 0 }).y();
}
////////////////////////////////////////////没细看
int UnigineWidget::setVideoMode(int width, int height, int flags /*= 0*/, int refresh /*= 0*/)
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
		}
		else {
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

int UnigineWidget::restoreVideoMode()
{
	return 1;
}

int UnigineWidget::setUpdate(int update)
{
	return 1;
}

int UnigineWidget::setGamma(float gamma)
{
	return 1;
}

int UnigineWidget::setTitle(const char *title)
{
	return 1;
}

int UnigineWidget::setIcon(const unsigned char *data, int size)
{
	return 1;
}

void UnigineWidget::setWidth(int value)
{

}

void UnigineWidget::setHeight(int value)
{

}

int UnigineWidget::getFlags()
{
	return 1;
}

int UnigineWidget::getUpdate()
{
	return 1;
}

void UnigineWidget::setMouse(int x, int y)
{

}

void UnigineWidget::setMouseGrab(int grab)
{

}

void UnigineWidget::setMouseShow(int show)
{

}

int UnigineWidget::setMouseCursor(const unsigned char *data, int size, int x /*= 0*/, int y /*= 0*/)
{
	return 1;
}

int UnigineWidget::getMouseX()
{
	return 1;
}

int UnigineWidget::getMouseY()
{
	return 1;
}

int UnigineWidget::getMouseGrab()
{
	return 1;
}

int UnigineWidget::getMouseShow()
{
	return 0;
}

void UnigineWidget::setMouseAxis(int axis, int value)
{
}

int UnigineWidget::getMouseAxis(int axis)
{
	return 0;
}

int UnigineWidget::clearMouseAxis(int axis)
{
	return 0;
}

void UnigineWidget::setMouseButton(int button)
{
}

int UnigineWidget::getMouseButton()
{
	return 0;
}

int UnigineWidget::getMouseButtonState(int button)
{
	return 0;
}

int UnigineWidget::clearMouseButtonState(int button)
{
	return 0;
}

int UnigineWidget::getNumTouches()
{
	return 0;
}

int UnigineWidget::getTouchX(int touch)
{
	return 0;
}

int UnigineWidget::getTouchY(int touch)
{
	return 0;
}

void UnigineWidget::setKeyState(int key, int state)
{
}

int UnigineWidget::getKeyState(int key)
{
	return 0;
}

int UnigineWidget::clearKeyState(int key)
{
	return 0;
}

void UnigineWidget::setClipboard(const char * str)
{
}

const char * UnigineWidget::getClipboard()
{
	return nullptr;
}

