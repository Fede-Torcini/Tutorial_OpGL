#include "Test3DCubeBatch.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <imGui/imgui.h>

namespace test {

	Test3DCubeBatch::Test3DCubeBatch()
		:m_Translation(0, 0, 0), m_Rotate(0, 0),
		m_Proj(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1000.0f, 1000.0f)), 
		//m_Proj(glm::perspective(55.0f, 1920.0f/ 1080.0f, 1.0f, 150.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(960.0f, 540.0f, 0)))
		//m_View(glm::lookAt(glm::vec3(0), glm::vec3(300.0f, 300.0f, 0), glm::vec3(0, 0, -1)))
	{
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));

		glm::vec3 center(0, 0, 0);
		float size = 200.0f;

		float positions[] =
		{
			center.x - size, center.y - size, center.z - size, 1.0f, 0.0f, 0.0f,
			center.x + size, center.y - size, center.z - size, 0.0f, 1.0f, 0.0f,
			center.x + size, center.y + size, center.z - size, 0.0f, 0.0f, 1.0f,
			center.x - size, center.y + size, center.z - size, 1.0f, 0.0f, 1.0f,

			center.x - size, center.y - size, center.z + size, 1.0f, 0.0f, 0.0f,
			center.x + size, center.y - size, center.z + size, 0.0f, 1.0f, 0.0f,
			center.x + size, center.y + size, center.z + size, 0.0f, 0.0f, 1.0f,
			center.x - size, center.y + size, center.z + size, 1.0f, 0.0f, 1.0f
		};

		unsigned int indices[] =
		{
			0, 1, 2, 2, 3, 0,
			0, 3, 7, 7, 4, 0,
			4, 5, 6, 6, 7, 4,
			5, 6, 2, 2, 1, 5,
			2, 6, 7, 7, 3, 2,
			0, 1, 5, 5, 4, 0,
		};

		//Set up OpenGL
		m_VB = std::make_unique<VertexBuffer>(positions, 8 * 6 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3);
		layout.Push(GL_FLOAT, 3);

		m_Vao = std::make_unique<VertexArray>();
		m_IB = std::make_unique<IndexBuffer>(indices, 36);
		m_Vao->AddBuffer(*m_VB, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/BasicColor.shader");
		m_Shader->Bind();
	}

	Test3DCubeBatch::~Test3DCubeBatch()
	{
		GLCall(glDisable(GL_DEPTH_TEST));
	}

	void Test3DCubeBatch::OnUpdate(float deltaTime)
	{
	}

	void Test3DCubeBatch::OnRender()
	{
		Renderer renderer;
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		//Set up mvp
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		model = glm::rotate(model, m_Rotate.y, glm::vec3(0,1,0));
		model = glm::rotate(model, m_Rotate.x, glm::vec3(1,0,0));
		glm::mat4 mvp = m_Proj * m_View * model;

		m_Shader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_Vao, *m_IB, *m_Shader);
	}
	void Test3DCubeBatch::OnImGuiRender()
	{
		ImGui::SliderFloat3("Camera", &m_Translation.x, 0.0f, 1920.0f);
		ImGui::SliderFloat2("Rotate", &m_Rotate.x, -3.14f, 3.14f);
	}
}