#if !defined(KRATOS_MESHLESS_MEMBRANE_ELEMENT_H_INCLUDED )
#define  KRATOS_MESHLESS_MEMBRANE_ELEMENT_H_INCLUDED


// System includes
#include "includes/define.h"
#include "includes/element.h"
#include "includes/ublas_interface.h"
#include "includes/variables.h"

// External includes
#include "boost/smart_ptr.hpp"

// Project includes
#include "custom_elements/meshless_base_element.h"
#include "custom_elements/meshless_base_surface_element.h"

namespace Kratos
{
///@name Kratos Classes
///@{
/// Short class definition.
/** Kirchhoff-Love Shell. Optimized Isogeometric Analysis Element by Kiendl et al. .
*/
class MeshlessMembraneElement
    : public MeshlessBaseSurfaceElement
{
public:
    ///@name Type Definitions
    ///@{
    /// Counted pointer of MeshlessMembraneElement
    KRATOS_CLASS_POINTER_DEFINITION(MeshlessMembraneElement);
    ///@}
    ///@name Life Cycle
    ///@{
    /// Default constructor.
	// Constructor using an array of nodes
	MeshlessMembraneElement(IndexType NewId, GeometryType::Pointer pGeometry)
		: MeshlessBaseSurfaceElement(NewId, pGeometry)
	{};
	// Constructor using an array of nodes with properties
	MeshlessMembraneElement(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties)
		: MeshlessBaseSurfaceElement(NewId, pGeometry, pProperties)
	{};

	// default constructor necessary for serialization
	MeshlessMembraneElement() : MeshlessBaseSurfaceElement() {};

	/// Destructor.
	virtual ~MeshlessMembraneElement() override
	{};

	Element::Pointer Create(IndexType NewId, NodesArrayType const& ThisNodes, PropertiesType::Pointer pProperties) const override
	{
		return Kratos::make_shared< MeshlessMembraneElement >(NewId, GetGeometry().Create(ThisNodes), pProperties);
	};

    ///@}
    ///@name Operations
	///@{

	/**
	* This functions calculates both the RHS and the LHS
	* @param rLeftHandSideMatrix: The LHS
	* @param rRightHandSideVector: The RHS
	* @param rCurrentProcessInfo: The current process info instance
	* @param CalculateStiffnessMatrixFlag: The flag to set if compute the LHS
	* @param CalculateResidualVectorFlag: The flag to set if compute the RHS
	*/
	void CalculateAll(
		MatrixType& rLeftHandSideMatrix,
		VectorType& rRightHandSideVector,
		ProcessInfo& rCurrentProcessInfo,
		const bool CalculateStiffnessMatrixFlag,
		const bool CalculateResidualVectorFlag
	) override;


	/**
	* Calculate a double Variable on the Element Constitutive Law
	* @param rVariable: The variable we want to get
	* @param rOutput: The values obtained int the integration points
	* @param rCurrentProcessInfo: the current process info instance
	*/
	void CalculateOnIntegrationPoints(
		const Variable<double>& rVariable,
		std::vector<double>& rOutput,
		const ProcessInfo& rCurrentProcessInfo
	) override;

	/**
	* Calculate a Vector Variable on the Element Constitutive Law
	* @param rVariable: The variable we want to get
	* @param rOutput: The values obtained int the integration points
	* @param rCurrentProcessInfo: the current process info instance
	*/
	void CalculateOnIntegrationPoints(
		const Variable<Vector>& rVariable,
		std::vector<Vector>& rValues,
		const ProcessInfo& rCurrentProcessInfo
	) override;


	void CalculateDampingMatrix(
		MatrixType& rDampingMatrix,
		ProcessInfo& rCurrentProcessInfo) override;
	/**
	* This is called during the assembling process in order to calculate the elemental mass matrix
	* @param rMassMatrix: the elemental mass matrix
	* @param rCurrentProcessInfo: the current process info instance
	*/
	void CalculateMassMatrix(
		MatrixType& rMassMatrix,
		ProcessInfo& rCurrentProcessInfo
	) override;

	/**
	* Sets on rResult the ID's of the element degrees of freedom
	* @param rResult: The vector containing the equation id
	* @param rCurrentProcessInfo: The current process info instance
	*/
	void EquationIdVector(
		EquationIdVectorType& rResult,
		ProcessInfo& rCurrentProcessInfo
	) override;

	/**
	* Sets on rElementalDofList the degrees of freedom of the considered element geometry
	* @param rElementalDofList: The vector containing the dof of the element
	* @param rCurrentProcessInfo: The current process info instance
	*/
	void GetDofList(
		DofsVectorType& rElementalDofList,
		ProcessInfo& rCurrentProcessInfo
	) override;

	///@}

protected:
	/**
	* It initializes the material
	*/
	virtual void InitializeMaterial();
	/**
	* Called at the end of eahc solution step
	* @param rCurrentProcessInfo: the current process info instance
	*/
	void FinalizeSolutionStep(ProcessInfo& rCurrentProcessInfo) override;

private:
	///@name Static Member Variables
	///@{
	///@name Operations
	///@{
	void CalculateMetric( MetricVariables& metric ) override;


	/**
	* This functions updates the constitutive variables
	* @param rActualMetric: The actual metric
	* @param rThisConstitutiveVariables: The constitutive variables to be calculated
	* @param rValues: The CL parameters
	* @param ThisStressMeasure: The stress measure considered
	*/
	void CalculateConstitutiveVariables(
		MetricVariables& rActualMetric,
		ConstitutiveVariables& rThisConstitutiveVariables,
		ConstitutiveLaw::Parameters& rValues,
		const ConstitutiveLaw::StressMeasure ThisStressMeasure
	) override;
	///@}

	///@}
	///@name Serialization
	///@{

	friend class Serializer;

	void save(Serializer& rSerializer) const override
	{
		KRATOS_SERIALIZE_SAVE_BASE_CLASS(rSerializer, Element)
	}

	void load(Serializer& rSerializer) override
	{
		KRATOS_SERIALIZE_LOAD_BASE_CLASS(rSerializer, Element)
	}

	///@}

};	 // Class MeshlessMembraneElement
///@}

}  // namespace Kratos.

#endif // KRATOS_MESHLESS_MESHLESS_MEMBRANE_ELEMENT_H_INCLUDED  defined 