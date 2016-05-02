// algorithms_final_project.cpp : Defines the entry point for the console application.
//

#include <map> //For map
#include <iostream> // For cout
#include <algorithm> // For std::min_element, std::sort
#include <vector> // For std::vector
#include <iterator> // For begin() and end()
#include <functional> // for std::bind
#include <chrono> 
#include <random>
#include <string> // For std::string, std::to_string
#include <iomanip> // For std::setprecision
#include <math.h> // For atan2
#include <tuple> // For std::tie

using namespace std;
using namespace std::chrono;

struct point {
	bool operator ==(const point& p) {
		return (this->x == p.x) && (this->y == p.y);
	}
	bool operator !=(const point& p) {
		return !(*this == p);
	}
	float x, y;
};

std::vector<point> merge_hulls(std::vector<point> const& left, std::vector<point> const& right) {
	std::vector<point> convex_hull_points;
	auto left_point = [](point const& p1, point const& p2) {
		return p1.x < p2.x;
	};




	return convex_hull_points;
}

std::vector<point> divide_and_conquer(std::vector<point> points) {
	std::vector<point> convex_hull_points;
	auto min_x_coordinate = [](point const& p1, point const& p2) {
		if (p1.x == p2.x) {
			return p1.y < p2.y;
		}
		else {
			return p1.x < p2.x;
		}
	};
	if (points.size() <= 3) {
		convex_hull_points = points;
	}
	else {

		size_t mid = points.size() / 2;
		std::nth_element(points.begin(), points.begin() + mid, points.end(), min_x_coordinate);
		std::vector<point> left_points(points.begin(), points.begin() + mid);
		std::vector<point> right_points(points.begin() + mid, points.end());
		std::vector<point> hull_a = divide_and_conquer(left_points);
		std::vector<point> hull_b = divide_and_conquer(right_points);



	}

	return convex_hull_points;
}

std::vector<point> jarvis_march(std::vector<point> points) {
	std::vector<point> convex_hull_points;
	auto left_or_right_turn_function = [](point const& p1, point const& p2, point const& p3) {
		//right turn if > 0, left turn if < 0, and collinear if 0
		return ((p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y));
	};
	auto min_x_coordinate = [](point const& p1, point const& p2) {
		if (p1.x == p2.x) {
			return p1.y < p2.y;
		}
		else {
			return p1.x < p2.x;
		}
	};
	point endpoint;
	point min_point = *std::min_element(points.begin(), points.end(), min_x_coordinate);
	point hull_point = min_point;
	auto i = 0;
	do {
		convex_hull_points.push_back(hull_point);
		endpoint = points[0];
		for (int j = 1; j < points.size(); j++) {
			if ((left_or_right_turn_function(convex_hull_points.back(), endpoint, points[j]) < 0)) {
				endpoint = points[j];
				i = j;
			}
		}
		points.erase(points.begin() + i);
		hull_point = endpoint;
	} while (endpoint != convex_hull_points[0]);

	return convex_hull_points;
}




std::vector<point> graham_scan(std::vector<point> points) {
	std::vector<point> convex_hull_points;
	auto min_y_coordinate = [](point const& p1, point const& p2) {
		if (p1.y == p2.y) {
			return p1.x < p2.x;
		}
		else {
			return p1.y < p2.y;
		}
	};
	auto min_y = *std::min_element(points.begin(), points.end(), min_y_coordinate);
	//convex_hull_points.push_back(min_y);
	auto left_or_right_turn_function = [](point const& p1, point const& p2, point const& p3) {
		//right turn if > 0, left turn if < 0, and collinear if 0
		return ((p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y));
	};
	auto angle_comparison = [&min_y](point const& p1, point const& p2) {
		auto angle = [&min_y](point const& p) {
			return atan2(p.y - min_y.y, p.x - min_y.x);
		};
		auto distance = [&min_y](point const& p) {
			return sqrt((p.y - min_y.y)*(p.y - min_y.y) + (p.x - min_y.x)*(p.x - min_y.x));
		};
		auto angle_one = angle(p1);
		auto angle_two = angle(p2);
		auto distance_one = distance(p1);
		auto distance_two = distance(p2);
		if (angle_one == angle_two) {
			return distance_one < distance_two;
		}
		else {
			return angle_one < angle_two;
		}
	};
	std::sort(points.begin(), points.end(), angle_comparison);
	convex_hull_points.push_back(points[0]);
	convex_hull_points.push_back(points[1]);
	convex_hull_points.push_back(points[2]);
	for (int i = 3; i < points.size(); i++) {
		while (left_or_right_turn_function(convex_hull_points[convex_hull_points.size() - 2], convex_hull_points.back(), points[i]) > 0)
			convex_hull_points.pop_back();
		convex_hull_points.push_back(points[i]);
	}
	return convex_hull_points;
}


int test_correctness_of_graham_scan() {
	std::vector<point> coordinates;
	auto add_point = [&coordinates](float x, float y) {
		point p;
		p.x = x;
		p.y = y;
		coordinates.push_back(p);
	};
	float values[8][2] = { { 0.f, 3.f },{ 1.f, 1.f },{ 2.f, 2.f },{ 4.f, 4.f },{ 0.f, 0.f },{ 1.f, 2.f },{ 3.f, 1.f },{ 3.f, 3.f } };
	for (int i = 0; i < 8; i++) {
		add_point(values[i][0], values[i][1]);
	}
	std::vector<point> hull = jarvis_march(coordinates);
	std::for_each(hull.begin(), hull.end(), [](point const& p) {std::cout << std::fixed << std::setprecision(2) << p.x << " " << p.y << std::endl;});
	return 1;
}
/*
expected output:
0.00 0.00
3.00 1.00
4.00 4.00
0.00 3.00
*/
int main() {
	test_correctness_of_graham_scan();
}

/*
std::map<int, std::string> integer_strings(){
std::map<int, std::string> integer_map;
integer_map[1000] = " one thousand ";
integer_map[10000] = " ten thousand ";
integer_map[100000] = " one hundred thousand ";
integer_map[1000000] = " one million ";
integer_map[10000000] = " ten million ";
integer_map[100000000] = " one hundred million ";
integer_map[1000000000] = " one hundred million ";
return integer_map;
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
std::map<int, std::string> integer_map = integer_strings();
for (size_t i = 3; i < 5; i++) {
numbers_of_points = (size_t)std::pow(10, i);
length_string = integer_map[numbers_of_points];

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
coordinates.push_back(coordinate);
}

start_time = std::chrono::high_resolution_clock::now();//get the start time
convex_hull_graham_scan = graham_scan(coordinates);
end_time = std::chrono::high_resolution_clock::now(); // get the end time
duration_graham_scan = std::chrono::duration_cast<microseconds>(end_time - start_time);
std::cout << std::fixed << std::setprecision(2) << " Duration of graham scan using " << length_string.c_str() << " points, in range " << "(" << min_range << "," << min_range << ") to " "(" << max_range << "," << max_range << ") : " << duration_graham_scan.count() << " ms" << std::endl;

start_time = std::chrono::high_resolution_clock::now();//get the start time
convex_hull_jarvis_march = jarvis_march(coordinates);
end_time = std::chrono::high_resolution_clock::now(); // get the end time
duration_jarvis_march = std::chrono::duration_cast<microseconds>(end_time - start_time);
std::cout << std::fixed << std::setprecision(2) << " Duration of jarvis march using " << length_string.c_str() << " points, in range " << "(" << min_range << "," << min_range << "," << ") to " "(" << max_range << "," << max_range << ") : " << duration_jarvis_march.count() << " ms" << std::endl;

start_time = std::chrono::high_resolution_clock::now();//get the start time
convex_hull_divide_and_conquer = divide_and_conquer(coordinates);
end_time = std::chrono::high_resolution_clock::now(); // get the end time
duration_divide_and_conquer = std::chrono::duration_cast<microseconds>(end_time - start_time);
std::cout << std::fixed << std::setprecision(2) << " Duration of divide and conquer using " << length_string.c_str() << " points, in range " << "(" << min_range << "," << min_range << "," << ") to " "(" << max_range << "," << max_range << ") : " << duration_divide_and_conquer.count() << " ms" << std::endl;
}
}
return 0;
}
*/
