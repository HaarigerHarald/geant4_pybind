#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MaterialPropertiesTable.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4MaterialPropertiesTable(py::module &m)
{
   py::class_<G4MaterialPropertiesTable>(m, "G4MaterialPropertiesTable", "material properties table class")

      .def("__copy__", [](const G4MaterialPropertiesTable &self) { return new G4MaterialPropertiesTable(self); })
      .def("__deepcopy__",
           [](const G4MaterialPropertiesTable &self, py::dict) { return new G4MaterialPropertiesTable(self); })

      .def(py::init<>())
      .def("AddConstProperty",
           py::overload_cast<const G4String &, G4double, G4bool>(&G4MaterialPropertiesTable::AddConstProperty),
           py::arg("key"), py::arg("propertyValue"), py::arg("createNewKey") = false)

      .def("AddConstProperty",
           py::overload_cast<const char *, G4double, G4bool>(&G4MaterialPropertiesTable::AddConstProperty),
           py::arg("key"), py::arg("propertyValue"), py::arg("createNewKey") = false)

      .def("AddEntry", py::overload_cast<const G4String &, G4double, G4double>(&G4MaterialPropertiesTable::AddEntry),
           py::arg("key"), py::arg("aPhotonEnergy"), py::arg("aPropertyValue"))

      .def("AddEntry", py::overload_cast<const char *, G4double, G4double>(&G4MaterialPropertiesTable::AddEntry),
           py::arg("key"), py::arg("aPhotonEnergy"), py::arg("aPropertyValue"))

      .def(
         "AddProperty",
         py::overload_cast<const G4String &, const std::vector<double> &, const std::vector<double> &, G4bool, G4bool>(
            &G4MaterialPropertiesTable::AddProperty),
         py::arg("key"), py::arg("photonEnergies"), py::arg("propertyValues"), py::arg("createNewKey") = false,
         py::arg("spline") = false, py::return_value_policy::reference)

      .def(
         "AddProperty",
         [](G4MaterialPropertiesTable &self, const char *key, G4double *photonEnergies, G4double *propertyValues,
            G4int numEntries, G4bool createNewKey, G4bool spline) {
            return std::make_tuple(
               self.AddProperty(key, photonEnergies, propertyValues, numEntries, createNewKey, spline), photonEnergies,
               propertyValues);
         },
         py::arg("key"), py::arg("photonEnergies"), py::arg("propertyValues"), py::arg("numEntries"),
         py::arg("createNewKey") = false, py::arg("spline") = false, py::return_value_policy::automatic_reference)

      .def("AddProperty",
           py::overload_cast<const G4String &, G4MaterialPropertyVector *, G4bool>(
              &G4MaterialPropertiesTable::AddProperty),
           py::arg("key"), py::arg("opv"), py::arg("createNewKey") = false)

      .def("AddProperty",
           py::overload_cast<const char *, G4MaterialPropertyVector *, G4bool>(&G4MaterialPropertiesTable::AddProperty),
           py::arg("key"), py::arg("opv"), py::arg("createNewKey") = false)

      .def("AddProperty",
           py::overload_cast<const G4String &, const G4String &>(&G4MaterialPropertiesTable::AddProperty),
           py::arg("key"), py::arg("mat"))

      .def("ConstPropertyExists",
           py::overload_cast<const G4String &>(&G4MaterialPropertiesTable::ConstPropertyExists, py::const_),
           py::arg("key"))

      .def("ConstPropertyExists",
           py::overload_cast<const char *>(&G4MaterialPropertiesTable::ConstPropertyExists, py::const_), py::arg("key"))

      .def("ConstPropertyExists",
           py::overload_cast<const G4int>(&G4MaterialPropertiesTable::ConstPropertyExists, py::const_),
           py::arg("index"))

      .def("DumpTable", &G4MaterialPropertiesTable::DumpTable)
      .def("GetConstProperties", &G4MaterialPropertiesTable::GetConstProperties)
      .def("GetConstProperty",
           py::overload_cast<const G4String &>(&G4MaterialPropertiesTable::GetConstProperty, py::const_),
           py::arg("key"))

      .def("GetConstProperty",
           py::overload_cast<const char *>(&G4MaterialPropertiesTable::GetConstProperty, py::const_), py::arg("key"))

      .def("GetConstProperty", py::overload_cast<const G4int>(&G4MaterialPropertiesTable::GetConstProperty, py::const_),
           py::arg("index"))

      .def("GetConstPropertyIndex", &G4MaterialPropertiesTable::GetConstPropertyIndex, py::arg("key"))
      .def("GetMaterialConstPropertyNames", &G4MaterialPropertiesTable::GetMaterialConstPropertyNames)
      .def("GetMaterialPropertyNames", &G4MaterialPropertiesTable::GetMaterialPropertyNames)
      .def("GetProperties", &G4MaterialPropertiesTable::GetProperties)
      .def("GetProperty", py::overload_cast<const char *>(&G4MaterialPropertiesTable::GetProperty, py::const_),
           py::arg("key"), py::return_value_policy::reference)

      .def("GetProperty", py::overload_cast<const G4String &>(&G4MaterialPropertiesTable::GetProperty, py::const_),
           py::arg("key"), py::return_value_policy::reference)

      .def("GetProperty", py::overload_cast<const G4int>(&G4MaterialPropertiesTable::GetProperty, py::const_),
           py::arg("index"), py::return_value_policy::reference)

      .def("GetPropertyIndex", &G4MaterialPropertiesTable::GetPropertyIndex, py::arg("key"))
      .def("RemoveConstProperty", py::overload_cast<const G4String &>(&G4MaterialPropertiesTable::RemoveConstProperty),
           py::arg("key"))

      .def("RemoveConstProperty", py::overload_cast<const char *>(&G4MaterialPropertiesTable::RemoveConstProperty),
           py::arg("key"))

      .def("RemoveProperty", py::overload_cast<const G4String &>(&G4MaterialPropertiesTable::RemoveProperty),
           py::arg("key"))

      .def("RemoveProperty", py::overload_cast<const char *>(&G4MaterialPropertiesTable::RemoveProperty),
           py::arg("key"));
}
