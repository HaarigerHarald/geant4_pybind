#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ErrorPlaneSurfaceTarget.hh>
#include <G4Step.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ErrorPlaneSurfaceTarget : public G4ErrorPlaneSurfaceTarget, public py::trampoline_self_life_support {
public:
   using G4ErrorPlaneSurfaceTarget::G4ErrorPlaneSurfaceTarget;

   G4ThreeVector Intersect(const G4ThreeVector &point, const G4ThreeVector &direc) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ErrorPlaneSurfaceTarget, Intersect, point, direc);
   }

   G4double GetDistanceFromPoint(const G4ThreeVector &point, const G4ThreeVector &direc) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ErrorPlaneSurfaceTarget, GetDistanceFromPoint, point, direc);
   }

   G4double GetDistanceFromPoint(const G4ThreeVector &pt) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ErrorPlaneSurfaceTarget, GetDistanceFromPoint, pt);
   }

   G4Plane3D GetTangentPlane(const G4ThreeVector &point) const override
   {
      PYBIND11_OVERRIDE(G4Plane3D, G4ErrorPlaneSurfaceTarget, GetTangentPlane, point);
   }

   void Dump(const G4String &msg) const override { PYBIND11_OVERRIDE(void, G4ErrorPlaneSurfaceTarget, Dump, msg); }

   G4bool TargetReached(const G4Step *arg0) override
   {
      PYBIND11_OVERRIDE(G4bool, G4ErrorPlaneSurfaceTarget, TargetReached, arg0);
   }
};

void export_G4ErrorPlaneSurfaceTarget(py::module &m)
{
   py::class_<G4ErrorPlaneSurfaceTarget, PyG4ErrorPlaneSurfaceTarget, G4ErrorSurfaceTarget>(m,
                                                                                            "G4ErrorPlaneSurfaceTarget")

      .def(py::init<G4double, G4double, G4double, G4double>(), py::arg("a") = 0., py::arg("b") = 0., py::arg("c") = 0.,
           py::arg("d") = 0.)

      .def(py::init<const G4Normal3D &, const G4Point3D &>(), py::arg("n"), py::arg("p"))
      .def(py::init<const G4Point3D &, const G4Point3D &, const G4Point3D &>(), py::arg("p1"), py::arg("p2"),
           py::arg("p3"))

      .def("__copy__", [](const PyG4ErrorPlaneSurfaceTarget &self) { return PyG4ErrorPlaneSurfaceTarget(self); })
      .def("__deepcopy__",
           [](const PyG4ErrorPlaneSurfaceTarget &self, py::dict) { return PyG4ErrorPlaneSurfaceTarget(self); })

      .def("Intersect", &G4ErrorPlaneSurfaceTarget::Intersect, py::arg("point"), py::arg("direc"))
      .def("GetDistanceFromPoint",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(
              &G4ErrorPlaneSurfaceTarget::GetDistanceFromPoint, py::const_),
           py::arg("point"), py::arg("direc"))

      .def("GetDistanceFromPoint",
           py::overload_cast<const G4ThreeVector &>(&G4ErrorPlaneSurfaceTarget::GetDistanceFromPoint, py::const_),
           py::arg("pt"))

      .def("GetTangentPlane", &G4ErrorPlaneSurfaceTarget::GetTangentPlane, py::arg("point"))
      .def("Dump", &G4ErrorPlaneSurfaceTarget::Dump, py::arg("msg"));
}
