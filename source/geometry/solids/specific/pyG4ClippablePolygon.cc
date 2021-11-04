#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ClippablePolygon.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ClippablePolygon : public G4ClippablePolygon, public py::trampoline_self_life_support {
public:
   using G4ClippablePolygon::G4ClippablePolygon;

   void AddVertexInOrder(const G4ThreeVector vertex) override
   {
      PYBIND11_OVERRIDE(void, G4ClippablePolygon, AddVertexInOrder, vertex);
   }

   void ClearAllVertices() override { PYBIND11_OVERRIDE(void, G4ClippablePolygon, ClearAllVertices, ); }

   G4bool Clip(const G4VoxelLimits &voxelLimit) override
   {
      PYBIND11_OVERRIDE(G4bool, G4ClippablePolygon, Clip, voxelLimit);
   }

   G4bool PartialClip(const G4VoxelLimits &voxelLimit, const EAxis IgnoreMe) override
   {
      PYBIND11_OVERRIDE(G4bool, G4ClippablePolygon, PartialClip, voxelLimit, IgnoreMe);
   }

   void ClipAlongOneAxis(const G4VoxelLimits &voxelLimit, const EAxis axis) override
   {
      PYBIND11_OVERRIDE(void, G4ClippablePolygon, ClipAlongOneAxis, voxelLimit, axis);
   }

   G4bool GetExtent(const EAxis axis, G4double &min, G4double &max) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4ClippablePolygon, GetExtent, axis, min, max);
   }

   const G4ThreeVector *GetMinPoint(const EAxis axis) const override
   {
      PYBIND11_OVERRIDE(const G4ThreeVector *, G4ClippablePolygon, GetMinPoint, axis);
   }

   const G4ThreeVector *GetMaxPoint(const EAxis axis) const override
   {
      PYBIND11_OVERRIDE(const G4ThreeVector *, G4ClippablePolygon, GetMaxPoint, axis);
   }

   G4bool InFrontOf(const G4ClippablePolygon &other, EAxis axis) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4ClippablePolygon, InFrontOf, other, axis);
   }

   G4bool BehindOf(const G4ClippablePolygon &other, EAxis axis) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4ClippablePolygon, BehindOf, other, axis);
   }

   G4bool GetPlanerExtent(const G4ThreeVector &pointOnPlane, const G4ThreeVector &planeNormal, G4double &min,
                          G4double &max) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4ClippablePolygon, GetPlanerExtent, pointOnPlane, planeNormal, min, max);
   }
};

void export_G4ClippablePolygon(py::module &m)
{
   py::class_<G4ClippablePolygon, PyG4ClippablePolygon>(m, "G4ClippablePolygon")

      .def(py::init<>())
      .def("__copy__", [](const PyG4ClippablePolygon &self) { return PyG4ClippablePolygon(self); })
      .def("__deepcopy__", [](const PyG4ClippablePolygon &self, py::dict) { return PyG4ClippablePolygon(self); })
      .def("AddVertexInOrder", &G4ClippablePolygon::AddVertexInOrder, py::arg("vertex"))
      .def("ClearAllVertices", &G4ClippablePolygon::ClearAllVertices)
      .def("SetNormal", &G4ClippablePolygon::SetNormal, py::arg("newNormal"))
      .def("GetNormal", &G4ClippablePolygon::GetNormal)
      .def("Clip", &G4ClippablePolygon::Clip, py::arg("voxelLimit"))
      .def("PartialClip", &G4ClippablePolygon::PartialClip, py::arg("voxelLimit"), py::arg("IgnoreMe"))
      .def("ClipAlongOneAxis", &G4ClippablePolygon::ClipAlongOneAxis, py::arg("voxelLimit"), py::arg("axis"))
      .def("GetExtent", &G4ClippablePolygon::GetExtent, py::arg("axis"), py::arg("min"), py::arg("max"))
      .def("GetMinPoint", &G4ClippablePolygon::GetMinPoint, py::arg("axis"), py::return_value_policy::reference)
      .def("GetMaxPoint", &G4ClippablePolygon::GetMaxPoint, py::arg("axis"), py::return_value_policy::reference)
      .def("GetNumVertices", &G4ClippablePolygon::GetNumVertices)
      .def("Empty", &G4ClippablePolygon::Empty)
      .def("InFrontOf", &G4ClippablePolygon::InFrontOf, py::arg("other"), py::arg("axis"))
      .def("BehindOf", &G4ClippablePolygon::BehindOf, py::arg("other"), py::arg("axis"))
      .def("GetPlanerExtent", &G4ClippablePolygon::GetPlanerExtent, py::arg("pointOnPlane"), py::arg("planeNormal"),
           py::arg("min"), py::arg("max"));
}
