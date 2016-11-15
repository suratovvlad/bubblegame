#ifndef _RENDER_ITEXTURETYPE_H_
#define _RENDER_ITEXTURETYPE_H_

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

namespace Render {

class ITextureType
{
public:

	enum TextureType {
		SIMPLE_TEXTURE = 0, COMBINED_TEXTURE, PARTIAL_TEXTURE, CUBE_TEXTURE, VOLUME_TEXTURE
	};

	virtual TextureType GetTextureType() const = 0;

};

}

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif // _RENDER_ITEXTURETYPE_H_
