#pragma once
#include <cstdint>

//xoroshiro128+ implementation for C++
//Based on David Blackman and Sebastiano Vigna's C implementation (http://vigna.di.unimi.it/xorshift/xoroshiro128plus.c)
//Has a period of 2^128-1
class Rand
{
public:
	///<summary>Generate unsigned long.</summary>
	uint64_t Next();
	///<summary>Generate signed integer between a (inclusive) and b (exclusive).</summary>
	int Int(int a, int b);
	///<summary>Generate double precision floating point value between a and b.</summary>
	double Double(double a, double b);
	///<summary>Generate single precision floating point value between a and b.</summary>
	float Float(float a, float b);
	Rand(uint64_t seed0, uint64_t seed1);
private:
	uint64_t z = 0;
	uint64_t w = 1;
};

