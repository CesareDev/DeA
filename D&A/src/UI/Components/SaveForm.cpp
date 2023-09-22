#include "pch.h"
#include "SaveForm.h"
#include <Windows.h>

SaveForm::SaveForm()
{
}

SaveForm::~SaveForm()
{
}

void SaveForm::Init(const ResourceManager& resourceManager, const sf::Vector2f& position, unsigned int saveNumber)
{
	m_TextureRect = {722, 123, 80, 32};
	m_Position = position;
	setTexture(resourceManager.GetTilesetTexture());
	setPosition(m_Position);
	setTextureRect(m_TextureRect);

	const auto& font = resourceManager.GetFont();
	const_cast<sf::Texture&>(font.getTexture(80)).setSmooth(false);
	m_Text.setFont(font);
	m_Text.setCharacterSize(80);

	//SAVE::INFO
	std::string s = SAVE::SAVE_MANAGER.GetInfo(saveNumber);
	if (s == "")
	{
		m_Text.setString("Save: " + std::to_string(saveNumber));
	}
	else
	{
		const_cast<sf::Texture&>(font.getTexture(40)).setSmooth(false);
		m_Text.setCharacterSize(40);
		m_Text.setString(s);
	}
	
	int x;
	if (s == "")
		x = int((getPosition().x * 5.f) + 200 - m_Text.getGlobalBounds().width / 2);
	else
		x = int((getPosition().x * 5.f) + 40);
	int y = int((getPosition().y * 5.f) + 80 - m_Text.getGlobalBounds().height / 2);
	m_TextPosition = { (float)x, (float)y };
	m_Text.setPosition(m_TextPosition);
	m_Text.setOutlineColor(sf::Color::Black);
	m_Text.setOutlineThickness(4.f);

	m_SaveIndex = saveNumber;
	m_DeleteButton.Init(resourceManager, { 794, 357, 16, 16 }, getPosition() + sf::Vector2f(getGlobalBounds().getSize().x + 8.f, 8.f));
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

bool SaveForm::SubmitDelete()
{
	return m_Delete;
}

void SaveForm::PerformDelete(bool canDelete)
{
	if (canDelete)
	{
		m_Text.setCharacterSize(80);
		m_Text.setString("Save: " + std::to_string(m_SaveIndex));
		int x = int((getPosition().x * 5.f) + 200 - m_Text.getGlobalBounds().width / 2);
		int y = int((getPosition().y * 5.f) + 80 - m_Text.getGlobalBounds().height / 2);
		m_TextPosition = { (float)x, (float)y };
		m_Text.setPosition(m_TextPosition);
		SAVE::SAVE_MANAGER.DeleteSave(m_SaveIndex);
	}
	m_Delete = false;
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
		if (sf::Joystick::isButtonPressed(0, 1))
		{
			setTextureRect({ m_TextureRect.left + 162, m_TextureRect.top, m_TextureRect.width + 2, m_TextureRect.height + 2 });
			setPosition(m_Position.x - 1, m_Position.y);
			m_Text.setPosition(m_TextPosition.x, m_TextPosition.y + 5);
			m_Pressed = true;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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
				MUSIC::CLICK_SOUND->play();
			}
		}
	}
	else
	{
		m_Pressed = false;
	}

	if (m_DeleteButton.isClicked() && m_Text.getString().getSize() > 7)
		m_Delete = true;

	target.draw(*this);
	m_DeleteButton.Render(target);
}
