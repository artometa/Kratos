//
//   Project Name:        Kratos       
//   Last Modified by:    $Author:  $
//   Date:                $Date:  $
//   Revision:            $Revision: 1.3 $
//

// Project includes
#include "DEM_application.h"
#include "includes/kratos_flags.h"
#include "containers/flags.h"
#include "geometries/point_3d.h"
#include "geometries/line_3d_2.h"
#include "geometries/quadrilateral_3d_4.h"
#include "geometries/triangle_3d_3.h"
#include "geometries/sphere_3d_1.h"
#include "utilities/quaternion.h"
#include "custom_utilities/cluster_information.h"

#include "custom_constitutive/DEM_Dempack_CL.h"
#include "custom_constitutive/DEM_Dempack_2D_CL.h"
#include "custom_constitutive/DEM_Dempack_torque_CL.h"
#include "custom_constitutive/DEM_Dempack_dev_CL.h"
#include "custom_constitutive/dem_kdem_2d_cl.h"
#include "custom_constitutive/dem_kdem_fabric_2d_cl.h"
#include "custom_constitutive/DEM_D_Linear_viscous_Coulomb_CL.h"
#include "custom_constitutive/DEM_D_Linear_viscous_Coulomb_2D_CL.h"
#include "custom_constitutive/DEM_D_Hertz_viscous_Coulomb_CL.h"
#include "custom_constitutive/DEM_D_Hertz_viscous_Coulomb_2D_CL.h"
#include "custom_constitutive/DEM_D_JKR_cohesive_law.h"
#include "custom_constitutive/DEM_D_Bentonite_Colloid_CL.h"
#include "custom_constitutive/DEM_D_DMT_cohesive_law.h"
#include "custom_constitutive/dem_d_linear_custom_constants_cl.h"
#include "custom_constitutive/DEM_D_Conical_damage_CL.h"
#include "custom_constitutive/DEM_KDEM_fabric_CL.h"
#include "custom_constitutive/DEM_ExponentialHC_CL.h"

namespace Kratos
{
  KRATOS_CREATE_VARIABLE(WeakPointerVector< Element >, CONTINUUM_INI_NEIGHBOUR_ELEMENTS)
  KRATOS_CREATE_VARIABLE(WeakPointerVector< Element >, NODE_TO_NEIGH_ELEMENT_POINTER)
  
  //constitutive law
  KRATOS_CREATE_VARIABLE(std::string, DEM_DISCONTINUUM_CONSTITUTIVE_LAW_NAME)
  KRATOS_CREATE_VARIABLE(std::string, DEM_CONTINUUM_CONSTITUTIVE_LAW_NAME)
  KRATOS_CREATE_VARIABLE(DEMDiscontinuumConstitutiveLaw::Pointer, DEM_DISCONTINUUM_CONSTITUTIVE_LAW_POINTER)
  KRATOS_CREATE_VARIABLE(DEMContinuumConstitutiveLaw::Pointer, DEM_CONTINUUM_CONSTITUTIVE_LAW_POINTER)
          
  //Probability distribution
  KRATOS_CREATE_VARIABLE(std::string, PROBABILITY_DISTRIBUTION)        
  KRATOS_CREATE_VARIABLE(std::string, EXCENTRICITY_PROBABILITY_DISTRIBUTION)        

  // OPTIONS AND FLAGS  
  KRATOS_CREATE_VARIABLE(int, FORCE_INTEGRATION_GROUP)
  KRATOS_CREATE_VARIABLE(int, TOP)
  KRATOS_CREATE_VARIABLE(int, BOTTOM)
  KRATOS_CREATE_VARIABLE(int, BOUNDING_BOX_OPTION)
  KRATOS_CREATE_VARIABLE(int, ROTATION_OPTION)
  KRATOS_CREATE_VARIABLE(int, CRITICAL_TIME_OPTION)
  KRATOS_CREATE_VARIABLE(int, VIRTUAL_MASS_OPTION)
  KRATOS_CREATE_VARIABLE(int, SEARCH_CONTROL)
  KRATOS_CREATE_VARIABLE(double, COORDINATION_NUMBER)
  KRATOS_CREATE_VARIABLE(vector<int>, SEARCH_CONTROL_VECTOR)
  KRATOS_CREATE_VARIABLE(int, CLEAN_INDENT_OPTION)
  KRATOS_CREATE_VARIABLE(int, TRIHEDRON_OPTION)
  KRATOS_CREATE_VARIABLE(int, ROLLING_FRICTION_OPTION)
  KRATOS_CREATE_VARIABLE(int, POISSON_EFFECT_OPTION)          
  KRATOS_CREATE_VARIABLE(int, SHEAR_STRAIN_PARALLEL_TO_BOND_OPTION)
  KRATOS_CREATE_VARIABLE(int, NEIGH_INITIALIZED)
  KRATOS_CREATE_VARIABLE(int, TRIAXIAL_TEST_OPTION)
  KRATOS_CREATE_VARIABLE(int, FIX_VELOCITIES_FLAG)
  KRATOS_CREATE_VARIABLE(int, STRESS_STRAIN_OPTION)
  KRATOS_CREATE_VARIABLE(int, DUMMY_DEBUG_INT)
  KRATOS_CREATE_VARIABLE(int, PARTICLE_ID)
  KRATOS_CREATE_VARIABLE(bool, CONTAINS_CLUSTERS)
  KRATOS_CREATE_VARIABLE(bool, RANDOM_EULER_ANGLES)
  KRATOS_CREATE_VARIABLE(int, LOCAL_RESOLUTION_METHOD)
  KRATOS_CREATE_VARIABLE(int, COMPUTE_FEM_RESULTS_OPTION) 
  KRATOS_CREATE_VARIABLE(int, BREAKABLE_CLUSTER) 
  KRATOS_CREATE_VARIABLE(ClusterInformation, CLUSTER_INFORMATION) 
  KRATOS_CREATE_VARIABLE(std::string, CLUSTER_FILE_NAME) 
          
  KRATOS_CREATE_VARIABLE(double, INITIAL_VELOCITY_X_VALUE)
  KRATOS_CREATE_VARIABLE(double, INITIAL_VELOCITY_Y_VALUE)
  KRATOS_CREATE_VARIABLE(double, INITIAL_VELOCITY_Z_VALUE)
  KRATOS_CREATE_VARIABLE(double, INITIAL_ANGULAR_VELOCITY_X_VALUE)
  KRATOS_CREATE_VARIABLE(double, INITIAL_ANGULAR_VELOCITY_Y_VALUE)
  KRATOS_CREATE_VARIABLE(double, INITIAL_ANGULAR_VELOCITY_Z_VALUE)

  // *************** Continuum only BEGIN *************
  KRATOS_CREATE_VARIABLE(bool, DELTA_OPTION)
  KRATOS_CREATE_VARIABLE(int, CASE_OPTION)
  KRATOS_CREATE_VARIABLE(double, SKIN_SPHERE)
  KRATOS_CREATE_VARIABLE(int, PROPERTIES_ID)
  KRATOS_CREATE_VARIABLE(int, CONTACT_MESH_OPTION)
  //KRATOS_CREATE_VARIABLE(int, FAILURE_CRITERION_OPTION)
  KRATOS_CREATE_VARIABLE(int, CONCRETE_TEST_OPTION)
  KRATOS_CREATE_VARIABLE(int, COHESIVE_GROUP)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_TENSION)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_COHESION)
  KRATOS_CREATE_VARIABLE(int, IF_BOUNDARY_ELEMENT)
  KRATOS_CREATE_VARIABLE(Vector, IF_BOUNDARY_FACE)
  KRATOS_CREATE_VARIABLE(vector<int>, PARTICLE_CONTACT_FAILURE_ID)
    
  // *************** Continuum only END ***************

  // MATERIAL PARAMETERS
  KRATOS_CREATE_VARIABLE(double, NODAL_MASS_COEFF)
  KRATOS_CREATE_VARIABLE(double, DEM_MAGIC_FACTOR)
  KRATOS_CREATE_VARIABLE(double, DEM_MAGIC_FACTOR_POISSON)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_MOMENT_OF_INERTIA)
  KRATOS_CREATE_VARIABLE(double, ROLLING_FRICTION)
  KRATOS_CREATE_VARIABLE(double, HISTORICAL_MIN_K)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_INERTIA)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_DENSITY)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_FRICTION)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_STATIC_FRICTION_COEF)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_DYNAMIC_FRICTION_COEF)
  KRATOS_CREATE_VARIABLE(double, COEFFICIENT_OF_RESTITUTION)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_ROTATION_DAMP_RATIO)
  KRATOS_CREATE_VARIABLE(double, DAMPING_GAMMA)  
  KRATOS_CREATE_VARIABLE(double, K_NORMAL)
  KRATOS_CREATE_VARIABLE(double, K_TANGENTIAL)
  KRATOS_CREATE_VARIABLE(double, CONTACT_RADIUS)
  KRATOS_CREATE_VARIABLE(double, MAX_STRESS)
  KRATOS_CREATE_VARIABLE(double, ALPHA)
  KRATOS_CREATE_VARIABLE(double, GAMMA)
  KRATOS_CREATE_VARIABLE(double, ALPHA_FUNCTION)
  KRATOS_CREATE_VARIABLE(double, EXCENTRICITY)
  KRATOS_CREATE_VARIABLE(double, EXCENTRICITY_STANDARD_DEVIATION)
  KRATOS_CREATE_VARIABLE(double, FABRIC_COEFFICIENT)
  KRATOS_CREATE_VARIABLE(double, POISSON_VALUE)
  KRATOS_CREATE_VARIABLE(double, KT_FACTOR)
          

  // *************** Nano-particle only BEGIN *************
  KRATOS_CREATE_VARIABLE(double, CATION_CONCENTRATION)
  // *************** Nano-particle only END *************

  // *************** Continuum only BEGIN *************
  KRATOS_CREATE_VARIABLE(double, SLOPE_FRACTION_N1)
  KRATOS_CREATE_VARIABLE(double, SLOPE_FRACTION_N2)
  KRATOS_CREATE_VARIABLE(double, SLOPE_FRACTION_N3)
  KRATOS_CREATE_VARIABLE(double, SLOPE_LIMIT_COEFF_C1)
  KRATOS_CREATE_VARIABLE(double, SLOPE_LIMIT_COEFF_C2)
  KRATOS_CREATE_VARIABLE(double, SLOPE_LIMIT_COEFF_C3)
  KRATOS_CREATE_VARIABLE(double, YOUNG_MODULUS_PLASTIC)
  KRATOS_CREATE_VARIABLE(double, PLASTIC_YIELD_STRESS)
  KRATOS_CREATE_VARIABLE(double, DAMAGE_FACTOR)
  KRATOS_CREATE_VARIABLE(double, SHEAR_ENERGY_COEF)        
  KRATOS_CREATE_VARIABLE(double, DONZE_G1)
  KRATOS_CREATE_VARIABLE(double, DONZE_G2)
  KRATOS_CREATE_VARIABLE(double, DONZE_G3)
  KRATOS_CREATE_VARIABLE(double, DONZE_MAX_DEF)
  KRATOS_CREATE_VARIABLE(double, CONTACT_FAILURE)
  KRATOS_CREATE_VARIABLE(double, CONTACT_SIGMA)
  KRATOS_CREATE_VARIABLE(double, CONTACT_TAU)
  KRATOS_CREATE_VARIABLE(double, FAILURE_CRITERION_STATE)
  KRATOS_CREATE_VARIABLE(double, UNIDIMENSIONAL_DAMAGE)
  KRATOS_CREATE_VARIABLE(double, CONTACT_ORIENTATION)
  KRATOS_CREATE_VARIABLE(double, CONTACT_SIGMA_MIN)
  KRATOS_CREATE_VARIABLE(double, CONTACT_TAU_ZERO)
  KRATOS_CREATE_VARIABLE(double, CONTACT_INTERNAL_FRICC)

  // *************** Continuum only END *************

  // GEOMETRIC PARAMETERS
  // *************** Continuum only BEGIN *************
  KRATOS_CREATE_VARIABLE(double, LOCAL_CONTACT_AREA_HIGH)
  KRATOS_CREATE_VARIABLE(double, LOCAL_CONTACT_AREA_LOW)
  KRATOS_CREATE_VARIABLE(double, MEAN_CONTACT_AREA)
  KRATOS_CREATE_VARIABLE(double, REPRESENTATIVE_VOLUME)
  KRATOS_CREATE_VARIABLE(boost::numeric::ublas::vector<int>, NEIGHBOUR_IDS)
  KRATOS_CREATE_VARIABLE(boost::numeric::ublas::vector<double>, NEIGHBOURS_CONTACT_AREAS)
  // *************** Continuum only END ***************      

  //INLET PARAMETERS
  KRATOS_CREATE_VARIABLE(double, INLET_START_TIME)
  KRATOS_CREATE_VARIABLE(double, INLET_STOP_TIME)
  KRATOS_CREATE_VARIABLE(double, INLET_NUMBER_OF_PARTICLES)
  KRATOS_CREATE_VARIABLE(double, STANDARD_DEVIATION)
  KRATOS_CREATE_VARIABLE(double, MAX_RAND_DEVIATION_ANGLE)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(LINEAR_VELOCITY)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(INLET_INITIAL_VELOCITY)

  // KINEMATICS
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_ROTATION_ANGLE)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(EULER_ANGLES)
  KRATOS_CREATE_VARIABLE(Quaternion<double>, ORIENTATION)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(DELTA_DISPLACEMENT)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(DELTA_ROTA_DISPLACEMENT)
  KRATOS_CREATE_VARIABLE(double, VELOCITY_START_TIME)
  KRATOS_CREATE_VARIABLE(double, VELOCITY_STOP_TIME)
  KRATOS_CREATE_VARIABLE(double, ANGULAR_VELOCITY_START_TIME)
  KRATOS_CREATE_VARIABLE(double, ANGULAR_VELOCITY_STOP_TIME)
  KRATOS_CREATE_VARIABLE(int, RIGID_BODY_MOTION)

  // FORCE AND MOMENTUM
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_MOMENT)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(ROLLING_RESISTANCE_MOMENT)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(MAX_ROTA_MOMENT)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(ELASTIC_FORCES)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(CONTACT_FORCES)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(RIGID_ELEMENT_FORCE)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(TANGENTIAL_ELASTIC_FORCES)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(FORCE_REACTION)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(MOMENT_REACTION)        
  KRATOS_CREATE_VARIABLE(double, DEM_PRESSURE)
  KRATOS_CREATE_VARIABLE(double, DEM_NODAL_AREA)
   
  // ENERGY
  KRATOS_CREATE_VARIABLE(double, PARTICLE_ELASTIC_ENERGY)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_TRANSLATIONAL_KINEMATIC_ENERGY)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_ROTATIONAL_KINEMATIC_ENERGY)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_GRAVITATIONAL_ENERGY)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_INELASTIC_VISCODAMPING_ENERGY)
  KRATOS_CREATE_VARIABLE(double, PARTICLE_INELASTIC_FRICTIONAL_ENERGY)
  KRATOS_CREATE_VARIABLE(int, COMPUTE_ENERGY_OPTION)

  // *************** Continuum only BEGIN *************
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(INITIAL_ROTA_MOMENT)
  KRATOS_CREATE_VARIABLE(Vector, PARTICLE_BLOCK_CONTACT_FORCE)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(EXTERNAL_APPLIED_FORCE)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(EXTERNAL_APPLIED_MOMENT)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(LOCAL_CONTACT_FORCE)
  KRATOS_CREATE_VARIABLE(VectorArray3Double, PARTICLE_CONTACT_FORCES )

  // CONCRETE TEST
  KRATOS_CREATE_VARIABLE(double, FIXED_VEL_TOP)
  KRATOS_CREATE_VARIABLE(double, FIXED_VEL_BOT)
  KRATOS_CREATE_VARIABLE(double, AREA_VERTICAL_TAPA)
  KRATOS_CREATE_VARIABLE(double, AREA_VERTICAL_CENTRE)

  // TENSION
  KRATOS_CREATE_VARIABLE(double, DEM_STRESS_XX)
  KRATOS_CREATE_VARIABLE(double, DEM_STRESS_XY)
  KRATOS_CREATE_VARIABLE(double, DEM_STRESS_XZ)
  KRATOS_CREATE_VARIABLE(double, DEM_STRESS_YX)
  KRATOS_CREATE_VARIABLE(double, DEM_STRESS_YY)
  KRATOS_CREATE_VARIABLE(double, DEM_STRESS_YZ)
  KRATOS_CREATE_VARIABLE(double, DEM_STRESS_ZX)
  KRATOS_CREATE_VARIABLE(double, DEM_STRESS_ZY)
  KRATOS_CREATE_VARIABLE(double, DEM_STRESS_ZZ)

  // APPLIED LOADS

  KRATOS_CREATE_VARIABLE(double, BLAST_RADIUS)
  KRATOS_CREATE_VARIABLE(int   , BLAST_CURVE)
  KRATOS_CREATE_VARIABLE(double, BLAST_PRESSURE_MAX)
  KRATOS_CREATE_VARIABLE(double, BLAST_TIME_PRESSURE_MAX)
  KRATOS_CREATE_VARIABLE(double, BLAST_SHAPE_FACTOR)
  KRATOS_CREATE_VARIABLE(double, BLAST_TIME_DELAY)
  KRATOS_CREATE_VARIABLE(int   , BLAST_BOREHOLE)
  KRATOS_CREATE_VARIABLE(int   , BLAST_NPOINTS)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_1)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_2)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_3)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_4)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_5)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_6)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_7)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_8)
  // *************** Continuum only END *************

  // Possible future blocks (no FEM) interaction
  KRATOS_CREATE_VARIABLE(Vector, PARTICLE_BLOCK_CONTACT_FAILURE_ID)
  KRATOS_CREATE_VARIABLE(Vector, PARTICLE_BLOCK_IF_INITIAL_CONTACT)
  KRATOS_CREATE_VARIABLE(WeakPointerVector<Element >, NEIGHBOUR_PARTICLE_BLOCK_ELEMENTS)
  KRATOS_CREATE_VARIABLE(WeakPointerVector<Condition >,     NEIGHBOUR_RIGID_FACES)
  KRATOS_CREATE_VARIABLE(Vector,    NEIGHBOUR_RIGID_FACES_PRAM)
  KRATOS_CREATE_VARIABLE(WeakPointerVector<Element >, NEIGHBOUR_PARTICLE_OF_RIGID_FACE)
  KRATOS_CREATE_VARIABLE(Vector,   NEIGHBOUR_RIGID_FACES_ELASTIC_CONTACT_FORCE)
  KRATOS_CREATE_VARIABLE(Vector,   NEIGHBOUR_RIGID_FACES_TOTAL_CONTACT_FORCE)

  // DUMMY INT AND DOUBLE VARIABLES
  KRATOS_CREATE_VARIABLE(int, DUMMY_SWITCH)
  KRATOS_CREATE_VARIABLE(double, TOTAL_CONTACT_DISTANCES)
  
  // *************** Thermal only BEGIN *************
  KRATOS_CREATE_VARIABLE(double, HEATFLUX)
  KRATOS_CREATE_VARIABLE(double, THERMAL_CONDUCTIVITY)
  // *************** Thermal only END ***************  

  // EXPORTS
  KRATOS_CREATE_VARIABLE(double, EXPORT_PARTICLE_FAILURE_ID)
  KRATOS_CREATE_VARIABLE(double, EXPORT_ID)
  KRATOS_CREATE_VARIABLE(int,    PRINT_EXPORT_ID)
  
  // For DEM_FEM element
  KRATOS_CREATE_VARIABLE(double, LOCAL_DAMP_RATIO)        
  // For DEM_FEM condition
  // KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( FORCE_RESIDUAL )
  // KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( EXTERNAL_FORCE )

  // DUMMY VARIABLES FOR CALCULATE
  KRATOS_CREATE_VARIABLE(double, CALCULATE_COMPUTE_NEW_NEIGHBOURS_HISTORICAL_DATA)
  KRATOS_CREATE_VARIABLE(double, CALCULATE_COMPUTE_NEW_RIGID_FACE_NEIGHBOURS_HISTORICAL_DATA)
  KRATOS_CREATE_VARIABLE(double, CALCULATE_SET_INITIAL_DEM_CONTACTS)
  KRATOS_CREATE_VARIABLE(double, CALCULATE_SET_INITIAL_FEM_CONTACTS)

  // Cfeng,131013,RigidFace Movement
  KRATOS_CREATE_VARIABLE(double, RIGID_FACE_ROTA_SPEED)
  KRATOS_CREATE_VARIABLE(double, RIGID_FACE_AXIAL_SPEED)
  KRATOS_CREATE_VARIABLE(int,    RIGID_FACE_PROP_ID)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(RIGID_FACE_ROTA_ORIGIN_COORD)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(RIGID_FACE_ROTA_AXIAL_DIR)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(RIGID_FACE_ROTA_GLOBAL_VELOCITY)
  KRATOS_CREATE_VARIABLE(double, RIGID_FACE_BEGIN_TIME)
  KRATOS_CREATE_VARIABLE(double, RIGID_FACE_END_TIME)
  KRATOS_CREATE_VARIABLE(int,    RIGID_FACE_FLAG)
  KRATOS_CREATE_VARIABLE(Vector, RIGID_FACE_COMPUTE_MOVEMENT)
  
  //SLS DEM-FEM
  KRATOS_CREATE_VARIABLE(double, WALL_FRICTION)
  KRATOS_CREATE_VARIABLE(double, SHEAR_STRESS)
  KRATOS_CREATE_VARIABLE(double, NON_DIMENSIONAL_VOLUME_WEAR)
  KRATOS_CREATE_VARIABLE(double, IMPACT_WEAR)
  KRATOS_CREATE_VARIABLE(double, SEVERITY_OF_WEAR)
  KRATOS_CREATE_VARIABLE(double, BRINELL_HARDNESS)
  KRATOS_CREATE_VARIABLE(bool  , COMPUTE_WEAR)        
  KRATOS_CREATE_VARIABLE(double, IMPACT_WEAR_SEVERITY)
  KRATOS_CREATE_VARIABLE(double, WALL_COHESION)
  
  //DEM_CLUSTERS
  KRATOS_CREATE_VARIABLE(double, CLUSTER_VOLUME)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(PRINCIPAL_MOMENTS_OF_INERTIA)
  KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(LOCAL_ANGULAR_VELOCITY)
  KRATOS_CREATE_VARIABLE(double, CHARACTERISTIC_LENGTH)
  KRATOS_CREATE_VARIABLE(double, SPRAYED_MATERIAL)
  
  //BOUNDING BOX
  KRATOS_CREATE_VARIABLE(double, BOUNDING_BOX_START_TIME)
  KRATOS_CREATE_VARIABLE(double, BOUNDING_BOX_STOP_TIME)

  //FLAGS
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, HAS_ROTATION, 0);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, IS_SINTERING, 1);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, HAS_ROLLING_FRICTION, 2);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, HAS_CRITICAL_TIME, 4);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, FIXED_VEL_X, 5);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, FIXED_VEL_Y, 6);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, FIXED_VEL_Z, 7);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, FIXED_ANG_VEL_X, 8);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, FIXED_ANG_VEL_Y, 9);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, FIXED_ANG_VEL_Z, 10);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, BELONGS_TO_A_CLUSTER, 11);
  KRATOS_CREATE_LOCAL_FLAG(DEMFlags, HAS_STRESS_TENSOR, 12);

  //ELEMENTS
    
  KratosDEMApplication::KratosDEMApplication():
    mCylinderParticle2D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mCylinderContinuumParticle2D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mSphericParticle3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mNanoParticle3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mSphericContinuumParticle3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mThermalSphericContinuumParticle3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mThermalSphericParticle3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mSinteringSphericContinuumParticle3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mParticleContactElement(0, Element::GeometryType::Pointer(new Line3D2<Node<3> >(Element::GeometryType::PointsArrayType(2)))),
    mSolidFace3D3N(0, Element::GeometryType::Pointer(new Triangle3D3 <Node<3> >(Element::GeometryType::PointsArrayType(3)))),
    mSolidFace3D4N(0, Element::GeometryType::Pointer(new Quadrilateral3D4 <Node<3> >(Element::GeometryType::PointsArrayType(4)))),
    mRigidFace3D3N(0, Element::GeometryType::Pointer(new Triangle3D3 <Node<3> >(Element::GeometryType::PointsArrayType(3)))),
    mRigidFace3D4N(0, Element::GeometryType::Pointer(new Quadrilateral3D4 <Node<3> >(Element::GeometryType::PointsArrayType(4)))),
    mRigidEdge3D2N(0, Element::GeometryType::Pointer(new Line3D2 <Node<3> >(Element::GeometryType::PointsArrayType(2)))),
    mCluster3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mCubeCluster3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mPillCluster3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mEllipsoidCluster3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mCuboidCluster3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mCapsuleCluster3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),        
    mSingleSphereCluster3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mBeadCluster3D(0, Element::GeometryType::Pointer(new Sphere3D1<Node<3> >(Element::GeometryType::PointsArrayType(1)))),
    mMapCon3D3N(0, Element::GeometryType::Pointer(new Triangle3D3 <Node<3> >(Element::GeometryType::PointsArrayType(3))))
  {}
    
    void KratosDEMApplication::Register() {
        
    // Calling base class register to register Kratos components

    KratosApplication::Register();
    
    std::cout << std::endl;
    std::cout << "     KRATOS |  _ \\| ____|  \\/  |  _ \\ __ _  ___| | __      "  << std::endl;
    std::cout << "            | | | |  _| | |\\/| | |_) / _` |/ __| |/ /      "    << std::endl;
    std::cout << "            | |_| | |___| |  | |  __/ (_| | (__|   <       "     << std::endl;
    std::cout << "            |____/|_____|_|  |_|_|   \\__,_|\\___|_|\\_\\      " << std::endl << std::endl;
    std::cout << "Importing DEMApplication... ";
   
#ifdef KRATOS_BUILD_TYPE
#define ____CONVERT_INNER_VALUE_TO_STRING(S) ____CONVERT_TO_STRING(S)
#define ____CONVERT_TO_STRING(S) #S
    std::cout << "( compiled in mode \""<<____CONVERT_INNER_VALUE_TO_STRING(KRATOS_BUILD_TYPE)<<"\" )";
#undef ____CONVERT_INNER_VALUE_TO_STRING
#undef ____CONVERT_TO_STRING
#endif

    KRATOS_REGISTER_VARIABLE(CONTINUUM_INI_NEIGHBOUR_ELEMENTS)
    KRATOS_REGISTER_VARIABLE(NODE_TO_NEIGH_ELEMENT_POINTER)
  
    //constitutive law
    KRATOS_REGISTER_VARIABLE(DEM_DISCONTINUUM_CONSTITUTIVE_LAW_NAME)
    KRATOS_REGISTER_VARIABLE(DEM_CONTINUUM_CONSTITUTIVE_LAW_NAME)
    KRATOS_REGISTER_VARIABLE(DEM_DISCONTINUUM_CONSTITUTIVE_LAW_POINTER)
    KRATOS_REGISTER_VARIABLE(DEM_CONTINUUM_CONSTITUTIVE_LAW_POINTER)
           
    KRATOS_REGISTER_VARIABLE(PROBABILITY_DISTRIBUTION)        
    KRATOS_REGISTER_VARIABLE(EXCENTRICITY_PROBABILITY_DISTRIBUTION)        

    // OPTIONS AND FLAGS
    KRATOS_REGISTER_VARIABLE(TOP)
    KRATOS_REGISTER_VARIABLE(BOTTOM)
    KRATOS_REGISTER_VARIABLE(FORCE_INTEGRATION_GROUP)
    KRATOS_REGISTER_VARIABLE(SHEAR_STRAIN_PARALLEL_TO_BOND_OPTION)
    KRATOS_REGISTER_VARIABLE(POISSON_EFFECT_OPTION)
    KRATOS_REGISTER_VARIABLE(ROLLING_FRICTION_OPTION)
    KRATOS_REGISTER_VARIABLE(BOUNDING_BOX_OPTION)
    KRATOS_REGISTER_VARIABLE(ROTATION_OPTION)
    KRATOS_REGISTER_VARIABLE(CRITICAL_TIME_OPTION)
    KRATOS_REGISTER_VARIABLE(VIRTUAL_MASS_OPTION)
    KRATOS_REGISTER_VARIABLE(SEARCH_CONTROL) 
    KRATOS_REGISTER_VARIABLE(COORDINATION_NUMBER)
    KRATOS_REGISTER_VARIABLE(SEARCH_CONTROL_VECTOR)
    KRATOS_REGISTER_VARIABLE(CLEAN_INDENT_OPTION)
    KRATOS_REGISTER_VARIABLE(TRIHEDRON_OPTION)
    KRATOS_REGISTER_VARIABLE(NEIGH_INITIALIZED)
    KRATOS_REGISTER_VARIABLE(TRIAXIAL_TEST_OPTION)
    KRATOS_REGISTER_VARIABLE(FIX_VELOCITIES_FLAG)
    KRATOS_REGISTER_VARIABLE(STRESS_STRAIN_OPTION)
    KRATOS_REGISTER_VARIABLE(PARTICLE_ID)
    KRATOS_REGISTER_VARIABLE(CONTAINS_CLUSTERS)
    KRATOS_REGISTER_VARIABLE(RANDOM_EULER_ANGLES)
    KRATOS_REGISTER_VARIABLE(LOCAL_RESOLUTION_METHOD)
    KRATOS_REGISTER_VARIABLE(COMPUTE_FEM_RESULTS_OPTION) 
    KRATOS_REGISTER_VARIABLE(BREAKABLE_CLUSTER)
    KRATOS_REGISTER_VARIABLE(CLUSTER_INFORMATION)
    KRATOS_REGISTER_VARIABLE(CLUSTER_FILE_NAME)
            
    KRATOS_REGISTER_VARIABLE(INITIAL_VELOCITY_X_VALUE)
    KRATOS_REGISTER_VARIABLE(INITIAL_VELOCITY_Y_VALUE)
    KRATOS_REGISTER_VARIABLE(INITIAL_VELOCITY_Z_VALUE)
    KRATOS_REGISTER_VARIABLE(INITIAL_ANGULAR_VELOCITY_X_VALUE)
    KRATOS_REGISTER_VARIABLE(INITIAL_ANGULAR_VELOCITY_Y_VALUE)
    KRATOS_REGISTER_VARIABLE(INITIAL_ANGULAR_VELOCITY_Z_VALUE)
    
    // *************** Continuum only BEGIN *************
    KRATOS_REGISTER_VARIABLE(DELTA_OPTION)
    KRATOS_REGISTER_VARIABLE(CASE_OPTION)
    KRATOS_REGISTER_VARIABLE(SKIN_SPHERE)
    KRATOS_REGISTER_VARIABLE(PROPERTIES_ID)
    KRATOS_REGISTER_VARIABLE(CONTACT_MESH_OPTION)
    //KRATOS_REGISTER_VARIABLE(FAILURE_CRITERION_OPTION)
    KRATOS_REGISTER_VARIABLE(CONCRETE_TEST_OPTION)
    KRATOS_REGISTER_VARIABLE(COHESIVE_GROUP)
    KRATOS_REGISTER_VARIABLE(PARTICLE_TENSION)
    KRATOS_REGISTER_VARIABLE(PARTICLE_COHESION)
    KRATOS_REGISTER_VARIABLE(IF_BOUNDARY_ELEMENT)
    KRATOS_REGISTER_VARIABLE(IF_BOUNDARY_FACE)
    KRATOS_REGISTER_VARIABLE(PARTICLE_CONTACT_FAILURE_ID)
    KRATOS_REGISTER_VARIABLE(EXPORT_PARTICLE_FAILURE_ID)
    // *************** Continuum only END ***************

    // MATERIAL PARAMETERS

    KRATOS_REGISTER_VARIABLE(NODAL_MASS_COEFF)
    KRATOS_REGISTER_VARIABLE(PARTICLE_MOMENT_OF_INERTIA)
    KRATOS_REGISTER_VARIABLE(ROLLING_FRICTION)
    KRATOS_REGISTER_VARIABLE(HISTORICAL_MIN_K)
    KRATOS_REGISTER_VARIABLE(PARTICLE_INERTIA)
    KRATOS_REGISTER_VARIABLE(PARTICLE_DENSITY)
    KRATOS_REGISTER_VARIABLE(PARTICLE_FRICTION)
    KRATOS_REGISTER_VARIABLE(PARTICLE_STATIC_FRICTION_COEF)
    KRATOS_REGISTER_VARIABLE(PARTICLE_DYNAMIC_FRICTION_COEF)
    KRATOS_REGISTER_VARIABLE(COEFFICIENT_OF_RESTITUTION)
    KRATOS_REGISTER_VARIABLE(PARTICLE_ROTATION_DAMP_RATIO)
    KRATOS_REGISTER_VARIABLE(DAMPING_GAMMA)
    KRATOS_REGISTER_VARIABLE(K_NORMAL)
    KRATOS_REGISTER_VARIABLE(K_TANGENTIAL)
    KRATOS_REGISTER_VARIABLE(CONTACT_RADIUS)
    KRATOS_REGISTER_VARIABLE(MAX_STRESS)
    KRATOS_REGISTER_VARIABLE(ALPHA)
    KRATOS_REGISTER_VARIABLE(ALPHA_FUNCTION)
    KRATOS_REGISTER_VARIABLE(GAMMA)
    KRATOS_REGISTER_VARIABLE(EXCENTRICITY)
    KRATOS_REGISTER_VARIABLE(EXCENTRICITY_STANDARD_DEVIATION)
    KRATOS_REGISTER_VARIABLE(FABRIC_COEFFICIENT)
    KRATOS_REGISTER_VARIABLE(POISSON_VALUE)
    KRATOS_REGISTER_VARIABLE(KT_FACTOR)

    // *************** Nano-particle only BEGIN *************
    KRATOS_REGISTER_VARIABLE(CATION_CONCENTRATION)
    // *************** Nano-particle only END *************

    // *************** Continuum only BEGIN *************
    KRATOS_REGISTER_VARIABLE(SLOPE_FRACTION_N1)
    KRATOS_REGISTER_VARIABLE(SLOPE_FRACTION_N2)
    KRATOS_REGISTER_VARIABLE(SLOPE_FRACTION_N3)
    KRATOS_REGISTER_VARIABLE(SLOPE_LIMIT_COEFF_C1)
    KRATOS_REGISTER_VARIABLE(SLOPE_LIMIT_COEFF_C2)
    KRATOS_REGISTER_VARIABLE(SLOPE_LIMIT_COEFF_C3)
    KRATOS_REGISTER_VARIABLE(YOUNG_MODULUS_PLASTIC)
    KRATOS_REGISTER_VARIABLE(PLASTIC_YIELD_STRESS)
    KRATOS_REGISTER_VARIABLE(DAMAGE_FACTOR)
    KRATOS_REGISTER_VARIABLE(SHEAR_ENERGY_COEF)          
    KRATOS_REGISTER_VARIABLE(DONZE_G1)
    KRATOS_REGISTER_VARIABLE(DONZE_G2)
    KRATOS_REGISTER_VARIABLE(DONZE_G3)
    KRATOS_REGISTER_VARIABLE(DONZE_MAX_DEF)
    KRATOS_REGISTER_VARIABLE(CONTACT_FAILURE)
    KRATOS_REGISTER_VARIABLE(CONTACT_ORIENTATION)
    KRATOS_REGISTER_VARIABLE(CONTACT_SIGMA)
    KRATOS_REGISTER_VARIABLE(CONTACT_TAU)
    KRATOS_REGISTER_VARIABLE(FAILURE_CRITERION_STATE)
    KRATOS_REGISTER_VARIABLE(UNIDIMENSIONAL_DAMAGE)
    KRATOS_REGISTER_VARIABLE(CONTACT_SIGMA_MIN)
    KRATOS_REGISTER_VARIABLE(CONTACT_TAU_ZERO)
    KRATOS_REGISTER_VARIABLE(CONTACT_INTERNAL_FRICC)
    // *************** Continuum only END *************

    // GEOMETRIC PARAMETERS

    // *************** Continuum only BEGIN *************
    KRATOS_REGISTER_VARIABLE(LOCAL_CONTACT_AREA_HIGH)
    KRATOS_REGISTER_VARIABLE(LOCAL_CONTACT_AREA_LOW)
    KRATOS_REGISTER_VARIABLE(MEAN_CONTACT_AREA)
    KRATOS_REGISTER_VARIABLE(REPRESENTATIVE_VOLUME)
    KRATOS_REGISTER_VARIABLE(NEIGHBOUR_IDS)
    KRATOS_REGISTER_VARIABLE(NEIGHBOURS_CONTACT_AREAS)
    // *************** Continuum only END ***************
            
    // INLET PARAMETERS    
    KRATOS_REGISTER_VARIABLE(INLET_START_TIME)    
    KRATOS_REGISTER_VARIABLE(INLET_STOP_TIME)
    KRATOS_REGISTER_VARIABLE(INLET_NUMBER_OF_PARTICLES)
    KRATOS_REGISTER_VARIABLE(STANDARD_DEVIATION)   
    KRATOS_REGISTER_VARIABLE(MAX_RAND_DEVIATION_ANGLE)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(LINEAR_VELOCITY)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(INLET_INITIAL_VELOCITY)
 
    // KINEMATICS
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_ROTATION_ANGLE)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(EULER_ANGLES)
    KRATOS_REGISTER_VARIABLE(ORIENTATION)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(DELTA_DISPLACEMENT)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(DELTA_ROTA_DISPLACEMENT)
    KRATOS_REGISTER_VARIABLE(VELOCITY_START_TIME)
    KRATOS_REGISTER_VARIABLE(VELOCITY_STOP_TIME)
    KRATOS_REGISTER_VARIABLE(ANGULAR_VELOCITY_START_TIME)
    KRATOS_REGISTER_VARIABLE(ANGULAR_VELOCITY_STOP_TIME)
    KRATOS_REGISTER_VARIABLE(RIGID_BODY_MOTION)

    // FORCE AND MOMENTUM
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_MOMENT)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(ROLLING_RESISTANCE_MOMENT)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(MAX_ROTA_MOMENT)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(ELASTIC_FORCES)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(CONTACT_FORCES)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(RIGID_ELEMENT_FORCE)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(TANGENTIAL_ELASTIC_FORCES)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(FORCE_REACTION)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(MOMENT_REACTION)
    KRATOS_REGISTER_VARIABLE(DEM_PRESSURE)
    KRATOS_REGISTER_VARIABLE(DEM_NODAL_AREA)        

    // ENERGY
    KRATOS_REGISTER_VARIABLE(PARTICLE_ELASTIC_ENERGY)
    KRATOS_REGISTER_VARIABLE(PARTICLE_TRANSLATIONAL_KINEMATIC_ENERGY)
    KRATOS_REGISTER_VARIABLE(PARTICLE_ROTATIONAL_KINEMATIC_ENERGY)
    KRATOS_REGISTER_VARIABLE(PARTICLE_GRAVITATIONAL_ENERGY)
    KRATOS_REGISTER_VARIABLE(PARTICLE_INELASTIC_VISCODAMPING_ENERGY)
    KRATOS_REGISTER_VARIABLE(PARTICLE_INELASTIC_FRICTIONAL_ENERGY)
    KRATOS_REGISTER_VARIABLE(COMPUTE_ENERGY_OPTION)        

    // *************** Continuum only BEGIN *************
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(INITIAL_ROTA_MOMENT)
    KRATOS_REGISTER_VARIABLE(PARTICLE_BLOCK_CONTACT_FORCE)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(EXTERNAL_APPLIED_FORCE)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(EXTERNAL_APPLIED_MOMENT)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(LOCAL_CONTACT_FORCE)
    KRATOS_REGISTER_VARIABLE(PARTICLE_CONTACT_FORCES)

    // CONCRETE TEST
    KRATOS_REGISTER_VARIABLE(FIXED_VEL_TOP)
    KRATOS_REGISTER_VARIABLE(FIXED_VEL_BOT)
    KRATOS_REGISTER_VARIABLE(AREA_VERTICAL_TAPA)
    KRATOS_REGISTER_VARIABLE(AREA_VERTICAL_CENTRE)

    // TENSION
    KRATOS_REGISTER_VARIABLE(DEM_STRESS_XX)
    KRATOS_REGISTER_VARIABLE(DEM_STRESS_XY)
    KRATOS_REGISTER_VARIABLE(DEM_STRESS_XZ)
    KRATOS_REGISTER_VARIABLE(DEM_STRESS_YX)
    KRATOS_REGISTER_VARIABLE(DEM_STRESS_YY)
    KRATOS_REGISTER_VARIABLE(DEM_STRESS_YZ)
    KRATOS_REGISTER_VARIABLE(DEM_STRESS_ZX)
    KRATOS_REGISTER_VARIABLE(DEM_STRESS_ZY)
    KRATOS_REGISTER_VARIABLE(DEM_STRESS_ZZ)

    // APPLIED LOADS
    KRATOS_REGISTER_VARIABLE(BLAST_RADIUS)
    KRATOS_REGISTER_VARIABLE(BLAST_CURVE)
    KRATOS_REGISTER_VARIABLE(BLAST_PRESSURE_MAX)
    KRATOS_REGISTER_VARIABLE(BLAST_TIME_PRESSURE_MAX)
    KRATOS_REGISTER_VARIABLE(BLAST_SHAPE_FACTOR)
    KRATOS_REGISTER_VARIABLE(BLAST_TIME_DELAY)
    KRATOS_REGISTER_VARIABLE(BLAST_BOREHOLE)
    KRATOS_REGISTER_VARIABLE(BLAST_NPOINTS)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_1)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_2)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_3)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_4)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_5)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_6)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_7)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(BLAST_COORDINATES_8)
    // *************** Continuum only END *************
            
    // *************** Thermal only BEGIN *************
    KRATOS_REGISTER_VARIABLE(HEATFLUX)
    KRATOS_REGISTER_VARIABLE(THERMAL_CONDUCTIVITY)        
    // *************** Thermal only END ***************       

    // Possible future blocks (no FEM) interaction

    KRATOS_REGISTER_VARIABLE(PARTICLE_BLOCK_CONTACT_FAILURE_ID)
    KRATOS_REGISTER_VARIABLE(PARTICLE_BLOCK_IF_INITIAL_CONTACT)
    KRATOS_REGISTER_VARIABLE(NEIGHBOUR_PARTICLE_BLOCK_ELEMENTS)
    KRATOS_REGISTER_VARIABLE(NEIGHBOUR_RIGID_FACES)
    KRATOS_REGISTER_VARIABLE(NEIGHBOUR_RIGID_FACES_PRAM)
    KRATOS_REGISTER_VARIABLE(NEIGHBOUR_PARTICLE_OF_RIGID_FACE)	
    KRATOS_REGISTER_VARIABLE(NEIGHBOUR_RIGID_FACES_ELASTIC_CONTACT_FORCE)
    KRATOS_REGISTER_VARIABLE(NEIGHBOUR_RIGID_FACES_TOTAL_CONTACT_FORCE)
    
    // DUMMIES INT AND DOUBLE VARIABLES
    KRATOS_REGISTER_VARIABLE(DUMMY_SWITCH)
    
    //EXPORTS
    KRATOS_REGISTER_VARIABLE(EXPORT_ID)
    KRATOS_REGISTER_VARIABLE(PRINT_EXPORT_ID)

    //For DEM_FEM Element
    KRATOS_REGISTER_VARIABLE(LOCAL_DAMP_RATIO)
           
    //For DEM_FEM Condition
//    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( FORCE_RESIDUAL )
//    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( EXTERNAL_FORCE )

    // DUMMY VARIABLES FOR CALCULATE
    KRATOS_REGISTER_VARIABLE(CALCULATE_COMPUTE_NEW_NEIGHBOURS_HISTORICAL_DATA)
    KRATOS_REGISTER_VARIABLE(CALCULATE_COMPUTE_NEW_RIGID_FACE_NEIGHBOURS_HISTORICAL_DATA)
    KRATOS_REGISTER_VARIABLE(CALCULATE_SET_INITIAL_DEM_CONTACTS)
    KRATOS_REGISTER_VARIABLE(CALCULATE_SET_INITIAL_FEM_CONTACTS)
    KRATOS_REGISTER_VARIABLE(RIGID_FACE_ROTA_SPEED)
    KRATOS_REGISTER_VARIABLE(RIGID_FACE_AXIAL_SPEED)
    KRATOS_REGISTER_VARIABLE(RIGID_FACE_PROP_ID)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(RIGID_FACE_ROTA_ORIGIN_COORD)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(RIGID_FACE_ROTA_AXIAL_DIR)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(RIGID_FACE_ROTA_GLOBAL_VELOCITY)
    KRATOS_REGISTER_VARIABLE(RIGID_FACE_BEGIN_TIME)
    KRATOS_REGISTER_VARIABLE(RIGID_FACE_END_TIME)
    KRATOS_REGISTER_VARIABLE(RIGID_FACE_FLAG)
    KRATOS_REGISTER_VARIABLE(RIGID_FACE_COMPUTE_MOVEMENT)
            
    //SLS DEM-FEM
    KRATOS_REGISTER_VARIABLE(WALL_FRICTION)
    KRATOS_REGISTER_VARIABLE(SHEAR_STRESS)
    KRATOS_REGISTER_VARIABLE(NON_DIMENSIONAL_VOLUME_WEAR)
    KRATOS_REGISTER_VARIABLE(IMPACT_WEAR)
    KRATOS_REGISTER_VARIABLE(SEVERITY_OF_WEAR)
    KRATOS_REGISTER_VARIABLE(BRINELL_HARDNESS)
    KRATOS_REGISTER_VARIABLE(COMPUTE_WEAR)
    KRATOS_REGISTER_VARIABLE(IMPACT_WEAR_SEVERITY)
    KRATOS_REGISTER_VARIABLE(WALL_COHESION)
    //DEM_CLUSTERS
    KRATOS_REGISTER_VARIABLE(CLUSTER_VOLUME)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(PRINCIPAL_MOMENTS_OF_INERTIA)
    KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(LOCAL_ANGULAR_VELOCITY)
    KRATOS_REGISTER_VARIABLE(CHARACTERISTIC_LENGTH)
    KRATOS_REGISTER_VARIABLE(SPRAYED_MATERIAL)
            
    //BOUNDING BOX
    KRATOS_REGISTER_VARIABLE(BOUNDING_BOX_START_TIME)
    KRATOS_REGISTER_VARIABLE(BOUNDING_BOX_STOP_TIME)
            
    //FOR RECAREY FORMULAE
    KRATOS_REGISTER_VARIABLE(TOTAL_CONTACT_DISTANCES)
            
    // ELEMENTS
    KRATOS_REGISTER_ELEMENT("CylinderParticle2D", mCylinderParticle2D)
    KRATOS_REGISTER_ELEMENT("CylinderContinuumParticle2D", mCylinderContinuumParticle2D)
    KRATOS_REGISTER_ELEMENT("SphericParticle3D", mSphericParticle3D)
    KRATOS_REGISTER_ELEMENT("NanoParticle3D", mNanoParticle3D)
    KRATOS_REGISTER_ELEMENT("SphericContinuumParticle3D", mSphericContinuumParticle3D)
    KRATOS_REGISTER_ELEMENT("ThermalSphericContinuumParticle3D", mThermalSphericContinuumParticle3D)
    KRATOS_REGISTER_ELEMENT("ThermalSphericParticle3D", mThermalSphericParticle3D)
    KRATOS_REGISTER_ELEMENT("SinteringSphericContinuumParticle3D", mSinteringSphericContinuumParticle3D)
    KRATOS_REGISTER_ELEMENT("ParticleContactElement", mParticleContactElement)		
	
    KRATOS_REGISTER_CONDITION("SolidFace3D", mSolidFace3D3N)
    KRATOS_REGISTER_CONDITION("SolidFace3D3N", mSolidFace3D3N)
    KRATOS_REGISTER_CONDITION("SolidFace3D4N", mSolidFace3D4N)
    KRATOS_REGISTER_CONDITION("RigidFace3D", mRigidFace3D3N)
    KRATOS_REGISTER_CONDITION("RigidFace3D3N", mRigidFace3D3N)
    KRATOS_REGISTER_CONDITION("RigidFace3D4N", mRigidFace3D4N)
    KRATOS_REGISTER_CONDITION("RigidEdge3D", mRigidEdge3D2N)
    KRATOS_REGISTER_CONDITION("RigidEdge3D2N", mRigidEdge3D2N)

    KRATOS_REGISTER_ELEMENT("Cluster3D", mCluster3D)
    KRATOS_REGISTER_ELEMENT("CubeCluster3D", mCubeCluster3D)
    KRATOS_REGISTER_ELEMENT("PillCluster3D", mPillCluster3D)
    KRATOS_REGISTER_ELEMENT("EllipsoidCluster3D", mEllipsoidCluster3D)
    KRATOS_REGISTER_ELEMENT("CuboidCluster3D", mCuboidCluster3D)
    KRATOS_REGISTER_ELEMENT("CapsuleCluster3D", mCapsuleCluster3D)
    KRATOS_REGISTER_ELEMENT("SingleSphereCluster3D", mSingleSphereCluster3D)
    KRATOS_REGISTER_ELEMENT("BeadCluster3D", mBeadCluster3D)
    KRATOS_REGISTER_CONDITION("MAPcond", mMapCon3D3N)

    // SERIALIZER
    Serializer::Register("VariablesList", mVariablesList);
    Serializer::Register("PropertiesProxy", PropertiesProxy());

    Serializer::Register("DEM_D_Linear_viscous_Coulomb", DEM_D_Linear_viscous_Coulomb());
    Serializer::Register("DEM_D_Linear_viscous_Coulomb2D", DEM_D_Linear_viscous_Coulomb2D());
    Serializer::Register("DEM_D_Hertz_viscous_Coulomb", DEM_D_Hertz_viscous_Coulomb());
    Serializer::Register("DEM_D_Hertz_viscous_Coulomb2D", DEM_D_Hertz_viscous_Coulomb2D());
    Serializer::Register("DEM_D_JKR_Cohesive_Law", DEM_D_JKR_Cohesive_Law());    
    Serializer::Register("DEM_D_Bentonite_Colloid", DEM_D_Bentonite_Colloid());
    Serializer::Register("DEM_D_DMT_Cohesive_Law", DEM_D_DMT_Cohesive_Law());
    Serializer::Register("DEM_D_Linear_Custom_Constants", DEM_D_Linear_Custom_Constants());
    Serializer::Register("DEM_D_Conical_damage", DEM_D_Conical_damage());
    
    Serializer::Register("DEM_Dempack", DEM_Dempack());
    Serializer::Register("DEM_Dempack2D", DEM_Dempack2D());    
    Serializer::Register("DEM_KDEM", DEM_KDEM());
    Serializer::Register("DEM_KDEMFabric", DEM_KDEMFabric());
    Serializer::Register("DEM_Dempack_torque", DEM_Dempack_torque());
    Serializer::Register("DEM_Dempack_dev", DEM_Dempack_dev());
    Serializer::Register("DEM_KDEM2D", DEM_KDEM2D());
    Serializer::Register("DEM_ExponentialHC", DEM_ExponentialHC());
    
    std::cout << " done."                                  << std::endl;
  }
}  // namespace Kratos.


