#include "PlayerShip.h"
#include "../ASCII_GAME/Core/Maths/Vector2.h"
#include "../ASCII_GAME/Core/Renderer/ConsoleColours.h"
#include <Windows.h>

const int MOVEMENT_SPEED = 4;

CHAR_INFO ShipSprite[] =
{
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
	{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
	{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
};

PlayerShip::PlayerShip()
	:m_UpKey(0)
	, m_DownKey(0)
	, m_LeftKey(0)
	, m_RightKey(0)
	, m_bInitialised(false)
{
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::Initialise(Vector2& position, int upKey, int downKey, int leftKey, int rightKey)
{
	m_UpKey = upKey;
	m_DownKey = downKey;
	m_LeftKey = leftKey;
	m_RightKey = rightKey;

	Sprite::Initialise(ShipSprite, Vector2(12, 8));

	Vector2 startPosition(position.x - (Sprite::GetSize().x + 220), position.y - (Sprite::GetSize().y / 2));
	SetPosition(startPosition);

	m_bInitialised = true;
}

void PlayerShip::Update()
{
	if (!m_bInitialised)
		return;

	if (UpKeyPressed())
	{
		MoveUp();
	}

	if (LeftKeyPressed())
	{
		MoveLeft();
	}

	if (RightKeyPressed())
	{
		MoveRight();
	}

	if (DownKeyPressed())
	{
		MoveDown();
	}
}

void PlayerShip::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised)
		return;

	Sprite::Render(pRenderer);
}

void PlayerShip::MoveUp()
{
	SetPosition(Vector2(GetPosition().x, GetPosition().y - MOVEMENT_SPEED));

	

	if (GetPosition().y + GetSize().y <= 0)
	{
		MoveDown();
	}

	if (GetPosition().x < 0)
	{
		MoveRight();
	}

	if (GetPosition().x + GetSize().x > SCREEN_WIDTH)
	{
		MoveLeft();
	}
}

void PlayerShip::MoveDown()
{
	SetPosition(Vector2(GetPosition().x, GetPosition().y + MOVEMENT_SPEED));

	if (GetPosition().y + GetSize().y >= SCREEN_HEIGHT)
	{
		MoveUp();
	}

	if (GetPosition().x < 0)
	{
		MoveRight();
	}

	if (GetPosition().x + GetSize().x > SCREEN_WIDTH)
	{
		MoveLeft();
	}
}

bool PlayerShip::UpKeyPressed()
{
	return (GetKeyState(m_UpKey) < 0);
}

bool PlayerShip::DownKeyPressed()
{
	return (GetKeyState(m_DownKey) < 0);
}

void PlayerShip::MoveLeft()
{
	SetPosition(Vector2(GetPosition().x - MOVEMENT_SPEED, GetPosition().y));

	if (GetPosition().x < 0)
	{
		MoveRight();
	}
}

void PlayerShip::MoveRight()
{
	SetPosition(Vector2(GetPosition().x + MOVEMENT_SPEED, GetPosition().y));

	if (GetPosition().x + GetSize().x > SCREEN_WIDTH)
	{
		MoveLeft();
	}
}

bool PlayerShip::LeftKeyPressed()
{
	return (GetKeyState(m_LeftKey) < 0);
}

bool PlayerShip::RightKeyPressed()
{
	return (GetKeyState(m_RightKey) < 0);
}

