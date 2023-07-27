#pragma once
#include "ResourceManager.h"

class Window : public sf::RenderWindow
{
public:

	Window();
	~Window();

	void Init(const ResourceManager& resourceManager);

protected:

	void onCreate() override;

private:

	const ResourceManager* m_ResourceManager;
	sf::Cursor m_Cursor;
};

