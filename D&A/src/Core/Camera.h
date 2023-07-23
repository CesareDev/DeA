#pragma once

class Camera : public sf::View
{
public:

	Camera();
	~Camera();

	bool Init(const sf::Vector2f& startPosition, const sf::FloatRect& limits, const sf::FloatRect& viewArea);
	void Update(const sf::Vector2f& position, float dt);
	const sf::FloatRect& GetVisibleArea() const;

private:

	float m_Left;
	float m_Right;
	float m_Top;
	float m_Bottom;
};

