#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VTrajectoryPoint.hh>
#include <G4AttDef.hh>
#include <G4AttValue.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VTrajectoryPoint : public G4VTrajectoryPoint {

public:
   const G4ThreeVector GetPosition() const override
   {
      PYBIND11_OVERRIDE_PURE(const G4ThreeVector, G4VTrajectoryPoint, GetPosition, );
   }

   const std::vector<G4ThreeVector> *GetAuxiliaryPoints() const override
   {
      py::gil_scoped_acquire gil;
      py::function override = py::get_override(static_cast<const G4VTrajectoryPoint *>(this), "GetAuxiliaryPoints");
      if (override) {
         auto o = override();
         if (py::isinstance<py::list>(o)) {
            std::vector<G4ThreeVector> *auxPoints   = new std::vector<G4ThreeVector>();
            py::list                    pyAuxPoints = o.cast<py::list>();
            for (auto entry : pyAuxPoints) {
               auxPoints->push_back(entry.cast<G4ThreeVector>());
            }

            return auxPoints;
         } else {

            py::print("Invalid return type \"G4VTrajectoryPoint::GetAuxiliaryPoints\"",
                      py::arg("file") = py::module_::import("sys").attr("stderr"));
            return nullptr;
         }
      }

      return G4VTrajectoryPoint::GetAuxiliaryPoints();
   }

   const std::map<G4String, G4AttDef> *GetAttDefs() const override
   {
      py::gil_scoped_acquire gil;
      py::function           override = py::get_override(static_cast<const G4VTrajectoryPoint *>(this), "GetAttDefs");
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

            py::print("Invalid return type \"G4VTrajectoryPoint::GetAttDefs\"",
                      py::arg("file") = py::module_::import("sys").attr("stderr"));
            return nullptr;
         }
      }

      return G4VTrajectoryPoint::GetAttDefs();
   }

   std::vector<G4AttValue> *CreateAttValues() const override
   {
      py::gil_scoped_acquire gil;
      py::function override = py::get_override(static_cast<const G4VTrajectoryPoint *>(this), "CreateAttValues");
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

            py::print("Invalid return type \"G4VTrajectoryPoint::CreateAttValues\"",
                      py::arg("file") = py::module_::import("sys").attr("stderr"));
            return nullptr;
         }
      }

      return G4VTrajectoryPoint::CreateAttValues();
   }
};

void export_G4VTrajectoryPoint(py::module &m)
{
   py::class_<G4VTrajectoryPoint, PyG4VTrajectoryPoint>(m, "G4VTrajectoryPoint")
      .def(py::init<>())

      .def("GetPosition", &G4VTrajectoryPoint::GetPosition)
      .def("GetAuxiliaryPoints", &G4VTrajectoryPoint::GetAuxiliaryPoints)
      .def("GetAttDefs", &G4VTrajectoryPoint::GetAttDefs)
      .def("CreateAttValues", &G4VTrajectoryPoint::CreateAttValues);
}
