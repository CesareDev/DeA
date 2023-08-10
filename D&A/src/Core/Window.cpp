#include "pch.h"
#include "Window.h"

Window::Window()
	: sf::RenderWindow()
{
}

Window::~Window()
{
}

void Window::Init(const ResourceManager& resourceManager)
{
	m_ResourceManager = &resourceManager;
	m_Cursor.loadFromPixels(m_ResourceManager->GetCursoImg().getPixelsPtr(), sf::Vector2u(32, 32), sf::Vector2u(0, 0));
}

void Window::onCreate()
{
	sf::RenderWindow::onCreate();
	setMouseCursor(m_Cursor);
	setIcon(256, 256, m_ResourceManager->GetIcon().getPixelsPtr());
	setVerticalSyncEnabled(true);
}