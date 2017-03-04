#include "Asset.h"

namespace Asset
{
	// AssetData
	AssetData::AssetData()
	{
		_id = indexAsset;
		++indexAsset;
	}

	AssetData::~AssetData()
	{
		std::cout << "- Delete AssetData : " << _name << "\n";
	}

	int AssetData::getId()
	{
		return _id;
	}
	// Bitmap 
	Bitmap::Bitmap(std::string name, const char *fileName)
	{
		_name = name;
		_fileName = fileName;
		_data = al_load_bitmap(fileName);
	}
	Bitmap::~Bitmap()
	{
		al_destroy_bitmap(_data);
	}
	Draw::Bitmap* Bitmap::data()
	{
		return _data;
	}
	// Font
	Font::Font(std::string name, const char*fileName, int fontSize, int flags)
	{
		_name = name;
		_fileName = fileName;
		_data = al_load_font(fileName, fontSize, flags);
	}
	Font::~Font()
	{
		al_destroy_font(_data);
	}
	Draw::Font* Font::data()
	{
		return _data;
	}

	// Sample
	Sample::Sample(std::string name, const char*fileName)
	{
		_name = name;
		_fileName = fileName;
		_data = al_load_sample(fileName);
	}
	Sample::~Sample()
	{
		al_destroy_sample(_data);
	}
	Sound::Sample* Sample::data()
	{
		return _data;
	}

	// AssetManager
	AssetManager::AssetManager(std::string name):
		_name(name)
	{

	}

	AssetManager::~AssetManager()
	{
		if (!_mapAsset.empty())
		{
			auto it = _mapAsset.begin();

			while (it != _mapAsset.end())
			{
				if (it->second != nullptr)
				{

					delete it->second;
					it->second = nullptr;
					//it = _mapAsset.erase(it);
				}

				++it;
			}

			_mapAsset.clear();
		}

	}

	AssetManager *AssetManager::add(AssetData *content)
	{
		if (content == nullptr)
			return nullptr;

		_mapAsset.insert(std::pair<std::string, AssetData*>(content->_name, content));
		return this;
	}

	bool AssetManager::del(std::string name)
	{
		auto it = _mapAsset.find(name);

		if (it == _mapAsset.end())
		{
			std::cout << "Not found : " << name << "\n";
			return false;
		}

		if (it->second != nullptr)
		{
			delete it->second;
			it->second = nullptr;
		}

		_mapAsset.erase(it);
		//std::cout << "item found : "<< name << "\n";
		return true;

	}
	void AssetManager::showAll()
	{
		auto it = _mapAsset.begin();

		while (it != _mapAsset.end())
		{
			if ((*it).second != nullptr)
				std::cout << "[ " << it->second->_id << " = " << it->second->_name << " ]\n";

			++it;
		}
	}


}