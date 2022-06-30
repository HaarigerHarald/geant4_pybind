#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NistMaterialBuilder.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>
#include <G4NistElementBuilder.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4NistMaterialBuilder(py::module &m)
{
   py::class_<G4NistMaterialBuilder>(m, "G4NistMaterialBuilder")

      .def(py::init<G4NistElementBuilder *, G4int>(), py::arg("arg0"), py::arg("verb") = 0)
      .def("ConstructNewGasMaterial", &G4NistMaterialBuilder::ConstructNewGasMaterial, py::arg("name"),
           py::arg("nameDB"), py::arg("temp"), py::arg("pres"), py::return_value_policy::reference)

      .def("ConstructNewIdealGasMaterial", &G4NistMaterialBuilder::ConstructNewIdealGasMaterial, py::arg("name"),
           py::arg("elm"), py::arg("nbAtoms"), py::arg("temp") = NTP_Temperature,
           py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"), py::return_value_policy::reference)

      .def("ConstructNewMaterial",
           py::overload_cast<const G4String &, const std::vector<G4String> &, const std::vector<int> &, G4double,
                             G4State, G4double, G4double>(&G4NistMaterialBuilder::ConstructNewMaterial),
           py::arg("name"), py::arg("elm"), py::arg("nbAtoms"), py::arg("dens"), py::arg("state") = kStateSolid,
           py::arg("temp") = NTP_Temperature, py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"),
           py::return_value_policy::reference)

      .def("ConstructNewMaterial",
           py::overload_cast<const G4String &, const std::vector<G4String> &, const std::vector<double> &, G4double,
                             G4State, G4double, G4double>(&G4NistMaterialBuilder::ConstructNewMaterial),
           py::arg("name"), py::arg("elm"), py::arg("weight"), py::arg("dens"), py::arg("state") = kStateSolid,
           py::arg("temp") = NTP_Temperature, py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"),
           py::return_value_policy::reference)

      .def("FindMaterial", &G4NistMaterialBuilder::FindMaterial, py::arg("name"), py::return_value_policy::reference)
      .def("FindOrBuildMaterial", &G4NistMaterialBuilder::FindOrBuildMaterial, py::arg("name"),
           py::arg("warning") = true, py::return_value_policy::reference)

      .def("FindOrBuildSimpleMaterial", &G4NistMaterialBuilder::FindOrBuildSimpleMaterial, py::arg("Z"),
           py::arg("warning"), py::return_value_policy::reference)

      .def("FindSimpleMaterial", &G4NistMaterialBuilder::FindSimpleMaterial, py::arg("Z"),
           py::return_value_policy::reference)

      .def("GetMaterialNames", &G4NistMaterialBuilder::GetMaterialNames)
      .def("GetMeanIonisationEnergy", &G4NistMaterialBuilder::GetMeanIonisationEnergy, py::arg("index"))
      .def("GetNominalDensity", &G4NistMaterialBuilder::GetNominalDensity, py::arg("index"))
      .def("ListBioChemicalMaterials", &G4NistMaterialBuilder::ListBioChemicalMaterials)
      .def("ListHepMaterials", &G4NistMaterialBuilder::ListHepMaterials)
      .def("ListMaterials", &G4NistMaterialBuilder::ListMaterials)
      .def("ListNistCompoundMaterials", &G4NistMaterialBuilder::ListNistCompoundMaterials)
      .def("ListNistSimpleMaterials", &G4NistMaterialBuilder::ListNistSimpleMaterials)
      .def("ListSpaceMaterials", &G4NistMaterialBuilder::ListSpaceMaterials)
      .def("SetVerbose", &G4NistMaterialBuilder::SetVerbose, py::arg("val"));
}
