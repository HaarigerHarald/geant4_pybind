#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ErrorTarget.hh>
#include <G4Step.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ErrorTarget : public G4ErrorTarget, public py::trampoline_self_life_support {
public:
   using G4ErrorTarget::G4ErrorTarget;

   void Dump(const G4String &msg) const override { PYBIND11_OVERRIDE_PURE(void, G4ErrorTarget, Dump, msg); }

   G4double GetDistanceFromPoint(const G4ThreeVector &arg0, const G4ThreeVector &arg1) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ErrorTarget, GetDistanceFromPoint, arg0, arg1);
   }

   G4double GetDistanceFromPoint(const G4ThreeVector &arg0) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ErrorTarget, GetDistanceFromPoint, arg0);
   }

   G4bool TargetReached(const G4Step *arg0) override { PYBIND11_OVERRIDE(G4bool, G4ErrorTarget, TargetReached, arg0); }
};

void export_G4ErrorTarget(py::module &m)
{
   py::enum_<G4ErrorTargetType>(m, "G4ErrorTargetType")
      .value("G4ErrorTarget_PlaneSurface", G4ErrorTarget_PlaneSurface)
      .value("G4ErrorTarget_CylindricalSurface", G4ErrorTarget_CylindricalSurface)
      .value("G4ErrorTarget_GeomVolume", G4ErrorTarget_GeomVolume)
      .value("G4ErrorTarget_TrkL", G4ErrorTarget_TrkL)
      .export_values();

   py::class_<G4ErrorTarget, PyG4ErrorTarget>(m, "G4ErrorTarget")

      .def("__copy__", [](const PyG4ErrorTarget &self) { return PyG4ErrorTarget(self); })
      .def("__deepcopy__", [](const PyG4ErrorTarget &self, py::dict) { return PyG4ErrorTarget(self); })
      .def(py::init<>())
      .def("Dump", &G4ErrorTarget::Dump, py::arg("msg"))
      .def("GetDistanceFromPoint", py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(
                                      &G4ErrorTarget::GetDistanceFromPoint, py::const_))

      .def("GetDistanceFromPoint",
           py::overload_cast<const G4ThreeVector &>(&G4ErrorTarget::GetDistanceFromPoint, py::const_))

      .def("GetType", &G4ErrorTarget::GetType)
      .def("TargetReached", &G4ErrorTarget::TargetReached);
}
