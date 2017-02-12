#include "renderlib_api.h"
#include <memory>

class SceneNode;

/**
	\class	NodeComponent
	\brief	A NodeComponent is a modular building block of SceneNodes.
			It has an execute method which can run arbitrary logic. 
			As of now, there is no option to render from a component. 
*/
class  NodeComponent {

public:
	#ifdef _WIN32
	RENDERLIB_API 
	#endif 
	virtual void execute() = 0;				///< This method is called each frame when the owning SceneNodes update method is run
	#ifdef _WIN32 
	RENDERLIB_API 
	#endif 
	virtual std::shared_ptr<SceneNode> getSceneNode();	///< Get the parent SceneNode reference of this component

private:
	std::shared_ptr<SceneNode> _parentNode;
};
