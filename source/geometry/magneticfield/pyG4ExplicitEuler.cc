#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ExplicitEuler.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ExplicitEuler : public G4ExplicitEuler, public py::trampoline_self_life_support {
public:
   using G4ExplicitEuler::G4ExplicitEuler;

   void DumbStepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE(void, G4ExplicitEuler, DumbStepper, y, dydx, h, yout);
   }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4ExplicitEuler, IntegratorOrder, ); }

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4ExplicitEuler, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4ExplicitEuler, DistChord, ); }
};

void export_G4ExplicitEuler(py::module &m)
{
   py::class_<G4ExplicitEuler, PyG4ExplicitEuler, G4MagErrorStepper>(m, "G4ExplicitEuler")

      .def(py::init<G4EquationOfMotion *, G4int>(), py::arg("EqRhs"), py::arg("numberOfVariables") = 6)
      .def("DumbStepper", &G4ExplicitEuler::DumbStepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"))
      .def("IntegratorOrder", &G4ExplicitEuler::IntegratorOrder);
}
