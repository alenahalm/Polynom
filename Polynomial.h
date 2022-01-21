#ifndef POLYNOMIAL_POLYNOMIAL_H
#define POLYNOMIAL_POLYNOMIAL_H

#include <iostream>

using namespace std;

class Polynomial {
private:
    int power;
    double* coefficients;
public:
    Polynomial(int pow, double* coef);
    double getValueForArg(double a);
    Polynomial getDerivative(int order);
    Polynomial getIntegral();
    vector<double> getRoots(double e, double a, double b);


    Polynomial operator=(Polynomial polynomial);
    friend Polynomial operator+(Polynomial pol1, Polynomial pol2);
    friend Polynomial operator-(Polynomial pol1, Polynomial pol2);
    friend Polynomial operator*(Polynomial pol1, Polynomial pol2);
    friend Polynomial operator/(Polynomial pol1, Polynomial pol2);
    friend Polynomial operator*(Polynomial pol, double num);
    friend Polynomial operator*(double num, Polynomial pol);

    friend ostream &operator<<(ostream &out, Polynomial pol);
};


#endif //POLYNOMIAL_POLYNOMIAL_H
