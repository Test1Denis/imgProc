#ifndef _img_proc_h_
#define _img_proc_h_

#include <iostream>
#include <fstream>
#include <cstring>



/*
 *
 */
struct Img {
	int* img_pixels;
	int w;
	int h;
	
	int _x_core; //координаты центарльного пикселя для маски
	int _y_core;

	Img();
	Img(int x_core, int y_core);
	~Img() {
		delete [] img_pixels;
	}
};

class ImgProc  {
	private :
		Img *mask;
		Img img[2];
		int curImg {0};

		void showImg(int img_num);
		void clearUpdatedImg();
		void copyMask(int, int);

	public :
		ImgProc() {
			mask = new Img(0,0);
			int t = 0;
			//reset buffered image
			while(t++ < img[1].w * img[1].h) {
				img[1].img_pixels[t] = 0x00;
			}
		}
		~ImgProc() {
			delete mask;
		}

		void dilatation();
		void erosian();

		void updateImg();

		void showCurrentImg();
		void showModifiedImg();
		void setMask(const Img& new_mask);

};


#endif

