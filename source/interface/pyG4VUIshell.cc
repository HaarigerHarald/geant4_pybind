#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VUIshell.hh>
#include <G4UIcommandTree.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PublicG4VUIshell : public G4VUIshell {
public:
   using G4VUIshell::commandColor;
   using G4VUIshell::currentCommandDir;
   using G4VUIshell::directoryColor;
   using G4VUIshell::G4VUIshell;
   using G4VUIshell::GetAbsCommandDirPath;
   using G4VUIshell::GetCommandPathTail;
   using G4VUIshell::GetCommandTree;
   using G4VUIshell::lsColorFlag;
   using G4VUIshell::MakePrompt;
   using G4VUIshell::nColumn;
   using G4VUIshell::promptSetting;
   using G4VUIshell::promptString;
};

class PyG4VUIshell : public G4VUIshell {
public:
   using G4VUIshell::G4VUIshell;

   void MakePrompt(const char *msg = 0) override { PYBIND11_OVERRIDE(void, G4VUIshell, MakePrompt, msg); }

   void SetLsColor(TermColorIndex idx1, TermColorIndex idx2) override
   {
      PYBIND11_OVERRIDE(void, G4VUIshell, SetLsColor, idx1, idx2);
   }

   void ShowCurrentDirectory() const override { PYBIND11_OVERRIDE(void, G4VUIshell, ShowCurrentDirectory, ); }

   void ListCommand(const G4String &input, const G4String &candidate = "") const override
   {
      PYBIND11_OVERRIDE(void, G4VUIshell, ListCommand, input, candidate);
   }

   G4String GetCommandLineString(const char *msg = 0) override
   {
      PYBIND11_OVERRIDE_PURE(G4String, G4VUIshell, GetCommandLineString, msg);
   }

   void ResetTerminal() override { PYBIND11_OVERRIDE(void, G4VUIshell, ResetTerminal, ); }
};

void export_G4VUIshell(py::module &m)
{
   py::enum_<TermColorIndex>(m, "TermColorIndex")
      .value("BLACK", BLACK)
      .value("RED", RED)
      .value("GREEN", GREEN)
      .value("YELLOW", YELLOW)
      .value("BLUE", BLUE)
      .value("PURPLE", PURPLE)
      .value("CYAN", CYAN)
      .value("WHITE", WHITE)
      .export_values();

   py::class_<G4VUIshell, PyG4VUIshell>(m, "G4VUIshell")
      .def(py::init<G4String>())
      .def(py::init<>())

      .def("SetNColumn", &G4VUIshell::SetNColumn)
      .def("SetPrompt", &G4VUIshell::SetPrompt)
      .def("SetCurrentDirectory", &G4VUIshell::SetCurrentDirectory)
      .def("SetLsColor", &G4VUIshell::SetLsColor)
      .def("ShowCurrentDirectory", &G4VUIshell::ShowCurrentDirectory)
      .def("ListCommand", &G4VUIshell::ListCommand, py::arg("input"), py::arg("candidate") = "")
      .def("GetCommandLineString", &G4VUIshell::GetCommandLineString)
      .def("ResetTerminal", &G4VUIshell::ResetTerminal)

      .def_readwrite("promptSetting", &PublicG4VUIshell::promptSetting)
      .def_readwrite("promptString", &PublicG4VUIshell::promptString)

      .def("MakePrompt", &PublicG4VUIshell::MakePrompt, py::arg("msg") = static_cast<const char *>(nullptr))

      .def_readwrite("nColumn", &PublicG4VUIshell::nColumn)
      .def_readwrite("lsColorFlag", &PublicG4VUIshell::lsColorFlag)
      .def_readwrite("commandColor", &PublicG4VUIshell::commandColor)
      .def_readwrite("currentCommandDir", &PublicG4VUIshell::currentCommandDir)
      .def_readwrite("commandColor", &PublicG4VUIshell::commandColor)

      .def("GetCommandTree", &PublicG4VUIshell::GetCommandTree)
      .def("GetAbsCommandDirPath", &PublicG4VUIshell::GetAbsCommandDirPath)
      .def("GetCommandPathTail", &PublicG4VUIshell::GetCommandPathTail);
}