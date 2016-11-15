#pragma once

// Р С™Р В»Р В°РЎРѓРЎРѓ Р Т‘Р В»РЎРЏ iphone-Р С—Р С•Р Т‘Р С•Р В±Р Р…Р С•Р С–Р С• РЎРѓР С”РЎР‚Р С•Р В»Р В»Р С‘Р Р…Р С–Р В° (Р Р†Р ВµРЎР‚РЎвЂљР С‘Р С”Р В°Р В»РЎРЉР Р…Р С•Р С–Р С• Р С‘Р В»Р С‘ Р С–Р С•РЎР‚Р С‘Р В·Р С•Р Р…РЎвЂљР В°Р В»РЎРЉР Р…Р С•Р С–Р С•)
// Р ВРЎРѓР С—Р С•Р В»РЎРЉР В·Р С•Р Р†Р В°Р Р…Р С‘Р Вµ:
//  РЎРѓР С•Р В·Р Т‘Р В°Р ВµР С Р С•Р В±РЎР‰Р ВµР С”РЎвЂљ
//  Р С‘Р Р…Р С‘РЎвЂ Р С‘Р В°Р В»Р С‘Р В·Р С‘РЎР‚РЎС“Р ВµР С РЎР‚Р В°Р В·Р СР ВµРЎР‚ Р С”Р С•Р Р…РЎвЂљР ВµР Р…РЎвЂљР В° РЎвЂћРЎС“Р Р…Р С”РЎвЂ Р С‘Р ВµР в„– SetContentsSize()
//  Р С—Р С•РЎРѓРЎвЂ№Р В»Р В°Р ВµР С Р ВµР СРЎС“ MouseMove, MouseUp, MouseDown, Update
//  РЎР‚Р С‘РЎРѓРЎС“Р ВµР С Р С”Р С•Р Р…РЎвЂљР ВµР Р…РЎвЂљ, Р С‘РЎРѓР С—Р С•Р В»РЎРЉР В·РЎС“РЎРЏ Р В·Р Р…Р В°РЎвЂЎР ВµР Р…Р С‘Р Вµ GetPosition()
//  РЎР‚Р С‘РЎРѓРЎС“Р ВµР С РЎРѓР В»Р В°Р в„–Р Т‘Р ВµРЎР‚, Р С‘РЎРѓР С—Р С•Р В»РЎРЉР В·РЎС“РЎРЏ GetSliderShiftAndSize()
// Р С’Р В»Р С–Р С•РЎР‚Р С‘РЎвЂљР С Р С—Р С•Р В·Р В°Р С‘Р СРЎРѓРЎвЂљР Р†Р С•Р Р†Р В°Р Р… Р С•РЎвЂљРЎРѓРЎР‹Р Т‘Р В°: http://www.macresearch.org/dynamics-scrolling
class KineticScroller
{
public:
		// Коэффициенты:
        float drag_threshold; // На сколько нужно сдвинуть палец, чтобы началось перетаскивание.
        float bounce_n; // На сколько можно выехать за самый край (при position < 0, то есть справа)
        float bounce_p; // (при position > 0, то есть слева)
        float return_coeff; // Коэффициент, используемый для вычисления скорости при bounce.
        float min_bounce_vel; // Минимальная скорость при bounce.
        float max_velocity;
        float off_velocity; // Минимальная скорость отрыва от магнитной точки.
        float run_velocity; // Скорость свободного качения к магнитной точке. Обычно run_velocity = max_velocity.
        float deceleration1, deceleration2; // Линейное замедление, экспоненциальное замедление.
        float bounce_deceleration;
		float maxSpeedConstantMotion;		//Максимальная скорость разгона скроллера при постоянном движении
		float accelerationConstantMotion;	//Ускорение скроллера при постоянном движении

        // Параметры зоны перемещения
        float drag_min_pos; // Самый левый край прокрутки.
        float drag_max_pos; // Самый правый край.
        std::vector<float> magnet_points;

        // Динамические параметры
        float position; // Текущее смещение аквариума.
        float scroll_v; // Скорость скролла.

protected:

		bool isDragging; // Триггер перетаскивания после преодоления порогового смещения.
        bool tap_down, tap_up; // Было ли нажатие/отпускание (проверяется и сбрасывается в Update).
		bool just_touched;	//только что тапнули (чтобы остановить прокрутку по инерции). устанавливается в Touched. сбрасывается при движении пальца или отпускании
        bool isMagneted; // Примагнитились. Нужно, чтобы не отмагничиваться из-за высокой скорости при bounce.
        float click_pos, last_mouse_pos, prev_mouse_pos;
        std::vector<float> velocity_buf; // Буфер для вычисления средней скорости движения пальца.
		bool isSimulatedMoving; //Имитируем ли перемещение искуственно
		float SimulatedStartPos;//Начальная точка имитации движения
		float SimulatedEndPos;	//Конечная точка имитации движения
		float SimulatedSpeed;	//Скорость для имитации 
		float SimulatedTimer;	//Таймер для расчета пути
		bool isConstantMotion;	//Флаг для запуска постоянного движения скроллера (актуально, к примеру, для титров) 

public:
        KineticScroller();
        
        void Update(float dt);
        
        void MouseDown(float mouse_pos);
        void MouseMove(float mouse_pos);
        void MouseUp(float mouse_pos);
		void Touched();
		void UnTouched();
        
        bool WillBeDragging();
        void CancelDragging();
        bool IsTapDown() { return tap_down; }

		// Скролл движется?
		bool IsScrolling() const { return scroll_v != 0.0f; }
        
        bool HasMagnetPoints();
		float NearestMagnetPoint(float p); // В случае отсутствия точек возвращает ноль, так что лучше заранее проверять, есть ли они.
        float NextMagnetPoint(float p); // Следующая точка в сторону скорости. Если стоит на точке, то возвращает её.
        
        bool OnMagnetPoint(); // Находимся на магнитной точке, не двигаемся и не перетаскиваем.
        
        float Fraction(); // Возвращает положение скроллера, нормализованное к интервалу [0, 1].
        void SetFracPos(float f); // Устанавливает положение скроллера между min и max значениями на основе f из интервала [0, 1].		void SetBounceNP(int value); // Set bounce_n & bounce_p
		void SetBounceNP(int value); // Set bounce_n & bounce_p

		void StartSimulatedMoving(float endpos, float speed); //Активируем имитацию
		void UpdateSimulatedMoving(float dt); //Обновление состояния имитации
		bool GetIsSimulatedMoving(){return isSimulatedMoving;}

		//Запустить постоянное движение скроллера (MaxSpeed = 50, Acceleration = 2) 
		void StartConstantMotion(); 
		//Запустить постоянное движение скроллера (MaxSpeed - максимальная скорость, Acceleration - ускорение) 
		void StartConstantMotion(float MaxSpeed, float Acceleration);
		//Остановить постоянное движение скроллера
		void StopConstantMotion();

		// Методы для доступа к свойствам
		void setDeceleration1(float d) { deceleration1 = d; }
		float getDeceleration1() const { return deceleration1; }

		void setDeceleration2(float d) { deceleration2 = d; }
		float getDeceleration2() const { return deceleration2; }

		void setDragThreshold(float d) { drag_threshold = d; }
};
