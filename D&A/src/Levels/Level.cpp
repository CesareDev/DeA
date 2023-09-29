#include "pch.h"
#include "Level.h"
#include "Entities/EntityInclude.h"

Level::Level()
{
}

Level::~Level()
{
}

bool Level::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt, 0.5f);
}

bool Level::OnExit(float dt)
{
	return m_Transition.FadeOut(dt, 0.5f);
}

void Level::Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt)
{
	for (auto it = m_Tree->begin(); it != m_Tree->end();)
	{
		it->obj->Update({ *m_Tree, m_Map, m_AStar, currentState, currentLevel, entranceIndex }, dt);
		switch (it->obj->GetType())
		{
		case EntityType::Character:
		{
			if (((Character*)it->obj)->IsDead())
			{
				it = m_Tree->remove(it);
				continue;
			}
			else
			{
				if (((Character*)it->obj)->IsMoving())
					m_Tree->relocate(it, it->obj->GetBounds());
			}
			break;
		}
		default:
			break;
		}
		++it;
	}

	m_Camera.Update(m_Player->GetCenter(), dt);
	m_Map.update(dt);
	m_Hud.Update(dt);
	m_Label.Update(dt);
}

void Level::Render(sf::RenderTarget& target)
{
	target.setView(m_Camera);

	m_Map.drawLayer(target, 0);
	m_Map.drawLayer(target, 1);

	const auto& list = m_Tree->search(m_Camera.GetVisibleArea());

	for (const auto& en : list)
		en->obj->Render(target);

	m_Map.drawLayer(target, 2);

	for (const auto& en : list)
		if (en->obj->GetType() == EntityType::Character)
			((Character*)en->obj)->RenderWeapon(target);

	m_Hud.Render(target);
	m_Label.Render(target);
	m_Transition.Render(target);
}

void Level::InitEnemies(const ResourceManager& resourceManager)
{
	const auto& entitiesInfo = CONFIG::LEVELS_ENTITIES_INFO[(int)GetId()];
	m_Enemies.resize(entitiesInfo.size());

	for (int i = 0; i < entitiesInfo.size(); ++i)
	{
		switch (entitiesInfo[i].id)
		{
		case EntityID::SmallDemon:
			m_Enemies[i].reset(new SmallDemon());
			break;
		case EntityID::HalfDemon:
			m_Enemies[i].reset(new HalfDemon());
			break;
		case EntityID::Demon:
			m_Enemies[i].reset(new Demon());
			break;
		case EntityID::MagicDemon:
			m_Enemies[i].reset(new MagicDemon());
			break;
		case EntityID::DemonBoss:
			if (!SAVE::DEMON_BOSS_DEFEATED)
				m_Enemies[i].reset(new DemonBoss());
			break;
		case EntityID::SmallOrc:
			m_Enemies[i].reset(new SmallOrc());
			break;
		case EntityID::Orc:
			m_Enemies[i].reset(new Orc());
			break;
		case EntityID::MaskedOrc:
			m_Enemies[i].reset(new MaskedOrc());
			break;
		case EntityID::TribalOrc:
			m_Enemies[i].reset(new TribalOrc());
			break;
		case EntityID::OrcBoss:
			if (!SAVE::ORC_BOSS_DEFEATED)
				m_Enemies[i].reset(new OrcBoss());
			break;
		case EntityID::SmallUndead:
			m_Enemies[i].reset(new SmallUndead());
			break;
		case EntityID::HalfUndead:
			m_Enemies[i].reset(new HalfUndead());
			break;
		case EntityID::Undead:
			m_Enemies[i].reset(new Undead());
			break;
		case EntityID::UndeadSlime:
			m_Enemies[i].reset(new UndeadSlime());
			break;
		case EntityID::UndeadBoss:
			if (!SAVE::UNDEAD_BOSS_DEFEATED)
				m_Enemies[i].reset(new UndeadBoss());
			break;
		default:
			break;
		}
		if (m_Enemies[i])
		{
			m_Enemies[i]->Init(resourceManager, entitiesInfo[i].position);
			m_Tree->insert(m_Enemies[i].get(), m_Enemies[i]->GetBounds());
		}
	}
}

void Level::DeleteCoins()
{
	for (auto it = m_Tree->begin(); it != m_Tree->end(); ++it)
		if (it->obj->GetId() == EntityID::Coin)
			delete it->obj;
}
