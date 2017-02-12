#include "stdafx.h"
#include "nodecomponent.h"

std::shared_ptr<SceneNode> NodeComponent::getSceneNode() {
	return _parentNode;
}
