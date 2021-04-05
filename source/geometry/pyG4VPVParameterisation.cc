#include <pybind11/pybind11.h>

#include <G4VPVParameterisation.hh>
#include <G4PVReplica.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VTouchable.hh>
#include <G4VSolid.hh>
#include <G4Material.hh>
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
#include <G4VVolumeMaterialScanner.hh>

#include "typecast.hh"

namespace py = pybind11;

class PyG4VPVParameterisation : public G4VPVParameterisation {
public:
   using G4VPVParameterisation::G4VPVParameterisation;

   void ComputeTransformation(const G4int i, G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VPVParameterisation, ComputeTransformation, i, vol);
   }

   G4VSolid *ComputeSolid(const G4int i, G4VPhysicalVolume *vol) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VPVParameterisation, ComputeSolid, i, vol);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch = nullptr) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VPVParameterisation, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VPVParameterisation, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VPVParameterisation, GetMaterialScanner, );
   }

   void ComputeDimensions(G4Box &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Tubs &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Trd &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Trap &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Cons &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Sphere &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Orb &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Ellipsoid &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Torus &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Para &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Polycone &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Polyhedra &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }

   void ComputeDimensions(G4Hype &solid, const G4int copyNo, const G4VPhysicalVolume *vol) const override
   {
      PYBIND11_OVERRIDE(void, G4VPVParameterisation, ComputeDimensions, solid, copyNo, vol);
   }
};

void export_G4VPVParameterisation(py::module &m)
{
   py::class_<G4VPVParameterisation, PyG4VPVParameterisation, std::unique_ptr<G4VPVParameterisation, py::nodelete>>(
      m, "G4VPVParameterisation")

      .def(py::init<>())
      .def("ComputeTransformation", &G4VPVParameterisation::ComputeTransformation)
      .def("ComputeSolid", &G4VPVParameterisation::ComputeSolid)
      .def("ComputeMaterial", &G4VPVParameterisation::ComputeMaterial, py::arg("repNo"), py::arg("currentVol"),
           py::arg("parentTouch") = static_cast<const G4VTouchable *>(nullptr))

      .def("IsNested", &G4VPVParameterisation::IsNested)
      .def("GetMaterialScanner", &G4VPVParameterisation::GetMaterialScanner)

      .def("ComputeDimensions", py::overload_cast<G4Box &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Tubs &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Trd &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Trap &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Cons &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Sphere &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Orb &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Ellipsoid &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Torus &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Para &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Polycone &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Polyhedra &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Hype &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_));
}
