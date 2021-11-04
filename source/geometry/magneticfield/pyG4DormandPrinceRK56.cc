#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DormandPrinceRK56.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4DormandPrinceRK56 : public G4DormandPrinceRK56, public py::trampoline_self_life_support {
public:
   using G4DormandPrinceRK56::G4DormandPrinceRK56;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4DormandPrinceRK56, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4DormandPrinceRK56, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4DormandPrinceRK56, IntegratorOrder, ); }
};

void export_G4DormandPrinceRK56(py::module &m)
{
   py::class_<G4DormandPrinceRK56, PyG4DormandPrinceRK56, G4MagIntegratorStepper>(m, "G4DormandPrinceRK56")

      .def(py::init<G4EquationOfMotion *, G4int, G4bool>(), py::arg("EqRhs"), py::arg("numberOfVariables") = 6,
           py::arg("primary") = true)

      .def("Stepper", &G4DormandPrinceRK56::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("DistChord", &G4DormandPrinceRK56::DistChord)
      .def("IntegratorOrder", &G4DormandPrinceRK56::IntegratorOrder)
      .def("SetupInterpolate_low", &G4DormandPrinceRK56::SetupInterpolate_low, py::arg("yInput"), py::arg("dydx"),
           py::arg("Step"))

      .def("Interpolate_low", &G4DormandPrinceRK56::Interpolate_low, py::arg("yInput"), py::arg("dydx"),
           py::arg("Step"), py::arg("yOut"), py::arg("tau"))

      .def("SetupInterpolation", &G4DormandPrinceRK56::SetupInterpolation)
      .def("SetupInterpolate", &G4DormandPrinceRK56::SetupInterpolate, py::arg("yInput"), py::arg("dydx"),
           py::arg("Step"))

      .def("Interpolate",
           py::overload_cast<const G4double *, const G4double *, const G4double, G4double *, G4double>(
              &G4DormandPrinceRK56::Interpolate),
           py::arg("yInput"), py::arg("dydx"), py::arg("Step"), py::arg("yOut"), py::arg("tau"))

      .def("Interpolate", py::overload_cast<G4double, G4double *>(&G4DormandPrinceRK56::Interpolate), py::arg("tau"),
           py::arg("yOut"))

      .def("SetupInterpolate_high", &G4DormandPrinceRK56::SetupInterpolate_high, py::arg("yInput"), py::arg("dydx"),
           py::arg("Step"))

      .def("Interpolate_high", &G4DormandPrinceRK56::Interpolate_high, py::arg("yInput"), py::arg("dydx"),
           py::arg("Step"), py::arg("yOut"), py::arg("tau"));
}
