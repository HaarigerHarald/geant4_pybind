#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VPVDivisionFactory.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VPVDivisionFactory : public G4VPVDivisionFactory, public py::trampoline_self_life_support {
public:
   using G4VPVDivisionFactory::G4VPVDivisionFactory;

   G4VPhysicalVolume *CreatePVDivision(const G4String &pName, G4LogicalVolume *pLogical, G4LogicalVolume *pMother,
                                       const EAxis pAxis, const G4int nReplicas, const G4double width,
                                       const G4double offset) override
   {
      PYBIND11_OVERRIDE_PURE(G4VPhysicalVolume *, G4VPVDivisionFactory, CreatePVDivision, pName, pLogical, pMother,
                             pAxis, nReplicas, width, offset);
   }

   G4VPhysicalVolume *CreatePVDivision(const G4String &pName, G4LogicalVolume *pLogical,
                                       G4LogicalVolume *pMotherLogical, const EAxis pAxis, const G4int nReplicas,
                                       const G4double offset) override
   {
      PYBIND11_OVERRIDE_PURE(G4VPhysicalVolume *, G4VPVDivisionFactory, CreatePVDivision, pName, pLogical,
                             pMotherLogical, pAxis, nReplicas, offset);
   }

   G4VPhysicalVolume *CreatePVDivision(const G4String &pName, G4LogicalVolume *pLogical,
                                       G4LogicalVolume *pMotherLogical, const EAxis pAxis, const G4double width,
                                       const G4double offset) override
   {
      PYBIND11_OVERRIDE_PURE(G4VPhysicalVolume *, G4VPVDivisionFactory, CreatePVDivision, pName, pLogical,
                             pMotherLogical, pAxis, width, offset);
   }

   G4VPhysicalVolume *CreatePVDivision(const G4String &pName, G4LogicalVolume *pLogical,
                                       G4LogicalVolume *pMotherLogical, const G4VPVParameterisation *param) override
   {
      PYBIND11_OVERRIDE_PURE(G4VPhysicalVolume *, G4VPVDivisionFactory, CreatePVDivision, pName, pLogical,
                             pMotherLogical, param);
   }

   G4bool IsPVDivision(const G4VPhysicalVolume *pv) const override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VPVDivisionFactory, IsPVDivision, pv);
   }
};

void export_G4VPVDivisionFactory(py::module &m)
{
   py::class_<G4VPVDivisionFactory, PyG4VPVDivisionFactory, py::nodelete>(m, "G4VPVDivisionFactory")

      .def("__copy__", [](const PyG4VPVDivisionFactory &self) { return PyG4VPVDivisionFactory(self); })
      .def("__deepcopy__", [](const PyG4VPVDivisionFactory &self, py::dict) { return PyG4VPVDivisionFactory(self); })
      .def_static("Instance", &G4VPVDivisionFactory::Instance, py::return_value_policy::reference)
      .def("CreatePVDivision",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int,
                             const G4double, const G4double>(&G4VPVDivisionFactory::CreatePVDivision),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMother"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"), py::return_value_policy::reference)

      .def("CreatePVDivision",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int,
                             const G4double>(&G4VPVDivisionFactory::CreatePVDivision),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("offset"), py::return_value_policy::reference)

      .def("CreatePVDivision",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4double,
                             const G4double>(&G4VPVDivisionFactory::CreatePVDivision),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("width"),
           py::arg("offset"), py::return_value_policy::reference)

      .def("CreatePVDivision",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const G4VPVParameterisation *>(
              &G4VPVDivisionFactory::CreatePVDivision),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("param"),
           py::return_value_policy::reference)

      .def("IsPVDivision", &G4VPVDivisionFactory::IsPVDivision, py::arg("pv"));
}
