#include "pch.h"
#include "Katana.h"
#include "Entities/Characters/Character.h"

Katana::Katana()
{
}

Katana::~Katana()
{
}

void Katana::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
    setTexture(resourceManager.GetTilesetTexture());
    setTextureRect({ 293, 82, 6, 29 });
    setOrigin(3.f, 36.f);

    m_Bounds.size = { 72.f, 72.f };
    m_HitPoints.resize(3);

    SetPosition(position);

    m_Damage = CONFIG::WEAPONS_PARAM[GetId()];
}

void Katana::Update(UpdateArgs args, float dt)
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
                        en->TakeDamage(m_Damage);
            }
        }
    }
}

void Katana::Render(sf::RenderTarget& target)
{
    target.draw(*this);
}

void Katana::SetPosition(const sf::Vector2f& position)
{
    setPosition(position);
    sf::Vector2f dir = { cosf(m_Angle * M_PI / 180.f), sinf(m_Angle * M_PI / 180.f) };
    m_Center = position + 24.f * dir;
    m_HitPoints[0] = m_Center - 7.f * dir;
    m_HitPoints[1] = m_Center;
    m_HitPoints[2] = m_Center + 9.f * dir;
    m_Bounds.position = position - sf::Vector2f(36.f, 36.f);
}

EntityID Katana::GetId() const
{
    return EntityID::Katana;
}

void Katana::Attack(float dt)
{
    if (sf::Joystick::isButtonPressed(0, 5) && !m_IsAttacking)
    {
        m_IsAttacking = true;
        m_AttackAngle = m_Angle;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking)
    {
        m_IsAttacking = true;
        m_AttackAngle = m_Angle;
    }
    if (m_IsAttacking)
    {
        m_ElapsedTime += dt;
        if (m_ElapsedTime <= 0.25f)
        {
            if (!m_PlaySound)
                MUSIC::ATTACK_SOUND->play();
            m_PlaySound = true;
            m_CanHit = true;
            m_Angle = 360.f * sinf(2 * M_PI * m_ElapsedTime) + m_AttackAngle;
            setRotation(m_Angle + 90.f);
        }
        else if (m_ElapsedTime > 0.35f && m_ElapsedTime <= 0.5f)
        {
            if (m_PlaySound)
                MUSIC::ATTACK_SOUND->play();
            m_PlaySound = false;
            float mag = 15.f * sinf((20.f / 3.f) * M_PI * (m_ElapsedTime - 0.35f));
            sf::Vector2f dir = { cosf(m_Angle * M_PI / 180.f), sinf(m_Angle * M_PI / 180.f) };
            SetPosition(getPosition() + mag * dir);
        }
        else if (m_ElapsedTime > 0.5f)
        {
            m_CanHit = false;
            m_ElapsedTime = 0.f;
            m_IsAttacking = false;
        }
    }
}
