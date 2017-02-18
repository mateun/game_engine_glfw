#include "stdafx.h"
#include <renderlib.h>
#include <display.h>
#include <imageimport.h>

class MyPlayerControllerScript : public NodeComponent {
	
public:
	virtual void execute() {
		//printf("in exec. of PlayerControllerScript\n");
	}
};

class GameObject : public SceneNode {

public:
	GameObject() {}
	virtual  void update(GameTime& gameTime) {
		SceneNode::update(gameTime);
		//printf("in update of GameObject\n");
	}
	virtual void render(RenderDevice& rd) {
		//printf("render in node\n");
	}

	void specialFunc() {

	}
	
};

int main(int argc, char** args) {
	MultiFormatImageImporter pngImporter;
	std::unique_ptr<unsigned char> pixels = pngImporter.importImage("G:/Archive/Pictures/2D/Textures/Lava_d.png");
	unsigned char * pr = pixels.get();

	RenderDevice rd;
	DefaultScene scene;
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->addComponent(std::move(std::make_unique<MyPlayerControllerScript>()));
	scene.addNode(go);

	GLFWDisplay display(800, 600, false);

	while (true) {
		go->specialFunc();
		display.pollEvents();
		scene.update();
		scene.render(rd);
		display.swapBuffers();
	}

	return 0;
}