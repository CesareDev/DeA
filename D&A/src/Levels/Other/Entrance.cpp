#include "pch.h"
#include "Entrance.h"
#include "Entities/Environments/Coin.h"

Entrance::Entrance()
{
}

Entrance::~Entrance()
{
}

void Entrance::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Player = &player;
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Entrance");

	if (SAVE::DEMON_BOSS_DEFEATED && SAVE::ORC_BOSS_DEFEATED && SAVE::UNDEAD_BOSS_DEFEATED)
	{
		m_Player->SetPosition({ m_Player->getPosition().x, m_Player->getPosition().y + 160.f });
		m_Map.load("../res/map/entranceWin.tmx", &resourceManager.GetTilesetTexture());
		m_Princess.Init(resourceManager, { 232.f, 80.f });
		m_Princess.SetPlayer(player);
	}
	else
		m_Map.load("../res/map/entrance.tmx", &resourceManager.GetTilesetTexture());


	m_Tree = &tree; 
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });
	//this func-^
	//clear too

	if (entranceIndex == 0)
		m_Player->SetPosition({ 224.f, 432.f }); //starting point
	else if (entranceIndex == 1)
		m_Player->SetPosition({ 48.f, 240.f }); //orcs1
	else if (entranceIndex == 2)
		m_Player->SetPosition({ 176.f, 48.f }); //demons2
	else if (entranceIndex == 3)
		m_Player->SetPosition({ 288.f, 48.f }); //demons1
	else if (entranceIndex == 4)
		m_Player->SetPosition({ 416.f, 240.f }); //undeads1

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder1.Init(resourceManager, { 32.f, 240.f });
	m_Ladder1.SetTeleportLevel(LevelID::OrcsOne, 0);

	m_Ladder2.Init(resourceManager, { 160.f, 48.f });
	m_Ladder2.SetTeleportLevel(LevelID::DemonsTwo, 0);

	m_Ladder3.Init(resourceManager, { 304.f, 48.f });
	m_Ladder3.SetTeleportLevel(LevelID::DemonsOne, 0);

	m_Ladder4.Init(resourceManager, { 432.f, 240.f });
	m_Ladder4.SetTeleportLevel(LevelID::UndeadsOne, 0);

	m_StoryMessage.Init(resourceManager, { 224.f, 384.f });
	if (GLOBAL::JOYSTICK_AVAILABLE)
		m_StoryMessage.SetText("Orcs demons and undeads\nhave invaded the castle.\nDefeat them and save the princess\n-- Press Space to close -- / -- X --");
	else
		m_StoryMessage.SetText("Orcs demons and undeads\nhave invaded the castle.\nDefeat them and save the princess\n-- Press Space to close --");

	m_CommandMessage.Init(resourceManager, { 224.f, 304.f });
	if (GLOBAL::JOYSTICK_AVAILABLE)
		m_CommandMessage.SetText("Command / PS4 joystick:\nWASD to move / Left Analog\nLeft Mouse to attack / R1\nScrool to change weapon / L2 - R2\nE for the shop - Square");
	else
		m_CommandMessage.SetText("Command:\nWASD to move\nLeft Mouse to attack\nScrool to change weapon\nE for the shop");

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder1, m_Ladder1.GetBounds());
	m_Tree->insert(&m_Ladder2, m_Ladder2.GetBounds());
	m_Tree->insert(&m_Ladder3, m_Ladder3.GetBounds());
	m_Tree->insert(&m_Ladder4, m_Ladder4.GetBounds());

	m_Tree->insert(&m_StoryMessage, m_StoryMessage.GetBounds());
	m_Tree->insert(&m_CommandMessage, m_CommandMessage.GetBounds());

	if (SAVE::DEMON_BOSS_DEFEATED && SAVE::ORC_BOSS_DEFEATED && SAVE::UNDEAD_BOSS_DEFEATED)
		m_Tree->insert(&m_Princess, m_Princess.GetBounds());
}

LevelID Entrance::GetId() const
{
	return LevelID::Entrance;
}

void Entrance::Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt)
{
	Level::Update(currentState, currentLevel, entranceIndex, dt);

	//MESSAGE UPDATE(ONLY FOR THIS LEVEL)
	if (GLOBAL::JOYSTICK_AVAILABLE)
	{
		m_StoryMessage.SetText("Orcs demons and undeads\nhave invaded the castle.\nDefeat them and save the princess\n-- Press Space to close -- / -- X --");
		m_CommandMessage.SetText("Command / PS4 joystick:\nWASD to move / Left Analog\nLeft Mouse to attack / R1\nScrool to change weapon / L2 - R2\nE for the shop - Square");
	}
	else
	{
		m_StoryMessage.SetText("Orcs demons and undeads\nhave invaded the castle.\nDefeat them and save the princess\n-- Press Space to close --");
		m_CommandMessage.SetText("Command:\nWASD to move\nLeft Mouse to attack\nScrool to change weapon\nE for the shop");
	}
}

void Entrance::Render(sf::RenderTarget& target)
{
	Level::Render(target);


	//MESSAGE RENDER (ONLY FOR THIS LEVEL)
	m_StoryMessage.RenderText(target);
	m_CommandMessage.RenderText(target);
}