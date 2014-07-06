#ifndef __VECTOR_H_
#define __VECTOR_H_

#include <cmath>
#include <iostream>

class Vector {
public:
	Vector() : v{0, 0, 0} {};
	Vector(float x, float y, float z) : v{x, y, z} {};
	~Vector() {};

	/**
	 * Basic vector operations
	 */
	const float operator[](int index) const {
		return v[index];
	};
	Vector operator+(const Vector& rhs) const {
		return Vector(v[0] + rhs[0], v[1] + rhs[1], v[2] + rhs[2]);
	}
	Vector operator-(const Vector& rhs) const {
		return Vector(v[0] - rhs[0], v[1] - rhs[1], v[2] - rhs[2]);
	}

	/**
	 * Extended vector operations
	 */
	const float length() const {
		return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	};
	const Vector normalize() const {
		float invlength = 1 / this->length();
		return Vector(v[0] * invlength, v[1] * invlength, v[2] * invlength);
	}
	const float operator*(const Vector& rhs) const {
		return	v[0] * rhs[0] +
				v[1] * rhs[1] +
				v[2] * rhs[2];
	}
	const Vector operator%(const Vector& rhs) const {
		return Vector(	v[1] * rhs[2] - v[2] * rhs[1],
						v[2] * rhs[0] - v[0] * rhs[2],
						v[0] * rhs[1] - v[1] * rhs[0]);
	}
private:
	float v[3];
};

inline Vector operator*(const float factor, const Vector& rhs) {
	return Vector(factor * rhs[0], factor * rhs[1], factor * rhs[2]);
}
inline Vector operator*(const Vector& lhs, const float factor) {
	return factor * lhs;
}
inline std::ostream& operator<<(std::ostream& out, const Vector& rhs) {
	return out << "x: " << rhs[0] << "\ty: " << rhs[1] << "\tz: " << rhs[2];
}

#endif /* VECTOR_H_ */
