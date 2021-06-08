#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4UImessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UImessenger : public G4UImessenger {

public:
   using G4UImessenger::G4UImessenger;

   G4String GetCurrentValue(G4UIcommand *command) override
   {
      PYBIND11_OVERRIDE(G4String, G4UImessenger, GetCurrentValue, command);
   }

   void SetNewValue(G4UIcommand *command, G4String newValue) override
   {
      PYBIND11_OVERRIDE(void, G4UImessenger, SetNewValue, command, newValue);
   }
};

void export_G4UImessenger(py::module &m)
{
   py::class_<G4UImessenger, PyG4UImessenger>(m, "G4UImessenger")
      .def(py::init<>())
      .def(py::init<const G4String &, const G4String &, G4bool>(), py::arg("path"), py::arg("dsc"),
           py::arg("commandsToBeBroadcasted") = true)

      .def("GetCurrentValue", &G4UImessenger::GetCurrentValue)
      .def("SetNewValue", &G4UImessenger::SetNewValue)
      .def("CommandsShouldBeInMaster", &G4UImessenger::CommandsShouldBeInMaster)
      .def(py::self == py::self)
      .def(py::self != py::self);
}
