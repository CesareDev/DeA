#include "pch.h"
#include "CheckBox.h"

CheckBox::CheckBox()
{
}

CheckBox::~CheckBox()
{
}

void CheckBox::Init(const ResourceManager& resourceManager, const sf::Vector2f& position, bool checked)
{
	m_Position = position;
	m_Checked = checked;
	m_TextureRect = { 776, 409, 14, 14 };
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect(m_TextureRect);
	setPosition(m_Position);
}

void CheckBox::Update(float dt)
{
}

void CheckBox::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	m_Clicked = false;
	if (m_Checked)
	{		
		setTextureRect({ m_TextureRect.left + 46, m_TextureRect.top, m_TextureRect.width + 2, m_TextureRect.height + 1 });
		setPosition(m_Position.x, m_Position.y - 1.f);
	}
	else
	{
		setTextureRect(m_TextureRect);
		setPosition(m_Position);
	}

	if (getGlobalBounds().contains(mpos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_Checked)
			{
				setTextureRect({ m_TextureRect.left + 80, m_TextureRect.top, m_TextureRect.width + 4, m_TextureRect.height + 3 });
				setPosition(m_Position.x - 1.f, m_Position.y - 1.f);
			}
			else
			{
				setTextureRect({ m_TextureRect.left + 30, m_TextureRect.top, m_TextureRect.width + 2, m_TextureRect.height + 2 });
				setPosition(m_Position.x - 1.f, m_Position.y);
			}
			m_Pressed = true;
		}
		else
		{
			if (m_Checked)
			{
				setTextureRect({ m_TextureRect.left + 62, m_TextureRect.top, m_TextureRect.width + 4, m_TextureRect.height + 3 });
				setPosition(m_Position.x - 1.f, m_Position.y - 2.f);
			}
			else
			{
				setTextureRect({ m_TextureRect.left + 14, m_TextureRect.top, m_TextureRect.width + 2, m_TextureRect.height + 2 });
				setPosition(m_Position.x - 1.f, m_Position.y - 1.f);
			}
			if (m_Pressed)
			{
				m_Checked = !m_Checked;
				m_Pressed = false;
				m_Clicked = true;
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

void CheckBox::SetChecked(bool value)
{
	m_Checked = value;
}

bool CheckBox::isChecked()
{
	return m_Checked;
}

bool CheckBox::isClicked()
{
	return m_Clicked;
}
