#include "ship.h"
#include "bullet.h"
#include "global.h"
#include <PA9.h>
#include "gfx/all_gfx.h"

ship::ship() {
	x = 112;
	y = 352;
	shieldsize = 64;
	isWhite=true;
	shieldshrinking = false;
	shieldgrowing = false;
	
	PA_DualLoadSpritePal(SHIP, (void*)ikaruga_Pal);
	PA_DualCreateSprite(SHIP, (void*)ikaruga_Sprite, OBJ_SIZE_32X32, COLOR256, SHIP, x, y);
	PA_DualStartSpriteAnim(SHIP, LIGHT, LIGHT, 1);
	
	PA_DualLoadSpritePal(SHIELD, (void*)shield_Pal);
	PA_DualCreateSprite(SHIELD, (void*)shield_Sprite, OBJ_SIZE_64X64, COLOR256, SHIELD, x-16, y-16);
	PA_DualStartSpriteAnim(SHIELD, LIGHT, LIGHT, 1);
	
	PA_DualSetSpriteRotEnable(SHIELD, SHIELD);
}
void ship::switchColor() {
	if(!shieldshrinking && !shieldgrowing) {
		shieldsize -= 2;
		shieldshrinking = true;
	}
	else if(shieldshrinking) {
		shieldsize -= 2;
		if(shieldsize == 0) {
			PA_DualStartSpriteAnim(SHIP, !CURRENTCOLOR, !CURRENTCOLOR, 1);
			PA_DualStartSpriteAnim(SHIELD, CURRENTCOLOR, CURRENTCOLOR, 1);
			isWhite = !isWhite;
			shieldshrinking = false;
			shieldgrowing = true;
		}
	}
	else if(shieldgrowing) {
		shieldsize += 2;
		if(shieldsize == 64) shieldgrowing = false;
	}
}
void ship::updateBullets() {
	std::vector<bullet*> temp;
	for(int n = 0; n < (int)bullets.size(); n++) {
		if(bullets[n] -> update()) temp.push_back(bullets[n]);
		else delete bullets[n];
	}
	bullets = temp;
}
void ship::update(){
	if(Pad.Newpress.B || shieldshrinking || shieldgrowing) switchColor();
	if(Pad.Newpress.A) bullets.push_back(new bullet(x+12, y, 0, -5, CURRENTCOLOR));

	int dx = 3*(Pad.Held.Right-Pad.Held.Left);
	int dy = 3*(Pad.Held.Down-Pad.Held.Up);

	x += dx;
	y += dy;

	if(x > 224) x = 224;
	if(x < 0) x = 0;
	if(y > 352) y = 352;
	if(y < 0) y = 0;

	updateBullets();

	PA_DualSetSpriteXY(SHIP, x, y);
	PA_DualSetSpriteXY(SHIELD, x-16, y-16);
	PA_DualSetRotsetNoAngle(SHIELD, (96-shieldsize)*8, (96-shieldsize)*8);
}
