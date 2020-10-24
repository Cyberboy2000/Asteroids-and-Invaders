#include "Rand.h"
#include <limits>
#include <stdexcept>
#include <cstdint>

//a, b and c chosen as recommended by Sebastiano Vigna
constexpr uint64_t a = 24;
constexpr uint64_t b = 16;
constexpr uint64_t c = 37;

//Double precision floats have 1 sign bit, 11 bits of exponent, and 52 bits of mantissa
constexpr int signAndExponentSize = 12;

//xoroshiro128+ implementation for C++
//Based on David Blackman and Sebastiano Vigna's C implementation (http://vigna.di.unimi.it/xorshift/xoroshiro128plus.c)
//Has a period of 2^128-1

inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

uint64_t Rand::Next() {
	uint64_t x = z;
	uint64_t y = w;

	y ^= x;
	z = rotl(x, a) ^ y ^ (y << b);
	w = rotl(x, c);

	return z + w;
}

//Interface functions

int Rand::Int(int a, int b) {
	if (b < a) {
		throw new std::invalid_argument(b + " < " + a);
	}
	uint32_t v;
	uint32_t n = (uint32_t)(b - a);
	uint32_t max = UINT_MAX - (UINT_MAX % n);
	do {
		uint64_t u = Next();
		v = (uint32_t)(u >> 32);
	} while (v >= max);

	return (int)(a + v % n);
}

double Rand::Double(double a, double b) {
	uint64_t mantissa = Next() >> signAndExponentSize;
	double one = 1;
	uint64_t exponent = *(uint64_t*)(&one);
	uint64_t binaryExpr = exponent + mantissa;
	double val = *(double*)& binaryExpr;
	return a + (b - a) * (val - 1);
}

float Rand::Float(float a, float b) {
	return (float)Double(a, b);
}

Rand::Rand(uint64_t seed0, uint64_t seed1) : z(seed0), w(seed1) {
	if (z == 0 && w == 0) {
		w = 1;
	}
}