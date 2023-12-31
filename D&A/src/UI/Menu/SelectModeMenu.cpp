#include "pch.h"
#include "SelectModeMenu.h"

SelectModeMenu::SelectModeMenu()
{
}

SelectModeMenu::~SelectModeMenu()
{
}

void SelectModeMenu::Init(const ResourceManager& resourceManager)
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
	m_Frame.setTextureRect({ 946, 318, 78, 76 });
	m_Frame.setPosition(89.f, 37.f);
	m_BackButton.Init(resourceManager, { 776, 357, 16, 16 }, { 16.f, 16.f });
	m_StoryButton.Init(resourceManager, { 776, 195, 45, 22 }, { 105.5f, 48.f });
	m_ArenaButton.Init(resourceManager, { 776, 171, 45, 22 }, { 105.5f, 80.f });
	m_Save0.Init(resourceManager, { 128.f, 16.f }, 0);
	m_Save1.Init(resourceManager, { 128.f, 56.f }, 1);
	m_Save2.Init(resourceManager, { 128.f, 96.f }, 2);
	m_FadeColor = m_Save1.getColor();

	m_DeleteForm.Init(resourceManager, { 89.f,  34.f });
}

void SelectModeMenu::Update(StateID& currentState, float dt)
{
	if (m_BackButton.isClicked())
		currentState = StateID::StartMenuState;
	else if (m_ArenaButton.isClicked())
	{
		currentState = StateID::ArenaState;
	}
	if (m_StoryButton.isClicked() && !m_Animation)
	{
		m_Animation = true;
		m_FadeColor.a = 0;
	}
	if (m_Save0.isClicked())
	{
		currentState = StateID::GameState;
		SAVE::SAVE_MANAGER.LoadSave(0);
	}
	else if (m_Save1.isClicked())
	{
		currentState = StateID::GameState;
		SAVE::SAVE_MANAGER.LoadSave(1);
	}
	else if (m_Save2.isClicked())
	{
		currentState = StateID::GameState;
		SAVE::SAVE_MANAGER.LoadSave(2);
	}

	if (m_Save0.SubmitDelete())
	{
		m_RenderDeleteForm = true;
		if (m_DeleteForm.IsYesClicked())
			m_Save0.PerformDelete(true);
		else if (m_DeleteForm.IsNoClicked())
			m_Save0.PerformDelete(false);
	}
	else if (m_Save1.SubmitDelete())
	{
		m_RenderDeleteForm = true;
		if (m_DeleteForm.IsYesClicked())
			m_Save1.PerformDelete(true);
		else if (m_DeleteForm.IsNoClicked())
			m_Save1.PerformDelete(false);
	}
	else if (m_Save2.SubmitDelete())
	{
		m_RenderDeleteForm = true;
		if (m_DeleteForm.IsYesClicked())
			m_Save2.PerformDelete(true);
		else if (m_DeleteForm.IsNoClicked())
			m_Save2.PerformDelete(false);
	}

	MoveButton(currentState, dt);
}

void SelectModeMenu::Render(sf::RenderTarget& target)
{
	target.setView(m_StaticCamera);

	m_Batch.Begin(96);
	for (const auto& s : m_Border)
		m_Batch.Submit(s);
	m_Batch.Render(target);

	if (!m_RenderDeleteForm)
	{
		target.draw(m_Frame);
		m_BackButton.Render(target);
		m_StoryButton.Render(target);
		m_ArenaButton.Render(target);

		if (m_SelectSave)
		{
			m_Save0.Render(target);
			m_Save1.Render(target);
			m_Save2.Render(target);

			sf::View view({ 0.f, 0.f, (float)GLOBAL::WIN_WIDTH, (float)GLOBAL::WIN_HEIGHT });
			target.setView(view);
			target.draw(m_Save0.GetText());
			target.draw(m_Save1.GetText());
			target.draw(m_Save2.GetText());


			target.setView(m_StaticCamera);
		}
	}
	else
	{
		m_DeleteForm.Render(target);
	}

	m_RenderDeleteForm = false;
}

void SelectModeMenu::MoveButton(StateID& currentState, float dt)
{
	if (m_Animation)
	{
		if (m_StoryButton.GetPosition().x > 48.f || m_FadeColor.a < 255)
		{
			float x = Lerp(m_StoryButton.GetPosition().x, 48.f, 1 - powf(0.025, dt));
			float sy = m_StoryButton.GetPosition().y;
			float ay = m_ArenaButton.GetPosition().y;
			float fy = m_Frame.getPosition().y;
			m_StoryButton.SetPosition(x, sy);
			m_ArenaButton.SetPosition(x, ay);
			m_Frame.setPosition(x - 16.5f, fy);
			if (x < 64.f)
			{
				m_SelectSave = true;
				m_FadeColor.a = (((x - 48.f) / 16.f) * -255.f) + 255.f;
				if (m_FadeColor.a > 253)
					m_FadeColor.a = 255;
				const auto& color = m_Frame.getColor();
				m_Frame.setColor(sf::Color(color.r, color.g, color.b, 255 - m_FadeColor.a));
				m_Save0.setColor(m_FadeColor);
				m_Save1.setColor(m_FadeColor);
				m_Save2.setColor(m_FadeColor);
			}
			if (m_StoryButton.GetPosition().x < 48.05f)
			{
				m_StoryButton.SetPosition(48.f, sy);
				m_ArenaButton.SetPosition(48.f, ay);
			}
		}
	}
}

float SelectModeMenu::Lerp(float a, float b, float f)
{
	return a + f * (b - a);
}
