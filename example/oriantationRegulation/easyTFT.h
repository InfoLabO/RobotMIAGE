#pragma once

#include <ArduinoRobot.h>

class EasyTFT {


	public:

		static uint16_t bgColor;

		EasyTFT(unsigned int x, unsigned int y, uint16_t color = BLACK);
		~EasyTFT();

		void text(const char *txt);
		void text(int x);
		void text(double x);
		void text(char c);

		void clean();

	private:

		const int x;
		const int y;
		const uint16_t color;

		char * prevText;

};

