
#ifndef LENSING_MATH_HPP
#define LENSING_MATH_HPP

#include <cmath>
#include <complex>

namespace Lensing {

	// Computes the radial potential: r⁴ - b²·r² + 2·b²·r
	double radial_potential(double r, double b);

	// Returns the minimum r (real root of a cubic equation)
	double minrs(double b);

	// dφ/dr
	double d_phi_dr(double r, double b);

	// dφ/dx used for offset impact parameters
	double d_phi_dx(double x, double b, double rt);

	// φ(rs, b) = ∫ dφ/dr from rs to ∞
	double phi(double rs, double b);

	// φ(xi, b) = ∫ dφ/dx from ∞ to xi
	double phi_from_x(std::complex<double> xi, double b);

	// ψ(φ, θ) = arccos(sin(θ) * sin(φ))
	double psi(double phi, double theta);

	// φ(φ, θ) = arccos(cos(φ) / sqrt(cos²(φ) + cos²(θ) * sin²(φ)))
	double varphi(double phi, double theta);

} // namespace Lensing

#endif // LENSING_MATH_HPP
