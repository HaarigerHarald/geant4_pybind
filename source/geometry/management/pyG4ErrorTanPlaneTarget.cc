#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ErrorTanPlaneTarget.hh>
#include <G4Step.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ErrorTanPlaneTarget : public G4ErrorTanPlaneTarget, public py::trampoline_self_life_support {
public:
   using G4ErrorTanPlaneTarget::G4ErrorTanPlaneTarget;

   G4Plane3D GetTangentPlane(const G4ThreeVector &point) const override
   {
      PYBIND11_OVERRIDE_PURE(G4Plane3D, G4ErrorTanPlaneTarget, GetTangentPlane, point);
   }

   void Dump(const G4String &msg) const override { PYBIND11_OVERRIDE_PURE(void, G4ErrorTanPlaneTarget, Dump, msg); }

   G4double GetDistanceFromPoint(const G4ThreeVector &arg0, const G4ThreeVector &arg1) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ErrorTanPlaneTarget, GetDistanceFromPoint, arg0, arg1);
   }

   G4double GetDistanceFromPoint(const G4ThreeVector &arg0) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ErrorTanPlaneTarget, GetDistanceFromPoint, arg0);
   }

   G4bool TargetReached(const G4Step *arg0) override
   {
      PYBIND11_OVERRIDE(G4bool, G4ErrorTanPlaneTarget, TargetReached, arg0);
   }
};

void export_G4ErrorTanPlaneTarget(py::module &m)
{
   py::class_<G4ErrorTanPlaneTarget, PyG4ErrorTanPlaneTarget, G4ErrorTarget>(m, "G4ErrorTanPlaneTarget")

      .def(py::init<>())
      .def("__copy__", [](const PyG4ErrorTanPlaneTarget &self) { return PyG4ErrorTanPlaneTarget(self); })
      .def("__deepcopy__", [](const PyG4ErrorTanPlaneTarget &self, py::dict) { return PyG4ErrorTanPlaneTarget(self); })
      .def("GetTangentPlane", &G4ErrorTanPlaneTarget::GetTangentPlane, py::arg("point"))
      .def("Dump", &G4ErrorTanPlaneTarget::Dump, py::arg("msg"));
}
