#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>


using namespace std;

const double PI = 3.1415926;


template<typename T>
T compute_poly(vector<T> poly, T val) {
    T res = 0;
    int n = poly.size();
    T cur = 1;
    for (int i = 0; i < n; ++i) {
        res += cur * poly[i];
        cur *= val;
    }

    return res;
}


vector<complex<double>> DFT(vector<complex<double>> vec) {
    int n = vec.size();
    vector<complex<double>> res(n);
    complex<double> ci(0, 1);

    for (int i = 0; i < n; ++i) {
        double dn = static_cast<double>(n);
        double di = static_cast<double>(i);
        double exp_num = 2.0 * PI * di / dn;
        complex<double> cur_root = exp(ci * exp_num);
        res[i] = compute_poly(vec, cur_root);
    }

    return res;
}

vector<complex<double>> IDFT(vector<complex<double>> vec) {
    int n = vec.size();
    vector<complex<double>> res(n);
    complex<double> ci(0, 1);

    for (int i = 0; i < n; ++i) {
        double dn = static_cast<double>(n);
        double di = static_cast<double>(i);
        double exp_num = -2.0 * PI * di / dn;
        complex<double> cur_root = exp(ci * exp_num);
        res[i] = compute_poly(vec, cur_root) / dn;
    }

    return res;
}


int main(){
    vector<complex<double>> a = {complex<double>(0, 0), complex<double>(1, 0), complex<double>(2, 0), complex<double>(3, 0)};

    vector<complex<double>> res = DFT(a);
    for (int i = 0; i < static_cast<double>(res.size()); ++i) {
        cout << res[i] << " ";
    }
    cout << endl;

    complex<double> b(0, 1);
    cout << 2.0 * b << endl;

    vector<complex<double>> ires = IDFT(res);

    for (int i = 0; i < static_cast<double>(ires.size()); ++i) {
        cout << ires[i] << " ";
    }
    cout << endl;


    return 0;
}
