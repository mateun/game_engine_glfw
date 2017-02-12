#pragma once
#include "renderlib_api.h"
#include "mesh.h"
#include "material.h"
#include "texture.h"

/**
	\class	RenderCommand
	\brief	This class stores the information to render a specific mesh
			with a texture and a material.
*/
#ifdef _WIN32
class RENDERLIB_API RenderCommand {
#else
class RenderCommand {
#endif

public:
	virtual void setMesh(Mesh);
	virtual Mesh getMesh();
	virtual void setTexture(Texture);
	virtual Texture getTexture();
	virtual void setMaterial(Material);
	virtual Material getMaterial();

private:
	Mesh _mesh;
	Material _material;
	Texture _texture;


};
