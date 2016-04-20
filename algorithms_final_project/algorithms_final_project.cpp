// algorithms_final_project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm> // For std::min_element, std::sort
#include <vector> // For std::vector
#include <iterator> // For begin() and end()
#include <functional> // for std::bind
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

struct point {
	float x, y, z;
};

std::vector<point> graham_scan(std::vector<point> points) {
	std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();//get the start time
	std::vector<point> convex_hull_points;
	auto lowest_y_coordinate = std::min_element(points.begin(), points.end(), [](point const& p1, point const& p2)
	{
		return p1.y < p2.y;
	});
	auto angle_comparison_lambda_function = [](point const& p1, point const& p2, point const& the_lowest_y_coordinate_point_found_on_the_last_line) {
		auto find_angle_of_two_points = [](point const& p1, point const& p2) {

			return 1;
		};
		auto angle_of_p1_and_origin = find_angle_of_two_points(p1, the_lowest_y_coordinate_point_found_on_the_last_line);
		auto angle_of_p2_and_origin = find_angle_of_two_points(p2, the_lowest_y_coordinate_point_found_on_the_last_line);
		return angle_of_p1_and_origin < angle_of_p2_and_origin;
	};
	std::sort(points.begin(), points.end(), std::bind(angle_comparison_lambda_function, std::placeholders::_1, std::placeholders::_2, lowest_y_coordinate));
	auto left_or_right_turn_function = [](point const& p) {


	};
	std::for_each(points.begin() + 1, points.end(), left_or_right_turn_function);




	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now(); // get the end time
	auto duration = std::chrono::duration_cast<microseconds>(end_time - start_time).count();
	return convex_hull_points;
}



int main()
{

	return 0;
}



