#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4UIcommand.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UIcommand : public G4UIcommand {
public:
   using G4UIcommand::G4UIcommand;

   G4int DoIt(G4String parameterList) override { PYBIND11_OVERRIDE(G4int, G4UIcommand, DoIt, parameterList); }

   void List() override { PYBIND11_OVERRIDE(void, G4UIcommand, List, ); }
};

void export_G4UIcommand(py::module &m)
{
   py::class_<G4UIcommand>(m, "G4UIcommand", "UI command")
      .def(py::init<const char *, G4UImessenger *>())

      .def("GetTitle", &G4UIcommand::GetTitle)

      .def(py::self == py::self)
      .def(py::self != py::self)

      .def("DoIt", &G4UIcommand::DoIt)
      .def("GetCurrentValue", &G4UIcommand::GetCurrentValue)
      .def("AvailableForStates", py::overload_cast<G4ApplicationState>(&G4UIcommand::AvailableForStates))
      .def("AvailableForStates",
           py::overload_cast<G4ApplicationState, G4ApplicationState>(&G4UIcommand::AvailableForStates))

      .def("AvailableForStates", py::overload_cast<G4ApplicationState, G4ApplicationState, G4ApplicationState>(
                                    &G4UIcommand::AvailableForStates))

      .def("AvailableForStates",
           py::overload_cast<G4ApplicationState, G4ApplicationState, G4ApplicationState, G4ApplicationState>(
              &G4UIcommand::AvailableForStates))

      .def("AvailableForStates",
           py::overload_cast<G4ApplicationState, G4ApplicationState, G4ApplicationState, G4ApplicationState,
                             G4ApplicationState>(&G4UIcommand::AvailableForStates))

      .def("IsAvailable", &G4UIcommand::IsAvailable)
      .def("List", &G4UIcommand::List)

      .def_static("ConvertToString", py::overload_cast<G4bool>(&G4UIcommand::ConvertToString))
      .def_static("ConvertToString", py::overload_cast<G4int>(&G4UIcommand::ConvertToString))
      .def_static("ConvertToString", py::overload_cast<G4long>(&G4UIcommand::ConvertToString))
      .def_static("ConvertToString", py::overload_cast<G4double>(&G4UIcommand::ConvertToString))
      .def_static("ConvertToString", py::overload_cast<G4double, const char *>(&G4UIcommand::ConvertToString))
      .def_static("ConvertToString", py::overload_cast<G4ThreeVector>(&G4UIcommand::ConvertToString))
      .def_static("ConvertToString", py::overload_cast<G4ThreeVector, const char *>(&G4UIcommand::ConvertToString))

      .def_static("ConvertToBool", &G4UIcommand::ConvertToBool)
      .def_static("ConvertToInt", &G4UIcommand::ConvertToInt)
      .def_static("ConvertToLongInt", &G4UIcommand::ConvertToLongInt)
      .def_static("ConvertToDouble", &G4UIcommand::ConvertToDouble)
      .def_static("ConvertToDimensionedDouble", &G4UIcommand::ConvertToDimensionedDouble)
      .def_static("ConvertTo3Vector", &G4UIcommand::ConvertTo3Vector)
      .def_static("ConvertToDimensioned3Vector", &G4UIcommand::ConvertToDimensioned3Vector)

      .def_static("ValueOf", &G4UIcommand::ValueOf)
      .def_static("CategoryOf", &G4UIcommand::CategoryOf)
      .def_static("UnitsList", &G4UIcommand::UnitsList)

      .def("SetRange", &G4UIcommand::SetRange)

      .def("GetRange", &G4UIcommand::GetRange)
      .def("GetGuidanceEntries", &G4UIcommand::GetGuidanceEntries)
      .def("GetGuidanceLine", &G4UIcommand::GetGuidanceLine)
      .def("GetCommandPath", &G4UIcommand::GetCommandPath)
      .def("GetCommandName", &G4UIcommand::GetCommandName)
      .def("GetParameterEntries", &G4UIcommand::GetParameterEntries)
      .def("GetParameter", &G4UIcommand::GetParameter, py::return_value_policy::reference_internal)
      .def("GetStateList", &G4UIcommand::GetStateList)
      .def("GetMessenger", &G4UIcommand::GetMessenger, py::return_value_policy::reference)
      .def("SetParameter",
           [](G4UIcommand &self, py::disown_ptr<G4UIparameter> newParameter) { self.SetParameter(newParameter); })

      .def("SetGuidance", &G4UIcommand::SetGuidance)
      .def("GetTitle", &G4UIcommand::GetTitle)
      .def("SetToBeBroadcasted", &G4UIcommand::SetToBeBroadcasted)
      .def("SetToBeFlushed", &G4UIcommand::SetToBeFlushed)
      .def("ToBeFlushed", &G4UIcommand::ToBeFlushed)
      .def("SetWorkerThreadOnly", &G4UIcommand::SetWorkerThreadOnly)
      .def("IsWorkerThreadOnly", &G4UIcommand::IsWorkerThreadOnly)

      //.def("CommandFailed", py::overload_cast<G4int, G4ExceptionDescription&>(&G4UIcommand::CommandFailed))
      //.def("CommandFailed", py::overload_cast<G4ExceptionDescription&>(&G4UIcommand::CommandFailed))
      .def("IfCommandFailed", &G4UIcommand::IfCommandFailed)
      .def("GetFailureDescription", &G4UIcommand::GetFailureDescription)
      .def("ResetFailure", &G4UIcommand::ResetFailure);
}
