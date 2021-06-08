
#ifdef G4_HAS_GDML
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GDMLParser.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GDMLParser(py::module &m)
{
   py::class_<G4GDMLParser>(m, "G4GDMLParser", "GDML parser")
      .def(py::init<>())
      .def("Read", &G4GDMLParser::Read, py::arg("filename"), py::arg("validate") = true)
      .def("ReadModule", &G4GDMLParser::ReadModule, py::arg("filename"), py::arg("validate") = true)
      .def("ParseST", &G4GDMLParser::ParseST, py::return_value_policy::reference)
      .def(
         "Write",
         py::overload_cast<const G4String &, const G4VPhysicalVolume *, G4bool, const G4String &>(&G4GDMLParser::Write),
         py::arg("filename"), py::arg("pvol") = static_cast<const G4VPhysicalVolume *>(nullptr), py::arg("refs") = true,
         py::arg("schemaLocation") = G4GDML_DEFAULT_SCHEMALOCATION)

      .def("Write",
           py::overload_cast<const G4String &, const G4LogicalVolume *, G4bool, const G4String &>(&G4GDMLParser::Write),
           py::arg("filename"), py::arg("lvol"), py::arg("refs") = true,
           py::arg("schemaLocation") = G4GDML_DEFAULT_SCHEMALOCATION)

      .def("GetWorldVolume", &G4GDMLParser::GetWorldVolume, py::arg("setupName") = "Default",
           py::return_value_policy::reference);
}
#endif // G4_HAS_GDML
