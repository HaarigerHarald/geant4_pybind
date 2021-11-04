#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TsitourasRK45.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4TsitourasRK45 : public G4TsitourasRK45, public py::trampoline_self_life_support {
public:
   using G4TsitourasRK45::G4TsitourasRK45;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4TsitourasRK45, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4TsitourasRK45, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4TsitourasRK45, IntegratorOrder, ); }
};

void export_G4TsitourasRK45(py::module &m)
{
   py::class_<G4TsitourasRK45, PyG4TsitourasRK45, G4MagIntegratorStepper>(m, "G4TsitourasRK45")

      .def(py::init<G4EquationOfMotion *, G4int, G4bool>(), py::arg("EqRhs"), py::arg("numberOfVariables") = 6,
           py::arg("primary") = true)

      .def("Stepper", &G4TsitourasRK45::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("SetupInterpolation", &G4TsitourasRK45::SetupInterpolation)
      .def("Interpolate", &G4TsitourasRK45::Interpolate, py::arg("yInput"), py::arg("dydx"), py::arg("Step"),
           py::arg("yOut"), py::arg("tau"))

      .def("DistChord", &G4TsitourasRK45::DistChord)
      .def("IntegratorOrder", &G4TsitourasRK45::IntegratorOrder);
}
