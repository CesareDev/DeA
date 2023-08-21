#include "pch.h"
#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::Init(const ResourceManager& resourceManager, const Player& player)
{
	m_Player = const_cast<Player*>(&player);

	m_Inv.setTexture(resourceManager.GetTilesetTexture());
	m_Inv.setTextureRect({ 360, 166, 51, 29 });

	float x = 8.f;
	float y = ((GLOBAL::WIN_HEIGHT / 5.f) - m_Inv.getGlobalBounds().getSize().y - 8.f);
	m_Inv.setPosition(x, y);

	m_IconPos[0] = { x + 4.f, y + 4.f };
	m_IconPos[1] = { x + 15.f, y + 4.f };
	m_IconPos[2] = { x + 26.f, y + 4.f };
	m_IconPos[3] = { x + 37.f, y + 4.f };
	m_IconPos[4] = { x + 4.f, y + 15.f };
	m_IconPos[5] = { x + 15.f, y + 15.f };
	m_IconPos[6] = { x + 26.f, y + 15.f };
	m_IconPos[7] = { x + 37.f, y + 15.f };

	m_Icons.resize(32);
	for (int i = 0; i < 32; i += 4)
	{
		sf::Vector2f pos = m_IconPos[i / 4] + sf::Vector2f(1.f, 1.f);
		m_Icons[i].position = pos;
		m_Icons[i + 1].position = pos + sf::Vector2f(8.f, 0.f);
		m_Icons[i + 2].position = pos + sf::Vector2f(8.f, 8.f);
		m_Icons[i + 3].position = pos + sf::Vector2f(0.f, 8.f);
	}

	m_States.texture = &resourceManager.GetTilesetTexture();

	m_CurrentIndex = m_Player->GetCurrentWeaponIndex();
	m_CurrentIconFrame.setPosition(m_IconPos[m_CurrentIndex]);
	m_CurrentIconFrame.setSize({ 10.f, 10.f });
	m_CurrentIconFrame.setFillColor(sf::Color(238, 142, 46, 80));
}

void Inventory::Update(float dt)
{
	if (!m_Player->IsAttacking())
	{
		if (GLOBAL::MOUSEWHELL_OFFSET > 7)
			GLOBAL::MOUSEWHELL_OFFSET = 0;
		if (GLOBAL::MOUSEWHELL_OFFSET < 0)
			GLOBAL::MOUSEWHELL_OFFSET = 7;
		m_CurrentIndex = GLOBAL::MOUSEWHELL_OFFSET;
		m_Player->SetCurrentWeaponIndex(m_CurrentIndex);
		m_CurrentIconFrame.setPosition(m_IconPos[m_CurrentIndex]);
	}
	for (int i = 0; i < 32; i += 4)
	{
		float size = 8.f;
		sf::Vector2f txCoord;
		switch (m_Player->GetWeaponID(i / 4))
		{
		case EntityID::Knife:
		{
			txCoord = { 360.f, 197.f };
			break;
		}
		case EntityID::RustySword:
		{
			txCoord = { 368.f, 197.f };
			break;
		}
		case EntityID::Sword:
		{
			txCoord = { 376.f, 197.f };
			break;
		}
		case EntityID::MagicSword:
		{
			txCoord = { 384.f, 197.f };
			break;
		}
		case EntityID::GreatHammer:
		{
			txCoord = { 360.f, 205.f };
			break;
		}
		case EntityID::Hammer:
		{
			txCoord = { 368.f, 205.f };
			break;
		}
		case EntityID::Mace:
		{
			txCoord = { 376.f, 205.f };
			break;
		}
		case EntityID::GreatMace:
		{
			txCoord = { 384.f, 205.f };
			break;
		}
		case EntityID::Katana:
		{
			txCoord = { 360.f, 213.f };
			break;
		}
		case EntityID::GreatSword:
		{
			txCoord = { 368.f, 213.f };
			break;
		}
		case EntityID::ColossalSword:
		{
			txCoord = { 376.f, 213.f };
			break;
		}
		case EntityID::GreatAxe:
		{
			txCoord = { 360.f, 237.f };
			break;
		}
		case EntityID::Spear:
		{
			txCoord = { 368.f, 237.f };
			break;
		}
		case EntityID::Bow:
		{
			txCoord = { 360.f, 245.f };
			break;
		}
		case EntityID::HealthPotion:
		{
			txCoord = { 360.f, 261.f };
			break;
		}
		case EntityID::BigHealthPotion:
		{
			txCoord = { 360.f, 253.f };
			break;
		}
		case EntityID::DamagePotion:
		{
			txCoord = { 384.f, 261.f };
			break;
		}
		case EntityID::BigDamagePotion:
		{
			txCoord = { 384.f, 253.f };
			break;
		}
		default:
			break;
		}
		m_Icons[i].texCoords = txCoord;
		m_Icons[i + 1].texCoords = { txCoord.x + size, txCoord.y };
		m_Icons[i + 2].texCoords = { txCoord.x + size, txCoord.y + size };
		m_Icons[i + 3].texCoords = { txCoord.x, txCoord.y + size };
	}
}

void Inventory::Render(sf::RenderTarget& target)
{
	target.draw(m_Inv);
	target.draw(m_Icons.data(), m_Icons.size(), sf::Quads, m_States);
	target.draw(m_CurrentIconFrame);
}