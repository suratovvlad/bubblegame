#pragma once

#include <Utils/Color.h>

#include "IFlashDisplayObject.h"
#include "IFlashSprite.h"
#include "IFlashCustomDrawOperation.h"
#include "FlashMarkSweep.h"
#include "FlashUtility.hpp"
#include "FlashUpdateListener.hpp"

/*
	Базовый клас реализации интерфейса IFlashDisplayObject(все кастомные объекты следует наследовать от него)
	в таком виде:

	class FlashDisplayObjectChild: public FlashDisplayObject<IFlashDisplayObject>
	{
		...
	}

	Всех наследников этого класса следует создавать по следующему сценарию:

	IFlashDisplayObject* l_obj = new CPrototype<FlashDisplayObjectChild>();
	В этом случае объект бдует иметь возможность клонироваться (метод Clone интрефейса IPrototype), 
	но для правильной работы клонирование необхождимо описать корректный конструктор копирования

	или 

	IFlashDisplayObject* l_obj = new CFlashUnknown<FlashDisplayObjectChild>();
	Если не требуется функциональность клонирования

	С полной диаграммой классов можно ознакомится по ссылке ниже:
	https://drive.google.com/a/playrix.com/file/d/0Bziu0DiTP-9vSjNteDFDSDFSQkU/view?usp=sharing

*/
template<class T>
class FlashDisplayObject: public T
{
public:
	FlashDisplayObject():
		parent(NULL),
		updateRate(1),
		decomposition(),
		name(""),
		operation(NULL),
		mouseTransparent(false),
		skipMouseEvents(false),
		ownVisible(true),
		autoPlay(true),
		decompositionValid(false),
		ownColor(Color::WHITE)
	{
		::memcpy(ownMatrix, identityMatrix, 6 * sizeof(float));
	};

	/*
		При кажущейся излишности конструктор копированя тут необходим, потому как при создании объектов через шаблон (CPrototype<FlashDisplayObjectContainer>),
		конструктор копирования базового класса(CPrototype) не вызовется если тут не переопределить конструктор копирования
	*/
	FlashDisplayObject(FlashDisplayObject& _ref):
		parent(NULL),
		updateRate(_ref.updateRate),
		decomposition(_ref.decomposition),
		name(_ref.name),
		operation(_ref.operation),
		mouseTransparent(_ref.mouseTransparent),
		skipMouseEvents(_ref.skipMouseEvents),
		ownVisible(_ref.ownVisible),
		autoPlay(_ref.autoPlay),
		decompositionValid(_ref.decompositionValid),
		ownColor(_ref.ownColor)
	{
		::memcpy(ownMatrix, _ref.ownMatrix, 6 * sizeof(float));
	};

	virtual ~FlashDisplayObject()
	{
	};

	void applyTransform(IFlashDisplayObject* another)
	{
		float A[9];
		float B[9];
		float C[9];
		this->getMatrix(A);
		another->getMatrix(B);
		::multMatrix3x3(C, A, B);
		this->setMatrix(C);

		ownColor *= another->getColor();

		this->setVisible(another->getVisible() && this->getVisible());
	};

	void advance(FlashUpdateListener* updateListener, float dt)
	{
		updateListener->addUpdateRequest(this, dt);
	};

	void setHitTestTransparent(bool _value)
	{
		mouseTransparent = _value;
	};

	bool getHitTestTransparent()
	{
		return mouseTransparent;
	};

	void setHitTestDispatcher(bool _value)
	{
		skipMouseEvents = !_value;
	};

	bool getHitTestDispatcher()
	{
		return !skipMouseEvents;
	};

	void setVisible(bool value)
	{
		ownVisible = value;
	};

	bool getVisible()
	{
		return ownVisible;
	};

	void setName(const std::string& _name)
	{
		name = _name;
	};

	const std::string& getName()
	{
		return name;
	};

	void setAlpha(float value)
	{
		ownColor.alpha = value * 0xFF;
	};

	float getAlpha()
	{
		return ownColor.alpha / (float)0xFF;
	};

	void setColor(const Color& color)
	{
		ownColor = color;
	};

	const Color& getColor()
	{
		return ownColor;
	};

	void setPosition(float x, float y)
	{
		ownMatrix[2] = x;
		ownMatrix[5] = y;
	};

	void getPosition(float& x, float& y)
	{
		if ( !decompositionValid )
			__decompose();

		x = ownMatrix[2];
		y = ownMatrix[5];
	};

	void setRotation(float radians)
	{
		if ( !decompositionValid )
			__decompose();

		decomposition.rotation = radians;
		recompose(ownMatrix, decomposition);
	};

	float getRotation()
	{
		if ( !decompositionValid )
			__decompose();

		return decomposition.rotation;
	};

	void setShear(float k)
	{
		if ( !decompositionValid )
			__decompose();

		decomposition.shear = k;
		recompose(ownMatrix, decomposition);
	};

	float getShear()
	{
		if ( !decompositionValid )
			__decompose();

		return decomposition.shear;
	};

	void setScale(float scaleX, float scaleY)
	{
		if ( !decompositionValid )
			__decompose();

		decomposition.scaleX = scaleX;
		decomposition.scaleY = scaleY;
		recompose(ownMatrix, decomposition);
	};

	void getScale(float& x, float& y)
	{
		if ( !decompositionValid )
			__decompose();

		x = decomposition.scaleX;
		y = decomposition.scaleY;
	};

	void setMatrix(const float *matrix)
	{
		::memcpy((uint8_t*)ownMatrix, (uint8_t*)matrix, sizeof(float) * 6);
		decompositionValid = false;
	};

	void getMatrix(float *matrix)
	{
		::memcpy((uint8_t*)matrix, (uint8_t*)ownMatrix, sizeof(float) * 6);
	};

	void localToParent(float& x, float& y)
	{
		float x0 = x * ownMatrix[0] + y * ownMatrix[1] + ownMatrix[2];
		float y0 = x * ownMatrix[3] + y * ownMatrix[4] + ownMatrix[5];

		x = x0;
		y = y0;
	};

	void parentToLocal(float& x, float& y)
	{
		float det = 1.0f / (ownMatrix[0] * ownMatrix[4] - ownMatrix[1] * ownMatrix[3]);
		float tx = det * (ownMatrix[1] * ownMatrix[5] - ownMatrix[4] * ownMatrix[2]);
		float ty = det * (ownMatrix[3] * ownMatrix[2] - ownMatrix[0] * ownMatrix[5]);
		float a = det * ownMatrix[4];
		float b = -det * ownMatrix[3];
		float c = -det * ownMatrix[1];
		float d = det * ownMatrix[0];

		float x0 = x * a + y * c + tx;
		float y0 = x * b + y * d + ty;

		x = x0;
		y = y0;
	};

	void localToGlobal(float &x, float &y)
	{
		IFlashDisplayObject* displayObject = this;

		while ( displayObject )
		{
			displayObject->localToParent(x, y);
			displayObject = displayObject->getParent();
		};
	};

	void globalToLocal(float &x, float &y)
	{
		if ( parent )
			parent->globalToLocal(x, y);

		parentToLocal(x, y);
	};

	void localToTarget(float &x, float& y, IFlashDisplayObject* target)
	{
		if ( target == 0 ){
			//по определению
			localToGlobal(x, y);

		//Несколько частных случаев для ускорения работы (getCommonAncestor дорогой)
		}else if ( target == this ){
			return;
		}else if ( target == parent ){
			return localToParent(x, y);
		}else if ( target->getParent() == parent ){
			localToParent(x, y);
			target->parentToLocal(x, y);
		}else{
			IFlashDisplayObject* commonAncestor = getCommonAncestor(target);

			if ( !commonAncestor ){
				localToGlobal(x, y);
				target->globalToLocal(x, y);
			}else{
				IFlashDisplayObject* current = this;
				while ( current != commonAncestor ){
					current->localToParent(x, y);
					current = current->getParent();
				}
				__ancestorToLocal(x, y, current, target);
			}
		}
	};

	void update(float dt)
	{
	};

	bool hasUpdate()
	{
		return false;
	};

	void unsafeSetParent(IFlashSprite* _parent)
	{
		if(parent != _parent)
		{
			int l_incval = hasUpdate() ? 1 : 0;

			if (parent != NULL)
			{
				parent->changeUpdateListeners(-l_incval);
			};

			parent = _parent;
	
			if (parent )
			{
				parent->changeUpdateListeners(l_incval);
			};
		};
	};

	IFlashSprite* getParent()
	{
		return parent;
	};

	IFlashDisplayObject* getCommonAncestor(IFlashDisplayObject* another)
	{
		IFlashDisplayObject* l_retval = nullptr;

		if (another )
		{
			IFlashDisplayObject* lTree[256];
			IFlashDisplayObject* rTree[256];
			int lPtr = 0, rPtr = 0;

			for (IFlashDisplayObject* l_left = this; l_left; l_left = l_left->getParent())
			{
				lTree[lPtr] = l_left;
				lPtr += 1;
			};

			for (IFlashDisplayObject* l_right = another; l_right; l_right = l_right->getParent())
			{
				rTree[rPtr] = l_right;
				rPtr += 1;
			};
		
			lPtr--;
			rPtr--;

			while ( lPtr >= 0 && rPtr >= 0 && (lTree[lPtr] == rTree[rPtr]))
			{
				l_retval = lTree[lPtr];

				lPtr--;
				rPtr--;
			};
		};

		return l_retval;
	}

	IFlashDisplayObject* getRoot()
	{
		IFlashDisplayObject* l_retval = this;

		while (l_retval->getParent())
			l_retval = l_retval->getParent();

		return l_retval;
	};

	void setUpdateRate(float rate)
	{
		updateRate = rate;
	};

	float getUpdateRate()
	{
		return updateRate;
	};

	void setCustomDrawOperation(IFlashCustomDrawOperation* _operation)
	{
		operation = _operation;
	};

private:
	void __decompose()
	{
		decomposition = decompose(ownMatrix);
		decompositionValid = true;
	};

	void __ancestorToLocal(float &x, float& y, IFlashDisplayObject* ancestor, IFlashDisplayObject* target)
	{
		if ( ancestor == target ){
			return;
		}else if ( ancestor == target->getParent() ){
			target->parentToLocal(x, y);
		}else{
			__ancestorToLocal(x, y, ancestor, target->getParent());
			target->parentToLocal(x, y);
		}
	};

protected:
	GC_BLACKEN_DECL()
	{
		if ( parent )
			GC_SHOULD_MARK(parent);

		if ( operation )
			GC_SHOULD_MARK((IGCRef*)operation);
	};

public:
	IFlashSprite* parent;
	IFlashCustomDrawOperation* operation;

	float ownMatrix[6];
	Color ownColor;

	float updateRate;

	MatrixDecomposition decomposition;

	std::string name;

	bool mouseTransparent:1;
	bool skipMouseEvents:1;
	bool ownVisible:1;
	bool autoPlay:1;
	bool decompositionValid:1;
};
