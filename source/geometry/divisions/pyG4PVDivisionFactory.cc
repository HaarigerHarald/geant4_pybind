#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PVDivisionFactory.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4PVDivisionFactory : public G4PVDivisionFactory, public py::trampoline_self_life_support {
public:
   using G4PVDivisionFactory::G4PVDivisionFactory;

   G4VPhysicalVolume *CreatePVDivision(const G4String &pName, G4LogicalVolume *pLogical, G4LogicalVolume *pMother,
                                       const EAxis pAxis, const G4int nReplicas, const G4double width,
                                       const G4double offset) override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4PVDivisionFactory, CreatePVDivision, pName, pLogical, pMother, pAxis,
                        nReplicas, width, offset);
   }

   G4VPhysicalVolume *CreatePVDivision(const G4String &pName, G4LogicalVolume *pLogical,
                                       G4LogicalVolume *pMotherLogical, const EAxis pAxis, const G4int nReplicas,
                                       const G4double offset) override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4PVDivisionFactory, CreatePVDivision, pName, pLogical, pMotherLogical,
                        pAxis, nReplicas, offset);
   }

   G4VPhysicalVolume *CreatePVDivision(const G4String &pName, G4LogicalVolume *pLogical,
                                       G4LogicalVolume *pMotherLogical, const EAxis pAxis, const G4double width,
                                       const G4double offset) override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4PVDivisionFactory, CreatePVDivision, pName, pLogical, pMotherLogical,
                        pAxis, width, offset);
   }

   G4VPhysicalVolume *CreatePVDivision(const G4String &pName, G4LogicalVolume *pLogical,
                                       G4LogicalVolume *pMotherLogical, const G4VPVParameterisation *param) override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4PVDivisionFactory, CreatePVDivision, pName, pLogical, pMotherLogical,
                        param);
   }

   G4bool IsPVDivision(const G4VPhysicalVolume *pv) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4PVDivisionFactory, IsPVDivision, pv);
   }
};

void export_G4PVDivisionFactory(py::module &m)
{
   py::class_<G4PVDivisionFactory, PyG4PVDivisionFactory, G4VPVDivisionFactory, py::nodelete>(m, "G4PVDivisionFactory")

      .def("__copy__", [](const PyG4PVDivisionFactory &self) { return PyG4PVDivisionFactory(self); })
      .def("__deepcopy__", [](const PyG4PVDivisionFactory &self, py::dict) { return PyG4PVDivisionFactory(self); })

      .def("CreatePVDivision",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int,
                             const G4double, const G4double>(&G4PVDivisionFactory::CreatePVDivision),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMother"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"), py::return_value_policy::reference)

      .def("CreatePVDivision",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int,
                             const G4double>(&G4PVDivisionFactory::CreatePVDivision),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("offset"), py::return_value_policy::reference)

      .def("CreatePVDivision",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4double,
                             const G4double>(&G4PVDivisionFactory::CreatePVDivision),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("width"),
           py::arg("offset"), py::return_value_policy::reference)

      .def("CreatePVDivision",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const G4VPVParameterisation *>(
              &G4PVDivisionFactory::CreatePVDivision),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("param"),
           py::return_value_policy::reference)

      .def("IsPVDivision", &G4PVDivisionFactory::IsPVDivision, py::arg("pv"))
      .def_static("GetInstance", &G4PVDivisionFactory::GetInstance, py::return_value_policy::reference);
}
