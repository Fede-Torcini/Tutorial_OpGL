#include "TestTwoSnails.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <imGui/imgui.h>

namespace test {

	TestTwoSnails::TestTwoSnails()
		:m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0),
		m_Proj(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)), 
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		float positions[] =
		{
			-270.0f, -270.0f,  0.0f,  0.0f,
			 270.0f, -270.0f,  1.0f,  0.0f,
			 270.0f,  270.0f,  1.0f,  1.0f,
			-270.0f,  270.0f,  0.0f,  1.0f
		};

		unsigned int indices[] =
		{
			0,1,2,
			2,3,0
		};

		//Set up OpenGL
		m_VB = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2);
		layout.Push(GL_FLOAT, 2);

		m_Vao = std::make_unique<VertexArray>();
		m_IB = std::make_unique<IndexBuffer>(indices, 6);
		m_Vao->AddBuffer(*m_VB, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>("res/textures/snail.png");
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTwoSnails::~TestTwoSnails()
	{
		GLCall(glDisable(GL_BLEND));
	}

	void TestTwoSnails::OnUpdate(float deltaTime)
	{
	}

	void TestTwoSnails::OnRender()
	{
		Renderer renderer;

		m_Texture->Bind();

		//Set up mvp
		//Draw first snail
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_Vao, *m_IB, *m_Shader);

		//Draw second snail
		model = glm::translate(glm::mat4(1.0f), m_TranslationB);
		mvp = m_Proj * m_View * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_Vao, *m_IB, *m_Shader);
	}
	void TestTwoSnails::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 1920.0f);
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 1920.0f);
	}
}