from KratosMultiphysics import *
from KratosMultiphysics.mpi import *
from KratosMultiphysics.MappingApplication import *

def run():
    Tester.SetVerbosity(Tester.Verbosity.TESTS_OUTPUTS) # TESTS_OUTPUTS
    Tester.RunTestCases("*MPICommunicatorExtensionTest*")

if __name__ == '__main__':
    run()