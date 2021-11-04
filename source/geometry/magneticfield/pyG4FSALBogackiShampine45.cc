#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4FSALBogackiShampine45.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4FSALBogackiShampine45 : public G4FSALBogackiShampine45, public py::trampoline_self_life_support {
public:
   using G4FSALBogackiShampine45::G4FSALBogackiShampine45;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr,
                G4double *nextDydx) override
   {
      PYBIND11_OVERRIDE(void, G4FSALBogackiShampine45, Stepper, y, dydx, h, yout, yerr, nextDydx);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4FSALBogackiShampine45, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4FSALBogackiShampine45, IntegratorOrder, ); }
};

void export_G4FSALBogackiShampine45(py::module &m)
{
   py::class_<G4FSALBogackiShampine45, PyG4FSALBogackiShampine45, G4VFSALIntegrationStepper>(m,
                                                                                             "G4FSALBogackiShampine45")

      .def(py::init<G4EquationOfMotion *, G4int, G4bool>(), py::arg("EqRhs"), py::arg("numberOfVariables") = 6,
           py::arg("primary") = true)

      .def("Stepper", &G4FSALBogackiShampine45::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"), py::arg("nextDydx"))

      .def("interpolate", &G4FSALBogackiShampine45::interpolate, py::arg("yInput"), py::arg("dydx"), py::arg("yOut"),
           py::arg("Step"), py::arg("tau"))

      .def("DistChord", &G4FSALBogackiShampine45::DistChord)
      .def("IntegratorOrder", &G4FSALBogackiShampine45::IntegratorOrder);
}
