#include "stdafx.h"
#include "rendercommand.h"


void RenderCommand::setMesh(Mesh m) {
	_mesh = m;
}

void RenderCommand::setMaterial(Material m) {
	_material = m;
}

void RenderCommand::setTexture(Texture t) {
	_texture = t;
}

Mesh RenderCommand::getMesh() {
	return _mesh;
}

Material RenderCommand::getMaterial() {
	return _material;
}

Texture RenderCommand::getTexture() {
	return _texture;
}