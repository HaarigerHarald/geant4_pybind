#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NistManager.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>
#include <G4NistMessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4NistManager(py::module &m)
{
   py::class_<G4NistManager, py::nodelete>(m, "G4NistManager")

      .def("BuildMaterialWithNewDensity", &G4NistManager::BuildMaterialWithNewDensity, py::arg("name"),
           py::arg("basename"), py::arg("density") = 0., py::arg("temp") = NTP_Temperature,
           py::arg_v("pres", CLHEP::STP_Pressure, "STP_Pressure"), py::return_value_policy::reference)

      .def("ConstructNewGasMaterial", &G4NistManager::ConstructNewGasMaterial, py::arg("name"), py::arg("nameNist"),
           py::arg("temp"), py::arg("pres"), py::arg("isotopes") = true, py::return_value_policy::reference)

      .def("ConstructNewIdealGasMaterial", &G4NistManager::ConstructNewIdealGasMaterial, py::arg("name"),
           py::arg("elm"), py::arg("nbAtoms"), py::arg("isotopes") = true, py::arg("temp") = NTP_Temperature,
           py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"), py::return_value_policy::reference)

      .def("ConstructNewMaterial",
           py::overload_cast<const G4String &, const std::vector<G4String> &, const std::vector<int> &, G4double,
                             G4bool, G4State, G4double, G4double>(&G4NistManager::ConstructNewMaterial),
           py::arg("name"), py::arg("elm"), py::arg("nbAtoms"), py::arg("dens"), py::arg("isotopes") = true,
           py::arg("state") = kStateSolid, py::arg("temp") = NTP_Temperature,
           py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"), py::return_value_policy::reference)

      .def("ConstructNewMaterial",
           py::overload_cast<const G4String &, const std::vector<G4String> &, const std::vector<double> &, G4double,
                             G4bool, G4State, G4double, G4double>(&G4NistManager::ConstructNewMaterial),
           py::arg("name"), py::arg("elm"), py::arg("weight"), py::arg("dens"), py::arg("isotopes") = true,
           py::arg("state") = kStateSolid, py::arg("temp") = NTP_Temperature,
           py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"), py::return_value_policy::reference)

      .def("FindElement", &G4NistManager::FindElement, py::arg("Z"), py::return_value_policy::reference)
      .def("FindMaterial", &G4NistManager::FindMaterial, py::arg("name"), py::return_value_policy::reference)
      .def("FindOrBuildElement", py::overload_cast<G4int, G4bool>(&G4NistManager::FindOrBuildElement), py::arg("Z"),
           py::arg("isotopes") = true, py::return_value_policy::reference)

      .def("FindOrBuildElement", py::overload_cast<const G4String &, G4bool>(&G4NistManager::FindOrBuildElement),
           py::arg("symb"), py::arg("isotopes") = true, py::return_value_policy::reference)

      .def("FindOrBuildMaterial", &G4NistManager::FindOrBuildMaterial, py::arg("name"), py::arg("isotopes") = true,
           py::arg("warning") = false, py::return_value_policy::reference)

      .def("FindOrBuildSimpleMaterial", &G4NistManager::FindOrBuildSimpleMaterial, py::arg("Z"),
           py::arg("warning") = false, py::return_value_policy::reference)

      .def("FindSimpleMaterial", &G4NistManager::FindSimpleMaterial, py::arg("Z"), py::return_value_policy::reference)
      .def("GetA27", &G4NistManager::GetA27, py::arg("Z"))
      .def("GetAtomicMass", &G4NistManager::GetAtomicMass, py::arg("Z"), py::arg("N"))
      .def("GetAtomicMassAmu", py::overload_cast<const G4String &>(&G4NistManager::GetAtomicMassAmu, py::const_),
           py::arg("symb"))

      .def("GetAtomicMassAmu", py::overload_cast<G4int>(&G4NistManager::GetAtomicMassAmu, py::const_), py::arg("Z"))
      .def("GetElement", &G4NistManager::GetElement, py::arg("index"), py::return_value_policy::reference)
      .def("GetICRU90StoppingData", &G4NistManager::GetICRU90StoppingData, py::return_value_policy::reference)
      .def("GetIsotopeAbundance", &G4NistManager::GetIsotopeAbundance, py::arg("Z"), py::arg("N"))
      .def("GetIsotopeMass", &G4NistManager::GetIsotopeMass, py::arg("Z"), py::arg("N"))
      .def("GetLOGAMU", &G4NistManager::GetLOGAMU, py::arg("Z"))
      .def("GetLOGZ", &G4NistManager::GetLOGZ, py::arg("Z"))
      .def("GetMaterial", &G4NistManager::GetMaterial, py::arg("index"), py::return_value_policy::reference)
      .def("GetMeanIonisationEnergy", &G4NistManager::GetMeanIonisationEnergy, py::arg("Z"))
      .def("GetNistElementNames", &G4NistManager::GetNistElementNames)
      .def("GetNistFirstIsotopeN", &G4NistManager::GetNistFirstIsotopeN, py::arg("Z"))
      .def("GetNistMaterialNames", &G4NistManager::GetNistMaterialNames)
      .def("GetNominalDensity", &G4NistManager::GetNominalDensity, py::arg("Z"))
      .def("GetNumberOfElements", &G4NistManager::GetNumberOfElements)
      .def("GetNumberOfMaterials", &G4NistManager::GetNumberOfMaterials)
      .def("GetNumberOfNistIsotopes", &G4NistManager::GetNumberOfNistIsotopes, py::arg("Z"))
      .def("GetTotalElectronBindingEnergy", &G4NistManager::GetTotalElectronBindingEnergy, py::arg("Z"))
      .def("GetVerbose", &G4NistManager::GetVerbose)
      .def("GetZ", &G4NistManager::GetZ, py::arg("symb"))
      .def("GetZ13", py::overload_cast<G4double>(&G4NistManager::GetZ13, py::const_), py::arg("Z"))
      .def("GetZ13", py::overload_cast<G4int>(&G4NistManager::GetZ13, py::const_), py::arg("Z"))
      .def_static("Instance", &G4NistManager::Instance, py::return_value_policy::reference)
      .def("ListMaterials", &G4NistManager::ListMaterials)
      .def("PrintElement", py::overload_cast<G4int>(&G4NistManager::PrintElement, py::const_), py::arg("Z"))
      .def("PrintElement", py::overload_cast<const G4String &>(&G4NistManager::PrintElement, py::const_))
      .def("PrintG4Element", &G4NistManager::PrintG4Element)
      .def("PrintG4Material", &G4NistManager::PrintG4Material)
      .def("SetDensityEffectCalculatorFlag",
           py::overload_cast<const G4String &, G4bool>(&G4NistManager::SetDensityEffectCalculatorFlag))

      .def("SetDensityEffectCalculatorFlag",
           py::overload_cast<G4Material *, G4bool>(&G4NistManager::SetDensityEffectCalculatorFlag))

      .def("SetVerbose", &G4NistManager::SetVerbose);
}
