#pragma once
#include "renderlib_api.h"

/**
	\class	GameTime
	\brief	This class contains different kinds of time information, 
			such as the total time the game is running, 
			the last frametime etc.
 */
class RENDERLIB_API GameTime {

public:
	virtual long getTotalGameTime();		///< returns the time the game is running, in ms
	virtual long getFrameTime();			///< returns the last frame duration in ms
};