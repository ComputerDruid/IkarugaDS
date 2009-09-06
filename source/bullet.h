#ifndef BULLET_H //header guard
#define BULLET_H

class bullet {
	public:
		bullet(int xpos, int ypos, int xvel, int yvel, int xacc, int yacc, bool c, bool e);
		int x;
		int y;
		int dx;
		int dy;
		int ax;
		int ay;
		bool color;
		int spritenum;
		bool isenemy;

		bool update();
};
#endif //BULLET_H header guard
