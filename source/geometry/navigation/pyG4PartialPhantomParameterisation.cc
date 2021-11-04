#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PartialPhantomParameterisation.hh>
#include <G4Material.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VTouchable.hh>
#include <G4VSolid.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Trd.hh>
#include <G4Trap.hh>
#include <G4Cons.hh>
#include <G4Sphere.hh>
#include <G4Orb.hh>
#include <G4Ellipsoid.hh>
#include <G4Torus.hh>
#include <G4Para.hh>
#include <G4Polycone.hh>
#include <G4Polyhedra.hh>
#include <G4Hype.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4PartialPhantomParameterisation : public G4PartialPhantomParameterisation,
                                           public py::trampoline_self_life_support {
public:
   using G4PartialPhantomParameterisation::G4PartialPhantomParameterisation;

   void ComputeTransformation(const G4int arg0, G4VPhysicalVolume *arg1) const override
   {
      PYBIND11_OVERRIDE(void, G4PartialPhantomParameterisation, ComputeTransformation, arg0, arg1);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4PartialPhantomParameterisation, ComputeMaterial, repNo, currentVol,
                        parentTouch);
   }

   G4int GetReplicaNo(const G4ThreeVector &localPoint, const G4ThreeVector &localDir) override
   {
      PYBIND11_OVERRIDE(G4int, G4PartialPhantomParameterisation, GetReplicaNo, localPoint, localDir);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4PartialPhantomParameterisation, ComputeSolid, arg0, arg1);
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PartialPhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1,
                             arg2);
      return G4PartialPhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4PartialPhantomParameterisation, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4PartialPhantomParameterisation, GetMaterialScanner, );
   }
};

void export_G4PartialPhantomParameterisation(py::module &m)
{
   py::class_<G4PartialPhantomParameterisation, PyG4PartialPhantomParameterisation, G4PhantomParameterisation>(
      m, "G4PartialPhantomParameterisation")

      .def(py::init<>())
      .def("__copy__",
           [](const PyG4PartialPhantomParameterisation &self) { return PyG4PartialPhantomParameterisation(self); })

      .def("__deepcopy__", [](const PyG4PartialPhantomParameterisation &self,
                              py::dict) { return PyG4PartialPhantomParameterisation(self); })

      .def("ComputeTransformation", &G4PartialPhantomParameterisation::ComputeTransformation)
      .def("ComputeMaterial", &G4PartialPhantomParameterisation::ComputeMaterial, py::arg("repNo"),
           py::arg("currentVol"), py::arg("parentTouch") = static_cast<const G4VTouchable *>(nullptr),
           py::return_value_policy::reference)

      .def("GetReplicaNo", &G4PartialPhantomParameterisation::GetReplicaNo, py::arg("localPoint"), py::arg("localDir"))
      .def("GetTranslation", &G4PartialPhantomParameterisation::GetTranslation, py::arg("copyNo"))
      .def("GetMaterialIndex",
           py::overload_cast<size_t, size_t, size_t>(&G4PartialPhantomParameterisation::GetMaterialIndex, py::const_),
           py::arg("nx"), py::arg("ny"), py::arg("nz"))

      .def("GetMaterialIndex",
           py::overload_cast<size_t>(&G4PartialPhantomParameterisation::GetMaterialIndex, py::const_),
           py::arg("copyNo"))

      .def("GetMaterial",
           py::overload_cast<size_t, size_t, size_t>(&G4PartialPhantomParameterisation::GetMaterial, py::const_),
           py::arg("nx"), py::arg("ny"), py::arg("nz"), py::return_value_policy::reference)

      .def("GetMaterial", py::overload_cast<size_t>(&G4PartialPhantomParameterisation::GetMaterial, py::const_),
           py::arg("copyNo"), py::return_value_policy::reference)

      .def("SetFilledIDs", &G4PartialPhantomParameterisation::SetFilledIDs, py::arg("fid"))
      .def("SetFilledMins", &G4PartialPhantomParameterisation::SetFilledMins, py::arg("fmins"))
      .def("BuildContainerWalls", &G4PartialPhantomParameterisation::BuildContainerWalls);
}
