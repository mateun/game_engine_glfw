#include "stdafx.h"
#include <renderlib.h>

class MyPlayerControllerScript : public NodeComponent {
	
public:
	virtual void execute() {
		//printf("in exec. of PlayerControllerScript\n");
	}
};

class TriRenderCommand : public RenderCommand {

public:
	TriRenderCommand() {
		_shader.createProgram("simplevs.glsl", "simpleps.glsl");
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		glPointSize(40.0f);
		
	}
	virtual void execute() {
		glBindVertexArray(_vao);
		GLenum err = glGetError();
		if (err != 0) printf("gl error: %d", err);
		_shader.bindToPipeline();
		err = glGetError();
		if (err != 0) printf("gl error: %d", err);
		glDrawArrays(GL_POINTS, 0, 1);
		err = glGetError();
		if (err != 0) printf("gl error: %d", err);

	}

private:
	Shader _shader;
	GLuint _vao;
};

class GameObject : public SceneNode {

public:
	GameObject() {
		rc = std::make_shared<TriRenderCommand>();
	}
	virtual  void update(GameTime& gameTime) {
		SceneNode::update(gameTime);
		//printf("in update of GameObject\n");
	}
	virtual void render(RenderDevice& rd) {
		rd.addRenderCommand(rc);

	}

	void specialFunc() {

	}

private:
	std::shared_ptr<TriRenderCommand> rc;
	
};

int main(int argc, char** args) {
	MultiFormatImageImporter pngImporter;
	std::unique_ptr<unsigned char> pixels = pngImporter.importImage("G:/Archive/Pictures/2D/Textures/Lava_d.png");
	unsigned char * pr = pixels.get();

	GLFWDisplay display(800, 600, false);

	RenderDevice rd;
	DefaultScene scene;
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->addComponent(std::move(std::make_unique<MyPlayerControllerScript>()));
	scene.addNode(go);

	while (true) {
		go->specialFunc();
		display.pollEvents();
		scene.update();
		scene.render(rd);
		display.swapBuffers();
	}

	return 0;
}