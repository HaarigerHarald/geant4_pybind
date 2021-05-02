#include <pybind11/pybind11.h>

#include <G4UIcmdWithoutParameter.hh>
#include <G4UImessenger.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4UIcmdWithoutParameter(py::module &m)
{
   py::class_<G4UIcmdWithoutParameter, G4UIcommand, std::unique_ptr<G4UIcmdWithoutParameter>>(m,
                                                                                              "G4UIcmdWithoutParameter")

      .def(py::init<const char *, G4UImessenger *>(), py::arg("theCommandPath"), py::arg("theMessenger"));
}
