#ifndef TYPE_CAST_HH
#define TYPE_CAST_HH

#include <pybind11/pybind11.h>
#include <pybind11/cast.h>

#include <G4String.hh>

namespace pybind11 {
namespace detail {
template <>
struct type_caster<G4String> {
public:
   PYBIND11_TYPE_CASTER(G4String, _("G4String"));

   bool load(handle src, bool)
   {
      handle load_src = src;
      if (!src) {
         return false;
      } else if (!PyUnicode_Check(load_src.ptr())) {
         if (PYBIND11_BYTES_CHECK(src.ptr())) {

            const char *bytes = PYBIND11_BYTES_AS_STRING(src.ptr());
            if (bytes) {
               value = G4String(bytes, (size_t)PYBIND11_BYTES_SIZE(src.ptr()));
               return true;
            }
         }
         return false;
      }

      auto utfNbytes = reinterpret_steal<object>(PyUnicode_AsEncodedString(load_src.ptr(), "utf-8", nullptr));
      if (!utfNbytes) {
         PyErr_Clear();
         return false;
      }

      const auto *buffer = reinterpret_cast<const char *>(PYBIND11_BYTES_AS_STRING(utfNbytes.ptr()));
      size_t      length = (size_t)PYBIND11_BYTES_SIZE(utfNbytes.ptr()) / sizeof(char);
      value              = G4String(buffer, length);

      return true;
   }

   static handle cast(G4String src, return_value_policy /* policy */, handle /* parent */)
   {
      return PyUnicode_DecodeUTF8(src.c_str(), src.size(), nullptr);
   }
};
} // namespace detail
} // namespace pybind11

#endif // TYPE_CAST_HH
