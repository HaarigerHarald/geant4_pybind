#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ImplicitEuler.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ImplicitEuler : public G4ImplicitEuler, public py::trampoline_self_life_support {
public:
   using G4ImplicitEuler::G4ImplicitEuler;

   void DumbStepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE(void, G4ImplicitEuler, DumbStepper, y, dydx, h, yout);
   }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4ImplicitEuler, IntegratorOrder, ); }

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4ImplicitEuler, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4ImplicitEuler, DistChord, ); }
};

void export_G4ImplicitEuler(py::module &m)
{
   py::class_<G4ImplicitEuler, PyG4ImplicitEuler, G4MagErrorStepper>(m, "G4ImplicitEuler")

      .def(py::init<G4EquationOfMotion *, G4int>(), py::arg("EqRhs"), py::arg("numberOfVariables") = 6)
      .def("DumbStepper", &G4ImplicitEuler::DumbStepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"))
      .def("IntegratorOrder", &G4ImplicitEuler::IntegratorOrder);
}
