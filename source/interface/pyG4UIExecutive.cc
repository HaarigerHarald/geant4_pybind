#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIExecutive.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIExecutive(py::module &m)
{
   py::class_<G4UIExecutive>(m, "G4UIExecutive")
      .def(py::init<>([](G4int argc, const std::vector<std::string> &argv, const G4String &type) {
              static std::vector<std::string>  arvCopy = std::vector<std::string>(argv);
              static std::unique_ptr<char *[]> pArgv   = std::make_unique<char *[]>(argc);
              for (G4int i = 0; i < argc; i++) {
                 pArgv.get()[i] = &arvCopy[i][0];
              }

              return new G4UIExecutive(argc, pArgv.get(), type);
           }),
           py::arg("argc"), py::arg("argv"), py::arg("type") = "")

      //.def("GetSession", &G4UIExecutive::GetSession, py::return_value_policy::reference_internal)
      .def("SetPrompt", &G4UIExecutive::SetPrompt)
      .def("SetLsColor", &G4UIExecutive::SetLsColor)
      .def("SessionStart", &G4UIExecutive::SessionStart)
      .def("IsGUI", &G4UIExecutive::IsGUI);
}
