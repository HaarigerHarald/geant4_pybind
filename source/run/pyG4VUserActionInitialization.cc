#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VUserActionInitialization.hh>

#include <G4RunManager.hh>
#include <G4UserRunAction.hh>
#include <G4UserTrackingAction.hh>
#include <G4UserSteppingAction.hh>
#include <G4UserEventAction.hh>
#include <G4UserStackingAction.hh>
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4VSteppingVerbose.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VUserActionInitialization : public G4VUserActionInitialization, public py::trampoline_self_life_support {
public:
   using G4VUserActionInitialization::G4VUserActionInitialization;
   using G4VUserActionInitialization::SetUserAction;

   void Build() const override { PYBIND11_OVERRIDE_PURE(void, G4VUserActionInitialization, Build, ); }

   void BuildForMaster() const override { PYBIND11_OVERRIDE(void, G4VUserActionInitialization, BuildForMaster, ); }

   G4VSteppingVerbose *InitializeSteppingVerbose() const override
   {
      py::gil_scoped_acquire gil;
      py::function           override =
         py::get_override(static_cast<const G4VUserActionInitialization *>(this), "InitializeSteppingVerbose");
      if (override) {
         py::object o = override();

         return py::detail::cast_safe<py::disown_ptr<G4VSteppingVerbose>>(std::move(o));
      }

      return G4VUserActionInitialization::InitializeSteppingVerbose();
   };
};

void export_G4VUserActionInitialization(py::module &m)
{
   py::class_<G4VUserActionInitialization, PyG4VUserActionInitialization>(m, "G4VUserActionInitialization")

      .def(py::init<>())
      .def("Build", &G4VUserActionInitialization::Build)
      .def("BuildForMaster", &G4VUserActionInitialization::BuildForMaster)

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, py::disown_ptr<G4VUserPrimaryGeneratorAction> action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
           })

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, py::disown_ptr<G4UserRunAction> action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
           })

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, py::disown_ptr<G4UserEventAction> action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
           })

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, py::disown_ptr<G4UserStackingAction> action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
           })

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, py::disown_ptr<G4UserTrackingAction> action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
           })

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, py::disown_ptr<G4UserSteppingAction> action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
           })

      .def("InitializeSteppingVerbose", &G4VUserActionInitialization::InitializeSteppingVerbose);
}