#ifndef __VOLUMETEXTURE_H__
#define __VOLUMETEXTURE_H__

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
#	define DEVVOLUMETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_IPHONE
#	include <OpenGLES/ES2/gl.h>
#	define DEVVOLUMETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_ANDROID
#	include <GLES/gl.h>
#	include <GLES/glext.h>
#	define DEVVOLUMETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_MACOS
#	include <OpenGL/OpenGL.h>
#	define DEVVOLUMETEXTURE GLuint
#endif

namespace Render
{
	class RenderDeviceImpl;

	// ����� 3D ��������
	class VolumeTexture : public Resource, public ITextureType
	{
		friend class RenderDeviceImpl;

	public:
		std::string textureID;
		std::string path;

	protected:
		/// �������� ������ ���������
		bool binded;
		/// ���� �� �������� ���������
		bool wasUploaded;
		DEVVOLUMETEXTURE _tex;
		FilteringType _filter;
		AddressMode _address;

	public:
		VolumeTexture();
		virtual ~VolumeTexture();
		
		static VolumeTexture* CreateFromXml(rapidxml::xml_node<>* elem);
		
		const std::string& GetName() const { return textureID; }
		size_t GetMemoryInUse() const;

		/// �������� �� ���������, ��� ������������� ���������. ������������� ����������� ������������ �������� ��� ����������������� RenderDeviceImpl. ��. Texture::setDynamic
		bool Empty() const;
		void setFilteringType(FilteringType filter);
		void setAddressMode(AddressMode address);
		AddressMode getAddressMode() const;
		/// ��������� ��������
		virtual void Upload();
		/// ��������� �������� � �������� �����
		virtual void Bind(int channel = 0, int stageOp = 0);
		/// ��������� ��������
		virtual void Release();

		virtual TextureType GetTextureType() const { return VOLUME_TEXTURE; }
	};

	typedef boost::intrusive_ptr<VolumeTexture> VolumeTexturePtr;
}

#endif // __VOLUMETEXTURE_H__
