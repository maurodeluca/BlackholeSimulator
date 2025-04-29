#include "LensingMath.hpp"
#include <limits>
#include <boost/math/quadrature/trapezoidal.hpp>

using namespace std;
using boost::math::quadrature::trapezoidal;

namespace Lensing {

    double radial_potential(double r, double b) {
        return pow(r, 4) - pow(b, 2) * pow(r, 2) + 2 * pow(b, 2) * r;
    }

    double minrs(double b) {
        using cplx = complex<double>;
        cplx term = pow(b, 2);
        cplx sqrtTerm = sqrt(cplx(1.0) - term / 27.0);
        cplx c1 = pow(-1.0 + sqrtTerm, 1.0 / 3.0);
        cplx c2 = pow(-1.0 - sqrtTerm, 1.0 / 3.0);
        cplx temp = pow(term, 1.0 / 3.0) * (c1 + c2);
        return (abs(temp.imag()) < 1e-10) ? temp.real() : 0.0;
    }

    double d_phi_dr(double r, double b) {
        return b / sqrt(radial_potential(r, b));
    }

    double d_phi_dx(double x, double b, double rt) {
        double xsq = x * x;
        double denom1 = xsq + rt;
        double insideSqrt = -((b * b * (-2.0 + xsq + rt)) / denom1) + pow(denom1, 2);

        if (insideSqrt <= 0.0) return 0.0; // Avoid NaNs or complex sqrt

        return -2.0 * b * abs(x) / (denom1 * sqrt(insideSqrt));
    }

    double phi(double rs, double b) {
        auto integrand = [b](double r) {
            return d_phi_dr(r, b);
            };
        return trapezoidal(integrand, rs, 1e6, 1e-6); // upper bound chosen arbitrarily
    }

    static double transformed(double t, double b, double rt, double c) {
        if (t <= 0.0 || t >= 1.0) return 0.0; // avoid division by zero
        double x = c + (1.0 - t) / t;
        double dxdt = -1.0 / (t * t);
        return d_phi_dx(x, b, rt) * dxdt;
    }

    double phi_from_x(complex<double> xi, double b) {
        using cplx = complex<double>;
        double rt = minrs(b);

        if (imag(cplx(xi)) != 0.0) {
            return numeric_limits<double>::infinity();
        }

        auto integrand = [b, rt](double t) {
            return transformed(t, b, rt, 0.0);
        };

        if (rt == 0.0 && xi.real() < 0.0) {
            return trapezoidal(integrand, 0.0, 1.0, 1e-6);
        }

        double c = real(xi);

        auto integrand2 = [b, rt, c](double t) {
            return transformed(t, b, rt, c);
        };

        return trapezoidal(integrand2, 0.0, 1.0, 1e-6);
    }

    double psi(double phi, double theta) {
        return acos(sin(theta) * sin(phi));
    }

    double varphi(double phi, double theta) {
        double cosPhi = cos(phi);
        double cosTheta = cos(theta);
        double sinPhi = sin(phi);
        double denominator = sqrt(cosPhi * cosPhi + cosTheta * cosTheta * sinPhi * sinPhi);

        if (denominator == 0.0) return 0.0;

        return acos(cosPhi / denominator);
    }

} // namespace Lensing
