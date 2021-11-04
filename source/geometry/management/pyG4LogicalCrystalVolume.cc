#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4LogicalCrystalVolume.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VPVParameterisation.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VSolid.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4VisAttributes.hh>
#include <G4CrystalExtension.hh>
#include <G4ExtendedMaterial.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4LogicalCrystalVolume : public G4LogicalCrystalVolume, public py::trampoline_self_life_support {
public:
   using G4LogicalCrystalVolume::G4LogicalCrystalVolume;

   G4bool IsExtended() const override { PYBIND11_OVERRIDE(G4bool, G4LogicalCrystalVolume, IsExtended, ); }
};

void export_G4LogicalCrystalVolume(py::module &m)
{
   py::class_<G4LogicalCrystalVolume, PyG4LogicalCrystalVolume, G4LogicalVolume, py::nodelete>(m,
                                                                                               "G4LogicalCrystalVolume")

      .def(py::init_alias<G4VSolid *, G4ExtendedMaterial *, const G4String &, G4FieldManager *, G4VSensitiveDetector *,
                          G4UserLimits *, G4bool, G4int, G4int, G4int, G4double>(),
           py::arg("pSolid"), py::arg("pMaterial"), py::arg("name"),
           py::arg("pFieldMgr")  = static_cast<G4FieldManager *>(nullptr),
           py::arg("pSDetector") = static_cast<G4VSensitiveDetector *>(nullptr),
           py::arg("pULimits") = static_cast<G4UserLimits *>(nullptr), py::arg("optimise") = true, py::arg("h") = 0,
           py::arg("k") = 0, py::arg("l") = 0, py::arg("rot") = 0., py::keep_alive<1, 5>(), py::keep_alive<1, 6>(),
           py::keep_alive<1, 7>())

      .def("IsExtended", &G4LogicalCrystalVolume::IsExtended)
      .def("SetMillerOrientation", &G4LogicalCrystalVolume::SetMillerOrientation, py::arg("h"), py::arg("k"),
           py::arg("l"), py::arg("rot") = 0.)

      .def("RotateToLattice", &G4LogicalCrystalVolume::RotateToLattice, py::arg("dir"))
      .def("RotateToSolid", &G4LogicalCrystalVolume::RotateToSolid, py::arg("dir"))
      .def("GetCrystal", &G4LogicalCrystalVolume::GetCrystal, py::return_value_policy::reference)
      .def("GetBasis", &G4LogicalCrystalVolume::GetBasis, py::arg("i"))
      .def("SetVerbose", &G4LogicalCrystalVolume::SetVerbose, py::arg("aInt"))
      .def_static("IsLattice", &G4LogicalCrystalVolume::IsLattice, py::arg("aLV"));
}
