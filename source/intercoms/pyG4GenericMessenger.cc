#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GenericMessenger.hh>
#include <G4UIdirectory.hh>

#include <array>
#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

struct func_handle {
   py::function f;
   func_handle() {}
   func_handle(py::function &&f_) : f(std::move(f_)) {}

   ~func_handle()
   {
      py::gil_scoped_acquire acq;
      py::function           kill_f(std::move(f));
   }
};

#define PROXY_SET(arg)                                                               \
   void proxy0##arg(arg val)                                                         \
   {                                                                                 \
      py::gil_scoped_acquire acq;                                                    \
      pyFuncts##arg[0].f(val);                                                       \
   }                                                                                 \
                                                                                     \
   void proxy1##arg(arg val)                                                         \
   {                                                                                 \
      py::gil_scoped_acquire acq;                                                    \
      pyFuncts##arg[1].f(val);                                                       \
   }                                                                                 \
                                                                                     \
   void proxy2##arg(arg val)                                                         \
   {                                                                                 \
      py::gil_scoped_acquire acq;                                                    \
      pyFuncts##arg[2].f(val);                                                       \
   }                                                                                 \
                                                                                     \
   void proxy3##arg(arg val)                                                         \
   {                                                                                 \
      py::gil_scoped_acquire acq;                                                    \
      pyFuncts##arg[3].f(val);                                                       \
   }                                                                                 \
                                                                                     \
   void proxy4##arg(arg val)                                                         \
   {                                                                                 \
      py::gil_scoped_acquire acq;                                                    \
      pyFuncts##arg[4].f(val);                                                       \
   }                                                                                 \
                                                                                     \
   std::array<void (ProxyG4GenericMessenger::*)(arg), 5> functs##arg = {             \
      {&ProxyG4GenericMessenger::proxy0##arg, &ProxyG4GenericMessenger::proxy1##arg, \
       &ProxyG4GenericMessenger::proxy2##arg, &ProxyG4GenericMessenger::proxy3##arg, \
       &ProxyG4GenericMessenger::proxy4##arg}};                                      \
                                                                                     \
   std::array<func_handle, 5> pyFuncts##arg = {                                      \
      {func_handle(), func_handle(), func_handle(), func_handle(), func_handle()}};  \
   size_t pyFuncNum##arg = 0

#define PROXY_REGISTER(arg, func, classVar) \
   classVar.pyFuncts##arg[classVar.pyFuncNum##arg++] = func_handle(std::move(func));

#define PROXY_GET_LAST(arg, classVar) classVar.functs##arg[classVar.pyFuncNum##arg - 1]

/* This is a hack, the neater solution for the whole function problem is making
 * G4GenericMessenger accept regular std::functions. */
class ProxyG4GenericMessenger : public G4GenericMessenger {

public:
   ProxyG4GenericMessenger(void *obj, const G4String &dir = "", const G4String &doc = "")
      : G4GenericMessenger(this, dir, doc)
   {
   }

   PROXY_SET(G4bool);
   PROXY_SET(G4int);
   PROXY_SET(G4double);
};

enum PropertyType { type_bool, type_int, type_double };

struct PropertyWrapper {

   union {
      G4bool   boolVal;
      G4int    intVal;
      G4double doubleVal;
   };

   PropertyType type;

   PropertyWrapper(G4bool val) : boolVal(val), type(type_bool) {}

   PropertyWrapper(G4int val) : intVal(val), type(type_int) {}

   PropertyWrapper(G4double val) : doubleVal(val), type(type_double) {}
};

void export_G4GenericMessenger(py::module &m)
{
   py::class_<ProxyG4GenericMessenger, G4UImessenger> genericMessenger(m, "G4GenericMessenger");

   py::class_<PropertyWrapper>(genericMessenger, "Property")

      .def(py::init<>([](const py::object &variable) {
         if (py::isinstance<py::bool_>(variable)) {
            G4bool val = variable.cast<G4bool>();
            return new PropertyWrapper(val);
         } else if (py::isinstance<py::int_>(variable)) {
            G4int val = variable.cast<G4int>();
            return new PropertyWrapper(val);
         } else if (py::isinstance<py::float_>(variable)) {
            G4double val = variable.cast<G4double>();
            return new PropertyWrapper(val);
         }
         py::pybind11_fail("Property must be bool, int or float!");
      }))

      .def_property(
         "value",
         [](PropertyWrapper &self) -> py::object {
            if (self.type == type_bool) {
               return py::bool_(self.boolVal);
            } else if (self.type == type_int) {
               return py::int_(self.intVal);
            } else if (self.type == type_double) {
               return py::float_(self.doubleVal);
            }
            return py::none();
         },
         [](PropertyWrapper &self, const py::object &variable) {
            if (self.type == type_bool) {
               self.boolVal = variable.cast<G4bool>();
            } else if (self.type == type_int) {
               self.intVal = variable.cast<G4int>();
            } else if (self.type == type_double) {
               self.doubleVal = variable.cast<G4double>();
            }
         })

      .def(
         "__str__",
         [](const PropertyWrapper &self) {
            std::stringstream ss;
            if (self.type == type_bool) {
               ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self.boolVal;
            } else if (self.type == type_int) {
               ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self.intVal;
            } else if (self.type == type_double) {
               ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self.doubleVal;
            }
            return ss.str();
         },
         py::is_operator())

      .def(
         "__int__",
         [](const PropertyWrapper &self) {
            if (self.type == type_bool) {
               return py::int_((long)self.boolVal);
            } else if (self.type == type_int) {
               return py::int_((long)self.intVal);
            } else if (self.type == type_double) {
               return py::int_((long)self.doubleVal);
            }
            py::pybind11_fail("Property must be bool, int or float!");
         },
         py::is_operator())

      .def(
         "__float__",
         [](const PropertyWrapper &self) {
            if (self.type == type_bool) {
               return py::float_((double)self.boolVal);
            } else if (self.type == type_int) {
               return py::float_((double)self.intVal);
            } else if (self.type == type_double) {
               return py::float_(self.doubleVal);
            }
            py::pybind11_fail("Property must be bool, int or float!");
         },
         py::is_operator())

      .def(
         "__bool__",
         [](const PropertyWrapper &self) {
            if (self.type == type_bool) {
               return py::bool_(self.boolVal);
            } else if (self.type == type_int) {
               return py::bool_(self.intVal);
            } else if (self.type == type_double) {
               return py::bool_(self.doubleVal);
            }
            py::pybind11_fail("Property must be bool, int or float!");
         },
         py::is_operator());

   py::class_<G4GenericMessenger::Command> gmCommand(genericMessenger, "Command");

   py::enum_<G4GenericMessenger::Command::UnitSpec>(gmCommand, "UnitSpec")
      .value("UnitCategory", G4GenericMessenger::Command::UnitCategory)
      .value("UnitDefault", G4GenericMessenger::Command::UnitDefault)
      .export_values();

   gmCommand.def("SetStates", py::overload_cast<G4ApplicationState>(&G4GenericMessenger::Command::SetStates))
      .def("SetStates",
           py::overload_cast<G4ApplicationState, G4ApplicationState>(&G4GenericMessenger::Command::SetStates))

      .def("SetStates", py::overload_cast<G4ApplicationState, G4ApplicationState, G4ApplicationState>(
                           &G4GenericMessenger::Command::SetStates))

      .def("SetStates",
           py::overload_cast<G4ApplicationState, G4ApplicationState, G4ApplicationState, G4ApplicationState>(
              &G4GenericMessenger::Command::SetStates))

      .def("SetStates",
           py::overload_cast<G4ApplicationState, G4ApplicationState, G4ApplicationState, G4ApplicationState,
                             G4ApplicationState>(&G4GenericMessenger::Command::SetStates))

      .def("SetRange", &G4GenericMessenger::Command::SetRange)
      .def("SetGuidance", &G4GenericMessenger::Command::SetGuidance)
      .def("SetUnit", &G4GenericMessenger::Command::SetUnit)
      .def("SetUnitCategory", &G4GenericMessenger::Command::SetUnitCategory)
      .def("SetDefaultUnit", &G4GenericMessenger::Command::SetDefaultUnit)
      .def("SetParameterName",
           py::overload_cast<const G4String &, G4bool, G4bool>(&G4GenericMessenger::Command::SetParameterName),
           py::arg("name"), py::arg("omittable"), py::arg("currentAsDefault") = false)

      .def("SetParameterName",
           py::overload_cast<const G4String &, const G4String &, const G4String &, G4bool, G4bool>(
              &G4GenericMessenger::Command::SetParameterName),
           py::arg("name"), py::arg("arg1"), py::arg("arg2"), py::arg("omittable"), py::arg("currentAsDefault") = false)

      .def("SetParameterName", &G4GenericMessenger::Command::SetDefaultValue)
      .def("SetDefaultValue", &G4GenericMessenger::Command::SetDefaultValue)
      .def("SetCandidates", &G4GenericMessenger::Command::SetCandidates)
      .def("SetToBeBroadcasted", &G4GenericMessenger::Command::SetToBeBroadcasted)
      .def("SetToBeFlushed", &G4GenericMessenger::Command::SetToBeFlushed)
      .def("SetWorkerThreadOnly", &G4GenericMessenger::Command::SetWorkerThreadOnly);

   genericMessenger
      .def(py::init<void *, const G4String &, const G4String &>(), py::arg("obj"), py::arg("dir") = "",
           py::arg("doc") = "")

      .def("GetCurrentValue", &G4GenericMessenger::GetCurrentValue, py::arg("command"))
      .def("SetNewValue", &G4GenericMessenger::SetNewValue, py::arg("command"), py::arg("newValue"))

      .def(
         "DeclareProperty",
         [](ProxyG4GenericMessenger &self, const G4String &name, PropertyWrapper *wrapper, const G4String &doc) {
            if (wrapper->type == type_bool) {
               return self.DeclareProperty(name, G4AnyType(wrapper->boolVal), doc);
            } else if (wrapper->type == type_int) {
               return self.DeclareProperty(name, G4AnyType(wrapper->intVal), doc);
            } else {
               return self.DeclareProperty(name, G4AnyType(wrapper->doubleVal), doc);
            }
         },
         py::arg("name"), py::arg("variable"), py::arg("doc") = "")

      .def(
         "DeclarePropertyWithUnit",
         [](ProxyG4GenericMessenger &self, const G4String &name, const G4String &defaultUnit, PropertyWrapper *wrapper,
            const G4String &doc) {
            if (wrapper->type == type_bool) {
               return self.DeclarePropertyWithUnit(name, defaultUnit, G4AnyType(wrapper->boolVal), doc);
            } else if (wrapper->type == type_int) {
               return self.DeclarePropertyWithUnit(name, defaultUnit, G4AnyType(wrapper->intVal), doc);
            } else {
               return self.DeclarePropertyWithUnit(name, defaultUnit, G4AnyType(wrapper->doubleVal), doc);
            }
         },
         py::arg("name"), py::arg("defaultUnit"), py::arg("variable"), py::arg("doc") = "")

      .def(
         "DeclareMethod",
         [](ProxyG4GenericMessenger &self, const G4String &name, py::function fun, const G4String &doc) {
            py::object get_type_hints = py::module::import("typing").attr("get_type_hints");
            py::list   types          = py::list(get_type_hints(fun).attr("values")());

            if (types.size() < 1) {
               PROXY_REGISTER(G4double, fun, self);
               return self.DeclareMethod(name, PROXY_GET_LAST(G4double, self), doc);
            } else {
               py::object argtype = types[0];

               if (argtype.is(py::bool_().get_type())) {
                  PROXY_REGISTER(G4bool, fun, self);
                  return self.DeclareMethod(name, PROXY_GET_LAST(G4bool, self), doc);
               } else if (argtype.is(py::int_().get_type())) {
                  PROXY_REGISTER(G4int, fun, self);
                  return self.DeclareMethod(name, PROXY_GET_LAST(G4int, self), doc);
               } else {
                  PROXY_REGISTER(G4double, fun, self);
                  return self.DeclareMethod(name, PROXY_GET_LAST(G4double, self), doc);
               }
            }
         },
         py::arg("name"), py::arg("fun"), py::arg("doc") = "")
      .def(
         "DeclareMethodWithUnit",
         [](ProxyG4GenericMessenger &self, const G4String &name, const G4String &defaultUnit, py::function fun,
            const G4String &doc) {
            py::object get_type_hints = py::module::import("typing").attr("get_type_hints");
            py::list   types          = py::list(get_type_hints(fun).attr("values")());

            if (types.size() < 1) {
               PROXY_REGISTER(G4double, fun, self);
               return self.DeclareMethodWithUnit(name, defaultUnit, PROXY_GET_LAST(G4double, self), doc);
            } else {
               py::object argtype = types[0];

               if (argtype.is(py::bool_().get_type())) {
                  PROXY_REGISTER(G4bool, fun, self);
                  return self.DeclareMethodWithUnit(name, defaultUnit, PROXY_GET_LAST(G4bool, self), doc);
               } else if (argtype.is(py::int_().get_type())) {
                  PROXY_REGISTER(G4int, fun, self);
                  return self.DeclareMethodWithUnit(name, defaultUnit, PROXY_GET_LAST(G4int, self), doc);
               } else {
                  PROXY_REGISTER(G4double, fun, self);
                  return self.DeclareMethodWithUnit(name, defaultUnit, PROXY_GET_LAST(G4double, self), doc);
               }
            }
         },
         py::arg("name"), py::arg("defaultUnit"), py::arg("fun"), py::arg("doc") = "")

      .def("SetDirectory", &G4GenericMessenger::SetDirectory, py::arg("dir"))
      .def("SetGuidance", &G4GenericMessenger::SetGuidance);
}
