#pragma once
#include <iostream>
#include <string>
#include <assert.h>

//GLM
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Classe para manipulação dos shaders
#include "Shader.h"


using namespace std;
using namespace glm;

class Sprite
{
	public:
		Sprite(GLuint texID, vec3 pos, vec3 escala, Shader* shader, float speed, float ang = 0.0, bool mirrored = false);
		~Sprite();

		void setShader(Shader* shader);
		void draw();
		void mirrorIt(bool mirrored);
		void moveLeft();
		void moveRight();
		
	protected:
		void update();

		//Atributos necessários para cada sprite
		GLuint VAO;
		GLuint texID; 

		glm::vec3 pos, scale;
		float ang, speed;
		bool isMirrored;

		Shader* shader;
};

