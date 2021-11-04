#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MagErrorStepper.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4MagErrorStepper : public G4MagErrorStepper, public py::trampoline_self_life_support {
public:
   using G4MagErrorStepper::G4MagErrorStepper;

   void DumbStepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4MagErrorStepper, DumbStepper, y, dydx, h, yout);
   }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE_PURE(G4int, G4MagErrorStepper, IntegratorOrder, ); }

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4MagErrorStepper, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4MagErrorStepper, DistChord, ); }
};

void export_G4MagErrorStepper(py::module &m)
{
   py::class_<G4MagErrorStepper, PyG4MagErrorStepper, G4MagIntegratorStepper>(m, "G4MagErrorStepper")

      .def(py::init<G4EquationOfMotion *, G4int, G4int>(), py::arg("EqRhs"), py::arg("numberOfVariables"),
           py::arg("numStateVariables") = 12)

      .def("Stepper", &G4MagErrorStepper::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("DumbStepper", &G4MagErrorStepper::DumbStepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"))
      .def("DistChord", &G4MagErrorStepper::DistChord);
}
