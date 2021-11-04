#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TriangularFacet.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VFacet.hh>
#include <G4ThreeVector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4TriangularFacet : public G4TriangularFacet, public py::trampoline_self_life_support {
public:
   using G4TriangularFacet::G4TriangularFacet;

   G4VFacet *GetClone() override { PYBIND11_OVERRIDE(G4VFacet *, G4TriangularFacet, GetClone, ); }

   G4double Distance(const G4ThreeVector &p, G4double minDist) override
   {
      PYBIND11_OVERRIDE(G4double, G4TriangularFacet, Distance, p, minDist);
   }

   G4double Distance(const G4ThreeVector &p, G4double minDist, const G4bool outgoing) override
   {
      PYBIND11_OVERRIDE(G4double, G4TriangularFacet, Distance, p, minDist, outgoing);
   }

   G4double Extent(const G4ThreeVector axis) override { PYBIND11_OVERRIDE(G4double, G4TriangularFacet, Extent, axis); }

   G4bool Intersect(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool outgoing, G4double &distance,
                    G4double &distFromSurface, G4ThreeVector &normal) override
   {
      PYBIND11_OVERRIDE(G4bool, G4TriangularFacet, Intersect, p, v, outgoing, distance, distFromSurface, normal);
   }

   G4double GetArea() const override { PYBIND11_OVERRIDE(G4double, G4TriangularFacet, GetArea, ); }

   G4ThreeVector GetPointOnFace() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TriangularFacet, GetPointOnFace, );
   }

   G4ThreeVector GetSurfaceNormal() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TriangularFacet, GetSurfaceNormal, );
   }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4TriangularFacet, GetEntityType, );
   }

   G4bool IsDefined() const override { PYBIND11_OVERRIDE(G4bool, G4TriangularFacet, IsDefined, ); }

   G4int GetNumberOfVertices() const override { PYBIND11_OVERRIDE(G4int, G4TriangularFacet, GetNumberOfVertices, ); }

   G4ThreeVector GetVertex(G4int i) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TriangularFacet, GetVertex, i);
   }

   void SetVertex(G4int i, const G4ThreeVector &val) override
   {
      PYBIND11_OVERRIDE(void, G4TriangularFacet, SetVertex, i, val);
   }

   G4ThreeVector GetCircumcentre() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TriangularFacet, GetCircumcentre, );
   }

   G4double GetRadius() const override { PYBIND11_OVERRIDE(G4double, G4TriangularFacet, GetRadius, ); }

   G4int AllocatedMemory() override { PYBIND11_OVERRIDE(G4int, G4TriangularFacet, AllocatedMemory, ); }

   G4int GetVertexIndex(G4int i) const override { PYBIND11_OVERRIDE(G4int, G4TriangularFacet, GetVertexIndex, i); }

   void SetVertexIndex(G4int i, G4int j) override { PYBIND11_OVERRIDE(void, G4TriangularFacet, SetVertexIndex, i, j); }

   void SetVertices(std::vector<G4ThreeVector, std::allocator<G4ThreeVector>> *v) override
   {
      PYBIND11_OVERRIDE(void, G4TriangularFacet, SetVertices, v);
   }
};

void export_G4TriangularFacet(py::module &m)
{
   py::class_<G4TriangularFacet, PyG4TriangularFacet, G4VFacet>(m, "G4TriangularFacet")

      .def(py::init<>())
      .def(py::init<const G4ThreeVector &, const G4ThreeVector &, const G4ThreeVector &, G4FacetVertexType>(),
           py::arg("vt0"), py::arg("vt1"), py::arg("vt2"), py::arg("type"))

      .def("__copy__", [](const PyG4TriangularFacet &self) { return PyG4TriangularFacet(self); })
      .def("__deepcopy__", [](const PyG4TriangularFacet &self, py::dict) { return PyG4TriangularFacet(self); })
      .def("GetClone", &G4TriangularFacet::GetClone, py::return_value_policy::reference)
      .def("GetFlippedFacet", &G4TriangularFacet::GetFlippedFacet, py::return_value_policy::reference)
      .def("Distance", py::overload_cast<const G4ThreeVector &>(&G4TriangularFacet::Distance), py::arg("p"))
      .def("Distance", py::overload_cast<const G4ThreeVector &, G4double>(&G4TriangularFacet::Distance), py::arg("p"),
           py::arg("minDist"))

      .def("Distance", py::overload_cast<const G4ThreeVector &, G4double, const G4bool>(&G4TriangularFacet::Distance),
           py::arg("p"), py::arg("minDist"), py::arg("outgoing"))

      .def("Extent", &G4TriangularFacet::Extent, py::arg("axis"))
      .def("Intersect", &G4TriangularFacet::Intersect, py::arg("p"), py::arg("v"), py::arg("outgoing"),
           py::arg("distance"), py::arg("distFromSurface"), py::arg("normal"))

      .def("GetArea", &G4TriangularFacet::GetArea)
      .def("GetPointOnFace", &G4TriangularFacet::GetPointOnFace)
      .def("GetSurfaceNormal", &G4TriangularFacet::GetSurfaceNormal)
      .def("SetSurfaceNormal", &G4TriangularFacet::SetSurfaceNormal, py::arg("normal"))
      .def("GetEntityType", &G4TriangularFacet::GetEntityType)
      .def("IsDefined", &G4TriangularFacet::IsDefined)
      .def("GetNumberOfVertices", &G4TriangularFacet::GetNumberOfVertices)
      .def("GetVertex", &G4TriangularFacet::GetVertex, py::arg("i"))
      .def("SetVertex", &G4TriangularFacet::SetVertex, py::arg("i"), py::arg("val"))
      .def("GetCircumcentre", &G4TriangularFacet::GetCircumcentre)
      .def("GetRadius", &G4TriangularFacet::GetRadius)
      .def("AllocatedMemory", &G4TriangularFacet::AllocatedMemory)
      .def("GetVertexIndex", &G4TriangularFacet::GetVertexIndex, py::arg("i"))
      .def("SetVertexIndex", &G4TriangularFacet::SetVertexIndex, py::arg("i"), py::arg("j"))
      .def("SetVertices", &G4TriangularFacet::SetVertices, py::arg("v"));
}
