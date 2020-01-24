#pragma once

#include <string>
#include <memory>
#include <unordered_map>

class Texture;
class Shader;

template <typename T>
class ResourceManager
{
public:
	static void add(const std::string& key, const T& value)
	{
		ResourceManager<T>::storage.insert({ key, value });
	}

	static const T& get(const std::string& key)
	{
		return storage[key];
	}
private:
	static std::unordered_map<std::string, T> storage;
};

template <typename T>
std::unordered_map<std::string, T> ResourceManager<T>::storage;

using TextureManager = ResourceManager<std::shared_ptr<Texture>>;
using ShaderManager = ResourceManager<std::shared_ptr<Shader>>;
