#pragma once
#include "renderlib_api.h"
#include "reflectionmacros.h"
#include <memory>
#include <string>
#include <vector>


class Scene;
class NodeComponent;
class RenderDevice;
class GameTime;



/**
	\class	SceneNode
	\brief	A SceneNode is the main building block of a scene
			and represents the "game objects" of a game. 
			Each SceneNode has a location and rotation in the world,
			and can update and render itself during a frame of execution.


	SceneNodes follow a modular approach in that most of its functionality is
	implemented through NodeComponents. A NodeComponent can extend the functionality
	of a SceneNode in arbitrary ways, as its "execute" method is called once per frame, 
	when the update method is called. 
	
	Please note, that through NodeComponents it is not possible to influence the way an object is
	rendered. Possibly, this constraint will be lifted in the future.
 */
class  SceneNode {

	REFLECTION_CODE(SceneNode)

public:
	RENDERLIB_API SceneNode();
	SceneNode(const SceneNode& other) = delete;
	SceneNode& operator=(const SceneNode& other) = delete;
	RENDERLIB_API virtual void addComponent(std::unique_ptr<NodeComponent> component);
	RENDERLIB_API virtual void removeComponent(const std::string& componentId);
	RENDERLIB_API virtual void update(GameTime& gameTime);
	RENDERLIB_API virtual void render(RenderDevice& renderDevice) = 0;
	RENDERLIB_API virtual NodeComponent& getComponent(const std::string& componentId);	///< Queries the node for a component with the given id
	
private:
	std::vector<std::unique_ptr<NodeComponent>> _components;
};

