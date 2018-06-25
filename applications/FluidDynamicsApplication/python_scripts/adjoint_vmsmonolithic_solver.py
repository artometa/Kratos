from __future__ import print_function, absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7
# Importing the Kratos Library
import KratosMultiphysics

# Check that applications were imported in the main script
KratosMultiphysics.CheckRegisteredApplications("AdjointFluidApplication")

# Import applications
import KratosMultiphysics.AdjointFluidApplication as KratosAdjoint

# Import base class file
from adjoint_fluid_solver import AdjointFluidSolver

def CreateSolver(main_model_part, custom_settings):
    return AdjointVMSMonolithicSolver(main_model_part, custom_settings)

class AdjointVMSMonolithicSolver(AdjointFluidSolver):

    def _ValidateSettings(self, settings):
        # default settings string in json format
        default_settings = KratosMultiphysics.Parameters("""
        {
            "solver_type" : "adjoint_vmsmonolithic_solver",
            "model_part_name": "AdjointFluidModelPart",
            "domain_size": 2,
            "scheme_settings" : {
                "scheme_type" : "bossak"
            },
            "response_function_settings" : {
                "response_type" : "drag"
            },
            "model_import_settings" : {
                "input_type"     : "mdpa",
                "input_filename" : "unknown_name"
            },
            "linear_solver_settings" : {
                "solver_type" : "AMGCL"
            },
            "volume_model_part_name" : "volume_model_part",
            "skin_parts"  : [""],
            "no_skin_parts"  : [""],
            "dynamic_tau" : 0.0,
            "oss_switch"  : 0,
            "echo_level"  : 0,
            "time_stepping"               : {
                "automatic_time_step" : false,
                "time_step"           : -0.1
        }
        }""")

        settings.ValidateAndAssignDefaults(default_settings)
        return settings

    def __init__(self, model, custom_settings):
        super(AdjointVMSMonolithicSolver,self).__init__(model,custom_settings)
        
        # There is only a single rank in OpenMP, we always print
        self._is_printing_rank = True

        self.element_name = "VMSAdjointElement"
        if self.settings["domain_size"].GetInt() == 2:
            self.condition_name = "LineCondition"
        elif self.settings["domain_size"].GetInt() == 3:
            self.condition_name = "SurfaceCondition"

        # construct the linear solver
        import linear_solver_factory
        self.linear_solver = linear_solver_factory.ConstructSolver(self.settings["linear_solver_settings"])

        KratosMultiphysics.Logger.PrintInfo(self.__class__.__name__, "Construction of AdjointVMSMonolithicSolver finished.")

    def AddVariables(self):

        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.VELOCITY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.ACCELERATION)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.PRESSURE)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.ADJOINT_VELOCITY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.ADJOINT_ACCELERATION)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.AUX_ADJOINT_ACCELERATION)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.ADJOINT_PRESSURE)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.VISCOSITY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.DENSITY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.BODY_FORCE)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.SHAPE_SENSITIVITY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.NORMAL_SENSITIVITY)

        KratosMultiphysics.Logger.PrintInfo(self.__class__.__name__, "Adjoint fluid solver variables added correctly.")

    def PrepareModelPart(self):
        self._set_physical_properties()
        super(AdjointVMSMonolithicSolver, self).PrepareModelPart()

    def Initialize(self):

        self.computing_model_part = self.GetComputingModelPart()

        domain_size = self.main_model_part.ProcessInfo[KratosMultiphysics.DOMAIN_SIZE]

        if self.settings["response_function_settings"]["response_type"].GetString() == "drag":
            if (domain_size == 2):
                self.response_function = KratosAdjoint.DragResponseFunction2D(self.main_model_part, self.settings["response_function_settings"])
            elif (domain_size == 3):
                self.response_function = KratosAdjoint.DragResponseFunction3D(self.main_model_part, self.settings["response_function_settings"])
            else:
                raise Exception("Invalid DOMAIN_SIZE: " + str(domain_size))
        else:
            raise Exception("invalid response_type: " + self.settings["response_function_settings"]["response_type"].GetString())

        if self.settings["scheme_settings"]["scheme_type"].GetString() == "bossak":
            self.time_scheme = KratosAdjoint.AdjointBossakScheme(self.settings["scheme_settings"], self.response_function)
        elif self.settings["scheme_settings"]["scheme_type"].GetString() == "steady":
            self.time_scheme = KratosAdjoint.AdjointSteadyVelocityPressureScheme(self.settings["scheme_settings"], self.response_function)
        else:
            raise Exception("invalid scheme_type: " + self.settings["scheme_settings"]["scheme_type"].GetString())

        builder_and_solver = KratosMultiphysics.ResidualBasedBlockBuilderAndSolver(self.linear_solver)

        self.solver = KratosMultiphysics.ResidualBasedLinearStrategy(self.main_model_part,
                                                                     self.time_scheme,
                                                                     self.linear_solver,
                                                                     builder_and_solver,
                                                                     False,
                                                                     False,
                                                                     False,
                                                                     False)

        (self.solver).SetEchoLevel(self.settings["echo_level"].GetInt())

        (self.solver).Initialize()

        (self.solver).Check()

        self.main_model_part.ProcessInfo.SetValue(KratosMultiphysics.DYNAMIC_TAU, self.settings["dynamic_tau"].GetDouble())
        self.main_model_part.ProcessInfo.SetValue(KratosMultiphysics.OSS_SWITCH, self.settings["oss_switch"].GetInt())

        KratosMultiphysics.Logger.PrintInfo(self.__class__.__name__, "Solver initialization finished.")

    def _set_physical_properties(self):
        # Transfer density and (kinematic) viscostity to the nodes
        for el in self.main_model_part.Elements:
            rho = el.Properties.GetValue(KratosMultiphysics.DENSITY)
            if rho <= 0.0:
                raise Exception("DENSITY set to {0} in Properties {1}, positive number expected.".format(rho,el.Properties.Id))
            dyn_viscosity = el.Properties.GetValue(KratosMultiphysics.DYNAMIC_VISCOSITY)
            if dyn_viscosity <= 0.0:
                raise Exception("DYNAMIC_VISCOSITY set to {0} in Properties {1}, positive number expected.".format(dyn_viscosity,el.Properties.Id))
            kin_viscosity = dyn_viscosity / rho
            break

        KratosMultiphysics.VariableUtils().SetScalarVar(KratosMultiphysics.DENSITY, rho, self.main_model_part.Nodes)
        KratosMultiphysics.VariableUtils().SetScalarVar(KratosMultiphysics.VISCOSITY, kin_viscosity, self.main_model_part.Nodes)        