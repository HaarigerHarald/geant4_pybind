#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HelixExplicitEuler.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4HelixExplicitEuler : public G4HelixExplicitEuler, public py::trampoline_self_life_support {
public:
   using G4HelixExplicitEuler::G4HelixExplicitEuler;

   void Stepper(const G4double *y, const G4double *arg1, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4HelixExplicitEuler, Stepper, y, arg1, h, yout, yerr);
   }

   void DumbStepper(const G4double *y, G4ThreeVector Bfld, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE(void, G4HelixExplicitEuler, DumbStepper, y, Bfld, h, yout);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4HelixExplicitEuler, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4HelixExplicitEuler, IntegratorOrder, ); }
};

void export_G4HelixExplicitEuler(py::module &m)
{
   py::class_<G4HelixExplicitEuler, PyG4HelixExplicitEuler, G4MagHelicalStepper>(m, "G4HelixExplicitEuler")

      .def(py::init<G4Mag_EqRhs *>(), py::arg("EqRhs"))
      .def("Stepper", &G4HelixExplicitEuler::Stepper, py::arg("y"), py::arg("arg1"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("DumbStepper", &G4HelixExplicitEuler::DumbStepper, py::arg("y"), py::arg("Bfld"), py::arg("h"),
           py::arg("yout"))

      .def("DistChord", &G4HelixExplicitEuler::DistChord)
      .def("IntegratorOrder", &G4HelixExplicitEuler::IntegratorOrder);
}
