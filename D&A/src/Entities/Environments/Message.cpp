#include "pch.h"
#include "Message.h"

Message::Message()
{
}

Message::~Message()
{
}

void Message::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 384, 544, 16, 16 });

    const auto& font = resourceManager.GetFont();
    const_cast<sf::Texture&>(font.getTexture(80)).setSmooth(false);
    m_Text.setFont(font);
    m_Text.setCharacterSize(80);
    m_Text.setOutlineColor(sf::Color::Black);
    m_Text.setOutlineThickness(4.f);

    m_TextFrame.setFillColor(sf::Color(211, 191, 169));
    m_TextFrame.setOutlineColor(sf::Color(34, 34, 34));
    m_TextFrame.setOutlineThickness(5.f);

	SetPosition(position);
}

void Message::Update(UpdateArgs args, float dt)
{
    for (const auto& en : args.qTree.search(m_Bounds))
    {
        if (en->obj->GetId() == EntityID::Player)
        {
            auto d = sf::distance(en->obj->GetCenter(), GetCenter());
            if (d < 24.f)
            {
                if (m_AutoRead)
                {
                    m_Interact = true;
                    m_AutoRead = false;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_Pressed)
                {
                    m_Pressed = true;
                }
                else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_Pressed)
                {
                    m_Pressed = false;
                    m_Clicked = true;
                    m_Interact = !m_Interact;
                }
            }
            else
            {
                if (!m_AutoRead)
                    m_Interact = false;
            }
        }
    }
}

void Message::Render(sf::RenderTarget& target)
{
    target.draw(*this);
}

void Message::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Bounds.position = position - sf::Vector2f(16.f, 16.f);
	m_Bounds.size = { 48.f, 48.f };
	m_Center = position + sf::Vector2f(8.f, 8.f);
}

EntityID Message::GetId() const
{
	return EntityID::Message;
}

void Message::SetText(const std::string& text, bool autoRead)
{
    m_Text.setString(text);
    int x = 640 - m_Text.getGlobalBounds().width / 2.f;
    int y = 360 - m_Text.getGlobalBounds().height / 2.f;
    m_Text.setPosition(x, y);
    m_TextFrame.setPosition(x - 8.f, y - 8.f);
    m_TextFrame.setSize(m_Text.getGlobalBounds().getSize() + sf::Vector2f(16.f, 16.f));
    m_AutoRead = autoRead;
}

void Message::RenderText(sf::RenderTarget& target)
{
    if (m_Interact)
    {
        auto c = target.getView();
        sf::View v({ 0.f, 0.f, 1280, 720 });
        target.setView(v);
        target.draw(m_TextFrame);
        target.draw(m_Text);
        target.setView(c);
    }
}
