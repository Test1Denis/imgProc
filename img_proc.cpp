#include "img_proc.h"



Img::Img() {
	w = 39;
	h = 20;
	img_pixels = new int [w * h];
	for (int i = 0; i < w*h; i++) {
		img_pixels[i] = 0x00;		
	}

	img_pixels[w * h/2 + w/2] = 0x01;
	img_pixels[w * h/2 + w/2 + 1] = 0x01;
	img_pixels[w * h/2 + w/2 - 1] = 0x01;
//add pixel to corner
	img_pixels[0] = 0x01;
	img_pixels[h*w - 1] = 0x01;
	img_pixels[w - 1] = 0x01;
	img_pixels[h*w - w] = 0x01;
}

Img::Img(int x_core, int y_core) : _x_core(x_core), _y_core(y_core) {
	w = 3;
	h = 3;
	img_pixels = new int [w * h] {1,1,1,1,1,1,1,1,1};
}

void ImgProc::clearUpdatedImg() {
	int w = img[1 - curImg].w;
	int h = img[1 - curImg].h;
	memset(&img[1 - curImg].img_pixels[0], 0x00, img[1-curImg].w * img[1-curImg].h * sizeof(int)); 
}

void ImgProc::copyMask(int x_core, int y_core) {
	int cur_update_img = 1 - curImg;
/*
	x,y -- coor for mask
	x_core, y_core -- coor pixel 
*/
	for (int y_mask = 0, y_img = y_core - mask->_y_core; y_mask < mask->h; y_mask++, y_img++) {
		if (y_img < 0 || y_img > img[cur_update_img].h - 1) {
			continue;
		}
		for (int x_mask = 0, x_img = x_core - mask->_x_core; x_mask < mask->w; x_mask++, x_img++) {
			if (x_img < 0 || x_img > img[cur_update_img].w - 1) {
				continue;
			}
			img[cur_update_img].img_pixels[y_img * img[cur_update_img].w + x_img] += mask->img_pixels[y_mask * mask->w + x_mask];	
		}
	}
}

void ImgProc::dilatation() {
	clearUpdatedImg();	

	for (int y = 0; y < img[curImg].h; y++) {
		for (int x = 0; x < img[curImg].w; x++) {
			if (img[curImg].img_pixels[img[curImg].w * y + x] == 0) {
				continue;
			}
			copyMask(x,y);		
		}
	}
}

void ImgProc::showImg(int img_num) {
	if (img_num > 1) {
		std::cout << "error img buffer" << std::endl;
		return;
	}
	for (int y = 0; y < img[img_num].h; y++) {
		for (int x = 0; x < img[img_num].w; x++) {
			std::cout << img[img_num].img_pixels[x + y*img[img_num].w];
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

void ImgProc::showCurrentImg() {
	std::cout << "cur img, imgNum = " << curImg << std::endl;
	showImg(curImg);
}

void ImgProc::showModifiedImg() {
	std::cout << "mod img, imgNum = " << 1 - curImg << std::endl;
	showImg(1 - curImg);
}

void ImgProc::updateImg() {
	curImg = 1 - curImg;
}
