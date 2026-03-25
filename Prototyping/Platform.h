#pragma once

#include <vector>
class Platform
{
public:
	Platform(Vector2f leftPoint, Vector2f rightPos);
	~Platform();
	void Draw() const;

	void Update(float elapsedSec);

	Vector2f GetLeftPoint() const;
	Vector2f GetRightPoint() const;
protected:

private:
	int ChangeNewPlatform(int nrOfPlatforms);
	void ChangePlatformDiffs();
	int m_GoToPlatformIdx{};
	int m_CurrPlatform{};
	float m_Speed{ 3.f };
	Vector2f m_LeftPoint{};
	Vector2f m_RightPoint{};
	std::vector<Vector2f>m_GoToPlatform{ Vector2f{50.f,100.f},Vector2f{150.f,100.f} };
	float m_Timer{};
	const std::vector<Vector2f>m_AllPlatforms{
		Vector2f{50.f,100.f}
		,Vector2f{150.f,100.f}
		,Vector2f{350.f,100.f}
		,Vector2f{450.f,100.f}
		,Vector2f{650.f,100.f}
		,Vector2f{750.f,100.f}

		,Vector2f{50.f,250.f}
		,Vector2f{150.f,250.f}
		,Vector2f{350.f,250.f}
		,Vector2f{450.f,250.f}
		,Vector2f{650.f,250.f}
		,Vector2f{750.f,250.f}

		,Vector2f{50.f,400.f}
		,Vector2f{150.f,400.f}
		,Vector2f{350.f,400.f}
		,Vector2f{450.f,400.f}
		,Vector2f{650.f,400.f}
		,Vector2f{750.f,400.f}
	};

	float m_DiffLeftX{};
	float m_DiffLeftY{};
	float m_DiffRightX{};
	float m_DiffRightY{};
};

