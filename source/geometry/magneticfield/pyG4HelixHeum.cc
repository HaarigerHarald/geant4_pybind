#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HelixHeum.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4HelixHeum : public G4HelixHeum, public py::trampoline_self_life_support {
public:
   using G4HelixHeum::G4HelixHeum;

   void DumbStepper(const G4double *y, G4ThreeVector Bfld, G4double h, G4double *yout) override
   {
      PYBIND11_OVERRIDE(void, G4HelixHeum, DumbStepper, y, Bfld, h, yout);
   }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4HelixHeum, IntegratorOrder, ); }

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4HelixHeum, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4HelixHeum, DistChord, ); }
};

void export_G4HelixHeum(py::module &m)
{
   py::class_<G4HelixHeum, PyG4HelixHeum, G4MagHelicalStepper>(m, "G4HelixHeum")

      .def(py::init<G4Mag_EqRhs *>(), py::arg("EqRhs"))
      .def("DumbStepper", &G4HelixHeum::DumbStepper, py::arg("y"), py::arg("Bfld"), py::arg("h"), py::arg("yout"))
      .def("IntegratorOrder", &G4HelixHeum::IntegratorOrder);
}
