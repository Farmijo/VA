#pragma once
class Triangle
{
public:
	union
	{
		struct { unsigned int t[3]; };
		struct { unsigned int a, b, c; };
	};
};