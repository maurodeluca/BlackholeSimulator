# 🌀 Blackhole Simulator

**BlackholeSimulator** is a C++ simulation of a black hole that visually recreates the stunning effects of gravitational lensing and relativistic orbital motion, inspired by scientific visuals such as those in *Interstellar*. The simulation uses accurate physics equations and real-time 2D projection of 3D motion using [SFML](https://www.sfml-dev.org/).

---

## 🚀 Features

- 🌌 **Gravitational lensing**: Simulates light bending using geodesics in Schwarzschild spacetime.
- 🛰️ **3D particle motion**: Orbits and trajectories are calculated in spherical coordinates and projected into 2D space.
- 🧠 **Numerical integration** of relativistic equations (e.g., φ(x), ψ(φ, θ), etc.).
- 🔄 **Real-time simulation loop** using SFML.
- 📏 **Configurable camera tilt** and orbital parameters.
- ✨ **Particle trail rendering** that moves realistically around the black hole.

---

## 📸 Preview

> _[Optional: Insert a screenshot or a gif of the simulation running]_

---

## 🔧 Requirements

- C++17 or later
- [SFML 3.0+](https://www.sfml-dev.org/download.php)
- CMake 3.10+

---

## 🛠️ Build Instructions

1. **Clone the repo:**
   ```bash
   git clone https://github.com/yourusername/BlackholeSimulator.git
   cd BlackholeSimulator
   ```

2. **Configure and build with CMake:**
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

3. **(Optional) Copy SFML DLLs to the build directory (Windows only):**
   Copy the following DLLs from your SFML `bin/` folder to the `build/` output directory:
   - `sfml-graphics-2.dll`
   - `sfml-window-2.dll`
   - `sfml-system-2.dll`

---

## 🧪 Controls

| Key       | Action                      |
|-----------|-----------------------------|
| Arrow keys | Tilt the camera            |

---

## 🧬 Physics Notes

This simulation numerically integrates light and particle paths in the curved spacetime around a non-rotating black hole (Schwarzschild metric). The lensing is computed via:

- `phi_from_x()`: Integrates the deflection angle from the point of closest approach
- `psi(phi, theta)`: Used to determine angular position on screen
- Lookup tables for matching the bending angle to impact parameter `b`

---

## 📁 Project Structure

```
BlackholeSim/
├── src/
│   ├── main.cpp
│   ├── Particle.cpp
│   ├── LensingMath.cpp
│   └── ...
├── include/
│   ├── Particle.hpp
│   ├── LensingMath.hpp
│   └── ...
├── assets/          # Optional: shaders, textures, etc.
├── CMakeLists.txt
└── README.md
```

---

## 📄 License

GPL v3 License — feel free to use, modify, and contribute!

---

## 🙌 Acknowledgments

- Inspired by Kip Thorne’s *Interstellar* simulations
- Powered by SFML
- Built with love and physics

---

## 📫 Contact

Created by **Mauro De Luca**  
📧 maurodeluca94@gmail.com  
🔗 [github.com/maurodeluca](https://github.com/maurodeluca)
