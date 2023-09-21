#include "pch.h"
#include "ColossalSword.h"
#include "Entities/Characters/Character.h"

ColossalSword::ColossalSword()
{
}

ColossalSword::~ColossalSword()
{
}

void ColossalSword::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
    setTexture(resourceManager.GetTilesetTexture());
    setTextureRect({ 322, 81, 12, 30 });
    setOrigin(6.f, 37.f);

    m_Bounds.size = { 74.f, 74.f };
    m_HitPoints.resize(4);

    SetPosition(position);
}

void ColossalSword::Update(UpdateArgs args, float dt)
{
    Attack(dt);
    if (m_CanHit)
    {
        for (const auto& it : args.qTree.search(m_Bounds))
        {
            if (it->obj->GetId() != EntityID::Player && it->obj->GetType() == EntityType::Character)
            {
                Character* en = (Character*)it->obj;
                for (const auto& p : m_HitPoints)
                    if (en->GetBounds().contains(p))
                        en->TakeDamage(18);
            }
        }
    }
}

void ColossalSword::Render(sf::RenderTarget& target)
{
    target.draw(*this);
}

void ColossalSword::SetPosition(const sf::Vector2f& position)
{
    setPosition(position);
    sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
    m_HitPoints[0] = position + 17.f * dir;
    m_HitPoints[1] = position + 22.f * dir;
    m_Center = m_HitPoints[1];
    m_HitPoints[2] = position + 27.f * dir;
    m_HitPoints[3] = position + 34.f * dir;
    m_Bounds.position = position - sf::Vector2f(37.f, 37.f);
}

EntityID ColossalSword::GetId() const
{
    return EntityID::ColossalSword;
}

void ColossalSword::Attack(float dt)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking)
    {
        m_IsAttacking = true;
        m_AttackAngle = m_Angle;
    }
    if (m_IsAttacking)
    {
        m_ElapsedTime += dt;
        if (m_ElapsedTime <= 0.75f)
        {
            m_Angle = -120 * sinf((2.f / 3.f) * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
            setRotation(m_Angle + 90.f);
        }
        else if (m_ElapsedTime > 0.9f && m_ElapsedTime <= 1.4f)
        {
            if (!m_CanHit)
                MUSIC::ATTACK_SOUND->play();
            m_CanHit = true;
            m_Angle = 720 * sinf(acos(-1.f) * (m_ElapsedTime - 0.9f)) + m_AttackAngle;
            setRotation(m_Angle + 90.f);
        }
        else if (m_ElapsedTime > 1.4f)
        {
            m_CanHit = false;
            m_ElapsedTime = 0.f;
            m_IsAttacking = false;
        }
    }
}
