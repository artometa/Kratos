Work_Dir=/home/inigo/simulations/naca0012/07_salome/05_MeshRefinement

Generate_Mesh_File_Path=$PWD/generate_mdpas/generateMeshRefinement.py
Salome_Converter_File_Path=$PWD/generate_mdpas/use_converter.py
Mesh_Refinement_File_Path=$PWD/MeshRefinement.py

sed 's|'"Number_Of_Refinements = TBD"'|'"Number_Of_Refinements = $Number_Of_Refinements"'|g' -i /$Generate_Mesh_File_Path \
                                                            /$Salome_Converter_File_Path /$Mesh_Refinement_File_Path

sed 's|'"Number_Of_AOAS = TBD"'|'"Number_Of_AOAS = $Number_Of_AOAS"'|g' -i /$Generate_Mesh_File_Path \
                                                            /$Salome_Converter_File_Path /$Mesh_Refinement_File_Path



sed 's|'"Initial_AOA = TBD"'|'"Initial_AOA = $Initial_AOA"'|g' -i /$Generate_Mesh_File_Path \
                                                            /$Salome_Converter_File_Path /$Mesh_Refinement_File_Path

sed 's|'"AOA_Increment = TBD"'|'"AOA_Increment = $AOA_Increment"'|g' -i /$Generate_Mesh_File_Path \
                                                            /$Salome_Converter_File_Path /$Mesh_Refinement_File_Path



sed 's|'"Initial_Airfoil_MeshSize = TBD"'|'"Initial_Airfoil_MeshSize = $Initial_Airfoil_MeshSize"'|g' -i /$Generate_Mesh_File_Path \
                                                            /$Salome_Converter_File_Path /$Mesh_Refinement_File_Path

sed 's|'"Airfoil_Refinement_Factor = TBD"'|'"Airfoil_Refinement_Factor = $Airfoil_Refinement_Factor"'|g' -i /$Generate_Mesh_File_Path \
                                                            /$Salome_Converter_File_Path /$Mesh_Refinement_File_Path



sed 's|'"Initial_FarField_MeshSize = TBD"'|'"Initial_FarField_MeshSize = $Initial_FarField_MeshSize"'|g' -i /$Generate_Mesh_File_Path \
                                                            /$Salome_Converter_File_Path /$Mesh_Refinement_File_Path

sed 's|'"FarField_Refinement_Factor = TBD"'|'"FarField_Refinement_Factor = $FarField_Refinement_Factor"'|g' -i /$Generate_Mesh_File_Path \
                                                            /$Salome_Converter_File_Path /$Mesh_Refinement_File_Path