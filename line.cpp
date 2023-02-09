#include "line.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <memory>
#include <future>
#include <omp.h>
#include <map>

using namespace std;

#define pi 3.14159265358979323846

// функция для 6 задания (параллельная)
template <typename T>
auto omp_accumulate(const T& curves, int64_t init) {
    int64_t sum = init;

    #pragma omp parallel for reduction(+:sum)
    for(auto it = curves.begin(); it != curves.end(); ++it) {
        sum += it->get()->GetRadius();
    }

    return sum;
}

int main() {
    list<unique_ptr<Curve>> curves;

    // 2 

    // для рандома
    random_device rd;
    mt19937 gen(rd()); 
    uniform_int_distribution<> curve_distr(1, 3); // для выбора кривой
    uniform_int_distribution<> radius_distr(1, 10000); // определяем диапазон радиусов
    uniform_int_distribution<> step_distr(1, 10); // для шага спирали
    uniform_int_distribution<> center_distr(-100, 100); // для центров
    uniform_int_distribution<> t_distr(0, 314); // для производных

    for (size_t i = 0; i < 15; ++i)
    {
        int type = curve_distr(gen);
        switch(type)
        {
            case 1:
                curves.emplace_back(make_unique<Circle>(center_distr(gen), center_distr(gen), radius_distr(gen)));
                break;
            case 2:
                curves.emplace_back(make_unique<Ellipse>(center_distr(gen), center_distr(gen), radius_distr(gen), radius_distr(gen)));
                break;
            case 3:
                curves.emplace_back(make_unique<Spiral>(center_distr(gen), center_distr(gen), radius_distr(gen), step_distr(gen)));
                break;
        }
    }

    // 1
    cout << "Evaluating first 15 curves derivatives at random parameter" << endl;
    vector3d derivative;
    double parameter;
    for (auto it = curves.begin(); it != curves.end(); ++it)
    {
        cout << "Curve #" << distance(curves.begin(), it) + 1 << " is";
        if (dynamic_cast<Circle*>(it->get()) != nullptr)
            cout << " Circle ";
        else if (dynamic_cast<Ellipse*>(it->get()) != nullptr)
            cout << " Ellipse ";
        else if (dynamic_cast<Spiral*>(it->get()) != nullptr)
            cout << " Spiral ";
        parameter = t_distr(gen) / 100.0;
        cout << "with derivative at parameter: " << parameter << " with coordinates: ";
        derivative = it->get()->der1(parameter);
        cout << "x = " << derivative.x << ", y = " << derivative.y << ", z = " << derivative.z << endl;
    }

    // 3
    cout << "Evaluating first 15 curves at point pi/4" << endl;
    vector3d xyz;
    parameter = pi/4;
    for (auto it = curves.begin(); it != curves.end(); ++it)
    {
        cout << "Curve #" << distance(curves.begin(), it) + 1 << " is";
        if (dynamic_cast<Circle*>(it->get()) != nullptr)
            cout << " Circle ";
        else if (dynamic_cast<Ellipse*>(it->get()) != nullptr)
            cout << " Ellipse ";
        else if (dynamic_cast<Spiral*>(it->get()) != nullptr)
            cout << " Spiral ";
        cout << "with coordinates : ";
        xyz = it->get()->equation(parameter);
        cout << "x = " << xyz.x << ", y = " << xyz.y << ", z = " << xyz.z << endl;
    }

    // 4
    list<unique_ptr<Curve>> circles;
    for (auto it = curves.begin(); it != curves.end(); ++it) {
        if (dynamic_cast<Circle*>(it->get()) != nullptr) {
            auto temp_it = it;
            ++it;
            circles.splice(circles.end(), curves, temp_it);
        }
    }

    // 5
    circles.sort([](auto& lhs, auto& rhs) {
        return lhs->GetRadius() < rhs->GetRadius();
    });
    cout << "Circles after sorting: " << endl;
    for (auto it = circles.begin(); it != circles.end(); ++it) {
        cout << "Circle #" << distance(circles.begin(), it) << " with radius: " ;
        cout << it->get()->GetRadius() << endl;
    }
    // 6 
    cout << endl << "Sum of curves radiuses in container: " << omp_accumulate(curves, 0) << endl;
}