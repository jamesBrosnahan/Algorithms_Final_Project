// algorithms_final_project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream> // For cout
#include <algorithm> // For std::min_element, std::sort
#include <vector> // For std::vector
#include <iterator> // For begin() and end()
#include <functional> // for std::bind
#include <chrono> 
#include <random>
#include <string> // For std::string, std::to_string
#include <iomanip> // For std::setprecision

using namespace std;
using namespace std::chrono;

struct point {
	float x, y, z;
};

std::vector<point> two_dimension_jarvis_march(std::vector<point> points) {
	std::vector<point> convex_hull_points;


	return convex_hull_points;
}

std::vector<point> two_dimension_divide_and_conquer(std::vector<point> points) {
	std::vector<point> convex_hull_points;


	return convex_hull_points;
}

std::vector<point> two_dimension_graham_scan(std::vector<point> points) {
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

	return convex_hull_points;
}

std::vector<point> jarvis_march(std::vector<point> points) {
	std::vector<point> convex_hull_points;


	return convex_hull_points;
}

std::vector<point> divide_and_conquer(std::vector<point> points) {
	std::vector<point> convex_hull_points;


	return convex_hull_points;
}

std::vector<point> graham_scan(std::vector<point> points) {
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
	/*
	std::sort(points.begin(), points.end(), std::bind(angle_comparison_lambda_function, std::placeholders::_1, std::placeholders::_2, lowest_y_coordinate));
	auto left_or_right_turn_function = [](point const& p) {


	};
	std::for_each(points.begin() + 1, points.end(), left_or_right_turn_function);
	*/

	return convex_hull_points;
}

int main()
{
	std::chrono::high_resolution_clock::time_point end_time, start_time;
	std::vector < point> coordinates;
	std::vector < point> convex_hull_graham_scan, convex_hull_jarvis_march, convex_hull_divide_and_conquer;
	std::string length_string;
	std::chrono::microseconds duration_graham_scan, duration_jarvis_march, duration_divide_and_conquer;
	float min_range, max_range; 
	size_t numbers_of_points;
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution;
	std::function<float()> random_coordinate;

	for (size_t i = 3; i < 5; i++) {
		numbers_of_points = (size_t)std::pow(10, i);
		switch (numbers_of_points) {
		case(1000) :
			length_string = " one thousand ";
			break;
		case(10000) :
			length_string = " ten thousand ";
			break;
		case(100000) :
			length_string = " one hundred thousand ";
			break;
		case(1000000) :
			length_string = " one million ";
			break;
		case(10000000) :
			length_string = " ten million ";
			break;
		case(100000000) :
			length_string = " one hundred million ";
			break;
		case(1000000000) :
			length_string = " one billion ";
			break;
		}
		for (size_t j = 1; j < 2; j++) {
			min_range = -1.f * pow(10.f, (float)j);
			max_range = pow(10.f, (float)j);
			distribution = std::uniform_real_distribution<float>(min_range, max_range);
			random_coordinate = std::bind(distribution, generator);
			if (coordinates.size() > 0) {
				coordinates.clear();
			}
			for (size_t i = 0; i < numbers_of_points; i++) {
				point coordinate;
				coordinate.x = random_coordinate();
				coordinate.y = random_coordinate();
				coordinate.z = random_coordinate();
				coordinates.push_back(coordinate);
			}

			start_time = std::chrono::high_resolution_clock::now();//get the start time
			convex_hull_graham_scan = two_dimension_graham_scan(coordinates);
			end_time = std::chrono::high_resolution_clock::now(); // get the end time
			duration_graham_scan = std::chrono::duration_cast<microseconds>(end_time - start_time);
			std::cout << std::fixed << std::setprecision(2) << " Duration of graham scan using " << length_string.c_str() << " points, in range " << "(" << min_range << "," << min_range << "," << min_range << ") to " "(" << max_range << "," << max_range << "," << max_range << ") : " << duration_graham_scan.count() << " ms" << std::endl;

			start_time = std::chrono::high_resolution_clock::now();//get the start time
			convex_hull_jarvis_march = two_dimension_jarvis_march(coordinates);
			end_time = std::chrono::high_resolution_clock::now(); // get the end time
			duration_jarvis_march = std::chrono::duration_cast<microseconds>(end_time - start_time);
			std::cout << std::fixed << std::setprecision(2) << " Duration of jarvis march using " << length_string.c_str() << " points, in range " << "(" << min_range << "," << min_range << "," << min_range << ") to " "(" << max_range << "," << max_range << "," << max_range << ") : " << duration_jarvis_march.count() << " ms" << std::endl;

			start_time = std::chrono::high_resolution_clock::now();//get the start time
			convex_hull_divide_and_conquer = two_dimension_divide_and_conquer(coordinates);
			end_time = std::chrono::high_resolution_clock::now(); // get the end time
			duration_divide_and_conquer = std::chrono::duration_cast<microseconds>(end_time - start_time);
			std::cout << std::fixed << std::setprecision(2) << " Duration of divide and conquer using " << length_string.c_str() << " points, in range " << "(" << min_range << "," << min_range << "," << min_range << ") to " "(" << max_range << "," << max_range << "," << max_range << ") : " << duration_divide_and_conquer.count() << " ms" << std::endl;
		}
	}
	return 0;
}



