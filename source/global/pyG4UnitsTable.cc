#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/operators.h>

#include <G4UnitsTable.hh>
#include <G4Accumulable.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UnitsTable(py::module &m)
{
   py::bind_vector<G4UnitsTable>(m, "G4UnitsTable");

   py::bind_vector<G4UnitsContainer>(m, "G4UnitsContainer");

   py::class_<G4UnitDefinition, py::nodelete>(m, "G4UnitDefinition", "Unit Definition")

      .def(py::init<const G4String &, const G4String &, const G4String &, G4double>())

      .def("GetName", &G4UnitDefinition::GetName)
      .def("GetSymbol", &G4UnitDefinition::GetSymbol)
      .def("GetValue", &G4UnitDefinition::GetValue)
      .def("PrintDefinition", &G4UnitDefinition::PrintDefinition)

      .def_static("BuildUnitsTable", &G4UnitDefinition::BuildUnitsTable)
      .def_static("PrintUnitsTable", &G4UnitDefinition::PrintUnitsTable)
      .def_static("GetUnitsTable", &G4UnitDefinition::GetUnitsTable, py::return_value_policy::reference)

      .def_static("GetValueOf", &G4UnitDefinition::GetValueOf)
      .def_static("GetCategory", &G4UnitDefinition::GetCategory);

   py::class_<G4UnitsCategory>(m, "G4UnitsCategory", "Units Category")

      .def(py::init<const G4String &>())

      .def("GetName", &G4UnitsCategory::GetName)
      .def("GetUnitsList", &G4UnitsCategory::GetUnitsList, py::return_value_policy::reference)
      .def("GetNameMxLen", &G4UnitsCategory::GetNameMxLen)
      .def("GetSymbMxLen", &G4UnitsCategory::GetSymbMxLen)
      .def("UpdateNameMxLen", &G4UnitsCategory::UpdateNameMxLen)
      .def("UpdateSymbMxLen", &G4UnitsCategory::UpdateSymbMxLen)
      .def("PrintCategory", &G4UnitsCategory::PrintCategory);

   py::class_<G4BestUnit>(m, "G4BestUnit", "present best unit")

      .def(py::init<G4double, const G4String &>(), py::arg("internalValue"), py::arg("category"))
      .def(py::init<const G4ThreeVector &, const G4String &>(), py::arg("internalValue"), py::arg("category"))
      .def(py::init<>([](G4Accumulable<G4double> internalValue, const G4String &category) {
              return new G4BestUnit(internalValue.GetValue(), category);
           }),
           py::arg("internalValue"), py::arg("category"))

      .def("GetCategory", &G4BestUnit::GetCategory)
      .def("GetIndexOfCategory", &G4BestUnit::GetIndexOfCategory)
      .def(
         "__str__",
         [](const G4BestUnit &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator())

      .def(
         "__format__",
         [](const G4BestUnit &self, const py::str &spec) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            std::size_t idx      = 0;
            std::string bestUnit = ss.str();
            double      value    = std::stod(bestUnit, &idx);
            py::object  format   = py::module::import("builtins").attr("format");
            return format(value, spec) + py::str(bestUnit.c_str() + idx);
         },
         py::is_operator());
}
