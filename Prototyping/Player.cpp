#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "utils.h"
#include "Platform.h"
Player::Player(float posX, float posY)
{	
	m_instances++;
	if (m_pWalkSprt == nullptr)
	{
		m_pWalkSprt = { new Texture{"1Rengoku.png"}};
		m_Bounds = Rectf{ posX + m_pWalkSprt->GetWidth() / 10.f, posY, m_pWalkSprt->GetWidth() / 25.f, m_pWalkSprt->GetHeight() / 25.f};

	}
}
Player::~Player()
{
	m_instances--;
	if (m_pWalkSprt != nullptr
		&& m_instances == 0)
	{
		delete m_pWalkSprt;
		m_pWalkSprt = nullptr;
	}
}

void Player::Draw() const
{
	m_pWalkSprt->Draw(m_Bounds, GetCurrentFrameRect());
}

void Player::HandleFalling(float elapsedSec, std::vector<Platform*> platformVector)
{
	if (platformVector.size() != 0)
	{

		for (Platform* platform : platformVector)
		{
			std::vector<Vector2f> pointVector{};
			pointVector.push_back(platform->GetLeftPoint());
			pointVector.push_back(platform->GetRightPoint());

			const float rightOffset{ m_Bounds.width / 129.f * 20.f };
			const float leftOffset{ m_Bounds.width / 129.f * 40.f };
			utils::HitInfo hitInfo{};

			if (utils::Raycast(pointVector, Vector2f{ m_Bounds.left + leftOffset,m_Bounds.bottom + m_Bounds.height * 0.2f }, Vector2f{ m_Bounds.left + leftOffset ,m_Bounds.bottom }, hitInfo)
				|| (utils::Raycast(pointVector, Vector2f{ m_Bounds.left + m_Bounds.width - leftOffset,m_Bounds.bottom + m_Bounds.height * 0.2f}, Vector2f{ m_Bounds.left + m_Bounds.width - leftOffset ,m_Bounds.bottom }, hitInfo)))
			{
				m_Velocity.y = 0.f;
				m_Bounds.bottom = hitInfo.intersectPoint.y;
			}
			else {
				float gravity{ 9.81f };
				float speed{ 20.f };
				m_Velocity.y += gravity * elapsedSec * speed;
				m_Bounds.bottom -= m_Velocity.y * elapsedSec;
			}
		}
	}
	else {
		float gravity{ 9.81f };
		float speed{ 20.f };
		m_Velocity.y += gravity * elapsedSec * speed;
		m_Bounds.bottom -= m_Velocity.y * elapsedSec;
	}
	HandleDying();
}

void Player::HandleMovement(float elapsedSec, const Uint8* pStates)
{
	if (pStates[SDL_SCANCODE_LEFT])
	{
		m_WalkingState = WalkingState::left;
		int x = static_cast<int>(m_WalkingState);
		m_Bounds.left -= elapsedSec * m_Velocity.x;
	}

	//else if (pStates[SDL_SCANCODE_UP])
	//{
	//	m_WalkingState = WalkingState::up;
	//	int x = static_cast<int>(m_WalkingState);
	//	m_Position.y += elapsedSec * velocity;
	//}
	else if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_WalkingState = WalkingState::right;
		int x = static_cast<int>(m_WalkingState);

		m_Bounds.left += elapsedSec * m_Velocity.x;
	}
	//else if (pStates[SDL_SCANCODE_DOWN])
	//{
	//	m_WalkingState = WalkingState::down;
	//	int x = static_cast<int>(m_WalkingState);
	//	m_Position.y -= elapsedSec * velocity;
	//
	//}
	else {
		m_WalkingState = WalkingState::none;
		//m_FrameNr = 1;
	}

	const float maxTimePerFrame{ 0.18f };
	m_AccumulatedTime += elapsedSec;

	if (m_AccumulatedTime >= maxTimePerFrame)
	{
		if (m_WalkingState != WalkingState::none)
		{
			if (m_FrameNr >= m_SpriteCols) m_FrameNr = 0;
				else m_FrameNr++;
		}
		else 
		{
			m_FrameNr++;
			if (m_FrameNr >= 4) m_FrameNr = 0;
		}
	m_AccumulatedTime -= maxTimePerFrame;
	}

}

Rectf Player::GetCurrentFrameRect() const
{
	float width{ (m_pWalkSprt->GetWidth() / m_SpriteCols)  };
	float height{ (m_pWalkSprt->GetHeight() / m_SpriteRows)  };
	return Rectf{
		(width )* m_FrameNr ,
		(height )* static_cast<int>(m_WalkingState),
		width,
		height
	};
}

void Player::HandleDying()
{
	if (m_Bounds.bottom <= 0.f)
	{
		ResetPos();
	}
}

void Player::ResetPos()
{
	SetPosition(100.f, 300.f);
}

void Player::SetPosition(Vector2f newPos)
{
	m_Bounds.left = newPos.x;
	m_Bounds.bottom = newPos.y;
}

void Player::SetPosition(float left, float bottom)
{
	SetPosition(Vector2f(left, bottom));
}