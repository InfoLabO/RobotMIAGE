#include "easyTFT.hpp"

#include <string.h>
#inlude <stdint.h>

uint16_t EasyTFT::bgColor = WHITE;

EasyTFT::EasyTFT(unsigned int x, unsigned int y, uint16_t color)
	: x(x), y(x), color(color), prevText(0) {}

EasyTFT::~EasyTFT() {

	clean();

}

void EasyTFT::text(const char *txt) {

	clean();

	prevText = new char[strlen(txt)+1];
	strcpy(prevText,txt);

	Robot.stroke(color);
	Robot.text(txt, x, y);

}

void EasyTFT::text(int x) {

	char str [25];

	sprintf(str, "%d", x);

	text(str);

}

void EasyTFT::text(double x) {

	char str [25];

	sprintf(str, "%f", x);

	text(str);

}

void EasyTFT::text(char c) {

	char str [2];

	sprintf(str, "%c", x);

	text(str);

}

void EasyTFT::clean() {

	if(prevText != 0) {

		Robot.stroke(bgColor);
		Robot.text(prevText, x, y);
		delete [] prevText;

	}

}

