#include <Engine/Graphics/Renderer/Batch.hpp>

#include <Engine/Graphics/Renderer/Renderable.hpp>
#include <Engine/Graphics/Buffers/Buffers.hpp>
#include <Engine/Graphics/Shader.hpp>
#include <Engine/Graphics/Texture.hpp>
#include <Engine/Graphics/View.hpp>

struct VertexData
{
	glm::vec2 pos;
	glm::vec2 uv;
	glm::vec4 color;
};

Batch::Batch(const std::string& name, const std::shared_ptr<View>& view) :
	name(name),
	vao(nullptr),
	shader(nullptr),
	texture(nullptr),
	view(view),
	dirty(true)
{
}

void Batch::submit(const std::shared_ptr<Renderable>& renderable)
{
	renderables.push_back(renderable);
	dirty = true;
}

void Batch::begin()
{
	if (dirty)
	{
		updateVAO();
		dirty = false;
		std::cout << "Batch (" << name << ") renderables count : " << renderables.size() << std::endl;
	}

	shader->bind();
	texture->bind();
	shader->setMat4("u_view", view->getMatrix());
	shader->setInt("u_texture", 0);
	vao->bind();
}

void Batch::render()
{
	glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
}

void Batch::end()
{
	vao->unbind();
	texture->unbind();
	shader->unbind();
}

void Batch::clear()
{
	renderables.erase(renderables.begin(), renderables.end());
}

void Batch::setShader(const std::shared_ptr<Shader>& value)
{
	shader = value;
}

const std::shared_ptr<Shader>& Batch::getShader() const
{
	return shader;
}

void Batch::setTexture(const std::shared_ptr<Texture>& value)
{
	texture = value;
}
const std::shared_ptr<Texture>& Batch::getTexture() const
{
	return texture;
}

void Batch::updateVAO()
{
	int count = renderables.size();

	std::vector<unsigned int> indices;
	std::vector<VertexData> vertices;

	indices.resize(count * 6);
	vertices.resize(count * 4);

	int ii = 0; // indices index
	int iv = 0; // vertices index
	for (auto renderable : renderables)
	{
		// индексы
		{
			indices[(ii * 6) + 0] = (ii * 4) + 0;
			indices[(ii * 6) + 1] = (ii * 4) + 1;
			indices[(ii * 6) + 2] = (ii * 4) + 2;

			indices[(ii * 6) + 3] = (ii * 4) + 0;
			indices[(ii * 6) + 4] = (ii * 4) + 3;
			indices[(ii * 6) + 5] = (ii * 4) + 2;

			ii++;
		}

		// вершины
		{
			{
				glm::mat4 transform = renderable->getTransform();
				vertices[iv + 0].pos = glm::vec2(transform * glm::vec4(-0.5f, -0.5f, 0.f, 1.f));
				vertices[iv + 1].pos = glm::vec2(transform * glm::vec4(-0.5f, 0.5f, 0.f, 1.f));
				vertices[iv + 2].pos = glm::vec2(transform * glm::vec4(0.5f, 0.5f, 0.f, 1.f));
				vertices[iv + 3].pos = glm::vec2(transform * glm::vec4(0.5f, -0.5f, 0.f, 1.f));
			}

			{
				const std::vector<glm::vec2>& uv = renderable->getUV();
				vertices[iv + 0].uv = uv[0];
				vertices[iv + 1].uv = uv[1];
				vertices[iv + 2].uv = uv[2];
				vertices[iv + 3].uv = uv[3];
			}

			{
				glm::vec4 color = renderable->getColor();
				vertices[iv + 0].color = color;
				vertices[iv + 1].color = color;
				vertices[iv + 2].color = color;
				vertices[iv + 3].color = color;
			}

			iv += 4;
		}
	}

	std::shared_ptr<IndexBuffer> ibo;
	ibo = std::make_shared<IndexBuffer>(indices.data(), indices.size());

	std::shared_ptr<VertexBuffer> vbo;
	vbo = std::make_shared<VertexBuffer>(vertices.data(), sizeof(VertexData) * vertices.size());
	vbo->setLayout(VertexLayout({
		VertexAttribute("pos", GLDataType::Float2),
		VertexAttribute("uv", GLDataType::Float2),
		VertexAttribute("color", GLDataType::Float4),
		}));

	vao = std::make_shared<VertexArray>();

	vao->setIndexBuffer(ibo);
	vao->setVertexBuffer(vbo);
}
