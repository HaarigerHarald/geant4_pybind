#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VPVParameterisation.hh>
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

class PyG4VPVParameterisation : public G4VPVParameterisation, public py::trampoline_self_life_support {
public:
   using G4VPVParameterisation::G4VPVParameterisation;

   void ComputeTransformation(const G4int arg0, G4VPhysicalVolume *arg1) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VPVParameterisation, ComputeTransformation, arg0, arg1);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VPVParameterisation, ComputeSolid, arg0, arg1);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VPVParameterisation, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VPVParameterisation, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VPVParameterisation, GetMaterialScanner, );
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VPVParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VPVParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }
};

void export_G4VPVParameterisation(py::module &m)
{
   py::class_<G4VPVParameterisation, PyG4VPVParameterisation>(m, "G4VPVParameterisation")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VPVParameterisation &self) { return PyG4VPVParameterisation(self); })
      .def("__deepcopy__", [](const PyG4VPVParameterisation &self, py::dict) { return PyG4VPVParameterisation(self); })
      .def("ComputeTransformation", &G4VPVParameterisation::ComputeTransformation)
      .def("ComputeSolid", &G4VPVParameterisation::ComputeSolid, py::return_value_policy::reference)
      .def("ComputeMaterial", &G4VPVParameterisation::ComputeMaterial, py::arg("repNo"), py::arg("currentVol"),
           py::arg("parentTouch") = static_cast<const G4VTouchable *>(nullptr), py::return_value_policy::reference)

      .def("IsNested", &G4VPVParameterisation::IsNested)
      .def("GetMaterialScanner", &G4VPVParameterisation::GetMaterialScanner, py::return_value_policy::reference)

      .def("ComputeDimensions", py::overload_cast<G4Box &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Tubs &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Trd &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Trap &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Cons &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Sphere &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Orb &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Ellipsoid &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Torus &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Para &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Polycone &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Polyhedra &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_))

      .def("ComputeDimensions", py::overload_cast<G4Hype &, const G4int, const G4VPhysicalVolume *>(
                                   &G4VPVParameterisation::ComputeDimensions, py::const_));
}
