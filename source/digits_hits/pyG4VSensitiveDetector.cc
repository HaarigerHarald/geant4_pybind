#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4VSensitiveDetector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PublicG4VSensitiveDetector : public G4VSensitiveDetector {
public:
   using G4VSensitiveDetector::collectionName;
   using G4VSensitiveDetector::GetCollectionID;
   using G4VSensitiveDetector::ProcessHits;

   using G4VSensitiveDetector::active;
   using G4VSensitiveDetector::filter;
   using G4VSensitiveDetector::fullPathName;
   using G4VSensitiveDetector::ROgeometry;
   using G4VSensitiveDetector::SensitiveDetectorName;
   using G4VSensitiveDetector::thePathName;
   using G4VSensitiveDetector::verboseLevel;
};

// Trampolin class
class PyG4VSensitiveDetector : public G4VSensitiveDetector, public py::trampoline_self_life_support {
public:
   using G4VSensitiveDetector::G4VSensitiveDetector;

   void Initialize(G4HCofThisEvent *hCofThisEvent) override
   {
      PYBIND11_OVERRIDE(void, G4VSensitiveDetector, Initialize, hCofThisEvent);
   }

   void EndOfEvent(G4HCofThisEvent *hCofThisEvent) override
   {
      PYBIND11_OVERRIDE(void, G4VSensitiveDetector, EndOfEvent, hCofThisEvent);
   }

   void clear() override { PYBIND11_OVERRIDE(void, G4VSensitiveDetector, clear, ); }

   void DrawAll() override { PYBIND11_OVERRIDE(void, G4VSensitiveDetector, DrawAll, ); }

   void PrintAll() override { PYBIND11_OVERRIDE(void, G4VSensitiveDetector, PrintAll, ); }

   G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VSensitiveDetector, ProcessHits, aStep, ROhist);
   }

   G4int GetCollectionID(G4int i) override { PYBIND11_OVERRIDE(G4int, G4VSensitiveDetector, GetCollectionID, i); }

   G4VSensitiveDetector *Clone() const override
   {
      PYBIND11_OVERRIDE(G4VSensitiveDetector *, G4VSensitiveDetector, Clone, );
   }
};

void export_G4VSensitiveDetector(py::module &m)
{
   py::class_<G4CollectionNameVector>(m, "G4CollectionNameVector")
      .def(py::init<>())
      .def("insert", &G4CollectionNameVector::insert)
      .def(
         "__getitem__", [](G4CollectionNameVector &self, std::size_t n) { return self[n]; }, py::is_operator(),
         py::return_value_policy::reference_internal);

   py::implicitly_convertible<G4CollectionNameVector, std::vector<G4String>>();

   py::class_<G4VSensitiveDetector, PyG4VSensitiveDetector>(m, "G4VSensitiveDetector",
                                                            "base class of senstive detector")

      .def(py::init<G4String>())
      .def(py::init([](const PyG4VSensitiveDetector &o) { return new PyG4VSensitiveDetector(o); }))

      .def("Initialize", &G4VSensitiveDetector::Initialize)
      .def("EndOfEvent", &G4VSensitiveDetector::EndOfEvent)
      .def("clear", &G4VSensitiveDetector::clear)
      .def("DrawAll", &G4VSensitiveDetector::DrawAll)
      .def("PrintAll", &G4VSensitiveDetector::PrintAll)
      .def("Hit", &G4VSensitiveDetector::Hit)
      .def("ProcessHits", &PublicG4VSensitiveDetector::ProcessHits)
      .def("SetROgeometry", &G4VSensitiveDetector::SetROgeometry)
      .def("GetNumberOfCollections", &G4VSensitiveDetector::GetNumberOfCollections)
      .def("GetCollectionName", &G4VSensitiveDetector::GetCollectionName)
      .def("SetVerboseLevel", &G4VSensitiveDetector::SetVerboseLevel)
      .def("Activate", &G4VSensitiveDetector::Activate)
      .def("isActive", &G4VSensitiveDetector::isActive)
      .def("GetName", &G4VSensitiveDetector::GetName)
      .def("GetPathName", &G4VSensitiveDetector::GetPathName)
      .def("GetFullPathName", &G4VSensitiveDetector::GetFullPathName)
      .def("GetROgeometry", &G4VSensitiveDetector::GetROgeometry, py::return_value_policy::reference_internal)

      .def("GetCollectionID", &PublicG4VSensitiveDetector::GetCollectionID)
      .def_readwrite("collectionName", &PublicG4VSensitiveDetector::collectionName)
      .def_readwrite("active", &PublicG4VSensitiveDetector::active)
      .def_readwrite("filter", &PublicG4VSensitiveDetector::filter)
      .def_readwrite("fullPathName", &PublicG4VSensitiveDetector::fullPathName)
      .def_readwrite("ROgeometry", &PublicG4VSensitiveDetector::ROgeometry)
      .def_readwrite("SensitiveDetectorName", &PublicG4VSensitiveDetector::SensitiveDetectorName)
      .def_readwrite("thePathName", &PublicG4VSensitiveDetector::thePathName)
      .def_readwrite("verboseLevel", &PublicG4VSensitiveDetector::verboseLevel)
      .def("Clone", &G4VSensitiveDetector::Clone);
}
