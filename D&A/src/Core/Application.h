#pragma once
#include "StateManager.h"
#include "Window.h"
#include "ResourceManager.h"

class Application
{
public:
	
	Application();
	~Application();
	void Run();

private:

	void PollEvent();
	void Update();
	void Render();

	void HandleJoiystickInput(float dt);

private:

	Window m_Window;
	sf::Clock m_Clock;
	sf::Event m_Event;

	float m_ElapsedTime = 0.f;
	bool m_ChangingCursor = false;

	ResourceManager m_ResourceManager;
	StateManager m_StateManager;
};

