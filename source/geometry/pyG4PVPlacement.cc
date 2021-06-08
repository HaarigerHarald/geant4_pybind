#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4PVPlacement(py::module &m)
{
   py::class_<G4PVPlacement, G4VPhysicalVolume, py::nodelete>(m, "G4PVPlacement", "physical volume placement")

      .def(py::init<>([](py::disown_ptr<G4RotationMatrix> pRot, const G4ThreeVector &tlate, const G4String &pName,
                         G4LogicalVolume *pLogical, G4VPhysicalVolume *pMother, G4bool pMany, G4int pCopyNo,
                         G4bool pSurfChk) {
              return new G4PVPlacement(pRot, tlate, pName, pLogical, pMother, pMany, pCopyNo, pSurfChk);
           }),
           py::arg("pRot"), py::arg("tlate"), py::arg("pName"), py::arg("pLogical"), py::arg("pMother"),
           py::arg("pMany"), py::arg("pCopyNo"), py::arg("pSurfChk") = false, py::keep_alive<1, 2>(),
           py::keep_alive<1, 5>(), py::keep_alive<6, 1>())

      .def(py::init<>([](py::disown_ptr<G4RotationMatrix> pRot, const G4ThreeVector &tlate,
                         G4LogicalVolume *pCurrentLogical, const G4String &pName, G4LogicalVolume *pMotherLogical,
                         G4bool pMany, G4int pCopyNo, G4bool pSurfChk) {
              return new G4PVPlacement(pRot, tlate, pCurrentLogical, pName, pMotherLogical, pMany, pCopyNo, pSurfChk);
           }),
           py::arg("pRot"), py::arg("tlate"), py::arg("pCurrentLogical"), py::arg("pName"), py::arg("pMotherLogical"),
           py::arg("pMany"), py::arg("pCopyNo"), py::arg("pSurfChk") = false, py::keep_alive<1, 2>(),
           py::keep_alive<1, 4>(), py::keep_alive<6, 1>())

      .def(py::init<const G4Transform3D &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int>(),
           py::keep_alive<1, 3>(), py::keep_alive<5, 1>())

      .def(py::init<const G4Transform3D &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int>(),
           py::keep_alive<1, 4>(), py::keep_alive<5, 1>())

      .def(py::init<const G4Transform3D &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int,
                    G4bool>(),
           py::keep_alive<1, 3>(), py::keep_alive<5, 1>())

      .def(py::init<const G4Transform3D &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int,
                    G4bool>(),
           py::keep_alive<1, 4>(), py::keep_alive<5, 1>())

      .def("CheckOverlaps", &G4PVPlacement::CheckOverlaps, py::arg("res") = 1000, py::arg("tol") = 0.0,
           py::arg("verbose") = true, py::arg("maxErr") = 1)

      .def("IsMany", &G4PVPlacement::IsMany)
      .def("IsReplicated", &G4PVPlacement::IsReplicated)
      .def("IsParameterised", &G4PVPlacement::IsParameterised)
      .def("GetParameterisation", &G4PVPlacement::GetParameterisation)
      .def("GetReplicationData", &G4PVPlacement::GetReplicationData)
      .def("IsRegularStructure", &G4PVPlacement::IsRegularStructure)
      .def("GetRegularStructureId", &G4PVPlacement::GetRegularStructureId)
      .def("VolumeType", &G4PVPlacement::VolumeType);
}
