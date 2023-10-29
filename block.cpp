
//branchout
#include "block.h"
#include <iostream>
/**
 * Creates a square Block that is dimension x dimension pixels in size,
 * starting at (x, y) on img. Assumes that the requested
 * Block fits on the image (inputs are feasible)
**/
void Block::Build(PNG& img, unsigned int x, unsigned int y, unsigned int dimension) {
	// complete your implementation below
	vector<vector<RGBAPixel>> vec( dimension , vector<RGBAPixel> (dimension));  
   data = vec;
	for (unsigned int i  = x; i < (x+dimension); i++) {
		for (unsigned int j  = y; j < (y+dimension); j++) {
			data[j-y][i-x].r = img.getPixel(i, j)->r;
			data[j-y][i-x].g = img.getPixel(i, j)->g;
			data[j-y][i-x].b = img.getPixel(i, j)->b;
		}
	}
}

/**
 * Renders this Block onto img with its upper-left corner at (x, y).
 * Assumes block fits on the image.
 * 
 * @param full - whether to render the entire contents to the target PNG,
 *               or the average color to a single pixel in the target PNG.
**/
void Block::Render(PNG& img, unsigned int x, unsigned int y, bool full) const {
	// complete your implementation below
	// ignore this comment
	int capacity = Dimension();
	if (full) {
		for (unsigned int i = x; i < (x+capacity); i++) { 
			for (unsigned int j = y; j < (y+capacity); j++) {
				img.getPixel(i, j)->r = data[j-y][i-x].r;
				img.getPixel(i, j)->g = data[j-y][i-x].g;
				img.getPixel(i, j)->b = data[j-y][i-x].b ;
			}
		}	
		
	} else {

		RGBAPixel pixel = GetAverageColor();

		img.getPixel(x, y)->r = pixel.r;
		img.getPixel(x, y)->g = pixel.g;
		img.getPixel(x, y)->b = pixel.b;
	}
}

/**
 * Flips the Block's pixel data horizontally by a simple reflection
 * across the vertical axis through its middle.
**/
void Block::FlipHorizontal() {
	// complete your implementation below
    for (unsigned int i = 0; i < (Dimension()); i++) {
			for (unsigned int j = 0; j < (Dimension()/2); j++) {
				RGBAPixel temp = data[i][j];
				data[i][j] = data[i][Dimension()-j-1];
				data[i][Dimension()-j-1] = temp;
			}
		}
}

/**
 * Flips the Block's pixel data vertically by a simple reflection
 * across the horizontal axis through its middle.
**/
void Block::FlipVertical() {
	// complete your implementation below
        for (unsigned int i = 0; i < (Dimension()/2); i++) {
			for (unsigned int j = 0; j < (Dimension()); j++) {
				RGBAPixel temp = data[i][j];
				data[i][j] = data[Dimension()-i-1][j];
				data[Dimension()-i-1][j] = temp;
			}
		}
}

/**
 * Returns the dimension of the block (its width or height).
 */
unsigned int Block::Dimension() const {
	// replace the statement below with your implementation
	return data.size();
}

/**
 * Returns the average color of the pixels in the block's data.
**/
//TODO
RGBAPixel Block::GetAverageColor() const {
	// replace the statement below with your implementation
		int avgRed = 0;
		int avgGreen = 0;
		int avgBlue = 0;
		for (unsigned int i = 0; i < (Dimension()); i++) {
			for (unsigned int j = 0; j < (Dimension()); j++) {
				avgRed += data[i][j].r;
				avgGreen += data[i][j].g;
				avgBlue += data[i][j].b;
			}
		}
		if (Dimension() > 0) {
			avgRed = avgRed/(Dimension()*Dimension());		
			avgGreen = avgGreen/(Dimension()*Dimension());
			avgBlue = avgBlue/(Dimension()*Dimension());
		}
		RGBAPixel pixel(avgRed, avgGreen, avgBlue);
	return pixel;
}

/**
 * Replaces all pixel data in the block with the block's average color.
**/
//TODO
void Block::FillAverage() {
	// complete your implementation below
	
		RGBAPixel pixel = GetAverageColor();
	for (unsigned int i = 0; i < (Dimension()); i++) {
			for (unsigned int j = 0; j < (Dimension()); j++) {
				data[i][j].r = pixel.r;
				data[i][j].g = pixel.g;
				data[i][j].b = pixel.b;
			}
	
	}		
    
}
