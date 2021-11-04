#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ExactHelixStepper.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ExactHelixStepper : public G4ExactHelixStepper, public py::trampoline_self_life_support {
public:
   using G4ExactHelixStepper::G4ExactHelixStepper;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4ExactHelixStepper, Stepper, y, dydx, h, yout, yerr);
   }

   void DumbStepper(const G4double *y, G4ThreeVector Bfld, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE(void, G4ExactHelixStepper, DumbStepper, y, Bfld, h, yout);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4ExactHelixStepper, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4ExactHelixStepper, IntegratorOrder, ); }
};

void export_G4ExactHelixStepper(py::module &m)
{
   py::class_<G4ExactHelixStepper, PyG4ExactHelixStepper, G4MagHelicalStepper>(m, "G4ExactHelixStepper")

      .def(py::init<G4Mag_EqRhs *>(), py::arg("EqRhs"))
      .def("Stepper", &G4ExactHelixStepper::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("DumbStepper", &G4ExactHelixStepper::DumbStepper, py::arg("y"), py::arg("Bfld"), py::arg("h"),
           py::arg("yout"))

      .def("DistChord", &G4ExactHelixStepper::DistChord)
      .def("IntegratorOrder", &G4ExactHelixStepper::IntegratorOrder);
}
