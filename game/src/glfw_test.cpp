// glfw_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#ifdef _WIN32
#include <Windows.h>
#endif

enum GLShaderType {
	VERTEX,
	PIXEL
};

struct Model {
	GLuint vao;
	uint16_t numIndices;
};

// function prototypes
glm::vec3 readPosition(const std::string& line);
glm::vec2 readUV(const std::string& line);
glm::vec3 readNormal(const std::string& line);
glm::vec3 readFace(const std::string& line);
glm::vec3 readFace(const std::string& line, int subIndex);
glm::vec3 readFaceNormal(const std::string& line);
glm::vec3 readFaceUV(const std::string& line);

// globals (pfui..)
GLuint vaoTriangle;
bool shouldRun = true;

void printGLError(GLenum err) {
	if (err != 0) {
		printf("err: %d%s\n", err, gluErrorString(err));
	}
}

GLenum checkGLError() {
	GLenum err = glGetError();
	return err;
}

std::string readFileIntoString(const std::string& fileName) {
	std::ifstream inFile(fileName, std::ios::in);
	std::ostringstream code;
	while (inFile.good()){
		int c = inFile.get();
		if (!inFile.eof()) code << (char)c;
	}
	inFile.close();
	return code.str();
}
GLuint createShader(const std::string& vertexFile, const std::string& pixelFile) {
	std::string srcVertex = readFileIntoString(vertexFile);
	std::string srcPixel = readFileIntoString(pixelFile);
		
	GLuint handle = glCreateProgram();
	GLuint hV = glCreateShader(GL_VERTEX_SHADER);
	GLuint hP = glCreateShader(GL_FRAGMENT_SHADER);

	const char* srcVertexC = srcVertex.c_str();
	const char* srcPixelC = srcPixel.c_str();
	glShaderSource(hV, 1, &srcVertexC, NULL);
	glCompileShader(hV);
	
	GLint result;
	glGetShaderiv(hV, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result) {
		printf("error compiling vertex shader\n");
		return 0;
	}
	else {
		glAttachShader(handle, hV);
	}

	glShaderSource(hP, 1, &srcPixelC, NULL);
	glCompileShader(hP);
	
	glGetShaderiv(hP, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result) {
		printf("error compiling pixel shader\n");
		return 0;
	}
	else {
		glAttachShader(handle, hP);
	}

	glLinkProgram(handle);
	GLint status = 0;
	glGetProgramiv(handle, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) {
		printf("error linking the program.\n");
		return 0;
	}
	return handle;
}

GLFWwindow* initWindow(bool fullScreen) {
	if (!glfwInit()) {
		printf("error in glfw init.\n");
		exit(1);
	}

	GLFWmonitor* mon;
	if (fullScreen)
		mon = glfwGetPrimaryMonitor();
	else
		mon = NULL;
		

	GLFWwindow* window = glfwCreateWindow(800, 600, "ferklwindow", mon, NULL);
	if (!window) {
		glfwTerminate();
		exit(1);
	}
	
	glfwMakeContextCurrent(window);
	GLenum err = glGetError();
	printGLError(err);
	
	// glew stuff
	//glewExperimental = GL_TRUE;
	err = glewInit();
	if (GLEW_OK != err) {
		printf("glew error. %s\n", glewGetErrorString(err));
		exit(1);
	}

	printGLError(checkGLError());

	return window;
}



// setup a vertex buffer 
// for a triangle
void initTriangle() {
	GLuint vbo;
	
	glGenVertexArrays(1, &vaoTriangle);
	printGLError(checkGLError());
	glBindVertexArray(vaoTriangle);
	printGLError(checkGLError());

	glGenBuffers(1, &vbo);
	printGLError(checkGLError());
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	printGLError(checkGLError());

	GLfloat triPos[12] = {
		-0.5, -0.5, -0,
		0.5, 0.5, -0,
		-0.5, 0.5, -0,
		0.5, -0.5, -0
	};

	std::vector<GLfloat> pos;
	for (GLfloat p : triPos) {
		pos.push_back(p);
	}

	GLuint triIndices[6] = {
		0, 1, 2,
		0,1,3
	};
	std::vector<GLuint> ind;
	for (GLuint i : triIndices) {
		ind.push_back(i);
	}

	glBufferData(GL_ARRAY_BUFFER, pos.size() * 4, &pos.front(), GL_STATIC_DRAW);
	printf("sizeof tripos array: %d\n", sizeof(triPos));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind.front(), GL_STATIC_DRAW);
	printf("sizeof triIndices array: %d\n", sizeof(triIndices));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

// Returns a VAO id
Model importObjModel(const std::string& modelFileName) {
	std::string text = readFileIntoString(modelFileName);
	std::istringstream iss(text);
	std::string line;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> faces;
	std::vector<glm::vec3> facesNormals;
	std::vector<glm::vec3> facesUVs;

	std::vector<glm::vec3> positions_final;
	std::vector<glm::vec3> normals_final;
	std::vector<glm::vec2> uvs_final;
	std::vector<GLuint> indices_final;

	while (std::getline(iss, line)) {
		if (line[0] == '#') {
			printf("skip comment.\n");
		} 
		else if(line[0] == 'v' && line[1] == ' ') {
			positions.push_back(readPosition(line));
		}
		else if (line[0] == 'v' && line[1] == 't') {
			uvs.push_back(readUV(line));
		}
		else if (line[0] == 'v' && line[1] == 'n') {
			normals.push_back(readNormal(line));
		}
		else if (line[0] == 'f') {
			faces.push_back(readFace(line));
			facesNormals.push_back(readFaceNormal(line));
			facesUVs.push_back(readFaceUV(line));
		}
	}

	int idx = 0;
	std::map<int, int> combos;
	int positionIndex = faces.size();
	for (glm::vec3 f : faces) {
		int v1 = f.x;
		int v2 = f.y;
		int v3 = f.z;

		int uv1 = facesUVs[idx].x;
		int uv2 = facesUVs[idx].y;

		int n1 = facesNormals[idx].x;
		int n2 = facesNormals[idx].y;
		int n3 = facesNormals[idx].z;

		if (combos[v1] == 0) {
			combos[v1] = n1;
		} 
		else if (combos[v1] != n1) {
			// create duplicate vertex at end of vertices
			glm::vec3 pos = positions[v1-1];
			positions.push_back(pos);
			// and change the face definition to the new index
			f.x = positions.size() - 1;
			faces[idx].x = positions.size();
		}

		if (combos[v2] == 0) {
			combos[v2] = n2;
		} 
		else if (combos[v2] != n2) {
			// create duplicate vertex at end of vertices
			glm::vec3 pos = positions[v2-1];
			positions.push_back(pos);
			// and change the face definition to the new index
			faces[idx].y = positions.size();
		}
		if (combos[v3] == 0) {
			combos[v3] = n3;
		} 
		else if (combos[v3] != n3) {
			// create duplicate vertex at end of vertices
			glm::vec3 pos = positions[v3-1];
			positions.push_back(pos);
			// and change the face definition to the new index
			faces[idx].z = positions.size();
		}

		idx++;
	}

	// allocate enough space for the uvs and normals final vectors
	positions_final.resize(positions.size());
	normals_final.resize(positions.size());
	uvs_final.resize(positions.size());

	// iterate through all faces again 
	// and store all data in its final destination.
	// store the index in an ibo vector
	idx = 0;
	for (glm::vec3 f : faces) {
		int p1 = f.x;
		int p2 = f.y;
		int p3 = f.z;

		int u1 = facesUVs[idx].x;
		int u2 = facesUVs[idx].y;
		int u3 = facesUVs[idx].z;

		int n1 = facesNormals[idx].x;
		int n2 = facesNormals[idx].y;
		int n3 = facesNormals[idx].z;

		glm::vec3 v1 = positions[p1 - 1];
		glm::vec3 v2 = positions[p2 - 1];
		glm::vec3 v3 = positions[p3 - 1];

		positions_final[p1 - 1] = (v1);
		positions_final[p2 - 1] = (v2);
		positions_final[p3 - 1] = (v3);
		
		uvs_final[p1-1] = uvs[u1-1];
		uvs_final[p2-1] = uvs[u2-1];
		uvs_final[p3-1] = uvs[u3-1];

		normals_final[p1 - 1] = normals[n1-1];
		normals_final[p2 - 1] = normals[n2-1];
		normals_final[p3 - 1] = normals[n3-1];

		indices_final.push_back(p1-1);
		indices_final.push_back(p2-1);
		indices_final.push_back(p3-1);
		
		idx ++;

	}

	std::vector<GLfloat> positions_final_data;
	for (glm::vec3 p : positions_final) {
		positions_final_data.push_back(p.x);
		positions_final_data.push_back(p.y);
		positions_final_data.push_back(p.z);
	}
	
	GLuint vaoModel;
	glGenVertexArrays(1, &vaoModel);
	printGLError(checkGLError());
	glBindVertexArray(vaoModel);
	printGLError(checkGLError());

	GLuint vboModel;
	glGenBuffers(1, &vboModel);
	printGLError(checkGLError());
	glBindBuffer(GL_ARRAY_BUFFER, vboModel);
	printGLError(checkGLError());
	glBufferData(GL_ARRAY_BUFFER, positions_final_data.size()*4, &positions_final_data.front(), GL_STATIC_DRAW);
	printf("sizeof tripos array: %d\n", positions_final_data.size()*4);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	std::vector<GLfloat> normals_final_data;
	for (glm::vec3 p : normals_final) {
		normals_final_data.push_back(p.x);
		normals_final_data.push_back(p.y);
		normals_final_data.push_back(p.z);
	}
	

	GLuint vboNormals;
	glGenBuffers(1, &vboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
	glBufferData(GL_ARRAY_BUFFER, normals_final_data.size() * 4, &normals_final_data.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);



	GLuint vboIndices;
	glGenBuffers(1, &vboIndices);
	printGLError(checkGLError());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
	printGLError(checkGLError());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_final.size()*4, &indices_final.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	Model m;
	m.vao = vaoModel;
	m.numIndices = indices_final.size();
	return m;
}

std::vector<std::string> tokenize(const std::string& source, char delimiter) {
	std::stringstream in(source);
	std::string seg;
	std::vector<std::string> ret;
	while (std::getline(in, seg, delimiter)) {
		ret.push_back(seg);
	}
	return ret;
}

glm::vec2 readUV(const std::string& line) {
	glm::vec2 v;
	std::vector<std::string> tokens = tokenize(line, ' ');
	v.x = atof(tokens[1].c_str());
	v.y = atof(tokens[2].c_str());

	return v;
}

glm::vec3 readPosition(const std::string& line) {
	glm::vec3 v;
	std::vector<std::string> tokens = tokenize(line, ' ');
	v.x = atof(tokens[1].c_str());
	v.y = atof(tokens[2].c_str());
	v.z = atof(tokens[3].c_str());

	return v;
}

glm::vec3 readNormal(const std::string& line) {
	glm::vec3 v;
	std::vector<std::string> tokens = tokenize(line, ' ');
	v.x = atof(tokens[1].c_str());
	v.y = atof(tokens[2].c_str());
	v.z = atof(tokens[3].c_str());

	return v;
}

glm::vec3 readFace(const std::string& line) {
	return readFace(line, 0);
}

glm::vec3 readFaceNormal(const std::string& line) {
	return readFace(line, 2);
}

glm::vec3 readFaceUV(const std::string& line) {
	return readFace(line, 1);
}

glm::vec3 readFace(const std::string& line, int subIndex) {
	glm::vec3 v;
	std::vector<std::string> tokens = tokenize(line, ' ');
	int idx = 1;
	int idxz = 0;
	for (std::string s : tokens)
	{
		if (s[0] != 'f') {
			std::vector<std::string> subs = tokenize(s, '/');
			v[idxz] = atoi(subs[subIndex].c_str());
			idxz++;
		}
	}

	return v;
}

void transformModel(glm::vec3 translation, glm::vec3 rotAxis, float rotAngle, GLint locMV) {
	glm::mat4 matMV;
	matMV = glm::translate(matMV, translation);
	matMV = glm::rotate(matMV, rotAngle, rotAxis);
	matMV = glm::scale(matMV, glm::vec3(0.2, 0.2, 0.2));

	glUniformMatrix4fv(locMV, 1, GL_FALSE, glm::value_ptr(matMV));
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		shouldRun = false;
	}
}

#ifdef _WIN32
int _tmain__(int argc, char* argv[])
{
	printf("GLFW test application starting up.\n");
	glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
	GLFWwindow* window = initWindow(false);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	glClearColor(0, 1.0, 1.0, 1);
	printGLError(checkGLError());
	initTriangle();
	printGLError(checkGLError());

	// compile our shader program
	GLuint shaderProg = createShader("vshader.glsl", "pshader.glsl");
	printGLError(checkGLError());


	// print out version number
	printf("GL Version: %s\n", glGetString(GL_VERSION));
	int maj, min;
	glGetIntegerv(GL_MAJOR_VERSION, &maj);
	glGetIntegerv(GL_MINOR_VERSION, &min);
	printf("GL version maj.min: %d.%d\n", maj, min);

	// import the model
	//Model model = importObjModel("house.obj");

	// basic transformation matrices
	/*glm::mat4 matProj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	
	float rotZ = 0;

	GLint locProj = glGetUniformLocation(shaderProg, "proj");
	GLint locMV = glGetUniformLocation(shaderProg, "mv");
	GLint locBaseCol = glGetUniformLocation(shaderProg, "baseCol");
	glUseProgram(shaderProg);
	glUniformMatrix4fv(locProj, 1, GL_FALSE, glm::value_ptr(matProj));*/

	long frameEnd = 0;

	glfwSetKeyCallback(window, keyCallBack);

	glPointSize(20);
	GLuint simpleShaderProg = createShader("simplevs.glsl", "simpleps.glsl");
	printGLError(checkGLError());

	GLfloat bgcol[] = { 0, 0, 0, 1 };

	while (!glfwWindowShouldClose(window) && shouldRun) {
		//glClear(GL_COLOR_BUFFER_BIT );
		glClearBufferfv(GL_COLOR, 0, bgcol);
		//glClearBufferfv(GL_DEPTH, 0, bgcol);

		glBindVertexArray(vaoTriangle);
		glUseProgram(simpleShaderProg);
		glDrawArrays(GL_POINTS, 0, 1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// main loop
	//while (!glfwWindowShouldClose(window) && shouldRun) {
	//	long now = GetTickCount();
	//	long duration = now - frameEnd;

	//	printf("duration: %d\n", duration);

	//	// wait for 16ms
	//	int ctr = 0;
	//	if (duration < 15) {
	//		while (duration < 15) {
	//			// logic
	//			ctr++;
	//			rotZ += 0.001f * duration;
	//			Sleep(1);
	//			duration = GetTickCount() - frameEnd;
	//			printf("duration after loop: %d ctr: %d\n", duration, ctr);
	//		}
	//	}
	//	else {
	//		rotZ += 0.001f * duration;
	//	}

	//	rotZ += 0.01f;

	//	printf("duration after wait: %d\n", duration);

	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//			// model transformation
	//	float one = 1;
	//	glm::mat4 matMV = glm::mat4x4(one);
	//	//matMV = glm::translate(matMV, glm::vec3(0, 0, -8));
	//	////matMV = glm::rotate(matMV, rotZ, glm::vec3(0, 0, 1));
	//	//
	//	//matMV = glm::rotate(matMV, glm::radians(rotZ * 10.1f), glm::vec3(0, 1, 0));
	//	//matMV = glm::scale(matMV, glm::vec3(0.2, 0.2, 0.2));

	//	transformModel(glm::vec3(0, 0, -7), glm::vec3(0, 1, 0), glm::radians(rotZ * 20), locMV);
	//	glUniform4fv(locBaseCol, 1, glm::value_ptr(glm::vec4(0.7, 0.999, 0.8, 1)));

	//	glBindVertexArray(model.vao);
	//	//glBindVertexArray(vaoTriangle);
	//	printGLError(checkGLError());
	//	glDrawElements(GL_TRIANGLES, model.numIndices, GL_UNSIGNED_INT, 0);

	//	// Draw at other location with other rotation
	//	transformModel(glm::vec3(-1.5, -1, -6), glm::vec3(0.7, 0.2, 1), glm::radians(rotZ * 40), locMV);
	//	glUniform4fv(locBaseCol, 1, glm::value_ptr(glm::vec4(0.1, 0.7, 0.8, 1)));
	//	glDrawElements(GL_TRIANGLES, model.numIndices, GL_UNSIGNED_INT, 0);

	//	printGLError(checkGLError());
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//	frameEnd = GetTickCount();


	//}

	glfwTerminate();
	return 0;
}
#endif
