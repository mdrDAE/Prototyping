#pragma once
class Screen
{
public:
	enum class Screens {
		start,
		gameplay,
		death
	};

protected:
	void SwitchScreen(Screens screen);

private:
	Screens m_ScreenState{};
};

