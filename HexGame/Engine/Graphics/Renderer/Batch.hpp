#pragma once

#include <string>
#include <vector>
#include <memory>

class VertexArray;
class Renderable;
class Texture;
class Shader;
class View;

class Batch
{
public:
	Batch(const std::shared_ptr<View>& view);

	void submit(const std::shared_ptr<Renderable>& renderable);

	void begin();
	void render();
	void end();

	void clear();

	void setShader(const std::shared_ptr<Shader>& value);
	const std::shared_ptr<Shader>& getShader() const;

	void setTexture(const std::shared_ptr<Texture>& value);
	const std::shared_ptr<Texture>& getTexture() const;
private:
	void updateVAO();

	std::vector<std::shared_ptr<Renderable>> renderables;

	std::shared_ptr<VertexArray> vao;

	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;

	std::shared_ptr<View> view;

	mutable bool dirty;
};
