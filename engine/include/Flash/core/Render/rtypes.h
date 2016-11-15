#pragma once

#include <FreeType/TextStyle.h>

typedef unsigned int FlashColor;
typedef unsigned int FlashConstantId;
typedef unsigned int FlashEnum;
typedef unsigned int FlashShader;

struct TextObjectOutputParams
{
	freetype::TextStyle* textStyle;
	const char* text;
	Color color;
	float width, height;
	int textLength;
	bool snapToPixels;
	bool suggestFontsize;
	bool cacheAsBitmap;
};

struct FlashConstant
{
	union
	{
		FlashEnum f_enum;
		void* f_texture;
		FlashShader f_shader;
		float f_float;
		float f_vector[4];
		float f_matrix3x2[6];
		float f_matrix4x4[16];
	};

	enum Tag{TagNotSet, TagEnum, TagTexture, TagFloat, TagShader, TagVector, TagMatrix3x2, TagMatrix4x4};
	Tag tag;
	bool valid;
};
