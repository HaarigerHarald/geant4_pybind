#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4VHitsCollection.hh>
#include <G4VHit.hh>
#include <G4AttDef.hh>
#include <G4AttValue.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PublicG4VHitsCollection : public G4VHitsCollection {
public:
   using G4VHitsCollection::colID;
   using G4VHitsCollection::collectionName;
   using G4VHitsCollection::SDname;
};

class PyG4VHitsCollection : public G4VHitsCollection, public py::trampoline_self_life_support {
public:
   using G4VHitsCollection::G4VHitsCollection;

   void DrawAllHits() override { PYBIND11_OVERRIDE(void, G4VHitsCollection, DrawAllHits, ); }

   void PrintAllHits() override { PYBIND11_OVERRIDE(void, G4VHitsCollection, PrintAllHits, ); }

   G4VHit *GetHit(size_t n) const override { PYBIND11_OVERRIDE(G4VHit *, G4VHitsCollection, GetHit, n); }

   size_t GetSize() const override { PYBIND11_OVERRIDE(size_t, G4VHitsCollection, GetSize, ); }
};

void export_G4VHitsCollection(py::module &m)
{
   py::class_<G4VHitsCollection, PyG4VHitsCollection>(m, "G4VHitsCollection")

      .def(py::init<>())
      .def(py::init<G4String, G4String>())
      .def(py::self == py::self)

      .def("DrawAllHits", &G4VHitsCollection::DrawAllHits)
      .def("PrintAllHits", &G4VHitsCollection::PrintAllHits)
      .def("DrawAllHits", &G4VHitsCollection::DrawAllHits)

      .def_readwrite("collectionName", &PublicG4VHitsCollection::collectionName)
      .def_readwrite("SDname", &PublicG4VHitsCollection::SDname)
      .def_readwrite("colID", &PublicG4VHitsCollection::colID)

      .def("GetName", &G4VHitsCollection::GetName)
      .def("GetSDname", &G4VHitsCollection::GetSDname)
      .def("SetColID", &G4VHitsCollection::SetColID)
      .def("GetColID", &G4VHitsCollection::GetColID)
      .def("GetHit", &G4VHitsCollection::GetHit, py::return_value_policy::reference_internal)
      .def("GetSize", &G4VHitsCollection::GetSize);
}
