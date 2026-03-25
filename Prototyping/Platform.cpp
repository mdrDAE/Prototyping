#include "pch.h"
#include "Platform.h"
#include "utils.h"

Platform::Platform(Vector2f leftPoint, Vector2f rightPos)
	:m_LeftPoint(leftPoint)
	,m_RightPoint(rightPos)
{
}
Platform::~Platform()
{
}

void Platform::Draw() const
{
	const float LineWidth{2.f};
	utils::DrawLine(m_LeftPoint, m_RightPoint, LineWidth);
}

void Platform::Update(float elapsedSec)
{
	const float maxTimer{ 3.f };
	const int nrOfPlatforms{9};
	m_Timer += elapsedSec;
	if (m_Timer >= maxTimer)
	{
		ChangeNewPlatform(nrOfPlatforms);

		if (m_GoToPlatform.size() != 0)
		{
			if ((m_LeftPoint.x != m_GoToPlatform[0].x) || (m_LeftPoint.y != m_GoToPlatform[0].y)
				|| (m_RightPoint.x != m_GoToPlatform[1].x) || (m_RightPoint.y != m_GoToPlatform[1].y))
			{
				
				m_LeftPoint.x += m_DiffLeftX  * (elapsedSec / m_Speed);
				m_LeftPoint.y += m_DiffLeftY * (elapsedSec / m_Speed);
				m_RightPoint.x += m_DiffRightX * (elapsedSec / m_Speed);
				m_RightPoint.y += m_DiffRightY * (elapsedSec / m_Speed);

				if ((m_LeftPoint.x <= m_GoToPlatform[0].x + 1.f) && (m_LeftPoint.y <= m_GoToPlatform[0].y + 1.f)
					&& (m_LeftPoint.x >= m_GoToPlatform[0].x - 1.f) && (m_LeftPoint.y >= m_GoToPlatform[0].y - 1.f))
				{
					m_Timer -= maxTimer;
					m_DiffLeftX = 0.f;
					m_DiffLeftY = 0.f;
					m_DiffRightX = 0.f;
					m_DiffRightY = 0.f;
					m_CurrPlatform = m_GoToPlatformIdx;
				}
			}
		}
	}
}

int Platform::ChangeNewPlatform(int nrOfPlatforms) {
	if (m_GoToPlatform[0].x == m_AllPlatforms[m_CurrPlatform].x
		&& m_GoToPlatform[0].x == m_AllPlatforms[m_CurrPlatform].x)
	{
		int randPlatform{ (rand() % nrOfPlatforms) * 2 };
		while (m_GoToPlatform[0].x == m_AllPlatforms[randPlatform].x && m_GoToPlatform[0].y == m_AllPlatforms[randPlatform].y)
		{
			randPlatform = (rand() % nrOfPlatforms) * 2;
		}
		m_GoToPlatform[0] = m_AllPlatforms[randPlatform]; //left
		m_GoToPlatform[1] = m_AllPlatforms[randPlatform + 1]; //right

	
		ChangePlatformDiffs();
		
		m_GoToPlatformIdx = randPlatform;
	}
	return -1;
}

Vector2f Platform::GetLeftPoint() const
{
	return m_LeftPoint;
}

Vector2f Platform::GetRightPoint() const
{
	return m_RightPoint;
}

void Platform::ChangePlatformDiffs()
{
	m_DiffLeftX = { (m_GoToPlatform[0].x - m_LeftPoint.x) };
	m_DiffLeftY = { (m_GoToPlatform[0].y - m_LeftPoint.y) };
	m_DiffRightX = { (m_GoToPlatform[1].x - m_RightPoint.x) };
	m_DiffRightY = { (m_GoToPlatform[1].y - m_RightPoint.y) };
}