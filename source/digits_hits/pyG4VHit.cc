#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4VHit.hh>
#include <G4AttDef.hh>
#include <G4AttValue.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VHit : public G4VHit, public py::trampoline_self_life_support {
public:
   using G4VHit::G4VHit;

   void Draw() override { PYBIND11_OVERRIDE(void, G4VHit, Draw, ); }
   void Print() override { PYBIND11_OVERRIDE(void, G4VHit, Print, ); }

   const std::map<G4String, G4AttDef> *GetAttDefs() const override
   {
      py::gil_scoped_acquire gil;
      py::function           override = py::get_override(static_cast<const G4VHit *>(this), "GetAttDefs");
      if (override) {
         py::dict                      pyAttDefs = override();
         std::map<G4String, G4AttDef> *attDefs   = new std::map<G4String, G4AttDef>();

         for (auto pair : pyAttDefs) {
            attDefs->insert({pair.first.cast<G4String>(), pair.second.cast<G4AttDef>()});
         }

         return attDefs;
      }
      return G4VHit::GetAttDefs();
   }

   std::vector<G4AttValue> *CreateAttValues() const override
   {
      py::gil_scoped_acquire gil;
      py::function           override = py::get_override(static_cast<const G4VHit *>(this), "CreateAttValues");
      if (override) {
         py::list                 pyAttValues = override();
         std::vector<G4AttValue> *attValues   = new std::vector<G4AttValue>(pyAttValues.size());

         for (size_t i = 0; i < pyAttValues.size(); i++) {
            (*attValues)[i] = pyAttValues[i].cast<G4AttValue>();
         }

         return attValues;
      }
      return G4VHit::CreateAttValues();
   }
};

void export_G4VHit(py::module &m)
{
   py::class_<G4VHit, PyG4VHit>(m, "G4VHit")
      .def(py::init<>())
      .def(py::self == py::self)
      .def("Draw", &G4VHit::Draw)
      .def("Print", &G4VHit::Print)
      .def("GetAttDefs", &G4VHit::GetAttDefs)
      .def("CreateAttValues", &G4VHit::CreateAttValues);
}
