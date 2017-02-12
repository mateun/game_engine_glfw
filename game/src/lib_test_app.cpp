#include "stdafx.h"
#include <renderlib.h>
#include <display.h>
#include <imageimport.h>

class MyPlayerControllerScript : public NodeComponent {
	
public:
	virtual void execute() {
		printf("in exec. of PlayerControllerScript\n");
	}
};

class GameObject : public SceneNode {

public:
	GameObject() {}
	virtual  void update(GameTime& gameTime) {
		SceneNode::update(gameTime);
		printf("in update of GameObject\n");
	}
	virtual void render(RenderDevice& rd) {
		printf("render in node\n");
	}

	void specialFunc() {

	}
	
};

int main(int argc, char** args) {

	PngImporter pngImporter;
	pngImporter.importImage("G:/Archive/Pictures/2D/Textures/Lava_d.png");

	RenderDevice rd;
	DefaultScene scene;
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	printf("refcount of go: %d\n", go.use_count());
	printf("typeName of sceneNode: %s\n", go->getTypeName());
	go->addComponent(std::move(std::make_unique<MyPlayerControllerScript>()));
	scene.addNode(go);

	printf("is go empty?: %p\n", go.get());
	printf("refcount of go: %d\n", go.use_count());

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