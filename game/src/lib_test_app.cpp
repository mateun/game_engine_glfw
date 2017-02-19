#include "stdafx.h"
#include <renderlib.h>

class MyPlayerControllerScript : public NodeComponent {
	
public:
	virtual void execute() {
		//printf("in exec. of PlayerControllerScript\n");
	}
};

class TriRenderCommand : public RenderCommand {

public:
	TriRenderCommand() {
		_shader.createProgram("simplevs.glsl", "simpleps.glsl");
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		

		GLenum err = glGetError();
		
		GLfloat triPos[20] = {
			-0.5, -0.5, -0, 0, 0,
			0.5, 0.5, -0, 1, 1,
			-0.5, 0.5, -0, 0, 1,
			0.5, -0.5, -0, 1, 0
		};

		std::vector<GLfloat> pos;
		for (GLfloat p : triPos) {
			pos.push_back(p);
		}

		GLfloat tricol[8] = {
			1, 0,
			1, 1,
			0.5, 0.5,
			0.25, 0.75
		};
		std::vector<GLfloat> col;
		for (GLfloat p : tricol) {
			col.push_back(p);
		}


		GLuint triIndices[6] = {
			0, 1, 2,
			0,3,1
		};
		std::vector<GLuint> ind;
		for (GLuint i : triIndices) {
			ind.push_back(i);
		}

		glBufferData(GL_ARRAY_BUFFER, pos.size() * 4, &pos.front(), GL_STATIC_DRAW);
		printf("sizeof tripos array: %d %d\n", sizeof(triPos), pos.size() * 4);

		// positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * 4, (void*)0);
		glEnableVertexAttribArray(0);

		
		// uvs
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * 4, (void*) 12);
		glEnableVertexAttribArray(1);
		err = glGetError();
		if (err != 0) printf("0 gl error: %d", err);

		// col
		GLuint vboCol;
		glGenBuffers(1, &vboCol);
		glBindBuffer(GL_ARRAY_BUFFER, vboCol);
		glBufferData(GL_ARRAY_BUFFER, col.size() * 4, &col.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);

		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind.front(), GL_STATIC_DRAW);
		printf("sizeof triIndices array: %d\n", sizeof(triIndices));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// Texture setup
		GLubyte * data = new GLubyte[16 * 16*4];
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &_texture);
		err = glGetError();
		if (err != 0) printf("0 gl error: %d", err);
		glBindTexture(GL_TEXTURE_2D, _texture);
		err = glGetError();
		if (err != 0) printf("01 gl error: %d", err);
		//glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8I, 64, 64);
		err = glGetError();
		if (err != 0) printf("02 gl error: %d", err);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// fill data into texture
		for (int x = 0; x < 16*16*4; x+=4) {
				data[x] = 0xff;
				data[x+1] = 0xab;
				data[x+2] = 0x00;
				data[x+3] = 0xff;
		}

		MultiFormatImageImporter pngImporter;
		std::unique_ptr<FBImage> image = pngImporter.importImage("G:/Archive/Pictures/2D/Textures/Pixelart/ChibbyMalePixelChar512.png");
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image->getPixels());
		err = glGetError();
		if (err != 0) {
			printf("03 gl error: %d: %s", err, gluErrorString(err));
		}

		delete [] data;


	}

	virtual void execute() {
		glBindVertexArray(_vao);
		GLenum err = glGetError();
		if (err != 0) printf("1 gl error: %d", err);
		_shader.bindToPipeline();
		err = glGetError();
		if (err != 0) printf("2 gl error: %d", err);
		//glDrawArrays(GL_TRIANGLES, 0, 4);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		err = glGetError();
		if (err != 0) printf("3 gl error: %d", err);

	}

private:
	Shader _shader;
	GLuint _vao;
	GLuint _texture;
};

class GameObject : public SceneNode {

public:
	GameObject() {
		rc = std::make_shared<TriRenderCommand>();
	}
	virtual  void update(GameTime& gameTime) {
		SceneNode::update(gameTime);
		//printf("in update of GameObject\n");
	}
	virtual void render(RenderDevice& rd) {
		rd.addRenderCommand(rc);

	}

	void specialFunc() {

	}

private:
	std::shared_ptr<TriRenderCommand> rc;
	
};

int main(int argc, char** args) {
	MultiFormatImageImporter pngImporter;
	std::unique_ptr<FBImage> img = pngImporter.importImage("G:/Archive/Pictures/2D/Textures/Lava_d.png");
	
	GLFWDisplay display(800, 600, false);

	RenderDevice rd;
	DefaultScene scene;
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->addComponent(std::move(std::make_unique<MyPlayerControllerScript>()));
	scene.addNode(go);

	while (true) {
		go->specialFunc();
		display.pollEvents();
		scene.update();
		scene.render(rd);
		display.swapBuffers();
	}

	return 0;
}