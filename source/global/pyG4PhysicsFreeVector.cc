#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PhysicsFreeVector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4PhysicsFreeVector : public G4PhysicsFreeVector, public py::trampoline_self_life_support {
public:
   using G4PhysicsFreeVector::G4PhysicsFreeVector;

   void Initialise() override { PYBIND11_OVERRIDE(void, G4PhysicsFreeVector, Initialise, ); }
};

void export_G4PhysicsFreeVector(py::module &m)
{
   py::class_<G4PhysicsFreeVector, PyG4PhysicsFreeVector, G4PhysicsVector>(m, "G4PhysicsFreeVector")

      .def("__copy__", [](const PyG4PhysicsFreeVector &self) { return new PyG4PhysicsFreeVector(self); })
      .def("__deepcopy__", [](const PyG4PhysicsFreeVector &self, py::dict) { return new PyG4PhysicsFreeVector(self); })
      .def("__copy__", [](const G4PhysicsFreeVector &self) { return new G4PhysicsFreeVector(self); })
      .def("__deepcopy__", [](const G4PhysicsFreeVector &self, py::dict) { return new G4PhysicsFreeVector(self); })
      .def(py::init<G4bool>(), py::arg("spline") = false)
      .def(py::init<G4int>(), py::arg("length"))
      .def(py::init<size_t, G4bool>(), py::arg("length"), py::arg("spline") = false)
      .def(py::init<size_t, G4double, G4double, G4bool>(), py::arg("length"), py::arg("emin"), py::arg("emax"),
           py::arg("spline") = false)

      .def(py::init<const std::vector<double> &, const std::vector<double> &, G4bool>(), py::arg("energies"),
           py::arg("values"), py::arg("spline") = false)

      .def(py::init<const G4double *, const G4double *, size_t, G4bool>(), py::arg("energies"), py::arg("values"),
           py::arg("length"), py::arg("spline") = false)

      .def("InsertValues", &G4PhysicsFreeVector::InsertValues, py::arg("energy"), py::arg("value"))
      .def("PutValue", &G4PhysicsFreeVector::PutValue, py::arg("index"), py::arg("e"), py::arg("value"))
      .def("PutValues", &G4PhysicsFreeVector::PutValues, py::arg("index"), py::arg("energy"), py::arg("value"));
}
