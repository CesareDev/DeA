#include "pch.h"
#include "Mace.h"
#include "Core/Camera.h"
#include "Entities/Characters/Character.h"

Mace::Mace()
{
}

Mace::~Mace()
{
}

void Mace::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 323, 57, 10, 22 });
	setOrigin(5.f, 29.f);

	m_Bounds.size = { 58.f, 58.f };
	m_HitPoints.resize(2);

	SetPosition(position);
}

void Mace::Update(UpdateArgs args, float dt)
{
	for (auto it = args.qTree.begin(); it != args.qTree.end(); ++it)
	{
		if (it->obj->GetId() == EntityID::Player)
			SetPosition(it->obj->GetCenter());
	}
	Attack(dt);
	if (m_CanHit)
	{
		for (const auto& it : args.qTree.search(m_Bounds))
		{
			if (it->obj->GetId() != EntityID::Player && it->obj->GetType() == EntityType::Character)
			{
				Character* en = (Character*)it->obj;
				for (const auto& p : m_HitPoints)
				{
					if (en->GetBounds().contains(p))
					{
						en->TakeDamage(2);
					}
				}
			}
		}
	}
}

void Mace::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	if (!m_IsAttacking)
		m_Angle = (atan2f(mpos.y - getPosition().y, mpos.x - getPosition().x) * 180.f / acos(-1.f)) + 90.f;

	target.draw(*this);
}

void Mace::SetPosition(const sf::Vector2f& position)
{
	sf::Vector2f dir = { cosf(m_AttackAngle * acos(-1.f) / 180.f), sinf(m_AttackAngle * acos(-1.f) / 180.f) };
	if (m_IsAttacking)
	{
		setOrigin(5.f, 22.f);
		setPosition(position + 7.f * dir);
		m_Center = getPosition() + 9.f * dir;
	}
	else
	{
		setOrigin(5.f, 29.f);
		setPosition(position);
		m_Center = position + 17.f * dir;
	}
	m_HitPoints[0] = m_Center;
	m_HitPoints[1] = m_Center + 9.f * dir;
	m_Bounds.position = getPosition() - sf::Vector2f(29.f, 29.f);
}

EntityID Mace::GetId() const
{
	return EntityID::Mace;
}

void Mace::Attack(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking)
	{
		m_IsAttacking = true;
		m_AttackAngle = m_Angle - 90.f;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking)
	{
		setRotation(m_Angle);
	}
	if (m_IsAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime <= 0.25f)
		{
			if (std::abs(m_AttackAngle) < 90.f)
			{
				m_Angle = m_AttackAngle - 60 * sinf(2 * acos(-1.f) * m_ElapsedTime) + 90.f;
			}
			else
			{
				m_Angle = m_AttackAngle + 60 * sinf(2 * acos(-1.f) * m_ElapsedTime) + 90.f;
			}
			setRotation(m_Angle);
		}
		else if (m_ElapsedTime > 0.25f && m_ElapsedTime <= 0.35f)
		{
			m_CanHit = true;
			if (std::abs(m_AttackAngle) < 90.f)
			{
				m_Angle = m_AttackAngle - 60.f + 120 * sinf(5 * acos(-1.f) * (m_ElapsedTime - 0.25f)) + 90.f;
			}
			else
			{
				m_Angle = m_AttackAngle + 60.f - 120 * sinf(5 * acos(-1.f) * (m_ElapsedTime - 0.25f)) + 90.f;
			}
			setRotation(m_Angle);
		}
		else if (m_ElapsedTime > 0.35f && m_ElapsedTime <= 0.5f)
		{
			m_CanHit = false;
			if (std::abs(m_AttackAngle) < 90.f)
			{
				m_Angle = m_AttackAngle + 60.f - 60 * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.35f)) + 90.f;
			}
			else
			{
				m_Angle = m_AttackAngle - 60.f + 60 * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.35f)) + 90.f;
			}
			setRotation(m_Angle);
		}
		else
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
	}
}