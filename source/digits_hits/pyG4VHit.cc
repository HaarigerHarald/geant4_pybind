#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <G4VHit.hh>
#include <G4AttDef.hh>
#include <G4AttValue.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class PyG4VHit : public G4VHit {
public:
   using G4VHit::G4VHit;

   void Draw() override { PYBIND11_OVERRIDE(void, G4VHit, Draw, ); }
   void Print() override { PYBIND11_OVERRIDE(void, G4VHit, Print, ); }

   const std::map<G4String, G4AttDef> *GetAttDefs() const override
   {
      PYBIND11_OVERRIDE(PYBIND11_TYPE(const std::map<G4String, G4AttDef> *), G4VHit, GetAttDefs, );
   }

   std::vector<G4AttValue> *CreateAttValues() const override
   {
      PYBIND11_OVERRIDE(std::vector<G4AttValue> *, G4VHit, CreateAttValues, );
   }
};

void export_G4VHit(py::module &m)
{
   py::class_<G4VHit, owntrans_ptr<G4VHit>>(m, "G4VHit")
      .def(py::init<>())
      .def(py::self == py::self)
      .def("Draw", &G4VHit::Draw)
      .def("Print", &G4VHit::Print)
      .def("GetAttDefs", &G4VHit::GetAttDefs)
      .def("CreateAttValues", &G4VHit::CreateAttValues);
}
