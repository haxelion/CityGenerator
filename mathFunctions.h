#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <ctime>
#include <cstdlib>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int rand(int min, int max);
double randUniform();
double randNormal(double mean = 0.0, double std = 1.0);
int min(int a, int b);
int max(int a, int b);
float maxf(float a, float b);

#endif
