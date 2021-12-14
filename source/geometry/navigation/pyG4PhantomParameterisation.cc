#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PhantomParameterisation.hh>
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

class PyG4PhantomParameterisation : public G4PhantomParameterisation, public py::trampoline_self_life_support {
public:
   using G4PhantomParameterisation::G4PhantomParameterisation;

   void ComputeTransformation(const G4int arg0, G4VPhysicalVolume *arg1) const override
   {
      PYBIND11_OVERRIDE(void, G4PhantomParameterisation, ComputeTransformation, arg0, arg1);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4PhantomParameterisation, ComputeSolid, arg0, arg1);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4PhantomParameterisation, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4PhantomParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4PhantomParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   G4int GetReplicaNo(const G4ThreeVector &localPoint, const G4ThreeVector &localDir) override
   {
      PYBIND11_OVERRIDE(G4int, G4PhantomParameterisation, GetReplicaNo, localPoint, localDir);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4PhantomParameterisation, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4PhantomParameterisation, GetMaterialScanner, );
   }
};

void export_G4PhantomParameterisation(py::module &m)
{
   py::class_<G4PhantomParameterisation, PyG4PhantomParameterisation, G4VPVParameterisation>(
      m, "G4PhantomParameterisation")

      .def(py::init<>())
      .def("__copy__", [](const PyG4PhantomParameterisation &self) { return PyG4PhantomParameterisation(self); })
      .def("__deepcopy__",
           [](const PyG4PhantomParameterisation &self, py::dict) { return PyG4PhantomParameterisation(self); })

      .def("ComputeTransformation", &G4PhantomParameterisation::ComputeTransformation)
      .def("ComputeSolid", &G4PhantomParameterisation::ComputeSolid, py::return_value_policy::reference)

      .def("ComputeMaterial", &G4PhantomParameterisation::ComputeMaterial, py::arg("repNo"), py::arg("currentVol"),
           py::arg("parentTouch") = static_cast<const G4VTouchable *>(nullptr), py::return_value_policy::reference)

      .def("ComputeDimensions", py::overload_cast<G4Box &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Tubs &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Trd &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Trap &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Cons &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Orb &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Sphere &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Ellipsoid &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Torus &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Para &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Hype &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Polycone &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Polyhedra &, const G4int, const G4VPhysicalVolume *>(
                                   &G4PhantomParameterisation::ComputeDimensions, py::const_))

      .def("BuildContainerSolid",
           py::overload_cast<G4VPhysicalVolume *>(&G4PhantomParameterisation::BuildContainerSolid),
           py::arg("pPhysicalVol"))

      .def("BuildContainerSolid", py::overload_cast<G4VSolid *>(&G4PhantomParameterisation::BuildContainerSolid),
           py::arg("pMotherSolid"))

      .def("GetReplicaNo", &G4PhantomParameterisation::GetReplicaNo, py::arg("localPoint"), py::arg("localDir"))
      .def("SetMaterials", &G4PhantomParameterisation::SetMaterials, py::arg("mates"))
      .def("SetMaterialIndices", &G4PhantomParameterisation::SetMaterialIndices, py::arg("matInd"))
      .def("SetVoxelDimensions", &G4PhantomParameterisation::SetVoxelDimensions, py::arg("halfx"), py::arg("halfy"),
           py::arg("halfz"))

      .def("SetNoVoxels", &G4PhantomParameterisation::SetNoVoxels, py::arg("nx"), py::arg("ny"), py::arg("nz"))
      .def("GetVoxelHalfX", &G4PhantomParameterisation::GetVoxelHalfX)
      .def("GetVoxelHalfY", &G4PhantomParameterisation::GetVoxelHalfY)
      .def("GetVoxelHalfZ", &G4PhantomParameterisation::GetVoxelHalfZ)
      .def("GetNoVoxelsX", &G4PhantomParameterisation::GetNoVoxelsX)
      .def("GetNoVoxelsY", &G4PhantomParameterisation::GetNoVoxelsY)
      .def("GetNoVoxelsZ", &G4PhantomParameterisation::GetNoVoxelsZ)
      .def("GetNoVoxels", &G4PhantomParameterisation::GetNoVoxels)
      .def("GetMaterials", &G4PhantomParameterisation::GetMaterials)
      .def("GetMaterialIndices", &G4PhantomParameterisation::GetMaterialIndices, py::return_value_policy::reference)
      .def("GetContainerSolid", &G4PhantomParameterisation::GetContainerSolid, py::return_value_policy::reference)
      .def("GetTranslation", &G4PhantomParameterisation::GetTranslation, py::arg("copyNo"))
      .def("SkipEqualMaterials", &G4PhantomParameterisation::SkipEqualMaterials)
      .def("SetSkipEqualMaterials", &G4PhantomParameterisation::SetSkipEqualMaterials, py::arg("skip"))
      .def("GetMaterialIndex",
           py::overload_cast<size_t, size_t, size_t>(&G4PhantomParameterisation::GetMaterialIndex, py::const_),
           py::arg("nx"), py::arg("ny"), py::arg("nz"))

      .def("GetMaterialIndex", py::overload_cast<size_t>(&G4PhantomParameterisation::GetMaterialIndex, py::const_),
           py::arg("copyNo"))

      .def("GetMaterial",
           py::overload_cast<size_t, size_t, size_t>(&G4PhantomParameterisation::GetMaterial, py::const_),
           py::arg("nx"), py::arg("ny"), py::arg("nz"), py::return_value_policy::reference)

      .def("GetMaterial", py::overload_cast<size_t>(&G4PhantomParameterisation::GetMaterial, py::const_),
           py::arg("copyNo"), py::return_value_policy::reference)

      .def("CheckVoxelsFillContainer", &G4PhantomParameterisation::CheckVoxelsFillContainer, py::arg("contX"),
           py::arg("contY"), py::arg("contZ"));
}
