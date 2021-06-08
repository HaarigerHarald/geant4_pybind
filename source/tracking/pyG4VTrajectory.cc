#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VTrajectory.hh>
#include <G4AttDef.hh>
#include <G4AttValue.hh>
#include <G4Step.hh>
#include <G4VTrajectoryPoint.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VTrajectory : public G4VTrajectory, public py::trampoline_self_life_support {
public:
   using G4VTrajectory::G4VTrajectory;

   G4int    GetTrackID() const override { PYBIND11_OVERRIDE_PURE(G4int, G4VTrajectory, GetTrackID, ); }
   G4int    GetParentID() const override { PYBIND11_OVERRIDE_PURE(G4int, G4VTrajectory, GetParentID, ); }
   G4String GetParticleName() const override { PYBIND11_OVERRIDE_PURE(G4String, G4VTrajectory, GetParticleName, ); }
   G4double GetCharge() const override { PYBIND11_OVERRIDE_PURE(G4double, G4VTrajectory, GetCharge, ); }

   G4int GetPDGEncoding() const override { PYBIND11_OVERRIDE_PURE(G4int, G4VTrajectory, GetPDGEncoding, ); }

   G4ThreeVector GetInitialMomentum() const override
   {
      PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4VTrajectory, GetInitialMomentum, );
   }

   G4int GetPointEntries() const override { PYBIND11_OVERRIDE_PURE(G4int, G4VTrajectory, GetPointEntries, ); }

   G4VTrajectoryPoint *GetPoint(G4int i) const override
   {
      PYBIND11_OVERRIDE_PURE(G4VTrajectoryPoint *, G4VTrajectory, GetPoint, i);
   }

   void ShowTrajectory(std::ostream &os = G4cout) const override
   {
      // TODO
      PYBIND11_OVERRIDE(void, G4VTrajectory, ShowTrajectory, );
   }

   void DrawTrajectory() const override { PYBIND11_OVERRIDE(void, G4VTrajectory, DrawTrajectory, ); }

   const std::map<G4String, G4AttDef> *GetAttDefs() const override
   {
      py::gil_scoped_acquire gil;
      py::function           override = py::get_override(static_cast<const G4VTrajectory *>(this), "GetAttDefs");
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

      return G4VTrajectory::GetAttDefs();
   }

   std::vector<G4AttValue> *CreateAttValues() const override
   {
      py::gil_scoped_acquire gil;
      py::function           override = py::get_override(static_cast<const G4VTrajectory *>(this), "CreateAttValues");
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

      return G4VTrajectory::CreateAttValues();
   }

   void AppendStep(const G4Step *aStep) override { PYBIND11_OVERRIDE_PURE(void, G4VTrajectory, AppendStep, aStep); }

   void MergeTrajectory(G4VTrajectory *secondTrajectory) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VTrajectory, MergeTrajectory, secondTrajectory);
   }
};

void export_G4VTrajectory(py::module &m)
{
   py::class_<G4VTrajectory, PyG4VTrajectory>(m, "G4VTrajectory")
      .def(py::init<>())

      .def("GetTrackID", &G4VTrajectory::GetTrackID)
      .def("GetParentID", &G4VTrajectory::GetParentID)
      .def("GetParticleName", &G4VTrajectory::GetParticleName)
      .def("GetCharge", &G4VTrajectory::GetCharge)
      .def("GetPDGEncoding", &G4VTrajectory::GetPDGEncoding)
      .def("GetInitialMomentum", &G4VTrajectory::GetInitialMomentum)
      .def("GetPointEntries", &G4VTrajectory::GetPointEntries)
      .def("GetPoint", &G4VTrajectory::GetPoint)
      .def("ShowTrajectory", &G4VTrajectory::ShowTrajectory)
      .def("DrawTrajectory", &G4VTrajectory::DrawTrajectory)
      .def("GetAttDefs", &G4VTrajectory::GetAttDefs)
      .def("CreateAttValues", &G4VTrajectory::CreateAttValues)
      .def("AppendStep", &G4VTrajectory::AppendStep)
      .def("MergeTrajectory", &G4VTrajectory::MergeTrajectory);
}
