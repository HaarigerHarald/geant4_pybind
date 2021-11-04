#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PolyhedraSide.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4SolidExtentList.hh>
#include <G4IntersectingCone.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4PolyhedraSide : public G4PolyhedraSide, public py::trampoline_self_life_support {
public:
   using G4PolyhedraSide::G4PolyhedraSide;

   G4bool Intersect(const G4ThreeVector &p, const G4ThreeVector &v, G4bool outgoing, G4double surfTolerance,
                    G4double &distance, G4double &distFromSurface, G4ThreeVector &normal, G4bool &allBehind) override
   {
      PYBIND11_OVERRIDE(G4bool, G4PolyhedraSide, Intersect, p, v, outgoing, surfTolerance, distance, distFromSurface,
                        normal, allBehind);
   }

   G4double Distance(const G4ThreeVector &p, G4bool outgoing) override
   {
      PYBIND11_OVERRIDE(G4double, G4PolyhedraSide, Distance, p, outgoing);
   }

   EInside Inside(const G4ThreeVector &p, G4double tolerance, G4double *bestDistance) override
   {
      PYBIND11_OVERRIDE(EInside, G4PolyhedraSide, Inside, p, tolerance, bestDistance);
   }

   G4ThreeVector Normal(const G4ThreeVector &p, G4double *bestDistance) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4PolyhedraSide, Normal, p, bestDistance);
   }

   G4double Extent(const G4ThreeVector axis) override { PYBIND11_OVERRIDE(G4double, G4PolyhedraSide, Extent, axis); }

   void CalculateExtent(const EAxis axis, const G4VoxelLimits &voxelLimit, const G4AffineTransform &tranform,
                        G4SolidExtentList &extentList) override
   {
      PYBIND11_OVERRIDE(void, G4PolyhedraSide, CalculateExtent, axis, voxelLimit, tranform, extentList);
   }

   G4VCSGface *Clone() override { PYBIND11_OVERRIDE(G4VCSGface *, G4PolyhedraSide, Clone, ); }

   G4double SurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4PolyhedraSide, SurfaceArea, ); }

   G4ThreeVector GetPointOnFace() override { PYBIND11_OVERRIDE(G4ThreeVector, G4PolyhedraSide, GetPointOnFace, ); }
};

void export_G4PolyhedraSide(py::module &m)
{
   py::class_<G4PolyhedraSideRZ>(m, "G4PolyhedraSideRZ")

      .def(py::init<>())
      .def("__copy__", [](const G4PolyhedraSideRZ &self) { return G4PolyhedraSideRZ(self); })
      .def("__deepcopy__", [](const G4PolyhedraSideRZ &self, py::dict) { return G4PolyhedraSideRZ(self); })
      .def_readwrite("r", &G4PolyhedraSideRZ::r)
      .def_readwrite("z", &G4PolyhedraSideRZ::z);

   py::class_<G4PhSideData>(m, "G4PhSideData")

      .def(py::init<>())
      .def("__copy__", [](const G4PhSideData &self) { return G4PhSideData(self); })
      .def("__deepcopy__", [](const G4PhSideData &self, py::dict) { return G4PhSideData(self); })
      .def("initialize", &G4PhSideData::initialize)
      .def_readwrite("fPhix", &G4PhSideData::fPhix)
      .def_readwrite("fPhiy", &G4PhSideData::fPhiy)
      .def_readwrite("fPhiz", &G4PhSideData::fPhiz)
      .def_readwrite("fPhik", &G4PhSideData::fPhik);

   py::class_<G4PolyhedraSide, PyG4PolyhedraSide, G4VCSGface, py::nodelete>(m, "G4PolyhedraSide")

      .def(py::init<const G4PolyhedraSideRZ *, const G4PolyhedraSideRZ *, const G4PolyhedraSideRZ *,
                    const G4PolyhedraSideRZ *, G4int, G4double, G4double, G4bool, G4bool>(),
           py::arg("prevRZ"), py::arg("tail"), py::arg("head"), py::arg("nextRZ"), py::arg("numSide"),
           py::arg("phiStart"), py::arg("phiTotal"), py::arg("phiIsOpen"), py::arg("isAllBehind") = false)

      .def("__copy__", [](const PyG4PolyhedraSide &self) { return PyG4PolyhedraSide(self); })
      .def("__deepcopy__", [](const PyG4PolyhedraSide &self, py::dict) { return PyG4PolyhedraSide(self); })
      .def("Intersect", &G4PolyhedraSide::Intersect, py::arg("p"), py::arg("v"), py::arg("outgoing"),
           py::arg("surfTolerance"), py::arg("distance"), py::arg("distFromSurface"), py::arg("normal"),
           py::arg("allBehind"))

      .def("Distance", &G4PolyhedraSide::Distance, py::arg("p"), py::arg("outgoing"))
      .def("Inside", &G4PolyhedraSide::Inside, py::arg("p"), py::arg("tolerance"), py::arg("bestDistance"))
      .def("Normal", &G4PolyhedraSide::Normal, py::arg("p"), py::arg("bestDistance"))
      .def("Extent", &G4PolyhedraSide::Extent, py::arg("axis"))

      .def("CalculateExtent", &G4PolyhedraSide::CalculateExtent, py::arg("axis"), py::arg("voxelLimit"),
           py::arg("tranform"), py::arg("extentList"))

      .def("Clone", &G4PolyhedraSide::Clone, py::return_value_policy::reference)
      .def("SurfaceTriangle", &G4PolyhedraSide::SurfaceTriangle, py::arg("p1"), py::arg("p2"), py::arg("p3"),
           py::arg("p4"))

      .def("GetPointOnPlane", &G4PolyhedraSide::GetPointOnPlane, py::arg("p0"), py::arg("p1"), py::arg("p2"),
           py::arg("p3"), py::arg("Area"))

      .def("SurfaceArea", &G4PolyhedraSide::SurfaceArea)
      .def("GetPointOnFace", &G4PolyhedraSide::GetPointOnFace)
      .def("GetInstanceID", &G4PolyhedraSide::GetInstanceID)
      .def_static("GetSubInstanceManager", &G4PolyhedraSide::GetSubInstanceManager);
}
