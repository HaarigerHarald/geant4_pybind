#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DoLoMcPriRK34.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4DoLoMcPriRK34 : public G4DoLoMcPriRK34, public py::trampoline_self_life_support {
public:
   using G4DoLoMcPriRK34::G4DoLoMcPriRK34;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4DoLoMcPriRK34, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4DoLoMcPriRK34, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4DoLoMcPriRK34, IntegratorOrder, ); }
};

void export_G4DoLoMcPriRK34(py::module &m)
{
   py::class_<G4DoLoMcPriRK34, PyG4DoLoMcPriRK34, G4MagIntegratorStepper>(m, "G4DoLoMcPriRK34")

      .def(py::init<G4EquationOfMotion *, G4int, G4bool>(), py::arg("EqRhs"), py::arg("numberOfVariables") = 6,
           py::arg("primary") = true)

      .def("Stepper", &G4DoLoMcPriRK34::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("SetupInterpolation", &G4DoLoMcPriRK34::SetupInterpolation)
      .def("SetupInterpolate", &G4DoLoMcPriRK34::SetupInterpolate, py::arg("yInput"), py::arg("dydx"), py::arg("Step"))
      .def("Interpolate",
           py::overload_cast<const G4double *, const G4double *, const G4double, G4double *, G4double>(
              &G4DoLoMcPriRK34::Interpolate),
           py::arg("yInput"), py::arg("dydx"), py::arg("Step"), py::arg("yOut"), py::arg("tau"))

      .def("Interpolate", py::overload_cast<G4double, G4double *>(&G4DoLoMcPriRK34::Interpolate), py::arg("tau"),
           py::arg("yOut"))

      .def("DistChord", &G4DoLoMcPriRK34::DistChord)
      .def("IntegratorOrder", &G4DoLoMcPriRK34::IntegratorOrder);
}
