/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loader.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 09:24:37 by amatshiy          #+#    #+#             */
/*   Updated: 2018/08/20 09:42:05 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __IMAGE_LOADER__
# define __IMAGE_LOADER__

# include <iostream>

class ImageLoader
{
    private:
        unsigned char *ImageData;

    public:
        ImageLoader();
        ImageLoader(std::string file_path, int &width, int &height, int &nrChannels);
        ~ImageLoader();

        unsigned char * getImageData();
        void    freeImageData();
};

# endif