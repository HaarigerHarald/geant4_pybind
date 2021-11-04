#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4QuadrangularFacet.hh>
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

class PyG4QuadrangularFacet : public G4QuadrangularFacet, public py::trampoline_self_life_support {
public:
   using G4QuadrangularFacet::G4QuadrangularFacet;

   G4int AllocatedMemory() override { PYBIND11_OVERRIDE_PURE(G4int, G4QuadrangularFacet, AllocatedMemory, ); }

   void SetVertexIndex(G4int i, G4int j) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4QuadrangularFacet, SetVertexIndex, i, j);
   }

   G4int GetVertexIndex(G4int i) const override
   {
      PYBIND11_OVERRIDE_PURE(G4int, G4QuadrangularFacet, GetVertexIndex, i);
   }

   G4VFacet *GetClone() override { PYBIND11_OVERRIDE(G4VFacet *, G4QuadrangularFacet, GetClone, ); }

   G4double Distance(const G4ThreeVector &p, G4double minDist) override
   {
      PYBIND11_OVERRIDE(G4double, G4QuadrangularFacet, Distance, p, minDist);
   }

   G4double Distance(const G4ThreeVector &p, G4double minDist, const G4bool outgoing) override
   {
      PYBIND11_OVERRIDE(G4double, G4QuadrangularFacet, Distance, p, minDist, outgoing);
   }

   G4double Extent(const G4ThreeVector axis) override
   {
      PYBIND11_OVERRIDE(G4double, G4QuadrangularFacet, Extent, axis);
   }

   G4bool Intersect(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool outgoing, G4double &distance,
                    G4double &distFromSurface, G4ThreeVector &normal) override
   {
      PYBIND11_OVERRIDE(G4bool, G4QuadrangularFacet, Intersect, p, v, outgoing, distance, distFromSurface, normal);
   }

   G4ThreeVector GetSurfaceNormal() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4QuadrangularFacet, GetSurfaceNormal, );
   }

   G4double GetArea() const override { PYBIND11_OVERRIDE(G4double, G4QuadrangularFacet, GetArea, ); }

   G4ThreeVector GetPointOnFace() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4QuadrangularFacet, GetPointOnFace, );
   }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4QuadrangularFacet, GetEntityType, );
   }

   G4bool IsDefined() const override { PYBIND11_OVERRIDE(G4bool, G4QuadrangularFacet, IsDefined, ); }

   G4int GetNumberOfVertices() const override { PYBIND11_OVERRIDE(G4int, G4QuadrangularFacet, GetNumberOfVertices, ); }

   G4ThreeVector GetVertex(G4int i) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4QuadrangularFacet, GetVertex, i);
   }

   void SetVertex(G4int i, const G4ThreeVector &val) override
   {
      PYBIND11_OVERRIDE(void, G4QuadrangularFacet, SetVertex, i, val);
   }

   void SetVertices(std::vector<G4ThreeVector, std::allocator<G4ThreeVector>> *v) override
   {
      PYBIND11_OVERRIDE(void, G4QuadrangularFacet, SetVertices, v);
   }

   G4double GetRadius() const override { PYBIND11_OVERRIDE(G4double, G4QuadrangularFacet, GetRadius, ); }

   G4ThreeVector GetCircumcentre() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4QuadrangularFacet, GetCircumcentre, );
   }
};

void export_G4QuadrangularFacet(py::module &m)
{
   py::class_<G4QuadrangularFacet, PyG4QuadrangularFacet, G4VFacet>(m, "G4QuadrangularFacet")

      .def(py::init<const G4ThreeVector &, const G4ThreeVector &, const G4ThreeVector &, const G4ThreeVector &,
                    G4FacetVertexType>(),
           py::arg("Pt0"), py::arg("vt1"), py::arg("vt2"), py::arg("vt3"), py::arg("type"))

      .def("__copy__", [](const PyG4QuadrangularFacet &self) { return PyG4QuadrangularFacet(self); })
      .def("__deepcopy__", [](const PyG4QuadrangularFacet &self, py::dict) { return PyG4QuadrangularFacet(self); })
      .def("GetClone", &G4QuadrangularFacet::GetClone, py::return_value_policy::reference)
      .def("Distance", py::overload_cast<const G4ThreeVector &>(&G4QuadrangularFacet::Distance), py::arg("p"))
      .def("Distance", py::overload_cast<const G4ThreeVector &, G4double>(&G4QuadrangularFacet::Distance), py::arg("p"),
           py::arg("minDist"))

      .def("Distance", py::overload_cast<const G4ThreeVector &, G4double, const G4bool>(&G4QuadrangularFacet::Distance),
           py::arg("p"), py::arg("minDist"), py::arg("outgoing"))

      .def("Extent", &G4QuadrangularFacet::Extent, py::arg("axis"))
      .def("Intersect", &G4QuadrangularFacet::Intersect, py::arg("p"), py::arg("v"), py::arg("outgoing"),
           py::arg("distance"), py::arg("distFromSurface"), py::arg("normal"))

      .def("GetSurfaceNormal", &G4QuadrangularFacet::GetSurfaceNormal)
      .def("GetArea", &G4QuadrangularFacet::GetArea)
      .def("GetPointOnFace", &G4QuadrangularFacet::GetPointOnFace)
      .def("GetEntityType", &G4QuadrangularFacet::GetEntityType)
      .def("IsDefined", &G4QuadrangularFacet::IsDefined)
      .def("GetNumberOfVertices", &G4QuadrangularFacet::GetNumberOfVertices)
      .def("GetVertex", &G4QuadrangularFacet::GetVertex, py::arg("i"))
      .def("SetVertex", &G4QuadrangularFacet::SetVertex, py::arg("i"), py::arg("val"))
      .def("SetVertices", &G4QuadrangularFacet::SetVertices, py::arg("v"))
      .def("GetRadius", &G4QuadrangularFacet::GetRadius)
      .def("GetCircumcentre", &G4QuadrangularFacet::GetCircumcentre);
}
