#include "Myfunc.h"

double dvlp_x, dvlp_y, rls_x, rls_y;

int DrawGraph_Ex(int x, int y, int GrHandle, int TransFlag) {

	return DrawGraph(x, y, GrHandle, TransFlag);

};

int DrawExtendGraph_Ex(double x1, double y1, double x2, double y2, int GrHandle, int TransFlag) {

	return DrawExtendGraph((int)(x1 / dvlp_x*rls_x), (int)(y1 / dvlp_y*rls_y), (int)(x2 / dvlp_x*rls_x), (int)(y2 / dvlp_y*rls_y), GrHandle, TransFlag);

}

int DrawLine_Ex(double x1, double y1, double x2, double y2, unsigned int Color) {

	return DrawLine((int)(x1 / dvlp_x*rls_x), (int)(y1 / dvlp_y*rls_y), (int)(x2 / dvlp_x*rls_x), (int)(y2 / dvlp_y*rls_y), Color);

}

int DrawBox_Ex(double x1,double y1,double x2,double y2,unsigned int Color,int FillFlag) {
	
	return DrawBox((int)(x1 / dvlp_x*rls_x), (int)(y1 / dvlp_y*rls_y), (int)(x2 / dvlp_x*rls_x), (int)(y2 / dvlp_y*rls_y), Color, FillFlag);
}

int GetTime() {
	return GetNowCount();
}

int ElapsedTime(int start_time) {
	return GetNowCount() - start_time;
}
