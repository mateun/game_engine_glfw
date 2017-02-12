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
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	SceneNode();
	SceneNode(const SceneNode& other) = delete;
	SceneNode& operator=(const SceneNode& other) = delete;
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual void addComponent(std::unique_ptr<NodeComponent> component);
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual void removeComponent(const std::string& componentId);
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual void update(GameTime& gameTime);
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual void render(RenderDevice& renderDevice) = 0;
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual NodeComponent& getComponent(const std::string& componentId);	///< Queries the node for a component with the given id
	
private:
	std::vector<std::unique_ptr<NodeComponent>> _components;
};

