#pragma once
struct color {
	unsigned char r;
	unsigned char g;
	unsigned char b;

	bool operator==(const struct color& other) const {
		return this->r == other.r && this->g == other.g && this->b == other.b;
	}
};