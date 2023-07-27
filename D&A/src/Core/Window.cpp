#include "pch.h"
#include "Window.h"

Window::Window()
	: sf::RenderWindow()
{
	m_CursorImg.loadFromFile("../res/cursor64.png");
	m_Cursor.loadFromPixels(m_CursorImg.getPixelsPtr(), sf::Vector2u(64, 64), sf::Vector2u(0, 0));
	m_Icon.loadFromFile("../res/icon.png");
}

Window::~Window()
{
}

void Window::onCreate()
{
	sf::RenderWindow::onCreate();
	setMouseCursor(m_Cursor);
	setIcon(256, 256, m_Icon.getPixelsPtr());
	setVerticalSyncEnabled(true);
}