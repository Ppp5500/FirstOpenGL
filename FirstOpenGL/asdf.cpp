//Be sure to include GLAD before GLFW.
//The include file for GLAD includes the required 
//OpenGL headers behind the scenes(like GL / gl.h) 
//so be sure to include GLAD before other header 
//files that require OpenGL(like GLFW).
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int wwidth, int height);
void processInput(GLFWwindow* window);
void SetBackGroundColor();

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	// 버텍스 배열
	float vertices[] = {
		// 위치 정보			// 색상 정보
		0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,	0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	// 정점 인덱스
	// 각 정점들을 어떻게 삼각형으로 만들지에 대한 정보
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
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

	Shader ourShader("FirstVertex.vs", "FristFrag.fs");

	// 버텍스 버퍼 객체 생성
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	// 버텍스 배열 객체 생성
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 원소 버퍼 객체 생성
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);

	// 버텍스 배열을 버텍스 버퍼에 전달
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 원소 퍼버에 인덱스 배열 전달
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 버텍스 위치 속성 포인터 설정
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 버텍스 색상 속성 포인터 설정
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 뷰포트 설정
	//glViewport(0, 0, 800, 600);

	// 사용가능한 최대 버텍스 속성 수 검색
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// ------------
	// render loop
	// 프레임마다 호출 됨
	while (!glfwWindowShouldClose(window)) {
		// 입력
		processInput(window);

		// 기타 명령
		SetBackGroundColor();
		
		// 사각형 그리기
		/*glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);*/

		// 기존 세이더 활성화
		//glUseProgram(shaderProgram);

		// 새로운 셰이더
		ourShader.use();
		ourShader.setFloat("someUniform", 1.0f);

		// uniform 업데이트
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue)/2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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