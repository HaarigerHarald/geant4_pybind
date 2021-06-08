#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NistManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4NistManager(py::module &m)
{

   py::class_<G4NistManager, py::nodelete>(m, "G4NistManager", "manager class for NIST materials")

      .def_static("Instance", &G4NistManager::Instance, py::return_value_policy::reference)

      .def("SetVerbose", &G4NistManager::SetVerbose)
      .def("GetVerbose", &G4NistManager::GetVerbose)

      .def("GetElement", &G4NistManager::GetElement, py::return_value_policy::reference)
      .def("FindOrBuildElement", py::overload_cast<G4int, G4bool>(&G4NistManager::FindOrBuildElement),
           py::return_value_policy::reference)

      .def("FindOrBuildElement", py::overload_cast<const G4String &, G4bool>(&G4NistManager::FindOrBuildElement),
           py::return_value_policy::reference)

      .def("GetNumberOfElements", &G4NistManager::GetNumberOfElements)
      .def("GetZ", &G4NistManager::GetZ)
      .def("GetIsotopeMass", &G4NistManager::GetIsotopeMass)
      .def("PrintElement", py::overload_cast<const G4String &>(&G4NistManager::PrintElement, py::const_))
      .def("PrintElement", py::overload_cast<G4int>(&G4NistManager::PrintElement, py::const_))
      .def("PrintG4Element", &G4NistManager::PrintG4Element)

      .def("GetMaterial", &G4NistManager::GetMaterial, py::return_value_policy::reference)
      .def("FindOrBuildMaterial", &G4NistManager::FindOrBuildMaterial, py::arg("name"), py::arg("isotopes") = true,
           py::arg("warning") = false, py::return_value_policy::reference)

      .def("ConstructNewMaterial",
           py::overload_cast<const G4String &, const std::vector<G4String> &, const std::vector<G4int> &, G4double,
                             G4bool, G4State, G4double, G4double>(&G4NistManager::ConstructNewMaterial),
           py::arg("name"), py::arg("elm"), py::arg("w"), py::arg("dens"), py::arg("isotopes") = true,
           py::arg("state") = kStateSolid, py::arg("T") = NTP_Temperature, py::arg("P") = CLHEP::STP_Pressure,
           py::return_value_policy::reference)

      .def("ConstructNewMaterial",
           py::overload_cast<const G4String &, const std::vector<G4String> &, const std::vector<G4double> &, G4double,
                             G4bool, G4State, G4double, G4double>(&G4NistManager::ConstructNewMaterial),
           py::arg("name"), py::arg("elm"), py::arg("w"), py::arg("dens"), py::arg("isotopes") = true,
           py::arg("state") = kStateSolid, py::arg("T") = NTP_Temperature, py::arg("P") = CLHEP::STP_Pressure,
           py::return_value_policy::reference)

      .def("ConstructNewGasMaterial", &G4NistManager::ConstructNewGasMaterial, py::arg("name"), py::arg("nameNist"),
           py::arg("temp"), py::arg("pres"), py::arg("isotopes") = true, py::return_value_policy::reference)

      .def("GetNumberOfMaterials", &G4NistManager::GetNumberOfMaterials)
      .def("ListMaterials", &G4NistManager::ListMaterials)
      .def("PrintG4Material", &G4NistManager::PrintG4Material);
}
