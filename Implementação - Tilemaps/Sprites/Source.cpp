#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <assert.h>

//GLM
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//STB IMAGE
#include<stb_image.h>


using namespace std;
//using namespace glm; //para não usar glm::

//Classe para manipulação dos shaders
#include "Shader.h"

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
int setupGeometry();
void drawScene(int VAO, int texID);
GLuint loadTexture(string texturePath);

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{

	ifstream file("map.txt");
	if (!file.is_open()) {
		std::cout << "Erro ao abrir o arquivo." << std::endl;
		return 1;
	}

	std::string tileset_name;
	int tile_count, tile_width, tile_height, tiles_l, tiles_c;
	file >> tileset_name >> tile_count >> tile_height >> tile_width >> tiles_x >> tiles_y;

	std::vector<std::vector<int>> tiles;
	int tile_value;
	while (file >> tile_value) {
		std::vector<int> row;
		row.push_back(tile_value);
		for (int i = 1; i < tiles_y; ++i) {
			file >> tile_value;
			row.push_back(tile_value);
		}
		tiles.push_back(row);
	}

	file.close();

	std::cout << "Nome: " << tileset_name << std::endl;
	std::cout << "Quantidade de tiles: " << tile_count << std::endl;
	std::cout << "Largura do tile: " << tile_width << std::endl;
	std::cout << "Altura do tile: " << tile_height << std::endl;
	std::cout << "Tiles:" << std::endl;
	for (const auto& row : tiles) {
		for (int value : row) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
}
	
//	// Inicialização da GLFW
//	glfwInit();
//
//	// Criação da janela GLFW
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tilemap", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//
//	// Fazendo o registro da função de callback para a janela GLFW
//	glfwSetKeyCallback(window, key_callback);
//
//	// GLAD: carrega todos os ponteiros d funções da OpenGL
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		cout << "Failed to initialize GLAD" << endl;
//
//	}
//
//	// Obtendo as informações de versão
//	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
//	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
//	cout << "Renderer: " << renderer << endl;
//	cout << "OpenGL version supported " << version << endl;
//
//	// Compilando e buildando o programa de shader
//	//Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");
//	Shader shader("../shaders/tex_vert.glsl", "../shaders/tex_frag.glsl");
//
//	GLuint VAO = setupGeometry();
//	
//	GLuint texID = loadTexture("../../Textures/Pixelwall.png");
//	
//	//Ativando o buffer de textura 0 da opengl
//	glActiveTexture(GL_TEXTURE0);
//
//	shader.Use();
//
//	//Matriz de projeção paralela ortográfica
//	glm::mat4 projection = glm::ortho(0.0,800.0,0.0,600.0,-1.0,1.0);
//	//Enviando para o shader a matriz como uma var uniform
//	shader.setMat4("projection", glm::value_ptr(projection));
//	
//	//Matriz de transformação do objeto (matriz de modelo)
//	glm::mat4 model = glm::mat4(1); //matriz identidade
//	model = glm::translate(model, glm::vec3(400.0, 300.0, 0.0));
//	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
//	model = glm::scale(model, glm::vec3(400.0, 400.0, 0.0));
//	shader.setMat4("model", glm::value_ptr(model));
//
//	shader.setInt("texBuffer", 0);
//
//	// Loop da aplicação - "game loop"
//	while (!glfwWindowShouldClose(window))
//	{
//		// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
//		int width, height;
//		glfwGetFramebufferSize(window, &width, &height);
//		glViewport(0, 0, width, height); //unidades de tela: pixel
//		
//		// Limpa o buffer de cor
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glLineWidth(10);
//		glPointSize(20);
//
//		//Chamadas de desenho da cena
//		drawScene(VAO, texID);
//
//		// Troca os buffers da tela
//		glfwSwapBuffers(window);
//
//		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
//		glfwPollEvents();
//	}
//	// Pede pra OpenGL desalocar os buffers
//	glDeleteVertexArrays(1, &VAO);
//	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
//	glfwTerminate();
//	return 0;
//}
//
//// Função de callback de teclado - só pode ter uma instância (deve ser estática se
//// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
//// ou solta via GLFW
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//}
//
//
//
//int setupGeometry()
//{
//	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
//	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
//	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
//	// Pode ser armazenado em um VBO único ou em VBOs separados
//	GLfloat vertices[] = {
//		//x     y    z    r    g    b    s    t
//		
//		//Retângulo inteiro
//		-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,   // Canto inferior esquerdo
//		-0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,   // Canto superior esquerdo
//		0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,   // Canto inferior direito
//		0.5f, 0.5f, 0.0f,    1.0f, 1.0f, 1.0f,  1.0f, 1.0f    // Canto superior direito
//		
//		//OU
//		//Triangulo 0
//		//-0.5f , 0.5f, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0,  //v0
//		//-0.5f ,-0.5f, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
//		// 0.5f , 0.5f, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,  //v2
//		// //Triangulo 1	
//	 //   -0.5f ,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //v1
//		// 0.5f ,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //v3
//		// 0.5f , 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f   //v2
//		
//	};
//
//	GLuint VBO, VAO;
//	//Geração do identificador do VBO
//	glGenBuffers(1, &VBO);
//	//Faz a conexão (vincula) do buffer como um buffer de array
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//Envia os dados do array de floats para o buffer da OpenGl
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	//Geração do identificador do VAO (Vertex Array Object)
//	glGenVertexArrays(1, &VAO);
//	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
//	// e os ponteiros para os atributos 
//	glBindVertexArray(VAO);
//	
//	//Atributo 0 - posição
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	//Atributo 1 - cor
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	//Atributo 2 - coordenadas de textura
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//
//	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
//	// atualmente vinculado - para que depois possamos desvincular com segurança
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
//	glBindVertexArray(0);
//
//	return VAO;
//}
//
//
//
//void drawScene(int VAO, int texID)
//{
//	glBindTexture(GL_TEXTURE_2D, texID);
//	glBindVertexArray(VAO); //Conectando ao buffer de geometria
//
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Para o retângulo
//	//OU
//	//glDrawArrays(GL_TRIANGLES, 0, 6); //Para os triângulos
//	glBindTexture(GL_TEXTURE_2D, 0); //unbind
//	glBindVertexArray(0); //Desconectando o buffer de geometria
//
//}
//
//GLuint loadTexture(string texturePath)
//{
//	GLuint texID;
//
//	// Gera o identificador da textura na memória 
//	glGenTextures(1, &texID);
//	glBindTexture(GL_TEXTURE_2D, texID);
//
//	//Configuração do parâmetro WRAPPING nas coords s e t
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	//Configuração do parâmetro FILTERING na minificação e magnificação da textura
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannels;
//	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
//
//	if (data)
//	{
//		if (nrChannels == 3) //jpg, bmp
//		{
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		}
//		else //png
//		{
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		}
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//
//	stbi_image_free(data);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	return texID;
//}


