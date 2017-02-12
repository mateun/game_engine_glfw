#include "renderlib_api.h"
#include <vector>

class RenderCommand;

/**
	\class	RenderDevice
	\brief	This class takes care of the low level rendering
			functionality. 

	This class is responsible for rendering the submitted RenderCommands
	as quickly as possible. 
	During a frame, RenderCommand objects are added to the RenderDevice. 
	When the command "render" is given, the device
	should do optimizations such as sorting by shaders, textures etc. 

*/
class RenderDevice {

public:
	RENDERLIB_API virtual void addRenderCommand(const RenderCommand renderCommand);	///< Adds a new RenderCommand to be drawn with the next render call
	RENDERLIB_API virtual void deleteCommandBuffer();		///< Delete the contents of the command buffer completely
	RENDERLIB_API virtual void render();	///< Renders all commands to the backbuffer

protected:
	RENDERLIB_API virtual void clearBackBuffer();
	std::vector<RenderCommand> _renderCommands;
};