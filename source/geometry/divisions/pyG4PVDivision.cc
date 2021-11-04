#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PVDivision.hh>
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

class RotationSharedG4PVDivision : public G4PVDivision, public SharedPhysicalVolumeRotation {
public:
   using G4PVDivision::G4PVDivision;
};

class PyG4PVDivision : public RotationSharedG4PVDivision, public py::trampoline_self_life_support {
public:
   using RotationSharedG4PVDivision::RotationSharedG4PVDivision;

   G4bool IsMany() const override { PYBIND11_OVERRIDE(G4bool, G4PVDivision, IsMany, ); }

   G4int GetCopyNo() const override { PYBIND11_OVERRIDE(G4int, G4PVDivision, GetCopyNo, ); }

   void SetCopyNo(G4int CopyNo) override { PYBIND11_OVERRIDE(void, G4PVDivision, SetCopyNo, CopyNo); }

   G4bool IsReplicated() const override { PYBIND11_OVERRIDE(G4bool, G4PVDivision, IsReplicated, ); }

   G4int GetMultiplicity() const override { PYBIND11_OVERRIDE(G4int, G4PVDivision, GetMultiplicity, ); }

   G4VPVParameterisation *GetParameterisation() const override
   {
      PYBIND11_OVERRIDE(G4VPVParameterisation *, G4PVDivision, GetParameterisation, );
   }

   void GetReplicationData(EAxis &axis, G4int &nReplicas, G4double &width, G4double &offset,
                           G4bool &consuming) const override
   {
      PYBIND11_OVERRIDE(void, G4PVDivision, GetReplicationData, axis, nReplicas, width, offset, consuming);
   }

   G4bool IsParameterised() const override { PYBIND11_OVERRIDE(G4bool, G4PVDivision, IsParameterised, ); }

   EVolume VolumeType() const override { PYBIND11_OVERRIDE(EVolume, G4PVDivision, VolumeType, ); }

   G4bool IsRegularStructure() const override { PYBIND11_OVERRIDE(G4bool, G4PVDivision, IsRegularStructure, ); }

   G4int GetRegularStructureId() const override { PYBIND11_OVERRIDE(G4int, G4PVDivision, GetRegularStructureId, ); }

   G4bool CheckOverlaps(G4int res, G4double tol, G4bool verbose, G4int errMax) override
   {
      PYBIND11_OVERRIDE(G4bool, G4PVDivision, CheckOverlaps, res, tol, verbose, errMax);
   }
};

void export_G4PVDivision(py::module &m)
{
   py::class_<RotationSharedG4PVDivision, PyG4PVDivision, G4VPhysicalVolume, py::nodelete>(m, "G4PVDivision")

      .def(py::init<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int, const G4double,
                    const G4double>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMother"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"))

      .def(py::init<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int, const G4double>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("offset"))

      .def(py::init<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4double,
                    const G4double>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("width"),
           py::arg("offset"))

      .def(py::init<const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, const EAxis, const G4int, const G4double,
                    const G4double>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMother"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"))

      .def("IsMany", &G4PVDivision::IsMany)
      .def("GetCopyNo", &G4PVDivision::GetCopyNo)
      .def("SetCopyNo", &G4PVDivision::SetCopyNo, py::arg("CopyNo"))
      .def("IsReplicated", &G4PVDivision::IsReplicated)
      .def("GetMultiplicity", &G4PVDivision::GetMultiplicity)
      .def("GetParameterisation", &G4PVDivision::GetParameterisation, py::return_value_policy::reference)

      .def("GetReplicationData", &G4PVDivision::GetReplicationData, py::arg("axis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"), py::arg("consuming"))

      .def("GetDivisionAxis", &G4PVDivision::GetDivisionAxis)
      .def("IsParameterised", &G4PVDivision::IsParameterised)
      .def("VolumeType", &G4PVDivision::VolumeType)
      .def("IsRegularStructure", &G4PVDivision::IsRegularStructure)
      .def("GetRegularStructureId", &G4PVDivision::GetRegularStructureId);
}
