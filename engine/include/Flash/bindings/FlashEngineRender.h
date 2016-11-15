#pragma once

#include <boost/intrusive_ptr.hpp>

#include <Render/RenderDevice.h>
#include <Render/SpriteBatch.h>
#include <Render/Texture.h>
#include <Render/VertexBufferBuilder.h>
#include <FreeType/bindings/FreeTypeEngineBinding.h>

#include "Flash/core/Render/FlashRender.h"

namespace Flash {
	bool isTextSnapped();
}

class FlashEngineRenderDevice: public IDeviceRender
{
public:
	FlashEngineRenderDevice();

	void setShader(FlashRender* render, FlashConstantId id, FlashShader shader);
	void setConstantEnum(FlashRender* render, FlashConstantId id, FlashEnum x);

	void setConstantFloat(FlashRender* render, FlashConstantId id, float x);
	void setConstantVector(FlashRender* render, FlashConstantId id, float* v);
	void setConstantMatrix3x2(FlashRender* render, FlashConstantId id, float* m);
	void setConstantMatrix4x4(FlashRender* render, FlashConstantId id, float* m);

	void setTexture(FlashRender* render, FlashConstantId id, void* _texture);

	freetype::Text* getText(TextObjectOutputParams& _params);
	void DrawFreeTypeText(TextObjectOutputParams& _params);
	void Draw(const math::Vector3& vec1, const math::Vector3& vec2, const math::Vector3& vec3, const math::Vector3& vec4, Color color, const FRect& uv);
	void Flush();
	void Begin();
	void End();

	void beginClipPlane(float x1, float y1, float x2, float y2);
	void endClipPlane();
	void updateClipPlanes();

	void beginScissorTest(const IRect& rect, ClippingMode clippingMode);
	void endScissorTest();

private:
	struct ClipPlane
	{
		float x1, y1, x2, y2;

		ClipPlane(float x1, float y1, float x2, float y2){
			this->x1 = x1;
			this->y1 = y1;
			this->x2 = x2;
			this->y2 = y2;
		}
	};

private:
	boost::intrusive_ptr<Render::SpriteBatch> __spriteBatch;
	Render::Texture* __spriteBatchTexture;
	uint16_t __spriteBatchStarted;

	std::vector<ClipPlane> clipPlanes;
	std::vector<ClipPlane> usedClipPlanes;
};