#ifndef __CUBETEXTURE_H__
#define __CUBETEXTURE_H__

#pragma once

#include "Utils/FPoint.h"
#include "Utils/Math.hpp"
#include "Render/Texture.h"
#include "Core/Resource.h"

namespace Core
{
	class ResourceManager;
}

#if defined(ENGINE_TARGET_WIN32)
#	include <GLES2/gl2.h>
#	include <GLES2/gl2ext.h>
#	define DEVCUBETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_IPHONE
#	include <OpenGLES/ES2/gl.h>
#	define DEVCUBETEXTURE GLuint
#endif

#if defined(ENGINE_TARGET_LINUX)
#	include <GLES/gl.h>
#	include <GLES/glext.h>
#	define DEVCUBETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_MACOS
#	include <OpenGL/OpenGL.h>
#	define DEVCUBETEXTURE GLuint
#endif

namespace Render
{
	class RenderDeviceImpl;
	class PartialTexture;

	// ����� ���������� ��������
	class CubeTexture : public Resource, public ITextureType
	{
		friend class RenderDeviceImpl;
		friend class RenderDeviceGLES2;

	public:
		std::string textureID;

		//���� true, �� paths ������ ���� � ��������� ������ ��������
		//� ������� -x, -y, -z, +x, +y, +z. ���� �����-�� �� paths ������, �� ��� ����� �������� ������
		//���� false, �� paths[0] ������ ������� ���� � ��������, ������� �������������� �������
		//��������� ��������, ��������� �� ���������� (�� ������, ����� �� ����-�� ������ ���������,
		//��������� ��� �������� �������������)
		bool hasSeparatePaths;
		std::string paths[6];

	protected:
		/// �������� ������ ���������
		bool binded;
		/// ���� �� �������� ���������
		bool wasUploaded;
		DEVCUBETEXTURE _tex;
		FilteringType _filter;
		AddressMode _address;
		EnginePixelType _pixelType;

	public:
		CubeTexture();
		virtual ~CubeTexture();

		void setFace(int face, const std::string& path);
		
		static CubeTexture * CreateFromXml(rapidxml::xml_node<>* elem);
		
		const std::string& GetName() const { return textureID; }
		size_t GetMemoryInUse() const;

		/// �������� �� ���������, ��� ������������� ���������. ������������� ����������� ������������ �������� ��� ����������������� RenderDeviceImpl. ��. Texture::setDynamic
		bool Empty() const;
		void setFilteringType(FilteringType filter);
		void setAddressMode(AddressMode address);
		AddressMode getAddressMode() const { return _address; }
		/// ��������� ��������
		virtual void Upload();
		/// ��������� �������� � �������� �����
		virtual void Bind(int channel = 0, int stageOp = 0);
		/// ��������� ��������
		virtual void Release();
		
		virtual DEVCUBETEXTURE GetNativeHandle() const { return _tex; }

		virtual TextureType GetTextureType() const { return CUBE_TEXTURE; }
	};

	typedef boost::intrusive_ptr<CubeTexture> CubeTexturePtr;
}

#endif // __CUBETEXTURE_H__
