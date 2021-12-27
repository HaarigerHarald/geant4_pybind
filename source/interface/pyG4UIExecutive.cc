#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIExecutive.hh>
#include <G4UIsession.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIExecutive(py::module &m)
{
   py::class_<G4UIExecutive> g4UIExecutive(m, "G4UIExecutive");

   g4UIExecutive
      .def(py::init<>([g4UIExecutive](G4int argc, std::vector<std::string> &argv, const G4String &type) {
              static std::vector<std::string>  arvCopy = std::vector<std::string>(std::move(argv));
              static std::unique_ptr<char *[]> pArgv   = std::make_unique<char *[]>(argc);
              for (G4int i = 0; i < argc; i++) {
                 pArgv.get()[i] = &arvCopy[i][0];
              }

              G4UIExecutive *ui = new G4UIExecutive(argc, pArgv.get(), type);

              if (ui->IsGUI()) {
                 G4UIsession *session = ui->GetSession();

                 class DummyStdoutRedirect {
                 };
                 py::class_<DummyStdoutRedirect> stdoutRedirect(g4UIExecutive, "StdoutRedirect");
                 stdoutRedirect.def(py::init<>())
                    .def("write",
                         [session](py::object self, const G4String &message) {
                            py::gil_scoped_release gil_release;
                            session->ReceiveG4cout(message);
                         })
                    .def("flush", [](py::object self) {});
                 py::module_::import("sys").attr("stdout") = stdoutRedirect();

                 class DummyStderrRedirect {
                 };
                 py::class_<DummyStderrRedirect> stderrRedirect(g4UIExecutive, "StderrRedirect");
                 stderrRedirect.def(py::init<>())
                    .def("write",
                         [session](py::object self, const G4String &message) {
                            py::gil_scoped_release gil_release;
                            session->ReceiveG4cerr(message);
                         })
                    .def("flush", [](py::object self) {});
                 py::module_::import("sys").attr("stderr") = stderrRedirect();
              }

              return ui;
           }),
           py::arg("argc"), py::arg("argv"), py::arg("type") = "")

      //.def("GetSession", &G4UIExecutive::GetSession, py::return_value_policy::reference_internal)
      .def("SetPrompt", &G4UIExecutive::SetPrompt)
      .def("SetLsColor", &G4UIExecutive::SetLsColor)
      .def("SessionStart", &G4UIExecutive::SessionStart, py::call_guard<py::gil_scoped_release>())
      .def("IsGUI", &G4UIExecutive::IsGUI)
      .def("__del__", [](py::object self) {
         // Reset stdout and stderr to python's default
         py::module_::import("sys").attr("stdout") = py::module_::import("sys").attr("__stdout__");
         py::module_::import("sys").attr("stderr") = py::module_::import("sys").attr("__stderr__");
      });
}
