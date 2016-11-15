#ifndef __PARTIALTEXTURE_H__
#define __PARTIALTEXTURE_H__

#pragma once

#include "Render/Texture.h"

namespace Render {

	class Sheet;

	/// ������ �������� ����������� �� ������� ����� ������ ��������.

	/// ��� ��������������, ������� �� ������ � ���� �����������, � ������������ ����� ������������� Sheet'�. ��������� � ��������������� image � ���� ��� ����� �����������, ��� ������ ��� ���.
	/// ����� �������� �������� ���������������� ����� ��������, � ��� �� ����� ������������
	/// RenderDeviceImpl::TranslateUV.
	class PartialTexture : public Texture 
	{
		friend class Render::Sheet;

	public:
		PartialTexture(Texture* texture, int x, int y, int w, int h, int ix, int iy, int fw, int fh, int aL, int texW = 0, int texH = 0);
		~PartialTexture();

		virtual DEVTEXTURE GetNativeHandle() const { return texture->_tex; }
		virtual size_t GetMemoryInUse() const { return sizeof(*this); }

		/// ��������� ����� �� ���������������� ���������� ����������. ���� ��, �� ���������� ������� TranslateUV ����� ����������.
		virtual bool needTranslate() const;
		/// ������������� ���������� ���������. ���������� � RenderDeviceImpl ���� needTranslate ���������� true.
		virtual void TranslateUV(FPoint &uv) const;
		/// ������������� ���������� ���������. ���������� � RenderDeviceImpl ���� needTranslate ���������� true.
		virtual void TranslateUV(FRect &rect, FRect &uv) const;
		virtual void TranslateUV(math::Vector3& v0, math::Vector3& v1, math::Vector3& v2, math::Vector3& v3, FRect &uv) const;

		/// ��������� ��������
		virtual void Bind(int channel = 0, int stageOp = 0);
		/// ��������� �����-����� ��������
		virtual void BindAlpha();

		virtual bool isPixelTransparent(int x, int y) const;
	
		virtual TextureType GetTextureType() const { return PARTIAL_TEXTURE; }
	
		Render::Texture* GetBaseTexture() const { return texture.get(); }

		// ��������������� ������� �������� ������
		//
		void Load(ResourceLoadMode load_mode);
		void Unload(ResourceLoadMode load_mode);
		void GroupLoad(ResourceLoadManager& glm);
		void GroupUnload(ResourceLoadManager& glm);
	
	protected:
		virtual void LoadFromFile(const std::string& filename) { }
		virtual void LoadFromImage(const Image& image) { }
		virtual void GetPropertiesFromFile(const std::string& filename) { }

		/// ��������� ��������
		virtual void Release();

	protected:
		/// �������� ������
		TexturePtr texture;
		/// ��������� � ������� ��������
		int16_t baseX, baseY, width, height, innerX, innerY, frameWidth, frameHeight, texW, texH;
		int16_t alphaLimit;
	};

	typedef boost::intrusive_ptr<PartialTexture> PartialTexturePtr;

} // namespace Render

#endif // __PARTIALTEXTURE_H__
