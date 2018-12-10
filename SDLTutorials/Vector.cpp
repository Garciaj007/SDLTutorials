#include "Vector.h"
#include <math.h>
//------------------------------------------------------- Vector 2 ----------------------------------------------------------

//Create Vector at 0,0

Vector2::Vector2() {
	Set(0, 0);
}

Vector2::Vector2(float s = float(0.0)) {
	Set(s, s);
}

//Create Vector at x,y
Vector2::Vector2(float x_, float y_) {
	Set(x_, y_);
}

Vector2::Vector2(const Vector2& v) {
	Set(v.x, v.y);
}

//Create Vector2 from Vector3
Vector2::Vector2(const Vector3& v) {
	Set(v.x, v.y);
}

//Create Vector2 from Vector4
Vector2::Vector2(const Vector4& v) {
	Set(v.x, v.y);
}

//Normalize Vector
void Vector2::Normalize() {
	Set(x / Mag(), y / Mag());
}

//Set Vector 
void Vector2::Set(float x_,float y_) const {
	x = x_;
	y = y_;
}

//Get Magnitude
float Vector2::Mag() {
	return sqrtf((x * x) + (y * y));
}

//Get Dot Product
float Vector2::Dot(Vector2 otherV_) {
	return (x * otherV_.x) + (y * otherV_.y);
}

//Convert to String
std::string Vector2::ToString() {
	return "[" + std::to_string(x) + "," + std::to_string(y) + "]";
}

Vector2& Vector2::operator=(const Vector2& v_) {
	Set(v_.x, v_.y);
	return *this;
}

Vector2& Vector2::operator=(const Vector3& v_) {
	Set(v_.x, v_.y);
	return *this;
}

Vector2& Vector2::operator=(const Vector4& v_) {
	Set(v_.x, v_.y);
	return *this;
}

//Add Vector Components
Vector2 Vector2::operator + (const Vector2& v_) const{
	Vector2 temp(x + v_.x, y + v_.y);
	return temp;
}

//Subtract Vector Components
Vector2 Vector2::operator - (const Vector2& v_) const{
	Vector2 temp(x - v_.x, y - v_.y);
	return temp;
}

//Multiply Vector Components by Scalar
Vector2 Vector2::operator * (const float s) const{
	Vector2 temp(x * s, y * s);
	return temp;
}

//Multiply Vector Components
Vector2 Vector2::operator * (const Vector2& v_) const{
	Vector2 temp(x * v_.x, y * v_.y);
	return temp;
}

Vector2 Vector2::operator / (const float s) const {
	Vector2 temp(x / s, y / s);
	return temp;
}

//Divide Vector Components
Vector2 Vector2::operator / (const Vector2& v_) const{
	Vector2 temp(x / v_.x, y / v_.y);
	return temp;
}

//Adds and Assigns Vector Components
Vector2 Vector2::operator += (const Vector2& v_) const {
	Vector2 temp(x += v_.x, y += v_.y);
	return temp;
}

//Subtracts and Assigns Vector Components
Vector2 Vector2::operator -= (const Vector2& v_) const {
	Vector2 temp(x -= v_.x, y -= v_.y);
	return temp;
}

//-------------------------------------------------------- Vector3 ---------------------------------------------------------------

//Creates Vector at 0,0,0
Vector3::Vector3() {
	Set(0, 0, 0);
}

Vector3::Vector3(float s) {
	Set(s, s, s);
}

//Creates Vector at x,y,z values
Vector3::Vector3(float x_, float y_, float z_) {
	Set(x_, y_, z_);
}

//Creates a 3D Vector using 2D Vector
Vector3::Vector3(const Vector2& otherV_) {
	Set(otherV_.x, otherV_.y, 0);
}

Vector3::Vector3(const Vector3& otherV_) {
	Set(otherV_.x, otherV_.y, otherV_.z);
}

//Creates a 3D Vector using 4D Vector 
Vector3::Vector3(const Vector4& otherV_) {
	Set(otherV_.x, otherV_.y, otherV_.z);
}

//Normalizes Vector
void Vector3::Normalize() {
	Set(x / Mag(), y / Mag(), z / Mag());
}

//Sets Vector
void Vector3::Set(float x_, float y_, float z_) const {
	x = x_;
	y = y_;
	z = z_;
}

//Gets Vector Magnitude
float Vector3::Mag() {
	return sqrtf((x * x) + (y * y) + (z * z));
}

float Vector3::Dot(Vector3 otherV_) {
	return (x * otherV_.x) + (y * otherV_.y) + (z * otherV_.z);
}

Vector3 Vector3::Cross(Vector3 v_) {
	Vector3 temp((y * v_.z) - (z * v_.y), (z * v_.x) - (x * v_.z), (x * v_.y) - (y * v_.x));
	return temp;
}

std::string Vector3::ToString() {
	return "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
}

Vector3& Vector3::operator=(const Vector2& v_) {
	Set(v_.x, v_.y, 0.0);
	return *this;
}

Vector3& Vector3::operator=(const Vector3& v_) {
	Set(v_.x, v_.y, v_.z);
	return *this;
}

Vector3& Vector3::operator=(const Vector4& v_) {
	Set(v_.x, v_.y, v_.z);
	return *this;
}

Vector3 Vector3::operator + (const Vector3& v_) const {
	Vector3 temp(x + v_.x, y + v_.y, z + v_.z);
	return temp;
}

Vector3 Vector3::operator - (const Vector3& v_) const {
	Vector3 temp(x - v_.x, y - v_.y, z - v_.z);
	return temp;
}

Vector3 Vector3::operator * (const float s) const {
	Vector3 temp(x * s, y * s, z * s);
	return temp;
}

Vector3 Vector3::operator * (const Vector3& v_) const {
	Vector3 temp(x * v_.x, y * v_.y, z * v_.z);
	return temp;
}

Vector3 Vector3::operator/(const float s) const {
	Vector3 temp(x / s, y / s, z / s);
	return temp;
}

Vector3 Vector3::operator / (const Vector3& v_) const {
	Vector3 temp(x / v_.x, y / v_.y, z / v_.z);
	return temp;
}

Vector3 Vector3::operator += (const Vector3& v_) const {
	Vector3 temp(x += v_.x, y += v_.y, z += v_.z);
	return temp;
}

Vector3 Vector3::operator -= (const Vector3& v_) const {
	Vector3 temp(x -= v_.x, y -= v_.y, z -= v_.z);
	return temp;
}

//---------------------------------------------------------- Vector 4 ----------------------------------------------------------------
Vector4::Vector4() {
	Set(0,0,0,0);
}

Vector4::Vector4(float s) {
	Set(s, s, s, s);
}

Vector4::Vector4(float x_, float y_, float z_, float w_) {
	Set(x_, y_, z_, w_);
}

Vector4::Vector4(const Vector2& otherV_) {
	Set(otherV_.x, otherV_.y, 0, 0);
}

Vector4::Vector4(const Vector3& otherV_) {
	Set(otherV_.x, otherV_.y, otherV_.z, 0);
}

Vector4::Vector4(const Vector4& otherV_) {
	Set(otherV_.x, otherV_.y, otherV_.z, otherV_.w);
}

void Vector4::Normalize() {
	Set(x / Mag(), y / Mag(), z / Mag(), w / Mag());
}

void Vector4::Set(float x_, float y_, float z_, float w_) const {
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

float Vector4::Mag() {
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

float Vector4::Dot(Vector4 otherV_) {
	return (x * otherV_.x) + (y * otherV_.y) + (z * otherV_.z) + (w * otherV_.w);
}

std::string Vector4::ToString() {
	return "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," + std::to_string(w) + "]";
}

Vector4& Vector4::operator = (const Vector2& v_) {
	Set(v_.x, v_.y, 0, 0);
	return *this;
}

Vector4& Vector4::operator = (const Vector3& v_) {
	Set(v_.x, v_.y, v_.z, 0);
	return *this;
}

Vector4& Vector4::operator = (const Vector4& v_) {
	Set(v_.x, v_.y, v_.z, v_.w);
	return *this;
}

Vector4 Vector4::operator + (const Vector4& v_) const {
	Vector4 temp(x + v_.x, y + v_.y, z + v_.z, w + v_.w);
	return temp;
}

void Vector4::operator-()const {
	x = -x; y = -y; z = -z; w = -w;
}

Vector4 Vector4::operator - (const Vector4& v_) const {
	Vector4 temp(x - v_.x, y - v_.y, z - v_.z, w - v_.w);
	return temp;
}

Vector4 Vector4::operator * (const float s) const {
	Vector4 temp(x * s, y * s, z * s, w * s);
	return temp;
}

Vector4 Vector4::operator * (const Vector4& v_) const {
	Vector4 temp(x * v_.x, y * v_.y, z * v_.z, w * v_.w);
	return temp;
}

Vector4 Vector4::operator/ (const float s) const {
	Vector4 temp(x / s, y / s, z / s, w / s);
	return temp;
}

Vector4 Vector4::operator / (const Vector4& v_) const {
	Vector4 temp(x / v_.x, y / v_.y, z / v_.z, w / v_.w);
	return temp;
}

Vector4 Vector4::operator += (const Vector4& v_) const {
	Vector4 temp(x += v_.x, y += v_.y, z += v_.z, w += v_.w);
	return temp;
}

Vector4 Vector4::operator -= (const Vector4& v_) const {
	Vector4 temp(x -= v_.x, y -= v_.y, z -= v_.z, w -= v_.w);
	return temp;
}