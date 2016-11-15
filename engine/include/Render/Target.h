#ifndef __RENDERTARGET_H__
#define __RENDERTARGET_H__

#pragma once

#include "Render/Texture.h"
#include "Render/RenderTypes.h"
#include "Utils/IRect.h"

namespace Render {

//
// Объект, ведущий себя подобно текстуре, в который можно что-то рисовать.
//
// Особенности:
// 1) тот кто создал объект методом Render::RenderDeviceImpl::CreateRenderTarget,
//    обязан также удалить его методом Render::RenderDeviceImpl::DeleteRenderTarget;
// 2) при всех операциях в Render::Target нужно проверять, валиден ли он с помощью IsValid();
//
class Target
{
public:
	virtual ~Target();

	bool needTranslate() const;
	
	void TranslateUV(FPoint& uv) const;
	void TranslateUV(FRect& rect, FRect& uv) const;
	void TranslateUV(math::Vector3& v0, math::Vector3& v1, math::Vector3& v2, math::Vector3& v3, FRect &uv) const;

	/// Возвращает ширину таргета
	int Width() const { return static_cast<int>(_width); }
	/// Возвращает высоту таргета
	int Height() const { return static_cast<int>(_height); }

	/// Возвращает рисуемую часть таргета
	IRect getBitmapRect() const { return IRect(IPoint(0, 0), _width, _height); }

	//
	// Установка текущей текстурой
	//
	void Bind(int cannel = 0, int stageOp = 0);

	//
	// Установка текущей текстурой для альфа-рисования
	//
	void BindAlpha();

	//
	// Рисование текстуры
	//
	void Draw(const FPoint& position);

	//
	// Валиден ли Таргет
	//
	bool IsValid() const;

	//
	// Использует ли таргет мультисэмплинг
	//
	bool IsMultisampled() const;

	/// Пустой ли Таргет.
	/// Пустой таргет есть валидный таргет, но его содержимое было утеряно в результате сброса устройства
	bool Empty() const;

	//
	// Сохраняет содержимое в буфер.
	// Работает только между вызовами BeginRenderTo()/EndRenderTo().
	//
	bool CopyToImage(Image& image);

	//
	// Сохранить в формате BMP
	// Особенность: переворачивает текстуру по вертикали
	// Работает только между вызовами BeginRenderTo()/EndRenderTo().
	//
	void SaveAsBmp(const std::string & path);

	//
	// Сохранить в формате PNG
	// Особенность: переворачивает текстуру по вертикали
	// Работает только между вызовами BeginRenderTo()/EndRenderTo().
	//
	void SaveAsPng(const std::string & path);
	
	//
	// Сохранить в формате JPEG
	// Работает только между вызовами BeginRenderTo()/EndRenderTo().
	//
	void SaveAsJpeg(const std::string& path, int quality = 80);

	//
	// Установка фильтрации таргета
	//
	void setFilterType(FilteringType filter);

	//
	// Установка адресации текстурных координат таргета
	//
	void setAddressMode(AddressMode address);

private:
	//
	// Конструктор скрыт для всех кроме RenderDeviceImpl
	//
	Target(int width, int height);

	//
	// Очистить ресурсы, которыми владеет объект
	//
	void ReleaseResources();

	//
	// Зачищает все ресурсы и делает цель невалидной.
	//
	void SetInvalid();

private:
	friend class RenderDeviceGLES2;
	friend class RenderDeviceGL;
		// чтобы только там можно было создавать объекты такого типа

	DEVTEXTURE _texture;	
	DEVTEXTURE _depthStencilBuffer;
	DEVTEXTURE _stencilSeparateBuffer;

#if defined(ENGINE_TARGET_IPHONE)
    DEVTEXTURE _msRB;
    DEVTEXTURE _msDB;
    DEVTEXTURE _msFB;
#endif
	
	int16_t _width;      ///< ширина текстуры
	int16_t _height;     ///< высота текстуры
	int16_t _widthPow2;  ///< ширина текстуры, округлённая до ближайшей большей степени двойки
	int16_t _heightPow2; ///< высота текстуры, округлённая до ближайшей большей степени двойки

	EnginePixelType _pixelType; ///< Формат пикселя
	FilteringType _filter;      ///< Тип фильтрации
	AddressMode _address;       ///< Тип адресации текстурных координат
	MultisampleType _msType;    ///< тип мультисэмплинга

	bool _valid        : 1; ///< Валидна ли цель рендеринга (становится невалидной, если устройство переинициализировалось)
	bool _empty        : 1; ///< Пуста ли цель рендеринга
	bool _isBinded     : 1; ///< Забиндена ли цель рендеринга
	bool _depth        : 1; ///< Используется ли depth buffer
	bool _stencil      : 1; ///< Используется ли stencil buffer
	bool _filterDirty  : 1; ///< Изменился ли _filter
	bool _addressDirty : 1;	///< Изменился ли _address
	bool _multisampled : 1; ///< Используется ли сглаживание
};

} // namespace Render

#endif // __RENDERTARGET_H__
