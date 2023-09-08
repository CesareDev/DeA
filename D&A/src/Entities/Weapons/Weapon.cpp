#include "pch.h"
#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

EntityType Weapon::GetType() const
{
    return EntityType::Weapon;
}

void Weapon::SetAngle(sf::RenderTarget& target)
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
    sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
    if (!m_IsAttacking)
        m_Angle = (atan2f(mpos.y - getPosition().y, mpos.x - getPosition().x) * 180.f / acos(-1.f));
    if (GetId() == EntityID::Bow)
    {
        setRotation(m_Angle);
    }
    else if (GetId() >= EntityID::HealthPotion)
    {
        if (!m_IsAttacking)
            setRotation(m_Angle);
    }
    else
    {
        if (!m_IsAttacking)
            setRotation(m_Angle + 90.f);
    }
}
