#pragma once
#include "DxLib.h"

extern double dvlp_x, dvlp_y, rls_x, rls_y;

int DrawGraph_Ex(int, int, int , int );
int DrawExtendGraph_Ex(double , double , double , double , int , int );
int DrawLine_Ex(double , double , double , double , unsigned int );
int DrawBox_Ex(double, double, double, double, unsigned int, int);

int GetTime();
int ElapsedTime(int start_time);