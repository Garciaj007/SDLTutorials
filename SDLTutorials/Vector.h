#ifndef VECTOR_H
#define VECTOR_H

#include <string>

//Forward Declaration
struct Vector2;
struct Vector3;
struct Vector4;

#ifndef VERY_SMALL
#define VERY_SMALL 1.0E-7F
#endif

//---------------------------------------------- Vector 2 ------------------------------------------------
struct Vector2
{
	//2D Components that can only be changed using const methods
	mutable float x, y;

	//Constructors
	Vector2(float x_, float y_);
	Vector2(const Vector2& v);
	Vector2(const Vector3& v);
	Vector2(const Vector4& v);
	Vector2(float s);
	Vector2();

	//Member Methods
	void Normalize();
	void Set(float x_, float y_) const;
	float Mag();
	float Dot(Vector2 otherV_);
	std::string ToString();

	//Operator Overloads
	Vector2& operator = (const Vector2& v);
	Vector2& operator = (const Vector3& v);
	Vector2& operator = (const Vector4& v);
	Vector2 operator + (const Vector2& v_) const;
	Vector2 operator - (const Vector2& v_) const;
	Vector2 operator * (const float s) const;
	Vector2 operator * (const Vector2& v_) const;
	Vector2 operator / (const float s) const;
	Vector2 operator / (const Vector2& v_) const;
	Vector2 operator += (const Vector2& v_) const;
	Vector2 operator -= (const Vector2& v_) const;
};

//-------------------------------------------------- Vector 3 -------------------------------------------------

struct Vector3 {
	//3D Components that are changeable using const methods
	mutable float x, y, z;

	//Constructors
	Vector3(float x_, float y_, float z_);
	Vector3(const Vector2& otherV_);
	Vector3(const Vector3& otherV_);
	Vector3(const Vector4& otherV_);
	Vector3(float s);
	Vector3();

	//Member Methods
	void Normalize();
	void Set(float x_, float y_, float z_) const;
	float Mag();
	float Dot(Vector3 otherV_);
	Vector3 Cross(Vector3 otherVec_);
	std::string ToString();

	//Operator Overloads
	Vector3& operator = (const Vector2& v_);
	Vector3& operator = (const Vector3& v_);
	Vector3& operator = (const Vector4& v_);
	Vector3 operator + (const Vector3& v_) const;
	Vector3 operator - (const Vector3& v_) const;
	Vector3 operator * (const float s) const;
	Vector3 operator * (const Vector3& v_) const;
	Vector3 operator / (const float s) const;
	Vector3 operator / (const Vector3& v_) const;
	Vector3 operator += (const Vector3& v_) const;
	Vector3 operator -= (const Vector3& v_) const;
};

//------------------------------------------------- Vector 4 ------------------------------------------------

struct Vector4 {
	//4D Components that are only changed by const methods
	mutable float x, y, z, w;

	//Constructors 
	Vector4(float x_, float y_, float z_, float w_);
	Vector4(const Vector2& otherV_);
	Vector4(const Vector3& otherV_);
	Vector4(const Vector4& otherV_);
	Vector4(float s);
	Vector4();

	//Member Methods 
	void Normalize();
	void Set(float x_, float y_, float z_, float w_) const;
	float Mag();
	float Dot(Vector4 otherV_);
	std::string ToString();

	//Operator Overloads
	void operator - ()const;
	Vector4& operator = (const Vector2& v_);
	Vector4& operator = (const Vector3& v_);
	Vector4& operator = (const Vector4& v_);
	Vector4 operator + (const Vector4& v_) const;
	Vector4 operator - (const Vector4& v_) const;
	Vector4 operator * (const float s) const;
	Vector4 operator * (const Vector4& v_) const;
	Vector4 operator / (const float s) const;
	Vector4 operator / (const Vector4& v_) const;
	Vector4 operator += (const Vector4& v_) const;
	Vector4 operator -= (const Vector4& v_) const;
};

#endif

