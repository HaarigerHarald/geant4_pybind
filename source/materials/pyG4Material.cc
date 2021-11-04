#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Material.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Material(py::module &m)
{
   py::enum_<G4State>(m, "G4State")
      .value("kStateUndefined", kStateUndefined)
      .value("kStateSolid", kStateSolid)
      .value("kStateLiquid", kStateLiquid)
      .value("kStateGas", kStateGas)
      .export_values();

   py::class_<G4Material, py::nodelete>(m, "G4Material", "material class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4State, G4double, G4double>(), py::arg("name"),
           py::arg("z"), py::arg("a"), py::arg("density"), py::arg("state") = kStateUndefined,
           py::arg("temp") = NTP_Temperature, py::arg("pressure") = CLHEP::STP_Pressure)

      .def(py::init<const G4String &, G4double, G4int, G4State, G4double, G4double>(), py::arg("name"),
           py::arg("density"), py::arg("nComponents"), py::arg("state") = kStateUndefined,
           py::arg("temp") = NTP_Temperature, py::arg("pressure") = CLHEP::STP_Pressure)

      .def(py::init<const G4String &, G4double, const G4Material *, G4State, G4double, G4double>(), py::arg("name"),
           py::arg("density"), py::arg("baseMaterial"), py::arg("state") = kStateUndefined,
           py::arg("temp") = NTP_Temperature, py::arg("pressure") = CLHEP::STP_Pressure)

      .def("AddElement", py::overload_cast<G4Element *, G4int>(&G4Material::AddElement))
      .def("AddElement", py::overload_cast<G4Element *, G4double>(&G4Material::AddElement))
      .def("AddMaterial", &G4Material::AddMaterial)
      .def("GetName", &G4Material::GetName, py::return_value_policy::reference)
      .def("GetChemicalFormula", &G4Material::GetChemicalFormula, py::return_value_policy::reference)
      .def("SetName", &G4Material::SetName)
      .def("SetChemicalFormula", &G4Material::SetChemicalFormula)
      .def("GetDensity", &G4Material::GetDensity)
      .def("GetState", &G4Material::GetState)
      .def("GetTemperature", &G4Material::GetTemperature)
      .def("GetPressure", &G4Material::GetPressure)

      .def("GetElementVector", &G4Material::GetElementVector, py::return_value_policy::reference)
      .def("GetElement", &G4Material::GetElement, py::return_value_policy::reference)
      .def("GetTotNbOfAtomsPerVolume", &G4Material::GetTotNbOfAtomsPerVolume)
      .def("GetTotNbOfElectPerVolume", &G4Material::GetTotNbOfElectPerVolume)
      .def("GetFractionVector",
           [](const G4Material *material) {
              py::list        fracList;
              const G4double *fracVec = material->GetFractionVector();
              size_t          nele    = material->GetNumberOfElements();
              for (size_t i = 0; i < nele; i++) {
                 fracList.append(fracVec[i]);
              }
              return fracList;
           })

      .def("GetAtomsVector",
           [](const G4Material *material) {
              py::list     atomsList;
              const G4int *atomsVec = material->GetAtomsVector();
              size_t       nele     = material->GetNumberOfElements();
              for (size_t i = 0; i < nele; i++) {
                 atomsList.append(atomsVec[i]);
              }
              return atomsList;
           })

      .def("GetVecNbOfAtomsPerVolume",
           [](const G4Material *material) {
              py::list        nbOfAtomsPerVolumeList;
              const G4double *nbOfAtomsPerVolumeVec = material->GetVecNbOfAtomsPerVolume();
              size_t          nele                  = material->GetNumberOfElements();
              for (size_t i = 0; i < nele; i++) {
                 nbOfAtomsPerVolumeList.append(nbOfAtomsPerVolumeVec[i]);
              }
              return nbOfAtomsPerVolumeList;
           })

      .def("GetAtomicNumDensityVector",
           [](const G4Material *material) {
              py::list        atomicNumDensityList;
              const G4double *atomicNumDensityVec = material->GetAtomicNumDensityVector();
              size_t          nele                = material->GetNumberOfElements();
              for (size_t i = 0; i < nele; i++) {
                 atomicNumDensityList.append(atomicNumDensityVec[i]);
              }
              return atomicNumDensityList;
           })

      .def("GetElectronDensity", &G4Material::GetElectronDensity)
      .def("GetRadlen", &G4Material::GetRadlen)
      .def("GetNuclearInterLength", &G4Material::GetNuclearInterLength)
      .def("GetIonisation", &G4Material::GetIonisation, py::return_value_policy::reference)
      .def("GetSandiaTable", &G4Material::GetSandiaTable, py::return_value_policy::reference)

      .def("GetZ", &G4Material::GetZ)
      .def("GetA", &G4Material::GetA)
      .def("SetMaterialPropertiesTable", &G4Material::SetMaterialPropertiesTable)
      .def("GetMaterialPropertiesTable", &G4Material::GetMaterialPropertiesTable, py::return_value_policy::reference)

      .def_static("GetMaterialTable", &G4Material::GetMaterialTable, py::return_value_policy::reference)
      .def_static("GetNumberOfMaterials", &G4Material::GetNumberOfMaterials)
      .def("GetIndex", &G4Material::GetIndex)
      .def_static("GetMaterial", py::overload_cast<const G4String &, G4bool>(&G4Material::GetMaterial), py::arg("name"),
                  py::arg("warning") = false, py::return_value_policy::reference)

      .def_static("GetMaterial", py::overload_cast<G4double, G4double, G4double>(&G4Material::GetMaterial),
                  py::return_value_policy::reference)

      .def_static("GetMaterial", py::overload_cast<size_t, G4double>(&G4Material::GetMaterial),
                  py::return_value_policy::reference)

      .def(
         "__str__",
         [](const G4Material &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator())

      .def("Print", [](const G4Material &self) { G4cout << self; });
}
