# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import unittest

from setuptools._entry_points import load
from setuptools.launch import run


class AddTest(unittest.TestCase):
    def test_addition(self):
        module = load('hello')
        self.assertEqual(module.add(1,2), 1 + 2)

def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    run(AddTest)

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
