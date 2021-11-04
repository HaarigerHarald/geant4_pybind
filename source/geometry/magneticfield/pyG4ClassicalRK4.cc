#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ClassicalRK4.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ClassicalRK4 : public G4ClassicalRK4, public py::trampoline_self_life_support {
public:
   using G4ClassicalRK4::G4ClassicalRK4;

   void DumbStepper(const G4double *yIn, const G4double *dydx, G4double h, G4double *yOut) override
   {
      PYBIND11_OVERRIDE(void, G4ClassicalRK4, DumbStepper, yIn, dydx, h, yOut);
   }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4ClassicalRK4, IntegratorOrder, ); }

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4ClassicalRK4, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4ClassicalRK4, DistChord, ); }
};

void export_G4ClassicalRK4(py::module &m)
{
   py::class_<G4ClassicalRK4, PyG4ClassicalRK4, G4MagErrorStepper>(m, "G4ClassicalRK4")

      .def(py::init<G4EquationOfMotion *, G4int>(), py::arg("EquationMotion"), py::arg("numberOfVariables") = 6)
      .def("DumbStepper", &G4ClassicalRK4::DumbStepper, py::arg("yIn"), py::arg("dydx"), py::arg("h"), py::arg("yOut"))
      .def("IntegratorOrder", &G4ClassicalRK4::IntegratorOrder);
}
