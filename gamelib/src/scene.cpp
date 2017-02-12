#include "stdafx.h"
#include "scene.h"
#include "scenenode.h"
#include "nodecomponent.h"
#include "renderdevice.h"

Scene::~Scene() {}

DefaultScene::~DefaultScene() {

}

void DefaultScene::addNode(std::shared_ptr<SceneNode> node) {
	_nodes.push_back(node);
}

void DefaultScene::removeNode(const std::string& id) {
	// TODO implement find by id
	// remove then from _nodes
	throw std::runtime_error("-- removeNode -- NOT implemented yet!");
}

void DefaultScene::update() {
	for (const auto& n : _nodes) {
		n.get()->update(_gameTime);
	}
}

void DefaultScene::render(RenderDevice& renderDevice) {
	for (const auto& n : _nodes) {
		n.get()->render(renderDevice);
	}
	renderDevice.render();
}

