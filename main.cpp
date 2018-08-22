/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 07:59:13 by amatshiy          #+#    #+#             */
/*   Updated: 2018/08/22 15:16:03 by amatshiy         ###   ########.fr       */
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
        0.3f,  0.3f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
        0.3f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
        0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        0.0f,  0.3f, 0.0f,   1.0f, 0.0f, 1.0f,   0.0f, 1.0f    // top left
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
    unsigned int *texture = new unsigned int[2];
    glGenTextures(2, texture);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    // set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //load image, create texture and generate mipmaps
    int width, height, nrChannels;

    // creating image data
    ImageLoader loader("player/front1.png", width, height, nrChannels);
    unsigned char * data = loader.getImageData();
    loader.freeImageData();
    if (data)
    {
        // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        exit(1);
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    //SECOND TEXTURE
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    // set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // creating image data
    ImageLoader loader2("player/back1.png", width, height, nrChannels);
    unsigned char * data2 = loader2.getImageData();
    loader2.freeImageData();
    if (data2)
    {
        // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        exit(1);
    }
    
    // render loop
    // -----------
	float h = 0.0f;
    float w = 0.0f;
    unsigned int curTex = 0;
    while (!glfwWindowShouldClose(window))
    {
        std::cout << "Current Texture: " << curTex << std::endl;
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render Texture
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
            // if (curTex != 1)
            //     glBindTexture(GL_TEXTURE_2D, 0);
            h += 0.01f;
            curTex = 1;
        }
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
            // if (curTex != 0)
            //     glBindTexture(GL_TEXTURE_2D, 0);
            h -= 0.01f;
            curTex = 0;
        }
        glBindTexture(GL_TEXTURE_2D, texture[curTex]);
        glActiveTexture(GL_TEXTURE0 + curTex);

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
		
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			w -= 0.01f;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			w += 0.01f;
        system("clear");
    }
    glBindTexture(GL_TEXTURE_2D, 0);
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