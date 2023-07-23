#include "pch.h"
#include "Application.h"

Application::Application()
{
	m_Window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "D&A", sf::Style::Default);
	m_StateManager.Init();
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
		{
			m_Window.close();
		}
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
