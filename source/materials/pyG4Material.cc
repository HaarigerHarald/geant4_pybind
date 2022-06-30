#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Material.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Material : public G4Material, public py::trampoline_self_life_support {
public:
   using G4Material::G4Material;

   G4bool IsExtended() const override { PYBIND11_OVERRIDE(G4bool, G4Material, IsExtended, ); }
};

void export_G4Material(py::module &m)
{
   py::enum_<G4State>(m, "G4State")
      .value("kStateUndefined", kStateUndefined)
      .value("kStateSolid", kStateSolid)
      .value("kStateLiquid", kStateLiquid)
      .value("kStateGas", kStateGas)
      .export_values();

   py::class_<G4Material, PyG4Material, py::nodelete>(m, "G4Material")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4State, G4double, G4double>(), py::arg("name"),
           py::arg("z"), py::arg("a"), py::arg("density"), py::arg("state") = kStateUndefined,
           py::arg_v("temp", NTP_Temperature, "NTP_Temperature"),
           py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"))

      .def(py::init<const G4String &, G4double, G4int, G4State, G4double, G4double>(), py::arg("name"),
           py::arg("density"), py::arg("nComponents"), py::arg("state") = kStateUndefined,
           py::arg_v("temp", NTP_Temperature, "NTP_Temperature"),
           py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"))

      .def(py::init<const G4String &, G4double, const G4Material *, G4State, G4double, G4double>(), py::arg("name"),
           py::arg("density"), py::arg("baseMaterial"), py::arg("state") = kStateUndefined,
           py::arg_v("temp", NTP_Temperature, "NTP_Temperature"),
           py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"))

      .def("AddElement", py::overload_cast<G4Element *, G4int>(&G4Material::AddElement), py::arg("elm"),
           py::arg("nAtoms"))

      .def("AddElement", py::overload_cast<G4Element *, G4double>(&G4Material::AddElement), py::arg("elm"),
           py::arg("frac"))

      .def("AddElementByMassFraction", &G4Material::AddElementByMassFraction, py::arg("elm"), py::arg("fraction"))
      .def("AddElementByNumberOfAtoms", &G4Material::AddElementByNumberOfAtoms, py::arg("elm"), py::arg("nAtoms"))
      .def("AddMaterial", &G4Material::AddMaterial, py::arg("material"), py::arg("fraction"))
      .def("ComputeDensityEffectOnFly", &G4Material::ComputeDensityEffectOnFly)
      .def("GetA", &G4Material::GetA)

      .def("GetAtomicNumDensityVector",
           [](const G4Material *material) {
              const G4double *atomicNumDensityVector = material->GetAtomicNumDensityVector();
              std::size_t     nele                   = material->GetNumberOfElements();

              return std::vector<G4double>(atomicNumDensityVector, atomicNumDensityVector + nele);
           })

      .def("GetAtomsVector",
           [](const G4Material *material) {
              const G4int *atomsVec = material->GetAtomsVector();
              size_t       nele     = material->GetNumberOfElements();

              return std::vector<G4double>(atomsVec, atomsVec + nele);
           })

      .def("GetBaseMaterial", &G4Material::GetBaseMaterial, py::return_value_policy::reference)
      .def("GetChemicalFormula", &G4Material::GetChemicalFormula)
      .def("GetDensity", &G4Material::GetDensity)
      .def("GetElectronDensity", &G4Material::GetElectronDensity)
      .def("GetElement", &G4Material::GetElement, py::arg("iel"), py::return_value_policy::reference)
      .def("GetElementVector", &G4Material::GetElementVector, py::return_value_policy::reference)
      .def("GetFractionVector",
           [](const G4Material *material) {
              const G4double *fracVec = material->GetFractionVector();
              size_t          nele    = material->GetNumberOfElements();

              return std::vector<G4double>(fracVec, fracVec + nele);
           })

      .def("GetFreeElectronDensity", &G4Material::GetFreeElectronDensity)
      .def("GetIndex", &G4Material::GetIndex)
      .def("GetIonisation", &G4Material::GetIonisation, py::return_value_policy::reference)
      .def("GetMassOfMolecule", &G4Material::GetMassOfMolecule)
      .def("GetMatComponents", &G4Material::GetMatComponents)
      .def_static("GetMaterial", py::overload_cast<const G4String &, G4bool>(&G4Material::GetMaterial), py::arg("name"),
                  py::arg("warning") = true, py::return_value_policy::reference)

      .def_static("GetMaterial", py::overload_cast<G4double, G4double, G4double>(&G4Material::GetMaterial),
                  py::arg("z"), py::arg("a"), py::arg("dens"), py::return_value_policy::reference)

      .def_static("GetMaterial", py::overload_cast<size_t, G4double>(&G4Material::GetMaterial), py::arg("nComp"),
                  py::arg("dens"), py::return_value_policy::reference)

      .def("GetMaterialPropertiesTable", &G4Material::GetMaterialPropertiesTable, py::return_value_policy::reference)
      .def_static("GetMaterialTable", &G4Material::GetMaterialTable, py::return_value_policy::reference)
      .def("GetName", &G4Material::GetName)
      .def("GetNuclearInterLength", &G4Material::GetNuclearInterLength)
      .def("GetNumberOfElements", &G4Material::GetNumberOfElements)
      .def_static("GetNumberOfMaterials", &G4Material::GetNumberOfMaterials)
      .def("GetPressure", &G4Material::GetPressure)
      .def("GetRadlen", &G4Material::GetRadlen)
      .def("GetSandiaTable", &G4Material::GetSandiaTable, py::return_value_policy::reference)
      .def("GetState", &G4Material::GetState)
      .def("GetTemperature", &G4Material::GetTemperature)
      .def("GetTotNbOfAtomsPerVolume", &G4Material::GetTotNbOfAtomsPerVolume)
      .def("GetTotNbOfElectPerVolume", &G4Material::GetTotNbOfElectPerVolume)
      .def("GetVecNbOfAtomsPerVolume",
           [](const G4Material *material) {
              const G4double *nbOfAtomsPerVolumeVec = material->GetVecNbOfAtomsPerVolume();
              size_t          nele                  = material->GetNumberOfElements();

              return std::vector<G4double>(nbOfAtomsPerVolumeVec, nbOfAtomsPerVolumeVec + nele);
           })

      .def("GetZ", &G4Material::GetZ)
      .def("IsExtended", &G4Material::IsExtended)
      .def("SetChemicalFormula", &G4Material::SetChemicalFormula, py::arg("chF"))
      .def("SetFreeElectronDensity", &G4Material::SetFreeElectronDensity)
      .def(
         "SetMaterialPropertiesTable",
         [](G4Material &self, py::disown_ptr<G4MaterialPropertiesTable> anMPT) {
            self.SetMaterialPropertiesTable(anMPT);
         },
         py::arg("anMPT"))

      .def("SetName", &G4Material::SetName, py::arg("name"))
      .def(
         "__str__",
         [](const G4Material &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
