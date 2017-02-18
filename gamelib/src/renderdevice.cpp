#include "stdafx.h"
#include "renderdevice.h"
#include "rendercommand.h"
#include "GL/glew.h"

RenderDevice::RenderDevice() {
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void RenderDevice::addRenderCommand(std::shared_ptr<RenderCommand> renderCommand) {
	_renderCommands.push_back(std::move(renderCommand));
}

void RenderDevice::deleteCommandBuffer() {
	_renderCommands.clear();
}

void RenderDevice::clearBackBuffer() {
	// TODO remove these one-time-startup thingies...
	
	const GLfloat bgcol[] = { 0, 0, .0, 1 };
	const GLfloat dval = 1;
	glClearBufferfv(GL_COLOR, 0, bgcol);
	glClearBufferfv(GL_DEPTH, 0, &dval);
	
}

void RenderDevice::render() {
	clearBackBuffer();
	for (const auto& rc : _renderCommands) {
		rc->execute();
	}

}

