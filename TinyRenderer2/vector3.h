#pragma once
#include <iostream>
using namespace std;

class vector3 {
	public:

	//��Ҫֱ���ڲ����б����ʼ����vec��x,y,z��
	//ֻ�ܴ��ι�����

	//vector3() {	}
	vector3(const vector3& a) :x(a.x), y(a.y), z(a.z) { }
	vector3(float nx, float ny, float nz) :x(nx), y(ny), z(nz) { }
	//��ʾ������ nx ��ֵ����Ա���� x
	//ֱ��ͨ����ʼ���б�������ֱֵ�Ӹ�ֵ����Ա������
	//������Ҫ���ڹ��캯�����ڽ��и�ֵ����
	~vector3()
	{
		delLog();
	}

	void delLog() {
		std::cout << ("del vector3\n");
	}

	float x, y, z;
	//��� c ���Ե�ϰ�ߣ����ظ�ֵ����������������ã���ʵ����ֵ?
	//���ض�Ԫ��������������vec����
	vector3 operator - ()const {
		return vector3(-x, -y, -z);
	}
	vector3 operator = (const vector3& a) {
		x = a.x; y = a.y; z = a.z;
		return *this;
		//why return *this
	}
	bool operator != (const vector3& a) {
		x = a.x; y = a.y; z = a.z;
		return a.x != y || a.y != y || a.z != z;
	}
	bool operator == (const vector3& a) {
		return a.x == y && a.y == y && a.z == z;
	}
	
	vector3  operator + (const vector3& a) {
		return vector3(x + a.x, y + a.y, z + a.z);
	}
	vector3  operator - (const vector3& a) {
		return vector3(x - a.x, y - a.y, z - a.z);
	}
	
	//������
	vector3  operator / (float a) {
		float oneOverA = 1.0f / a;
		return vector3(x * oneOverA, y * oneOverA, z * oneOverA);
	}
	vector3  operator * (float a) {
		return vector3(x * a, y * a, z * a);
	}
	//�����Է������
	vector3& operator +=(const vector3& a) {
		x += a.x; y += a.y; z += a.z; return *this;
	}
	vector3& operator -=(const vector3& a) {
		x -= a.x; y -= a.y; z -= a.z; return *this;
	}
	vector3& operator *=(float a) {
		x *= a; y *= a; z *= a;		
		return *this;
	}
	vector3& operator /=(float a) {
		float oneOverA = 1.0f / a;
		x *=oneOverA; y *=oneOverA; z *= oneOverA;
		return *this;
	}

	void zero() {
		x = y = z = 0.0f;
	}
	void normalize() {
		float magSq = x * x + y * y + z * z;
		if (magSq > 0)
		{
			float oneOverMagSq = 1.0f / magSq;
			x *= oneOverMagSq;
			y *= oneOverMagSq;
			z *= oneOverMagSq;
		}
	}

	float operator * (const vector3 & a) {
		return x * a.x + y * a.y + z * a.z;
	}

};

inline vector3 operator * (float a, const vector3& n) {
	return vector3(a * n.x, a * n.y, a * n.z);
}

inline float vector3Mag(const vector3 &a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline  vector3 crossProduct(const vector3& m, const vector3& n) {
	return vector3(
		m.y * n.z - m.z * n.y,
		m.x * n.z - m.z * n.x,
		m.x * n.y - m.y * n.x
	);
	//x�к���x
}

inline float distance(const vector3& m, const vector3& n) {
	float dx = m.x - n.x;
	float dy = m.y - n.y;
	float dz = m.z - n.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

extern const vector3 glZeroVector;