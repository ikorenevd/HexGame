#include <Game/Layers/MapLayer.hpp>

#include <Engine/Core/Manager.hpp>
#include <Engine/Graphics/Texture.hpp>

#include <Game/Map/Map.hpp>
#include <Game/Map/Tile.hpp>
#include <Game/Map/TerrainType.hpp>

MapLayer::MapLayer(const std::shared_ptr<Map>& map) :
	Layer("MapLayer"),
	map(map)
{
	view = std::make_shared<View>(glm::ivec2(1280, 720));

	TextureManager::add("orange", std::make_shared<Texture>("Assets\\Textures\\orange.png", ColorModel::RGBA));
	TextureManager::add("blue", std::make_shared<Texture>("Assets\\Textures\\blue.png", ColorModel::RGBA));
	TextureManager::add("grey", std::make_shared<Texture>("Assets\\Textures\\grey.png", ColorModel::RGBA));

	float vertices[] =
	{
		0.5f,  0.5f, 1.f, 1.f,
		0.5f, -0.5f, 1.f, 0.f,
		-0.5f, -0.5f, 0.f,0.f,
		-0.5f,  0.5f, 0.f, 1.f
	};

	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	vao = std::make_shared<VertexArray>();

	std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
	vbo->setLayout(VertexLayout({
		VertexAttribute("position", GLDataType::Float2),
		VertexAttribute("1", GLDataType::Float2)
	}));

	std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(indices, 6);

	vao->setIndexBuffer(ibo);
	vao->setVertexBuffer(vbo);

	ShaderManager::add("Texture", std::make_shared<Shader>("Assets\\Shaders\\TextureVert.glsl", "Assets\\Shaders\\TextureFrag.glsl"));
}

void MapLayer::update()
{
	if (Keyboard::isKeyPressed(GLFW_KEY_W))
		speed += 1.f;

	if (Keyboard::isKeyPressed(GLFW_KEY_S))
		speed -= 1.f;

	if (Keyboard::getKeyState(GLFW_KEY_UP))
		view->move({ 0.f, speed });

	if (Keyboard::getKeyState(GLFW_KEY_DOWN))
		view->move({ 0.f, -speed });

	if (Keyboard::getKeyState(GLFW_KEY_LEFT))
		view->move({ -speed, 0.f });

	if (Keyboard::getKeyState(GLFW_KEY_RIGHT))
		view->move({ speed, 0.f });
}

void MapLayer::render()
{
	auto shader = ShaderManager::get("Texture");
	shader->bind();
	shader->setInt("ourTexture", 0);
	shader->setMat4("view", view->getMatrix());
	vao->bind();

	auto size = map->getSize();
	for (int x = 0; x < size.x; x++)
		for (int y = 0; y < size.y; y++)
		{
			TerrainType type = map->getTile(glm::ivec3(x, y, -x-y))->getTerrainType();

			switch (type)
			{
			case TerrainType::Flatland:
				TextureManager::get("blue")->bind();
				break;
			case TerrainType::Hill:
				TextureManager::get("orange")->bind();
				break;
			case TerrainType::Mountain:
				TextureManager::get("grey")->bind();
				break;
			}

			glm::mat4 tranform = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0.f));
			glm::mat4 transform = glm::scale(glm::mat4(1.f), glm::vec3(100, 100, 1.f)) * glm::translate(glm::mat4(1.f), glm::vec3((float)(x + (float)y / 2) * 0.9f, (float)y * 0.80f, 0.f));
			shader->setMat4("transform", transform);

			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
		}
	
	vao->unbind();
	shader->unbind();
}