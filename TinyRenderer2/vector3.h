#pragma once
#include <iostream>
using namespace std;

class vector3 {
	public:

	//需要直接在参数列表里初始化，vec（x,y,z）
	//只能带参构造吗

	//vector3() {	}
	vector3(const vector3& a) :x(a.x), y(a.y), z(a.z) { }
	vector3(float nx, float ny, float nz) :x(nx), y(ny), z(nz) { }
	//表示将参数 nx 赋值给成员变量 x
	//直接通过初始化列表将参数的值直接赋值给成员变量，
	//而不需要再在构造函数体内进行赋值操作
	~vector3()
	{
		delLog();
	}

	void delLog() {
		std::cout << ("del vector3\n");
	}

	float x, y, z;
	//坚持 c 语言的习惯，重载赋值运算符，并返回引用，以实现左值?
	//重载二元运算符如何有两个vec参数
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
	
	//标量乘
	vector3  operator / (float a) {
		float oneOverA = 1.0f / a;
		return vector3(x * oneOverA, y * oneOverA, z * oneOverA);
	}
	vector3  operator * (float a) {
		return vector3(x * a, y * a, z * a);
	}
	//重载自反运算符
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
	//x行忽略x
}

inline float distance(const vector3& m, const vector3& n) {
	float dx = m.x - n.x;
	float dy = m.y - n.y;
	float dz = m.z - n.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

extern const vector3 glZeroVector;