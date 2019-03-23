typedef complex<double> base;

void fft (vector<base> & a, bool invert) {
    int n = (int) a.size();
    if (n == 1)  return;

    vector<base> a0 (n/2), a1 (n/2);
    for (int i=0, j=0; i<n; i+=2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i+1];
    }
    fft (a0, invert);
    fft (a1, invert);

    double ang = 2*PI/n * (invert ? -1 : 1);
    base w (1), wn (cos(ang), sin(ang));
    for (int i=0; i<n/2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i+n/2] = a0[i] - w * a1[i];
        if (invert)
            a[i] /= 2, a[i+n/2] /= 2;
        w *= wn;
    }
}

/// Let's take two polynomial whom we want to multiply:
/// 1: ax^0 + cx^1 + px^2 + dx^3 + ax^4
/// 2: bx^0 + bx^1 + ax^2 + cx^3 + px^4
/// Now take two vectors a and b such that,
/// a = [a, c, p, d, a];
/// b = [b, b, a, c, p];
/// Pass the vectors a and b to the function multiply().
/// It will return another vector which contains the coefficient after multiplication.

/// WARNING: FFT causes precision error. multiply() rounds them to long long.
/// Change long long to int depending on inputs.

void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
    vector<base> fa (a.begin(), a.end()), fb (b.begin(), b.end());
    size_t n = 1;
    while (n < max (a.size(), b.size())) n <<= 1;
    n <<= 1;
    fa.resize (n), fb.resize (n);

    fft (fa, false), fft (fb, false);
    for (size_t i=0; i<n; ++i)
        fa[i] *= fb[i];
    fft (fa, true);

    res.resize (n);
    for (size_t i=0; i<n; ++i)
        res[i] = int (fa[i].real() + 0.5);
}
