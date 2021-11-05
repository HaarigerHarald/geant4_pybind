#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParameterisationBox.hh>
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

class PyG4VParameterisationBox : public G4VParameterisationBox, public py::trampoline_self_life_support {
public:
   using G4VParameterisationBox::G4VParameterisationBox;

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VParameterisationBox, ComputeTransformation, copyNo, physVol);
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VParameterisationBox, GetMaxParameter, );
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VParameterisationBox, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4VParameterisationBox, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VParameterisationBox, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VParameterisationBox, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VParameterisationBox, GetMaterialScanner, );
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationBox, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationBox::ComputeDimensions(arg0, arg1, arg2);
   }
};

class PyG4ParameterisationBoxX : public G4ParameterisationBoxX, public py::trampoline_self_life_support {
public:
   using G4ParameterisationBoxX::G4ParameterisationBoxX;

   G4double GetMaxParameter() const override { PYBIND11_OVERRIDE(G4double, G4ParameterisationBoxX, GetMaxParameter, ); }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationBoxX, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Box &box, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationBoxX, "ComputeDimensions", std::addressof(box), copyNo, physVol);
      G4ParameterisationBoxX::ComputeDimensions(box, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationBoxX, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationBoxX, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationBoxX, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationBoxX, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationBoxX, GetMaterialScanner, );
   }
};

class PyG4ParameterisationBoxY : public G4ParameterisationBoxY, public py::trampoline_self_life_support {
public:
   using G4ParameterisationBoxY::G4ParameterisationBoxY;

   G4double GetMaxParameter() const override { PYBIND11_OVERRIDE(G4double, G4ParameterisationBoxY, GetMaxParameter, ); }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationBoxY, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Box &box, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationBoxY, "ComputeDimensions", std::addressof(box), copyNo, physVol);
      G4ParameterisationBoxY::ComputeDimensions(box, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationBoxY, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationBoxY, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationBoxY, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationBoxY, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationBoxY, GetMaterialScanner, );
   }
};

class PyG4ParameterisationBoxZ : public G4ParameterisationBoxZ, public py::trampoline_self_life_support {
public:
   using G4ParameterisationBoxZ::G4ParameterisationBoxZ;

   G4double GetMaxParameter() const override { PYBIND11_OVERRIDE(G4double, G4ParameterisationBoxZ, GetMaxParameter, ); }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationBoxZ, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Box &box, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationBoxZ, "ComputeDimensions", std::addressof(box), copyNo, physVol);
      G4ParameterisationBoxZ::ComputeDimensions(box, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationBoxZ, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationBoxZ, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationBoxZ, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationBoxZ, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationBoxZ, GetMaterialScanner, );
   }
};

void export_G4ParameterisationBox(py::module &m)
{
   py::class_<G4VParameterisationBox, PyG4VParameterisationBox, G4VDivisionParameterisation>(m,
                                                                                             "G4VParameterisationBox")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4VParameterisationBox &self) { return PyG4VParameterisationBox(self); })

      .def("__deepcopy__",
           [](const PyG4VParameterisationBox &self, py::dict) { return PyG4VParameterisationBox(self); });

   py::class_<G4ParameterisationBoxX, PyG4ParameterisationBoxX, G4VParameterisationBox>(m, "G4ParameterisationBoxX")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationBoxX &self) { return PyG4ParameterisationBoxX(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationBoxX &self, py::dict) { return PyG4ParameterisationBoxX(self); })

      .def("GetMaxParameter", &G4ParameterisationBoxX::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationBoxX::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Box &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationBoxX::ComputeDimensions, py::const_),
           py::arg("box"), py::arg("copyNo"), py::arg("physVol"));

   py::class_<G4ParameterisationBoxY, PyG4ParameterisationBoxY, G4VParameterisationBox>(m, "G4ParameterisationBoxY")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationBoxY &self) { return PyG4ParameterisationBoxY(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationBoxY &self, py::dict) { return PyG4ParameterisationBoxY(self); })

      .def("GetMaxParameter", &G4ParameterisationBoxY::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationBoxY::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Box &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationBoxY::ComputeDimensions, py::const_),
           py::arg("box"), py::arg("copyNo"), py::arg("physVol"));

   py::class_<G4ParameterisationBoxZ, PyG4ParameterisationBoxZ, G4VParameterisationBox>(m, "G4ParameterisationBoxZ")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationBoxZ &self) { return PyG4ParameterisationBoxZ(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationBoxZ &self, py::dict) { return PyG4ParameterisationBoxZ(self); })

      .def("GetMaxParameter", &G4ParameterisationBoxZ::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationBoxZ::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Box &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationBoxZ::ComputeDimensions, py::const_),
           py::arg("box"), py::arg("copyNo"), py::arg("physVol"));
}
