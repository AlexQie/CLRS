// This file defines the functions to compute Discrete Fourier Transform (DFT)
// of a vector and its inverse Discrete Fourier Transform (IDFT). If you want
// to know the details of the DFT and FFT algorithm, please refer to chapter. 30
// of CLRS book.

// DFT: the naive O(n^2) DFT algorithm
// IDFT: the naive O(n^2) IDFT algorithm
// FFT: the O(nlogn) DFT algorithm
// IFFT: the O(nlogn) IDFT algorithm
//--------------------------------------CAUTION-----------------------------------------
// In this file, the FFT and the IFFT functions can only handle the situation when the
// length of the input vector is power of 2. Thus, please DO NOT use these codes in your
// project:).
//------------------------------------CAUTION END---------------------------------------
// Wrote by Qie Chunguang, 12th, Dec, 2017

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


vector<complex<double>> FFT(vector<complex<double>> vec) {
    int n = vec.size();
    if (n == 1) {
        return vec;
    }
    vector<complex<double>> vec_odd(n / 2);
    vector<complex<double>> vec_even(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        vec_odd[i] = vec[2 * i + 1];
        vec_even[i] = vec[2 * i];
    }

    vector<complex<double>> fft_odd = FFT(vec_odd);
    vector<complex<double>> fft_even = FFT(vec_even);

    complex<double> w(1, 0);
    complex<double> wn = exp(2 * PI * complex<double>(0, 1) / static_cast<double>(n));
    vector<complex<double>> res(n);
    for (int i = 0; i < n / 2; ++i) {
        res[i] = fft_even[i] + w * fft_odd[i];
        res[i + n / 2] = fft_even[i] - w * fft_odd[i];
        w *= wn;
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


vector<complex<double>> IFFT(vector<complex<double>> vec) {
    int n = vec.size();
    if (n == 1) {
        return vec;
    }

    vector<complex<double>> vec_odd(n / 2);
    vector<complex<double>> vec_even(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        vec_odd[i] = vec[2 * i + 1];
        vec_even[i] = vec[2 * i];
    }

    vector<complex<double>> ifft_odd = IFFT(vec_odd);
    vector<complex<double>> ifft_even = IFFT(vec_even);

    complex<double> w(1, 0);
    complex<double> wn = exp(-2 * PI * complex<double>(0, 1) / static_cast<double>(n));
    vector<complex<double>> res(n);
    for (int i = 0; i < n / 2; ++i) {
        res[i] = (ifft_even[i] + w * ifft_odd[i]) / 2.0;
        res[i + n / 2] = (ifft_even[i] - w * ifft_odd[i]) / 2.0;
        w *= wn;
    }

    return res;
}


int main(){
    vector<complex<double>> a = {complex<double>(0, 0), complex<double>(1, 0), complex<double>(2, 0), complex<double>(3, 0)};
//    int data_size = 4096;
//    vector<complex<double>> a(data_size);
//    for (int i = 0; i < data_size; ++i) {
//        double x;
//        cin >> x;
//        a[i] = complex<double>(x, 0);
//    }

    vector<complex<double>> res = DFT(a);
    cout << "DFT result:" << endl;
    for (int i = 0; i < static_cast<double>(res.size()); ++i) {
        cout << res[i] << " ";
    }
    cout << endl;

    vector<complex<double>> ires = IDFT(res);
    cout << "IDFT result:" << endl;
    for (int i = 0; i < static_cast<double>(ires.size()); ++i) {
        cout << ires[i] << " ";
    }
    cout << endl;


    cout << "FFT result:" << endl;
    vector<complex<double>> fft_res = FFT(a);
    for (int i = 0; i < static_cast<double>(fft_res.size()); ++i) {
        cout << fft_res[i] << " ";
    }
    cout << endl;

    cout << "IFFT result:" << endl;
    vector<complex<double>> ifft_res = IFFT(fft_res);
    for (int i = 0; i < static_cast<double>(ifft_res.size()); ++i) {
        cout << ifft_res[i] << " ";
    }
    cout << endl;


    return 0;
}
