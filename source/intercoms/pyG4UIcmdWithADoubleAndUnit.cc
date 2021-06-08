#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UIcmdWithADoubleAndUnit : public G4UIcmdWithADoubleAndUnit {
public:
   using G4UIcmdWithADoubleAndUnit::G4UIcmdWithADoubleAndUnit;

   G4int DoIt(G4String parameterList) override
   {
      PYBIND11_OVERRIDE(G4int, G4UIcmdWithADoubleAndUnit, DoIt, parameterList);
   }
};

void export_G4UIcmdWithADoubleAndUnit(py::module &m)
{
   py::class_<G4UIcmdWithADoubleAndUnit, PyG4UIcmdWithADoubleAndUnit, G4UIcommand>(m, "G4UIcmdWithADoubleAndUnit")

      .def(py::init<const char *, G4UImessenger *>(), py::arg("theCommandPath"), py::arg("theMessenger"))
      .def("DoIt", &G4UIcmdWithADoubleAndUnit::DoIt)
      .def_static("GetNewDoubleValue", &G4UIcmdWithADoubleAndUnit::GetNewDoubleValue)
      .def_static("GetNewDoubleRawValue", &G4UIcmdWithADoubleAndUnit::GetNewDoubleRawValue)
      .def_static("GetNewUnitValue", &G4UIcmdWithADoubleAndUnit::GetNewUnitValue)
      .def("ConvertToStringWithBestUnit", &G4UIcmdWithADoubleAndUnit::ConvertToStringWithBestUnit)
      .def("ConvertToStringWithDefaultUnit", &G4UIcmdWithADoubleAndUnit::ConvertToStringWithDefaultUnit)
      .def("SetParameterName", &G4UIcmdWithADoubleAndUnit::SetParameterName, py::arg("theName"), py::arg("omittable"),
           py::arg("currentAsDefault") = false)

      .def("SetDefaultValue", &G4UIcmdWithADoubleAndUnit::SetDefaultValue)
      .def("SetUnitCategory", &G4UIcmdWithADoubleAndUnit::SetUnitCategory)
      .def("SetUnitCandidates", &G4UIcmdWithADoubleAndUnit::SetUnitCandidates)
      .def("SetDefaultUnit", &G4UIcmdWithADoubleAndUnit::SetDefaultUnit);
}
