#include "pch.h"
#include "DemonBoss.h"

DemonBoss::DemonBoss()
{
}

DemonBoss::~DemonBoss()
{
}

void DemonBoss::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
    setTexture(resourceManager.GetTilesetTexture());
    setTextureRect({ 0, 352, 32, 48 });
    setOrigin(0.f, 16.f);
    SetPosition(position);

    m_Bounds.size = { 32.f, 32.f };
    m_IsMoving = false;
    m_ElapsedAnimationTime = 0.f;
    m_TextureRect = getTextureRect();

    m_Health = 10;
    m_Vulnerable = true;
    const auto& font = resourceManager.GetFont();
    const_cast<sf::Texture&>(font.getTexture(40)).setSmooth(false);
    m_DamageTaken.setFont(font);
    m_DamageTaken.setCharacterSize(40);
    m_DamageTaken.setScale(0.f, 0.f);
    m_DamageTaken.setOutlineColor(sf::Color::Black);
    m_DamageTaken.setOutlineThickness(4.f);
}

void DemonBoss::Update(UpdateArgs args, float dt)
{
	if (m_Health > 0)
	{
		//Moving
		m_IsMoving = false;
		m_Velocity = { 0.f, 0.f };

		//Animation
		m_ElapsedAnimationTime += dt;
		if (m_ElapsedAnimationTime > 0.1f)
		{
			if (m_IsMoving)
			{
				m_TextureRect.top = 400;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 32;
				if (m_TextureRect.left >= 128)
				{
					m_TextureRect.left = 0;
				}
				m_ElapsedAnimationTime = 0.f;
			}
			else
			{
				m_TextureRect.top = 352;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 32;
				if (m_TextureRect.left >= 128)
				{
					m_TextureRect.left = 0;
				}
				m_ElapsedAnimationTime = 0.f;
			}
		}

		DamageAnimation(dt);
	}
	else
	{
		DeathAnimation(dt);
	}
}

void DemonBoss::Render(sf::RenderTarget& target)
{
    target.draw(*this);
	if (m_VulnerableTime > 0.f)
	{
		sf::View currentCamera = target.getView();
		sf::View v(currentCamera.getCenter() * 5.f, currentCamera.getSize() * 5.f);
		target.setView(v);
		target.draw(m_DamageTaken);

		target.setView(currentCamera);
	}
}

void DemonBoss::SetPosition(const sf::Vector2f& position)
{
    setPosition(position);
    m_Center = position + sf::Vector2f(16.f, 16.f);
    m_Bounds.position = position;
}

EntityID DemonBoss::GetId() const
{
    return EntityID::DemonBoss;
}
