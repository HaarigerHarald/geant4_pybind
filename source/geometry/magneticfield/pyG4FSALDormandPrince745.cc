#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4FSALDormandPrince745.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4FSALDormandPrince745 : public G4FSALDormandPrince745, public py::trampoline_self_life_support {
public:
   using G4FSALDormandPrince745::G4FSALDormandPrince745;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr,
                G4double *nextDydx) override
   {
      PYBIND11_OVERRIDE(void, G4FSALDormandPrince745, Stepper, y, dydx, h, yout, yerr, nextDydx);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4FSALDormandPrince745, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4FSALDormandPrince745, IntegratorOrder, ); }
};

void export_G4FSALDormandPrince745(py::module &m)
{
   py::class_<G4FSALDormandPrince745, PyG4FSALDormandPrince745, G4VFSALIntegrationStepper>(m, "G4FSALDormandPrince745")

      .def(py::init<G4EquationOfMotion *, G4int, G4bool>(), py::arg("EqRhs"), py::arg("numberOfVariables") = 6,
           py::arg("primary") = true)

      .def("Stepper", &G4FSALDormandPrince745::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"), py::arg("nextDydx"))

      .def("SetupInterpolate", &G4FSALDormandPrince745::SetupInterpolate, py::arg("yInput"), py::arg("dydx"),
           py::arg("Step"))

      .def("Interpolate", &G4FSALDormandPrince745::Interpolate, py::arg("yInput"), py::arg("dydx"), py::arg("Step"),
           py::arg("yOut"), py::arg("tau"))

      .def("DistChord", &G4FSALDormandPrince745::DistChord)
      .def("IntegratorOrder", &G4FSALDormandPrince745::IntegratorOrder)
      .def("isFSAL", &G4FSALDormandPrince745::isFSAL);
}
