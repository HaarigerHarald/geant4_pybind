#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VFacet.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VFacet : public G4VFacet, public py::trampoline_self_life_support {
public:
   using G4VFacet::G4VFacet;

   G4int GetNumberOfVertices() const override { PYBIND11_OVERRIDE_PURE(G4int, G4VFacet, GetNumberOfVertices, ); }

   G4ThreeVector GetVertex(G4int i) const override { PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4VFacet, GetVertex, i); }

   void SetVertex(G4int i, const G4ThreeVector &val) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VFacet, SetVertex, i, val);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE_PURE(G4GeometryType, G4VFacet, GetEntityType, ); }

   G4ThreeVector GetSurfaceNormal() const override
   {
      PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4VFacet, GetSurfaceNormal, );
   }

   G4bool IsDefined() const override { PYBIND11_OVERRIDE_PURE(G4bool, G4VFacet, IsDefined, ); }

   G4ThreeVector GetCircumcentre() const override
   {
      PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4VFacet, GetCircumcentre, );
   }

   G4double GetRadius() const override { PYBIND11_OVERRIDE_PURE(G4double, G4VFacet, GetRadius, ); }

   G4VFacet *GetClone() override { PYBIND11_OVERRIDE_PURE(G4VFacet *, G4VFacet, GetClone, ); }

   G4double Distance(const G4ThreeVector &arg0, G4double arg1) override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VFacet, Distance, arg0, arg1);
   }

   G4double Distance(const G4ThreeVector &arg0, G4double arg1, const G4bool arg2) override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VFacet, Distance, arg0, arg1, arg2);
   }

   G4double Extent(const G4ThreeVector arg0) override { PYBIND11_OVERRIDE_PURE(G4double, G4VFacet, Extent, arg0); }

   G4bool Intersect(const G4ThreeVector &arg0, const G4ThreeVector &arg1, const G4bool arg2, G4double &arg3,
                    G4double &arg4, G4ThreeVector &arg5) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VFacet, Intersect, arg0, arg1, arg2, arg3, arg4, arg5);
   }

   G4double GetArea() const override { PYBIND11_OVERRIDE_PURE(G4double, G4VFacet, GetArea, ); }

   G4ThreeVector GetPointOnFace() const override { PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4VFacet, GetPointOnFace, ); }

   G4int AllocatedMemory() override { PYBIND11_OVERRIDE_PURE(G4int, G4VFacet, AllocatedMemory, ); }

   void SetVertexIndex(G4int i, G4int j) override { PYBIND11_OVERRIDE_PURE(void, G4VFacet, SetVertexIndex, i, j); }

   G4int GetVertexIndex(G4int i) const override { PYBIND11_OVERRIDE_PURE(G4int, G4VFacet, GetVertexIndex, i); }

   void SetVertices(std::vector<G4ThreeVector, std::allocator<G4ThreeVector>> *vertices) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VFacet, SetVertices, vertices);
   }
};

void export_G4VFacet(py::module &m)
{
   py::enum_<G4FacetVertexType>(m, "G4FacetVertexType")
      .value("ABSOLUTE", ABSOLUTE)
      .value("RELATIVE", RELATIVE)
      .export_values();

   py::class_<G4VFacet, PyG4VFacet>(m, "G4VFacet")

      .def("__copy__", [](const PyG4VFacet &self) { return PyG4VFacet(self); })
      .def("__deepcopy__", [](const PyG4VFacet &self, py::dict) { return PyG4VFacet(self); })
      .def(py::init<>())
      .def("AllocatedMemory", &G4VFacet::AllocatedMemory)
      .def("ApplyTranslation", &G4VFacet::ApplyTranslation, py::arg("v"))
      .def("Distance", py::overload_cast<const G4ThreeVector &, G4double>(&G4VFacet::Distance))
      .def("Distance", py::overload_cast<const G4ThreeVector &, G4double, const G4bool>(&G4VFacet::Distance))

      .def("Extent", &G4VFacet::Extent)
      .def("GetArea", &G4VFacet::GetArea)
      .def("GetCircumcentre", &G4VFacet::GetCircumcentre)
      .def("GetClone", &G4VFacet::GetClone, py::return_value_policy::reference)
      .def("GetEntityType", &G4VFacet::GetEntityType)
      .def("GetNumberOfVertices", &G4VFacet::GetNumberOfVertices)
      .def("GetPointOnFace", &G4VFacet::GetPointOnFace)
      .def("GetRadius", &G4VFacet::GetRadius)
      .def("GetSurfaceNormal", &G4VFacet::GetSurfaceNormal)
      .def("GetVertex", &G4VFacet::GetVertex, py::arg("i"))
      .def("GetVertexIndex", &G4VFacet::GetVertexIndex, py::arg("i"))
      .def("Intersect", &G4VFacet::Intersect)
      .def("IsDefined", &G4VFacet::IsDefined)
      .def("IsInside", &G4VFacet::IsInside, py::arg("p"))
      .def("SetVertex", &G4VFacet::SetVertex, py::arg("i"), py::arg("val"))
      .def("SetVertexIndex", &G4VFacet::SetVertexIndex, py::arg("i"), py::arg("j"))
      .def("SetVertices", &G4VFacet::SetVertices, py::arg("vertices"))
      .def("StreamInfo", &G4VFacet::StreamInfo, py::arg("os"))
      .def("__eq__", &G4VFacet::operator==, py::is_operator());
}
