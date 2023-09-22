#include "pch.h"
#include "ScrollBar.h"

ScrollBar::ScrollBar()
{
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::Init(const ResourceManager& resourceManager, const sf::Vector2f& position, unsigned int* value)
{
	m_Value = value;

	m_SliderPosition = { position.x + 6.f + *m_Value, position.y + 6.f };
	m_Bar.setTexture(resourceManager.GetTilesetTexture());
    m_Bar.setTextureRect({ 776, 379, 132, 18 });
    m_Bar.setPosition(position);

    m_Slider.setTexture(resourceManager.GetTilesetTexture());
    m_SliderTextureRect = { 776, 399, 20, 6 };
    m_Slider.setTextureRect(m_SliderTextureRect);
    m_Slider.setPosition(m_SliderPosition);
}

void ScrollBar::Update(float dt)
{
	*m_Value = m_SliderPosition.x - m_Bar.getGlobalBounds().left - 6.f;
}

void ScrollBar::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	if (m_Slider.getGlobalBounds().contains(mpos) || m_Pressed)
	{
		if (sf::Joystick::isButtonPressed(0, 1))
		{
			m_Slider.setTextureRect({ m_SliderTextureRect.left + 42, m_SliderTextureRect.top, m_SliderTextureRect.width + 2, m_SliderTextureRect.height + 2 });
			m_SliderPosition.x = (mpos.x - m_Slider.getGlobalBounds().width / 2.f);
			if (m_SliderPosition.x < m_Bar.getGlobalBounds().left + 6.f)
				m_SliderPosition.x = m_Bar.getGlobalBounds().left + 6.f;
			if (m_SliderPosition.x + m_Slider.getGlobalBounds().width > m_Bar.getGlobalBounds().left + m_Bar.getGlobalBounds().width - 4.f)
				m_SliderPosition.x = m_Bar.getGlobalBounds().left + m_Bar.getGlobalBounds().width - m_Slider.getGlobalBounds().width - 4.f;
			m_Slider.setPosition(m_SliderPosition.x - 1.f, m_SliderPosition.y - 1.f);
			m_Pressed = true;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_Slider.setTextureRect({ m_SliderTextureRect.left + 42, m_SliderTextureRect.top, m_SliderTextureRect.width + 2, m_SliderTextureRect.height + 2 });
			m_SliderPosition.x = (mpos.x - m_Slider.getGlobalBounds().width / 2.f);
			if (m_SliderPosition.x < m_Bar.getGlobalBounds().left + 6.f)
				m_SliderPosition.x = m_Bar.getGlobalBounds().left + 6.f;
			if (m_SliderPosition.x + m_Slider.getGlobalBounds().width > m_Bar.getGlobalBounds().left + m_Bar.getGlobalBounds().width - 4.f)
				m_SliderPosition.x = m_Bar.getGlobalBounds().left + m_Bar.getGlobalBounds().width - m_Slider.getGlobalBounds().width - 4.f;
			m_Slider.setPosition(m_SliderPosition.x - 1.f, m_SliderPosition.y - 1.f);
			m_Pressed = true;
		}
		else
		{
			m_Slider.setTextureRect({ m_SliderTextureRect.left + 20, m_SliderTextureRect.top, m_SliderTextureRect.width + 2, m_SliderTextureRect.height + 2 });
			m_Slider.setPosition(m_SliderPosition.x - 1.f, m_SliderPosition.y - 1.f);
			m_Pressed = false;
		}
	}
	else
	{
		m_Slider.setTextureRect(m_SliderTextureRect);
		m_Slider.setPosition(m_SliderPosition);
	}
	target.draw(m_Bar);
	target.draw(m_Slider);
}

unsigned int ScrollBar::GetValue()
{
    return *m_Value;
}
