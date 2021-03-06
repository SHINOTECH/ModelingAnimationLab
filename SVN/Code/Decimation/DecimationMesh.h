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
#ifndef _DECIMATION_MESH
#define _DECIMATION_MESH

#include "Decimation/DecimationInterface.h"
#include "Geometry/HalfEdgeMesh.h"
#include "Util/Heap.h"
#include "Util/ColorMap.h"
#include <queue>

class DecimationMesh : public DecimationInterface, public HalfEdgeMesh
{
public :

  static const VisualizationMode CollapseCost;
  virtual std::list<VisualizationMode> GetVisualizationModes() {
    std::list<VisualizationMode> L = Mesh::GetVisualizationModes();
    L.push_back(CollapseCost);
    return L;
  }

  DecimationMesh() 
  { 
	  std::cout << "hi";
  }
  virtual ~DecimationMesh() { }

  /*! The EdgeCollapse is a Heapable type */

  virtual void Initialize();

  virtual void Update();

  virtual bool decimate();

  virtual bool decimate(unsigned int targetFaces);

  virtual void Render();

  virtual const char * GetTypeName() { return typeid(DecimationMesh).name(); }

protected :
  virtual void updateVertexProperties(Vertex v);

  virtual void updateFaceProperties(unsigned int ind);

  virtual void computeCollapse(Edge& e) = 0;

  virtual void Cleanup();
  

  //! The map that stores the edge collapses
  /*
  typedef std::multimap<float,HageMesh::IndexType> collapseType;
  collapseType collapseMap;
  */
  void updateEdgeCollapse(const Edge& e);
  Edge getNextCollapse();

  void drawText(const Vector3 & pos, const char * str);
  /*
  virtual bool save(std::ostream &os){
    os << "# DecimationMesh obj streamer\n# M&A 2008\n\n";
    os << "# Vertices\n";
    for(unsigned int i=0; i<GetNumVerts(); i++){
      os << "v " << v(i).pos[0] << " " <<  v(i).pos[1] << " " <<  v(i).pos[2] << "\n";
    }
    os << "\n# Faces\n";
    for(unsigned int i=0; i<GetNumFaces(); i++){
      if(!isFaceCollapsed(i)){
	EdgeIterator it = GetEdgeIterator(f(i).edge);
	os << "f " << it.GetEdgeVertexIndex()+1 << " "
	   << it.Next().GetEdgeVertexIndex()+1
	   << " " <<  it.Next().GetEdgeVertexIndex()+1 << "\n";
      }
    }
    return os.good();
  }*/
};

#endif
