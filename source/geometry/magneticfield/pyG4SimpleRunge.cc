#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SimpleRunge.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4SimpleRunge : public G4SimpleRunge, public py::trampoline_self_life_support {
public:
   using G4SimpleRunge::G4SimpleRunge;

   void DumbStepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE(void, G4SimpleRunge, DumbStepper, y, dydx, h, yout);
   }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4SimpleRunge, IntegratorOrder, ); }

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4SimpleRunge, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4SimpleRunge, DistChord, ); }
};

void export_G4SimpleRunge(py::module &m)
{
   py::class_<G4SimpleRunge, PyG4SimpleRunge, G4MagErrorStepper>(m, "G4SimpleRunge")

      .def(py::init<G4EquationOfMotion *, G4int>(), py::arg("EquationRhs"), py::arg("numberOfVariables") = 6)
      .def("DumbStepper", &G4SimpleRunge::DumbStepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"))
      .def("IntegratorOrder", &G4SimpleRunge::IntegratorOrder);
}
