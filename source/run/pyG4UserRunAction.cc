#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UserRunAction.hh>
#include <G4Run.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

// Trampolin class
class PyG4UserRunAction : public G4UserRunAction, public py::trampoline_self_life_support {

public:
   using G4UserRunAction::G4UserRunAction;

   void BeginOfRunAction(const G4Run *aRun) override
   {
      PYBIND11_OVERRIDE(void, G4UserRunAction, BeginOfRunAction, aRun);
   }

   void EndOfRunAction(const G4Run *aRun) override { PYBIND11_OVERRIDE(void, G4UserRunAction, EndOfRunAction, aRun); }

   G4Run *GenerateRun() override
   {
      py::gil_scoped_acquire gil;
      py::function           override = py::get_override(static_cast<const G4UserRunAction *>(this), "GenerateRun");
      if (override) {
         py::object o = override();
         return py::detail::cast_safe<py::disown_ptr<G4Run>>(std::move(o));
      }

      return G4UserRunAction::GenerateRun();
   }

   void SetMaster(G4bool val) override { PYBIND11_OVERRIDE(void, G4UserRunAction, SetMaster, val); }
};

void export_G4UserRunAction(py::module &m)
{
   py::class_<G4UserRunAction, PyG4UserRunAction>(m, "G4UserRunAction", "run action class")

      .def(py::init<>())
      .def("BeginOfRunAction", &G4UserRunAction::BeginOfRunAction)
      .def("EndOfRunAction", &G4UserRunAction::EndOfRunAction)
      .def("GenerateRun", &G4UserRunAction::GenerateRun, py::return_value_policy::reference)
      .def("SetMaster", &G4UserRunAction::SetMaster, py::arg("val") = true)
      .def("IsMaster", &G4UserRunAction::IsMaster);
}
