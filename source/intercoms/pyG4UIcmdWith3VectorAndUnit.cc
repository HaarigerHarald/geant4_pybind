#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UIcmdWith3VectorAndUnit : public G4UIcmdWith3VectorAndUnit {
public:
   using G4UIcmdWith3VectorAndUnit::G4UIcmdWith3VectorAndUnit;

   G4int DoIt(G4String parameterList) override
   {
      PYBIND11_OVERRIDE(G4int, G4UIcmdWith3VectorAndUnit, DoIt, parameterList);
   }
};

void export_G4UIcmdWith3VectorAndUnit(py::module &m)
{
   py::class_<G4UIcmdWith3VectorAndUnit, PyG4UIcmdWith3VectorAndUnit, G4UIcommand>(m, "G4UIcmdWith3VectorAndUnit")

      .def(py::init<const char *, G4UImessenger *>(), py::arg("theCommandPath"), py::arg("theMessenger"))
      .def("DoIt", &G4UIcmdWith3VectorAndUnit::DoIt)

      .def_static("GetNew3VectorValue", &G4UIcmdWith3VectorAndUnit::GetNew3VectorValue)
      .def_static("GetNew3VectorRawValue", &G4UIcmdWith3VectorAndUnit::GetNew3VectorRawValue)
      .def_static("GetNewUnitValue", &G4UIcmdWith3VectorAndUnit::GetNewUnitValue)
      .def("ConvertToStringWithBestUnit", &G4UIcmdWith3VectorAndUnit::ConvertToStringWithBestUnit)
      .def("ConvertToStringWithDefaultUnit", &G4UIcmdWith3VectorAndUnit::ConvertToStringWithDefaultUnit)
      .def("G4UIcmdWith3VectorAndUnit", &G4UIcmdWith3VectorAndUnit::SetParameterName, py::arg("theNameX"),
           py::arg("theNameY"), py::arg("theNameZ"), py::arg("omittable"), py::arg("currentAsDefault") = false)

      .def("SetDefaultValue", &G4UIcmdWith3VectorAndUnit::SetDefaultValue)
      .def("SetUnitCategory", &G4UIcmdWith3VectorAndUnit::SetUnitCategory)
      .def("SetUnitCandidates", &G4UIcmdWith3VectorAndUnit::SetUnitCandidates)
      .def("SetDefaultUnit", &G4UIcmdWith3VectorAndUnit::SetDefaultUnit);
}
