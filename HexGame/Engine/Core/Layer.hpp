#pragma once

#include <string>

class Layer
{
public:
	Layer(const std::string& name) :
		name(name)
	{}

	virtual void update() {};
	virtual void render() {};

	virtual void onAttach() {};

	const std::string& getName() const
	{
		return name;
	}
private:
	std::string name;
};
