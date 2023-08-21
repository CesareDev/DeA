#include "pch.h"
#include "Arrow.h"

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

void Arrow::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
    setTexture(resourceManager.GetTilesetTexture());
    setTextureRect({ 324, 219, 7, 21 });
    setOrigin(3.5f, 21.f);

    m_Bounds.size = { 21.f, 21.f };

    SetPosition(position);

    m_ElapsedAnimationTime = 0.f;
    m_Damage = 1;
}

void Arrow::Update(UpdateArgs args, float dt)
{
    if (m_Shooted && !m_Stopped)
    {
        SetPosition(getPosition() + m_Velocity * dt);
        if (args.tileMap.isCellWall(sf::Vector2i(m_HitPoint.x / 16.f, m_HitPoint.y / 16.f)))
            m_Stopped = true;
        else
        {
            for (const auto& en : args.qTree.search(m_Bounds))
            {
                if (en->obj->GetType() == EntityType::Character && en->obj->GetId() != EntityID::Player && en->obj->GetId() != EntityID::Arrow && en->obj != this)
                {
                    if (sf::distance(m_HitPoint, en->obj->GetCenter()) < en->obj->GetBounds().size.x / 2.f)
                    {
                        Character* c = (Character*)en->obj;
                        if (c->IsVulnerable())
                        {
                            c->TakeDamage(m_Damage);
                            m_EnemyPosition = &c->GetCenter();
                            m_HitPosition = getPosition() - c->GetCenter();
                            m_Stopped = true;
                        }
                    }
                }
            }
        }
    }
    else if (m_Stopped)
    {
        if (m_EnemyPosition != nullptr)
        {
            m_Alpha -= 255 * dt;
            if (m_Alpha > 0.f)
            {
                SetPosition(*m_EnemyPosition + m_HitPosition);
                const auto& color = getColor();
                setColor(sf::Color(color.r, color.g, color.b, m_Alpha));
            }
            else
                m_IsDead = true;
        }
        else
        {
            m_Alpha -= 255 * dt;
            if (m_Alpha > 0.f)
            {
                const auto& color = getColor();
                setColor(sf::Color(color.r, color.g, color.b, m_Alpha));
            }
            else
                m_IsDead = true;
        }
    }
}

void Arrow::Render(sf::RenderTarget& target)
{
    target.draw(*this);
}

void Arrow::SetPosition(const sf::Vector2f& position)
{
    setPosition(position);
    sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
    m_Center = position + 10.5f *  dir;
    m_HitPoint = position + 18.f * dir;
    m_Bounds.position = m_Center - sf::Vector2f(10.5f, 10.5f);
}

EntityID Arrow::GetId() const
{
    return EntityID::Arrow;
}

void Arrow::Spawn(float angle, const sf::Vector2f& position, float dt)
{
    m_Angle = angle;
    setRotation(m_Angle + 90.f);
    SetPosition(position);
    if (m_Damage < 10)
        m_ElapsedAnimationTime += dt;
    if (m_ElapsedAnimationTime > 0.5f && m_ElapsedAnimationTime <= 3.0f)
    {
        m_Damage = (9 * (m_ElapsedAnimationTime - 0.5f) / 2.5f) + 1;
        float value = 255.f * (m_ElapsedAnimationTime - 0.5f) / 2.5f;
        if (value < 255.f)
            setColor(sf::Color(255, 255 - value, 255 - value, 255));
        else
            setColor(sf::Color::White);
    }
    if (m_ElapsedAnimationTime > 4.f)
    {
        setColor(sf::Color::White);
        setTextureRect({ 335, 219, 7, 21 });
        m_Damage = 10;
    }
}

void Arrow::Shoot()
{
    m_Shooted = true;
    m_ElapsedAnimationTime = 0.f;
    m_Velocity = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
    if (m_Damage > 1)
        m_Velocity *= 128.f + (m_Damage / 10.f) * 128.f;
    else
        m_Velocity *= 128.f;
}