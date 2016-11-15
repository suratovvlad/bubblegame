#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#pragma once

#include "Render/Texture.h"

#ifndef MAKEFOURCC
    #define MAKEFOURCC(ch0, ch1, ch2, ch3) \
                ((uint32_t)(uint8_t)(ch0) | ((uint32_t)(uint8_t)(ch1) << 8) | \
                ((uint32_t)(uint8_t)(ch2) << 16) | ((uint32_t)(uint8_t)(ch3) << 24 ))
#endif /* defined(MAKEFOURCC) */

#define FOURCC_DXT1 MAKEFOURCC('D', 'X', 'T', '1')
#define FOURCC_DXT3 MAKEFOURCC('D', 'X', 'T', '3')
#define FOURCC_DXT5 MAKEFOURCC('D', 'X', 'T', '5')
#define FOURCC_ETC1 MAKEFOURCC('E', 'T', 'C', '0')

namespace Render {

enum ImageType {
	IT_NONE = 0,
	IT_PNG = 1 << 0,
	IT_JPG = 1 << 1,
	IT_WEBP = 1 << 2,
	IT_PVRTC = 1 << 3,
	IT_DDS = 1 << 4
};

class ImageLoader
{
public:
	ImageLoader(Render::Image* image, const std::string& filename);
	
	void Load();
	
	static void LoadJPG(Image* image, const std::string& file, GfxFileInfo *info = 0);
	static void LoadPNG(Image* image, const std::string& file, GfxFileInfo *info = 0);
	static void LoadWEBP(Image* image, const std::string& file, GfxFileInfo *info = 0);
	static void LoadPVRTC(Image* image, const std::string& file, GfxFileInfo *info = 0);
	static void LoadDDS(Image* image, const std::string& file, GfxFileInfo *info = 0);
	
	static void LoadJPGWithMask(Image* image, const std::string& file, const std::string& file_a);
	
	static ImageType SelectImageType(std::string &file, std::string &file_a);

private:
	friend class Render::Image;
	
	Image* _image;
	std::string _filename;
	IO::InputStreamPtr _stream;

	static void LoadJpgHelper(Image* image, const std::string& file, GfxFileInfo *info = NULL);
};

class ResizeToPowerOfTwo
{
public:
	void apply(Image *image);
};

class AddAlphaFromImage
{
	Image *_alpha_source;
public:
	AddAlphaFromImage(Image* alpha_source);
	
	void apply(Image *image);
};

} // namespace Render

bool SaveImageAsJpeg(Render::Image* image, const std::string &path, int quality);
bool SaveImageAsPng(Render::Image* image, const std::string &path);
bool SaveImageAsBmp(Render::Image* image, const std::string &path);

#endif // #ifndef _IMAGELOADER_H_
