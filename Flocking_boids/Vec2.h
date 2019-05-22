#pragma once
#include <SFML/Graphics.hpp>

struct Vec2 {
	float x, y;
	Vec2() {}
	Vec2(float x, float y) : x(x), y(y) {}
	operator sf::Vector2f() {
		return { x, y };
	}
	const Vec2& operator+ (const Vec2& other) const {
		return {x + other.x, y + other.y};
	}
	const Vec2& operator- (const Vec2& other) const {
		return { x - other.x, y - other.y };
	}
	const Vec2& operator* (const Vec2& other) const {
		return { x * other.x, y * other.y };
	}
	const Vec2& operator/ (const Vec2& other) const {
		return { x / other.x, y / other.y };
	}

	const Vec2& operator+ (float val) const {
		return { x + val, y + val };
	}
	const Vec2& operator- (float val) const {
		return { x - val, y - val };
	}
	const Vec2& operator* (float val) const {
		return { x * val, y * val };
	}
	const Vec2& operator/ (float val) const {
		val += 0.1f;
		return { x / val, y / val };
	}

	void operator+= (const Vec2& other) {
		*this = *this + other;
	}
	void operator-= (const Vec2& other) {
		*this = *this - other;
	}
	void operator*= (const Vec2& other) {
		*this = *this * other;
	}
	void operator/= (const Vec2& other) {
		*this = *this / other;
	}

	void operator+= (float val) {
		*this = *this + val;
	}
	void operator-= (float val) {
		*this = *this - val;
	}
	void operator*= (float val) {
		*this = *this * val;
	}
	void operator/= (float val) {
		*this = *this / val;
	}

	void normalize() {
		*this /= sqrt(x * x + y * y);
	}
};