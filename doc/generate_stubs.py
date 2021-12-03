import sys
import os
import importlib.util
from pybind11_stubgen import *

module_name = sys.argv[1]
extdir = os.path.dirname(sys.argv[2])

AUTO_STUB_GENERATION = True

spec = importlib.util.spec_from_file_location(module_name, sys.argv[2])
module = importlib.util.module_from_spec(spec)

FunctionSignature.ignore_invalid_signature = True
FunctionSignature.ignore_invalid_defaultarg = True
FunctionSignature.signature_downgrade = False

moduleGen = ModuleStubsGenerator(module)
moduleGen.parse()

with open(os.path.join(extdir, module_name + '.pyi'), 'w') as init_pyi:
    init_pyi.write('\n'.join(moduleGen.to_lines()))
