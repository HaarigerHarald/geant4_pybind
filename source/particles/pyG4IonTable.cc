#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4IonTable.hh>
#include <G4ParticleTable.hh>
#include <G4VIsotopeTable.hh>
#include <G4IsotopeProperty.hh>
#include <G4NuclideTable.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4IonTable(py::module &m)
{
   py::class_<G4IonTable>(m, "G4IonTable")
      .def(py::init<>())
      .def_static("GetIonTable", &G4IonTable::GetIonTable, py::return_value_policy::reference)

      .def("WorkerG4IonTable", &G4IonTable::WorkerG4IonTable)
      .def("DestroyWorkerG4IonTable", &G4IonTable::DestroyWorkerG4IonTable)
      .def("GetNumberOfElements", &G4IonTable::DestroyWorkerG4IonTable)
      .def("RegisterIsotopeTable", &G4IonTable::RegisterIsotopeTable)

      .def("GetIsotopeTable", &G4IonTable::GetIsotopeTable, py::arg("idx") = 0)
      .def("CreateAllIon", &G4IonTable::CreateAllIon)

      .def("CreateAllIsomer", &G4IonTable::CreateAllIsomer)
      .def("PrepareNuclideTable", &G4IonTable::PrepareNuclideTable)

      .def("GetIon", py::overload_cast<G4int, G4int, G4int>(&G4IonTable::GetIon), py::arg("Z"), py::arg("A"),
           py::arg("lvl") = 0, py::return_value_policy::reference_internal)

      .def("GetIon", py::overload_cast<G4int, G4int, G4int, G4int>(&G4IonTable::GetIon), py::arg("Z"), py::arg("A"),
           py::arg("L"), py::arg("lvl"), py::return_value_policy::reference_internal)

      .def("GetIon", py::overload_cast<G4int, G4int, G4double, G4int>(&G4IonTable::GetIon), py::arg("Z"), py::arg("A"),
           py::arg("E"), py::arg("J") = 0, py::return_value_policy::reference_internal)

      .def("GetIon", py::overload_cast<G4int, G4int, G4double, char, G4int>(&G4IonTable::GetIon), py::arg("Z"),
           py::arg("A"), py::arg("E"), py::arg("flbChar"), py::arg("J") = 0,
           py::return_value_policy::reference_internal)

      .def("GetIon", py::overload_cast<G4int, G4int, G4int, G4double, G4int>(&G4IonTable::GetIon), py::arg("Z"),
           py::arg("A"), py::arg("L"), py::arg("E"), py::arg("J") = 0, py::return_value_policy::reference_internal)

      .def("GetIon",
           py::overload_cast<G4int, G4int, G4int, G4double, G4Ions::G4FloatLevelBase, G4int>(&G4IonTable::GetIon),
           py::arg("Z"), py::arg("A"), py::arg("L"), py::arg("E"), py::arg("flb"), py::arg("J") = 0,
           py::return_value_policy::reference_internal)

      .def("GetIon", py::overload_cast<G4int, G4int, G4int, G4double, char, G4int>(&G4IonTable::GetIon), py::arg("Z"),
           py::arg("A"), py::arg("L"), py::arg("E"), py::arg("flbChar"), py::arg("J") = 0,
           py::return_value_policy::reference_internal)

      .def("GetIon", py::overload_cast<G4int>(&G4IonTable::GetIon), py::arg("encoding"))

      .def("FindIon", py::overload_cast<G4int, G4int, G4int>(&G4IonTable::FindIon), py::arg("Z"), py::arg("A"),
           py::arg("lvl") = 0, py::return_value_policy::reference_internal)

      .def("FindIon", py::overload_cast<G4int, G4int, G4int, G4int>(&G4IonTable::FindIon), py::arg("Z"), py::arg("A"),
           py::arg("L"), py::arg("lvl"), py::return_value_policy::reference_internal)

      .def("FindIon", py::overload_cast<G4int, G4int, G4double, G4int>(&G4IonTable::FindIon), py::arg("Z"),
           py::arg("A"), py::arg("E"), py::arg("J") = 0, py::return_value_policy::reference_internal)

      .def("FindIon", py::overload_cast<G4int, G4int, G4double, char, G4int>(&G4IonTable::FindIon), py::arg("Z"),
           py::arg("A"), py::arg("E"), py::arg("flbChar"), py::arg("J") = 0,
           py::return_value_policy::reference_internal)

      .def("FindIon", py::overload_cast<G4int, G4int, G4int, G4double, G4int>(&G4IonTable::FindIon), py::arg("Z"),
           py::arg("A"), py::arg("L"), py::arg("E"), py::arg("J") = 0, py::return_value_policy::reference_internal)

      .def("FindIon",
           py::overload_cast<G4int, G4int, G4int, G4double, G4Ions::G4FloatLevelBase, G4int>(&G4IonTable::FindIon),
           py::arg("Z"), py::arg("A"), py::arg("L"), py::arg("E"), py::arg("flb"), py::arg("J") = 0,
           py::return_value_policy::reference_internal)

      .def("FindIon", py::overload_cast<G4int, G4int, G4int, G4double, char, G4int>(&G4IonTable::FindIon), py::arg("Z"),
           py::arg("A"), py::arg("L"), py::arg("E"), py::arg("flbChar"), py::arg("J") = 0,
           py::return_value_policy::reference_internal)

      .def_static("IsIon", &G4IonTable::IsIon)
      .def_static("IsAntiIon", &G4IonTable::IsAntiIon)

      .def("GetIonName", py::overload_cast<G4int, G4int, G4int>(&G4IonTable::GetIonName, py::const_), py::arg("Z"),
           py::arg("A"), py::arg("lvl") = 0)
      .def("GetIonName",
           py::overload_cast<G4int, G4int, G4double, G4Ions::G4FloatLevelBase>(&G4IonTable::GetIonName, py::const_),
           py::arg("Z"), py::arg("A"), py::arg("E"), py::arg("flb") = G4Ions::G4FloatLevelBase::no_Float)

      .def("GetIonName",
           py::overload_cast<G4int, G4int, G4int, G4double, G4Ions::G4FloatLevelBase>(&G4IonTable::GetIonName,
                                                                                      py::const_),
           py::arg("Z"), py::arg("A"), py::arg("L"), py::arg("E"), py::arg("flb") = G4Ions::G4FloatLevelBase::no_Float)
      .def("GetIonName", py::overload_cast<G4int, G4int, G4int, G4int>(&G4IonTable::GetIonName, py::const_),
           py::arg("Z"), py::arg("A"), py::arg("L"), py::arg("lvl"))

      .def_static("GetNucleusEncoding",
                  py::overload_cast<G4int, G4int, G4double, G4int>(&G4IonTable::GetNucleusEncoding), py::arg("Z"),
                  py::arg("A"), py::arg("E") = 0.0, py::arg("lvl") = 0)

      .def_static("GetNucleusEncoding",
                  py::overload_cast<G4int, G4int, G4int, G4double, G4int>(&G4IonTable::GetNucleusEncoding),
                  py::arg("Z"), py::arg("A"), py::arg("L"), py::arg("E") = 0.0, py::arg("lvl") = 0)

      .def("GetIonMass", &G4IonTable::GetIonMass, py::arg("Z"), py::arg("A"), py::arg("L") = 0, py::arg("lvl") = 0)
      .def("GetNucleusMass", &G4IonTable::GetNucleusMass, py::arg("Z"), py::arg("A"), py::arg("L") = 0,
           py::arg("lvl") = 0)
      .def("GetIsomerMass", &G4IonTable::GetIsomerMass, py::arg("Z"), py::arg("A"), py::arg("lvl") = 0)

      .def("GetLifeTime", py::overload_cast<const G4ParticleDefinition *>(&G4IonTable::GetLifeTime, py::const_))

      .def("GetLifeTime",
           py::overload_cast<G4int, G4int, G4double, G4Ions::G4FloatLevelBase>(&G4IonTable::GetLifeTime, py::const_),
           py::arg("Z"), py::arg("A"), py::arg("E"), py::arg("flb") = G4Ions::G4FloatLevelBase::no_Float)

      .def("GetLifeTime", py::overload_cast<G4int, G4int, G4double, char>(&G4IonTable::GetLifeTime, py::const_),
           py::arg("Z"), py::arg("A"), py::arg("E"), py::arg("flbChar"))

      .def("GetMuonicAtom", py::overload_cast<G4Ions const *>(&G4IonTable::GetMuonicAtom))
      .def("GetMuonicAtom", py::overload_cast<G4int, G4int>(&G4IonTable::GetMuonicAtom))

      .def("Entries", &G4IonTable::Entries)
      .def("GetParticle", &G4IonTable::GetParticle, py::return_value_policy::reference)

      .def("Contains", &G4IonTable::Contains)

      .def("Insert", &G4IonTable::Insert)
      .def("Remove", &G4IonTable::Remove) // TODO

      .def("clear", &G4IonTable::clear)
      .def("size", &G4IonTable::size)
      .def("DumpTable", &G4IonTable::DumpTable, py::arg("particle_name") = "ALL");
}