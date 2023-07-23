#include "pch.h"
#include "Camera.h"
#include <iostream>

Camera::Camera()
{
}

Camera::~Camera()
{
}

bool Camera::Init(const sf::Vector2f& startPosition, const sf::FloatRect& limits, const sf::FloatRect& viewArea)
{
	reset(viewArea);

	m_Left = limits.left + getSize().x / 2.f;
	m_Top = limits.top + getSize().y / 2.f;
	m_Bottom = limits.height - getSize().y / 2.f;
	m_Right = limits.width - getSize().x / 2.f;

	if (startPosition.x < m_Left)
	{
		if (startPosition.y < m_Top)
		{
			setCenter(m_Left, m_Top);
		}
		else if (startPosition.y > m_Bottom)
		{
			setCenter(m_Left, m_Bottom);
		}
		else 
		{
			setCenter(m_Left, startPosition.y);
		}
	}
	else if (startPosition.x > m_Right)
	{
		if (startPosition.y < m_Top)
		{
			setCenter(m_Right, m_Top);
		}
		else if (startPosition.y > m_Bottom)
		{
			setCenter(m_Right, m_Bottom);
		}
		else 
		{
			setCenter(m_Right, startPosition.y);
		}
	}
	else if (startPosition.y < m_Top)
	{
		setCenter(startPosition.x, m_Top);
	}
	else if (startPosition.y > m_Bottom)
	{
		setCenter(startPosition.x, m_Bottom);
	}
	else 
	{
		setCenter(startPosition);
	}
	return true;
}

void Camera::Update(const sf::Vector2f& position, float dt)
{
	if (position.x < m_Left)
	{
		if (position.y < m_Top)
		{
			setCenter(m_Left, m_Top);
		}
		else if (position.y > m_Bottom)
		{
			setCenter(m_Left, m_Bottom);
		}
		else 
		{
			setCenter(m_Left, position.y);
		}
	}
	else if (position.x > m_Right)
	{
		if (position.y < m_Top)
		{
			setCenter(m_Right, m_Top);
		}
		else if (position.y > m_Bottom)
		{
			setCenter(m_Right, m_Bottom);
		}
		else 
		{
			setCenter(m_Right, position.y);
		}
	}
	else if (position.y < m_Top)
	{
		setCenter(position.x, m_Top);
	}
	else if (position.y > m_Bottom)
	{
		setCenter(position.x, m_Bottom);
	}
	else 
	{
		setCenter(position);
	}
}

const sf::FloatRect& Camera::GetVisibleArea() const
{
	return sf::FloatRect(getCenter() - getSize() / 2.f, getSize());
}