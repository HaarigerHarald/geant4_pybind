#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MagHelicalStepper.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4MagHelicalStepper : public G4MagHelicalStepper, public py::trampoline_self_life_support {
public:
   using G4MagHelicalStepper::G4MagHelicalStepper;

   void DumbStepper(const G4double *y, G4ThreeVector Bfld, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4MagHelicalStepper, DumbStepper, y, Bfld, h, yout);
   }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE_PURE(G4int, G4MagHelicalStepper, IntegratorOrder, ); }

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4MagHelicalStepper, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4MagHelicalStepper, DistChord, ); }
};

void export_G4MagHelicalStepper(py::module &m)
{
   py::class_<G4MagHelicalStepper, PyG4MagHelicalStepper, G4MagIntegratorStepper>(m, "G4MagHelicalStepper")

      .def(py::init<G4Mag_EqRhs *>(), py::arg("EqRhs"))
      .def("Stepper", &G4MagHelicalStepper::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("DumbStepper", &G4MagHelicalStepper::DumbStepper, py::arg("y"), py::arg("Bfld"), py::arg("h"),
           py::arg("yout"))

      .def("DistChord", &G4MagHelicalStepper::DistChord);
}
