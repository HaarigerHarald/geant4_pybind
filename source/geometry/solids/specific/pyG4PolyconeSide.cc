#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PolyconeSide.hh>
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

class PyG4PolyconeSide : public G4PolyconeSide, public py::trampoline_self_life_support {
public:
   using G4PolyconeSide::G4PolyconeSide;

   G4bool Intersect(const G4ThreeVector &p, const G4ThreeVector &v, G4bool outgoing, G4double surfTolerance,
                    G4double &distance, G4double &distFromSurface, G4ThreeVector &normal, G4bool &isAllBehind) override
   {
      PYBIND11_OVERRIDE(G4bool, G4PolyconeSide, Intersect, p, v, outgoing, surfTolerance, distance, distFromSurface,
                        normal, isAllBehind);
   }

   G4double Distance(const G4ThreeVector &p, G4bool outgoing) override
   {
      PYBIND11_OVERRIDE(G4double, G4PolyconeSide, Distance, p, outgoing);
   }

   EInside Inside(const G4ThreeVector &p, G4double tolerance, G4double *bestDistance) override
   {
      PYBIND11_OVERRIDE(EInside, G4PolyconeSide, Inside, p, tolerance, bestDistance);
   }

   G4ThreeVector Normal(const G4ThreeVector &p, G4double *bestDistance) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4PolyconeSide, Normal, p, bestDistance);
   }

   G4double Extent(const G4ThreeVector axis) override { PYBIND11_OVERRIDE(G4double, G4PolyconeSide, Extent, axis); }

   void CalculateExtent(const EAxis axis, const G4VoxelLimits &voxelLimit, const G4AffineTransform &tranform,
                        G4SolidExtentList &extentList) override
   {
      PYBIND11_OVERRIDE(void, G4PolyconeSide, CalculateExtent, axis, voxelLimit, tranform, extentList);
   }

   G4VCSGface *Clone() override { PYBIND11_OVERRIDE(G4VCSGface *, G4PolyconeSide, Clone, ); }

   G4double SurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4PolyconeSide, SurfaceArea, ); }

   G4ThreeVector GetPointOnFace() override { PYBIND11_OVERRIDE(G4ThreeVector, G4PolyconeSide, GetPointOnFace, ); }
};

void export_G4PolyconeSide(py::module &m)
{
   py::class_<G4PolyconeSideRZ>(m, "G4PolyconeSideRZ")

      .def(py::init<>())
      .def("__copy__", [](const G4PolyconeSideRZ &self) { return G4PolyconeSideRZ(self); })
      .def("__deepcopy__", [](const G4PolyconeSideRZ &self, py::dict) { return G4PolyconeSideRZ(self); })
      .def_readwrite("r", &G4PolyconeSideRZ::r)
      .def_readwrite("z", &G4PolyconeSideRZ::z);

   py::class_<G4PlSideData>(m, "G4PlSideData")

      .def(py::init<>())
      .def("__copy__", [](const G4PlSideData &self) { return G4PlSideData(self); })
      .def("__deepcopy__", [](const G4PlSideData &self, py::dict) { return G4PlSideData(self); })
      .def("initialize", &G4PlSideData::initialize)
      .def_readwrite("fPhix", &G4PlSideData::fPhix)
      .def_readwrite("fPhiy", &G4PlSideData::fPhiy)
      .def_readwrite("fPhiz", &G4PlSideData::fPhiz)
      .def_readwrite("fPhik", &G4PlSideData::fPhik);

   py::class_<G4PolyconeSide, PyG4PolyconeSide, G4VCSGface, py::nodelete>(m, "G4PolyconeSide")

      .def(py::init<const G4PolyconeSideRZ *, const G4PolyconeSideRZ *, const G4PolyconeSideRZ *,
                    const G4PolyconeSideRZ *, G4double, G4double, G4bool, G4bool>(),
           py::arg("prevRZ"), py::arg("tail"), py::arg("head"), py::arg("nextRZ"), py::arg("phiStart"),
           py::arg("deltaPhi"), py::arg("phiIsOpen"), py::arg("isAllBehind") = false)

      .def("__copy__", [](const PyG4PolyconeSide &self) { return PyG4PolyconeSide(self); })
      .def("__deepcopy__", [](const PyG4PolyconeSide &self, py::dict) { return PyG4PolyconeSide(self); })
      .def("Intersect", &G4PolyconeSide::Intersect, py::arg("p"), py::arg("v"), py::arg("outgoing"),
           py::arg("surfTolerance"), py::arg("distance"), py::arg("distFromSurface"), py::arg("normal"),
           py::arg("isAllBehind"))

      .def("Distance", &G4PolyconeSide::Distance, py::arg("p"), py::arg("outgoing"))
      .def("Inside", &G4PolyconeSide::Inside, py::arg("p"), py::arg("tolerance"), py::arg("bestDistance"))
      .def("Normal", &G4PolyconeSide::Normal, py::arg("p"), py::arg("bestDistance"))
      .def("Extent", &G4PolyconeSide::Extent, py::arg("axis"))
      .def("CalculateExtent", &G4PolyconeSide::CalculateExtent, py::arg("axis"), py::arg("voxelLimit"),
           py::arg("tranform"), py::arg("extentList"))

      .def("Clone", &G4PolyconeSide::Clone, py::return_value_policy::reference)
      .def("SurfaceArea", &G4PolyconeSide::SurfaceArea)
      .def("GetPointOnFace", &G4PolyconeSide::GetPointOnFace)
      .def("GetInstanceID", &G4PolyconeSide::GetInstanceID)
      .def_static("GetSubInstanceManager", &G4PolyconeSide::GetSubInstanceManager);
}
