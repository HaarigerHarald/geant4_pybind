#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RKG3_Stepper.hh>
#include <G4Mag_EqRhs.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4RKG3_Stepper : public G4RKG3_Stepper, public py::trampoline_self_life_support {
public:
   using G4RKG3_Stepper::G4RKG3_Stepper;

   void Stepper(const G4double *yIn, const G4double *dydx, G4double h, G4double *yOut, G4double *yErr) override
   {
      PYBIND11_OVERRIDE(void, G4RKG3_Stepper, Stepper, yIn, dydx, h, yOut, yErr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4RKG3_Stepper, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4RKG3_Stepper, IntegratorOrder, ); }
};

void export_G4RKG3_Stepper(py::module &m)
{
   py::class_<G4RKG3_Stepper, PyG4RKG3_Stepper, G4MagIntegratorStepper>(m, "G4RKG3_Stepper")

      .def(py::init<G4Mag_EqRhs *>(), py::arg("EqRhs"))
      .def("Stepper", &G4RKG3_Stepper::Stepper, py::arg("yIn"), py::arg("dydx"), py::arg("h"), py::arg("yOut"),
           py::arg("yErr"))

      .def("DistChord", &G4RKG3_Stepper::DistChord)
      .def("StepNoErr", &G4RKG3_Stepper::StepNoErr, py::arg("tIn"), py::arg("dydx"), py::arg("Step"), py::arg("tOut"),
           py::arg("B"))

      .def("StepWithEst", &G4RKG3_Stepper::StepWithEst, py::arg("tIn"), py::arg("dydx"), py::arg("Step"),
           py::arg("tOut"), py::arg("alpha2"), py::arg("beta2"), py::arg("B1"), py::arg("B2"))

      .def("IntegratorOrder", &G4RKG3_Stepper::IntegratorOrder);
}
