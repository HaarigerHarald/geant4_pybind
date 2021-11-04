#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VNestedParameterisation.hh>
#include <G4Material.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VTouchable.hh>
#include <G4VSolid.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Trd.hh>
#include <G4Trap.hh>
#include <G4Cons.hh>
#include <G4Sphere.hh>
#include <G4Orb.hh>
#include <G4Ellipsoid.hh>
#include <G4Torus.hh>
#include <G4Para.hh>
#include <G4Polycone.hh>
#include <G4Polyhedra.hh>
#include <G4Hype.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VNestedParameterisation : public G4VNestedParameterisation, public py::trampoline_self_life_support {
public:
   using G4VNestedParameterisation::G4VNestedParameterisation;

   G4Material *ComputeMaterial(G4VPhysicalVolume *currentVol, const G4int repNo,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE_PURE(G4Material *, G4VNestedParameterisation, ComputeMaterial, currentVol, repNo, parentTouch);
   }

   G4int GetNumberOfMaterials() const override
   {
      PYBIND11_OVERRIDE_PURE(G4int, G4VNestedParameterisation, GetNumberOfMaterials, );
   }

   G4Material *GetMaterial(G4int idx) const override
   {
      PYBIND11_OVERRIDE_PURE(G4Material *, G4VNestedParameterisation, GetMaterial, idx);
   }

   void ComputeTransformation(const G4int no, G4VPhysicalVolume *currentPV) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VNestedParameterisation, ComputeTransformation, no, currentPV);
   }

   G4VSolid *ComputeSolid(const G4int no, G4VPhysicalVolume *thisVol) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VNestedParameterisation, ComputeSolid, no, thisVol);
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VNestedParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VNestedParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VNestedParameterisation, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VNestedParameterisation, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VNestedParameterisation, GetMaterialScanner, );
   }
};

void export_G4VNestedParameterisation(py::module &m)
{
   py::class_<G4VNestedParameterisation, PyG4VNestedParameterisation, G4VPVParameterisation>(
      m, "G4VNestedParameterisation")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VNestedParameterisation &self) { return PyG4VNestedParameterisation(self); })
      .def("__deepcopy__",
           [](const PyG4VNestedParameterisation &self, py::dict) { return PyG4VNestedParameterisation(self); })

      .def("ComputeMaterial",
           py::overload_cast<G4VPhysicalVolume *, const G4int, const G4VTouchable *>(
              &G4VNestedParameterisation::ComputeMaterial),
           py::arg("currentVol"), py::arg("repNo"), py::arg("parentTouch") = static_cast<const G4VTouchable *>(nullptr),
           py::return_value_policy::reference)

      .def("GetNumberOfMaterials", &G4VNestedParameterisation::GetNumberOfMaterials)
      .def("GetMaterial", &G4VNestedParameterisation::GetMaterial, py::arg("idx"), py::return_value_policy::reference)
      .def("ComputeTransformation", &G4VNestedParameterisation::ComputeTransformation, py::arg("no"),
           py::arg("currentPV"))

      .def("ComputeSolid", &G4VNestedParameterisation::ComputeSolid, py::arg("no"), py::arg("thisVol"),
           py::return_value_policy::reference)

      .def("ComputeDimensions", py::overload_cast<G4Box &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Tubs &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Trd &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Trap &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Cons &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Sphere &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Orb &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Ellipsoid &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Torus &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Para &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Polycone &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Polyhedra &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Hype &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VNestedParameterisation::ComputeDimensions, py::const_))

      .def("ComputeMaterial",
           py::overload_cast<const G4int, G4VPhysicalVolume *, const G4VTouchable *>(
              &G4VNestedParameterisation::ComputeMaterial),
           py::arg("repNo"), py::arg("currentVol"), py::arg("parentTouch") = static_cast<const G4VTouchable *>(nullptr),
           py::return_value_policy::reference)

      .def("IsNested", &G4VNestedParameterisation::IsNested)
      .def("GetMaterialScanner", &G4VNestedParameterisation::GetMaterialScanner, py::return_value_policy::reference);
}
