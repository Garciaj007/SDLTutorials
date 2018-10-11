#ifndef VECTOR_H
#define VECTOR_H

#include <string>

//Defining Structs
struct Vector2;
struct Vector3;
struct Vector4;

//---------------------------------------------- Vector 2 ------------------------------------------------
struct Vector2
{
	//2D Components that can only be changed using const methods
	mutable float x, y;

	//Constructors
	Vector2(float x_, float y_);
	Vector2(Vector3 otherV_);
	Vector2(Vector4 otherV_);
	Vector2();

	//Member Methods
	void Normalize();
	void Set(float x_, float y_) const;
	float Mag();
	float Dot(Vector2 otherV_);
	std::string ToString();
		  
	//Operator Overloads
	Vector2 operator + (const Vector2& v_) const;
	Vector2 operator - (const Vector2& v_) const;
	Vector2 operator * (const float s) const;
	Vector2 operator * (const Vector2& v_) const;
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
	Vector3(Vector2 otherV_);
	Vector3(Vector4 otherV_);
	Vector3();

	//Member Methods
	void Normalize();
	void Set(float x_, float y_, float z_) const;
	float Mag();
	float Dot(Vector3 otherV_);
	Vector3 Cross(Vector3 otherVec_);
	std::string ToString();

	//Operator Overloads
	Vector3 operator + (const Vector3& v_) const;
	Vector3 operator - (const Vector3& v_) const;
	Vector3 operator * (const float s) const;
	Vector3 operator * (const Vector3& v_) const;
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
	Vector4(Vector2 otherV_);
	Vector4(Vector3 otherV_);
	Vector4();

	//Member Methods 
	void Normalize();
	void Set(float x_, float y_, float z_, float w_) const;
	float Mag();
	float Dot(Vector4 otherV_);
	std::string ToString();

	//Operator Overloads
	Vector4 operator + (const Vector4& v_) const;
	Vector4 operator - (const Vector4& v_) const;
	Vector4 operator * (const float s) const;
	Vector4 operator * (const Vector4& v_) const;
	Vector4 operator / (const Vector4& v_) const;
	Vector4 operator += (const Vector4& v_) const;
	Vector4 operator -= (const Vector4& v_) const;
};
#endif

