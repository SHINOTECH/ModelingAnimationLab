
#include "UniformCubicSplineSubdivisionCurve.h"

UniformCubicSplineSubdivisionCurve::UniformCubicSplineSubdivisionCurve(const std::vector<Vector3<float> > &joints,
                                                                       Vector3<float> lineColor,
                                                                       float lineWidth)
  : mCoefficients(joints), mControlPolygon(joints)
{
  this->mLineColor = lineColor;
  this->mLineWidth = lineWidth;
}


void UniformCubicSplineSubdivisionCurve::Subdivide()
{
  // Allocate space for new coefficients
  std::vector<Vector3<float> > newc(mCoefficients.size()*2-1);

  assert(mCoefficients.size() > 4 && "Need at least 5 points to subdivide");

  // Implement the subdivision scheme for a natural cubic spline here
  for(int i_n = 0; i_n < newc.size(); ++i_n)
  {
	  if(i_n == 0)
		  newc[i_n] = 8.0f*mCoefficients[0];
	  else if(i_n == newc.size()-1)
		  newc[i_n] = 8.0f*mCoefficients[mCoefficients.size()-1];
	  else if(i_n %2 == 1)
		  newc[i_n] = 4.0f*(mCoefficients[i_n/2]+mCoefficients[i_n/2 +1]);
	  else
		  newc[i_n] = mCoefficients[i_n/2 -1] + 6.0f*(mCoefficients[i_n/2]) + mCoefficients[i_n/2 +1];
	  newc[i_n]/=8.0f;		
  }

 mCoefficients = newc;
}


void UniformCubicSplineSubdivisionCurve::Render()
{
  // Apply transform
  glPushMatrix(); // Push modelview matrix onto stack

  // Convert transform-matrix to format matching GL matrix format
  // Load transform into modelview matrix
  glMultMatrixf( mTransform.ToGLMatrix().GetArrayPtr() );

  mControlPolygon.Render();

  // save line point and color states
  glPushAttrib(GL_POINT_BIT | GL_LINE_BIT | GL_CURRENT_BIT);

  // draw segments
  glLineWidth(mLineWidth);
  glColor3fv(mLineColor.GetArrayPtr());
  glBegin(GL_LINE_STRIP);
  // just draw the spline as a series of connected linear segments
  for(unsigned int i = 0; i < mCoefficients.size(); i++){
    glVertex3fv( mCoefficients.at(i).GetArrayPtr() );
  }
  glEnd();

  // restore attribs
  glPopAttrib();

  glPopMatrix();

  GLObject::Render();
}

