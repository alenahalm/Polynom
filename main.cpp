#include "Polynomial.h"

int main() {
    double array[3] = {8, 10, -3};
    double arr[2] = {2, 3};
    Polynomial pol1(2, array);
    Polynomial pol2(1, arr);
    cout << "Polynomial 1:" << endl;
    cout << pol1 << endl;
    cout << "Argument = 5:" << endl;
    cout << pol1.getValueForArg(5) << endl << endl;
    cout << "Derivative 1:" << endl;
    cout << pol1.getDerivative(1) << endl;
    cout << "Integral 1:" << endl;
    cout << pol1.getIntegral() << endl;
    cout << "Polynomial 2:" << endl;
    cout << pol2 << endl;
    cout << "Pol1 + Pol2" << endl;
    cout << pol1 + pol2 << endl;
    cout << "Pol1 / Pol2" << endl;
    cout << pol1 / pol2 << endl;
    cout << "Pol1 * Pol2" << endl;
    cout << pol1 * pol2 << endl;
}
