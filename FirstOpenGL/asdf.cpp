//Be sure to include GLAD before GLFW.
//The include file for GLAD includes the required 
//OpenGL headers behind the scenes(like GL / gl.h) 
//so be sure to include GLAD before other header 
//files that require OpenGL(like GLFW).
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int wwidth, int height);
void processInput(GLFWwindow* window);
void SetBackGroundColor();

int main() {

	// OpenGL 초기화&버전&프로파일 설정
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 윈도우 창 생성
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGl", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ---------------------
	// 버텍스 배열
	float vertices[] = {
		// 위치 정보				// 색상 정보			//텍스쳐 좌표
		0.5f,	0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f,	-0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,   0.0f, 1.0f
	};

	// 버텍스 인덱스
	// 각 정점들을 어떻게 삼각형으로 만들지에 대한 정보
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3	
	};

	// 텍스쳐 좌표
	float texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f
	};

	

	//---------------------------------------------------------
	//기존 셰이더 코드
	// 
	// 
	//// 버텍스 셰이더 소스
	//const char* vertexShaderSource = "#version 330 core\n"
	//	"layout (location = 0) in vec3 aPos;\n"
	//	"layout (location = 1) in vec3 aColor;\n"
	//	"out vec3 ourColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	"   gl_Position = vec4(aPos, 1.0);\n"
	//	"	ourColor = aColor;\n"
	//	"}\0";

	//// 프레그먼트 셰이더 소스
	//const char* fragmentShaderSource = "#version 330 core\n"
	//	"out vec4 FragColor;\n"
	//	"in vec3 ourColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	"   FragColor = vec4(ourColor, 1.0);\n"
	//	"}\n\0";

	//// 버텍스 셰이더 컴파일
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//// 버텍스 셰이더 컴파일 오류 확인
	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//
	//if (!success) {
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//// 프레그먼트 셰이더 컴파일
	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//// 셰이더 연결
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//// 셰이더 연결 성공 확인
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//}

	//// 사용한 셰이더 객체들은 삭제
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	//
	// 기존 셰이더 코드 끝
	//------------------------------------------

	// 셰이더 생성
	Shader ourShader("FirstVertex.vs", "FristFrag.fs");

	// ---------------------
	// 버텍스 버퍼 객체 생성
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	// 버텍스 배열 객체 생성
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 원소 버퍼 객체 생성
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// 버텍스 배열을 버텍스 버퍼에 전달
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 원소 퍼버에 인덱스 배열 전달
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 버텍스 위치 속성 포인터 설정
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 버텍스 색상 속성 포인터 설정
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 버텍스 텍스처 좌표 속성 포인터 설정
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// ---------------------
	// 텍스쳐 선언&바인딩
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// 텍스쳐 랩핑/필터링 옵션
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 텍스쳐
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load textue" << std::endl;
	}
	stbi_image_free(data);
	
	// ---------------------
	// 사용가능한 최대 버텍스 속성 수 검색
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// ---------------------
	// render loop
	// 프레임마다 호출 됨
	while (!glfwWindowShouldClose(window)) {
		// 입력
		processInput(window);

		// 기타 명령
		// 배경색 설정
		SetBackGroundColor();

		// 기존 세이더 활성화
		//glUseProgram(shaderProgram);

		// 새로운 셰이더
		ourShader.use();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 버퍼 교환과 이벤트 처리
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		std::cout << "a pressed" << std::endl;
}

void SetBackGroundColor() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}