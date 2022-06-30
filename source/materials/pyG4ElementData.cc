#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ElementData.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ElementData(py::module &m)
{
   py::class_<G4ElementData>(m, "G4ElementData")

      .def(py::init<>())
      .def("AddComponent", &G4ElementData::AddComponent, py::arg("Z"), py::arg("id"), py::arg("v"))
      .def("GetComponentDataByID", &G4ElementData::GetComponentDataByID, py::arg("Z"), py::arg("id"),
           py::return_value_policy::reference)

      .def("GetComponentDataByIndex", &G4ElementData::GetComponentDataByIndex, py::arg("Z"), py::arg("idx"),
           py::return_value_policy::reference)

      .def("GetComponentID", &G4ElementData::GetComponentID, py::arg("Z"), py::arg("idx"))
      .def("GetElement2DData", &G4ElementData::GetElement2DData, py::arg("Z"), py::return_value_policy::reference)
      .def("GetElementData", &G4ElementData::GetElementData, py::arg("Z"), py::return_value_policy::reference)
      .def("GetNumberOfComponents", &G4ElementData::GetNumberOfComponents, py::arg("Z"))
      .def("GetValueForComponent", &G4ElementData::GetValueForComponent, py::arg("Z"), py::arg("idx"),
           py::arg("kinEnergy"))

      .def("GetValueForElement", &G4ElementData::GetValueForElement, py::arg("Z"), py::arg("kinEnergy"))
      .def("InitialiseForComponent", &G4ElementData::InitialiseForComponent, py::arg("Z"), py::arg("nComponents") = 0)
      .def("InitialiseForElement", py::overload_cast<G4int, G4PhysicsVector *>(&G4ElementData::InitialiseForElement),
           py::arg("Z"), py::arg("v"))

      .def("InitialiseForElement", py::overload_cast<G4int, G4Physics2DVector *>(&G4ElementData::InitialiseForElement),
           py::arg("Z"), py::arg("v"))

      .def("SetName", &G4ElementData::SetName, py::arg("nam"));
}
