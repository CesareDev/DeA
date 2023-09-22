#include "pch.h"
#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Init(const ResourceManager& resourceManager, const sf::IntRect& textureRect, const sf::Vector2f& position)
{
	m_TextureRect = textureRect;
	m_Position = position;
	setTexture(resourceManager.GetTilesetTexture());
	setPosition(m_Position);
	setTextureRect(m_TextureRect);
}

bool Button::isClicked()
{
	return m_Clicked;
}

void Button::Move(float offsetX, float offsetY)
{
	m_Position.x += offsetX;
	m_Position.y += offsetY;
}

void Button::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

const sf::Vector2f& Button::GetPosition()
{
	return m_Position;
}

void Button::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	setTextureRect(m_TextureRect);
	setPosition(m_Position);
	m_Clicked = false;
	if (getGlobalBounds().contains(mpos))
	{
		if (sf::Joystick::isButtonPressed(0, 1))
		{
			setTextureRect({ m_TextureRect.left + 106, m_TextureRect.top, m_TextureRect.width + 2, m_TextureRect.height + 2 });
			setPosition(m_Position.x - 1, m_Position.y);
			m_Pressed = true;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			setTextureRect({ m_TextureRect.left + 106, m_TextureRect.top, m_TextureRect.width + 2, m_TextureRect.height + 2 });
			setPosition(m_Position.x - 1, m_Position.y);
			m_Pressed = true;
		}
		else
		{
			setTextureRect({ m_TextureRect.left + 52, m_TextureRect.top, m_TextureRect.width + 2, m_TextureRect.height + 2 });
			setPosition(m_Position.x - 1, m_Position.y - 1);
			if (m_Pressed)
			{
				m_Clicked = true;
				m_Pressed = false;
				MUSIC::CLICK_SOUND->play();
			}
		}
	}
	else
	{
		m_Pressed = false;
	}
	target.draw(*this);
}
