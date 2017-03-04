#ifndef ASSET_H
#define ASSET_H


#include <unordered_map>

#include "IContainer.h"
#include "IPlayable.h"
#include "Draw.h"
#include "Sound.h"

#define MAKE_ASSET(name) (new Asset::AssetManager(name))

#define GET_FONT(x) get<Asset::Font>(x)->_data
#define GET_BITMAP(x) get<Asset::Bitmap>(x)->_data
#define GET_SAMPLE(x) get<Asset::Sample>(x)->_data

namespace Asset
{
    static size_t indexAsset = 0;

    struct AssetData
    {
        int _id = 0;
        std::string _name = "";
        const char* _fileName = "";

		AssetData();
		~AssetData();
		int getId();
    };

    using MapAsset = std::unordered_map<std::string, AssetData*>;

    struct Bitmap : public AssetData
    {
        Draw::Bitmap* _data = nullptr;

		Bitmap(std::string name, const char *fileName);
		~Bitmap();
		Draw::Bitmap *data();
    };

    struct Font : public AssetData
    {
        Draw::Font* _data = nullptr;

		Font(std::string name, const char*fileName, int fontSize, int flags);
		~Font();
		Draw::Font* data();
    };

    struct Sample : public AssetData
    {
        Sound::Sample* _data = nullptr;

		Sample(std::string name, const char*fileName);
		~Sample();
		Sound::Sample* data();
    };

    struct AssetManager
    {
        std::string _name;
        MapAsset _mapAsset;

		AssetManager(std::string name = "");
		~AssetManager();

		AssetManager *add(AssetData *content);

		bool del(std::string name);
		void showAll();

		template <class C>
		C *get(std::string name)
		{
			auto it = _mapAsset.find(name);

			if (it != _mapAsset.end())
				return static_cast<C*>(it->second);

			return nullptr;
		}
    };

}



#endif // ASSET_H
