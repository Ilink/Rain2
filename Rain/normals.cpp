#include "normals.h"

/*
function calcFaceNormals(vertIndexes, verts){
	var vecA = vec3.create();
	var vecB = vec3.create();
	var vecC = vec3.create();
	var edgeA = vec3.create();
	var edgeB = vec3.create();
	var weightedNormalA = vec3.create(), weightedNormalB = vec3.create(), weightedNormalC = vec3.create();
	var faces = [];
	var vertSet = buildArray(verts.length / 3);
	var vertA, vertB;

	// iterator goes over a set of vertex indexes that will form a triangle
	vertIter(vertIndexes, function(faceIndex, a, b, c){
		var normal = vec3.create();
		vertA = getVert(verts, a);
		vecA.set([vertA[0], vertA[1], vertA[2]]);
		vertB = getVert(verts, b);
		vecB.set([vertB[0], vertB[1], vertB[2]]);
		vertC = getVert(verts, c);
		vecC.set([vertC[0], vertC[1], vertC[2]]);

		// Make the edge vectors
		vec3.subtract(vecB, vecA, edgeA);
		vec3.subtract(vecC, vecA, edgeB);

		vec3.cross(edgeA, edgeB, normal);
		faces.push(normal);
		vec3.normalize(normal);

		assignVertProperties(vertSet, a, faceIndex, normal);
		assignVertProperties(vertSet, b, faceIndex, normal);
		assignVertProperties(vertSet, c, faceIndex, normal);
	});

	calculateSimpleNormalAvg(vertSet);

	var normals = [];
	$.each(vertSet, function(i, v){
	    normals.push(v.normal[0], v.normal[1], v.normal[2]);
	});

	return normals;
}
*/

using namespace std;

void calcFaceNormals(vector <vertex>& verts, vector<GLuint>& triIndex){
	glm::vec3 vecA;
	glm::vec3 vecB;
	glm::vec3 vecC;
	glm::vec3 edgeA;
	glm::vec3 edgeB;
}