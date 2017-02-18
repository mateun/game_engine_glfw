#include "renderlib_api.h"
#include <vector>
#include <memory>

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
	#ifdef _WIN32 
	RENDERLIB_API
	#endif 
	RenderDevice();
	#ifdef _WIN32
	RENDERLIB_API 
	#endif
	virtual void addRenderCommand(std::unique_ptr<RenderCommand> renderCommand);	///< Adds a new RenderCommand to be drawn with the next render call
	#ifdef _WIN32
	RENDERLIB_API 
	#endif
	virtual void deleteCommandBuffer();		///< Delete the contents of the command buffer completely
	#ifdef _WIN32
	RENDERLIB_API 
	#endif
	virtual void render();	///< Renders all commands to the backbuffer
	RenderDevice(const RenderDevice& other) = delete;
	RenderDevice& operator=(const RenderDevice& other) = delete;
protected:
	#ifdef _WIN32
	RENDERLIB_API
	#endif
	virtual void clearBackBuffer();
	std::vector<std::unique_ptr<RenderCommand>> _renderCommands;
};
