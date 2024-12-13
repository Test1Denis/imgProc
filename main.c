#include <iostream>
#include "img_proc.h"

void test_ImgProc_dilatation() {

	ImgProc test;
	test.dilatation();
	test.showCurrentImg();
	test.showModifiedImg();
	test.updateImg();
	test.dilatation();
	test.showCurrentImg();
	test.showModifiedImg();

}


int main() {
	test_ImgProc_dilatation();
}
