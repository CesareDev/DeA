#include "pch.h"
#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

EntityType Character::GetType() const
{
    return EntityType::Character;
}

void Character::TakeDamage(unsigned int damage)
{
	if (m_Vulnerable)
	{
		m_DamageTaken.setString(std::to_string(damage));
		m_Health -= damage;
		m_Vulnerable = false;
	}
}

void Character::DamageAnimation(float dt)
{
	m_DamageTaken.setPosition(int(getPosition().x * 5.f - m_DamageTaken.getGlobalBounds().width / 2.f + (m_Bounds.size.x / 2.f * 5.f)), int(getPosition().y * 5.f - m_DamageTaken.getGlobalBounds().height));
	if (!m_Vulnerable)
	{
		m_VulnerableTime += dt;
		if (m_VulnerableTime <= 0.5f)
		{
			if (m_DamageTaken.getScale().x < 1.f)
				m_DamageTaken.setScale(4.f * m_VulnerableTime, 4.f * m_VulnerableTime);
			else
				m_DamageTaken.setScale(1.f, 1.f);
			m_IntervalTime += dt;
			setColor(sf::Color::White);
			if (m_IntervalTime < 0.1f)
				setColor(sf::Color::Red);
			else
				m_IntervalTime = 0.f;
		}
		else
		{
			setColor(sf::Color::White);
			m_DamageTaken.setScale(0.f, 0.f);
			m_Vulnerable = true;
			m_VulnerableTime = 0.f;
		}
	}
}

void Character::DeathAnimation(float dt)
{
	m_VulnerableTime += dt;
	m_DamageTaken.setPosition(int(getPosition().x * 5.f - m_DamageTaken.getGlobalBounds().width / 2.f + (m_Bounds.size.x / 2.f * 5.f)), int(getPosition().y * 5.f - m_DamageTaken.getGlobalBounds().height - 80.f));
	sf::Vector2f st = m_DamageTaken.getScale();
	if (st.x <= 1.f)
		m_DamageTaken.setScale(st.x + 4.f * dt, st.y + 4.f * dt);
	sf::Vector2f o = getOrigin();
	setOrigin(o.x, 24.f);
	sf::Vector2f s = getScale();
	setColor(sf::Color(50, 50, 50, 255)); //darkgrey
	if (s.y == 1.f)
		setPosition({ getPosition().x, getPosition().y + m_Bounds.size.y });
	if (s.y > 0.f)
		setScale(s.x, s.y - dt);
	else
	{
		m_DamageTaken.setScale(0.f, 0.f);
		m_VulnerableTime = 0.f;
		m_IsDead = true;
	}
}
