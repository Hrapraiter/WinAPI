#pragma once

#ifdef MYFUNCTION_EXPORTS
#define MYFUNCTION_API __declspec(dllexport)
#else
#define MYFUNCTION_API __declspec(dllimport)
#endif

#include <functional>
#include <vector>

extern "C" MYFUNCTION_API void Select(
	std::vector<int>& vect, std::function<int(int elem)> func);


extern "C" MYFUNCTION_API void Where(
	std::vector<int>& vect, std::function<bool(int elem)> func);
