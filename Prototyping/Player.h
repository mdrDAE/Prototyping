#pragma once
#include <vector>
class Platform;

class Texture;
class Player
{
public:
	enum class WalkingState {
		//down = 0,
		right = 0,
		left = 1,
		none = 2
		//up = 3,

	};
	//azd af azef azezef
	Player(float posX, float posY);
	~Player();
	void Draw() const;

	void HandleFalling(float elapsedSec, std::vector<Platform*> platformVector);
	void HandleMovement(float elapsedSec, const Uint8* pStates = nullptr);
	void HandleDying();

	void SetPosition(Vector2f newPos);
	void SetPosition(float left, float bottom);

	void ResetPos();

private:
	Rectf GetCurrentFrameRect() const;
	WalkingState m_WalkingState{ WalkingState::none };
	Texture* m_pWalkSprt{};
	Rectf m_Bounds{};
	int m_FrameNr{};
	float m_AccumulatedTime{};
	int m_instances{};

	Vector2f m_Velocity{ 220.f,0 };
	const int m_SpriteRows{ 14 };
	const int m_SpriteCols{ 8 };
};

