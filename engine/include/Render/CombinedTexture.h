#ifndef _RENDER_COMBINEDTEXTURE_H_
#define _RENDER_COMBINEDTEXTURE_H_

#include "Render/Texture.h"

namespace Render {

class CombinedTexture : public Texture
{
	public:
		CombinedTexture()
			: _tex_a(0)
			, _tex_b(0)
		{}
		
		virtual size_t GetMemoryInUse() const;
		
		/// Забиндить текстуру. Параметры должны быть по-умолчанию, иначе ошибка.
		virtual void Bind(int channel = 0, int stageOp = 0);
		/// Забиндить альфа-канал текстуры
		virtual void BindAlpha();
		
		virtual bool isPixelTransparent(int x, int y) const;
		
		virtual TextureType GetTextureType() const { return COMBINED_TEXTURE; }

	protected:
		/// Загрузить текстуру
		virtual void Upload(bool bCleanAfterUpload = true);
		/// Выгрузить текстуру
		virtual void Release();

		virtual void Purge();
		
		virtual void LoadFromFile(const std::string& filename = std::string());
		virtual void LoadFromImage(const Image& image_) { Assert(false); }

	protected:
		// inherited DEVTEXTURE _tex; ///< внутренний ID текстуры в видеопамяти.
		// _tex обычно равен _tex_a, но иногда может подменяться на _tex_b (например, при BindAlpha).
		DEVTEXTURE _tex_a; ///< внутренний ID первой текстуры в видеопамяти.
		DEVTEXTURE _tex_b; ///< внутренний ID второй текстуры в видеопамяти.

		// inherited Image image;
		Image image_b;
};
	
} // namespace Render

#endif // _RENDER_COMBINEDTEXTURE_H_
