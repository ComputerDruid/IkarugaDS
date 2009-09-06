#ifndef SHIP_H //header guard
#define SHIP_H

#include "bullet.h"
#include <vector>

class ship {
	public:
		ship();
		int x;
		int y;
		int shieldsize;
		int reloadtime;
		bool color;
		bool shieldshrinking;
		bool shieldgrowing;
		std::vector<bullet*> bullets;

		void update();
		void switchColor();
};
#endif //SHIP_H header guard
