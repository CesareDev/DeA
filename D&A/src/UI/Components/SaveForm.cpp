#include "pch.h"
#include "SaveForm.h"

SaveForm::SaveForm()
{
}

SaveForm::~SaveForm()
{
}

void SaveForm::Init(const TextureManager& textureManager, const sf::Vector2f& position, unsigned int saveNumber)
{
	m_TextureRect = {722, 123, 80, 32};
	m_Position = position;
	setTexture(textureManager.GetTilesetTexture());
	setPosition(m_Position);
	setTextureRect(m_TextureRect);

	const auto& font = textureManager.GetFont();
	const_cast<sf::Texture&>(font.getTexture(100)).setSmooth(false);
	m_Text.setFont(font);
	m_Text.setCharacterSize(100);
	std::string s = "Save " + std::to_string(saveNumber);
	m_Text.setString(s);

	int x = int((getPosition().x * 5.f) + 200 - m_Text.getGlobalBounds().width / 2);
	int y = int((getPosition().y * 5.f) + 80 - m_Text.getGlobalBounds().height / 2);
	m_TextPosition = { (float)x, (float)y };
	m_Text.setPosition(m_TextPosition);
	m_Text.setOutlineColor(sf::Color::Black);
	m_Text.setOutlineThickness(5.f);
}

bool SaveForm::isClicked()
{
	return m_Clicked;
}

void SaveForm::Move(float offsetX, float offsetY)
{
	m_Position.x += offsetX;
	m_Position.y += offsetY;
}

const sf::Vector2f& SaveForm::GetPosition()
{
	return m_Position;
}

void SaveForm::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

const sf::Text& SaveForm::GetText()
{
	return m_Text;
}

void SaveForm::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	setTextureRect(m_TextureRect);
	setPosition(m_Position);
	m_Text.setPosition(m_TextPosition);
	m_Clicked = false;
	if (getGlobalBounds().contains(mpos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			setTextureRect({ m_TextureRect.left + 162, m_TextureRect.top, m_TextureRect.width + 2, m_TextureRect.height + 2 });
			setPosition(m_Position.x - 1, m_Position.y);
			m_Text.setPosition(m_TextPosition.x, m_TextPosition.y + 5);
			m_Pressed = true;
		}
		else
		{
			setTextureRect({ m_TextureRect.left + 80, m_TextureRect.top, m_TextureRect.width + 2, m_TextureRect.height + 2 });
			setPosition(m_Position.x - 1, m_Position.y - 1);
			if (m_Pressed)
			{
				m_Clicked = true;
				m_Pressed = false;
			}
		}
	}
	else
	{
		m_Pressed = false;
	}
	target.draw(*this);
}
