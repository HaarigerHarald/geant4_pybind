import os
import sys
import subprocess


def test_example(dir, py_file, macro_file, out_file, extra_params=[]):
    examples_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), '../examples')

    py_file = os.path.join(os.path.join(examples_dir, dir), py_file)
    macro_file = os.path.join(os.path.join(examples_dir, dir), macro_file)
    out_file = os.path.join(os.path.join(examples_dir, dir), out_file)

    params = [sys.executable, py_file]
    params += extra_params
    params += [macro_file]
    output = subprocess.run(params, stdout=subprocess.PIPE)

    with open(out_file, 'r') as file:
        if output.stdout.decode('utf-8').find(file.read()) == -1:
            raise Exception(output.stdout.decode('utf-8'))


test_example('B1', 'exampleB1.py', 'exampleB1.in', 'exampleB1.out')

test_example('B2', 'exampleB2a.py', 'exampleB2.in', 'exampleB2a.out')
test_example('B2', 'exampleB2b.py', 'exampleB2.in', 'exampleB2b.out')

test_example('B3', 'exampleB3a.py', 'exampleB3.in', 'exampleB3a.out')
#test_example('B3', 'exampleB3b.py', 'exampleB3.in', 'exampleB3b.out')

test_example('B4', 'exampleB4a.py', 'exampleB4.in', 'exampleB4a.out', ['-m'])
test_example('B4', 'exampleB4b.py', 'exampleB4.in', 'exampleB4b.out', ['-m'])
test_example('B4', 'exampleB4c.py', 'exampleB4.in', 'exampleB4c.out', ['-m'])
test_example('B4', 'exampleB4d.py', 'exampleB4.in', 'exampleB4d.out', ['-m'])
