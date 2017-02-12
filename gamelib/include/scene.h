#pragma once
#include "renderlib_api.h"
#include "gametime.h"
#include <memory>
#include <string>
#include <vector>


class SceneNode;
class RenderDevice;



/** 
 *	\class	Scene
 *	\brief	A Scene object is the heart of the rendering
 * 			in the FB renderlib. 
 *			It consists of SceneNodes which are the foundational
 *			objects to be rendered and the user interacts with.
 *
 *	Normally, only one exists at any time, though technically, as long as you 
 *  can afford it from a performance point of view, you could have multiple scenes
 *	in your program as well. 
 *
 *	Example usage of the scene:
 *	\code
	// Setup phase
	Scene scene;
	scene.addNode(playerNode);
	scene.addNode(enemy1);
	scene.addNode(enemy2);

	// in game loop
	while (gameRunning) {
		scene.update();
		scene.render(myRenderDevice);
	}

	\endcode
 */
#ifdef _WIN32
class RENDERLIB_API Scene {
#else
class Scene {
#endif

public:
	virtual ~Scene();	///< Virtual destructor to allow for specific child destructor overrides


	virtual void addNode(std::shared_ptr<SceneNode> node) = 0;	///< Adds a node to the scene graph
	virtual void removeNode(const std::string& nodeId) = 0;		///< Removes a node from the scenegraph, destroying it effectively
	virtual void update() = 0;									///< Updates the complete scene, gives all nodes a chance to update
	virtual void render(RenderDevice& renderDevice) = 0;		///< Renders the complete scene

};


/** \class	DefaultScene
	\brief	The DefaultScene is a simple Scene implementation
			based on a simple vector of SceneNodes. 
			No culling optimization is implemented. 
*/
class  DefaultScene : public Scene {
public:
	DefaultScene() {}
	DefaultScene(const DefaultScene& other) = delete;
	 DefaultScene& operator=(DefaultScene& other) = delete;
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual ~DefaultScene();
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual void addNode(std::shared_ptr<SceneNode> node) override;
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual void removeNode(const std::string& nodeId) override;
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual void update() override;
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual void render(RenderDevice& renderDevice) override;

private:
	std::vector<std::shared_ptr<SceneNode>> _nodes;
	
	GameTime _gameTime;
};
