#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HelixImplicitEuler.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4HelixImplicitEuler : public G4HelixImplicitEuler, public py::trampoline_self_life_support {
public:
   using G4HelixImplicitEuler::G4HelixImplicitEuler;

   void DumbStepper(const G4double *y, G4ThreeVector Bfld, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE(void, G4HelixImplicitEuler, DumbStepper, y, Bfld, h, yout);
   }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4HelixImplicitEuler, IntegratorOrder, ); }

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4HelixImplicitEuler, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4HelixImplicitEuler, DistChord, ); }
};

void export_G4HelixImplicitEuler(py::module &m)
{
   py::class_<G4HelixImplicitEuler, PyG4HelixImplicitEuler, G4MagHelicalStepper>(m, "G4HelixImplicitEuler")

      .def(py::init<G4Mag_EqRhs *>(), py::arg("EqRhs"))
      .def("DumbStepper", &G4HelixImplicitEuler::DumbStepper, py::arg("y"), py::arg("Bfld"), py::arg("h"),
           py::arg("yout"))

      .def("IntegratorOrder", &G4HelixImplicitEuler::IntegratorOrder);
}
