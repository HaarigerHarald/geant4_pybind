#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParameterisationPara.hh>
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

class PyG4VParameterisationPara : public G4VParameterisationPara, public py::trampoline_self_life_support {
public:
   using G4VParameterisationPara::G4VParameterisationPara;

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VParameterisationPara, ComputeTransformation, copyNo, physVol);
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VParameterisationPara, GetMaxParameter, );
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VParameterisationPara, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4VParameterisationPara, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VParameterisationPara, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VParameterisationPara, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VParameterisationPara, GetMaterialScanner, );
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPara, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPara::ComputeDimensions(arg0, arg1, arg2);
   }
};

class PyG4ParameterisationParaX : public G4ParameterisationParaX, public py::trampoline_self_life_support {
public:
   using G4ParameterisationParaX::G4ParameterisationParaX;

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationParaX, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationParaX, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Para &para, const G4int copyNo, const G4VPhysicalVolume *pv) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationParaX, "ComputeDimensions", std::addressof(para), copyNo, pv);
      G4ParameterisationParaX::ComputeDimensions(para, copyNo, pv);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationParaX, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationParaX, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationParaX, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationParaX, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationParaX, GetMaterialScanner, );
   }
};

class PyG4ParameterisationParaY : public G4ParameterisationParaY, public py::trampoline_self_life_support {
public:
   using G4ParameterisationParaY::G4ParameterisationParaY;

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationParaY, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationParaY, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Para &para, const G4int copyNo, const G4VPhysicalVolume *pv) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationParaY, "ComputeDimensions", std::addressof(para), copyNo, pv);
      G4ParameterisationParaY::ComputeDimensions(para, copyNo, pv);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationParaY, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationParaY, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationParaY, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationParaY, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationParaY, GetMaterialScanner, );
   }
};

class PyG4ParameterisationParaZ : public G4ParameterisationParaZ, public py::trampoline_self_life_support {
public:
   using G4ParameterisationParaZ::G4ParameterisationParaZ;

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationParaZ, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationParaZ, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Para &para, const G4int copyNo, const G4VPhysicalVolume *pv) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationParaZ, "ComputeDimensions", std::addressof(para), copyNo, pv);
      G4ParameterisationParaZ::ComputeDimensions(para, copyNo, pv);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationParaZ, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationParaZ, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationParaZ, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationParaZ, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationParaZ, GetMaterialScanner, );
   }
};

void export_G4ParameterisationPara(py::module &m)
{
   py::class_<G4VParameterisationPara, PyG4VParameterisationPara, G4VDivisionParameterisation>(
      m, "G4VParameterisationPara")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4VParameterisationPara &self) { return PyG4VParameterisationPara(self); })

      .def("__deepcopy__",
           [](const PyG4VParameterisationPara &self, py::dict) { return PyG4VParameterisationPara(self); });

   py::class_<G4ParameterisationParaX, PyG4ParameterisationParaX, G4VParameterisationPara>(m, "G4ParameterisationParaX")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationParaX &self) { return PyG4ParameterisationParaX(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationParaX &self, py::dict) { return PyG4ParameterisationParaX(self); })

      .def("GetMaxParameter", &G4ParameterisationParaX::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationParaX::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Para &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationParaX::ComputeDimensions, py::const_),
           py::arg("para"), py::arg("copyNo"), py::arg("pv"));

   py::class_<G4ParameterisationParaY, PyG4ParameterisationParaY, G4VParameterisationPara>(m, "G4ParameterisationParaY")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationParaY &self) { return PyG4ParameterisationParaY(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationParaY &self, py::dict) { return PyG4ParameterisationParaY(self); })

      .def("GetMaxParameter", &G4ParameterisationParaY::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationParaY::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Para &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationParaY::ComputeDimensions, py::const_),
           py::arg("para"), py::arg("copyNo"), py::arg("pv"));

   py::class_<G4ParameterisationParaZ, PyG4ParameterisationParaZ, G4VParameterisationPara>(m, "G4ParameterisationParaZ")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationParaZ &self) { return PyG4ParameterisationParaZ(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationParaZ &self, py::dict) { return PyG4ParameterisationParaZ(self); })

      .def("GetMaxParameter", &G4ParameterisationParaZ::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationParaZ::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Para &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationParaZ::ComputeDimensions, py::const_),
           py::arg("para"), py::arg("copyNo"), py::arg("pv"));
}
