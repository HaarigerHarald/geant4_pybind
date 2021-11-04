#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PolyPhiFace.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4SolidExtentList.hh>
#include <G4ReduciblePolygon.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4PolyPhiFace : public G4PolyPhiFace, public py::trampoline_self_life_support {
public:
   using G4PolyPhiFace::G4PolyPhiFace;

   G4bool Intersect(const G4ThreeVector &p, const G4ThreeVector &v, G4bool outgoing, G4double surfTolerance,
                    G4double &distance, G4double &distFromSurface, G4ThreeVector &normal, G4bool &allBehind) override
   {
      PYBIND11_OVERRIDE(G4bool, G4PolyPhiFace, Intersect, p, v, outgoing, surfTolerance, distance, distFromSurface,
                        normal, allBehind);
   }

   G4double Distance(const G4ThreeVector &p, G4bool outgoing) override
   {
      PYBIND11_OVERRIDE(G4double, G4PolyPhiFace, Distance, p, outgoing);
   }

   EInside Inside(const G4ThreeVector &p, G4double tolerance, G4double *bestDistance) override
   {
      PYBIND11_OVERRIDE(EInside, G4PolyPhiFace, Inside, p, tolerance, bestDistance);
   }

   G4ThreeVector Normal(const G4ThreeVector &p, G4double *bestDistance) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4PolyPhiFace, Normal, p, bestDistance);
   }

   G4double Extent(const G4ThreeVector axis) override { PYBIND11_OVERRIDE(G4double, G4PolyPhiFace, Extent, axis); }

   void CalculateExtent(const EAxis axis, const G4VoxelLimits &voxelLimit, const G4AffineTransform &tranform,
                        G4SolidExtentList &extentList) override
   {
      PYBIND11_OVERRIDE(void, G4PolyPhiFace, CalculateExtent, axis, voxelLimit, tranform, extentList);
   }

   G4VCSGface *Clone() override { PYBIND11_OVERRIDE(G4VCSGface *, G4PolyPhiFace, Clone, ); }

   G4double SurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4PolyPhiFace, SurfaceArea, ); }

   G4ThreeVector GetPointOnFace() override { PYBIND11_OVERRIDE(G4ThreeVector, G4PolyPhiFace, GetPointOnFace, ); }
};

void export_G4PolyPhiFace(py::module &m)
{
   py::class_<G4PolyPhiFaceVertex>(m, "G4PolyPhiFaceVertex")

      .def("__copy__", [](const G4PolyPhiFaceVertex &self) { return G4PolyPhiFaceVertex(self); })
      .def("__deepcopy__", [](const G4PolyPhiFaceVertex &self, py::dict) { return G4PolyPhiFaceVertex(self); })
      .def(py::init<>())
      .def_readwrite("x", &G4PolyPhiFaceVertex::x)
      .def_readwrite("y", &G4PolyPhiFaceVertex::y)
      .def_readwrite("r", &G4PolyPhiFaceVertex::r)
      .def_readwrite("z", &G4PolyPhiFaceVertex::z)
      .def_readwrite("rNorm", &G4PolyPhiFaceVertex::rNorm)
      .def_readwrite("zNorm", &G4PolyPhiFaceVertex::zNorm)
      .def_readwrite("norm3D", &G4PolyPhiFaceVertex::norm3D)
      .def_readwrite("ear", &G4PolyPhiFaceVertex::ear)
      .def_readwrite("next", &G4PolyPhiFaceVertex::next)
      .def_readwrite("prev", &G4PolyPhiFaceVertex::prev);

   py::class_<G4PolyPhiFaceEdge>(m, "G4PolyPhiFaceEdge")

      .def(py::init<>())
      .def("__copy__", [](const G4PolyPhiFaceEdge &self) { return G4PolyPhiFaceEdge(self); })
      .def("__deepcopy__", [](const G4PolyPhiFaceEdge &self, py::dict) { return G4PolyPhiFaceEdge(self); })
      .def_readwrite("v0", &G4PolyPhiFaceEdge::v0)
      .def_readwrite("v1", &G4PolyPhiFaceEdge::v1)
      .def_readwrite("tr", &G4PolyPhiFaceEdge::tr)
      .def_readwrite("tz", &G4PolyPhiFaceEdge::tz)
      .def_readwrite("length", &G4PolyPhiFaceEdge::length)
      .def_readwrite("norm3D", &G4PolyPhiFaceEdge::norm3D);

   py::class_<G4PolyPhiFace, PyG4PolyPhiFace, G4VCSGface>(m, "G4PolyPhiFace")

      .def(py::init<const G4ReduciblePolygon *, G4double, G4double, G4double>(), py::arg("rz"), py::arg("phi"),
           py::arg("deltaPhi"), py::arg("phiOther"))

      .def("__copy__", [](const PyG4PolyPhiFace &self) { return PyG4PolyPhiFace(self); })
      .def("__deepcopy__", [](const PyG4PolyPhiFace &self, py::dict) { return PyG4PolyPhiFace(self); })
      .def("Intersect",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, G4bool, G4double, G4double &, G4double &,
                             G4ThreeVector &, G4bool &>(&G4PolyPhiFace::Intersect),
           py::arg("p"), py::arg("v"), py::arg("outgoing"), py::arg("surfTolerance"), py::arg("distance"),
           py::arg("distFromSurface"), py::arg("normal"), py::arg("allBehind"))

      .def("Distance", &G4PolyPhiFace::Distance, py::arg("p"), py::arg("outgoing"))
      .def("Inside", &G4PolyPhiFace::Inside, py::arg("p"), py::arg("tolerance"), py::arg("bestDistance"))
      .def("Normal", &G4PolyPhiFace::Normal, py::arg("p"), py::arg("bestDistance"))
      .def("Extent", &G4PolyPhiFace::Extent, py::arg("axis"))
      .def("CalculateExtent", &G4PolyPhiFace::CalculateExtent, py::arg("axis"), py::arg("voxelLimit"),
           py::arg("tranform"), py::arg("extentList"))

      .def("Clone", &G4PolyPhiFace::Clone, py::return_value_policy::reference)
      .def("SurfaceArea", &G4PolyPhiFace::SurfaceArea)
      .def("SurfaceTriangle", &G4PolyPhiFace::SurfaceTriangle, py::arg("p1"), py::arg("p2"), py::arg("p3"),
           py::arg("p4"))

      .def("GetPointOnFace", &G4PolyPhiFace::GetPointOnFace)
      .def("Diagnose", &G4PolyPhiFace::Diagnose, py::arg("solid"));
}
