#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <iomanip>

class Student;

double inputGrade(int studentNum, int subjectNum);
std::vector<double> calculateStudentAverages(const std::vector<Student*>& students);
std::vector<double> calculateSubjectAverages(const std::vector<Student*>& students, int M);
int findStudentWithMaxAverage(const std::vector<double>& studentAverages);
bool saveToFile(const std::string& filename, const std::vector<Student*>& students, int M);

#endif