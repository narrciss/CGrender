#pragma once
class matrix3
{
public:
	float x1, x2, x3;
	float y1, y2, y3;
	float z1, z2, z3;
	
	//init
	matrix3() {};
	matrix3(const matrix3& a)
		: x1(a.x1), x2(a.x2), x3(a.x3),
		y1(a.y1), y2(a.y2), y3(a.y3),
		z1(a.z1), z2(a.z2), z3(a.z3) {};
	matrix3(float nx1, float nx2, float nx3,
		float ny1, float ny2, float ny3,
		float nz1, float nz2, float nz3)
		:x1(nx1), x2(nx2), x3(nx3),
		y1(ny1), y2(ny2), y3(ny3),
		z1(nz1), z2(nz2), z3(nz3) {};

	//一元，关系
	matrix3 operator - () const{
		return matrix3(
			-x1, -x2, -x3,
			-y1, -y2, -y3,
			-z1, -z2, -z3
		);
	}
	matrix3 operator = (const matrix3& a) {
		x1 = a.x1; x2 = a.x2; x3 = a.x3;
		y1 = a.y1; y2 = a.y2; y3 = a.y3,
		z1 = a.z1; z2 = a.z2; z3 = a.z3;
		return *this;
	}
	bool operator == (const matrix3& a) {
		return
			x1 == a.x1 && x2 == a.x2 && x3 == a.x3 &&
			y1 == a.y1 && y2 == a.y2 && y3 == a.y3 &&
			z1 == a.z1 && z2 == a.z2 && z3 == a.z3;
	}
	bool operator != (const matrix3& a) {
		return
			x1 != a.x1 || x2 != a.x2 || x3 != a.x3 ||
			y1 != a.y1 || y2 != a.y2 || y3 != a.y3 ||
			z1 != a.z1 || z2 != a.z2 || z3 != a.z3;
	}

	//标量
	matrix3 operator + (const matrix3& a) {		
			x1+=a.x1; x2+=a.x2; x3+=a.x3;
			y1+=a.y1; y2+=a.y2; y3+=a.y3;
			z1 += a.z1; z2 += a.z2; z3 += a.z3;
			return *this;
	}
	matrix3 operator - (const matrix3& a) {		
		return matrix3(x1 - a.x1, x2 - a.x2, x3 - a.x3,
		y1 - a.y1, y2 - a.y2, y3 - a.y3,
		z1 - a.z1, z2 - a.z2, z3 - a.z3
		);
	}
	matrix3 operator * (float a) {
		return matrix3(
			x1 * a, x2 * a, x3 * a,
			y1 * a, y2 * a, y3 * a,
			z1 * a, z2 * a, z3 * a
		);
	}
	matrix3 operator / (float a) {
		float oneOverA = 1.0f / a;
		return matrix3(
			x1 * oneOverA, x2 * oneOverA, x3 * oneOverA,
			y1 * oneOverA, y2 * oneOverA, y3 * oneOverA,
			z1 * oneOverA, z2 * oneOverA, z3 * oneOverA
		);
	}

	//自反
	matrix3 operator += (const matrix3& a) {
		x1 + a.x1; x2 + a.x2; x3 + a.x3;
		y1 + a.y1; y2 + a.y2; y3 + a.y3;
		z1 + a.z1; z2 + a.z2; z3 + a.z3;
		return *this;
	}
	matrix3 operator -= (const matrix3& a) {
		x1 - a.x1; x2 - a.x2; x3 - a.x3;
		y1 - a.y1; y2 - a.y2; y3 - a.y3;
		z1 - a.z1; z2 - a.z2; z3 - a.z3;
		return *this;
	}
	matrix3 operator *= (float a) {		
			x1 *= a; x2 *= a; x3 *= a;
			y1 *= a; y2 *= a; y3 *= a;
			z1 *= a; z2 *= a; z3 *= a;
			return *this;
	}
	matrix3 operator /= (float a) {
		x1 /= a; x2 /= a; x3 /= a;
		y1 /= a; y2 /= a; y3 /= a;
		z1 /= a; z2 /= a; z3 /= a;
		return *this;
	}

	//dotProduct
	matrix3 operator * (const matrix3& a) {
		float c11 = x1 * a.x1 + x1 * a.y1 + x1 * a.z1;
		float c12 = x1 * a.x2 + x1 * a.y2 + x1 * a.z2;
		float c13  = x1 * a.x3 + x1 * a.y3 + x1 * a.z3;

		float c21 = x2 * a.x1 + x2 * a.y1 + x2 * a.z1;
		float c22 = x2 * a.x2 + x2 * a.y2 + x2 * a.z2;
		float c23 = x2 * a.x3 + x2 * a.y3 + x2 * a.z3;

		float c31 = x3 * a.x1 + x3 * a.y1 + x3 * a.z1;
		float c32 = x3 * a.x2 + x3 * a.y2 + x3 * a.z2;
		float c33 = x3 * a.x3 + x3 * a.y3 + x3 * a.z3;
		return matrix3(
			c11, c12, c13,
			c21, c22, c23,
			c31, c32, c33
		);
		//多逗号会导致类型错误
	}

	//转置 transpose

	//逆 inverse

};
inline matrix3 transpose(const matrix3& a) {
	return matrix3(a.x1, a.y1, a.z1,
		a.x2, a.y2, a.z2,
		a.x3, a.y3, a.z3);
}
inline float determinant(const matrix3& a) {
	return a.x1 * (a.y2 * a.z3 - a.z2 * a.y3)
		+ a.x2 * (a.y1 * a.z3 - a.z1 * a.y1)
		+ a.x3 * (a.y1 * a.z2 - a.z1 * a.y2);
}
inline matrix3 identety() {
	return matrix3(1.0f, 0, 0,
		0, 1.0f, 0,
		0, 0, 1.0f);
}
inline matrix3 inverse(const matrix3& a) {
	//代数余子式
	float c11 = a.x1*(a.y2 * a.z3 - a.z2 * a.y3);
	float c12 = -a.x2 * (a.y1 * a.z3 - a.z1 * a.y1);
	float c13 = a.x3 * (a.y1 * a.z2 - a.z1 * a.y2);

	float c21 = -a.y1 * (a.x2 * a.z3 - a.z2 * a.x3);
	float c22 = a.y2 * (a.x1 * a.z3 - a.z1 * a.x1);
	float c23 = -a.y3 * (a.x1 * a.z2 - a.z1 * a.x2);

	float c31 = a.z1 * (a.y2 * a.x3 - a.x2 * a.y3);
	float c32 = -a.z2 * (a.y1 * a.x3 - a.x1 * a.y1);
	float c33 = a.z3 * (a.y1 * a.x2 - a.x1 * a.y2);
	//转置
	matrix3 b(c11, c21, c31,
		c12, c22, c32,
		c13, c23, c33);
		//行列式
	float oneOverDeterminant = 1.0f / determinant(b);
	return b * oneOverDeterminant;
}

//左乘
//标量乘
//运算重载
//单位，求逆，转置，求行列式
//向量表示矩阵
//基向量
