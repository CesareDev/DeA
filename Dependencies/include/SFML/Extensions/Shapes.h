#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>

namespace sf
{
	float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	class Circle : public sf::Sprite
	{
	public:
		Circle();
		Circle(const sf::Texture& texture);
		Circle(const sf::Vector2f& position, float radius);
		Circle(const sf::Vector2f& position, float radius, const sf::Texture& texture);
		virtual ~Circle();

		void collide(Circle& other);
		bool contains(const sf::Vector2f& point) const;

		void moveCircle(const sf::Vector2f& offset);
		void moveCircle(float x, float y);

		void setCenter(const sf::Vector2f& pos);
		void setRadius(float radius);
		const sf::Vector2f& getCenter() const;
		float getRadius() const;

	private:
		sf::Vector2f m_Center;
		float m_Radius;
	};
}

