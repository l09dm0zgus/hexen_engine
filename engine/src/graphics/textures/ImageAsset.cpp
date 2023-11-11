//
// Created by cx9ps3 on 09.11.2023.
//

#include "ImageAsset.hpp"
#include <SDL_image.h>
#include <fstream>

void hexen::engine::graphics::ImageAsset::save(const std::filesystem::path &pathToAsset, const std::filesystem::path &pathToRawFile)
{
	HEXEN_ADD_TO_PROFILE();
	surface = IMG_Load(pathToRawFile.string().c_str());

	if (surface == nullptr)
	{
		SDL_Log("Error : Failed to load %s image.", pathToRawFile.string().c_str());
	}

	auto *format = surface->format;

	constexpr core::u8 eightBitsPerPixel = 8;
	constexpr core::u8 sixteenBitsPerPixel = 16;
	constexpr core::u8 thirtyTwoBitsPerPixel = 32;

	switch (format->BitsPerPixel)
	{
		case eightBitsPerPixel:
			assetDataFile["image_asset"]["format"] = format->Amask ? ImageFormat::RGBA8 : ImageFormat::RGB8;
			break;
		case sixteenBitsPerPixel:
			assetDataFile["image_asset"]["format"] = format->Amask ? ImageFormat::RGBA16 : ImageFormat::RGB16;
			break;
		case thirtyTwoBitsPerPixel:
			assetDataFile["image_asset"]["format"] = format->Amask ? ImageFormat::RGBA32 : ImageFormat::RGB32;
			break;
		default:
			assetDataFile["image_asset"]["format"] = format->Amask ? ImageFormat::RGBA8 : ImageFormat::RGB8;
			break;
	}

	height = surface->h;
	width = surface->w;
	pitch = surface->pitch;
	pixels = surface->pixels;

	std::vector<core::u8> const pixelsBuffer(static_cast<char*>(pixels), static_cast<char*>(pixels) + pitch * height);

	assetDataFile["image_asset"]["pitch"] = pitch;
	assetDataFile["image_asset"]["size"]["width"] = width;
	assetDataFile["image_asset"]["size"]["height"] = height;
	assetDataFile["image_asset"]["name"] = pathToRawFile.filename();
	assetDataFile["image_asset"]["raw_data"] = pixelsBuffer;

	auto binaryJsonData = nlohmann::json::to_bson(assetDataFile);
	std::ofstream outFile(pathToAsset, std::ios::binary);

	outFile.write((char *) binaryJsonData.data(), binaryJsonData.size() * sizeof(core::u8));

}

hexen::engine::core::vptr hexen::engine::graphics::ImageAsset::getRawData() const
{
	HEXEN_ADD_TO_PROFILE();
	return pixels;
}

hexen::engine::core::i32 hexen::engine::graphics::ImageAsset::getHeight() const
{
	HEXEN_ADD_TO_PROFILE();
	return assetDataFile["image_asset"]["size"]["height"];
}

hexen::engine::core::i32 hexen::engine::graphics::ImageAsset::getWidth() const
{
	HEXEN_ADD_TO_PROFILE();
	return assetDataFile["image_asset"]["size"]["width"];
}
std::string hexen::engine::graphics::ImageAsset::getName() const
{
	HEXEN_ADD_TO_PROFILE();
	return assetDataFile["image_asset"]["name"];
}

void hexen::engine::graphics::ImageAsset::load(const std::filesystem::path &pathToAsset)
{
	HEXEN_ADD_TO_PROFILE();
	std::ifstream const inFile(pathToAsset, std::ios::binary);
	std::stringstream ss;
	ss << inFile.rdbuf();

	assetDataFile = nlohmann::json::from_bson(ss);

	std::vector<core::u8> imagePixels = assetDataFile["image_asset"]["raw_data"];
	std::memcpy(pixels, imagePixels.data(), imagePixels.size());

	height = getHeight();
	width = getWidth();

	pitch = assetDataFile["image_asset"]["pitch"];
}

hexen::engine::graphics::ImageAsset::ImageFormat hexen::engine::graphics::ImageAsset::getFormat() const
{
	HEXEN_ADD_TO_PROFILE();
	return static_cast<ImageFormat>(assetDataFile["image_asset"]["format"]);
}

void hexen::engine::graphics::ImageAsset::flip()
{
	HEXEN_ADD_TO_PROFILE();
	char* temp = new char[pitch]; // intermediate buffer
	char* pixelsBuffer = (char*) pixels;

	for(int i = 0; i < height / 2; ++i)
	{
		// get pointers to the two rows to swap
		char* row1 = pixelsBuffer + i * pitch;
		char* row2 = pixelsBuffer + (height - i - 1) * pitch;

		// swap rows
		memcpy(temp, row1, pitch);
		memcpy(row1, row2, pitch);
		memcpy(row2, temp, pitch);
	}

	pixels = pixelsBuffer;

	delete[] temp;

}

hexen::engine::graphics::ImageAsset::~ImageAsset()
{
	if(surface != nullptr)
	{
		SDL_DestroySurface(surface);
	}
}