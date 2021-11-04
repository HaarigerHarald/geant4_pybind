#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4BogackiShampine45.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4BogackiShampine45 : public G4BogackiShampine45, public py::trampoline_self_life_support {
public:
   using G4BogackiShampine45::G4BogackiShampine45;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4BogackiShampine45, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4BogackiShampine45, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4BogackiShampine45, IntegratorOrder, ); }
};

void export_G4BogackiShampine45(py::module &m)
{
   py::class_<G4BogackiShampine45, PyG4BogackiShampine45, G4MagIntegratorStepper>(m, "G4BogackiShampine45")

      .def(py::init<G4EquationOfMotion *, G4int, G4bool>(), py::arg("EqRhs"), py::arg("numberOfVariables") = 6,
           py::arg("primary") = true)

      .def("Stepper", &G4BogackiShampine45::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("SetupInterpolation", &G4BogackiShampine45::SetupInterpolation)
      .def("Interpolate", &G4BogackiShampine45::Interpolate, py::arg("tau"), py::arg("yOut"))
      .def("SetupInterpolationHigh", &G4BogackiShampine45::SetupInterpolationHigh)
      .def("InterpolateHigh", &G4BogackiShampine45::InterpolateHigh, py::arg("tau"), py::arg("yOut"))
      .def("DistChord", &G4BogackiShampine45::DistChord)
      .def("IntegratorOrder", &G4BogackiShampine45::IntegratorOrder)
      .def("GetLastDydx", &G4BogackiShampine45::GetLastDydx, py::arg("dyDxLast"))
      .def("PrepareConstants", &G4BogackiShampine45::PrepareConstants);
}
