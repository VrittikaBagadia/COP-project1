#include "View.h"
#include "Edg3.h"
#include "Loop.h"

#include "OpenGL.h"
class construct3d
{
	Vert3 vposs[1000];
	Edg3 eposs[100]; // or try eposs[1000][1000]
	Loop lposs[100];
	
	void find3dvert2view(View top, View front);
	void find3dvert3view(View top, View front, View side);
	void enumedge3d();//3 do, check validity

	void findplane();
	void findcloseloop();
	void classifyloop();
	void checkcontainment(); //designate each loop as a face as well
	void hiddentest();
	void twoplanetest();
	void createsubobjets_classify();
	void displayPossibilities();
}
