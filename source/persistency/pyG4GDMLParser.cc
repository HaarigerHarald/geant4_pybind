#ifdef G4_HAS_GDML

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GDMLParser.hh>
#include <G4Element.hh>
#include <G4Isotope.hh>
#include <G4Material.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VisAttributes.hh>
#include <G4QuadrangularFacet.hh>
#include <G4TriangularFacet.hh>
#include <G4SurfaceProperty.hh>
#include <G4OpticalSurface.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4SolidExtentList.hh>
#include <G4IntersectingCone.hh>
#include <G4EnclosingCylinder.hh>
#include <G4ReduciblePolygon.hh>
#include <G4ClippablePolygon.hh>
#include <G4AssemblyVolume.hh>
#include <G4BooleanSolid.hh>
#include <G4ScaledSolid.hh>
#include <G4EllipticalCone.hh>
#include <G4EllipticalTube.hh>
#include <G4Paraboloid.hh>
#include <G4GenericPolycone.hh>
#include <G4Tet.hh>
#include <G4GenericTrap.hh>
#include <G4CutTubs.hh>
#include <G4TwistedBox.hh>
#include <G4TwistedTrap.hh>
#include <G4TwistedTrd.hh>
#include <G4TwistedTubs.hh>
#include <G4PVDivision.hh>
#include <G4LogicalBorderSurface.hh>
#include <G4LogicalSkinSurface.hh>
#include <G4ReflectionFactory.hh>
#include <G4AssemblyTriplet.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithABool.hh>
#include <G4ProductionCuts.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VSensitiveDetector.hh>
#include <G4Allocator.hh>
#include <G4ReferenceCountedHandle.hh>
#include <G4VoxelSafety.hh>
#include <G4PathFinder.hh>
#include <G4PropagatorInField.hh>
#include <G4GeometryMessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GDMLParser(py::module &m)
{
   py::class_<G4GDMLParser>(m, "G4GDMLParser")

      .def(py::init<>())
      .def(py::init<G4GDMLReadStructure *>())
      .def(py::init<G4GDMLReadStructure *, G4GDMLWriteStructure *>())
      .def("AddAuxiliary", &G4GDMLParser::AddAuxiliary, py::arg("myaux"))
      .def("AddModule", py::overload_cast<const G4VPhysicalVolume *>(&G4GDMLParser::AddModule), py::arg("physvol"))
      .def("AddModule", py::overload_cast<const G4int>(&G4GDMLParser::AddModule), py::arg("depth"))
      .def("AddVolumeAuxiliary", &G4GDMLParser::AddVolumeAuxiliary, py::arg("myaux"), py::arg("lvol"))
      .def("Clear", &G4GDMLParser::Clear)
      .def("GetAuxList", &G4GDMLParser::GetAuxList, py::return_value_policy::reference)
      .def("GetAuxMap", &G4GDMLParser::GetAuxMap, py::return_value_policy::reference)
      .def("GetConstant", &G4GDMLParser::GetConstant, py::arg("name"))
      .def("GetMatrix", &G4GDMLParser::GetMatrix, py::arg("name"))
      .def("GetMaxExportLevel", &G4GDMLParser::GetMaxExportLevel)
      .def("GetPhysVolume", &G4GDMLParser::GetPhysVolume, py::arg("name"), py::return_value_policy::reference)
      .def("GetPosition", &G4GDMLParser::GetPosition, py::arg("name"))
      .def("GetQuantity", &G4GDMLParser::GetQuantity, py::arg("name"))
      .def("GetRotation", &G4GDMLParser::GetRotation, py::arg("name"))
      .def("GetScale", &G4GDMLParser::GetScale, py::arg("name"))
      .def("GetVariable", &G4GDMLParser::GetVariable, py::arg("name"))
      .def("GetVolume", &G4GDMLParser::GetVolume, py::arg("name"), py::return_value_policy::reference)
      .def("GetVolumeAuxiliaryInformation", &G4GDMLParser::GetVolumeAuxiliaryInformation, py::arg("lvol"))
      .def("GetWorldVolume", &G4GDMLParser::GetWorldVolume, py::arg("setupName") = "Default",
           py::return_value_policy::reference)

      .def("IsValid", &G4GDMLParser::IsValid, py::arg("name"))
      .def("ParseST", &G4GDMLParser::ParseST, py::arg("name"), py::arg("medium"), py::arg("solid"),
           py::return_value_policy::reference)

      .def("Read", &G4GDMLParser::Read, py::arg("filename"), py::arg("Validate") = true)
      .def("ReadModule", &G4GDMLParser::ReadModule, py::arg("filename"), py::arg("Validate") = true)
      .def("SetAddPointerToName", &G4GDMLParser::SetAddPointerToName, py::arg("set"))
      .def("SetEnergyCutsExport", &G4GDMLParser::SetEnergyCutsExport)
      .def("SetMaxExportLevel", &G4GDMLParser::SetMaxExportLevel)
      .def("SetOutputFileOverwrite", &G4GDMLParser::SetOutputFileOverwrite, py::arg("flag"))
      .def("SetOverlapCheck", &G4GDMLParser::SetOverlapCheck)
      .def("SetRegionExport", &G4GDMLParser::SetRegionExport)
      .def("SetSDExport", &G4GDMLParser::SetSDExport)
      .def("SetStripFlag", &G4GDMLParser::SetStripFlag)
      .def("StripNamePointers", &G4GDMLParser::StripNamePointers)
      .def(
         "Write",
         py::overload_cast<const G4String &, const G4VPhysicalVolume *, G4bool, const G4String &>(&G4GDMLParser::Write),
         py::arg("filename"), py::arg("pvol") = static_cast<const G4VPhysicalVolume *>(nullptr),
         py::arg("storeReferences") = true, py::arg("SchemaLocation") = G4GDML_DEFAULT_SCHEMALOCATION)

      .def("Write",
           py::overload_cast<const G4String &, const G4LogicalVolume *, G4bool, const G4String &>(&G4GDMLParser::Write),
           py::arg("filename"), py::arg("lvol"), py::arg("storeReferences") = true,
           py::arg("SchemaLocation") = G4GDML_DEFAULT_SCHEMALOCATION);
}

#endif // G4_HAS_GDML
