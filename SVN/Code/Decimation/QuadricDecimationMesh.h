/*************************************************************************************************
 *
 * Modeling and animation (TNM079) 2007
 * Code base for lab assignments. Copyright:
 *   Gunnar Johansson (gunnar.johansson@itn.liu.se)
 *   Ken Museth (ken.museth@itn.liu.se)
 *   Michael Bang Nielsen (bang@daimi.au.dk)
 *   Ola Nilsson (ola.nilsson@itn.liu.se)
 *   Andreas Sˆderstrˆm (andreas.soderstrom@itn.liu.se)
 *
 *************************************************************************************************/
#ifndef _QUADRIC_DECIMATION_MESH
#define _QUADRIC_DECIMATION_MESH

#include <iomanip>
#include "Decimation/DecimationMesh.h"
#include "Math/Matrix4x4.h"

#ifdef __APPLE__
#include "GLUT/glut.h"
#else
#include "GL/glut.h"
#endif

class QuadricDecimationMesh : public virtual DecimationMesh
{
public :

	static const VisualizationMode QuadricIsoSurfaces;

	virtual std::list<VisualizationMode> GetVisualizationModes() {
		std::list<VisualizationMode> L = DecimationMesh::GetVisualizationModes();
		L.push_back(QuadricIsoSurfaces);
		return L;
	}

  QuadricDecimationMesh()
  {
  }
  virtual ~QuadricDecimationMesh() { }

  //! Initialize member data (error quadrics)
  virtual void Initialize();

protected :


  //! Compute the cost and new position for an edge collapse
  virtual void computeCollapse(Edge& e);
  //! Update vertex properties. Used after an edge collapse
  virtual void updateVertexProperties(Vertex v);
  //! Compute the quadric for a vertex
  Matrix4 createQuadricForVert(Vertex v) const;
  //! Copmute the quadric for a face
  Matrix4 createQuadricForFace(Face f) const;
	//! Render (redefined)
	virtual void Render();

  Vector4 getPlaneEquation(Face f) const
  {
	  auto vp = mMeshData.GetFaceVertices(f);
	  return Vector4(
		  f->Normal,
		  -f->Normal * vp[0]->Position
		  );
  }
};

#endif

