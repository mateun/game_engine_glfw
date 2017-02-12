#include "stdafx.h"
#include "renderdevice.h"
#include "rendercommand.h"
#include "GL/glew.h"

void RenderDevice::addRenderCommand(RenderCommand renderCommand) {
	_renderCommands.push_back(renderCommand);
}

void RenderDevice::deleteCommandBuffer() {
	_renderCommands.clear();
}

void RenderDevice::clearBackBuffer() {
	// TODO remove these one-time-startup thingies...
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void RenderDevice::render() {
	// TODO implement
	clearBackBuffer();

}

