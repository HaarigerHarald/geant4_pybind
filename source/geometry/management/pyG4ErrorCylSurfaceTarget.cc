#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ErrorCylSurfaceTarget.hh>
#include <G4Step.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ErrorCylSurfaceTarget : public G4ErrorCylSurfaceTarget, public py::trampoline_self_life_support {
public:
   using G4ErrorCylSurfaceTarget::G4ErrorCylSurfaceTarget;

   G4ThreeVector IntersectLocal(const G4ThreeVector &point, const G4ThreeVector &direc) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ErrorCylSurfaceTarget, IntersectLocal, point, direc);
   }

   G4double GetDistanceFromPoint(const G4ThreeVector &point, const G4ThreeVector &direc) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ErrorCylSurfaceTarget, GetDistanceFromPoint, point, direc);
   }

   G4double GetDistanceFromPoint(const G4ThreeVector &point) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ErrorCylSurfaceTarget, GetDistanceFromPoint, point);
   }

   G4Plane3D GetTangentPlane(const G4ThreeVector &point) const override
   {
      PYBIND11_OVERRIDE(G4Plane3D, G4ErrorCylSurfaceTarget, GetTangentPlane, point);
   }

   void Dump(const G4String &msg) const override { PYBIND11_OVERRIDE(void, G4ErrorCylSurfaceTarget, Dump, msg); }

   G4bool TargetReached(const G4Step *arg0) override
   {
      PYBIND11_OVERRIDE(G4bool, G4ErrorCylSurfaceTarget, TargetReached, arg0);
   }
};

void export_G4ErrorCylSurfaceTarget(py::module &m)
{
   py::class_<G4ErrorCylSurfaceTarget, PyG4ErrorCylSurfaceTarget, G4ErrorSurfaceTarget>(m, "G4ErrorCylSurfaceTarget")

      .def(py::init<const G4double &, const G4ThreeVector &, const G4RotationMatrix &>(), py::arg("radius"),
           py::arg("trans") = G4ThreeVector(), py::arg("rotm") = G4RotationMatrix())

      .def(py::init<const G4double &, const G4AffineTransform &>(), py::arg("radius"), py::arg("trans"))
      .def("__copy__", [](const PyG4ErrorCylSurfaceTarget &self) { return PyG4ErrorCylSurfaceTarget(self); })
      .def("__deepcopy__",
           [](const PyG4ErrorCylSurfaceTarget &self, py::dict) { return PyG4ErrorCylSurfaceTarget(self); })

      .def("IntersectLocal", &G4ErrorCylSurfaceTarget::IntersectLocal, py::arg("point"), py::arg("direc"))
      .def("GetDistanceFromPoint",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(
              &G4ErrorCylSurfaceTarget::GetDistanceFromPoint, py::const_),
           py::arg("point"), py::arg("direc"))

      .def("GetDistanceFromPoint",
           py::overload_cast<const G4ThreeVector &>(&G4ErrorCylSurfaceTarget::GetDistanceFromPoint, py::const_),
           py::arg("point"))

      .def("GetTangentPlane", &G4ErrorCylSurfaceTarget::GetTangentPlane, py::arg("point"))
      .def("Dump", &G4ErrorCylSurfaceTarget::Dump, py::arg("msg"));
}
