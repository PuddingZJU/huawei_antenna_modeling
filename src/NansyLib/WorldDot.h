#ifndef WORLDDOT_H
#define WORLDDOT_H

#include "WindowDot.h"

class WorldDot
{
	/*
	�������ڴ洢��obj�ļ���ֱ�Ӷ�ȡ�Ķ������꣬���⣬��obj�ļ���ֱ�Ӷ�ȡ������
	����Ƭ����һ��WorldDot�������������е�3��WorldDot����ʾ��
	*/
public:
	WorldDot();
	WorldDot(double d1, double d2, double d3, QRgb c, double n[3]);
	WorldDot(double d1, double d2, double d3, QRgb c);
	WorldDot(WorldDot*);
	~WorldDot();
	double GetX() {return x;};
	double GetY() {return y;};
	double GetZ() {return z;};
	QRgb GetColor() {return color;};
	void SetXYZ(double d1, double d2, double d3);
	void SetColor(QRgb c);
	void SetNorm(double d[3]);
	void GetNorm(double out[3]);
	void setTex(double d[2]);
	void getTex(double d[2]);
	void fromWorldDot(WorldDot*);

	int getIdx() const { return m_idx; }
	void setIdx(int val) { m_idx = val; }

private:
	double x, y, z;
	QRgb color;
	double norm[3];
	double tex[2];
	int m_idx;
	
};

#endif