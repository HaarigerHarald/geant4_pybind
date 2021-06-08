#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TrajectoryPoint.hh>
#include <G4AttDef.hh>
#include <G4AttValue.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4TrajectoryPoint : public G4TrajectoryPoint {

public:
   const G4ThreeVector GetPosition() const override
   {
      PYBIND11_OVERRIDE(const G4ThreeVector, G4TrajectoryPoint, GetPosition, );
   }

   const std::map<G4String, G4AttDef> *GetAttDefs() const override
   {
      py::gil_scoped_acquire gil;
      py::function           override = py::get_override(static_cast<const G4TrajectoryPoint *>(this), "GetAttDefs");
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

            py::print("Invalid return type \"G4TrajectoryPoint::GetAttDefs\"",
                      py::arg("file") = py::module_::import("sys").attr("stderr"));
            return nullptr;
         }
      }

      return G4TrajectoryPoint::GetAttDefs();
   }

   std::vector<G4AttValue> *CreateAttValues() const override
   {
      py::gil_scoped_acquire gil;
      py::function override = py::get_override(static_cast<const G4TrajectoryPoint *>(this), "CreateAttValues");
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

            py::print("Invalid return type \"G4TrajectoryPoint::CreateAttValues\"",
                      py::arg("file") = py::module_::import("sys").attr("stderr"));
            return nullptr;
         }
      }

      return G4TrajectoryPoint::CreateAttValues();
   }
};

void export_G4TrajectoryPoint(py::module &m)
{
   py::class_<G4TrajectoryPoint, PyG4TrajectoryPoint>(m, "G4TrajectoryPoint")
      .def(py::init<>())

      .def("GetPosition", &G4TrajectoryPoint::GetPosition)
      .def("GetAttDefs", &G4TrajectoryPoint::GetAttDefs)
      .def("CreateAttValues", &G4TrajectoryPoint::CreateAttValues);
}