#include "pch.h"
#include "StartMenu.h"

#include <iostream>

StartMenu::StartMenu()
{
}

StartMenu::~StartMenu()
{
}

void StartMenu::Init(const ResourceManager& resourceManager)
{
	m_StaticCamera.Init({ 0.f, 0.f }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Border.resize(96);
	m_Batch.Create(&resourceManager.GetTilesetTexture());

	for (int i = 0; i < m_Border.size(); ++i)
	{
		m_Border[i].setTexture(resourceManager.GetTilesetTexture());

		if (i == 0)
		{
			m_Border[i].setPosition(i, i);
			m_Border[i].setTextureRect({ 528, 40, 8, 8 });
		}
		else if (i < 31 && i > 0)
		{
			m_Border[i].setPosition(i * 8.f, 0.f);
			m_Border[i].setTextureRect({ 552, 40, 8, 8 });
		}
		else if (i == 31)
		{
			m_Border[i].setPosition(i * 8, 0.f);
			m_Border[i].setTextureRect({ 560, 40, 8, 8 });
		}
		else if (i < 48 && i > 31)
		{
			m_Border[i].setPosition(31 * 8, (i - 31) * 8);
			m_Border[i].setTextureRect({ 560, 48, 8, 8 });
		}
		else if (i == 48)
		{
			m_Border[i].setPosition(31 * 8, (i - 31) * 8);
			m_Border[i].setTextureRect({ 560, 56, 8, 8 });
		}
		else if (i < 79 && i > 48)
		{
			m_Border[i].setPosition((79 - i) * 8, 17 * 8);
			m_Border[i].setTextureRect({ 552, 56, 8, 8 });
		}
		else if (i == 79)
		{ 
			m_Border[i].setPosition((79 - i) * 8, 17 * 8);
			m_Border[i].setTextureRect({ 528, 56, 8, 8 });
		}
		else if (i > 79)
		{
			m_Border[i].setPosition(0.f, (96 - i) * 8);
			m_Border[i].setTextureRect({ 528, 48, 8, 8 });
		}
	}

	m_Frame.setTexture(resourceManager.GetTilesetTexture());
	m_Frame.setTextureRect({ 946, 220, 78, 98 });
	m_Frame.setPosition(89.f, 17.f);

	m_PlayButton.Init(resourceManager, {776, 219, 45, 22}, {105.5f, 28.f});
	m_OptionsButton.Init(resourceManager, { 774, 243, 50, 22 }, { 103, 56 });
	m_ExitButton.Init(resourceManager, { 776, 267, 45, 22 }, { 105.5f, 84 });
}

void StartMenu::Update(StateID& currentState, float dt)
{
	if (m_PlayButton.isClicked())
		currentState = StateID::SelectModeState;
	else if (m_OptionsButton.isClicked())
		currentState = StateID::OptionsMenuState;
	else if (m_ExitButton.isClicked())
	{
		SAVE::SAVE_MANAGER.SaveOptions();
		currentState = StateID::ExitState;
	}
}

void StartMenu::Render(sf::RenderTarget& target)
{
	target.setView(m_StaticCamera);

	m_Batch.Begin(96);
	for (const auto& s : m_Border)
		m_Batch.Submit(s);
	m_Batch.Render(target);

	target.draw(m_Frame);
	m_PlayButton.Render(target);
	m_OptionsButton.Render(target);
	m_ExitButton.Render(target);

	target.setView(target.getDefaultView());
}
