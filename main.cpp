/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 07:59:13 by amatshiy          #+#    #+#             */
/*   Updated: 2018/08/22 08:47:30 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <math.h>
# include <iostream>
# include <cmath>
# include "Image_Loader/image_loader.hpp"
# include "Image_Loader/stb_image.h"
# include "shader.hpp"

#define WIDTH 800
#define HEIGHT 600

void	framebuffer_size_callback(GLFWwindow* window, int width, int height);
void	processInput(GLFWwindow* window);

int	main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW failed to start" << std::endl;
		exit(1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Epic Window", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glViewport(0, 0, WIDTH, HEIGHT);

	// //Initializing glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
    	std::cout << "Failed to initialize GLAD" << std::endl;
    	return -1;
	}

	//build and compile shader program
    Shader ourShader("texture.vs", "texture.fs");

    float vertices[] = {
        // positions          // colors           // texture coords
        1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Binding Vertex Array Object
    glBindVertexArray(VAO);

    //Binding the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Binding the Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //load and create texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //load image, create texture and generate mipmaps
    int width, height, nrChannels;

    // creating image data
    ImageLoader loader("player/head.jpg", width, height, nrChannels);
    unsigned char * data = loader.getImageData();
    loader.freeImageData();
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        exit(1);
    }
    // stbi_image_free(data);
    
    // render loop
    // -----------
	float h = 0.0f;
    float w = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //bind texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        //render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//updating the coords of triCoords uniform
		int vertexTriLocation = ourShader.getLocation("moveCoords");
        if (!vertexTriLocation)
        {
            std::cout << "Error: Can't find location: " << vertexTriLocation << std::endl;
            exit(1);
        }
		glUniform3f(vertexTriLocation, w, h, 0.0f); //bottom right
		glUniform3f(vertexTriLocation, w, h, 0.0f); //bottom left
		glUniform3f(vertexTriLocation, w, h, 0.0f); //top


        // // update shader uniform
        // float timeValue = glfwGetTime();
        // float greenValue = sin(timeValue) / 2.0f + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // render the triangle
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
		if (glfwGetKey(window, 265) == GLFW_PRESS)
			h += 0.01f;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			h -= 0.01f;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			w -= 0.01f;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			w += 0.01f;
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
    glViewport(0, 0, width, height);
}