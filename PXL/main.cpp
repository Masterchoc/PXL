#include <iostream>

#include "GL/glew.h"
#include <SDL2/SDL.h>
#include "engine.h"
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

void cb()
{
	std::cout << "hello" << std::endl;
}

int main(int argc, char* argv[]) 
{
	Engine* engine = new Engine();
	Display* window = engine->getWindow();

	SceneManager* sceneManager = engine->getSceneManager();
	ShaderManager* shaderManager = engine->getShaderManager();

	Scene* scene = sceneManager->addScene("test");

	Camera camera(glm::vec3(0.0f, 0.0f, -3.0f), 70.0f, window->getAspect(), 0.01f, 1000.0f);
	window->setCamera(&camera);

	Mesh ak("ak47", "./res/models/ak47.obj");
	Mesh monkey("monkey", "./res/models/monkey.obj");

	Texture ak_texture("./res/textures/ak47_diffuse.jpg", true);
	Texture monkey_texture("./res/textures/checker.png", true);

	Transform ak_transform(glm::vec3(-2.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	Transform monkey_transform(glm::vec3(0.0f, 0.5f, -3.0f), glm::vec3(-0.6f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	Transform plane_transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(M_PI / 2.0f, 0.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f));

	Vertex vertices[] = {
		Vertex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f))
	};

	unsigned indices[] = { 0, 1, 2, 2, 1, 3};

	Mesh plane("plane", vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));


	scene->addMesh(&ak);
	scene->addMesh(&monkey);
	scene->addMesh(&plane);

	std::cout << "Scene meshes count: " << scene->getMeshes().size() << std::endl;

	float angle = 0.0f;
	Uint32 startclock = SDL_GetTicks();
	float deltaTime = 0.0f;
	Uint32 currentFPS = 0;
	
	//engine->render(cb);

	Shader* shader = shaderManager->getShader("basic");

	while (!window->isClosed())
	{
		deltaTime = (SDL_GetTicks() - startclock) / 1000.0f;
		startclock = SDL_GetTicks();

		angle += 0.3f * deltaTime;

		//if (deltaTime != 0)
		//td::cout << deltaTime << std::endl;

		window->clear(0.15f, 0.15f, 0.15f, 1.0f);

		camera.update(deltaTime);

		shader->bind();

		ak_transform.getRotation().y = angle;
		shader->update(ak_transform, camera);
		ak_texture.bind(0);
		ak.draw();

		shader->update(monkey_transform, camera);
		monkey_texture.bind(0);
		monkey.draw();

		shader->update(plane_transform, camera);
		monkey_texture.bind(0);
		plane.draw();

		window->swapBuffers();

		SDL_Delay(1);
	}

	return 0;
}