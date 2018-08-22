/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:30:12 by amatshiy          #+#    #+#             */
/*   Updated: 2018/08/22 08:18:06 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __SHADER_HPP__
# define __SHADER_HPP__

# include <glad/glad.h>

# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

class Shader
{
    public:
        unsigned int ID; //program ID

        Shader(const char *vertexPath, const char *fragmentPath);

        void    use();
        void    compileShader(unsigned int &shaderID, int type, const char *shaderCode);
        void    setBool(const std::string &name, bool value);
        void    setInt(const std::string &name, int value);
        void    setFloat(const std::string &name, float value);
        int     getLocation(std::string var);
};

# endif