import sys
kratos_benchmarking_path = '../../../../benchmarking' 
sys.path.append(kratos_benchmarking_path)
import benchmarking

print "Building reference data for Moving_Sphere..."
benchmarking.BuildReferenceData("ProjectionTest_3D_benchmarking.py", "ProjectionTest_3D_benchmarking_ref.txt")
