#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HelixMixedStepper.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4HelixMixedStepper : public G4HelixMixedStepper, public py::trampoline_self_life_support {
public:
   using G4HelixMixedStepper::G4HelixMixedStepper;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4HelixMixedStepper, Stepper, y, dydx, h, yout, yerr);
   }

   void DumbStepper(const G4double *y, G4ThreeVector Bfld, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE(void, G4HelixMixedStepper, DumbStepper, y, Bfld, h, yout);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4HelixMixedStepper, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4HelixMixedStepper, IntegratorOrder, ); }
};

void export_G4HelixMixedStepper(py::module &m)
{
   py::class_<G4HelixMixedStepper, PyG4HelixMixedStepper, G4MagHelicalStepper>(m, "G4HelixMixedStepper")

      .def(py::init<G4Mag_EqRhs *, G4int, G4double>(), py::arg("EqRhs"), py::arg("StepperNumber") = -1,
           py::arg("Angle_threshold") = -1.)

      .def("Stepper", &G4HelixMixedStepper::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("DumbStepper", &G4HelixMixedStepper::DumbStepper, py::arg("y"), py::arg("Bfld"), py::arg("h"),
           py::arg("yout"))

      .def("DistChord", &G4HelixMixedStepper::DistChord)
      .def("SetVerbose", &G4HelixMixedStepper::SetVerbose, py::arg("newvalue"))
      .def("PrintCalls", &G4HelixMixedStepper::PrintCalls)
      .def("SetupStepper", &G4HelixMixedStepper::SetupStepper, py::arg("EqRhs"), py::arg("StepperName"),
           py::return_value_policy::reference)

      .def("SetAngleThreshold", &G4HelixMixedStepper::SetAngleThreshold, py::arg("val"))
      .def("GetAngleThreshold", &G4HelixMixedStepper::GetAngleThreshold)
      .def("IntegratorOrder", &G4HelixMixedStepper::IntegratorOrder);
}
