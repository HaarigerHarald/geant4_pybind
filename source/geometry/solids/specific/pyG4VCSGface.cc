#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VCSGface.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4SolidExtentList.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VCSGface : public G4VCSGface, public py::trampoline_self_life_support {
public:
   using G4VCSGface::G4VCSGface;

   G4bool Intersect(const G4ThreeVector &p, const G4ThreeVector &v, G4bool outgoing, G4double surfTolerance,
                    G4double &distance, G4double &distFromSurface, G4ThreeVector &normal, G4bool &allBehind) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VCSGface, Intersect, p, v, outgoing, surfTolerance, distance, distFromSurface,
                             normal, allBehind);
   }

   G4double Distance(const G4ThreeVector &p, G4bool outgoing) override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VCSGface, Distance, p, outgoing);
   }

   EInside Inside(const G4ThreeVector &p, G4double tolerance, G4double *bestDistance) override
   {
      PYBIND11_OVERRIDE_PURE(EInside, G4VCSGface, Inside, p, tolerance, bestDistance);
   }

   G4ThreeVector Normal(const G4ThreeVector &p, G4double *bestDistance) override
   {
      PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4VCSGface, Normal, p, bestDistance);
   }

   G4double Extent(const G4ThreeVector axis) override { PYBIND11_OVERRIDE_PURE(G4double, G4VCSGface, Extent, axis); }

   void CalculateExtent(const EAxis axis, const G4VoxelLimits &voxelLimit, const G4AffineTransform &tranform,
                        G4SolidExtentList &extentList) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VCSGface, CalculateExtent, axis, voxelLimit, tranform, extentList);
   }

   G4VCSGface *Clone() override { PYBIND11_OVERRIDE_PURE(G4VCSGface *, G4VCSGface, Clone, ); }

   G4double SurfaceArea() override { PYBIND11_OVERRIDE_PURE(G4double, G4VCSGface, SurfaceArea, ); }

   G4ThreeVector GetPointOnFace() override { PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4VCSGface, GetPointOnFace, ); }
};

void export_G4VCSGface(py::module &m)
{
   py::class_<G4VCSGface, PyG4VCSGface>(m, "G4VCSGface")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VCSGface &self) { return PyG4VCSGface(self); })
      .def("__deepcopy__", [](const PyG4VCSGface &self, py::dict) { return PyG4VCSGface(self); })
      .def("Intersect", &G4VCSGface::Intersect, py::arg("p"), py::arg("v"), py::arg("outgoing"),
           py::arg("surfTolerance"), py::arg("distance"), py::arg("distFromSurface"), py::arg("normal"),
           py::arg("allBehind"))

      .def("Distance", &G4VCSGface::Distance, py::arg("p"), py::arg("outgoing"))
      .def("Inside", &G4VCSGface::Inside, py::arg("p"), py::arg("tolerance"), py::arg("bestDistance"))
      .def("Normal", &G4VCSGface::Normal, py::arg("p"), py::arg("bestDistance"))
      .def("Extent", &G4VCSGface::Extent, py::arg("axis"))
      .def("CalculateExtent", &G4VCSGface::CalculateExtent, py::arg("axis"), py::arg("voxelLimit"), py::arg("tranform"),
           py::arg("extentList"))

      .def("Clone", &G4VCSGface::Clone, py::return_value_policy::reference)
      .def("SurfaceArea", &G4VCSGface::SurfaceArea)
      .def("GetPointOnFace", &G4VCSGface::GetPointOnFace);
}
