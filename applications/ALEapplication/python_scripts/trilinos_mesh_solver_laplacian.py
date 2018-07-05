from __future__ import print_function, absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7

# Importing the Kratos Library
import KratosMultiphysics

# Check that applications were imported in the main script
KratosMultiphysics.CheckRegisteredApplications("ALEApplication", "TrilinosApplication")

# Import applications
import KratosMultiphysics.TrilinosApplication as TrilinosApplication

# Other imports
import trilinos_mesh_solver_base


def CreateSolver(mesh_model_part, custom_settings):
    return TrilinosMeshSolverComponentwise(mesh_model_part, custom_settings)


class TrilinosMeshSolverComponentwise(trilinos_mesh_solver_base.TrilinosMeshSolverBase):
    def __init__(self, mesh_model_part, custom_settings):
        super(TrilinosMeshSolverComponentwise, self).__init__(mesh_model_part, custom_settings)
        self.print_on_rank_zero("::[TrilinosMeshSolverComponentwise]:: Construction finished")

    #### Private functions ####

    def _create_mesh_motion_solver(self):
        linear_solver = self.get_linear_solver()
        time_order = self.settings["time_order"].GetInt()
        reform_dofs_each_step = self.settings["reform_dofs_each_step"].GetBool()
        compute_reactions = self.settings["compute_reactions"].GetBool()
        echo_level = self.settings["echo_level"].GetInt()
        communicator = self.get_communicator()
        solver = TrilinosApplication.TrilinosLaplacianMeshMovingStrategy(
            communicator,
            self.mesh_model_part,
            linear_solver,
            time_order,
            reform_dofs_each_step,
            compute_reactions,
            echo_level)
        return solver