#include <iostream>
#include <math.h>
#include <random>

double f(const double& x) {
    double f = pow(x, 2) * exp(sin(x));
    return f;
}

double fm(const double& x) {
    double f = (pow(x, 2) * exp(sin(x))) * (sin(5 * x));
    return f;
}
double randPoint(int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(a, b);
    return dist(gen);
}

double P(double Ti, double f, double fi) {
    double P = pow(2.7, (-(fi - f)) / Ti);
    return P;
}
void table(std::string type) {
    const double Tmin = 0.1, Tmax = 10000;
    double x, xi, Ti = Tmax, ff, ffi;
    int i = 0;
    x = randPoint(9, 14);
    double mini = x, min = { type == "унимодальная" ? f(x) : fm(x) };
    std::cout << " N       T             x         f(x)\n";
    while (Ti > Tmin) {
        i++;
        xi = randPoint(7, 10);
        if (type == "унимодальная") {
            ff = f(x);
            ffi = f(xi);
        }
        else {
            ff = fm(x);
            ffi = fm(xi);
        }
        if (ffi <= ff) {
            x = xi;
        }
        else {
            if (randPoint(0, 1) < P(Ti, ff, ffi))
                x = xi;
        }
        if (ff < min) {
            min = { type == "унимодальная" ? f(x) : fm(x) };
            mini = x;
        }
        std::cout.width(7);
        std::cout << i;
        std::cout.width(12);
        std::cout << Ti;
        std::cout.width(12);
        std::cout << x;
        std::cout.width(12);
        std::cout << ff << '\n';
        Ti *= 0.95;
    }
    std::cout << "Result Xmin = " << mini << " Fmin = " << min << '\n';
}
int main() {
    std::cout.setf(std::ios::left);
    table("унимодальная");
    table("модальная");
    return 0;
}