#pragma once
#include<Windows.h>
#include<vector>
#include<functional>
#include<memory>

struct Point
{
	const char* ResourseID;
	INT x;
	INT y;
	Point(const char* ResourseID , INT x , INT y):ResourseID(ResourseID), x(x) , y(y){}
};
class PointCollection
{
	std::vector<Point> points;
public:
	std::unique_ptr<Point> operator[](int index)
	{
		if (index < 0 || index >= points.size())return nullptr;
		return std::make_unique<Point>(points[index]);
	}
	std::unique_ptr<Point> operator[](const char* resourseID)
	{
		std::vector<Point>::iterator iterator;
		if((iterator = std::find_if(points.begin() , points.end() , [&resourseID](Point p){return p.ResourseID == resourseID;})) != points.end())
		{
			return std::make_unique<Point>(*iterator._Ptr);
		}
		return nullptr;
	}
	
	PointCollection() = default;

	void addPoint(const char* resourseID,int x , int y)
	{
		if (resourseID == NULL || resourseID == "")return;

		std::vector<Point>::iterator iterator;
		if ((iterator = std::find_if(points.begin(), points.end(), [&resourseID](Point& p) {return p.ResourseID == resourseID;})) != points.end())
		{
			iterator->x = x;
			iterator->y = y;
			return;
		}
		points.push_back(Point(resourseID, x, y));
	}
	void delPoint(const char* resourseID)
	{
		std::vector<Point>::iterator iterator;
		if ((iterator = std::find_if(points.begin(), points.end(), [&resourseID](Point& p) {return p.ResourseID == resourseID; })) != points.end())
			points.erase(iterator);
	}
	void SelectX(std::function<int(int x)> func)
	{
		for(Point& point : points)
		{
			point.x = func(point.x);
		}
	}
	void SelectY(std::function<int(int y)> func)
	{
		for (Point& point : points)
		{
			point.y = func(point.y);
		}
	}
};