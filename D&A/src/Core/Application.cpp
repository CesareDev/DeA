#include "pch.h"
#include "Application.h"

Application::Application()
{
	m_ResourceManager.Init();
	
	m_Window.Init(m_ResourceManager);
	m_Window.create(sf::VideoMode(GLOBAL::WIN_WIDTH, GLOBAL::WIN_HEIGHT), "D&A", sf::Style::Default);

	m_StateManager.Init(m_ResourceManager);
}

Application::~Application()
{
}

void Application::Run()
{
	while (m_Window.isOpen())
	{
		PollEvent();
		Update();
		Render();
	}
}

void Application::PollEvent()
{
	while (m_Window.pollEvent(m_Event))
	{
		if (m_Event.type == sf::Event::Closed)
			m_Window.close();
		if (m_Event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			GLOBAL::MOUSEWHELL_OFFSET -= m_Event.mouseWheelScroll.delta;
	}
}

void Application::Update()
{
	m_ElapsedTime = m_Clock.restart().asSeconds();

	m_StateManager.Update(m_ElapsedTime);
}

void Application::Render()
{
	m_Window.clear();

	m_StateManager.Render(m_Window);

	m_Window.display();
}