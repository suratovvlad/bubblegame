#pragma once

///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///

#include <vector>
#include <list>

class MiniBubble;
class Bubble;

class TestWidget : public GUI::Widget
{
	enum GameState
	{
		START_SCREEN = 1,
		IN_LEVEL = 2,
		END_LEVEL = 3,
		RESTART_LEVEL = 4,
		END_GAME = 5,
		POST_START_SCREEN = 6
	};

public:
	TestWidget(const std::string& name, rapidxml::xml_node<>* elem);

	void Draw();
	void Update(float dt);
	
	void AcceptMessage(const Message& message);
	
	bool MouseDown(const IPoint& mouse_pos);
	void MouseMove(const IPoint& mouse_pos);
	void MouseUp(const IPoint& mouse_pos);

private:
	void Init();

	void DrawStartScreen();
	void DrawPostStartScreen();
	void DrawInLevel();
	void DrawEndLevel();
	void DrawRestartLevel();
	void DrawEndGame();

	void StartNewLevel();
	void StartNewLevel(const IPoint &mouse_pos);
	void RestartLevel();
	void RestartGame();

private:

	Render::Texture* m_startButtonTex;

	EffectsContainer _effCont;

	std::list<MiniBubble> m_mini_bubbles_list;
	unsigned int m_bubblesCount;

	std::list<Bubble> m_bubbles_list;

	unsigned int m_gameState;
	bool m_isAlreadyClickedLevel; // Only One Click Per Level
	unsigned int m_gameLevel;
	unsigned int m_collectedBubbles;
	unsigned int m_goalForLevel;
	unsigned int m_goalPerLevel;
	bool m_isLastLevel;
	bool m_isFirstLaunch;
	unsigned int m_score;
	unsigned int m_totalScore;

	struct ScoreBubble{
		unsigned int score;
		float pos_x;
		float pos_y;
		unsigned int time;
	};

	std::list<ScoreBubble> m_scoresList;
};
