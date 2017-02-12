#pragma once
#include <glm\vec2.hpp>
#include <glm\mat4x4.hpp>


class GameObject;


class Component {

public:
	
};

class ExecutableComponent : public Component {

public:
	virtual void execute(GameObject& parentGameObject) = 0;
};

class TransformComponent : public Component {

public:
	glm::vec3 getLocation() { return _location;  }

private: 
	glm::vec3 _location;
	
};

class MeshComponent : public Component {

public:
	
	
};

class ScriptComponent : public ExecutableComponent {
public: 

	virtual void execute(GameObject& parentGameObject) override; 
};