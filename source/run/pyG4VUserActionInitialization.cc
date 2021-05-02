#include <pybind11/pybind11.h>

#include <G4VUserActionInitialization.hh>

#include <G4RunManager.hh>
#include <G4UserRunAction.hh>
#include <G4UserTrackingAction.hh>
#include <G4UserSteppingAction.hh>
#include <G4UserEventAction.hh>
#include <G4UserStackingAction.hh>
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4VSteppingVerbose.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4VUserActionInitialization) : public G4VUserActionInitialization {
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
         o.inc_ref();

         G4VSteppingVerbose *ptr;
         if (py::detail::cast_is_temporary_value_reference<G4VSteppingVerbose *>::value) {
            static py::detail::override_caster_t<G4VSteppingVerbose *> caster;
            ptr = py::detail::cast_ref<G4VSteppingVerbose *>(std::move(o), caster);
         } else {
            ptr = py::detail::cast_safe<G4VSteppingVerbose *>(std::move(o));
         }

         owntrans_ptr<G4VSteppingVerbose>::remove(ptr);
         return ptr;
      }

      return G4VUserActionInitialization::InitializeSteppingVerbose();
   };

   TRAMPOLINE_DESTRUCTOR(G4VUserActionInitialization);
};

void export_G4VUserActionInitialization(py::module &m)
{
   py::class_<G4VUserActionInitialization, TRAMPOLINE_NAME(G4VUserActionInitialization),
              owntrans_ptr<G4VUserActionInitialization>>(m, "G4VUserActionInitialization")

      .def(py::init<>())
      .def("Build", &G4VUserActionInitialization::Build)
      .def("BuildForMaster", &G4VUserActionInitialization::BuildForMaster)

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, G4VUserPrimaryGeneratorAction *action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4VUserPrimaryGeneratorAction, action);
              owntrans_ptr<G4VUserPrimaryGeneratorAction>::remove(action);
           })

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, G4UserRunAction *action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4UserRunAction, action);
              owntrans_ptr<G4UserRunAction>::remove(action);
           })

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, G4UserEventAction *action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4UserEventAction, action);
              owntrans_ptr<G4UserEventAction>::remove(action);
           })

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, G4UserStackingAction *action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4UserStackingAction, action);
              owntrans_ptr<G4UserStackingAction>::remove(action);
           })

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, G4UserTrackingAction *action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4UserTrackingAction, action);
              owntrans_ptr<G4UserTrackingAction>::remove(action);
           })

      .def("SetUserAction",
           [](G4VUserActionInitialization &self, G4UserSteppingAction *action) {
              G4RunManager::GetRunManager()->SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4UserSteppingAction, action);
              owntrans_ptr<G4UserSteppingAction>::remove(action);
           })

      .def("InitializeSteppingVerbose", &G4VUserActionInitialization::InitializeSteppingVerbose);
}