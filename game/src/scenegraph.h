#pragma once
#include <vector>

class GameObject;

class Scenegraph {

public:
	virtual void addGameObject(GameObject* gameObject) = 0;
	virtual void removeGameObject(GameObject* gameObject) = 0;

	virtual void renderScene() = 0;


};

class SimpleSceneGraph : public Scenegraph {

public:
	virtual void addGameObject(GameObject* gameObject) override;
	virtual void removeGameObject(GameObject* gameObject) override;

	virtual void renderScene() override;


private:
	std::vector<GameObject*> _gameObjectList;

	
};