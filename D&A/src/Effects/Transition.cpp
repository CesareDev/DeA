#include "pch.h"
#include "Transition.h"

Transition::Transition()
{
}

Transition::~Transition()
{
}

void Transition::Init(const ResourceManager& resourceManager)
{
	m_Alpha = 255.f;

	m_FadeRect.setPosition(0.f, 0.f);
	m_FadeRect.setSize(sf::Vector2f(GLOBAL::WIN_WIDTH, GLOBAL::WIN_HEIGHT));
	m_FadeRect.setFillColor(sf::Color(0, 0, 0, m_Alpha));
}

bool Transition::FadeIn(float dt, float animatinTimeInSeconds)
{
	if (animatinTimeInSeconds == 0.f)
	{
		m_EnterOrExit = false;
		return false;
	}
	m_EnterOrExit = true;
	if (m_Alpha > 0.f)
	{
		m_Alpha -= 255 * (dt / animatinTimeInSeconds);
		if (m_Alpha < 0.f)
			m_Alpha = 0.f; 
		m_FadeRect.setFillColor(sf::Color(0, 0, 0, m_Alpha));
		return true;
	}
	m_EnterOrExit = false;
	return false;
}

bool Transition::FadeOut(float dt, float animatinTimeInSeconds)
{
	if (animatinTimeInSeconds == 0.f)
	{
		m_EnterOrExit = false;
		return false;
	}
	m_EnterOrExit = true;
	if (m_Alpha < 255.f)
	{
		m_Alpha += 255 * (dt / animatinTimeInSeconds);
		if (m_Alpha > 255.f)
			m_Alpha = 255.f;
		m_FadeRect.setFillColor(sf::Color(0, 0, 0, m_Alpha));
		return true;
	}
	m_EnterOrExit = false;
	return false;
}

void Transition::Render(sf::RenderTarget& target)
{
	if (m_EnterOrExit)
	{
		const auto& view = target.getView();
		m_FadeRect.setSize(view.getSize());
		m_FadeRect.setPosition(view.getCenter() - (view.getSize() / 2.f));
		target.draw(m_FadeRect);
	}
}
