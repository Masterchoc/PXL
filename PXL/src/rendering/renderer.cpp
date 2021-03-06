#include "renderer.h"

Renderer::Renderer(Display* window, Loader* loader, ShaderManager* shaderManager, AssetManager* assetManager, GuiManager* guiManager)
{
	m_window = window;
	m_loader = loader;

	m_entityRenderer = new EntityRenderer(shaderManager);
	m_skyboxRenderer = new SkyboxRenderer(m_loader, shaderManager);
	m_guiRenderer = new GuiRenderer(guiManager, window);

	glEnable(GL_MULTISAMPLE);
}

void Renderer::clear(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::render(Scene* scene, double delta)
{
	glViewport(0, 0, (GLsizei)m_window->getSize().x, (GLsizei)m_window->getSize().y);

	if (m_viewport != nullptr) 
	{
		glEnable(GL_SCISSOR_TEST);

		GLsizei w = (GLsizei)m_viewport->getLayout()->getComputedSize().x;
		GLsizei h = (GLsizei)(m_viewport->getLayout()->getComputedSize().y);
		GLint x = 0;
		GLint y = -30;

		glScissor(x, (GLint)((m_window->getSize().y - h) + y), w, h);

		m_skyboxRenderer->render(scene, delta);
		m_entityRenderer->render(scene, delta);

		glDisable(GL_SCISSOR_TEST);
	}	

	m_guiRenderer->render(scene, delta);
}

Renderer::~Renderer()
{
	delete m_entityRenderer;
	delete m_skyboxRenderer;
	delete m_guiRenderer;
}
