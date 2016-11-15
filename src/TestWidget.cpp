#include "stdafx.h"
#include "TestWidget.h"
#include "MiniBubble.h"
#include "Bubble.h"
#include "BubbleColor.h"
#include "SettingsManager.h"
#include <MM.h>

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
{
	Init();
}

void TestWidget::Init()
{
	m_startButtonTex = Core::resourceManager.Get<Render::Texture>("btnStart_Text");

	m_bubblesCount = utils::lexical_cast<unsigned int>(SettingsManager::Instance()->GetSettingByName(COUNT_POINTS, "20"));
	m_goalPerLevel = utils::lexical_cast<unsigned int>(SettingsManager::Instance()->GetSettingByName(GOAL_PER_ROUND, "3"));

	m_gameState = START_SCREEN;
	m_isAlreadyClickedLevel = false;

	m_gameLevel = 0;
	m_collectedBubbles = 0;
	m_goalForLevel = 0;
	m_isLastLevel = false;
	m_isFirstLaunch = true;
	m_score = 0;
	m_totalScore = 0;

	// Play main theme
	std::string main_theme_track = SettingsManager::Instance()->GetSettingByName(MAIN_THEME_TRACK, "Jump_and_run");
	MM::manager.PlayTrack(main_theme_track, true, 0.5f);
}

void TestWidget::DrawStartScreen()
{
	//
	// Получаем текущее положение курсора мыши.
	//
	IPoint mouse_pos = Core::mainInput.GetMousePos();

	//
	// Проталкиваем в стек текущее преобразование координат, чтобы в дальнейшем
	// можно было восстановить это преобразование вызовом PopMatrix.
	//
	Render::device.PushMatrix();

	math::Vector3 screen_center;
	Layer* topLayer = Core::mainScreen.GetTopLayer();
	if (NULL != topLayer) {
		screen_center = topLayer->centerRotation;
	}


	Render::device.MatrixTranslate(screen_center);
	Render::device.MatrixTranslate(-m_startButtonTex->getBitmapRect().width*0.5f, -m_startButtonTex->getBitmapRect().height*0.5f, 0.0f);

	//
	// Метод Texture::Draw() выводит квадратный спрайт с размерами текстуры
	// в центре координат (0, 0). Центр координат и преобразование координат вершин
	// спрайта устанавливаются с применением текущего преобразования.
	//
	// При вызове метода Texture::Draw() вызывать Texture::Bind() необязательно.
	//

	m_startButtonTex->Draw();

	//
	// Воостанавливаем прежнее преобразование координат, снимая со стека изменённый фрейм.
	//
	Render::device.PopMatrix();
}

void TestWidget::DrawPostStartScreen()
{
	Render::BindFont("Animated");
	Render::PrintString(512, 410, "{font size=\"36\"} To win you've to collect bubbles.\n Click left mouse button to create BIG BUBBLE. It'll help you to win!\n Click now right button to start the game", 1.0f, CenterAlign);
}

void TestWidget::DrawInLevel()
{
	std::list<Bubble>::iterator iterator_bubbles = m_bubbles_list.begin();
	while (iterator_bubbles != m_bubbles_list.end())
	{
		(*iterator_bubbles).Draw();
		++iterator_bubbles;
	}

	std::list<MiniBubble>::iterator iterator_miniBubbles = m_mini_bubbles_list.begin();
	while (iterator_miniBubbles != m_mini_bubbles_list.end())
	{
		bool isClose = false;
		float pos_x = 0.0f;
		float pos_y = 0.0f;
		std::string color = "";

		if (!m_bubbles_list.empty()) {
			std::list<Bubble>::iterator iterator = m_bubbles_list.begin();
			while (iterator != m_bubbles_list.end())
			{

				(*iterator_miniBubbles).GetCurrentPosition(pos_x, pos_y);
				color = (*iterator_miniBubbles).GetColor();

				isClose = (*iterator).isClose(pos_x, pos_y, (*iterator_miniBubbles).GetRadius());

				if (isClose) {
					break;
				}
				++iterator;
			}
		}

		if (!isClose) {
			(*iterator_miniBubbles).Draw();
			++iterator_miniBubbles;
		}
		else {
			iterator_miniBubbles = m_mini_bubbles_list.erase(iterator_miniBubbles);
			m_bubbles_list.push_back(Bubble(color, pos_x, pos_y));			

			++m_collectedBubbles;

			ParticleEffectPtr _eff = _effCont.AddEffect(BubbleColor::Instance()->GetExplodeColor(color));
			_eff->posX = pos_x;
			_eff->posY = pos_y;
			_eff->Reset();

			MM::manager.PlaySample("BubblePop");

			ScoreBubble score_bubble;
			score_bubble.score = BubbleColor::Instance()->GetBubbleScore(color);
			score_bubble.pos_x = pos_x;
			score_bubble.pos_y = pos_y;
			score_bubble.time = 30;
			m_scoresList.push_back(score_bubble);

			m_score += score_bubble.score;
		}
	}

	Render::BindFont("Animated");
	Render::PrintString(10, 750, "{font size=\"36\"}Level: " + utils::lexical_cast(m_gameLevel));
	Render::PrintString(512, 750, "{font size=\"36\"}Collected bubbles: " + utils::lexical_cast(m_collectedBubbles) + " from " + utils::lexical_cast(m_goalForLevel), 1.0, CenterAlign);
	Render::PrintString(10, 720, "{font size=\"36\"}Score: " + utils::lexical_cast(m_score));
	Render::PrintString(10, 690, "{font size=\"36\"}Total score: " + utils::lexical_cast(m_totalScore));
}

void TestWidget::DrawEndLevel()
{
	DrawInLevel();
	DrawStartScreen();
}

void TestWidget::DrawRestartLevel()
{
	DrawInLevel();
	Render::BindFont("Animated");
	Render::PrintString(512, 384, "{font size=\"36\"}Click right mouse button to restart this level", 1.0f, CenterAlign);
}

void TestWidget::DrawEndGame()
{
	Render::BindFont("Animated");
	Render::PrintString(512, 420, "{font size=\"36\"}Excellent! You win the game!\n Click right mouse button to restart game.\n Total score: " + utils::lexical_cast(m_totalScore), 1.0f, CenterAlign);

}

void TestWidget::Draw()
{
	// Выбор отрисовки в зависимости от состояния игры
	switch (m_gameState)
	{
	case START_SCREEN:
		DrawStartScreen();
		break;
	case IN_LEVEL:
		DrawInLevel();
		break;
	case END_LEVEL:
		DrawEndLevel();
		break;
	case RESTART_LEVEL:
		DrawRestartLevel();
		break;
	case END_GAME:
		DrawEndGame();
		break;
	case POST_START_SCREEN:
		DrawPostStartScreen();
		break;
	default:
		break;
	}

	// Отрисовываем заработанные очки
	std::list<ScoreBubble>::iterator iterator = m_scoresList.begin();
	while (iterator != m_scoresList.end())
	{
		Render::BindFont("Animated");
		Render::PrintString((*iterator).pos_x, (*iterator).pos_y, "{font size=\"36\"}+" + utils::lexical_cast((*iterator).score), 1.0f, CenterAlign);
		++iterator;
	}

	//
	// Получаем текущее положение курсора мыши.
	//
	IPoint mouse_pos = Core::mainInput.GetMousePos();

	//
	// Рисуем все эффекты, которые добавили в контейнер (Update() для контейнера вызывать не нужно).
	//
	_effCont.Draw();

	// Отрисовываем текущие координаты мыши
	Render::BindFont("arial");
	Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);
	

}

void TestWidget::Update(float dt)
{
	//
	// Обновим контейнер с эффектами
	//
	_effCont.Update(dt);

	if (IN_LEVEL == m_gameState)
	{
		// Обновляем или чистим список больших пузырей
		std::list<Bubble>::iterator iterator = m_bubbles_list.begin();
		while (iterator != m_bubbles_list.end())
		{
			if (!((*iterator).isLive())) {
				std::string color = (*iterator).GetColor();
				float pos_x = 0.0f;
				float pos_y = 0.0f;
				(*iterator).GetCurrentPosition(pos_x, pos_y);

				ParticleEffectPtr _eff = _effCont.AddEffect(BubbleColor::Instance()->GetExplodeColor(color));
				_eff->posX = pos_x;
				_eff->posY = pos_y;
				_eff->Reset();

				MM::manager.PlaySample("BubblePop");

				iterator = m_bubbles_list.erase(iterator);
			}
			else {
				(*iterator).Update(dt);
				++iterator;
			}

		}

		// Обновляем или чистим список мини-пузырей
		std::list<MiniBubble>::iterator iterator_miniBubbles = m_mini_bubbles_list.begin();
		while (iterator_miniBubbles != m_mini_bubbles_list.end())
		{
			(*iterator_miniBubbles).Update(dt);
			++iterator_miniBubbles;
		}

		if (m_isAlreadyClickedLevel
			&& m_bubbles_list.empty()) {
			if (m_collectedBubbles >= m_goalForLevel) {
				m_gameState = END_LEVEL;
			}
			else {
				m_gameState = RESTART_LEVEL;
			}
		}

		// Обновляем или чистим список очков, отображаемых на экране
		std::list<ScoreBubble>::iterator iterator_scores = m_scoresList.begin();
		while (iterator_scores != m_scoresList.end())
		{
			if ((*iterator_scores).time == 0) {
				iterator_scores = m_scoresList.erase(iterator_scores);
			}
			else {
				--(*iterator_scores).time;
				++iterator_scores;
			}
		}
	}	
}

void TestWidget::StartNewLevel()
{
	m_gameState = IN_LEVEL;

	// reset game state
	m_isAlreadyClickedLevel = false;
	m_mini_bubbles_list.clear();
	for (unsigned int i = 0; i < m_bubblesCount; ++i) {
		m_mini_bubbles_list.push_back(MiniBubble());
	}

	++m_gameLevel;
	m_collectedBubbles = 0;
	m_score = 0;
	m_scoresList.clear();

	if (m_isLastLevel
		&& m_goalForLevel >= m_bubblesCount) {
		m_gameState = END_GAME;
	}


	if (!m_isLastLevel
		&& (m_goalForLevel + m_goalPerLevel > m_bubblesCount)) {
		m_goalForLevel = m_bubblesCount;
		m_isLastLevel = true;
	}
	else {
		m_goalForLevel += m_goalPerLevel;
	}
}

void TestWidget::StartNewLevel(const IPoint &mouse_pos)
{
	math::Vector3 start_btn;
	Layer* topLayer = Core::mainScreen.GetTopLayer();
	if (NULL != topLayer) {
		start_btn = topLayer->centerRotation;
	}

	if (mouse_pos.x >= (start_btn.x - m_startButtonTex->getBitmapRect().width * 0.5f)
		&& mouse_pos.x <= (start_btn.x + m_startButtonTex->getBitmapRect().width * 0.5f)
		&& mouse_pos.y <= (start_btn.y + m_startButtonTex->getBitmapRect().height * 0.5f)
		&& mouse_pos.y >= (start_btn.y - m_startButtonTex->getBitmapRect().height * 0.5f))
	{
		m_totalScore += m_score;
		StartNewLevel();	
	}
}

void TestWidget::RestartLevel()
{
	// reset game state
	m_isAlreadyClickedLevel = false;
	m_mini_bubbles_list.clear();
	for (unsigned int i = 0; i < m_bubblesCount; ++i) {
		m_mini_bubbles_list.push_back(MiniBubble());
	}

	//m_needLevelRestart = true;
	m_collectedBubbles = 0;
	m_gameState = IN_LEVEL;
	m_score = 0;
	m_scoresList.clear();
}

void TestWidget::RestartGame()
{
	m_goalForLevel = 0;
	m_gameLevel = 0;
	m_gameState = START_SCREEN;
	m_isLastLevel = false;
	m_score = 0;
	m_scoresList.clear();
	m_totalScore = 0;
}

bool TestWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseRightButton())
	{
		if (RESTART_LEVEL == m_gameState) {
			RestartLevel();
		}
		else if (END_GAME == m_gameState) {
			RestartGame();
		}
		else if (POST_START_SCREEN == m_gameState) {
			StartNewLevel();
		}
	}
	else
	{
		if (START_SCREEN == m_gameState) {
			if (m_isFirstLaunch) {
				m_gameState = POST_START_SCREEN;
				m_isFirstLaunch = false;
			}
			else {
				StartNewLevel(mouse_pos);
			}
					
		}
		else if (IN_LEVEL == m_gameState) {
			if (!m_isAlreadyClickedLevel) {
				MM::manager.PlaySample("BubblePop");
				m_bubbles_list.push_back(Bubble());
				m_isAlreadyClickedLevel = true;
			}
		} 
		else if (END_LEVEL == m_gameState) {
			StartNewLevel(mouse_pos);
		}		
	}
	return false;
}

void TestWidget::MouseMove(const IPoint &mouse_pos)
{
}

void TestWidget::MouseUp(const IPoint &mouse_pos)
{
}

void TestWidget::AcceptMessage(const Message& message)
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//
	// Например, при вводе символа с клавиатуры виджетам на активном слое посылается
	// сообщение KeyPress с кодом символа в параметре.
	//
	if (message.getPublisher() == "KeyPress") 
	{
		int code = utils::lexical_cast<int>(message.getData());
		if (code < 0)
		{
			//
			// Отрицательные значения посылаются для виртуальных кодов клавиш,
			// например, -VK_RETURN, -VK_ESCAPE и т.д.
			//
			return;
		}
		
		//
		// Положительные значения посылаются для символов алфавита.
		//
		if (code == 'a')
		{
		}
	}
}
