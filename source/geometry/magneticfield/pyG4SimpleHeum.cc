#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SimpleHeum.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4SimpleHeum : public G4SimpleHeum, public py::trampoline_self_life_support {
public:
   using G4SimpleHeum::G4SimpleHeum;

   void DumbStepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE(void, G4SimpleHeum, DumbStepper, y, dydx, h, yout);
   }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4SimpleHeum, IntegratorOrder, ); }

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4SimpleHeum, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4SimpleHeum, DistChord, ); }
};

void export_G4SimpleHeum(py::module &m)
{
   py::class_<G4SimpleHeum, PyG4SimpleHeum, G4MagErrorStepper>(m, "G4SimpleHeum")

      .def(py::init<G4EquationOfMotion *, G4int>(), py::arg("EqRhs"), py::arg("num_variables") = 6)
      .def("DumbStepper", &G4SimpleHeum::DumbStepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"))
      .def("IntegratorOrder", &G4SimpleHeum::IntegratorOrder);
}
