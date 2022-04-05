# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import importlib
import unittest
from subprocess import run

import cffi as cffi


src_path = "C:/Users/Amelia/Desktop/Capstone/Daisy/DaisyExamples-master/MyProjects/Daisy-MultiFx-new/src/"

def load(filename):
    # load source code
    source = open(src_path + filename + '.cpp').read()
    includes = open(src_path + filename + '.h').read()

    # pass source code to CFFI
    ffibuilder = cffi.FFI()
    ffibuilder.cdef(includes)
    ffibuilder.set_source(filename + '_', source)
    ffibuilder.compile()

    # import and return resulting module
    module = importlib.import_module(filename + '_')
    return module.lib


class AddTest(unittest.TestCase):
    def test_addition(self):
        module = load('hello')
        #print(module)
        self.assertEqual(module.add(1, 2), 1 + 2)
        # self.assertEqual('foo'.upper(), 'FOO')


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    run(AddTest)
