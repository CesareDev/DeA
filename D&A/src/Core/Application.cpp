#include "pch.h"
#include "Application.h"

Application::Application()
{
	SAVE::SAVE_MANAGER.LoadConfig();

	m_ResourceManager.Init();
	m_Window.Init(m_ResourceManager);


	if (GLOBAL::FULLSCREEN)
		m_Window.create(sf::VideoMode().getFullscreenModes()[0], "D&A", sf::Style::Fullscreen);
	else
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

	HandleJoiystickInput(m_ElapsedTime);

	m_StateManager.Update(m_ElapsedTime);
}

void Application::Render()
{
	m_Window.clear();

	m_StateManager.Render(m_Window);

	m_Window.display();
}

void Application::HandleJoiystickInput(float dt)
{
	if (!GLOBAL::JOYSTICK_AVAILABLE)
		GLOBAL::JOYSTICK_AVAILABLE = sf::Joystick::isConnected(0);
	if (GLOBAL::JOYSTICK_AVAILABLE)
	{
		int rx = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
		int ry = sf::Joystick::getAxisPosition(0, sf::Joystick::R);

		sf::Vector2f mouseDir;

		if (std::abs(rx) < 10)
			mouseDir.x = 0.f;
		else if (rx > 10)
			mouseDir.x = (rx - 10.f) / 90.f;
		else
			mouseDir.x = (rx + 10.f) / 90.f;

		if (std::abs(ry) < 10)
			mouseDir.y = 0.f;
		else if (ry > 10)
			mouseDir.y = (ry - 10.f) / 90.f;
		else
			mouseDir.y = (ry + 10.f) / 90.f;

		sf::Vector2f mouseNextPos = sf::Vector2f(sf::Mouse::getPosition()) + mouseDir * 1024.f * dt;
		if (m_Window.hasFocus())
			sf::Mouse::setPosition(sf::Vector2i(mouseNextPos));
	}
}
