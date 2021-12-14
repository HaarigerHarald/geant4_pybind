#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ReplicatedSlice.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
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

#include "../management/pyG4VPhysicalVolume.hh"

namespace py = pybind11;

class RotationSharedG4ReplicatedSlice : public G4ReplicatedSlice, public SharedPhysicalVolumeRotation {
public:
   using G4ReplicatedSlice::G4ReplicatedSlice;
};

class PyG4ReplicatedSlice : public RotationSharedG4ReplicatedSlice, public py::trampoline_self_life_support {
public:
   using RotationSharedG4ReplicatedSlice::RotationSharedG4ReplicatedSlice;

   G4bool IsMany() const override { PYBIND11_OVERRIDE(G4bool, G4ReplicatedSlice, IsMany, ); }

   G4int GetCopyNo() const override { PYBIND11_OVERRIDE(G4int, G4ReplicatedSlice, GetCopyNo, ); }

   void SetCopyNo(G4int CopyNo) override { PYBIND11_OVERRIDE(void, G4ReplicatedSlice, SetCopyNo, CopyNo); }

   G4bool IsReplicated() const override { PYBIND11_OVERRIDE(G4bool, G4ReplicatedSlice, IsReplicated, ); }

   G4int GetMultiplicity() const override { PYBIND11_OVERRIDE(G4int, G4ReplicatedSlice, GetMultiplicity, ); }

   G4VPVParameterisation *GetParameterisation() const override
   {
      PYBIND11_OVERRIDE(G4VPVParameterisation *, G4ReplicatedSlice, GetParameterisation, );
   }

   void GetReplicationData(EAxis &axis, G4int &nReplicas, G4double &width, G4double &offset,
                           G4bool &consuming) const override
   {
      PYBIND11_OVERRIDE(void, G4ReplicatedSlice, GetReplicationData, axis, nReplicas, width, offset, consuming);
   }

   G4bool IsParameterised() const override { PYBIND11_OVERRIDE(G4bool, G4ReplicatedSlice, IsParameterised, ); }

   G4bool IsRegularStructure() const override { PYBIND11_OVERRIDE(G4bool, G4ReplicatedSlice, IsRegularStructure, ); }

   G4int GetRegularStructureId() const override
   {
      PYBIND11_OVERRIDE(G4int, G4ReplicatedSlice, GetRegularStructureId, );
   }

   G4bool CheckOverlaps(G4int res, G4double tol, G4bool verbose, G4int errMax) override
   {
      PYBIND11_OVERRIDE(G4bool, G4ReplicatedSlice, CheckOverlaps, res, tol, verbose, errMax);
   }
};

void export_G4ReplicatedSlice(py::module &m)
{
   py::class_<RotationSharedG4ReplicatedSlice, PyG4ReplicatedSlice, G4PVReplica, py::nodelete>(m, "G4ReplicatedSlice")

      .def(py::init<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int, const G4double,
                    const G4double, const G4double>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("half_gap"), py::arg("offset"))

      .def(py::init<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int, const G4double,
                    const G4double>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("half_gap"), py::arg("offset"))

      .def(py::init<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4double, const G4double,
                    const G4double>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("width"),
           py::arg("half_gap"), py::arg("offset"))

      .def(py::init<const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, const EAxis, const G4int, const G4double,
                    const G4double, const G4double>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherPhysical"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("half_gap"), py::arg("offset"))

      .def(py::init<const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, const EAxis, const G4int, const G4double,
                    const G4double>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherPhysical"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("half_gap"), py::arg("offset"))

      .def(py::init<const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, const EAxis, const G4double,
                    const G4double, const G4double>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherPhysical"), py::arg("pAxis"), py::arg("width"),
           py::arg("half_gap"), py::arg("offset"))

      .def("IsMany", &G4ReplicatedSlice::IsMany)
      .def("GetCopyNo", &G4ReplicatedSlice::GetCopyNo)
      .def("SetCopyNo", &G4ReplicatedSlice::SetCopyNo, py::arg("CopyNo"))
      .def("IsReplicated", &G4ReplicatedSlice::IsReplicated)
      .def("GetMultiplicity", &G4ReplicatedSlice::GetMultiplicity)
      .def("GetParameterisation", &G4ReplicatedSlice::GetParameterisation, py::return_value_policy::reference)

      .def("GetReplicationData", &G4ReplicatedSlice::GetReplicationData, py::arg("axis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"), py::arg("consuming"))

      .def("GetDivisionAxis", &G4ReplicatedSlice::GetDivisionAxis)
      .def("IsParameterised", &G4ReplicatedSlice::IsParameterised)
      .def("VolumeType", &G4ReplicatedSlice::VolumeType)
      .def("IsRegularStructure", &G4ReplicatedSlice::IsRegularStructure)
      .def("GetRegularStructureId", &G4ReplicatedSlice::GetRegularStructureId);
}
