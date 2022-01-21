#include "Polynomial.h"
#include <vector>

Polynomial::Polynomial(int pow, double *coef) {
    power = pow;
    coefficients = new double[pow + 1];
    for (int i = 0; i < pow + 1; ++i) {
        coefficients[i] = coef[i];
    }
}

double Polynomial::getValueForArg(double a) {
    double value = 0;
    for (int i = 0; i < power + 1; ++i) {
        int arg = 1;
        for (int j = 0; j < power - i; ++j) {
            arg *= a;
        }
        value += coefficients[i] * arg;
    }
    return value;
}

Polynomial operator+(Polynomial pol1, Polynomial pol2) {
    int pow;
    double* arr;
    if (pol1.power > pol2.power) {
        pow = pol1.power;
    }
    else {
        pow = pol2.power;
    }
    arr = new double[pow + 1];
    int coefIndex = pol1.power;
    for (int i = 0; i < pol1.power + 1; ++i) {
        arr[i] += pol1.coefficients[coefIndex];
        coefIndex--;
    }
    coefIndex = pol2.power;
    for (int i = 0; i < pol2.power + 1; ++i) {
        arr[i] += pol2.coefficients[coefIndex];
        coefIndex--;
    }
    for (int i = 0, j = pow; i < (pow + 1) / 2; ++i, --j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    int empty = 0;
    for (int i = 0; i < pow + 1; ++i) {
        if (arr[i] == 0) {
            empty++;
        }
        else {
            break;
        }
    }
    pow -= empty;
    double array[pow + 1];
    for (int i = 0; i < pow + 1; ++i) {
        array[i] = arr[i + empty];
    }
    return Polynomial(pow, array);
}

Polynomial operator-(Polynomial pol1, Polynomial pol2) {
    return pol1 + (-1) * pol2;
}

Polynomial operator*(Polynomial pol1, Polynomial pol2) {
    int pow = pol1.power + pol2.power;
    double arr[pow + 1];
    for (int i = 0; i < pow + 1; ++i) {
        arr[i] = 0;
    }
    for (int i = 0; i < pol1.power + 1; ++i) {
        for (int j = 0; j < pol2.power + 1; ++j) {
            arr[i + j] += pol1.coefficients[i] * pol2.coefficients[j];
        }
    }
    return Polynomial(pow, arr);
}

Polynomial Polynomial::operator=(Polynomial polynomial) {
    return Polynomial(polynomial.power, polynomial.coefficients);
}

ostream &operator<<(ostream &out, Polynomial polynomial) {
    for (int i = 0; i < polynomial.power + 1; ++i) {
        if (polynomial.coefficients[i] == 0) {
            continue;
        }
        if ((polynomial.coefficients[i] == 1 || polynomial.coefficients[i] == -1) && polynomial.power - i > 0) {
            if (polynomial.coefficients[i] > 0) {
                cout <<"+";
            }
            else {
                cout << "-";
            }
            cout <<"x";
            continue;
        }
        if (polynomial.coefficients[i] > 0 && i > 0) {
            cout<<"+";
        }
        cout << polynomial.coefficients[i];
        if (polynomial.power - i > 0) {
            cout <<"x";
            if (polynomial.power - i != 1) {
                cout <<"^"<<polynomial.power-i;
            }
        }
    }
    cout << endl;
}

Polynomial operator*(Polynomial pol, double num) {
    Polynomial polynomial(pol.power, pol.coefficients);
    for (int i = 0; i < pol.power + 1; ++i) {
        polynomial.coefficients[i] *= num;
    }
    return polynomial;
}

Polynomial operator*(double num, Polynomial pol) {
    return pol * num;
}

Polynomial Polynomial::getDerivative(int order) {
    double array[power];
    for (int i = 0; i < power; ++i) {
        array[i] = coefficients[i] * (power - i);
    }
    if (order == 1) {
        return Polynomial(power - 1, array);
    }
    else {
        return Polynomial(power - 1, array).getDerivative(order - 1);
    }
}

Polynomial Polynomial::getIntegral() {
    double arr[power + 2];
    for (int i = 0; i < power + 2; ++i) {
        if (i == power + 1) {
            arr[i] = 0;
            break;
        }
        arr[i] = coefficients[i] / (power - i + 1);
    }
    return Polynomial(power + 1, arr);
}

Polynomial operator/(Polynomial pol1, Polynomial pol2) {
    vector<Polynomial> left;
    left.push_back(Polynomial(pol1.power, pol1.coefficients));
    int index = 0;
    vector< pair<int, double> > result;
    while(left[index].power >= pol2.power) {
        pair<int, double> monomial;
        monomial.first = left[index].power - pol2.power;
        monomial.second = left[index].coefficients[0] / pol2.coefficients[0];
        double arr[monomial.first + 1];
        arr[0] = monomial.second;
        for (int i = 1; i < monomial.first + 1; ++i) {
            arr[i] = 0;
        }
        result.push_back(monomial);
        left.push_back(left[index] - (pol2 * Polynomial(monomial.first, arr)));
        index++;

    }
    int pow = result[0].first;
    double arr[pow + 1];
    for (int i = 0; i < pow + 1; ++i) {
        arr[i] = result[i].second;
    }
    return Polynomial(pow, arr);
}

bool difSign(double a, double b) {
    if (a * b < 0) {
        return true;
    }
    return false;
}

vector<double> Polynomial::getRoots(double e, double a, double b) {
    vector<double> roots;
    if (power == 0) return roots;
    if (power == 1) {
        double x = -coefficients[1] / coefficients[0];
        if (a <= x && x <= b) {
            roots.push_back(x);
        }
    }
    else if (power == 2) {
        double D = coefficients[1] * coefficients[1] - 4 * coefficients[0] * coefficients[2];
        double x = (-coefficients[1] + sqrt(D)) / (2 * coefficients[0]);
        if (a <= x && x <= b) {
            roots.push_back(x);
        }
        x = (-coefficients[1] - sqrt(D)) / (2 * coefficients[0]);
        if (a <= x && x <= b) {
            roots.push_back(x);
        }
    }
    else {
        double left = a, right = b;
        double middle;
        while ((right) - (left) > e) {
            middle = (left + right) / 2;
            if (difSign(getValueForArg(left), getValueForArg(middle))) {
                right = middle;
            }
            else {
                left = middle;
            }
            if (getValueForArg(middle) == 0) {
                break;
            }
        }
        roots.push_back(middle);

    }
    return roots;
}
