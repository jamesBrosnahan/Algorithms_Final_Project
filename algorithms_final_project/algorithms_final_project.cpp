// algorithms_final_project.cpp : Defines the entry point for the console application.
//
#define _USE_MATH_DEFINES
#include <cmath> 
#include <fstream> // For fstream
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
#include <sstream>  // std::stringstream
#include <future>// for test functions

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
	/*auto min_x_coordinate = [](point const& p1, point const& p2) {
		if (p1.x == p2.x) {
			return p1.y < p2.y;
		}
		else {
			return p1.x < p2.x;
		}
	};
	switch(points.size()){
	    case 0:
	    case 1:
	        convex_hull_points = points;
	        break;
        case 2:
	        bool temp_right = (points[1].x > points[0].x);
            bool temp_up = points[1].y > points[0].y;
	        auto temp_left_point = temp_right ? points[0] : (up ? points[0] : points[1]);
	        auto temp_right_point = temp_right ? points[1] : (up ? points[1] : points[0]);
	        convex_hull_points.push_back(temp_left_point);
	        convex_hull_points.push_back(temp_right_point);
	        break;
        case 3:
            
            break;
        default:
		    size_t mid = points.size() / 2;
		    std::nth_element(points.begin(), points.begin() + mid, points.end(), min_x_coordinate);
		    std::vector<point> left_points(points.begin(), points.begin() + mid);
		    std::vector<point> right_points(points.begin() + mid, points.end());
		    std::vector<point> hull_a = divide_and_conquer(left_points);
		    std::vector<point> hull_b = divide_and_conquer(right_points);            
            break;
	    }

    */
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
		for (int j = 0; j < points.size(); j++) {
			if ((left_or_right_turn_function(convex_hull_points.back(), endpoint, points[j]) < 0)) {
				endpoint = points[j];
				i = j;
			}
		}
		if (i < points.size() - 1)
		{
			points[i] = std::move(points.back());
		}
		if(points.size() > 0){
		    points.pop_back();
		}
		//points.erase(points.begin() + i);
		hull_point = endpoint;
	} while (endpoint != convex_hull_points[0] && points.size() > 0);

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

int test_correctness_of_jarvis_march() {
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
enum shape{random_shape, circle_shape, triangle_shape, square_shape};
std::string write_points(shape type, size_t number_of_points, size_t radius = 1, std::string file_name = "") {
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution;
	distribution = std::uniform_real_distribution<float>(-1.f * (float)radius, (float)radius);
	auto random_coordinate = std::bind(distribution, generator);
	std::ofstream file;
	auto random_points = [&]() {
		if (file_name == "") {
			file_name = "random_test_case" + std::to_string(number_of_points) + "_" + std::to_string(radius) + ".points";
		}
		file.open(file_name);
		file << number_of_points << std::endl;
		float x, y;
		for (int i = 0; i < number_of_points; i++) {
			x = random_coordinate();
			y = random_coordinate();
			file << std::to_string(x) << " " << std::to_string(y) << std::endl;
		}
		return file_name;
	};
	auto circle_points = [&]() {
		if (file_name == "") {
			file_name = "circle_test_case" + std::to_string(number_of_points) + "_" + std::to_string(radius) + ".points";
		}
		file.open(file_name);
		file << number_of_points << std::endl;
		float degree_increment = ((float)M_PI * 2.f) / (float)number_of_points;
		float x, y, a;
		for (int i = 0; i < number_of_points; i++) {
			a = degree_increment * (float)i;
			x = radius * cos(a);
			y = radius * sin(a);
			file << std::to_string(x) << " " << std::to_string(y) << std::endl;
		}
		return file_name;
	};
	auto square_points = [&]() {
		if (file_name == "") {
			file_name = "triangle_test_case" + std::to_string(number_of_points) + "_" + std::to_string(radius) + ".points";
		}
		file.open(file_name);
		file << number_of_points << std::endl;
		float degree_increment = ((float)M_PI * 2.f) / (float)number_of_points;
		float x, y, a;
		for (int i = 0; i < number_of_points; i++) {
			a = degree_increment * (float)i;
			x = radius * cos(a);
			y = radius * sin(a);
			file << std::to_string(x) << " " << std::to_string(y) << std::endl;
		}

		return file_name;
	};
	auto triangle_points = [&]() {
		if (file_name == "") {
			file_name = "triangle_test_case" + std::to_string(number_of_points) + "_" + std::to_string(radius) + ".points";
		}
		file.open(file_name);
		file << number_of_points << std::endl;
		float degree_increment = ((float)M_PI * 2.f) / (float)number_of_points;
		float x, y, a;
		for (int i = 0; i < number_of_points; i++) {
			a = degree_increment * (float)i;
			x = radius * cos(a);
			y = radius * sin(a);
			file << std::to_string(x) << " " << std::to_string(y) << std::endl;
		}

		return file_name;
	};

	switch (type) {
		case circle_shape:
			file_name = circle_points();
			break;
		case random_shape:
			file_name = random_points();
			break;
		case triangle_shape:
			file_name = triangle_points();
			break;
		case square_shape:
			file_name = square_points();
			break;
	}

	return file_name;
}

std::string write_random_points(size_t number_of_points, size_t radius=1, std::string file_name = ""){
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
    distribution = std::uniform_real_distribution<float>(-1.f * (float)radius, (float)radius);
    auto random_coordinate = std::bind(distribution, generator);
    if(file_name == ""){
        file_name = "random_test_case" + std::to_string(number_of_points) + "_" + std::to_string(radius) +".points";
    }
    std::ofstream file(file_name);
    file << number_of_points << std::endl;
    float x, y;
    for(int i = 0; i < number_of_points; i++){
        x = random_coordinate();
        y = random_coordinate();
        file << std::to_string(x) << " " << std::to_string(y) << std::endl;
    }
    return file_name;
}

std::string write_circle_points(size_t number_of_points, size_t radius=1, std::string file_name = ""){

    if(file_name == ""){
        file_name = "circle_test_case" + std::to_string(number_of_points) + "_" + std::to_string(radius) +".points";
    }
    std::ofstream file(file_name);
    file << number_of_points << std::endl;
    float degree_increment = ((float)M_PI * 2.f) / (float)number_of_points;
    float x, y, a;
    for(int i = 0; i < number_of_points; i++){
        a = degree_increment * (float)i;
        x = radius * cos(a);
        y = radius * sin(a);
        file << std::to_string(x) << " " << std::to_string(y) << std::endl;
    }
    return file_name;
}

std::vector<point> load_file(std::string file_name){
    std::vector<point> points;
    std::ifstream file(file_name);
    std::string value;
    std::stringstream line;
    point temp_point;
    std::getline(file, value);
    size_t number_of_points = (size_t)std::stoi(value);

    
    for(size_t i = 0; i < number_of_points; i++){
        std::getline(file, value);
        line.clear();
        line.str(value);
        std::getline(line, value, ' ');
        temp_point.x = std::stof(value);
        std::getline(line, value, ' ');
        temp_point.y = std::stof(value);
        points.push_back(temp_point);
    }
    return points;
}

void test_jarvis_march() {
    std::chrono::microseconds circle_microseconds, random_microseconds;
    std::ofstream log_file("jarvis_march_log_file.txt");
    size_t number_of_points = 360, radius=5;
    
    std::string file_name;
    std::vector<point> circle_points, random_points, circle_hull, random_hull;
    
    auto convex_hull = [](std::vector<point> &points, std::vector<point> &output_hull) -> std::chrono::microseconds{
        std::chrono::high_resolution_clock::time_point end_time, start_time;
        if(output_hull.size() > 0){
            output_hull.clear();
        }
        start_time = std::chrono::high_resolution_clock::now(); //get the start time
        output_hull = jarvis_march(points); //run algorithm
        end_time = std::chrono::high_resolution_clock::now(); // get the end time
        std::chrono::microseconds microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return microseconds;
    };    
    
    
    
    file_name = write_circle_points(number_of_points, radius);
    circle_points = load_file(file_name);

    file_name = write_random_points(number_of_points, radius);
    random_points = load_file(file_name);
    
    std::future<std::chrono::microseconds> circle_future(std::async(convex_hull, std::ref(circle_points), std::ref(circle_hull)));
    std::future<std::chrono::microseconds> random_future(std::async(convex_hull, std::ref(random_points), std::ref(random_hull)));

    random_microseconds = random_future.get();

    std::cout << std::fixed << std::setprecision(2) << " Duration of Jarvis March using " << number_of_points << " random points with a " << (2 * radius) << " by " << (2 * radius)  << " square completed in " << random_microseconds.count() << " microseconds " << std::endl;
    
    log_file << std::fixed << std::setprecision(2) << " Duration of Jarvis March using " << number_of_points << " random points with a " << (2 * radius) << " by " << (2 * radius)  << " square completed in " << random_microseconds.count() << " microseconds " << std::endl;
    
    circle_microseconds = circle_future.get();
    
    std::cout << std::fixed << std::setprecision(2) << " Duration of Jarvis March with " << number_of_points << " on a circle with radius " << radius << " completed in " << circle_microseconds.count() << " microseconds " << std::endl;
    
    log_file << std::fixed << std::setprecision(2) << " Duration of Jarvis March with " << number_of_points << " on a circle with radius " << radius << " completed in " << circle_microseconds.count() << " microseconds " << std::endl;
    
}

void test_graham_scan() {
    std::chrono::microseconds circle_microseconds, random_microseconds;
    std::ofstream log_file("graham_scan_log_file.txt");
    size_t number_of_points = 360, radius=5;
    
    std::string file_name;
    std::vector<point> circle_points, random_points, circle_hull, random_hull;
    
    auto convex_hull = [](std::vector<point> &points, std::vector<point> &output_hull) -> std::chrono::microseconds{
        std::chrono::high_resolution_clock::time_point end_time, start_time;
        if(output_hull.size() > 0){
            output_hull.clear();
        }
        start_time = std::chrono::high_resolution_clock::now(); //get the start time
        output_hull = graham_scan(points); //run algorithm
        end_time = std::chrono::high_resolution_clock::now(); // get the end time
        std::chrono::microseconds microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return microseconds;
    };    
    
    
    
    file_name = write_circle_points(number_of_points, radius);
    circle_points = load_file(file_name);

    file_name = write_random_points(number_of_points, radius);
    random_points = load_file(file_name);
    
    std::future<std::chrono::microseconds> circle_future(std::async(convex_hull, std::ref(circle_points), std::ref(circle_hull)));
    std::future<std::chrono::microseconds> random_future(std::async(convex_hull, std::ref(random_points), std::ref(random_hull)));

    std::cout << std::fixed << std::setprecision(2) << " Duration of Graham Scan using " << number_of_points << " random points with a " << (2 * radius) << " by " << (2 * radius)  << " square completed in " << random_future.get().count() << " microseconds " << std::endl;
    std::cout << std::fixed << std::setprecision(2) << " Duration of Graham Scan with " << number_of_points << " on a circle with radius " << radius << " completed in " << circle_future.get().count() << " microseconds " << std::endl;
    
}

int main() {
	//test_correctness_of_graham_scan();
	test_graham_scan();
	test_jarvis_march();
	return 1;
}

