#pragma once

class Window : public sf::RenderWindow
{
public:

	Window();
	~Window();

protected:

	void onCreate() override;

private:

	sf::Image m_CursorImg;
	sf::Cursor m_Cursor;
	sf::Image m_Icon;
};

