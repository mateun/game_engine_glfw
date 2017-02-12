#include "stdafx.h"
#include "scenenode.h"
#include "nodecomponent.h"

SceneNode::SceneNode() {

}

void SceneNode::addComponent(std::unique_ptr<NodeComponent> component) {
	_components.push_back(std::move(component));
}

void SceneNode::removeComponent(const std::string& id) {
	// TODO implement
	throw std::runtime_error("removeComponent: NOT YET IMPLEMENTED");
}

void SceneNode::update(GameTime& gameTime) {
	for (const auto& c : _components) {
		c.get()->execute();
	}
}

NodeComponent& SceneNode::getComponent(const std::string& id) {
	// TODO implement
	throw std::runtime_error("getComponent: NOT YET IMPLEMENTED");
}