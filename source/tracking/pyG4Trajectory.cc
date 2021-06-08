#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4Trajectory.hh>

#include <G4AttDef.hh>
#include <G4AttValue.hh>
#include <G4Step.hh>
#include <G4VTrajectoryPoint.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Trajectory : public G4Trajectory, public py::trampoline_self_life_support {
public:
   using G4Trajectory::G4Trajectory;

   void ShowTrajectory(std::ostream &os = G4cout) const override
   {
      // TODO
      PYBIND11_OVERRIDE(void, G4Trajectory, ShowTrajectory, );
   }

   void DrawTrajectory() const override { PYBIND11_OVERRIDE(void, G4Trajectory, DrawTrajectory, ); }

   void AppendStep(const G4Step *aStep) override { PYBIND11_OVERRIDE(void, G4Trajectory, AppendStep, aStep); }

   G4int GetPointEntries() const override { PYBIND11_OVERRIDE(G4int, G4Trajectory, GetPointEntries, ); }

   G4VTrajectoryPoint *GetPoint(G4int i) const override
   {
      PYBIND11_OVERRIDE(G4VTrajectoryPoint *, G4Trajectory, GetPoint, i);
   }

   void MergeTrajectory(G4VTrajectory *secondTrajectory) override
   {
      PYBIND11_OVERRIDE(void, G4Trajectory, MergeTrajectory, secondTrajectory);
   }

   const std::map<G4String, G4AttDef> *GetAttDefs() const override
   {
      py::gil_scoped_acquire gil;
      py::function           override = py::get_override(static_cast<const G4Trajectory *>(this), "GetAttDefs");
      if (override) {
         auto o = override();
         if (py::isinstance<py::dict>(o)) {
            std::map<G4String, G4AttDef> *attDefs    = new std::map<G4String, G4AttDef>();
            py::dict                      pyAttDeffs = o.cast<py::dict>();
            for (auto entry : pyAttDeffs) {
               attDefs->insert({entry.first.cast<G4String>(), entry.first.cast<G4AttDef>()});
            }

            return attDefs;
         } else {

            py::print("Invalid return type \"G4VTrajectory::GetAttDefs\"",
                      py::arg("file") = py::module_::import("sys").attr("stderr"));
            return nullptr;
         }
      }

      return G4Trajectory::GetAttDefs();
   }

   std::vector<G4AttValue> *CreateAttValues() const override
   {
      py::gil_scoped_acquire gil;
      py::function           override = py::get_override(static_cast<const G4Trajectory *>(this), "CreateAttValues");
      if (override) {
         auto o = override();
         if (py::isinstance<py::list>(o)) {
            std::vector<G4AttValue> *attValues   = new std::vector<G4AttValue>();
            py::list                 pyAttValues = o.cast<py::list>();
            for (auto entry : pyAttValues) {
               attValues->push_back(entry.cast<G4AttValue>());
            }

            return attValues;
         } else {

            py::print("Invalid return type \"G4VTrajectory::CreateAttValues\"",
                      py::arg("file") = py::module_::import("sys").attr("stderr"));
            return nullptr;
         }
      }

      return G4Trajectory::CreateAttValues();
   }
};

void export_G4Trajectory(py::module &m)
{
   py::class_<G4Trajectory, PyG4Trajectory, G4VTrajectory>(m, "G4Trajectory")
      .def(py::init<>())
      .def(py::init<const G4Track *>())
      .def(py::init<>([](G4Trajectory &other) { return new G4Trajectory(other); }))

      .def(py::self == py::self)

      .def("GetTrackID", &G4Trajectory::GetTrackID)
      .def("GetParentID", &G4Trajectory::GetParentID)
      .def("GetParticleName", &G4Trajectory::GetParticleName)
      .def("GetCharge", &G4Trajectory::GetCharge)
      .def("GetPDGEncoding", &G4Trajectory::GetPDGEncoding)

      .def("GetInitialKineticEnergy", &G4Trajectory::GetInitialKineticEnergy)
      .def("GetInitialMomentum", &G4Trajectory::GetInitialMomentum)
      .def("ShowTrajectory", &G4Trajectory::ShowTrajectory)
      .def("DrawTrajectory", &G4Trajectory::DrawTrajectory)
      .def("AppendStep", &G4Trajectory::AppendStep)
      .def("GetPointEntries", &G4Trajectory::GetPointEntries)
      .def("GetPoint", &G4Trajectory::GetPoint, py::return_value_policy::reference_internal)
      .def("MergeTrajectory",
           [](G4Trajectory &self, py::disown_ptr<G4VTrajectory> second) { self.MergeTrajectory(second); })

      .def("GetParticleDefinition", &G4Trajectory::GetParticleDefinition, py::return_value_policy::reference)
      .def("GetAttDefs", &G4Trajectory::GetAttDefs, py::return_value_policy::reference)
      .def("CreateAttValues", &G4Trajectory::CreateAttValues);
}
