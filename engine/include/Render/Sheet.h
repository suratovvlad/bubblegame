#ifndef __SHEET_H__
#define __SHEET_H__

#pragma once

#include "Render/PartialTexture.h"
#include "Render/Sprite.h"
#include "Core/Resource.h"

#ifdef ENGINE_TARGET_IPHONE
#include <strings.h>
#endif

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_array.hpp>

namespace Render {

	/// ����� ������������ ������ �������
	/// ��� ����� "��������" - �������, �������� �� ���������� �������.
	/// � ������ �������� ���������� �������� ������, � ���������� ��������� �������������,
	/// ������� ����� �������������� �� �������� ��������
	class Sheet : public Resource {
	public:
		/// �������� �������� �� ��������
		struct SheetItem {
			int x, y, width, height, innerX, innerY, frameWidth, frameHeight, alphaLimit;
			float prescale_x, prescale_y;
            SpritePtr sprite;
		};

		/// ��������� �������� �� xml
		static Sheet* CreateFromXml(rapidxml::xml_node<>* elem);
		
		/// ������ �������� ��������
		static Sheet* LoadSheet(const std::string& xml, const std::string& filename, const std::string& group = "", EnginePixelType pixelType = EnginePixelType::Default, bool useDithering = true, int alphaLimit = 0);

		/// ���������� ��� �������
		const std::string& GetName() const { return path; }

		size_t GetMemoryInUse() const;

		void Load(ResourceLoadMode load_mode);
		void Unload(ResourceLoadMode load_mode);
		void GroupLoad(ResourceLoadManager& glm);
		void GroupUnload(ResourceLoadManager& glm);
		
		/// �������� �� ������������� �������� � ��������� ������ �����
		/// (�������� ����� ������ ��������� ���������, �.�. � ����, �� ���������� �� �����������)
		bool TextureExists(const std::string& filename) const;
        
        bool SpriteExists(const std::string& filename) const;

		/// ��������� ��������� � ��������� �������� � ������.
		/// ���� ������� �� ������, ���������� false.
		bool GetSheetItem(const std::string& filename, SheetItem& item) const;
		
		/// ��������� �������������� �� ��������� �����. �� ������ ������ ���� ����������� ��������
		/// ������� ����� �������� (��. CheckTexture). ���� ����� �������� ���, ������������ NULL.
		/// � ���������� �������� ����� ��������� Render::PartialTexture,
		/// ��� _����� ������� ��������������_.
		Texture* CreateTexture(const std::string& filename) const;
        
        Sprite* CreateSprite(const std::string& filename) const;
		
		/// ��������� �������������� �� ��������� ������.
		/// ���� �������� � ����� ������� ��� (����� ������ ���� ����� GetSize()), ������������ NULL.
		/// � ���������� �������� ����� ��������� Render::PartialTexture,
		/// ��� _����� ������� ��������������_.
		Texture* CreateTexture(int i) const;
		
		/// ���������� ���������� �������, ������ ������� �������� �� �����
		Texture* GetCachedTexture(int i) const;
		
		/// ���������� ���������� �������, ����������� � ��������
		int GetCount() const { return items.size(); }
		
		/// ���������� �������� ��������
		Texture * GetSheetTexture() const { return tex.get(); }

	private:
		/// ����������� ��������, ��� ��������� ������ ������ ����� getFromXml.
		Sheet();

		/// ��������� xml ����, ����������� ������������ � �� ��������
		void ProcessXml(const std::string& xmlFile);

	private:		
		typedef std::map<std::string, SheetItem> SheetItems;

		SheetItems items;

		/// �������� ��������
		TexturePtr tex;
		
		typedef std::vector<TexturePtr> Textures;

		mutable Textures _cachedTextures;
			// ������ �������������� �������

		/// ���� � ���������
		std::string path;
		
		/// ������ � ������ ������
		int allW, allH;

		float _prescale_x, _prescale_y;

	private:
		Texture* CreateTexture(const SheetItem& it) const;
	};

	typedef boost::intrusive_ptr<Sheet> SheetPtr;
}

#endif // __SHEET_H__
