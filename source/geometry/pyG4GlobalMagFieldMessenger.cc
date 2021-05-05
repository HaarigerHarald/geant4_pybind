#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GlobalMagFieldMessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4GlobalMagFieldMessenger : public G4GlobalMagFieldMessenger {
public:
   using G4GlobalMagFieldMessenger::G4GlobalMagFieldMessenger;

   void SetNewValue(G4UIcommand *command, G4String newValue) override
   {
      PYBIND11_OVERRIDE(void, G4GlobalMagFieldMessenger, SetNewValue, command, newValue);
   }
};

void export_G4GlobalMagFieldMessenger(py::module &m)
{
   py::class_<G4GlobalMagFieldMessenger, PyG4GlobalMagFieldMessenger, G4UImessenger,
              std::unique_ptr<G4GlobalMagFieldMessenger>>(m, "G4GlobalMagFieldMessenger")

      .def(py::init<const G4ThreeVector &>(), py::arg("value") = G4ThreeVector())
      .def("SetNewValue", &G4GlobalMagFieldMessenger::SetNewValue)
      .def("SetFieldValue", &G4GlobalMagFieldMessenger::SetFieldValue)
      .def("GetFieldValue", &G4GlobalMagFieldMessenger::GetFieldValue)
      .def("SetVerboseLevel", &G4GlobalMagFieldMessenger::SetVerboseLevel)
      .def("GetVerboseLevel", &G4GlobalMagFieldMessenger::GetVerboseLevel);
}
