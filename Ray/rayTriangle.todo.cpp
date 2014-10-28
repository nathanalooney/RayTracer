#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"
#include <iostream>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void){

}
double RayTriangle::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){

	plane = Plane3D(v[0]->position, v[1]->position, v[2]->position);
	double t = (ray.position.dot(plane.normal.unit())+plane.distance)*-1/(ray.direction.dot(plane.normal));
	if (t < 0) {
		return -1;
	}
	double distance = (ray.direction*t).length();

	if (mx > 0 && distance > mx) {
		return -1;
	}

	v1 = v[0]->position - ray.position;
	v2 = v[1]->position - ray.position;
	Point3D norm = v2.crossProduct(v1).unit();
	Point3D p = ray.position + ray.direction*t;

	if ((p-ray.position).dot(norm) < 0) {
		return -1;
	}

	v1 = v[1]->position - ray.position;
	v2 = v[2]->position - ray.position;
	norm = v2.crossProduct(v1).unit();
	if ((p-ray.position).dot(norm) < 0) {
		return -1;
	}

	v1 = v[2]->position - ray.position;
	v2 = v[0]->position - ray.position;
	norm = v2.crossProduct(v1).unit();
	if ((p-ray.position).dot(norm) < 0) {
		return -1;
	}



	iInfo.iCoordinate = p;
	iInfo.material = material;
	iInfo.normal = plane.normal;

	return distance;
}
BoundingBox3D RayTriangle::setBoundingBox(void){
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	return -1;
}
