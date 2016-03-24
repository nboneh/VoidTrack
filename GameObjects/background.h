#include "../VoidTrack.h"

class Background{
	float r,g,b;
	unsigned int texture;
	public: 
		Background();
		void draw();
		void setColor(float _r,float _g,float _b);

};