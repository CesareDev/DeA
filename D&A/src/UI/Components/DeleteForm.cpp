#include "pch.h"
#include "DeleteForm.h"

DeleteForm::DeleteForm()
{
}

DeleteForm::~DeleteForm()
{
}

void DeleteForm::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({528, 528, 78, 76});
	setPosition(position);

	float yx = position.x + 16.f;
	float nx = position.x + 46.f;
	float y = position.y + 48.f;
	m_Yes.Init(resourceManager, { 776, 426, 16, 16 }, { yx, y });
	m_No.Init(resourceManager, { 794, 426, 16, 16 }, { nx, y });
}

void DeleteForm::Render(sf::RenderTarget& target)
{
	target.draw(*this);
	m_Yes.Render(target);
	m_No.Render(target);
}

bool DeleteForm::IsYesClicked()
{
	return m_Yes.isClicked();
}

bool DeleteForm::IsNoClicked()
{
	return m_No.isClicked();
}
